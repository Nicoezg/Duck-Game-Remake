#ifndef GAME_H
#define GAME_H

#include <SDL2pp/SDL2pp.hh>
#include <map>
#include <memory>
#include <vector>
#include "../client.h"
#include "duck.h"
#include "action_handler.h"
#include "../../common/events/broadcast.h"
#include "weapon.h"
#include "chestplate.h"
#include "helmet.h"

using namespace SDL2pp;

class Game{
    private:
        //SDLTTF ttf;
        Client &client;

        SDL sdl;

        Window window;

        Renderer renderer;

        std::vector<Duck> ducks;

        std::map<int, std::shared_ptr<SDL2pp::Texture>> textures;

        Weapon weapon;

        Helmet helmet;

        Chestplate chestplate;

        void loadTextures(Renderer &renderer);

        void render();


    public:
        Game(Client &client, int players);

        void updateGame(Broadcast broadcast);
        
        int start();

        
        
};
#endif