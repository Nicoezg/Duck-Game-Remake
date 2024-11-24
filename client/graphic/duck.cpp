#include "duck.h"
#include <iostream>
#include <SDL2/SDL_render.h>

const int DUCK_WIDTH = 32;
const int DUCK_HEIGHT = 32;

Duck::Duck(SDL2pp::Renderer &renderer, int id) : posX(0), posY(0), id(id), direction(), dead(false), renderer(renderer),
                                                 weaponsTexture(), wingsTexture(), sfx(), animationMovement(), sound(),
                                                 weapon(renderer, NO_WEAPON, id), helmet(renderer), chestplate(renderer),
                                                 walkClips(), jumpClip(), fallClip(), stillClipWings(), flappingClips(),
                                                 playDeadClips(), walkWeaponClips(), jumpWeaponClip(), fallWeaponClip(),
                                                 stillClipWeapon(), aimingUpwardsClip(), recoilClip() {
    for (int i = 0; i < 5; i++) {
        walkClips[i].x = (i + 1) * DUCK_WIDTH;
        walkClips[i].y = 0;
        walkClips[i].w = DUCK_WIDTH;
        walkClips[i].h = DUCK_HEIGHT;

        walkWeaponClips[i].x = (i + 1) * DUCK_WIDTH;
        walkWeaponClips[i].y = 0;
        walkWeaponClips[i].w = DUCK_WIDTH;
        walkWeaponClips[i].h = DUCK_HEIGHT;
    }

    stillClipWings.x = 0;
    stillClipWings.y = 0;
    stillClipWings.w = DUCK_WIDTH;
    stillClipWings.h = DUCK_HEIGHT;

    stillClipWeapon.x = 0;
    stillClipWeapon.y = 0;
    stillClipWeapon.w = DUCK_WIDTH;
    stillClipWeapon.h = DUCK_HEIGHT;

    jumpClip.x = DUCK_WIDTH;
    jumpClip.y = DUCK_HEIGHT;
    jumpClip.w = DUCK_WIDTH;
    jumpClip.h = DUCK_HEIGHT;

    jumpWeaponClip.x = DUCK_WIDTH;
    jumpWeaponClip.y = DUCK_HEIGHT;
    jumpWeaponClip.w = DUCK_WIDTH;
    jumpWeaponClip.h = DUCK_HEIGHT;

    fallClip.x = DUCK_WIDTH * 3;
    fallClip.y = DUCK_HEIGHT;
    fallClip.w = DUCK_WIDTH;
    fallClip.h = DUCK_HEIGHT;

    fallWeaponClip.x = DUCK_WIDTH * 3;
    fallWeaponClip.y = DUCK_HEIGHT;
    fallWeaponClip.w = DUCK_WIDTH;
    fallWeaponClip.h = DUCK_HEIGHT;

    playDeadClips[0].x = DUCK_WIDTH * 5;
    playDeadClips[0].y = DUCK_HEIGHT;
    playDeadClips[0].w = DUCK_WIDTH;
    playDeadClips[0].h = DUCK_HEIGHT;

    playDeadClips[1].x = 0;
    playDeadClips[1].y = DUCK_HEIGHT * 2;
    playDeadClips[1].w = DUCK_WIDTH;
    playDeadClips[1].h = DUCK_HEIGHT;

    playDeadClips[2].x = DUCK_WIDTH;
    playDeadClips[2].y = DUCK_HEIGHT * 2;
    playDeadClips[2].w = DUCK_WIDTH;
    playDeadClips[2].h = DUCK_HEIGHT;

    flappingClips[0].x = DUCK_WIDTH * 3;
    flappingClips[0].y = DUCK_HEIGHT;
    flappingClips[0].w = DUCK_WIDTH;
    flappingClips[0].h = DUCK_HEIGHT;

    flappingClips[1].x = DUCK_WIDTH * 2;
    flappingClips[1].y = DUCK_HEIGHT;
    flappingClips[1].w = DUCK_WIDTH;
    flappingClips[1].h = DUCK_HEIGHT;

    flappingClips[2].x = 0;
    flappingClips[2].y = DUCK_HEIGHT;
    flappingClips[2].w = DUCK_WIDTH;
    flappingClips[2].h = DUCK_HEIGHT;

    aimingUpwardsClip.x = jumpWeaponClip.x;
    aimingUpwardsClip.y = jumpWeaponClip.y;
    aimingUpwardsClip.w = jumpWeaponClip.w;
    aimingUpwardsClip.h = jumpWeaponClip.h;

    recoilClip.x = DUCK_WIDTH * 4;
    recoilClip.y = DUCK_HEIGHT;
    recoilClip.w = DUCK_WIDTH;
    recoilClip.h = DUCK_HEIGHT;


    sfx[0] = std::make_shared<SDL2pp::Chunk>(SDL2pp::Chunk("../client/graphic/audio/jump.wav"));
    sfx[1] = std::make_shared<SDL2pp::Chunk>(SDL2pp::Chunk("../client/graphic/audio/death.wav"));
}

