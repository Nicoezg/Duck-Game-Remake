#include "server/lobby.h"
#include "common/actions/connection/join.h"
#include "common/events/connection/game_creation.h"
#include "common/events/connection/game_join.h"
#include "common/events/connection/refresh_games.h"
#include "common/protocol/common/protocol_error.h"
#include "monitor_games.h"
#include "server/monitor_lobby.h"
#include <sys/socket.h>

Lobby::Lobby(Socket &&client, MonitorGames *games)
    : client(std::move(client)), protocol(&this->client, Encoder()),
      games(games), is_running(true), is_connected(false) {}

void Lobby::run() {
  try {
    int game_code = SIN_CODIGO;
    while (!is_connected) {
      std::shared_ptr<Action> action = protocol.read_element();
      std::shared_ptr<Event> response = process_action(*action, game_code);
      protocol.send_element(response);
      is_connected = response->is_connected();
    }
    games->add_to_game(game_code, std::move(client));

  } catch (const ProtocolError &e) {
    is_running = false;
    is_connected = false;
    return;
  }
  is_running = false;
}

std::shared_ptr<Event> Lobby::process_action(const Action &action,
                                             int &game_code) {
  std::shared_ptr<Event> response;
  switch (action.get_type()) {
  case CREATE_REQUEST:
    response = create_game(action);
    game_code = response->get_game_room().get_game_code();
    break;
  case JOIN_REQUEST:
    response = join_game(action);
    game_code = response->get_game_room().get_game_code();
    break;
  case REFRESH_REQUEST:
    response = std::make_shared<Refresh>(games->get_not_started_games());
    break;
  default:
    response = not_connected_to_game();
    break;
  }
  return response;
}

std::shared_ptr<Event> Lobby::not_connected_to_game() {
  return std::make_shared<GameJoin>(SIN_CODIGO, SIN_CODIGO, false, GameRoom(),
                                    std::list<PlayerData>());
}

void Lobby::set_players(const Action &action, int &player_id_1,
                        int &player_id_2, const int &game_code) {
  player_id_1 = games->get_player_id(game_code, action.get_game_mode(),
                                     action.get_player_name_1());
  player_id_2 = SIN_ASIGNAR;
  if (player_id_1 == SIN_ASIGNAR) {
    return;
  }

  if (action.get_game_mode() == DOS_JUGADORES) {
    player_id_2 = games->get_player_id(game_code, action.get_game_mode() - 1,
                                       action.get_player_name_2());
  }
}
std::shared_ptr<Event> Lobby::join_game(const Action &action) {
  int game_code = action.get_game_code();
  if (!games->game_exists(game_code)) {
    return not_connected_to_game();
  }
  int player_id_1, player_id_2;
  set_players(action, player_id_1, player_id_2, game_code);

  GameRoom game_room = games->get_game_room(game_code);
  if (game_room.get_game_code() == SIN_CODIGO) {
    return not_connected_to_game();
  }
  std::list<PlayerData> players_data = games->get_players_data(game_code);

  if (player_id_1 == SIN_ASIGNAR) {
    return not_connected_to_game();
  }
  return std::make_shared<GameJoin>(player_id_1, player_id_2, true, game_room,
                                    players_data);
}

std::shared_ptr<Event> Lobby::create_game(const Action &action) {
  int game_code =
      games->create_game(action.get_game_name(), action.get_max_players());

  int player_id_1, player_id_2;
  set_players(action, player_id_1, player_id_2, game_code);

  GameRoom game_room = games->get_game_room(game_code);
  std::list<PlayerData> players_data = games->get_players_data(game_code);
  return std::make_shared<GameCreation>(game_room, player_id_1, player_id_2,
                                        players_data);
}

bool Lobby::is_closed() const { return !is_running; }

void Lobby::close() {
  if (!is_running || is_connected)
    return;
  is_running = false;
  client.shutdown_and_close(SHUT_RDWR);
}
