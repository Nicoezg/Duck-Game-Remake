//
// Created by fran on 05/11/24.
//

#include "lobby_updater.h"

#include <utility>

LobbyUpdater::LobbyUpdater(Client *client, MainWindow *mainWindow)
    : running(true), client(client), mainWindow(mainWindow) {}

void LobbyUpdater::run() {
  try {
    while (running) {
      std::shared_ptr<Event> event = client->read_event();
      update(event);
    }
  } catch (const std::exception &e) {
  }
  running = false;
}

void LobbyUpdater::update(const std::shared_ptr<Event> &event) {
    switch (event->get_type()) {
        case NEW_PLAYER:
            mainWindow->show_connected_players(event, client->get_game_code());
            break;
        case JOIN_GAME:
            mainWindow->show_connected_players(event, client->get_game_code());
            break;
        case REFRESH_GAMES:
            mainWindow->RefreshServerList(event);
            break;
        case CREATE_GAME:
            mainWindow->show_connected_players(event, client->get_game_code());
            break;
        case START_GAME:
            running = false;
            mainWindow->exit();
            break;
        default:
            break;
    }
}

void LobbyUpdater::close() { running = false; }