//
// Created by cafrada on 22/04/23.
//

#ifndef TP_2_CLIENT_CLASS_H
#define TP_2_CLIENT_CLASS_H

#include <string>

#include "common/connection/connection_sender.h"
#include "common/protocol/protocol.h"
#include "common/queue.h"

class Client {
private:
  Queue<Action> queue;
  ConnectionSender sender;
  u_int32_t game_code;
  u_int16_t player_id;

  /**
   * @brief Ejecuta la accion de leer.
   * Lee del protocolo una accion con el estado del juego.
   * Imprime por salida estandar el estado del juego.
   */
  void action_read();

  /**
   * @brief Ejecuta la accion de un comando.
   */
  void run_command(const std::string &command);

  /**
   * Lee un comando de la entrada estandar.
   */
  std::string read_command();

  /**
   * Envia una accion atacar a traves del protocolo.
   */
  void action_attack();

public:
  Client(const char *hostname, const char *service_name);

  /**
   * @brief Inicia la ejecucion del cliente esperando
   * comandos por la entrada estandar.
   */
  void run();

  bool connect_to_game();

  std::string read_connect_command();

};

#endif // TP_2_CLIENT_CLASS_H
