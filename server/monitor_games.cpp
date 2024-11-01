#include "monitor_games.h"
#include "server/monitor_lobby.h"

MonitorGames::MonitorGames() : mtx(), games(), last_game_id(0) {}

int MonitorGames::create_game() {
  std::lock_guard<std::mutex> lock(mtx);

  last_game_id++;

  games[last_game_id] = std::make_unique<Game>();
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

uint16_t MonitorGames::get_player_id(int game_id) {
  std::lock_guard<std::mutex> lock(mtx);

  auto it = games.find(game_id);
  if (it != games.end()) {
    return it->second->get_next_player_id();
  }
  throw std::runtime_error("Game not found");
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