void Duck::render() {
    SDL2pp::Rect rect{posX, posY, DUCK_WIDTH, DUCK_HEIGHT};
    int flipType = direction ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL;
    int angle = 0; // innecesario
    std::shared_ptr<SDL2pp::Texture> texture = nullptr;

    SDL2pp::Rect currentClip;
    if (weapon.getId() == NO_WEAPON){
        switch (animationMovement.getCurrentType()) {
            case DEAD:
                currentClip = playDeadClips[animationMovement.getCurrentFrame()];
                break;
            case WALKING:
                currentClip = walkClips[animationMovement.getCurrentFrame()];
                break;
            case JUMPING:
                currentClip = jumpClip;
                break;
            case FALLING:
                currentClip = fallClip;
                break;
            case PLAYING_DEAD:
                currentClip = playDeadClips[animationMovement.getCurrentFrame()];
                break;
            case FLAPPING:
                currentClip = flappingClips[animationMovement.getCurrentFrame()];
                break;
            default:
                currentClip = stillClipWings;
                break;
        }
        texture = wingsTexture;
    }

    if (weapon.getId() != NO_WEAPON) {
        switch (animationMovement.getCurrentType()) {
            case DEAD:
                currentClip = playDeadClips[animationMovement.getCurrentFrame()];
                break;
            case WALKING:
                currentClip = walkWeaponClips[animationMovement.getCurrentFrame()];
                break;
            case JUMPING:
                currentClip = jumpWeaponClip;
                break;
            case FALLING:
                currentClip = fallWeaponClip;
                break;
            case PLAYING_DEAD:
                currentClip = playDeadClips[animationMovement.getCurrentFrame()];
                break;
            case AIMING_UPWARDS:
                currentClip = aimingUpwardsClip;
                break;
            case RECOIL:
                currentClip = recoilClip;
                break;
            default:
                currentClip = stillClipWeapon;
                break;
        }
        texture = weaponsTexture;
        
    }
    renderer.Copy(*texture, currentClip, rect, angle, SDL2pp::NullOpt, flipType);
    if (dead) {
        return;
    }


    if (animationMovement.getCurrentType() != PLAYING_DEAD) {
        if (chestplate.isEquipped()) {
            chestplate.render(posX, posY, direction);
        }
        if (helmet.isEquipped()){
            helmet.render(posX, posY, direction);
        }
        if (weapon.getId() != NO_WEAPON) {
            weapon.render(posX, posY, flipType);
        }
    }
    sound.play();

}

