#include "cowboy.h"

Cowboy::Cowboy(GameMap &map) : Weapon(map, 6, 20, WeaponId::COWBOY_PISTOL) {}

void Cowboy::shoot(Duck *owner) {
  if (hasAmmo()) {
    createBullet(owner, 0, false, reach, BulletId::SHOT);
    ammo--;
  } 
  
}