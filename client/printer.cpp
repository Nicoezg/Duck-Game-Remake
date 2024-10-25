//
// Created by fran on 24/10/24.
//

#include "printer.h"
#include "common/actions/move.h"

Printer::Printer(Queue<std::shared_ptr<Event>> *events) : events(events) {}

void Printer::run() {
    try {
        while (true) {
            std::shared_ptr<Event> event = events->pop();
            process_event(event);
        }
    } catch (const ClosedQueue &e) {
        return;
    } catch (...) {
        std::cerr << "Unexpected error in Printer" << std::endl;
    }
}

void Printer::process_event(std::shared_ptr<Event> &event) const {
    switch (event->get_type()) {
        case BROADCAST:
            for (const auto &player : event->get_players()) {
                std::cout << player.get_text() << std::endl;
            }
            break;
        default:
            std::cerr << "Evento no soportado" << std::endl;
            break;
    }
}
