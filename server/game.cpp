
#include "server/game.h"

#include <list>
#include <mutex>
#include <utility>

#include "common/queue.h"
#include "common/thread.h"
#include "common/actions/action_macros.h"

#define TIME_LOOP 1500


Game::Game()
        : commands(),
          notifier(&commands), running(true),
          next_player_id(0) {}

void Game::add(Socket &&socket) {
    notifier.subscribe(std::move(socket));
}

int Game::get_next_player_id() { return ++next_player_id; }

void Game::notify_event(std::shared_ptr<Event>& event) { notifier.notify(event); }

void Game::read_actions() {
    std::shared_ptr<Action> action;

    // Intenta obtener un comando de la cola de comandos de forma no bloqueante
    while (commands.try_pop(action)) {
        if (action->get_name() == ACTION_MOVE) {
            std::cout << "Movimiento" << std::endl;
        } else {
            std::cout << "Comando invalido" << std::endl;
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
