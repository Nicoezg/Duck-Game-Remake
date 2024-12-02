#ifndef TALLER_TP_CHESTPLATE_H
#define TALLER_TP_CHESTPLATE_H

#include "helmet_macros.h"
#include <string>

class Chestplate {
private:
  bool equipped;

public:
  explicit Chestplate(bool equipped = false);

  bool is_equipped() const;
};

#endif // TALLER_TP_HELMET_H
