#ifndef PROTOCOL_H
#define PROTOCOL_H

#define ATTACK_CODE 0x03
#define TYPE_KILL_CODE 0x04
#define TYPE_REVIVE_CODE 0x05
#define BROADCAST_CODE 0x06

#include <atomic>
#include <cstdint>
#include <mutex>
#include <string>
#include <vector>

#include "action.h"
#include "encoder.h"
#include "common/socket/socket.h"

class Protocol {
private:
  Socket *socket;
  std::atomic<bool> is_closed;
  Encoder encoder;
  /**
   * @brief Envia la cantidad de bytes especificada a traves del socket.
   */
  void send(void *data, size_t size);

  /**
   * @brief Lee del socket la cantidad de bytes especificada.
   */
  void read(void *data, size_t size);

  /**
   * @brief Lee del socket 1 byte y lo decodifica en un char.
   */
  int8_t read_action_code();

  /**
   * @brief Envia un mensaje de la accion atacar.
   */
  void send_attack(const Action &action);

  /**
   * @brief Codigica y envia un mensaje con el estado de la accion.
   * @param code Codigo de la accion.
   * @param action Accion a enviar.
   */
  void send_broadcast(const Action &action);

  /**
   * @brief Lee del socket 5 bytes y los decodifica en una accion.
   */
  Action read_message();

public:
  Protocol(Socket *socket, Encoder encoder);


  bool is_open();

  /**
   * @brief Lee una accion del socket.
   * @return Accion leida.
   */
  Action read_action();

  /**
   * @brief Envia una accion a traves del socket codificandola.
   * @param action Accion a enviar.
   */
  void send_action(const Action &action);

  void send_game_code(uint32_t game_code, uint16_t player_id);

  void read_game_data(uint32_t &game_code, uint16_t &player_id);

  uint32_t read_game_code();

  void send_game_code(uint32_t game_code);

    uint16_t read_player_id();
};

#endif // PROTOCOL_H
