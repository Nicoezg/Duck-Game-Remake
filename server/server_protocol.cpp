//
// Created by fran on 22/10/24.
//

#include "server_protocol.h"

ServerProtocol::ServerProtocol(Socket *socket, Encoder encoder) : actions_protocol(socket, encoder),
                                                                  event_protocol(socket, encoder) {}

std::shared_ptr<Action> ServerProtocol::read_element() {
    return actions_protocol.read_element();
}

void ServerProtocol::send_element(std::shared_ptr<Event> &event) {
    event_protocol.send_element(event);
}

bool ServerProtocol::is_open() {
    return actions_protocol.is_open() && event_protocol.is_open();
}

void ServerProtocol::close() {
    actions_protocol.close();
    event_protocol.close();
}