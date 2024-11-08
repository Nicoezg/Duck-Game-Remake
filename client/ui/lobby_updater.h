//
// Created by fran on 05/11/24.
//

#ifndef TALLER_TP_LOBBY_UPDATER_H
#define TALLER_TP_LOBBY_UPDATER_H


#include <memory>
#include "common/thread.h"
#include "client/communication/client.h"
#include "mainwindow.h"


class LobbyUpdater : public Thread {

private:
    std::atomic<bool> running;
    Client* client;
    MainWindow* mainWindow;

public:
    LobbyUpdater(Client* client, MainWindow* mainWindow);

    void run() override;

    void update(const std::shared_ptr<Event>& event);

    void close();

};


#endif //TALLER_TP_LOBBY_UPDATER_H
