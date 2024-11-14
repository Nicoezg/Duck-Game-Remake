#include "client.h"

#include "common/actions/connection/join.h"
#include "common/actions/player/move.h"
#include "common/events/base/event.h"
#include "common/protocol/common/protocol_error.h"
#include <iostream>
#include <utility>

#define NO_CONECTADO 0

Client::Client(const char *hostname, const char *service_name)
        : commands(), events(),
          connection(Socket(hostname, service_name), Encoder(), &this->events,
                     &this->commands),
          game_code(0), player_id_1(SIN_ASIGNAR), player_id_2(SIN_ASIGNAR),
          game_mode(SIN_ESPECIFICAR),connected(false),
          player_1_name(), player_2_name(){}


void Client::run() {
    connection.start();
}

void Client::close() {
    if (!connection.is_closed()) {
        connection.close();
    }
    connection.join();
}

void Client::send_action(std::shared_ptr<Action> &action) {
    if (game_code == NO_CONECTADO && action->get_type() != JOIN_REQUEST &&
        action->get_type() != CREATE_REQUEST && action->get_type() != REFRESH_REQUEST) {
        std::cout << "No se puede realizar la accion" << std::endl;
        return;
    }

    commands.push(action);
}

void Client::assign_player_ids(std::shared_ptr<Event> &event) {
    player_id_1 = event->get_player_id_1();
    player_id_2 = event->get_player_id_2();
    connected = true;

    std::cout << "Conectado al juego " << game_code << std::endl;
    std::cout << "ID Jugador 1: " << player_id_1 << std::endl;
    std::cout << "ID Jugador 2: " << player_id_2 << std::endl;
    std::cout << "Maximo de jugadores: " << event->get_max_players() << std::endl;
    if (event->get_type() == JOIN_GAME) {
        std::cout << "Jugadores conectados: " << event->get_actual_players() << std::endl;
    }
}

int Client::get_game_code() const {
    return game_code;
}

void Client::set_game_code(int code) {
    game_code = code;
}

void Client::set_player_1_name(std::string name) {
    player_1_name = std::move(name);
}

void Client::set_player_2_name(std::string name) {
    player_2_name = std::move(name);
}

std::shared_ptr<Event> Client::read_event() {
    std::shared_ptr<Event> event = events.pop();
    switch (event->get_type()) {
        case CREATE_GAME:
            game_code = event->get_game_code();
            assign_player_ids(event);
            break;
        case JOIN_GAME:
            assign_player_ids(event);
            break;
        default:
            break;
    }
    return event;
}

int Client::get_player_id_1() const {
    return player_id_1;
}

int Client::get_player_id_2() const {
    return player_id_2;
}

bool Client::is_connected() const {
    return connected;
}

std::shared_ptr<Event> Client::try_read() {
    std::shared_ptr<Event> event;
    events.try_pop(event);
    return event;
}