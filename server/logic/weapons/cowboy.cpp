#include "cowboy.h"

#define NAME COWBOY_NAME
const int AMMO = CONFIG.getBulletConfig(NAME).getAmmo();
const int REACH = CONFIG.getBulletConfig(NAME).getReach();
const int COOLDOWN = CONFIG.getBulletConfig(NAME).getCooldown();

Cowboy::Cowboy(GameMap &map) : Weapon(map, AMMO, REACH, WeaponId::COWBOY_PISTOL) {}

void Cowboy::shoot(Duck *owner) {
  if (hasAmmo()) {
    createBullet(owner, 0, false, reach, BulletId::SHOT);
    ammo--;
  } 
  
}