void Duck::update(const PlayerDTO &player){
    if (dead){
        return;
    }
    posX = player.get_position_x();
    posY = player.get_position_y();
    auto state = player.get_state();
    direction = player.is_right();

    if (state == DEAD){
        dead = true;
        animationMovement.changeState(PLAYING_DEAD, false);
        sound.change(sfx[1], 0);
        return;
    }

    bool aimingUpwards = state == AIMING_UPWARDS;
    weapon.update(player.get_weapon(), aimingUpwards);
    helmet.update(player.get_helmet());
    chestplate.update(player.get_chestplate());

    
    if (state == animationMovement.getCurrentType()) {
        return;
    }
    else if (state == PLAYING_DEAD) {
        animationMovement.changeState(PLAYING_DEAD, false);

    } else if (state == FLAPPING) {
        animationMovement.changeState(FLAPPING, true);

    } else if (state == FALLING) {
        animationMovement.changeState(FALLING, false);

    } else if (state == JUMPING) {
        animationMovement.changeState(JUMPING, false);
        sound.change(sfx[0], 0);

    } else if (state == AIMING_UPWARDS) {
        animationMovement.changeState(AIMING_UPWARDS, true);

    } else if (state == WALKING) {
        animationMovement.changeState(WALKING, true);

    } else if (state == RECOIL) {
        animationMovement.changeState(RECOIL, false);

    } else {
        animationMovement.changeState(BLANK, true);
    }
        // Cambiar a switch case
}

void Duck::updateFrame(int it) {
    animationMovement.update(it);
}

int Duck::getPosX() { return posX; }

int Duck::getPosY() { return posY; }

bool Duck::isFacingRight() { return direction; }

void Duck::loadTextures() {
    switch (id) {
        case 1:
            weaponsTexture = std::make_shared<SDL2pp::Texture>(renderer, SDL2pp::Surface(
                    "../client/sprites/ducks/white-duck-w-weapon.png"));
            wingsTexture = std::make_shared<SDL2pp::Texture>(renderer, SDL2pp::Surface(
                    "../client/sprites/ducks/white-duck-w-wings.png"));
            break;
        case 2:
            weaponsTexture = std::make_shared<SDL2pp::Texture>(renderer, SDL2pp::Surface(
                    "../client/sprites/ducks/red-duck-w-weapon.png"));
            wingsTexture = std::make_shared<SDL2pp::Texture>(renderer, SDL2pp::Surface(
                    "../client/sprites/ducks/red-duck-w-wings.png"));
            break;
        case 3:
            weaponsTexture = std::make_shared<SDL2pp::Texture>(renderer, SDL2pp::Surface(
                    "../client/sprites/ducks/pink-duck-w-weapon.png"));
            wingsTexture = std::make_shared<SDL2pp::Texture>(renderer, SDL2pp::Surface(
                    "../client/sprites/ducks/pink-duck-w-wings.png"));
            break;
        case 4:
            weaponsTexture = std::make_shared<SDL2pp::Texture>(renderer, SDL2pp::Surface(
                    "../client/sprites/ducks/orange-duck-w-weapon.png"));
            wingsTexture = std::make_shared<SDL2pp::Texture>(renderer, SDL2pp::Surface(
                    "../client/sprites/ducks/orange-duck-w-wings.png"));
            break;
        case 5:
            weaponsTexture = std::make_shared<SDL2pp::Texture>(renderer, SDL2pp::Surface(
                    "../client/sprites/ducks/gray-duck-w-weapon.png"));
            wingsTexture = std::make_shared<SDL2pp::Texture>(renderer, SDL2pp::Surface(
                    "../client/sprites/ducks/gray-duck-w-wings.png"));
            break;
        case 6:
            weaponsTexture = std::make_shared<SDL2pp::Texture>(renderer, SDL2pp::Surface(
                    "../client/sprites/ducks/yellow-duck-w-weapon.png"));
            wingsTexture = std::make_shared<SDL2pp::Texture>(renderer, SDL2pp::Surface(
                    "../client/sprites/ducks/yellow-duck-w-wings.png"));
            break;
        default:
            break;
    }
}

Duck::~Duck() {
}