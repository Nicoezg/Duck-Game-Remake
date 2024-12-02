#include "chestplate.h"

Chestplate::Chestplate(bool equipped) : equipped(equipped) {}

bool Chestplate::is_equipped() const { return equipped; }
