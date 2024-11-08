#include "weapon.h"
#define DATA_PATH "../sprites/"

Weapon::Weapon(SDL2pp::Renderer &renderer) : renderer(renderer) {
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
}

void Weapon::render(int x, int y, int weapon_id){
    std::shared_ptr<SDL2pp::Texture> texture = this->textures[weapon_id];
    SDL2pp::Rect dest(x, y, texture->GetWidth(), texture->GetHeight());
    renderer.Copy(*texture, SDL2pp::NullOpt, dest);
}