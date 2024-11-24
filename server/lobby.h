#ifndef TALLER_TP_LOBBY_H
#define TALLER_TP_LOBBY_H

class MonitorLobby;

#include "common/socket/socket.h"
#include "common/thread.h"
#include "monitor_games.h"
#include "server_protocol.h"
#include "common/actions/connection/join.h"
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

  std::shared_ptr<Event> create_game(Action& action);

  std::shared_ptr<Event> not_connected_to_game();

  std::shared_ptr<Event> join_game(Action &action);

  std::shared_ptr<Event> process_action(const std::shared_ptr<Action> &action,
                                        int &game_code);

    void set_players(const Action &action, int &player_id_1, int &player_id_2, const int &game_code);
};

#endif // TALLER_TP_LOBBY_H
