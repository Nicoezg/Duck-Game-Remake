#ifndef WEAPON_FACTORY_H
#define WEAPON_FACTORY_H

#include "common/events/items/item_spawn.h"
#include "server/logic/weapons/weapon.h"
#include "server/logic/weapons/ak47.h"
#include "server/logic/weapons/cowboy.h"
#include "server/logic/weapons/duelos.h"
#include "server/logic/weapons/grenade.h"
#include "server/logic/weapons/laser_rifle.h"
#include "server/logic/weapons/magnum.h"
#include "server/logic/weapons/pewpewlaser.h"
#include "server/logic/weapons/shotgun.h"
#include "server/logic/weapons/sniper.h"
#include "server/logic/weapons/banana.h"
#include "server/logic/weapons/no_weapon.h"

class WeaponFactory {
public:
    WeaponFactory() = default;
    static std::unique_ptr<Weapon> createWeapon(ItemSpawnId itemSpawnId, GameMap &map);
};

#endif // WEAPON_FACTORY_H
