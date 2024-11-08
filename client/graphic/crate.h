#ifndef CRATE_H
#define CRATE_H

#include <SDL2pp/SDL2pp.hh>
#include <map>
#include <memory>

class Crate {
    private:

    SDL2pp::Renderer &renderer;

    std::shared_ptr<SDL2pp::Texture> texture;

    int state; // empieza en 0, 1, 2, 3, 4 (en 4 se rompe)

    public:
    Crate(SDL2pp::Renderer &renderer);

    void render(int x, int y);

};
#endif