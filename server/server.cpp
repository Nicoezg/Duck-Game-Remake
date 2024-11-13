
#include "server/server.h"

#include <atomic>
#include <utility>

#include <sys/socket.h>

#include "common/actions/connection/create.h"
#include "common/socket/liberror.h"
#include "common/socket/socket.h"
#include "common/thread.h"

Server::Server(const char *service_name)
    : socket(service_name), lobby(), is_running(true) {
    Configurations::loadConfig();
}

void Server::run() {
  try {
    while (is_running) {
      Socket skt = socket.accept(); // Espera a que se conecte un cliente
      lobby.add_client(
          std::move(skt)); // Traspasa el socket al monitor del lobby
    }
  } catch (const LibError &e) {
  }
}

void Server::close() {
  is_running = false;
  socket.shutdown(SHUT_RDWR);
  socket.close();
  lobby.close();
}
