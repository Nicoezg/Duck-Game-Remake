#ifndef DUCK_H
#define DUCK_H

#include "weapon.h"  

class Duck {
    private:
        int id;
        int posX, posY;
        int velX, velY;
        bool jumping;
        bool flapping;
        bool shooting;
        GameMap& map;
        Weapon* weapon; 

        bool isRight;

    public:
        Duck(int& id, int& posX, int& posY, GameMap& map);

        void moveRight();
        void moveLeft();
        void move(bool isRight);
        void jump();
        void flap();
        void update();
        void shoot();

        int getPositionX() const;
        int getPositionY() const;
};

#endif // DUCK_H
