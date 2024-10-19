#include "client/client.h"

#include "common/protocol/action.h"
#include "common/protocol/action_macros.h"
#include "common/protocol/protocol_error.h"
#include <iostream>

Client::Client(const char *hostname, const char *service_name)
        : queue(), sender(Socket(hostname, service_name), queue, Encoder()), game_code(0),
          player_id(0) {}

std::string Client::read_command() {
    std::string action_key;
    std::cin >> action_key;
    return action_key;
}

void Client::run() {
    bool connected = false;
    try {
        connected = connect_to_game();
    } catch (const ProtocolError &e) {
        connected = false;
    }
    if (!connected) {
        sender.close();
        return;
    }

    sender.start();
    std::string action_key = read_command();
    try {
        while (!sender.is_closed() && action_key != ACTION_EXIT &&
               !sender.is_closed()) {
            run_command(action_key);
            action_key = read_command();
        }
    } catch (const std::exception &e) {
        std::cerr << "Unexpected error: " << e.what() << std::endl;
    }
    if (!sender.is_closed()) {
        sender.close();
    }
    sender.join();
}

std::string Client::read_connect_command() {
    std::string command;
    std::cin >> command;
    while (command != ACTION_JOIN && command != ACTION_CREATE &&
           command != ACTION_EXIT) {
        std::cout << "Ingrese " << ACTION_JOIN << " para unirse a un juego o "
                  << ACTION_CREATE << " para crear uno" << std::endl;
        std::cin >> command;
    }
    run_command(command);
    return command;
}

bool Client::connect_to_game() {
    std::string command = read_connect_command();
    if (command == ACTION_EXIT) {
        return false;
    }
    while (game_code == 0 && command != ACTION_EXIT) {
        command = read_connect_command();
        if (command == ACTION_EXIT) {
            return false;
        }
    }
    std::cout << "Conectado al juego " << game_code << " con id " << player_id << std::endl;
    return true;
}

void Client::run_command(const std::string &command) {
    if (command == ACTION_READ) {
        action_read();
    } else if (command == ACTION_ATTACK) {
        action_attack();
    } else if (command == ACTION_EXIT) {
        sender.close();
    } else if (command == ACTION_JOIN) {
        std::cin >> game_code;
        sender.connect_to_game(game_code, player_id);
    } else if (command == ACTION_CREATE) {
        sender.connect_to_game(game_code, player_id);
    } else {
        std::cout << "Comando invalido" << std::endl;
    }
}

void Client::action_attack() { sender.push_action(Action(ACTION_ATTACK)); }

void Client::action_read() {
    Action action = queue.pop();
    std::cout << action.get_text() << std::endl;
}