#ifndef ANIMATION_MOVEMENT_H
#define ANIMATION_MOVEMENT_H
#include <algorithm>

enum class MovementType {
    WALK,
    JUMP,
    FALL,
    PLAYDEAD,
    FLAP,
    AIMING_UPWARDS,
    IDLE
};

class AnimationMovement {
    private:
    MovementType currentType;
    int frameCount;
    int frameDuration;
    bool looping;

    int getDurationForState(MovementType type);

    public:

    AnimationMovement();

    void changeState(MovementType newType, bool shouldLoop = true);

    int getCurrentFrame();

    void update(int frame);

    MovementType getCurrentType() const;

};
#endif