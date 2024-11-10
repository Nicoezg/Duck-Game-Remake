#ifndef ANIMATION_STATE_H
#define ANIMATION_STATE_H
#include <algorithm>

enum class Type {
    WALK,
    JUMP,
    FALL,
    PLAYDEAD,
    IDLE
};

class AnimationState {
    private:
    Type currentType;
    int frameCount;
    int frameDuration;
    bool looping;

    int getDurationForState(Type type);

    public:

    AnimationState();

    void changeState(Type newType, bool shouldLoop = true);

    int getCurrentFrame();

    void update(int frame);

    Type getCurrentType() const;

};
#endif