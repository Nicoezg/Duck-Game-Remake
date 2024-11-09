#ifndef TALLER_TP_CHESTPLATE_H
#define TALLER_TP_CHESTPLATE_H

#include <string>
#include "helmet_macros.h"

class Chestplate {
private:
    bool equipped;
  
public:
  Chestplate(bool equipped = false);

  bool is_equipped() const;
};

#endif // TALLER_TP_HELMET_H
