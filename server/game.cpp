
#include "server/game.h"

#include <list>
#include <mutex>
#include <utility>

#include "common/queue.h"
#include "common/thread.h"
#include "common/protocol/action_macros.h"

#define TIME_LOOP 1500


Game::Game()
        : commands(), events(),
          notifier(commands, events), running(true),
          next_player_id(0) {}

void Game::add(Socket &&socket) {
    notifier.subscribe(std::move(socket));
}

u_int16_t Game::get_next_player_id() { return ++next_player_id; }


void Game::position_command(Action &action) { notifier.notify(action); }

void Game::read_actions() {
    Action action;

    // Intenta obtener un comando de la cola de comandos de forma no bloqueante
    while (commands.try_pop(action)) {
        if (action.get_name() == ACTION_ATTACK) {
            notifier.notify(action);
        } else {
            std::cout << "Comando invalido" << std::endl;
        }
    }
}

void Game::run() {
    try {
        notifier.start();

        while (running) {

            // Leo los comandos de los clientes
            read_actions();

            // Espero 200 ms por requerimiento del enunciado
            std::this_thread::sleep_for(std::chrono::milliseconds(TIME_LOOP));
        }
        notifier.join();
    } catch (const ClosedQueue &e) {
    }
}

void Game::close() {
    running = false;
    commands.close();
    events.close();
    notifier.close();
}

bool Game::is_running() const { return running; }
