//
// Created by fran on 22/10/24.
//

#include "client_protocol.h"
#include <iostream>

ClientProtocol::ClientProtocol(Socket *socket, Encoder encoder)
    : actions_protocol(socket, encoder), events_protocol(socket, encoder) {}

std::shared_ptr<Event> ClientProtocol::read_element() {
  return events_protocol.read_element();
}

void ClientProtocol::send_element(std::shared_ptr<Action> &action) {
  actions_protocol.send_element(*action);
}

bool ClientProtocol::is_open() {
  return actions_protocol.is_open() && events_protocol.is_open();
}

void ClientProtocol::close() {
  actions_protocol.close();
  events_protocol.close();
}
