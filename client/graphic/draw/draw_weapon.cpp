#include "draw_weapon.h"
#include "common/events/items/weapon_dto.h"
#include <iostream>
#define DATA_PATH "../client/sprites/"

DrawWeapon::DrawWeapon(SDL2pp::Renderer &renderer, WeaponId weaponId, uint8_t id) : textures(), sounds(), renderer(renderer), weaponId(weaponId), sound(), shoot(false) {

    std::cout << std::string("../client/sprites/weapons/pew-pew-laser-w-wing-") + std::to_string(id) + ".png" << std::endl;
    this->textures[0] = std::make_shared<SDL2pp::Texture>(renderer, SDL2pp::Surface("../client/sprites/weapons/grenade.png").SetColorKey(true, 0));
    this->textures[1] = std::make_shared<SDL2pp::Texture>(renderer, SDL2pp::Surface(DATA_PATH "weapons/banana.png").SetColorKey(true, 0));
    this->textures[2] = std::make_shared<SDL2pp::Texture>(renderer, SDL2pp::Surface(std::string("../client/sprites/weapons/pew-pew-laser-w-wing-") + std::to_string(id) + ".png").SetColorKey(true, 0));
    this->textures[3] = std::make_shared<SDL2pp::Texture>(renderer, SDL2pp::Surface(std::string("../client/sprites/weapons/laser-rifle-w-wing-") + std::to_string(id) + ".png").SetColorKey(true, 0));
    this->textures[4] = std::make_shared<SDL2pp::Texture>(renderer, SDL2pp::Surface(std::string("../client/sprites/weapons/ak47-w-wing-") + std::to_string(id) + ".png").SetColorKey(true, 0));
    this->textures[5] = std::make_shared<SDL2pp::Texture>(renderer, SDL2pp::Surface(std::string("../client/sprites/weapons/duel-pistol-w-wing-") + std::to_string(id) + ".png").SetColorKey(true, 0));
    this->textures[6] = std::make_shared<SDL2pp::Texture>(renderer, SDL2pp::Surface(std::string("../client/sprites/weapons/cowboy-pistol-w-wing-") + std::to_string(id) + ".png").SetColorKey(true, 0));
    this->textures[7] = std::make_shared<SDL2pp::Texture>(renderer, SDL2pp::Surface(std::string("../client/sprites/weapons/magnum-w-wing-") + std::to_string(id) + ".png").SetColorKey(true, 0));
    this->textures[8] = std::make_shared<SDL2pp::Texture>(renderer, SDL2pp::Surface(std::string("../client/sprites/weapons/shotgun-w-wing-") + std::to_string(id) + ".png").SetColorKey(true, 0));
    this->textures[9] = std::make_shared<SDL2pp::Texture>(renderer, SDL2pp::Surface(std::string("../client/sprites/weapons/sniper-w-wing-") + std::to_string(id) + ".png").SetColorKey(true, 0));


    this->sounds[2] = std::make_shared<SDL2pp::Chunk>("../client/graphic/audio/pew-pew-laser.wav");
    this->sounds[3] = std::make_shared<SDL2pp::Chunk>("../client/graphic/audio/laserRifle.wav");
    this->sounds[4] = std::make_shared<SDL2pp::Chunk>("../client/graphic/audio/ak47.wav");
    this->sounds[5] = std::make_shared<SDL2pp::Chunk>("../client/graphic/audio/duelingpistol.wav");
    this->sounds[6] = std::make_shared<SDL2pp::Chunk>("../client/graphic/audio/pistolFire.wav");
    this->sounds[7] = std::make_shared<SDL2pp::Chunk>("../client/graphic/audio/magShot.wav");
    this->sounds[8] = std::make_shared<SDL2pp::Chunk>("../client/graphic/audio/shotgunFire.wav");
    this->sounds[9] = std::make_shared<SDL2pp::Chunk>("../client/graphic/audio/sniper.wav");
}

void DrawWeapon::render(int x, int y, int flipType){
    std::shared_ptr<SDL2pp::Texture> texture = this->textures[9];
    SDL2pp::Rect dest(x - 4, y + 6 , 38, 32);
    renderer.Copy(*texture, SDL2pp::NullOpt, dest, 0.0, SDL2pp::NullOpt, flipType);
    if (shoot){
        sound.play();
        shoot = false;
    }
}

void DrawWeapon::render(const WeaponDTO &weapon){
    std::shared_ptr<SDL2pp::Texture> texture = this->textures[weapon.get_id()];
    SDL2pp::Rect dest(weapon.get_position_x(), weapon.get_position_y(), texture->GetWidth(), texture->GetHeight());
    renderer.Copy(*texture, SDL2pp::NullOpt, dest);
    // Falta ajustar las posiciones de las armas.
}

void DrawWeapon::update(const WeaponDTO &weapon){
    weaponId = weapon.get_id();
    // shoot = weapon.is_shooting(); // Implementar en DTO weapon
    if (weaponId != NO_WEAPON && weaponId != GRENADE && weaponId != BANANA){
        sound.change(sounds[weaponId]);
    }
}

WeaponId DrawWeapon::getId(){
    return weaponId;
}