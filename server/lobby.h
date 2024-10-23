#ifndef TALLER_TP_LOBBY_H
#define TALLER_TP_LOBBY_H

class MonitorLobby;

#include "common/socket/socket.h"
#include "common/thread.h"
#include "monitor_games.h"
#include "server_protocol.h"
#include <atomic>

const int SIN_CODIGO = 0;

class Lobby : public Thread {
private:
    Socket client;
    ServerProtocol protocol;
    MonitorGames *games;
    std::atomic<bool> is_running;
    std::atomic<bool> is_connected;

public:
    explicit Lobby(Socket &&client, MonitorGames *games);

    void run() override;

    bool is_closed() const;

    void close();

    std::shared_ptr<Event> create_game();

    std::shared_ptr<Event> not_connected_to_game();

    std::shared_ptr<Event> join_game(int game_code);

    std::shared_ptr<Event> process_action(const std::shared_ptr<Action> &action);
};

#endif // TALLER_TP_LOBBY_H
