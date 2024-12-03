//
// Created by fran on 22/10/24.
//

#include "actions_protocol.h"

#include "common/actions/connection/join.h"
#include "common/actions/connection/refresh_games.h"
#include "common/actions/player/aim_upwards.h"
#include "common/actions/player/jump_flap.h"
#include "common/actions/player/move.h"
#include "common/actions/player/pick_drop.h"
#include "common/actions/player/play_dead.h"
#include "common/actions/player/shoot.h"
#include "common/actions/player/still.h"
#include <iostream>
#include <stdexcept>

ActionsProtocol::ActionsProtocol(Socket *socket, Encoder encoder)
    : Protocol(socket), encoder(encoder) {}

std::shared_ptr<Action> ActionsProtocol::read_create_action() {
  std::vector<int8_t> data(READ_CREATE_SIZE);
  read(data.data(), data.size());
  GameMode game_mode = encoder.decode_game_mode(data);
  int max_players = encoder.decode_max_players(data);
  std::string game_name = read_player_name();
  std::string player_name_1 = read_player_name();
  std::string player_name_2 = read_player_name();
  return std::make_shared<Create>(game_mode, max_players, game_name,
                                  player_name_1, player_name_2);
}

std::shared_ptr<Action> ActionsProtocol::read_join_action() {
  std::vector<int8_t> data(READ_JOIN_SIZE);
  read(data.data(), data.size());
  int game_code = encoder.decode_game_code(data);
  GameMode game_mode = encoder.decode_game_mode(data);
  std::string player_name_1 = read_player_name();
  std::string player_name_2 = read_player_name();
  return std::make_shared<Join>(game_code, game_mode, player_name_1,
                                player_name_2);
}

std::shared_ptr<Action> ActionsProtocol::read_element() {
  switch (read_action_type()) {
  case CREATE_REQUEST:
    return read_create_action();
  case JOIN_REQUEST:
    return read_join_action();
  case MOVE:
    return read_move_action();

  case REFRESH_REQUEST:
    return std::make_shared<RefreshGames>();

  case START:
    return std::make_shared<Action>(START);
  case JUMP_FLAP:
    return read_jump_flap_action();
  case STILL:
    return read_still_action();
  case PLAY_DEAD:
    return read_play_dead_action();
  case SHOOT:
    return read_shoot_action();
  case AIM_UPWARDS:
    return read_aiming_upwards_action();
  case PICK_DROP:
    return read_pick_drop_action();
  case CHEAT:
    return read_cheat_action();

  default:
    throw std::runtime_error(
        "ActionsProtocol try to action_read invalid action.");
  }
}

void ActionsProtocol::send_element(const Action &action) {
  ActionType type = action.get_type();

  switch (type) {
  case CREATE_REQUEST:
    return send_create_action(action);
  case JOIN_REQUEST:
    return send_join_action(action);
  case MOVE:
    return send_move_action(action);

  case REFRESH_REQUEST:
    return send_refresh_action(action);

  case START:
    return send_start(action);
  case JUMP_FLAP:
    return send_jump_flap_action(action);
  case STILL:
    return send_still_action(action);
  case PLAY_DEAD:
    return send_play_dead_action(action);
  case SHOOT:
    return send_shoot_action(action);
  case AIM_UPWARDS:
    return send_aiming_upwards_action(action);
  case PICK_DROP:
    return send_pick_drop_action(action);
  case CHEAT:
    return send_cheat_action(action);
  default:
    throw std::runtime_error("ActionsProtocol try to send unknown action");
  }
}

ActionType ActionsProtocol::read_action_type() {
  std::vector<int8_t> data(ACTION_TYPE_SIZE);
  read(data.data(), data.size());
  return encoder.decode_action_type(data);
}

void ActionsProtocol::send_refresh_action(const Action &action) {
  std::vector<int8_t> data(ACTION_TYPE_SIZE);
  size_t offset = 0;
  encoder.encode_action_type(action.get_type(), &data[offset]);
  send(data.data(), data.size());
}

