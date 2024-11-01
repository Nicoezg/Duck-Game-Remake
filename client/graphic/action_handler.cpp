#include "action_handler.h"
#include <SDL2/SDL_events.h>
#include <SDL2pp/SDL2pp.hh>
#include <SDL2/SDL_keycode.h>
#include <exception>
#include "../../common/actions/action.h"
#include "../../common/actions/aim_upwards.h"
#include "../../common/actions/pick_drop.h"
#include "../../common/actions/move.h"
#include "../../common/actions/play_dead.h"
#include "../../common/actions/shoot.h"
#include "../../common/actions/jump_flap.h"

ActionHandler::ActionHandler(Client &client) : client(client){
    
}

void ActionHandler::processDuckEvents(){
    SDL_Event event;
    while (SDL_PollEvent(&event)){

        if (event.type == SDL_QUIT) {
            throw std::exception(); // a cambiar
        }
        if (event.type == SDL_KEYDOWN){
            switch (event.key.keysym.sym){
                case SDLK_LEFT:
                    Move moveLeft(this->client.getPlayerId(), false);
                    this->client.run_command(moveLeft);
                    break;

                case SDLK_RIGHT:
                    Move moveRight(this->client.getPlayerId(), true);
                    this->client.run_command(moveRight);
                    break;

                case SDLK_DOWN:
                    PlayDead playDead(this->client.getPlayerId(), true);
                    this->client.run_command(playDead);
                    break;

                case SDLK_UP:
                    JumpFlap jumpFlap(this->client.getPlayerId(), true);
                    this->client.run_command(jumpFlap);
                    break;

                case SDLK_y:
                    AimUpwards aimUpwards(this->client.getPlayerId(), true);
                    this->client.run_command(aimUpwards);
                    break;

                case SDLK_j:
                    PickDrop pickDrop(this->client.getPlayerId(), true);
                    this->client.run_command(pickDrop);
                    break;

                case SDLK_h:
                    PickDrop pickDrop(this->client.getPlayerId(), false);
                    this->client.run_command(pickDrop);
                    break;

                case SDLK_g:
                    Shoot shoot(this->client.getPlayerId());
                    this->client.run_command(shoot);
                    break;
                
            }

        } else if (event.type == SDL_KEYUP){
            switch (event.key.keysym.sym){
                case SDLK_LEFT:
                    break;

                case SDLK_RIGHT:
                    break;

                case SDLK_DOWN:
                    PlayDead playDead(this->client.getPlayerId(), false);
                    this->client.run_command(playDead);
                    break;
                
                case SDLK_y:
                    AimUpwards aimUpwards(this->client.getPlayerId(), false);
                    this->client.run_command(aimUpwards);
                    break;

            }
        }
    }
}

void ActionHandler::processEvents(){
    this->processDuckEvents();
}