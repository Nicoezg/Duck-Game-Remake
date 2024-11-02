#ifndef TALLER_TP_CLIENT_H
#define TALLER_TP_CLIENT_H

#include <string>

#include "client_protocol.h"
#include "common/actions/action.h"
#include "common/connection/connection.h"
#include "common/events/event.h"
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

  /**
   * @brief Ejecuta la accion de leer.
   * Lee del protocolo una accion con el estado del juego.
   * Imprime por salida estandar el estado del juego.
   */
  void action_read();

  /**
   * Lee un comando de la entrada estandar.
   */
  std::string read_command();

  bool connect_to_game();

  std::string read_connect_command();

  void command_create();

  void command_join();

  void assign_player_ids(std::shared_ptr<Event> &event);

  void show_connection_info(const std::shared_ptr<Event> &event) const;

  bool valid_command(const std::string &command);

  void command_move();

  

public:
  Client(const char *hostname, const char *service_name);

  void run();

  void run_command(const std::string &command);

  int get_player_id1();
};

#endif // TALLER_TP_CLIENT_H
