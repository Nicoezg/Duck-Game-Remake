#include "action_handler.h"
#include <SDL2/SDL_events.h>
#include <SDL2pp/SDL2pp.hh>
#include <SDL2/SDL_keycode.h>
#include <exception>

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
                    this->client.moveLeft();
                    break;
                case SDLK_RIGHT:
                    this->client.moveRight();
                    break;
                case SDLK_DOWN:
                    this->client.playDead();
                    break;
                case SDLK_UP:
                    this->client.up();
                    break;
                case SDLK_y:
                    this->client.aimUpwards();
                    break;
                case SDLK_j:
                    this->client.pickUp();
                    break;
                case SDLK_h:
                    this->client.drop();
                    break;
                case SDLK_g:
                    this->client.shoot();
                    break;
                
            }

        } else if (event.type == SDL_KEYUP){
            switch (event.key.keysym.sym){
                case SDLK_LEFT:
                    this->client.stopMoving();
                    break;
                case SDLK_RIGHT:
                    this->client.stopMoving();
                    break;
            }
        }
    }
}

void ActionHandler::processEvents(){
    this->processDuckEvents();
}