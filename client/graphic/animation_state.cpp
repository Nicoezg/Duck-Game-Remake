#include "animation_state.h"


AnimationState::AnimationState() : currentType(Type::IDLE), frameCount(0), frameDuration(1), looping(true) {}


int AnimationState::getDurationForState(Type type) {
        switch (type) {
            case Type::WALK: return 6;
            case Type::JUMP: return 1;
            case Type::FALL: return 1;
            case Type::IDLE: return 1;
            case Type::PLAYDEAD: return 3;
            default: return 1;
        }
    }

void AnimationState::changeState(Type newType, bool shouldLoop) {
        if (currentType != newType) {
            currentType = newType;
            frameCount = 0;
            frameDuration = getDurationForState(newType);
            looping = shouldLoop;
        }
    }

int AnimationState::getCurrentFrame() {
        return looping 
            ? (frameCount / frameDuration % frameDuration)
            : std::min(frameCount / frameDuration, frameDuration - 1);
    }

void AnimationState::update(int frame) {
        frameCount += frame;
    }

Type AnimationState::getCurrentType() const { return currentType; }
