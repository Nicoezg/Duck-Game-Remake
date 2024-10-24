#include "client/client.h"

#include "common/protocol/common/protocol_error.h"
#include "common/actions/join.h"
#include "common/events/event.h"
#include <iostream>


#define NO_CONECTADO 0

Client::Client(const char *hostname, const char *service_name) : commands(), events(),
        connection(Socket(hostname, service_name), Encoder(), &this->events, &this->commands),
        game_code(0), player_id_1(SIN_ASIGNAR), player_id_2(SIN_ASIGNAR), game_mode(SIN_ESPECIFICAR) {}

std::string Client::read_command() {
    std::string action_key;
    std::cin >> action_key;
    return action_key;
}

void Client::run() {
    connection.start();

    bool connected = false;
    try {
        connected = connect_to_game();
    } catch (const ProtocolError &e) {
        connected = false;
    }
    if (!connected) {
        connection.close();
        return;
    }

    std::string action_key = read_command();
    try {
        while (!connection.is_closed() && action_key != ACTION_EXIT) {
            run_command(action_key);
            action_key = read_command();
        }
    } catch (const std::exception &e) {
        std::cerr << "Unexpected error: " << e.what() << std::endl;
    }
    if (!connection.is_closed()) {
        connection.close();
    }
    connection.join();
}

bool Client::connect_to_game() {
    std::string command = read_connect_command();
    if (command == ACTION_EXIT) {
        return false;
    }
    while ((game_code == NO_CONECTADO || player_id_1 == SIN_ASIGNAR) && command != ACTION_EXIT) {
        command = read_connect_command();
        if (command == ACTION_EXIT) {
            return false;
        }
    }
    return true;
}

std::string Client::read_connect_command() {
    std::string command;
    std::cin >> command;
    while (command != ACTION_JOIN && command != ACTION_CREATE && command != ACTION_EXIT) {
        std::cout << "Ingrese " << ACTION_JOIN << " para unirse a un juego o "
                  << ACTION_CREATE << " para crear uno" << std::endl;
        std::cin >> command;
    }
    run_command(command);
    return command;
}


void Client::run_command(const std::string &command) {
    if (command == ACTION_EXIT) {
        connection.close();
    } else if (command == ACTION_JOIN) {
        command_join();
    } else if (command == ACTION_CREATE) {
        command_create();
    } else {
        std::cout << "Comando invalido" << std::endl;
    }
}

void Client::command_join() {
    int mode;
    std::cin >> game_code;
    std::cin >> mode;
    this->game_mode = GameMode(mode);
    std::shared_ptr<Action> action = std::make_shared<Join>(game_code, game_mode);
    commands.push(action);
    action_read();
}

void Client::command_create() {
    int mode;
    std::cin >> mode;
    this->game_mode = GameMode(mode);
    std::shared_ptr<Action> action = std::make_shared<Create>(game_mode);
    commands.push(action);
    action_read();
}

void Client::action_read() {
    std::shared_ptr<Event> event = events.pop();
    switch (event->get_type()) {
        case CREATE_GAME:
            game_code = event->get_game_code();
            assign_player_ids(event);
            break;
        case JOIN_GAME:
            assign_player_ids(event);
            break;
        case BROADCAST:
            break;
    }
    show_connection_info(event);
}

void Client::show_connection_info(const std::shared_ptr<Event> &event) const {
    if (event->is_connected()) {
        std::cout << "Conectado al juego " << game_code <<
                  " con PlayerId_1: " << player_id_1 <<
                  " con PlayerId_2: " << player_id_2 << std::endl;
    } else {
        std::cout << "No se pudo conectar al juego" << std::endl;
    }
}

void Client::assign_player_ids(std::shared_ptr<Event> &event) {
    player_id_1 = event->get_player_id_1();
    player_id_2 = event->get_player_id_2();
}


