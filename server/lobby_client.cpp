//
// Created by fran on 20/05/24.
//

#include "server/lobby_client.h"
#include "server/lobby.h"
#include "common/protocol/protocol_error.h"
#include <sys/socket.h>

LobbyClient::LobbyClient(Socket &&client, Lobby *lobby)
        : client(std::move(client)), protocol(&this->client, Encoder()),
          lobby(lobby), is_running(true), is_connected(false) {}

void LobbyClient::run() {
    try {
        bool ready = false;
        while (!ready) {
            u_int32_t game_code = protocol.read_game_code();
            if (game_code == SIN_CODIGO) {
                game_code = lobby->create_game();
            } else if (!lobby->game_exists(game_code)) {
                protocol.send_game_code(SIN_CODIGO, 0);
                continue;
            }
            game_setup(game_code);
            ready = true;
        }
    } catch (const ProtocolError &e) {
        is_running = false;
        is_connected = false;
        return;
    }
    is_running = false;
    is_connected = true;
}

void LobbyClient::game_setup(u_int32_t game_code) {
    u_int16_t player_id;
    lobby->set_player_id(game_code, player_id);
    protocol.send_game_code(game_code, player_id);
    lobby->add_to_game(game_code, std::move(client));
}

bool LobbyClient::is_closed() const { return !is_running; }

void LobbyClient::close() {
    if (!is_running || is_connected)
        return;
    is_running = false;
    client.shutdown(SHUT_RDWR);
    client.close();
}
