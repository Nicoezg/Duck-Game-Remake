#include "animation_wings.h"


AnimationWings::AnimationWings() : currentType(WingType::IDLE), frameCount(0), frameDuration(1), looping(true) {}


int AnimationWings::getDurationForState(WingType type) {
        switch (type) {
            case WingType::WALK: return 4;
            case WingType::JUMP: return 1;
            case WingType::FALL: return 1;
            case WingType::IDLE: return 1;
            case WingType::FLAPPING: return 3;
            case WingType::WEAPON: return 1;
            default: return 1;
        }
    }

void AnimationWings::changeState(WingType newType, bool shouldLoop) {
        if (currentType != newType) {
            currentType = newType;
            frameCount = 0;
            frameDuration = getDurationForState(newType);
            looping = shouldLoop;
        }
    }

int AnimationWings::getCurrentFrame() {
        return looping 
            ? (frameCount / frameDuration % frameDuration)
            : std::min(frameCount / frameDuration, frameDuration - 1);
    }

void AnimationWings::update(int frame) {
        frameCount += frame;
    }

WingType AnimationWings::getCurrentType() const { return currentType; }
