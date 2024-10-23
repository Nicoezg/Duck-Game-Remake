#ifndef TALLER_TP_GAME_CREATION_H
#define TALLER_TP_GAME_CREATION_H


#include "event.h"

class GameCreation : public Event {
private:
    int game_code;
    int player_id;
public:
    GameCreation(int game_code, int player_id);

    int get_game_code() const override;

    int get_player_id() const override;

    bool is_connected() const override;

};


#endif //TALLER_TP_GAME_CREATION_H
