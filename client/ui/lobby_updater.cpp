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
   } catch (ProtocolError &e) {
       // se cerro el protrocolo al terminar la conexion
   } catch (ClosedQueue &e) {
       // se cerro la cola de escritura
   } catch (...) {
       std::cerr << "Error desconocido lobby updater thread" << std::endl;
   }
  running = false;
}

void LobbyUpdater::update(const std::shared_ptr<Event> &event) {
    switch (event->get_type()) {
        case NEW_PLAYER:
            mainWindow->update_players_list(*event);
            break;
        case JOIN_GAME:
            mainWindow->show_connected_players(*event);
            break;
        case REFRESH_GAMES:
            mainWindow->RefreshServerList(*event);
            break;
        case CREATE_GAME:
            mainWindow->show_connected_players(*event);
            break;
        case START_GAME:
            running = false;
            mainWindow->close();
            break;
        default:
            break;
    }
}

void LobbyUpdater::close() { running = false; }