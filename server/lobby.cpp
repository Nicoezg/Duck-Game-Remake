//
// Created by fran on 19/05/24.
//

#include "server/lobby.h"

Lobby::Lobby() : mtx(), games(), last_game_id(0), clients() {}

void Lobby::add_client(Socket &&client) {
    std::lock_guard<std::mutex> lock(mtx);

    auto lobby_client = std::make_unique<LobbyClient>(std::move(client), this);

    lobby_client->start();
    clients.push_back(std::move(lobby_client));

    clean_closed_clients();
    clean_closed_games();
}

void Lobby::clean_closed_clients() {
    clients.remove_if([](const std::unique_ptr<LobbyClient> &client) {
        if (client->is_closed()) {
            client->close();
            client->join();
            return true;
        }
        return false;
    });
}

void Lobby::clean_closed_games() {
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

void Lobby::set_player_id(u_int32_t game_id, u_int16_t &player_id) {
    std::lock_guard<std::mutex> lock(mtx);

    auto it = games.find(game_id);
    if (it != games.end()) {
        player_id = it->second->get_next_player_id();
        return;
    }
    throw std::runtime_error("Game not found");
}

void Lobby::add_to_game(u_int32_t game_id, Socket &&client) {
    std::lock_guard<std::mutex> lock(mtx);

    auto it = games.find(game_id);
    if (it != games.end()) {
        it->second->add(std::move(client));
        return;
    }
    throw std::runtime_error("Game not found");
}

bool Lobby::game_exists(u_int32_t game_id) {
    std::lock_guard<std::mutex> lock(mtx);

    if (games.find(game_id) == games.end()) {
        return false;
    }
    return true;
}

u_int32_t Lobby::create_game() {
    std::lock_guard<std::mutex> lock(mtx);

    last_game_id++;

    games[last_game_id] = std::make_unique<Game>();
    games[last_game_id]->start();

    return last_game_id;
}

void Lobby::close() {
    std::lock_guard<std::mutex> lock(mtx);

    close_and_clean_games();

    close_and_clean_clients();
}

void Lobby::close_and_clean_clients() {
    for (auto &client: clients) {
        client->close();
        client->join();
    }
    clients.clear();
}

void Lobby::close_and_clean_games() {
    for (auto &game: games) {
        game.second->close();
        game.second->join();
    }
    games.clear();
}
