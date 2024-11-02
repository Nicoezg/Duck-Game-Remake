
#include "server/game.h"

#include <list>
#include <mutex>
#include <utility>

#include "common/actions/action_macros.h"
#include "common/actions/move.h"
#include "common/events/broadcast.h"
#include "common/queue.h"
#include "common/thread.h"

#define TIME_LOOP 200

Game::Game()
    : commands(), notifier(&commands), running(true), next_player_id(0),
      players() {}

void Game::add(Socket &&socket) { notifier.subscribe(std::move(socket)); }

int Game::get_next_player_id() {
  next_player_id++;
  players.insert_or_assign(next_player_id, Player(next_player_id, 0, 0, true, State::BLANK));
  return next_player_id;
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

void Game::read_actions() {
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
      players.at(action->get_player_id()).move(action->is_right());
      event = std::make_shared<Broadcast>(get_players());
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
