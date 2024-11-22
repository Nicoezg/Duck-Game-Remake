//
// Created by fran on 20/11/24.
//

#ifndef TALLER_TP_NO_WEAPON_H
#define TALLER_TP_NO_WEAPON_H


#include "weapon.h"

class NoWeapon : public Weapon {

public:
    NoWeapon(GameMap &map);

    void shoot(Duck *) override;

    bool isReadyToShoot() const override;
};


#endif //TALLER_TP_NO_WEAPON_H
