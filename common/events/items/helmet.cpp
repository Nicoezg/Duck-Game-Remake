#include "helmet.h"


Helmet::Helmet(HelmetId helmet_id)
    : helmet_id(helmet_id) {}

HelmetId Helmet::get_id() const { return helmet_id; }
