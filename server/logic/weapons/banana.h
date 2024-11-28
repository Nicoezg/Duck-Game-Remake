#ifndef BANANA_H
#define BANANA_H

#include "weapon.h"

#include "server/logic/duck.h"

class Banana : public Weapon {
public:
    Banana(GameMap &map);

    void shoot(Duck *owner) override;

    void replenishAmmo() override;
};

#endif // BANANA_H