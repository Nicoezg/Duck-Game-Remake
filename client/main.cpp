#include "mainwindow.h"
#include "lobby_updater.h"
#include "client/graphic/game.h"

#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    if (argc != 3) {
        throw std::runtime_error("invalid arguments quantity");
    }
    Client client(argv[1], argv[2]);
    MainWindow w(&client);
    LobbyUpdater lobbyUpdater(&client, &w);

    client.run();
    lobbyUpdater.start();

    w.show();
    app.exec();

    lobbyUpdater.close();
    lobbyUpdater.join();

    if (client.is_closed()) {
        return 0;
    }

    auto sdl_game = Game(client);
    sdl_game.start();
    client.close();

    return 0;
}
