#ifndef GAME_MAP_H
#define GAME_MAP_H

#include "common/events/player.h"
#include "common/actions/base/action.h"
#include <vector>
#include <list>
#include <memory>

class Duck;

class GameMap {
private:
    std::vector<Duck *> players;

public:
    GameMap();

    void addPlayer(int player_id);

    Duck *findPlayer(int playerId);

    void update();

    bool checkCollisionsWithBorders(int playerId);

    PlayerDTO getPlayerState(int playerId);

    void reapDead();

    ~GameMap();

    void process_action(std::shared_ptr<Action> &action);

    std::list<PlayerDTO> getState();
};

#endif
