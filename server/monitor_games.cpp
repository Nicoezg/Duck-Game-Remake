#include "monitor_games.h"
#include "server/monitor_lobby.h"

MonitorGames::MonitorGames() : mtx(), games(), last_game_id(0) {}

int MonitorGames::create_game(int max_players) {
  std::lock_guard<std::mutex> lock(mtx);

  last_game_id++;

  games[last_game_id] = std::make_unique<Game>(max_players);
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

int MonitorGames::get_player_id(int game_id, int new_players) {
  std::lock_guard<std::mutex> lock(mtx);

  auto it = games.find(game_id);
  if (it != games.end() && !it->second->is_full(new_players)) {
    return it->second->get_next_player_id();
  }
  throw std::runtime_error("Game not found or full");
}

int MonitorGames::get_player_id_admin(int game_id, int new_players) {
    std::lock_guard<std::mutex> lock(mtx);

    auto it = games.find(game_id);
    if (it != games.end() && !it->second->is_full(new_players)) {
        auto id = it->second->get_next_player_id();
        it->second->add_admin_id(id);
        return id;
    }
    throw std::runtime_error("Game not found or full");
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
      ++it;
    }
  }
}

void MonitorGames::get_max_and_actual_players(int game_code, int& actual, int& max) {
    std::lock_guard<std::mutex> lock(mtx);

    auto it = games.find(game_code);
    if (it != games.end()) {
        actual = it->second->get_actual_players();
        max = it->second->get_max_players();
        return;
    }
    throw std::runtime_error("Game not found");
}

std::list<GameRoom> MonitorGames::get_not_active_games(){
    std::lock_guard<std::mutex> lock(mtx);

    std::list<GameRoom> not_active_games;
    for (auto &game : games) {
        if (!game.second->is_started() && !game.second->is_full(UN_JUGADOR) ) {
            not_active_games.emplace_back(game.first, game.second->get_actual_players(), game.second->get_max_players());
        }
    }
    return not_active_games;
}