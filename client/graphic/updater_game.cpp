//
// Created by fran on 14/11/24.
//

#include "updater_game.h"

UpdaterGame::UpdaterGame(Client &client, Game &game) : running(false), client(client), game(game) {}

void UpdaterGame::run() {
    running = true;
    while (running) {
        std::shared_ptr<Event> event = client.read_event();
        if (event == nullptr) {
            continue;
        }
        process_event(event);
    }
}

void UpdaterGame::process_event(const std::shared_ptr<Event> &event) {
    switch (event->get_type()) {
        case BROADCAST:
            game.update(*event);
            std::cout << "Actualizado" << std::endl;
            break;
        default:
            break;
    }
}

void UpdaterGame::close() {
    running = false;
}
