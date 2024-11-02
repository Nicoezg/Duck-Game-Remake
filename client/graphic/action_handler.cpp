#include "action_handler.h"
#include <SDL2/SDL_events.h>
#include <SDL2pp/SDL2pp.hh>
#include <SDL2/SDL_keycode.h>
#include <exception>
#include <memory>
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
        std::shared_ptr<Action> action = nullptr;
        if (event.type == SDL_KEYDOWN){
            switch (event.key.keysym.sym){
                case SDLK_LEFT:
                    action = std::make_shared<Move>(this->client.get_player_id1(), false);
                    break;

                case SDLK_RIGHT:
                    action = std::make_shared<Move>(this->client.get_player_id1(), false);
                    break;

                case SDLK_DOWN:
                    action = std::make_shared<Move>(this->client.get_player_id1(), false);
                    break;

                case SDLK_UP:
                    action = std::make_shared<Move>(this->client.get_player_id1(), false);
                    break;

                case SDLK_y:
                    action = std::make_shared<Move>(this->client.get_player_id1(), false);
                    break;

                case SDLK_j:
                    action = std::make_shared<Move>(this->client.get_player_id1(), false);
                    break;

                case SDLK_h:
                    action = std::make_shared<Move>(this->client.get_player_id1(), false);
                    break;

                case SDLK_g:
                    action = std::make_shared<Move>(this->client.get_player_id1(), false);
                    break;
                
            }

        } else if (event.type == SDL_KEYUP){
            switch (event.key.keysym.sym){
                case SDLK_LEFT:
                    break;

                case SDLK_RIGHT:
                    break;

                case SDLK_DOWN:
                    action = std::make_shared<Move>(this->client.get_player_id1(), false);
                    break;
                
                case SDLK_y:
                    action = std::make_shared<Move>(this->client.get_player_id1(), false);
                    break;

            }
        }
        this->client.run_command("accion"); // Cambiar run_command del lado del client
    }
}

void ActionHandler::processEvents(){
    this->processDuckEvents();
}