#ifndef TALLER_TP_HELMET_H
#define TALLER_TP_HELMET_H

#include "helmet_macros.h"
#include <string>

class HelmetDTO {
private:
  HelmetId helmet_id;

public:
  explicit HelmetDTO(HelmetId helmet_id = NO_HELMET);

  HelmetId get_id() const;
};

#endif // TALLER_TP_HELMET_H
