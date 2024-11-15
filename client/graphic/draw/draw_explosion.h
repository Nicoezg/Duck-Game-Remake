#ifndef EXPLOSION_H
#define EXPLOSION_H

#include <SDL2pp/SDL2pp.hh>
#include <map>
#include <memory>
#include "../sound.h"
#include "../../../common/events/items/explosion.h"

class DrawExplosion{
    private:

    SDL2pp::Renderer &renderer;

    std::shared_ptr<SDL2pp::Texture> texture;

    Sound sound;

    SDL2pp::Rect explosionClip[6];

    public:
    DrawExplosion(SDL2pp::Renderer &renderer);

    void render(const Explosion& explosion);
};
#endif