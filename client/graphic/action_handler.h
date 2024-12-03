#ifndef ACTION_HANDLER_H
#define ACTION_HANDLER_H

#include "../../common/actions/base/action.h"
#include "../../common/actions/player/aim_upwards.h"
#include "../../common/actions/player/cheat.h"
#include "../../common/actions/player/jump_flap.h"
#include "../../common/actions/player/move.h"
#include "../../common/actions/player/pick_drop.h"
#include "../../common/actions/player/play_dead.h"
#include "../../common/actions/player/shoot.h"
#include "../../common/actions/player/still.h"
#include "../../common/events/items/weapon_macros.h"
#include "../communication/client.h"
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2pp/SDL2pp.hh>
#include <exception>
#include <iostream>
#include <memory>
#include <ostream>

class ActionHandler {
private:
  void processDuckEvents(WeaponId weaponId1, WeaponId weaponId2);
  Client &client;

public:
  explicit ActionHandler(Client &client);
  void processEvents(WeaponId weaponId1, WeaponId weaponId2);
};
#endif