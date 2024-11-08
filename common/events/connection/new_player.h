//
// Created by fran on 04/11/24.
//

#ifndef TALLER_TP_NEW_PLAYER_H
#define TALLER_TP_NEW_PLAYER_H


#include "common/events/base/event.h"

class NewPlayer : public Event {
private:
    int max_players;
    int actual_players;

public:
    NewPlayer(int max_players, int actual_players);

    int get_max_players() const override;

    int get_actual_players() const override;

};


#endif //TALLER_TP_NEW_PLAYER_H
