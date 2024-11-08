#ifndef CHESTPLATE_H
#define CHESTPLATE_H

#include <SDL2pp/SDL2pp.hh>
#include <map>
#include <memory>

class Chestplate {
    private:

    std::map<int, std::shared_ptr<SDL2pp::Texture>> textures;

    SDL2pp::Renderer &renderer;

    public:
    Chestplate(SDL2pp::Renderer &renderer);

    void render(int x, int y, int chestplate_id);

};
#endif