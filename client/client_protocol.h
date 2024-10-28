//
// Created by fran on 22/10/24.
//

#ifndef TALLER_TP_CLIENT_PROTOCOL_H
#define TALLER_TP_CLIENT_PROTOCOL_H

#include "common/protocol/actions/actions_protocol.h"
#include "common/protocol/events/events_protocol.h"

class ClientProtocol {
private:
  ActionsProtocol actions_protocol;
  EventsProtocol events_protocol;

public:
  ClientProtocol(Socket *socket, Encoder encoder);

  std::shared_ptr<Event> read_element();
  void send_element(std::shared_ptr<Action> &action);

  bool is_open();

  void close();
};

#endif // TALLER_TP_CLIENT_PROTOCOL_H
