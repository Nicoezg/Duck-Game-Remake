#ifndef HELMET_H
#define HELMET_H

#include <SDL2pp/SDL2pp.hh>
#include <map>
#include <memory>
#include "../../../common/events/items/helmet.h"

class DrawHelmet {
    private:
    std::map<int, std::shared_ptr<SDL2pp::Texture>> textures;

    SDL2pp::Renderer &renderer;

    HelmetId helmetId;

    public:
    DrawHelmet(SDL2pp::Renderer &renderer, HelmetId helmetId = NO_HELMET);

    void render(int x, int y);

    void update(const HelmetDTO &helmet);

    bool isEquipped();

};
#endif