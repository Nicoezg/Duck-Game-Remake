//
// Created by fran on 13/11/24.
//

#ifndef TALLER_TP_WEAPON_H
#define TALLER_TP_WEAPON_H



#define CONFIG Configurations::configurations()

class Duck;

class Weapon {
private:
    int reach;
    int ammo;
    bool reloading;
    int lastShot;

public:
    Weapon(int ammo, int reach);
    virtual ~Weapon() = default;


    //virtual bool shoot(Duck *shooter) = 0;
    //virtual bool canShoot() { return !isReloading() && hasAmmo(); }
    //virtual void reload() = 0;

    //bool hasAmmo() { return ammo > 0; }
    //int getAmmo() const;
    //int getReach() const;
    //bool isReloading() const;
};


#endif //TALLER_TP_WEAPON_H
