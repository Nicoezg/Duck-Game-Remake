#ifndef EXPLOSION_H
#define EXPLOSION_H

#include <SDL2pp/SDL2pp.hh>
#include <map>
#include <memory>
#include "../sound.h"

class DrawExplosion{
    private:
    std::shared_ptr<SDL2pp::Texture> texture;

    SDL2pp::Renderer &renderer;

    Sound sound;

    int frame;

    SDL2pp::Rect explosionClip[6];

    public:
    DrawExplosion(SDL2pp::Renderer &renderer);

    void render(int x, int y, int facing, int bullet_id);
};
#endif