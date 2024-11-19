#ifndef TALLER_TP_HELMET_H
#define TALLER_TP_HELMET_H

#include <string>
#include "helmet_macros.h"

class HelmetDTO {
private:
    HelmetId helmet_id;
  
public:
  HelmetDTO(HelmetId helmet_id = NO_HELMET);

  HelmetId get_id() const;
};

#endif // TALLER_TP_HELMET_H
