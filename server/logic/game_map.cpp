#include "game_map.h"

GameMap::GameMap(int& height, int& width) : height(height), width(width)
{
}

void GameMap::addPlayer(Duck* player)
{
    players.push_back(player);
}

void GameMap::update()
{
    for (auto player : players) {
        player->update();
    }
}

bool GameMap::checkCollisionsWithBorders(int playerId)
{
    Duck* player = players[playerId];
    if (player->getPositionX() >= width) {
        return false;
    } else if (player->getPositionX() <= 0) {
        return false;
    } else if (player->getPositionY() >= height) {
        return false;
    } else if (player->getPositionY() <= 0) {
        return false;
    } else {
        return true;
    }
}