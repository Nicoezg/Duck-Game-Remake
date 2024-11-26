#include "itemspawn.h"

ItemSpawn::ItemSpawn(int pos_x, int pos_y, ItemSpawnId content) : pos_x(pos_x), pos_y(pos_y), content(content)
{
}

int ItemSpawn::getPosX() const
{
    return pos_x;
}

int ItemSpawn::getPosY() const
{
    return pos_y;
}

ItemSpawnId ItemSpawn::getContent() const
{
    return content;
}

ItemSpawn::~ItemSpawn()
{
}
