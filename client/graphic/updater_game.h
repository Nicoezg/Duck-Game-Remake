//
// Created by fran on 14/11/24.
//

#ifndef TALLER_TP_UPDATER_GAME_H
#define TALLER_TP_UPDATER_GAME_H

#include "common/thread.h"
#include "client/communication/client.h"
#include "client/graphic/game.h"
#include "game.h"

class UpdaterGame : public Thread {

private:
    std::atomic<bool> running;
    Client &client;
    Game &game;

public:
    UpdaterGame(Client &client, Game &game);

    void run() override;

    void close();

    void process_event(const std::shared_ptr<Event> &event);
};


#endif //TALLER_TP_UPDATER_GAME_H
