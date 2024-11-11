#ifndef DUCK_H
#define DUCK_H

#include "game_map.h"
#include "weapons/weapon.h"

class Duck {
private:
  int id;
  int posX, posY;
  int velX, velY;
  bool jumping;
  bool flapping;
  bool shooting;
  GameMap &map;
  Weapon *weapon;
  bool isRight;
  State state;
  bool hasHelmet;
  bool hasArmour;

public:
  Duck(int &id, int &posX, int &posY, GameMap &map);

  void moveRight();
  void moveLeft();
  void move(bool isRight);
  void jump();
  void flap();
  void update();
  void shoot();

  void equipHelmet();
  void equipArmour();

  void takeDamage();

  int getPositionX() const;
  int getPositionY() const;
  int getId() const;
  bool getDirection() const;
  State getState() const;

  ~Duck();
};

#endif // DUCK_H
