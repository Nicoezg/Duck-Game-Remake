//
// Created by fran on 21/10/24.
//

#ifndef TALLER_TP_GAME_JOIN_H
#define TALLER_TP_GAME_JOIN_H


#include "event.h"

class GameJoin : public Event {
private:
    int player_id_1;
    int player_id_2;

    bool connected;

public:
    GameJoin(int player_id_1, int player_id_2, bool connected);

    int get_player_id_1() const override;

    int get_player_id_2() const override;

    int get_game_code() const override;

    bool is_connected() const override;
};


#endif //TALLER_TP_GAME_JOIN_H