void ActionsProtocol::send_create_action(const Action &action) {
  int player_names_size = LEN_SIZE * 3 + action.get_game_name().size() +
                          action.get_player_name_1().size() +
                          action.get_player_name_2().size();
  std::vector<int8_t> data(SEND_CREATE_SIZE + player_names_size);
  size_t offset = 0;
  offset += encoder.encode_action_type(action.get_type(), &data[offset]);
  offset += encoder.encode_game_mode(action.get_game_mode(), &data[offset]);
  offset += encoder.encode_max_players(action.get_max_players(), &data[offset]);
  add_name(action.get_game_name(), data, offset);
  add_name(action.get_player_name_1(), data, offset);
  add_name(action.get_player_name_2(), data, offset);
  send(data.data(), data.size());
}

void ActionsProtocol::send_join_action(const Action &action) {
  int player_names_size = LEN_SIZE * 2 + action.get_player_name_1().size() +
                          action.get_player_name_2().size();
  std::vector<int8_t> data(SEND_JOIN_SIZE + player_names_size);
  size_t offset = 0;
  offset += encoder.encode_action_type(action.get_type(), &data[offset]);
  offset += encoder.encode_game_code(action.get_game_code(), &data[offset]);
  offset += encoder.encode_game_mode(action.get_game_mode(), &data[offset]);
  add_name(action.get_player_name_1(), data, offset);
  add_name(action.get_player_name_2(), data, offset);
  send(data.data(), data.size());
}

void ActionsProtocol::send_move_action(const Action &action) {
  std::vector<int8_t> data(SEND_MOVE_SIZE);
  size_t offset = 0;
  offset += encoder.encode_action_type(action.get_type(), &data[offset]);
  offset += encoder.encode_player_id(action.get_player_id(), &data[offset]);
  encoder.encode_bool(action.is_right(), &data[offset]);
  send(data.data(), data.size());
}

void ActionsProtocol::send_jump_flap_action(const Action &action) {
  std::vector<int8_t> data(SEND_JUMP_SIZE);
  size_t offset = 0;
  offset += encoder.encode_action_type(action.get_type(), &data[offset]);
  offset += encoder.encode_player_id(action.get_player_id(), &data[offset]);
  encoder.encode_bool(action.is_jumping_flapping(), &data[offset]);
  send(data.data(), data.size());
}

void ActionsProtocol::send_still_action(const Action &action) {
  std::vector<int8_t> data(SEND_STILL_SIZE);
  size_t offset = 0;
  offset += encoder.encode_action_type(action.get_type(), &data[offset]);
  offset += encoder.encode_player_id(action.get_player_id(), &data[offset]);
  encoder.encode_bool(action.is_still(), &data[offset]);
  send(data.data(), data.size());
}

void ActionsProtocol::send_play_dead_action(const Action &action) {
  std::vector<int8_t> data(SEND_PLAY_DEAD_SIZE);
  size_t offset = 0;
  offset += encoder.encode_action_type(action.get_type(), &data[offset]);
  offset += encoder.encode_player_id(action.get_player_id(), &data[offset]);
  encoder.encode_bool(action.is_playing_dead(), &data[offset]);
  send(data.data(), data.size());
}

void ActionsProtocol::send_shoot_action(const Action &action) {
  std::vector<int8_t> data(SEND_SHOOT_SIZE);
  size_t offset = 0;
  offset += encoder.encode_action_type(action.get_type(), &data[offset]);
  offset += encoder.encode_player_id(action.get_player_id(), &data[offset]);
  encoder.encode_bool(action.is_shooting(), &data[offset]);
  send(data.data(), data.size());
}

void ActionsProtocol::send_aiming_upwards_action(const Action &action) {
  std::vector<int8_t> data(SEND_AIMING_UPWARDS_SIZE);
  size_t offset = 0;
  offset += encoder.encode_action_type(action.get_type(), &data[offset]);
  offset += encoder.encode_player_id(action.get_player_id(), &data[offset]);
  encoder.encode_bool(action.is_aiming_upwards(), &data[offset]);
  send(data.data(), data.size());
}

void ActionsProtocol::send_pick_drop_action(const Action &action) {
  std::vector<int8_t> data(SEND_PICK_DROP_SIZE);
  size_t offset = 0;
  offset += encoder.encode_action_type(action.get_type(), &data[offset]);
  offset += encoder.encode_player_id(action.get_player_id(), &data[offset]);
  encoder.encode_bool(action.is_picking_dropping(), &data[offset]);
  send(data.data(), data.size());
}

