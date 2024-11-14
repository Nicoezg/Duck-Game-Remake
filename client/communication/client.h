#ifndef TALLER_TP_CLIENT_H
#define TALLER_TP_CLIENT_H

#include <string>

#include "client_protocol.h"
#include "common/actions/base/action.h"
#include "common/connection/connection.h"
#include "common/events/base/event.h"
#include "common/game_mode.h"
#include "common/queue.h"

using ClientConnection =
    Connection<ClientProtocol, std::shared_ptr<Event>, std::shared_ptr<Action>>;

class Client {
private:
  Queue<std::shared_ptr<Action>> commands;
  Queue<std::shared_ptr<Event>> events;
  ClientConnection connection;
  int game_code;
  int player_id_1;
  int player_id_2;
  GameMode game_mode;
  bool connected;

  std::string player_1_name;
    std::string player_2_name;


  void assign_player_ids(std::shared_ptr<Event> &event);

public:
  Client(const char *hostname, const char *service_name);

  void run();

    void send_action(std::shared_ptr<Action> &action);

    void close();

    void set_game_code(int code);

    int get_game_code() const;

    int get_player_id_1() const;

    int get_player_id_2() const;

    void set_player_1_name(std::string name);

    void set_player_2_name(std::string name);

    std::shared_ptr<Event> read_event();

    std::shared_ptr<Event> try_read();

    bool is_connected() const;


};

#endif // TALLER_TP_CLIENT_H
