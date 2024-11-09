#ifndef ANIMATION_WINGS_H
#define ANIMATION_WINGS_H
#include <algorithm>

enum class WingType {
    WALK,
    JUMP,
    FALL,
    PLAYDEAD,
    FLAPPING,
    IDLE,
    WEAPON
};

class AnimationWings {
    private:
    WingType currentType;
    int frameCount;
    int frameDuration;
    bool looping;

    int getDurationForState(WingType type);

    public:

    AnimationWings();

    void changeState(WingType newType, bool shouldLoop = true);

    int getCurrentFrame();

    void update(int frame);

    WingType getCurrentType() const;

};
#endif