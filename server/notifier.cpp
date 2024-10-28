#include "server/notifier.h"

#include <memory>
#include <utility>

#include "common/queue.h"
#include "common/socket/liberror.h"
#include "common/socket/socket.h"

Notifier::Notifier(Queue<std::shared_ptr<Action>> *commands)
    : clients(), commands(commands), events(), mtx_client() {}

void Notifier::subscribe(Socket &&client) {
  std::lock_guard<std::mutex> lock(mtx_client);

  // Creamos una nueva conexión con el cliente
  std::shared_ptr<ServerConnection> new_client(
      new ServerConnection(std::move(client), Encoder(), commands, &events));

  clients.push_back(new_client);

  new_client->start();

  // Aprovechamos para limpiar los clientes que ya cerraron la conexión
  remove_closed_connections();
}

void Notifier::remove_closed_connections() {
  clients.remove_if([](const std::shared_ptr<ServerConnection> &client) {
    if (client->is_closed()) {
      client->join();
      return true;
    }
    return false;
  });
}

void Notifier::notify(const std::shared_ptr<Event> &event) {
  std::lock_guard<std::mutex> lock(mtx_client);
  for (auto &client : clients) {
    try {
      if (!client->is_closed()) {
        client->push(event);
      }
    } catch (const ClosedQueue &e) {
      client->close();
    }
  }
}

void Notifier::close() {
  for (auto &client : clients) {
    if (!client->is_closed()) {
      client->close();
    }
    client->join();
  }
  clients.clear();
}
