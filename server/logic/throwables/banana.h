#ifndef THROWN_BANANA_H
#define THROWN_BANANA_H

#include "throwable.h"

class ThrownBanana : public Throwable {
private:

    bool consumed = false;
    int distance_travelled = 0;
    bool onGround = false;
public:
  ThrownBanana(GameMap &map, bool isRight, int pos_x, int pos_y, int reach);

  void update() override;

  bool isOver() const override { return consumed; }

  void consume() override { consumed = true; }

  ThrowableDTO toDTO() const override;
};

#endif // THROWN_BANANA_H