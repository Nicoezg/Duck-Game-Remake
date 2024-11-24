//
// Created by fran on 22/10/24.
//

#include <iostream>
#include "server_protocol.h"

ServerProtocol::ServerProtocol(Socket *socket, Encoder encoder)
    : actions_protocol(socket, encoder), event_protocol(socket, encoder) {}

std::shared_ptr<Action> ServerProtocol::read_element() {
    std::shared_ptr<Action> action = actions_protocol.read_element();
    return action;
}

void ServerProtocol::send_element(std::shared_ptr<Event> &event) {
    try {
        event_protocol.send_element(*event);
    } catch (...) {
        std::cout << "Error reading action" << std::endl;
    }
}

bool ServerProtocol::is_open() {
  return actions_protocol.is_open() && event_protocol.is_open();
}

void ServerProtocol::close() {
  actions_protocol.close();
  event_protocol.close();
}