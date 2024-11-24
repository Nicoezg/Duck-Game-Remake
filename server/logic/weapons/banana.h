#include "weapon.h"

#include "server/logic/duck.h"

class Banana : public Weapon {
public:
    Banana(GameMap &map);

    void shoot(Duck *owner) override;
};