#ifndef WEAPON_H
#define WEAPON_H

class Duck;

class Weapon {
    protected:
        int reach;
        int ammunition;
        bool reloading;

    public:
        Weapon(int ammo, int reach) : ammunition(ammo), reach(reach) {}
        virtual ~Weapon() = default;

        virtual bool shoot(Duck* shooter) = 0;
        virtual void reload() = 0;

        int getAmmo() const;
        int getReach() const;
        bool isReloading() const;
};

#endif // WEAPON_H
