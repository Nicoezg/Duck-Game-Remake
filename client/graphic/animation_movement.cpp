#include "animation_movement.h"


AnimationMovement::AnimationMovement() : currentType(State::BLANK), frameCount(0), frameDuration(1), looping(true) {}


int AnimationMovement::getDurationForState(State type) {
        switch (type) {
            case State::WALKING: return 5;
            case State::JUMPING: return 1;
            case State::FALLING: return 1;
            case State::BLANK: return 1;
            case State::FLAPPING: return 3;
            case State::AIMING_UPWARDS: return 1;
            case State::RECOIL: return 1;
            case State::PLAYING_DEAD: return 3;
            default: return 1;
        }
    }

void AnimationMovement::changeState(State newType, bool shouldLoop) {
        if (currentType != newType) {
            currentType = newType;
            frameCount = 0;
            frameDuration = getDurationForState(newType);
            looping = shouldLoop;
        }
    }

int AnimationMovement::getCurrentFrame() {
        return looping 
            ? (frameCount / frameDuration % frameDuration)
            : std::min(frameCount / frameDuration, frameDuration - 1);
    }

void AnimationMovement::update(int frame) {
        frameCount += frame;
    }

State AnimationMovement::getCurrentType() const { return currentType; }
