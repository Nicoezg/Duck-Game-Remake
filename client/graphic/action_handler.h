#ifndef ACTION_HANDLER_H
#define ACTION_HANDLER_H

#include "../communication/client.h"
#include <SDL2/SDL_events.h>
#include <SDL2pp/SDL2pp.hh>
#include <SDL2/SDL_keycode.h>
#include <exception>
#include <iostream>
#include <memory>
#include <ostream>
#include "../../common/actions/base/action.h"
#include "../../common/actions/player/aim_upwards.h"
#include "../../common/actions/player/pick_drop.h"
#include "../../common/actions/player/move.h"
#include "../../common/actions/player/play_dead.h"
#include "../../common/actions/player/shoot.h"
#include "../../common/actions/player/jump_flap.h"
#include "../../common/actions/player/still.h"


class ActionHandler{
    private:
    
    void processDuckEvents();
    Client& client;

    public:

    ActionHandler(Client &client);
    void processEvents();
};
#endif