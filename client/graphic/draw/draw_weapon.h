#ifndef WEAPON_H
#define WEAPON_H

#include <SDL2pp/SDL2pp.hh>
#include <map>
#include <memory>
#include "../sound.h"
#include "common/events/items/weapon_macros.h"
#include "common/events/items/weapon_dto.h"

class DrawWeapon {
    private:
    std::map<int, std::shared_ptr<SDL2pp::Texture>> textures;

    std::map<int, std::shared_ptr<SDL2pp::Chunk>> sounds;

    SDL2pp::Renderer &renderer;

    WeaponId weaponId;

    Sound sound;

    bool shoot;

    public:
    DrawWeapon(SDL2pp::Renderer &renderer, WeaponId weaponId = NO_WEAPON, uint8_t id = 0);

    void render(int x, int y, int flipType);

    void render(const WeaponDTO& weapon);

    void update(const WeaponDTO &weapon);

    WeaponId getId();

};
#endif