std::shared_ptr<Action> ActionsProtocol::read_move_action() {
  std::vector<int8_t> data(READ_MOVE_SIZE);
  read(data.data(), data.size());
  int player_id = encoder.decode_player_id(data);
  bool is_right = encoder.decode_bool(data);
  return std::make_shared<Move>(player_id, is_right);
}

void ActionsProtocol::send_start(const Action &action) {
  std::vector<int8_t> data(ACTION_TYPE_SIZE);
  size_t offset = 0;
  encoder.encode_action_type(action.get_type(), &data[offset]);
  send(data.data(), data.size());
}

std::shared_ptr<Action> ActionsProtocol::read_jump_flap_action() {
  std::vector<int8_t> data(READ_JUMP_SIZE);
  read(data.data(), data.size());
  int player_id = encoder.decode_player_id(data);
  bool is_right = encoder.decode_bool(data);
  return std::make_shared<JumpFlap>(player_id, is_right);
}

std::shared_ptr<Action> ActionsProtocol::read_still_action() {
  std::vector<int8_t> data(READ_STILL_SIZE);
  read(data.data(), data.size());
  int player_id = encoder.decode_player_id(data);
  bool is_right = encoder.decode_bool(data);
  return std::make_shared<Still>(player_id, is_right);
}

std::shared_ptr<Action> ActionsProtocol::read_play_dead_action() {
  std::vector<int8_t> data(READ_PLAY_DEAD_SIZE);
  read(data.data(), data.size());
  int player_id = encoder.decode_player_id(data);
  bool is_right = encoder.decode_bool(data);
  return std::make_shared<PlayDead>(player_id, is_right);
}

std::shared_ptr<Action> ActionsProtocol::read_shoot_action() {
  std::vector<int8_t> data(READ_SHOOT_SIZE);
  read(data.data(), data.size());
  int player_id = encoder.decode_player_id(data);
  bool is_right = encoder.decode_bool(data);
  return std::make_shared<Shoot>(player_id, is_right);
}

std::shared_ptr<Action> ActionsProtocol::read_aiming_upwards_action() {
  std::vector<int8_t> data(READ_AIMING_UPWARDS_SIZE);
  read(data.data(), data.size());
  int player_id = encoder.decode_player_id(data);
  bool is_right = encoder.decode_bool(data);
  return std::make_shared<AimUpwards>(player_id, is_right);
}

std::shared_ptr<Action> ActionsProtocol::read_pick_drop_action() {
  std::vector<int8_t> data(READ_PICK_DROP_SIZE);
  read(data.data(), data.size());
  int player_id = encoder.decode_player_id(data);
  bool is_right = encoder.decode_bool(data);
  return std::make_shared<PickDrop>(player_id, is_right);
}

std::string ActionsProtocol::read_player_name() {
  std::vector<int8_t> data(LEN_SIZE);
  read(data.data(), data.size());
  int len = encoder.decode_len(data);
  if (len == 0) {
    return "";
  }
  data.resize(len);
  read(data.data(), data.size());
  return encoder.decode_string(data, len);
}

void ActionsProtocol::add_name(const std::string &name,
                               std::vector<int8_t> &data, size_t &offset) {
  offset += encoder.encode_len(name.size(), &data[offset]);
  if (name.empty()) {
    return;
  }
  offset += encoder.encode_string(name, &data[offset], name.size());
}

void ActionsProtocol::send_cheat_action(const Action &action) {
  std::vector<int8_t> data(SEND_CHEAT_SIZE);
  size_t offset = 0;
  offset += encoder.encode_action_type(action.get_type(), &data[offset]);
  offset += encoder.encode_player_id(action.get_player_id(), &data[offset]);
  encoder.encode_cheat_id(action.get_cheat_id(), &data[offset]);
  send(data.data(), data.size());
}

std::shared_ptr<Action> ActionsProtocol::read_cheat_action() {
  std::vector<int8_t> data(READ_CHEAT_SIZE);
  read(data.data(), data.size());
  int player_id = encoder.decode_player_id(data);
  CheatId cheat_id = encoder.decode_cheat_id(data);
  return std::make_shared<Cheat>(player_id, cheat_id);
}