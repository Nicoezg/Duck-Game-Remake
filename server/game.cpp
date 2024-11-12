
#include "server/game.h"

#include <list>
#include <mutex>
#include <utility>

#include "common/actions/base/action_macros.h"
#include "common/actions/player/move.h"
#include "common/events/broadcast.h"
#include "common/queue.h"
#include "common/thread.h"
#include "common/events/connection/new_player.h"
#include "common/events/connection/start_game.h"

#define TIME_LOOP 200

Game::Game(int max_players)
    : commands(), notifier(&commands), running(true), next_player_id(0),
      players(), actual_players(0), max_players(max_players), started(false), admin_ids() {}

void Game::add(Socket &&socket) {
    notifier.notify(std::make_shared<NewPlayer>(get_actual_players(),get_max_players()));
    notifier.subscribe(std::move(socket));
}

bool Game::is_full(int new_players) const {
  return actual_players  + new_players > max_players;
}

int Game::get_next_player_id() {
  next_player_id++;
  // La línea de abajo está de ejemplo, no compila y no funciona realmente así.
  // Hay que obtener las cosas me parece
  Weapon weapon(NO_WEAPON);
  Helmet helmet(NO_HELMET);
  Chestplate chestplate(false);
  players.insert_or_assign(next_player_id, Player(next_player_id, 0, 0, true, State::BLANK, weapon, helmet, chestplate));
  actual_players++;
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

void Game::valid_start(){
    std::shared_ptr<Action> action;

    bool ok = commands.try_pop(action);
    if (!ok || action->get_type() != START) {
        return;
    }
    start_game();
    notifier.notify(std::make_shared<StartGame>());
}

void Game::read_actions() {
    if (!started){
        valid_start();
        return;
    }

  std::shared_ptr<Action> action;

  // Intenta obtener un comando de la cola de comandos de forma no bloqueante
  while (commands.try_pop(action)) {
    if (action == nullptr) {
      return;
    }

    std::shared_ptr<Event> event;
    switch (action->get_type()) {
    case MOVE:
      if (players.find(action->get_player_id()) == players.end()) {
        std::cout << "Jugador no encontrado" << std::endl;
        break;
      }
      // players.at(action->get_player_id()).move(action->is_right());
      // Hay que conseguir la lista de bullets, crates y weapons. La linea de abajo está de ejemplo.
      event = std::make_shared<Broadcast>(get_players(), std::list<Bullet>(), std::list<Crate>(), std::list<Weapon>());
      notify_event(event);
      break;
    default:
      std::cout << "Comando invalido" << std::endl;
      break;
    }
  }
}

void Game::run() {
  try {
    while (running) {

      // Leo los comandos de los clientes
      read_actions();

      // Espero 200 ms por requerimiento del enunciado
      std::this_thread::sleep_for(std::chrono::milliseconds(TIME_LOOP));
    }
  } catch (const ClosedQueue &e) {
  }
}

void Game::close() {
  running = false;
  commands.close();
  notifier.close();
}

bool Game::is_running() const { return running; }

int Game::get_max_players() const {
    return max_players;
}

int Game::get_actual_players() const {
    return actual_players;
}

bool Game::is_started() const {
    return started;
}

void Game::start_game() {
    started = true;
}