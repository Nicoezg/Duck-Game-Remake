#include "monitor_games.h"
#include "server/monitor_lobby.h"

MonitorGames::MonitorGames() : mtx(), games(), last_game_id(0) {}

int MonitorGames::create_game(std::string game_name, int max_players) {
  std::lock_guard<std::mutex> lock(mtx);

  last_game_id++;

  games[last_game_id] = std::make_unique<Game>(last_game_id, game_name, max_players);
  games[last_game_id]->start();

  return last_game_id;
}

bool MonitorGames::game_exists(int game_id) {
  std::lock_guard<std::mutex> lock(mtx);

  if (games.find(game_id) == games.end()) {
    return false;
  }
  return true;
}

int MonitorGames::get_player_id(int game_id, int new_players, std::string player_name) {
  std::lock_guard<std::mutex> lock(mtx);

  auto it = games.find(game_id);
  if (it != games.end() && !it->second->is_full(new_players)) {
    return it->second->get_next_player_id(player_name);
  }
  return SIN_ASIGNAR;
}

void MonitorGames::add_to_game(int game_id, Socket &&client) {
  std::lock_guard<std::mutex> lock(mtx);

  auto it = games.find(game_id);
  if (it != games.end()) {
    it->second->add(std::move(client));
    return;
  }
  throw std::runtime_error("Game not found");
}

void MonitorGames::close_and_clean_games() {
  std::lock_guard<std::mutex> lock(mtx);
  for (auto &game : games) {
    game.second->close();
    game.second->join();
  }
  games.clear();
}

void MonitorGames::clean_closed_games() {
  std::lock_guard<std::mutex> lock(mtx);
  for (auto it = games.begin(); it != games.end();) {
    if (!it->second->is_running()) {
      it->second->close();
      it->second->join();
      it = games.erase(it);
    } else {
      it++;
    }
  }
}

GameRoom MonitorGames::get_game_room(int& game_code) {
    std::lock_guard<std::mutex> lock(mtx);

    auto it = games.find(game_code);
    if (it != games.end()) {
        return it->second->get_game_room();
    }
    return {};
}

std::list<GameRoom> MonitorGames::get_not_started_games(){
    std::lock_guard<std::mutex> lock(mtx);

    std::list<GameRoom> not_started_games;
    for (auto &game : games) {
        if (!game.second->is_started() && !game.second->is_full(UN_JUGADOR) ) {
            not_started_games.emplace_back(game.second->get_game_room());
        }
    }
    return not_started_games;
}

std::list<PlayerData> MonitorGames::get_players_data(int game_code) {
    std::lock_guard<std::mutex> lock(mtx);

    auto it = games.find(game_code);
    if (it != games.end()) {
        return it->second->get_players_data();
    }
    throw std::runtime_error("Game not found");
}
