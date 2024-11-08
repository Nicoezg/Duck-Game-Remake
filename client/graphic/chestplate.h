#ifndef CHESTPLATE_H
#define CHESTPLATE_H

#include <SDL2pp/SDL2pp.hh>
#include <map>

class Chestplate {
    private:

    std::map<int, SDL2pp::Texture> textures;

    SDL2_pp::Renderer &renderer;

    public:
    Chestplate();

    void render(int x, int y, int chestplate_id);

};
#endif