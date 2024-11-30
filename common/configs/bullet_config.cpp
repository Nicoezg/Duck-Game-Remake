//
// Created by fran on 21/11/24.
//

#include "bullet_config.h"

BulletConfig::BulletConfig(int ammo, int reach, int cooldown, int height, int width) :
        ammo(ammo), reach(reach), cooldown(cooldown),
        height(height), width(width) {}

int BulletConfig::getAmmo() const {
    return ammo;
}

int BulletConfig::getReach() const {
    return reach;
}

int BulletConfig::getCooldown() const {
    return cooldown;
}

int BulletConfig::getHeight() const {
    return height;
}

int BulletConfig::getWidth() const {
    return width;
}