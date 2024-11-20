//
// Created by fran on 22/10/24.
//

#ifndef TALLER_TP_SERVER_PROTOCOL_H
#define TALLER_TP_SERVER_PROTOCOL_H

#include "common/protocol/actions/actions_protocol.h"
#include "common/protocol/events/events_protocol.h"

class ServerProtocol {
private:
  ActionsProtocol actions_protocol;
  EventsProtocol event_protocol;

public:
  ServerProtocol(Socket *socket, Encoder encoder);

  std::shared_ptr<Action> read_element();

  void send_element(std::shared_ptr<Event> &event);

  bool is_open();

  void close();
};

#endif // TALLER_TP_SERVER_PROTOCOL_H
