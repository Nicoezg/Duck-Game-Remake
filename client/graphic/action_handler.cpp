#include "action_handler.h"
#include <SDL2/SDL_keycode.h>
#include <SDL_events.h>
#include <iostream>

ActionHandler::ActionHandler(Client &client) : client(client) {}

void ActionHandler::processDuckEvents(WeaponId weaponId1, WeaponId weaponId2) {
  SDL_Event event;
  while (SDL_PollEvent(&event)) {

    if (event.type == SDL_QUIT) {
      throw std::exception(); // a cambiar
    }
    if ((weaponId1 == WeaponId::PEW_PEW_LASER ||
         weaponId1 == WeaponId::COWBOY_PISTOL ||
         weaponId1 == WeaponId::MAGNUM || weaponId1 == WeaponId::SNIPER ||
         weaponId1 == WeaponId::SHOTGUN) &&
        event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_COMMA) {
      if (event.key.repeat == 0) {
        std::shared_ptr<Action> action =
            std::make_shared<Shoot>(this->client.get_player_id_1(), true);
        this->client.send_action(action);
        return;
      }
      return;
    }
    if ((weaponId2 == WeaponId::PEW_PEW_LASER ||
         weaponId2 == WeaponId::COWBOY_PISTOL ||
         weaponId2 == WeaponId::MAGNUM || weaponId2 == WeaponId::SNIPER ||
         weaponId2 == WeaponId::SHOTGUN) &&
        event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_g) {
      if (event.key.repeat == 0) {
        std::shared_ptr<Action> action =
            std::make_shared<Shoot>(this->client.get_player_id_2(), true);
        this->client.send_action(action);
        return;
      }
      return;
    }
    if (event.type == SDL_KEYDOWN) {
      std::shared_ptr<Action> action = nullptr;
      switch (event.key.keysym.sym) {
      case SDLK_LEFT:
        action = std::make_shared<Move>(this->client.get_player_id_1(), false);
        break;

      case SDLK_RIGHT:
        action = std::make_shared<Move>(this->client.get_player_id_1(), true);
        break;

      case SDLK_DOWN:
        action =
            std::make_shared<PlayDead>(this->client.get_player_id_1(), true);
        break;

      case SDLK_UP:
        action =
            std::make_shared<JumpFlap>(this->client.get_player_id_1(), true);
        break;

      case SDLK_l:
        action =
            std::make_shared<AimUpwards>(this->client.get_player_id_1(), true);
        break;

      case SDLK_MINUS:
        action =
            std::make_shared<PickDrop>(this->client.get_player_id_1(), false);
        break;

      case SDLK_PERIOD:
        action =
            std::make_shared<PickDrop>(this->client.get_player_id_1(), true);
        break;

      case SDLK_COMMA:
        action = std::make_shared<Shoot>(this->client.get_player_id_1(), true);
        break;
      case SDLK_F1:
        action = std::make_shared<Cheat>(this->client.get_player_id_1(),
                                         CheatId::GET_GRENADE);
        break;
      case SDLK_F2:
        action = std::make_shared<Cheat>(this->client.get_player_id_1(),
                                         CheatId::GET_BANANA);
        break;
      case SDLK_F3:
        action = std::make_shared<Cheat>(this->client.get_player_id_1(),
                                         CheatId::GET_PEW_PEW_LASER);
        break;
      case SDLK_F4:
        action = std::make_shared<Cheat>(this->client.get_player_id_1(),
                                         CheatId::GET_LASER_RIFLE);
        break;
      case SDLK_F5:
        action = std::make_shared<Cheat>(this->client.get_player_id_1(),
                                         CheatId::GET_AK47);
        break;
      case SDLK_F6:
        action = std::make_shared<Cheat>(this->client.get_player_id_1(),
                                         CheatId::GET_DUEL_PISTOL);
        break;
      case SDLK_F7:
        action = std::make_shared<Cheat>(this->client.get_player_id_1(),
                                         CheatId::GET_COWBOY_PISTOL);
        break;
      case SDLK_F8:
        action = std::make_shared<Cheat>(this->client.get_player_id_1(),
                                         CheatId::GET_MAGNUM);
        break;
      case SDLK_F9:
        action = std::make_shared<Cheat>(this->client.get_player_id_1(),
                                         CheatId::GET_SHOTGUN);
        break;
      case SDLK_F10:
        action = std::make_shared<Cheat>(this->client.get_player_id_1(),
                                         CheatId::GET_SNIPER);
        break;
      case SDLK_F11:
        action = std::make_shared<Cheat>(this->client.get_player_id_1(),
                                         CheatId::GET_HELMET);
        break;
      case SDLK_F12:
        action = std::make_shared<Cheat>(this->client.get_player_id_1(),
                                         CheatId::GET_CHESTPLATE);
        break;
      case SDLK_1:
        action = std::make_shared<Cheat>(this->client.get_player_id_1(),
                                         CheatId::WIN_INSTANTLY);
        break;
      case SDLK_2:
        action = std::make_shared<Cheat>(this->client.get_player_id_1(),
                                         CheatId::KILL_ALL);
        break;
      case SDLK_3:
        action = std::make_shared<Cheat>(this->client.get_player_id_1(),
                                         CheatId::THROW_EVERYTHING);
        break;
      case SDLK_4:
        action = std::make_shared<Cheat>(this->client.get_player_id_1(),
                                         CheatId::NEXT_ROUND);
        break;
      case SDLK_5:
        action = std::make_shared<Cheat>(this->client.get_player_id_1(),
                                         CheatId::INFINITE_AMMO);
        break;
      }
      if (!action && (client.get_player_id_2() == SIN_ASIGNAR)) {
        continue;
      }

      switch (event.key.keysym.sym) {
      case SDLK_a:
        action = std::make_shared<Move>(this->client.get_player_id_2(), false);
        break;
      case SDLK_d:
        action = std::make_shared<Move>(this->client.get_player_id_2(), true);
        break;
      case SDLK_w:
        action =
            std::make_shared<JumpFlap>(this->client.get_player_id_2(), true);
        break;
      case SDLK_s:
        action =
            std::make_shared<PlayDead>(this->client.get_player_id_2(), true);
        break;
      case SDLK_y:
        action =
            std::make_shared<AimUpwards>(this->client.get_player_id_2(), true);
        break;
      case SDLK_g:
        action = std::make_shared<Shoot>(this->client.get_player_id_2(), true);
        break;
      case SDLK_h:
        action =
            std::make_shared<PickDrop>(this->client.get_player_id_2(), true);
        break;
      case SDLK_j:
        action =
            std::make_shared<PickDrop>(this->client.get_player_id_2(), false);
        break;
      }

      if (!action) {
        continue;
      }
      this->client.send_action(action);

    } else if (event.type == SDL_KEYUP) {
      std::shared_ptr<Action> action = nullptr;
      switch (event.key.keysym.sym) {
      case SDLK_LEFT:
      case SDLK_RIGHT:
        action = std::make_shared<Still>(this->client.get_player_id_1(), true);
        break;

      case SDLK_DOWN:
        action =
            std::make_shared<PlayDead>(this->client.get_player_id_1(), false);
        break;
      case SDLK_l:
        action =
            std::make_shared<AimUpwards>(this->client.get_player_id_1(), false);
        break;
      }

      if (!action && (client.get_player_id_2() == SIN_ASIGNAR)) {
        continue;
      }
      switch (event.key.keysym.sym) {
      case SDLK_d:
      case SDLK_a:
        action = std::make_shared<Still>(this->client.get_player_id_2(), true);
        break;

      case SDLK_s:
        action =
            std::make_shared<PlayDead>(this->client.get_player_id_2(), false);
        break;
      case SDLK_y:
        action =
            std::make_shared<AimUpwards>(this->client.get_player_id_2(), false);
        break;
      }

      if (!action) {
        continue;
      }
      this->client.send_action(action);
    }
  }
}

void ActionHandler::processEvents(WeaponId weaponId1, WeaponId weaponId2) {
  this->processDuckEvents(weaponId1, weaponId2);
}