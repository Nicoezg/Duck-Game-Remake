#include "helmet.h"

HelmetDTO::HelmetDTO(HelmetId helmet_id) : helmet_id(helmet_id) {}

HelmetId HelmetDTO::get_id() const { return helmet_id; }
