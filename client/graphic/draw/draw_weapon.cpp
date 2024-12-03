#include "draw_weapon.h"
#include "common/events/items/weapon_dto.h"
#include <iostream>
#define DATA_PATH "../client/sprites/"

DrawWeapon::DrawWeapon(SDL2pp::Renderer &renderer, WeaponId weaponId,
                       uint8_t id)
    : textures(), sounds(), renderer(renderer), weaponId(weaponId), sound(),
      shoot(false), aimingUpwards(false), hasAmmo(false), playNoAmmo(false) {

  this->textures[0] = std::make_shared<SDL2pp::Texture>(
      renderer,
      SDL2pp::Surface(std::string("../client/sprites/weapons/grenade-w-wing-") +
                      std::to_string(id) + ".png"));
  this->textures[1] = std::make_shared<SDL2pp::Texture>(
      renderer,
      SDL2pp::Surface(std::string("../client/sprites/weapons/banana-w-wing-") +
                      std::to_string(id) + ".png"));
  this->textures[2] = std::make_shared<SDL2pp::Texture>(
      renderer,
      SDL2pp::Surface(
          std::string("../client/sprites/weapons/pew-pew-laser-w-wing-") +
          std::to_string(id) + ".png"));
  this->textures[3] = std::make_shared<SDL2pp::Texture>(
      renderer,
      SDL2pp::Surface(
          std::string("../client/sprites/weapons/laser-rifle-w-wing-") +
          std::to_string(id) + ".png"));
  this->textures[4] = std::make_shared<SDL2pp::Texture>(
      renderer,
      SDL2pp::Surface(std::string("../client/sprites/weapons/ak47-w-wing-") +
                      std::to_string(id) + ".png"));
  this->textures[5] = std::make_shared<SDL2pp::Texture>(
      renderer,
      SDL2pp::Surface(
          std::string("../client/sprites/weapons/duel-pistol-w-wing-") +
          std::to_string(id) + ".png"));
  this->textures[6] = std::make_shared<SDL2pp::Texture>(
      renderer,
      SDL2pp::Surface(
          std::string("../client/sprites/weapons/cowboy-pistol-w-wing-") +
          std::to_string(id) + ".png"));
  this->textures[7] = std::make_shared<SDL2pp::Texture>(
      renderer,
      SDL2pp::Surface(std::string("../client/sprites/weapons/magnum-w-wing-") +
                      std::to_string(id) + ".png"));
  this->textures[8] = std::make_shared<SDL2pp::Texture>(
      renderer,
      SDL2pp::Surface(std::string("../client/sprites/weapons/shotgun-w-wing-") +
                      std::to_string(id) + ".png"));
  this->textures[9] = std::make_shared<SDL2pp::Texture>(
      renderer,
      SDL2pp::Surface(std::string("../client/sprites/weapons/sniper-w-wing-") +
                      std::to_string(id) + ".png"));
  this->textures[10] = std::make_shared<SDL2pp::Texture>(
      renderer,
      SDL2pp::Surface(
          std::string("../client/sprites/weapons/grenade-no-safe-w-wing-") +
          std::to_string(id) + ".png"));

  this->sounds[2] = std::make_shared<SDL2pp::Chunk>(
      "../client/graphic/audio/pew-pew-laser.wav");
  this->sounds[3] =
      std::make_shared<SDL2pp::Chunk>("../client/graphic/audio/laserRifle.wav");
  this->sounds[4] =
      std::make_shared<SDL2pp::Chunk>("../client/graphic/audio/ak47.wav");
  this->sounds[5] = std::make_shared<SDL2pp::Chunk>(
      "../client/graphic/audio/duelingpistol.wav");
  this->sounds[6] =
      std::make_shared<SDL2pp::Chunk>("../client/graphic/audio/pistolFire.wav");
  this->sounds[7] =
      std::make_shared<SDL2pp::Chunk>("../client/graphic/audio/magShot.wav");
  this->sounds[8] = std::make_shared<SDL2pp::Chunk>(
      "../client/graphic/audio/shotgunFire.wav");
  this->sounds[9] =
      std::make_shared<SDL2pp::Chunk>("../client/graphic/audio/sniper.wav");
  this->sounds[10] =
      std::make_shared<SDL2pp::Chunk>("../client/graphic/audio/no-ammo.wav");
}

void DrawWeapon::render(int x, int y, int flipType) {
  float angle = 0.0;
  if (aimingUpwards && !flipType) {
    angle = 270.0;
    y -= 3;
    x -= 10;
  } else if (aimingUpwards) {
    angle = 90.0;
    y -= 3;
    x += 4;
  } else if (flipType) {
    x -= 4;
  } else {
    x -= 1;
  }
  std::shared_ptr<SDL2pp::Texture> texture = this->textures[weaponId - 1];

  SDL2pp::Rect dest(x, y + 6, 38, 32);

  renderer.Copy(*texture, SDL2pp::NullOpt, dest, angle, SDL2pp::NullOpt,
                flipType);
  if (!hasAmmo) {
    sound.play();
    return;
  }
  if (shoot) {
    sound.play();
    shoot = false;
  }
}

void DrawWeapon::update(const WeaponDTO &weapon, bool aimingUpwards) {
  this->weaponId = weapon.get_id();
  this->aimingUpwards = aimingUpwards;
  bool dtoAmmo = weapon.has_ammo();
  shoot = weapon.is_shooting();
  if (playNoAmmo) {
    sound.change(sounds[10], 0);
    playNoAmmo = false;
  }
  if (weaponId != NO_WEAPON && weaponId != GRENADE && weaponId != BANANA &&
      weaponId != ARMED_GRENADE && shoot && !playNoAmmo) {
    sound.change(sounds[weaponId - 1], 0);
  }
  if (!dtoAmmo && dtoAmmo != hasAmmo && shoot && weaponId != NO_WEAPON &&
      weaponId != GRENADE && weaponId != BANANA && weaponId != ARMED_GRENADE) {
    playNoAmmo = true;
  }
  hasAmmo = dtoAmmo;
}

WeaponId DrawWeapon::getId() { return weaponId; }