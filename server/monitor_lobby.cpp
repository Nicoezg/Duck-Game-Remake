#include "server/monitor_lobby.h"
#include "monitor_games.h"

MonitorLobby::MonitorLobby() : mtx(), games(), clients() {}

void MonitorLobby::add_client(Socket &&client) {
  std::lock_guard<std::mutex> lock(mtx);

  auto lobby = std::make_unique<Lobby>(std::move(client), &this->games);

  lobby->start();
  clients.push_back(std::move(lobby));

  games.clean_closed_games();
  clean_closed_clients();
}

void MonitorLobby::clean_closed_clients() {
  clients.remove_if([](const std::unique_ptr<Lobby> &client) {
    if (client->is_closed()) {
      client->close();
      client->join();
      return true;
    }
    return false;
  });
}

void MonitorLobby::close_and_clean_clients() {
  for (auto &client : clients) {
    client->close();
    client->join();
  }
  clients.clear();
}

void MonitorLobby::close() {
  std::lock_guard<std::mutex> lock(mtx);

  games.close_and_clean_games();

  close_and_clean_clients();
}
