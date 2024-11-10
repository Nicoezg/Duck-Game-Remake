#include "bullet.h"
#define DATA_PATH "../sprites/"

Bullet::Bullet(SDL2_pp::Renderer &renderer) : renderer(renderer) {
    this->textures[0] = SDL2pp::Texture(renderer, SDL2pp::Surface(DATA_PATH "weapons/grenade.png").SetColorKey(true, 0));
    this->textures[1] = SDL2pp::Texture(renderer, SDL2pp::Surface(DATA_PATH "weapons/banana.png").SetColorKey(true, 0));
    this->textures[2] = SDL2pp::Texture(renderer, SDL2pp::Surface(DATA_PATH "weapons/pew-pew-laser.png").SetColorKey(true, 0));
    this->textures[3] = SDL2pp::Texture(renderer, SDL2pp::Surface(DATA_PATH "weapons/laser-rifle.png").SetColorKey(true, 0));
    this->textures[4] = SDL2pp::Texture(renderer, SDL2pp::Surface(DATA_PATH "weapons/ak-47.png").SetColorKey(true, 0));
    this->textures[5] = SDL2pp::Texture(renderer, SDL2pp::Surface(DATA_PATH "weapons/duel-pistol.png").SetColorKey(true, 0));
    this->textures[6] = SDL2pp::Texture(renderer, SDL2pp::Surface(DATA_PATH "weapons/cowboy-pistol.png").SetColorKey(true, 0));
    this->textures[7] = SDL2pp::Texture(renderer, SDL2pp::Surface(DATA_PATH "weapons/magnum.png").SetColorKey(true, 0));
    this->textures[8] = SDL2pp::Texture(renderer, SDL2pp::Surface(DATA_PATH "weapons/shotgun.png").SetColorKey(true, 0));
    this->textures[9] = SDL2pp::Texture(renderer, SDL2pp::Surface(DATA_PATH "weapons/sniper.png").SetColorKey(true, 0));
}

// cambiar facing a un angulo de rotacion

void Bullet::render(int x, int y, int facing, int bullet_id){
    SDL2pp::Texture &texture = this->textures[bullet_id];
    SDL2pp::Rect dest(x, y, texture.GetWidth(), texture.GetHeight());
    renderer.Copy(texture, SDL2pp::NullOpt, dest);
}