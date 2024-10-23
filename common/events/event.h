//
// Created by fran on 21/10/24.
//

#ifndef TALLER_TP_EVENT_H
#define TALLER_TP_EVENT_H


#include "event_type.h"

class Event {
private:
    EventType type;

public:
    explicit Event(EventType type);

    EventType get_type();

    virtual int get_game_code() const = 0;

    virtual int get_player_id() const = 0;

    virtual bool is_connected() const = 0;
    virtual ~Event() = default;


};


#endif //TALLER_TP_EVENT_H
