#include "duck.h"
#include <SDL2/SDL_render.h>

const int DUCK_WIDTH = 32;
const int DUCK_HEIGHT = 32;



    Duck::Duck(std::shared_ptr<SDL2pp::Texture> texture) : posX(), posY(), id(), falling(), jumping(), dead(), playDead(), direction(), aimingUp(), newAction(), texture(texture), walkClips(), jumpClips(), playDeadClips() {}

    void Duck::render(SDL2pp::Renderer& renderer, int frame){
        int angulo = 0;
        SDL2pp::Rect rect{ posX, posY, DUCK_WIDTH, DUCK_HEIGHT };
        if (newAction){
            frame = 0;
            newAction = false;
        }
        int flipType = direction ? 1 : 0;
        if (dead){

        }else if (falling){
            renderer.Copy(*texture, jumpClips[1], rect, angulo, SDL2pp::NullOpt, flipType);

        } else if (jumping) {
            renderer.Copy(*texture, jumpClips[0], rect, angulo, SDL2pp::NullOpt, flipType);

        } else if (playDead) {
            renderer.Copy(*texture, playDeadClips[frame / 3 % 3], rect, angulo, SDL2pp::NullOpt, flipType);

        } else {
            renderer.Copy(*texture, walkClips[frame / 6 % 6], rect, angulo, SDL2pp::NullOpt, flipType);
        }
    }
    
    void Duck::setClips(){
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

    
    
    int Duck::getPosX() { return posX; }
    int Duck::getPosY() { return posY; }

    bool Duck::isJumping() { return jumping; }


    Duck::~Duck(){
    }