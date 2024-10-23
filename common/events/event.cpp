
#include "event.h"

Event::Event(EventType type) : type(type) {}

EventType Event::get_type() {
    return type;
}
