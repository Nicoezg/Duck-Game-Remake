#include "client/client.h"

#include "common/protocol/common/protocol_error.h"
#include "common/actions/join.h"
#include "common/events/event.h"
#include <iostream>


#define NO_CONECTADO 0

Client::Client(const char *hostname, const char *service_name) : commands(), events(),
        connection(Socket(hostname, service_name), Encoder(), &this->events, &this->commands),
        game_code(0), player_id(0) {}

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
    while ((game_code == NO_CONECTADO || player_id == NO_CONECTADO) && command != ACTION_EXIT) {
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
        std::cin >> game_code;
        std::shared_ptr<Action> action = std::make_shared<Join>(game_code);
        commands.push(action);
        action_read();
    } else if (command == ACTION_CREATE) {
        std::shared_ptr<Action> action = std::make_shared<Create>();
        commands.push(action);
        action_read();
    } else {
        std::cout << "Comando invalido" << std::endl;
    }
}

void Client::action_read() {
    std::shared_ptr<Event> event = events.pop();
    switch (event->get_type()) {
        case JOIN_GAME:
            player_id = event->get_player_id();
            break;
        case CREATE_GAME:
            game_code = event->get_game_code();
            player_id = event->get_player_id();
            break;
    }
    if (event->is_connected()) {
        std::cout << "Conectado al juego " << game_code << " con player_id " << player_id << std::endl;
    } else {
        std::cout << "No se pudo conectar al juego" << std::endl;
    }
}
