#ifndef TALLER_TP_HELMET_H
#define TALLER_TP_HELMET_H

#include <string>
#include "helmet_macros.h"

class Helmet {
private:
    HelmetId helmet_id;
  
public:
  Helmet(HelmetId helmet_id = NO_HELMET);

  HelmetId get_id() const;
};

#endif // TALLER_TP_HELMET_H
