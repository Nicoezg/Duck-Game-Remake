//
// Created by fran on 21/10/24.
//

#ifndef TALLER_TP_JOIN_H
#define TALLER_TP_JOIN_H


#include "common/game_mode.h"
#include "action_macros.h"
#include <string>
#include <cstdint>
#include "action.h"

class Join : public Action {
private:
    int game_code;
    GameMode game_mode;
public:
    explicit Join(int &game_code, GameMode game_mode);

    int get_game_code() const override;

    GameMode get_game_mode() const override;

};


#endif //TALLER_TP_JOIN_H
