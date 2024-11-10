#ifndef WEAPON_H
#define WEAPON_H

#include <SDL2pp/SDL2pp.hh>
#include <map>
#include <memory>
#include "../../../common/events/items/weapon.h"
#include "../sound.h"

class DrawWeapon {
    private:
    std::map<int, std::shared_ptr<SDL2pp::Texture>> textures;

    std::map<int, std::shared_ptr<SDL2pp::Chunk>> sounds;

    SDL2pp::Renderer &renderer;

    WeaponId weaponId;

    Sound sound;

    bool shoot;

    public:
    DrawWeapon(SDL2pp::Renderer &renderer, WeaponId weaponId = NO_WEAPON);

    void render(int x, int y);

    void render(const Weapon& weapon);

    void update(const Weapon &weapon);

    WeaponId getId();

};
#endif