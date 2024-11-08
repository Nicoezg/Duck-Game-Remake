#include "mainwindow.h"
#include "lobby_updater.h"

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

    client.close();
    lobbyUpdater.close();
    lobbyUpdater.join();

    return 0;
}
