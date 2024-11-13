#include "duck.h"
#include <SDL2/SDL_render.h>

const int DUCK_WIDTH = 32;
const int DUCK_HEIGHT = 32;

    Duck::Duck(SDL2pp::Renderer& renderer, int id) : posX(), posY(), id(id), direction(), renderer(renderer), 
    weaponsTexture(), wingsTexture(), sfx(), animationMovement(), sound(), weapon(renderer), helmet(renderer), chestplate(renderer), 
    walkClips(), jumpClip(), fallClip(), flappingClips(), playDeadClips(), walkWeaponClips(), jumpWeaponClip(), fallWeaponClip(), aimingUpwardsClip() {
        for (int i = 1; i < 6; i++){
            walkClips[i].x = i * DUCK_WIDTH;
            walkClips[i].y = 0;
            walkClips[i].w = DUCK_WIDTH;
            walkClips[i].h = DUCK_HEIGHT;

            walkWeaponClips[i].x = i * DUCK_WIDTH;
            walkWeaponClips[i].y = 0;
            walkWeaponClips[i].w = DUCK_WIDTH;
            walkWeaponClips[i].h = DUCK_HEIGHT;
        }

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

        aimingUpwardsClip.x = DUCK_WIDTH * 3;
        aimingUpwardsClip.y = DUCK_HEIGHT * 2;
        aimingUpwardsClip.w = DUCK_WIDTH;
        aimingUpwardsClip.h = DUCK_HEIGHT;

        sfx[0] = std::make_shared<SDL2pp::Chunk>(SDL2pp::Chunk(DATA_PATH "sounds/jump.wav"));
        sfx[1] = std::make_shared<SDL2pp::Chunk>(SDL2pp::Chunk(DATA_PATH "sounds/death.wav"));
        // Falta aiming_upwards. No se cual podria ser
    }

    void Duck::render(){
        SDL2pp::Rect rect{ posX, posY, DUCK_WIDTH, DUCK_HEIGHT };
        int flipType = direction ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
        int angle = 0; // innecesario

        SDL2pp::Rect currentClip;

        if (weapon.getId() == NO_WEAPON){

            switch (animationMovement.getCurrentType()) {
                case MovementType::WALK:
                    currentClip = walkClips[animationMovement.getCurrentFrame()];
                    break;
                case MovementType::JUMP:
                    currentClip = jumpClip;
                    sound.play();
                    break;
                case MovementType::FALL:
                    currentClip = fallClip;
                    break;
                case MovementType::PLAYDEAD:
                    currentClip = playDeadClips[animationMovement.getCurrentFrame()];
                    break;
                default:
                    currentClip = walkClips[0];
                    break;
            }

        } else {    
            switch (animationMovement.getCurrentType()) {
                case MovementType::WALK:
                    currentClip = walkWeaponClips[animationMovement.getCurrentFrame()];
                    break;
                case MovementType::JUMP:
                    currentClip = jumpWeaponClip;
                    sound.play();
                    break;
                case MovementType::FALL:
                    currentClip = fallWeaponClip;
                    break;
                case MovementType::PLAYDEAD:
                    currentClip = playDeadClips[animationMovement.getCurrentFrame()];
                    break;
                case MovementType::AIMING_UPWARDS:
                    currentClip = aimingUpwardsClip;
                    break;
                default:
                    currentClip = walkWeaponClips[0];
                    break;
            }
            weapon.render(posX, posY); // A determinar posiciones
        }
        if (chestplate.isEquipped()){
            chestplate.render(posX, posY); // A determinar posiciones
        }
        if (helmet.isEquipped()){
            helmet.render(posX, posY); // A determinar posiciones
        }
        sound.play();
        renderer.Copy(*weaponsTexture, currentClip, rect, angle, SDL2pp::NullOpt, flipType);
    }

    void Duck::update(const Player &player){
        int prevX = posX;
        posX = player.get_position_x();
        posY = player.get_position_y();
        direction = player.is_right();
        weapon.update(player.get_weapon());
        helmet.update(player.get_helmet());
        chestplate.update(player.get_chestplate());

        auto state = player.get_state();
        if (state == PLAYING_DEAD || state == DEAD) {
            animationMovement.changeState(MovementType::PLAYDEAD, false);
            sound.change(sfx[1], 0);

        } else if (state == FALLING) {
            animationMovement.changeState(MovementType::FALL, false);

        } else if (state == JUMPING) {
            animationMovement.changeState(MovementType::JUMP, false);
            sound.change(sfx[0], 0);

        } else if (state == FLAPPING) {
            animationMovement.changeState(MovementType::FALL, false);
        
        } else if (state == AIMING_UPWARDS) {
            animationMovement.changeState(MovementType::IDLE, false);

        } else  if (prevX != posX) {
            animationMovement.changeState(MovementType::WALK, true);

        } else {
            animationMovement.changeState(MovementType::IDLE, false);
        }
    }

    void Duck::updateFrame(int it){
        animationMovement.update(it);
    }

    int Duck::getPosX() { return posX; }

    int Duck::getPosY() { return posY; }

    bool Duck::isFacingRight() { return direction; }

    void Duck::loadTextures(){
        switch (id){
            case 0:
                weaponsTexture = std::make_shared<SDL2pp::Texture>(renderer, SDL2pp::Surface(DATA_PATH "ducks/white-duck-w-weapons.png").SetColorKey(true, 0));
                wingsTexture = std::make_shared<SDL2pp::Texture>(renderer, SDL2pp::Surface(DATA_PATH "ducks/white-duck-w-wings.png").SetColorKey(true, 0));
                break;
            case 1:
                weaponsTexture = std::make_shared<SDL2pp::Texture>(renderer, SDL2pp::Surface(DATA_PATH "ducks/gray-duck-w-weapons.png").SetColorKey(true, 0));
                wingsTexture = std::make_shared<SDL2pp::Texture>(renderer, SDL2pp::Surface(DATA_PATH "ducks/gray-duck-w-wings.png").SetColorKey(true, 0));
                break;
            case 2:
                weaponsTexture = std::make_shared<SDL2pp::Texture>(renderer, SDL2pp::Surface(DATA_PATH "ducks/yellow-duck-w-weapons.png").SetColorKey(true, 0));
                wingsTexture = std::make_shared<SDL2pp::Texture>(renderer, SDL2pp::Surface(DATA_PATH "ducks/yellow-duck-wings.png").SetColorKey(true, 0));
                break;
            case 3:
                weaponsTexture = std::make_shared<SDL2pp::Texture>(renderer, SDL2pp::Surface(DATA_PATH "ducks/orange-duck-w-weapons.png").SetColorKey(true, 0));
                wingsTexture = std::make_shared<SDL2pp::Texture>(renderer, SDL2pp::Surface(DATA_PATH "ducks/orange-duck-w-wings.png").SetColorKey(true, 0));
                break;
            case 4:
                weaponsTexture = std::make_shared<SDL2pp::Texture>(renderer, SDL2pp::Surface(DATA_PATH "ducks/red-duck-w-weapons.png").SetColorKey(true, 0));
                wingsTexture = std::make_shared<SDL2pp::Texture>(renderer, SDL2pp::Surface(DATA_PATH "ducks/red-duck-w-wings.png").SetColorKey(true, 0));
                break;
            case 5:
                weaponsTexture = std::make_shared<SDL2pp::Texture>(renderer, SDL2pp::Surface(DATA_PATH "ducks/pink-duck-w-weapons.png").SetColorKey(true, 0));
                wingsTexture = std::make_shared<SDL2pp::Texture>(renderer, SDL2pp::Surface(DATA_PATH "ducks/pink-duck-w-wings.png").SetColorKey(true, 0));
                break;
            default:
                break;
        }
    }

    Duck::~Duck(){
    }