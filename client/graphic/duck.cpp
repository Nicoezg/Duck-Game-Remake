#include "duck.h"
#include <SDL2/SDL_render.h>

const int DUCK_WIDTH = 32;
const int DUCK_HEIGHT = 32;



    Duck::Duck(SDL2pp::Renderer& renderer, int id) : posX(), posY(), id(id), direction(), renderer(renderer), texture(), animationState(), walkClips(), jumpClips(), playDeadClips() {
        for (int i = 0; i < 4; i++){
            walkClips[i].x = i * DUCK_WIDTH;
            walkClips[i].y = 0;
            walkClips[i].w = DUCK_WIDTH;
            walkClips[i].h = DUCK_HEIGHT;
        }

        for (int i = 0; i < 2; i++){
            jumpClips[i].x = i * DUCK_WIDTH;
            jumpClips[i].y = DUCK_HEIGHT;
            jumpClips[i].w = DUCK_WIDTH;
            jumpClips[i].h = DUCK_HEIGHT;
        }

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
    }

    void Duck::render(SDL2pp::Renderer& renderer){
        SDL2pp::Rect rect{ posX, posY, DUCK_WIDTH, DUCK_HEIGHT };
        int flipType = direction ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
        int angle = 0;

        // Select appropriate clip based on current animation state
        SDL2pp::Rect currentClip;

        switch (animationState.getCurrentType()) {
            case Type::WALK:
                currentClip = walkClips[animationState.getCurrentFrame()];
                break;
            case Type::JUMP:
                currentClip = jumpClips[0];
                break;
            case Type::FALL:
                currentClip = jumpClips[1];
                break;
            case Type::PLAYDEAD:
                currentClip = playDeadClips[animationState.getCurrentFrame()];
                break;
            default:
                currentClip = walkClips[0];
                break;
        }

        renderer.Copy(*texture, currentClip, rect, angle, SDL2pp::NullOpt, flipType);
    }

    void Duck::update(const Player &player){
        int prevX = posX;
        posX = player.get_position_x();
        posY = player.get_position_y();
        direction = player.is_right();

        if (player.is_playing_dead()){
            animationState.changeState(Type::PLAYDEAD, false);
        } else if (player.is_falling()) {
            animationState.changeState(Type::FALL, false);
        } else if (player.is_jumping()) {
            animationState.changeState(Type::JUMP, false);
        } else  if (prevX != posX) {
            animationState.changeState(Type::WALK, true);
        } else {
            animationState.changeState(Type::IDLE, false);
        }
    }

    void Duck::updateFrame(int it){
        animationState.update(it);
    }

    int Duck::getPosX() { return posX; }

    int Duck::getPosY() { return posY; }

    bool Duck::isFacingRight() { return direction; }

    void Duck::loadTextures(){
        switch (id){
            case 0:
                texture = std::make_shared<SDL2pp::Texture>(renderer, SDL2pp::Surface(DATA_PATH "ducks/white-duck.png").SetColorKey(true, 0));
                break;
            case 1:
                texture = std::make_shared<SDL2pp::Texture>(renderer, SDL2pp::Surface(DATA_PATH "ducks/grey-duck.png").SetColorKey(true, 0));
                break;
            case 2:
                texture = std::make_shared<SDL2pp::Texture>(renderer, SDL2pp::Surface(DATA_PATH "ducks/yellow-duck.png").SetColorKey(true, 0));
                break;
            case 3:
                texture = std::make_shared<SDL2pp::Texture>(renderer, SDL2pp::Surface(DATA_PATH "ducks/orange-duck.png").SetColorKey(true, 0));
                break;
            default:
                break;
        }
    }

    Duck::~Duck(){
    }