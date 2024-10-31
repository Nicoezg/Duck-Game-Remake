#include "duck.h"
#include "game_map.cpp"
#include <iostream>

#define GRAVEDAD 9
#define VELOCIDAD_HORIZONTAL 10
#define VELOCIDAD_SALTO 10
#define VELOCIDAD_ALETEO 15
#define GROUNDLEVEL 10

Duck::Duck(int &id, int &posX, int &posY, GameMap &map) : id(id), posX(posX), posY(posY), map(map)
{
    velX = 0;
    velY = 0;
    jumping = false;
    flapping = false;
    shooting = false;
    isRight = true;
    weapon = nullptr;
}

void Duck::moveLeft()
{
    if (map.checkCollisionsWithBorders(id)) {
        velX = -VELOCIDAD_HORIZONTAL;
        isRight = false;
    }
}

void Duck::moveRight()
{   
    if (map.checkCollisionsWithBorders(id)) {
        velX = VELOCIDAD_HORIZONTAL;
        isRight = true;
    }
}  
 
void Duck::move(bool isRight) 
{
    if (isRight){
        moveRight();
    }else {
        moveLeft();
    }
}

void Duck::jump()   
{
    if (!jumping && map.checkCollisionsWithBorders(id)) {
        velY = -VELOCIDAD_SALTO;
        jumping = true;
        flapping = false;
    }
}

// creo q esto no funciona como deberia
void Duck::flap()
{
    if (jumping && map.checkCollisionsWithBorders(id)) {
        velY = -VELOCIDAD_ALETEO;
        flapping = true;
        jumping = false;
    }
}

void Duck::update()
{
    if (jumping){
        velY += GRAVEDAD;
    } 

    posX += velX;
    posY += velY;

    if ( posY >= GROUNDLEVEL) { 
        posY = GROUNDLEVEL;
        jumping = false;
        velY = 0;
    }
  
}

void Duck::shoot() {
    weapon->shoot(this);
    shooting = true;
}

int Duck::getPositionX() const
{
    return posX;
}

int Duck::getPositionY() const
{
    return posY;
}
