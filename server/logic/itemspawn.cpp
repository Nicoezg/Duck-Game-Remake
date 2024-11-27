#include "itemspawn.h"

ItemSpawn::ItemSpawn(int pos_x, int pos_y, ItemSpawnId content) : pos_x(pos_x), pos_y(pos_y), content(content)
{
    available = true;
    respawnTime = getRespawnTime();
}

int ItemSpawn::getRespawnTime() const
{
    int respawnTime = 200 + std::rand() % 301; 
    return respawnTime;
}

int ItemSpawn::getPosX() const
{
    return pos_x;
}

int ItemSpawn::getPosY() const
{
    return pos_y;
}

bool ItemSpawn::isAvailable() const
{
    return available;
}

ItemSpawnId ItemSpawn::getContent() const
{
    return content;
}

ItemSpawnDTO ItemSpawn::toDTO() const
{
    return ItemSpawnDTO{content, pos_x, pos_y};
}

void ItemSpawn::notAvailable()
{
    available = false;
}

ItemSpawn::~ItemSpawn()
{
}
