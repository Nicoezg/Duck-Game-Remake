#ifndef TALLER_TP_CREATE_H
#define TALLER_TP_CREATE_H

#include "common/game_mode.h"
#include <string>
#include <cstdint>
#include "action.h"
#include "action_macros.h"

class Create : public Action {
private:
    GameMode game_mode;

public:
    Create(GameMode game_mode);

    GameMode get_game_mode() const override;
};

#endif // TALLER_TP_CREATE_H
