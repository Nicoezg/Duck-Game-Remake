#ifndef TALLER_TP_CREATE_H
#define TALLER_TP_CREATE_H

#include <string>
#include <cstdint>
#include "action.h"
#include "action_macros.h"

class Create : public Action {

public:
    Create();

    int get_game_code() const override;

    bool is_x_direction() const override;

    bool is_y_direction() const override;
};

#endif // TALLER_TP_CREATE_H
