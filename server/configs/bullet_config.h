//
// Created by fran on 21/11/24.
//

#ifndef TALLER_TP_BULLET_CONFIG_H
#define TALLER_TP_BULLET_CONFIG_H


class BulletConfig {
private:
    int ammo;
    int reach;
    int cooldown;

public:
    BulletConfig(int ammo, int reach, int cooldown);

    int getAmmo() const;

    int getReach() const;

    int getCooldown() const;
};


#endif //TALLER_TP_BULLET_CONFIG_H
