#include "server/notifier.h"

#include <memory>
#include <utility>

#include "common/queue.h"
#include "common/protocol/action.h"
#include "common/socket/liberror.h"
#include "common/socket/socket.h"
#include "common/connection/connection_sender.h"

Notifier::Notifier(Queue<Action> &commands, Queue<Action> &events)
        : commands(commands), events(events), is_running(true), mtx_client() {}

void Notifier::subscribe(Socket client) {
    std::lock_guard<std::mutex> lock(mtx_client);

    // Creamos un nuevo cliente con un smart pointer traspasantole el socket
    std::shared_ptr<ConnectionSender> new_client(
            new ConnectionSender(std::move(client), commands, Encoder()));

    clients.push_back(new_client);

    new_client->start();

    // Aprovechamos para limpiar los clientes que ya cerraron la conexión
    remove_closed_connections();
}

void Notifier::remove_closed_connections() {
    clients.remove_if([](const std::shared_ptr<ConnectionSender> &client) {
        if (client->is_closed()) {
            client->join();
            return true;
        }
        return false;
    });
}

void Notifier::notify(const Action &action) {
    std::lock_guard<std::mutex> lock(mtx_client);
    for (auto &client: clients) {
        try {
            if (!client->is_closed()) {
                client->push_action(action);
            }
        } catch (const ClosedQueue &e) {
            client->close();
        }
    }
}

void Notifier::run() {
    while (is_running) {
        try {
            // Espera bloqueado hasta que haya un evento para notificar
            notify(events.pop());
        } catch (const ClosedQueue &e) {
            return;
        }
    }
}

void Notifier::close() {
    is_running = false;
    for (auto &client: clients) {
        if (!client->is_closed()) {
            client->close();
        }
        client->join();
    }
    clients.clear();
}
