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
#include "common/events/game_over.h"

#define TIME_LOOP 20

Game::Game(int max_players)
        : commands(), notifier(&commands), running(true), next_player_id(0),
          players(), actual_players(0), max_players(max_players), started(false),
          admin_ids(), gameMap() {
}

void Game::add(Socket &&socket) {
    notifier.notify(std::make_shared<NewPlayer>(get_actual_players(), get_max_players()));
    notifier.subscribe(std::move(socket));
}

bool Game::is_full(int new_players) const {
    return actual_players + new_players > max_players;
}

int Game::get_next_player_id() {
    next_player_id++;

    gameMap.addPlayer(next_player_id);
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

std::list<PlayerDTO> Game::get_players() {
    std::list<PlayerDTO> players_list;
    for (auto &player: players) {
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
    std::shared_ptr<Event> event = std::make_shared<MapDTO>(gameMap.getMapDTO());
    notify_event(event);
}

void Game::run() {
    try {
        while (running) {
            std::this_thread::sleep_for(std::chrono::milliseconds(TIME_LOOP));
            read_actions();
            if (!started) {
                continue;
            }
            gameMap.update();
            notify_state();

            if (gameMap.checkFinished()) {
                std::shared_ptr<Event> event = std::make_shared<GameOver>(1, 10);
                notify_event(event);
                running = false;
            }
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
    gameMap.process_action(action);
}

void Game::notify_state() {
    std::shared_ptr<Event> event = std::make_shared<Broadcast>(gameMap.getState(), gameMap.getBulletsState());
    notify_event(event);
}

void Game::close() {
    running = false;
    notifier.close();
}

bool Game::is_running() const { return running; }

int Game::get_max_players() const { return max_players; }

int Game::get_actual_players() const { return actual_players; }

bool Game::is_started() const { return started; }

void Game::start_game() {
    started = true;
    notifier.notify(std::make_shared<StartGame>());
}