#ifndef WEAPON_SPAWN_H
#define WEAPON_SPAWN_H

#include <SDL2pp/SDL2pp.hh>
#include <map>
#include <memory>
#include "../sound.h"
#include "common/events/items/weapon_macros.h"
#include "common/events/items/weapon_dto.h"

class DrawWeaponSpawn {
    private:
    std::map<int, std::shared_ptr<SDL2pp::Texture>> textures;

    SDL2pp::Renderer &renderer;

    WeaponId weaponId;

    public:
    DrawWeaponSpawn(SDL2pp::Renderer &renderer);

    void render(const WeaponDTO& weapon);

    void update(const WeaponDTO &weapon);

    WeaponId getId();

};
#endif