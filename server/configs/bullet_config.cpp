//
// Created by fran on 21/11/24.
//

#include "bullet_config.h"

BulletConfig::BulletConfig(int ammo, int reach, int cooldown): ammo(ammo), reach(reach), cooldown(cooldown) {}

int BulletConfig::getAmmo() const {
    return ammo;
}

int BulletConfig::getReach() const {
    return reach;
}

int BulletConfig::getCooldown() const {
    return cooldown;
}