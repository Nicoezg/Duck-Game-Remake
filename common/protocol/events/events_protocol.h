#ifndef TALLER_TP_EVENTS_PROTOCOL_H
#define TALLER_TP_EVENTS_PROTOCOL_H

#include "common/events/base/event.h"
#include "common/protocol/common/protocol.h"

class EventsProtocol : public Protocol {
private:
  Encoder encoder;

  void send_create(const std::shared_ptr<Event> &event);

  void send_join(const std::shared_ptr<Event> &event);

  std::shared_ptr<Event> read_create();

  std::shared_ptr<Event> read_join();

public:
  EventsProtocol(Socket *socket, Encoder encoder);

  void send_element(std::shared_ptr<Event> &event);

  std::shared_ptr<Event> read_element();

  EventType read_event_type();

  std::shared_ptr<Event> read_broadcast();

  void send_broadcast(const std::shared_ptr<Event> &event);

    void send_refresh(const std::shared_ptr<Event> &event);

    std::shared_ptr<Event> read_refresh_game();

    std::shared_ptr<Event> read_new_player();

    void send_new_player(const std::shared_ptr<Event> &event);

    void send_start_game(const std::shared_ptr<Event> &event);

    WeaponDTO read_weapon(std::vector<int8_t> &data);

    Helmet read_helmet(std::vector<int8_t> &data);

    Chestplate read_chestplate(std::vector<int8_t> &data);

    void add_chestplate(std::vector<int8_t> &data, Chestplate chestplate, size_t& offset);

    void add_health(std::vector<int8_t> &data, Helmet helmet, size_t& offset);

    void add_weapon(std::vector<int8_t> &data, WeaponDTO weapon, size_t& offset);

    void add_players(const std::shared_ptr<Event> &event, std::vector<int8_t> &data, size_t& offset);
};

#endif // TALLER_TP_EVENTS_PROTOCOL_H
