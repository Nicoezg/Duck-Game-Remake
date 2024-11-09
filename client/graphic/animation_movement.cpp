#include "animation_movement.h"


AnimationMovement::AnimationMovement() : currentType(MovementType::IDLE), frameCount(0), frameDuration(1), looping(true) {}


int AnimationMovement::getDurationForState(MovementType type) {
        switch (type) {
            case MovementType::WALK: return 5;
            case MovementType::JUMP: return 1;
            case MovementType::FALL: return 1;
            case MovementType::IDLE: return 1;
            case MovementType::FLAP: return 3;
            case MovementType::AIMING_UPWARDS: return 1;
            case MovementType::PLAYDEAD: return 3;
            default: return 1;
        }
    }

void AnimationMovement::changeState(MovementType newType, bool shouldLoop) {
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

MovementType AnimationMovement::getCurrentType() const { return currentType; }
