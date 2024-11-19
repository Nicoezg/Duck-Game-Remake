#include "draw_weapon_spawn.h"
#include "common/events/items/weapon_dto.h"

#define DATA_PATH "../client/sprites/"

DrawWeaponSpawn::DrawWeaponSpawn(SDL2pp::Renderer &renderer) : textures(), renderer(renderer), weaponId(NO_WEAPON) {

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

    // Cambiar todos estos para que tengan el mismo tamaño.
}

void DrawWeaponSpawn::render(const WeaponDTO &weapon){
    std::shared_ptr<SDL2pp::Texture> texture = this->textures[weapon.get_id()];
    SDL2pp::Rect dest(weapon.get_position_x(), weapon.get_position_y(), texture->GetWidth(), texture->GetHeight());
    renderer.Copy(*texture, SDL2pp::NullOpt, dest);
    // Falta ajustar las posiciones de las armas.
}

void DrawWeaponSpawn::update(const WeaponDTO &weapon){
    weaponId = weapon.get_id();
}

WeaponId DrawWeaponSpawn::getId(){
    return weaponId;
}