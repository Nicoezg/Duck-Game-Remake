#include "action_handler.h"

ActionHandler::ActionHandler(Client &client) : client(client){
    
}

void ActionHandler::processDuckEvents(){
    SDL_Event event;
    while (SDL_PollEvent(&event)){

        if (event.type == SDL_QUIT) {
            throw std::exception(); // a cambiar
        }
        if (event.type == SDL_KEYDOWN){
            std::shared_ptr<Action> action = nullptr;
            switch (event.key.keysym.sym){
                case SDLK_LEFT:
                    action = std::make_shared<Move>(this->client.get_player_id_1(), false);
                    break;

                case SDLK_RIGHT:
                    action = std::make_shared<Move>(this->client.get_player_id_1(), false);
                    break;

                case SDLK_DOWN:
                    action = std::make_shared<Move>(this->client.get_player_id_1(), false);
                    break;

                case SDLK_UP:
                    action = std::make_shared<Move>(this->client.get_player_id_1(), false);
                    break;

                case SDLK_y:
                    action = std::make_shared<Move>(this->client.get_player_id_1(), false);
                    break;

                case SDLK_j:
                    action = std::make_shared<Move>(this->client.get_player_id_1(), false);
                    break;

                case SDLK_h:
                    action = std::make_shared<Move>(this->client.get_player_id_1(), false);
                    break;

                case SDLK_g:
                    action = std::make_shared<Move>(this->client.get_player_id_1(), false);
                    break;
                
            }
            this->client.send_action(action);

        } else if (event.type == SDL_KEYUP){
            std::shared_ptr<Action> action = nullptr;
            switch (event.key.keysym.sym){
                case SDLK_LEFT:
                    break;

                case SDLK_RIGHT:
                    break;

                case SDLK_DOWN:
                    action = std::make_shared<Move>(this->client.get_player_id_1(), false);
                    break;
                
                case SDLK_y:
                    action = std::make_shared<Move>(this->client.get_player_id_1(), false);
                    break;

            }
            this->client.send_action(action);
        }
    }
}

void ActionHandler::processEvents(){
    this->processDuckEvents();
}