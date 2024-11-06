#ifndef GAME_H
#define GAME_H

#include <SDL2pp/SDL2pp.hh>
#include <map>
#include <memory>
#include "../client.h"
#include "duck.h"
#include "action_handler.h"
#include "../../common/events/broadcast.h"

using namespace SDL2pp;

class Game{
    private:
        //SDLTTF ttf;
        Client &client;

        SDL sdl;

        Window window;

        Renderer renderer;

        // std::map<int, Duck> ducks;

        std::map<int, std::shared_ptr<SDL2pp::Texture>> textures;

        void loadTextures(Renderer &renderer);

        void render(Renderer &renderer, Duck &duck);

        void updateGame(Duck &duck);


    public:
        Game(Client &client);
        
        int start();

        
        
};
#endif