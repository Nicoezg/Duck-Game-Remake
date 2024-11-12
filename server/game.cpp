
#include "server/game.h"

#include <list>
#include <mutex>
#include <utility>

#include "common/actions/base/action_macros.h"
#include "common/actions/player/move.h"
#include "common/events/broadcast.h"
#include "common/events/connection/new_player.h"
#include "common/events/connection/start_game.h"
#include "common/queue.h"
#include "common/thread.h"
#include "game.h"

#define TIME_LOOP 200

Game::Game(int max_players)
    : commands(), notifier(&commands), running(true), next_player_id(0),
      players(), actual_players(0), max_players(max_players), started(false),
      admin_ids(), gameMap() {}

void Game::add(Socket &&socket) {
  notifier.notify(
      std::make_shared<NewPlayer>(get_actual_players(), get_max_players()));
  notifier.subscribe(std::move(socket));
}

bool Game::is_full(int new_players) const {
  return actual_players + new_players > max_players;
}

int Game::get_next_player_id() {
  next_player_id++;
  Player new_player(next_player_id, 0, 0, true, State::BLANK);
  players.insert_or_assign(next_player_id, new_player);
  actual_players++;

  Duck *duck = new Duck(next_player_id.load(), 0, 0, gameMap);
  gameMap.addPlayer(duck);

  return next_player_id;
}

void Game::add_admin_id(int id) {
  if (id <= actual_players) {
    admin_ids.push_back(id);
  }
}

void Game::notify_event(std::shared_ptr<Event> &event) {
  notifier.notify(event);
}

std::list<Player> Game::get_players() {
  std::list<Player> players_list;
  for (auto &player : players) {
    players_list.push_back(player.second);
  }
  return players_list;
}

void Game::valid_start() {
  std::shared_ptr<Action> action;

  bool ok = commands.try_pop(action);
  if (!ok || action->get_type() != START) {
    return;
  }
  start_game();
  notifier.notify(std::make_shared<StartGame>());
}

void Game::run() {
  try {
    while (running) {
      read_actions();
      std::this_thread::sleep_for(std::chrono::milliseconds(TIME_LOOP));
    }
  } catch (const ClosedQueue &e) {
  }
}

void Game::read_actions() {
  if (!started) {
    valid_start();
    return;
  }

  std::shared_ptr<Action> action;
  while (commands.try_pop(action)) {
    if (action != nullptr) {
      process_action(action);
    }
  }
}

void Game::process_action(std::shared_ptr<Action> &action) {
  int player_id = action->get_player_id();
  Duck *duck = gameMap.findPlayer(player_id);
  if (!duck)
    return;

  switch (action->get_type()) {
  case MOVE:
    duck->move(action->is_right());
    break;
  case JUMP:
    duck->jump();
    break;
  default:
    std::cout << "Acción inválida" << std::endl;
    break;
  }

  auto state = gameMap.getPlayerState(player_id);
  std::shared_ptr<Event> event = std::make_shared<Broadcast>(std::list<Player>{state});
  notify_event(event);
}

void Game::close() {
  running = false;
  commands.close();
  notifier.close();
}

bool Game::is_running() const { return running; }

int Game::get_max_players() const { return max_players; }

int Game::get_actual_players() const { return actual_players; }

bool Game::is_started() const { return started; }

void Game::start_game() { started = true; }