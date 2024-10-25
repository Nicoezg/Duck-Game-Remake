#ifndef TALLER_TP_EVENTS_PROTOCOL_H
#define TALLER_TP_EVENTS_PROTOCOL_H


#include "common/protocol/common/protocol.h"
#include "common/events/event.h"

class EventsProtocol : public Protocol {
private:
    Encoder encoder;

    void send_create(const std::shared_ptr<Event>& event);

    void send_join(const std::shared_ptr<Event>& event);

    std::shared_ptr<Event> read_create();

    std::shared_ptr<Event> read_join();

public:
    EventsProtocol(Socket* socket, Encoder encoder);

    void send_element(std::shared_ptr<Event>& event);

    std::shared_ptr<Event> read_element();

    EventType read_event_type();

    std::shared_ptr<Event> read_broadcast();

    void send_broadcast(const std::shared_ptr<Event> &event);
};


#endif //TALLER_TP_EVENTS_PROTOCOL_H
