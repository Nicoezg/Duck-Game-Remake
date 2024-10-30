#ifndef GAME_H
#define GAME_H

#include <SDL2pp/SDL2pp.hh>
#include <map>
#include <memory>
#include "idea_client.h"
#include "duck.h"

using namespace SDL2pp;

class Game{
    private:
        //SDLTTF ttf;
        Client &client;
        int result;
        //std::map<std::string, Duck> ducks;
        std::map<int, std::shared_ptr<SDL2pp::Texture>> textures;

        // void updateGame();

        void loadTextures(Renderer &renderer);

        void render(Renderer &renderer, Duck &duck, int it);


    public:
        Game(Client &client);
        int start();

        
        
};
#endif