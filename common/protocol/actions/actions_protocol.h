//
// Created by fran on 22/10/24.
//

#ifndef TALLER_TP_ACTIONS_PROTOCOL_H
#define TALLER_TP_ACTIONS_PROTOCOL_H

#include "common/actions/player/cheat.h"
#include "common/protocol/common/encoder.h"
#include "common/protocol/common/protocol.h"
#include "common/socket/socket.h"
#include <atomic>
#include <memory>

#define ACTION_TYPE_SIZE sizeof(int8_t)
#define GAME_CODE_SIZE sizeof(uint32_t)
#define GAME_MODE_SIZE sizeof(int8_t)
#define PLAYER_ID_SIZE sizeof(uint16_t)
#define MAX_PLAYER_SIZE sizeof(uint8_t)
#define IS_RIGHT_SIZE sizeof(uint8_t)
#define LEN_SIZE sizeof(uint8_t)
#define CHEAT_ID sizeof(uint8_t)

#define READ_JOIN_SIZE (GAME_CODE_SIZE + GAME_MODE_SIZE)
#define READ_CREATE_SIZE (GAME_MODE_SIZE + MAX_PLAYER_SIZE)
#define READ_MOVE_SIZE (PLAYER_ID_SIZE + IS_RIGHT_SIZE)
#define READ_JUMP_SIZE (PLAYER_ID_SIZE + IS_RIGHT_SIZE)
#define READ_STILL_SIZE (PLAYER_ID_SIZE + IS_RIGHT_SIZE)
#define READ_PLAY_DEAD_SIZE (PLAYER_ID_SIZE + IS_RIGHT_SIZE)
#define READ_SHOOT_SIZE (PLAYER_ID_SIZE + IS_RIGHT_SIZE)
#define READ_AIMING_UPWARDS_SIZE (PLAYER_ID_SIZE + IS_RIGHT_SIZE)
#define READ_PICK_DROP_SIZE (PLAYER_ID_SIZE + IS_RIGHT_SIZE)
#define READ_CHEAT_SIZE (PLAYER_ID_SIZE + CHEAT_ID)

#define SEND_JOIN_SIZE (ACTION_TYPE_SIZE + READ_JOIN_SIZE)
#define SEND_CREATE_SIZE (ACTION_TYPE_SIZE + READ_CREATE_SIZE)
#define SEND_MOVE_SIZE (ACTION_TYPE_SIZE + READ_MOVE_SIZE)
#define SEND_JUMP_SIZE (ACTION_TYPE_SIZE + READ_JUMP_SIZE)
#define SEND_STILL_SIZE (ACTION_TYPE_SIZE + READ_STILL_SIZE)
#define SEND_PLAY_DEAD_SIZE (ACTION_TYPE_SIZE + READ_PLAY_DEAD_SIZE)
#define SEND_SHOOT_SIZE (ACTION_TYPE_SIZE + READ_SHOOT_SIZE)
#define SEND_AIMING_UPWARDS_SIZE (ACTION_TYPE_SIZE + READ_AIMING_UPWARDS_SIZE)
#define SEND_PICK_DROP_SIZE (ACTION_TYPE_SIZE + READ_PICK_DROP_SIZE)
#define SEND_CHEAT_SIZE (ACTION_TYPE_SIZE + READ_CHEAT_SIZE)

class ActionsProtocol : public Protocol {
private:
  Encoder encoder;

  ActionType read_action_type();

  void send_create_action(const Action &action);

  void send_refresh_action(const Action &action);

  void send_join_action(const Action &action);

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
  void send_element(const Action &action);

  void send_move_action(const Action &action);

  void send_jump_flap_action(const Action &action);

  void send_still_action(const Action &action);

  void send_play_dead_action(const Action &action);

  void send_shoot_action(const Action &action);

  void send_aiming_upwards_action(const Action &action);

  void send_pick_drop_action(const Action &action);

  void send_cheat_action(const Action &action);

  std::shared_ptr<Action> read_move_action();

  std::shared_ptr<Action> read_jump_flap_action();

  std::shared_ptr<Action> read_still_action();

  std::shared_ptr<Action> read_play_dead_action();

  std::shared_ptr<Action> read_shoot_action();

  std::shared_ptr<Action> read_aiming_upwards_action();

  std::shared_ptr<Action> read_pick_drop_action();

  std::shared_ptr<Action> read_cheat_action();

  void send_start(const Action &action);

  std::string read_player_name();

  void add_name(const std::string &name, std::vector<int8_t> &data,
                size_t &offset);
};

#endif // TALLER_TP_ACTIONS_PROTOCOL_H