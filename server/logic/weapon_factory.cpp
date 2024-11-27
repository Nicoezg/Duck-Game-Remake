#include "weapon_factory.h"

std::unique_ptr<Weapon> WeaponFactory::createWeapon(ItemSpawnId itemSpawnId, GameMap &map)
{
    switch (itemSpawnId) {
        case ItemSpawnId::AK47_SPAWN:
            return std::make_unique<Ak47>(map);
        case ItemSpawnId::COWBOY_PISTOL_SPAWN:
            return std::make_unique<Cowboy>(map);
        case ItemSpawnId::DUEL_PISTOL_SPAWN:
            return std::make_unique<Duelos>(map);
        case ItemSpawnId::GRENADE_SPAWN:
            return std::make_unique<Grenade>(map);
        case ItemSpawnId::LASER_RIFLE_SPAWN:
            return std::make_unique<LaserRifle>(map);
        case ItemSpawnId::MAGNUM_SPAWN:
            return std::make_unique<Magnum>(map);
        case ItemSpawnId::PEW_PEW_LASER_SPAWN:
            return std::make_unique<PewPewLaser>(map);
        case ItemSpawnId::SHOTGUN_SPAWN:
            return std::make_unique<Shotgun>(map);
        case ItemSpawnId::SNIPER_SPAWN:
            return std::make_unique<Sniper>(map);
        case ItemSpawnId::BANANA_SPAWN:
            return std::make_unique<Banana>(map);
        default:
            return std::make_unique<NoWeapon>(map); 
    }
}
