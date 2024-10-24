//
// Created by fran on 21/10/24.
//

#ifndef TALLER_TP_JOIN_H
#define TALLER_TP_JOIN_H


#include <cstdint>
#include "action.h"

class Join : public Action {
private:
    int game_code;
public:
    explicit Join(int &game_code, GameMode game_mode);

    int get_game_code() const override;

    bool is_x_direction() const override;

    bool is_y_direction() const override;

};


#endif //TALLER_TP_JOIN_H
