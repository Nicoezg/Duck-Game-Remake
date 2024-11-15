#include <SDL_events.h>
#include "action_handler.h"

ActionHandler::ActionHandler(Client &client) : client(client) {

}

void ActionHandler::processDuckEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {

        if (event.type == SDL_QUIT) {
            throw std::exception(); // a cambiar
        }
        if (event.type == SDL_KEYDOWN) {
            std::shared_ptr<Action> action = nullptr;
            switch (event.key.keysym.sym) {
                case SDLK_LEFT:
                    action = std::make_shared<Move>(this->client.get_player_id_1(), false);
                    break;

                case SDLK_RIGHT:
                    action = std::make_shared<Move>(this->client.get_player_id_1(), true);
                    break;

                case SDLK_DOWN:
                    action = std::make_shared<PlayDead>(this->client.get_player_id_1(), true);
                    break;

                case SDLK_UP:
                    action = std::make_shared<JumpFlap>(this->client.get_player_id_1(), true);
                    break;

                case SDLK_y:
                    action = std::make_shared<AimUpwards>(this->client.get_player_id_1(), true);
                    break;

                case SDLK_j:
                    std::cout << "drop" << std::endl;
                    action = std::make_shared<PickDrop>(this->client.get_player_id_1(), false);
                    break;

                case SDLK_h:
                    std::cout << "pick" << std::endl;
                    action = std::make_shared<PickDrop>(this->client.get_player_id_1(), true);
                    break;

                case SDLK_g:
                    std::cout << "shoot" << std::endl;
                    action = std::make_shared<Shoot>(this->client.get_player_id_1(), true);
                    std::cout << "shoot" << std::endl;
                    break;
            }
            if (!action && (client.get_player_id_2() == SIN_ASIGNAR)) {
                continue;
            }

            switch (event.key.keysym.sym) {
                case SDLK_a:
                    action = std::make_shared<Move>(this->client.get_player_id_2(), false);
                    break;
                case SDLK_d:
                    action = std::make_shared<Move>(this->client.get_player_id_2(), true);
                    break;
                case SDLK_w:
                    action = std::make_shared<JumpFlap>(this->client.get_player_id_2(), true);
                    break;
                case SDLK_s:
                    action = std::make_shared<PlayDead>(this->client.get_player_id_2(), true);
                    break;
            }

            if (!action) {
                continue;
            }
            this->client.send_action(action);

        } else if (event.type == SDL_KEYUP) {
            std::shared_ptr<Action> action = nullptr;
            switch (event.key.keysym.sym) {
                case SDLK_LEFT:
                case SDLK_RIGHT:
                    action = std::make_shared<Still>(this->client.get_player_id_1(), true);
                    break;

                case SDLK_DOWN:
                    action = std::make_shared<PlayDead>(this->client.get_player_id_1(), false);
                    break;
                case SDLK_y:
                    action = std::make_shared<AimUpwards>(this->client.get_player_id_1(), false);
                    break;
            }

            if (!action && (client.get_player_id_2() == SIN_ASIGNAR)) {
                continue;
            }
            switch (event.key.keysym.sym) {
                case SDLK_d:
                case SDLK_a:
                    action = std::make_shared<Still>(this->client.get_player_id_2(), true);
                    break;
                case SDLK_s:
                    action = std::make_shared<PlayDead>(this->client.get_player_id_2(), false);
                    break;
            }

            if (!action) {
                continue;
            }
            this->client.send_action(action);
        }
    }
}

void ActionHandler::processEvents() {
    this->processDuckEvents();
}