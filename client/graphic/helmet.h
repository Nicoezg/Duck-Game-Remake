#ifndef HELMET_H
#define HELMET_H

#include <SDL2pp/SDL2pp.hh>
#include <map>
#include <memory>

class Helmet {
    private:

    std::map<int, std::shared_ptr<SDL2pp::Texture>> textures;

    SDL2pp::Renderer &renderer;

    public:
    Helmet(SDL2pp::Renderer &renderer);

    void render(int x, int y, int helmet_id);

};
#endif