#include "draw_weapon.h"
#include <iostream>
#define DATA_PATH "../client/sprites/"

DrawWeapon::DrawWeapon(SDL2pp::Renderer &renderer, WeaponId weaponId) : textures(), sounds(), renderer(renderer), weaponId(weaponId), sound(), shoot(false) {
    this->textures[0] = std::make_shared<SDL2pp::Texture>(renderer, SDL2pp::Surface(DATA_PATH "weapons/grenade.png").SetColorKey(true, 0));
    this->textures[1] = std::make_shared<SDL2pp::Texture>(renderer, SDL2pp::Surface(DATA_PATH "weapons/banana.png").SetColorKey(true, 0));
    this->textures[2] = std::make_shared<SDL2pp::Texture>(renderer, SDL2pp::Surface(DATA_PATH "weapons/pew-pew-laser.png").SetColorKey(true, 0));
    this->textures[3] = std::make_shared<SDL2pp::Texture>(renderer, SDL2pp::Surface(DATA_PATH "weapons/laser-rifle.png").SetColorKey(true, 0));
    this->textures[4] = std::make_shared<SDL2pp::Texture>(renderer, SDL2pp::Surface(DATA_PATH "weapons/ak-47.png").SetColorKey(true, 0));
    this->textures[5] = std::make_shared<SDL2pp::Texture>(renderer, SDL2pp::Surface(DATA_PATH "weapons/duel-pistol.png").SetColorKey(true, 0));
    this->textures[6] = std::make_shared<SDL2pp::Texture>(renderer, SDL2pp::Surface(DATA_PATH "weapons/cowboy-pistol.png").SetColorKey(true, 0));
    this->textures[7] = std::make_shared<SDL2pp::Texture>(renderer, SDL2pp::Surface(DATA_PATH "weapons/magnum.png").SetColorKey(true, 0));
    this->textures[8] = std::make_shared<SDL2pp::Texture>(renderer, SDL2pp::Surface(DATA_PATH "weapons/shotgun.png").SetColorKey(true, 0));
    this->textures[9] = std::make_shared<SDL2pp::Texture>(renderer, SDL2pp::Surface(DATA_PATH "weapons/sniper.png").SetColorKey(true, 0));


    this->sounds[2] = std::make_shared<SDL2pp::Chunk>("../client/graphic/audio/pew-pew-laser.wav");
    this->sounds[3] = std::make_shared<SDL2pp::Chunk>("../client/graphic/audio/laserRifle.wav");
    this->sounds[4] = std::make_shared<SDL2pp::Chunk>("../client/graphic/audio/ak47.wav");
    this->sounds[5] = std::make_shared<SDL2pp::Chunk>("../client/graphic/audio/duelingpistol.wav");
    this->sounds[6] = std::make_shared<SDL2pp::Chunk>("../client/graphic/audio/pistolFire.wav");
    this->sounds[7] = std::make_shared<SDL2pp::Chunk>("../client/graphic/audio/magShot.wav");
    this->sounds[8] = std::make_shared<SDL2pp::Chunk>("../client/graphic/audio/shotgunFire.wav");
    this->sounds[9] = std::make_shared<SDL2pp::Chunk>("../client/graphic/audio/sniper.wav");
}

void DrawWeapon::render(int x, int y){
    std::shared_ptr<SDL2pp::Texture> texture = this->textures[weaponId];
    SDL2pp::Rect dest(x, y, texture->GetWidth(), texture->GetHeight());
    renderer.Copy(*texture, SDL2pp::NullOpt, dest);
    if (shoot){
        sound.play();
        shoot = false;
    }
}

void DrawWeapon::render(const Weapon &weapon){
    std::shared_ptr<SDL2pp::Texture> texture = this->textures[weapon.get_id()];
    SDL2pp::Rect dest(weapon.get_position_x(), weapon.get_position_y(), texture->GetWidth(), texture->GetHeight());
    renderer.Copy(*texture, SDL2pp::NullOpt, dest);
}

void DrawWeapon::update(const Weapon &weapon){
    weaponId = weapon.get_id();
    // shoot = weapon.is_shooting(); // Implementar en DTO weapon
    if (weaponId != NO_WEAPON && weaponId != GRENADE && weaponId != BANANA){
        sound.change(sounds[weaponId]);
    }
}

WeaponId DrawWeapon::getId(){
    return weaponId;
}