#ifndef ANIMATION_MOVEMENT_H
#define ANIMATION_MOVEMENT_H
#include <algorithm>
#include "../../common/events/player_macros.h"

class AnimationMovement {
    private:
    State currentType;
    int frameCount;
    int frameDuration;
    bool looping;

    int getDurationForState(State type);

    public:

    AnimationMovement();

    void changeState(State newType, bool shouldLoop = true);

    int getCurrentFrame();

    void update(int frame);

    State getCurrentType() const;

};
#endif