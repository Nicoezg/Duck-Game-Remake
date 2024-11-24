#include "throwable.h"

class ThrownBanana : public Throwable {
private:

    bool consumed = false;
public:
  ThrownBanana(GameMap &map, bool isRight, int pos_x, int pos_y, int reach);

  void update() override;

  bool isOver() const override { return consumed; }


  BulletDTO toDTO() const override;
};
