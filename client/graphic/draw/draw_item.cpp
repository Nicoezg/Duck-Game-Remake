#include "draw_item.h"

#define DATA_PATH "../client/assets/sprites/"

DrawItemSpawn::DrawItemSpawn(SDL2pp::Renderer &renderer)
    : textures(), renderer(renderer) {

  this->textures[0] = std::make_shared<SDL2pp::Texture>(
      renderer, SDL2pp::Surface(DATA_PATH "items/grenade-spawn.png"));
  this->textures[1] = std::make_shared<SDL2pp::Texture>(
      renderer, SDL2pp::Surface(DATA_PATH "items/banana-spawn.png"));
  this->textures[2] = std::make_shared<SDL2pp::Texture>(
      renderer, SDL2pp::Surface(DATA_PATH "items/pew-pew-laser-spawn.png"));
  this->textures[3] = std::make_shared<SDL2pp::Texture>(
      renderer, SDL2pp::Surface(DATA_PATH "items/laser-rifle-spawn.png"));
  this->textures[4] = std::make_shared<SDL2pp::Texture>(
      renderer, SDL2pp::Surface(DATA_PATH "items/ak-47-spawn.png"));
  this->textures[5] = std::make_shared<SDL2pp::Texture>(
      renderer, SDL2pp::Surface(DATA_PATH "items/duel-pistol-spawn.png"));
  this->textures[6] = std::make_shared<SDL2pp::Texture>(
      renderer, SDL2pp::Surface(DATA_PATH "items/cowboy-pistol-spawn.png"));
  this->textures[7] = std::make_shared<SDL2pp::Texture>(
      renderer, SDL2pp::Surface(DATA_PATH "items/magnum-spawn.png"));
  this->textures[8] = std::make_shared<SDL2pp::Texture>(
      renderer, SDL2pp::Surface(DATA_PATH "items/shotgun-spawn.png"));
  this->textures[9] = std::make_shared<SDL2pp::Texture>(
      renderer, SDL2pp::Surface(DATA_PATH "items/sniper-spawn.png"));
  this->textures[10] = std::make_shared<SDL2pp::Texture>(
      renderer, SDL2pp::Surface(DATA_PATH "items/knight-helmet-spawn.png"));
  this->textures[11] = std::make_shared<SDL2pp::Texture>(
      renderer, SDL2pp::Surface(DATA_PATH "items/chestplate-spawn.png"));
}

void DrawItemSpawn::render(const ItemSpawnDTO &itemSpawn) {
  if (itemSpawn.get_id() == ItemSpawnId::NOTHING_SPAWN) {
    return;
  }
  std::shared_ptr<SDL2pp::Texture> texture =
      this->textures[itemSpawn.get_id() - 1];
  SDL2pp::Rect dest(itemSpawn.get_position_x(), itemSpawn.get_position_y(),
                    texture->GetWidth(), texture->GetHeight());
  renderer.Copy(*texture, SDL2pp::NullOpt, dest);
}