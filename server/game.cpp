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

Game::Game(int id, std::string name, int max_players)
        : id(id), name(name), commands(), notifier(&commands), running(true), next_player_id(0),
          actual_players(0), max_players(max_players), started(false),
          gameMap(), players() {
}

void Game::add(Socket &&socket) {
    notifier.notify(std::make_shared<NewPlayer>(get_actual_players(), get_max_players(), get_players_data()));
    notifier.subscribe(std::move(socket));
}

bool Game::is_full(int new_players) const {
    return actual_players + new_players > max_players;
}

int Game::get_next_player_id(std::string player_name) {
    next_player_id++;
    players[next_player_id] = player_name;
    gameMap.addPlayer(next_player_id);
    actual_players++;

    return next_player_id;
}

void Game::notify_event(std::shared_ptr<Event> &event) {
    notifier.notify(event);
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
            checkNewRound();
            notify_state();
            checkFinishGame();
        }
    } catch (const ClosedQueue &e) {
    }
}

void Game::checkFinishGame() {
    if (gameMap.check_finished()) {
        int winner_id = gameMap.get_winner_id();
        std::shared_ptr<Event> event = std::make_shared<GameOver>(PlayerData(winner_id, players[winner_id]), 10);
        notify_event(event);
        running = false;
    }
}

void Game::checkNewRound() {
    if (gameMap.pauseForScores()){
        /* std::map<uint8_t, std::string, std::greater<>> scoresMap;
        for (auto player: players) {
            scoresMap[gameMap.getPlayerWins(player.first)] = player.second;
        }
        std::vector<std::string> names; // cambiar a list
        std::vector<uint8_t> scores; // cambiar a list
        for (auto score: scoresMap) {
            names.push_back(score.second);
            scores.push_back(score.first);
        }
        std::shared_ptr<Event> event = std::make_shared<Score>(names, score);
        notify_event(event); */
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
    // getCratesState y getItemSpawnsState no estan implementados
    std::shared_ptr<Event> event = std::make_shared<Broadcast>(gameMap.getState(), gameMap.getBulletsState(),
    gameMap.getCratesState(), gameMap.getItemSpawnsState(), gameMap.getExplosionsState());
    notify_event(event);
}

void Game::close() {
    running = false;
    notifier.close();
}

bool Game::is_running() const {
    return running;
}

int Game::get_max_players() const {
    return max_players;
}

int Game::get_actual_players() const {
    return actual_players;
}

GameRoom Game::get_game_room() const {
    return {id, name, actual_players, max_players};
}

std::list<PlayerData> Game::get_players_data() {
    std::list<PlayerData> players_data;

    for (auto &player : players) {
        players_data.emplace_back(player.first, player.second);
    }
    return players_data;
}

bool Game::is_started() const { return started; }

void Game::start_game() {
    started = true;
    notifier.notify(std::make_shared<StartGame>());
}