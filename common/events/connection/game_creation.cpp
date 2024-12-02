//
// Created by fran on 21/10/24.
//

#include "game_creation.h"

#include <utility>

GameCreation::GameCreation(GameRoom game_room, int player_id_1, int player_id_2,
                           std::list<PlayerData> players_data)
    : Event(CREATE_GAME), game_room(std::move(game_room)),
      player_id_1(player_id_1), player_id_2(player_id_2),
      players_data(std::move(players_data)) {}

GameRoom GameCreation::get_game_room() const { return game_room; }

int GameCreation::get_player_id_1() const { return player_id_1; }

int GameCreation::get_player_id_2() const { return player_id_2; }

std::list<PlayerData> GameCreation::get_players_data() const {
  return players_data;
}

bool GameCreation::is_connected() const { return true; }

int GameCreation::get_max_players() const {
  return game_room.get_max_players();
}

int GameCreation::get_actual_players() const {
  return game_room.get_actual_players();
}
