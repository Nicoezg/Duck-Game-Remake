//
// Created by fran on 22/10/24.
//

#ifndef TALLER_TP_ACTIONS_PROTOCOL_H
#define TALLER_TP_ACTIONS_PROTOCOL_H

#include "common/protocol/common/encoder.h"
#include "common/protocol/common/protocol.h"
#include "common/socket/socket.h"
#include <atomic>
#include <memory>

class ActionsProtocol : public Protocol {
private:
  Encoder encoder;

  ActionType read_action_type();

  void send_create_action(const std::shared_ptr<Action> &action);

  void send_refresh_action(const std::shared_ptr<Action> &action);

  void send_join_action(const std::shared_ptr<Action> &action);

  std::shared_ptr<Action> read_create_action();

  std::shared_ptr<Action> read_join_action();

public:
  ActionsProtocol(Socket *socket, Encoder encoder);

  /**
   * @brief Lee una accion del socket.
   * @return Accion leida.
   */
  std::shared_ptr<Action> read_element();

  /**
   * @brief Envia una accion a traves del socket codificandola.
   * @param action Accion a enviar.
   */
  void send_element(const std::shared_ptr<Action> &action);

  void send_move_action(const std::shared_ptr<Action> &action);

  void send_jump_flap_action(const std::shared_ptr<Action> &action);

  void send_still_action(const std::shared_ptr<Action> &action);

  void send_play_dead_action(const std::shared_ptr<Action> &action);

  void send_shoot_action(const std::shared_ptr<Action> &action);

  void send_aiming_upwards_action(const std::shared_ptr<Action> &action);

  void send_pick_drop_action(const std::shared_ptr<Action> &action);

  std::shared_ptr<Action> read_move_action();

  std::shared_ptr<Action> read_jump_flap_action();

  std::shared_ptr<Action> read_still_action();

  std::shared_ptr<Action> read_play_dead_action();

  std::shared_ptr<Action> read_shoot_action();

  std::shared_ptr<Action> read_aiming_upwards_action();

  std::shared_ptr<Action> read_pick_drop_action();

  void send_start(const std::shared_ptr<Action> &action);
};

#endif // TALLER_TP_ACTIONS_PROTOCOL_H