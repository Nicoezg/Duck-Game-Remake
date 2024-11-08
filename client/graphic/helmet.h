#ifndef HELMET_H
#define HELMET_H

#include <SDL2pp/SDL2pp.hh>
#include <map>

class Helmet {
    private:

    std::map<int, SDL2pp::Texture> textures;

    SDL2_pp::Renderer &renderer;

    public:
    Helmet();

    void render(int x, int y, int helmet_id);

};
#endif