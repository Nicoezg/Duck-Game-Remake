#ifndef BULLET_H
#define BULLET_H

#include <SDL2pp/SDL2pp.hh>
#include <map>
#include <memory>
#include "../sound.h"
#include "../../../common/events/items/bullet.h"

class DrawBullet{
    private:
    std::map<int, std::shared_ptr<SDL2pp::Texture>> textures;

    SDL2pp::Renderer &renderer;

    Sound sound;

    SDL2pp::Rect explosionClip[6];

    public:
    DrawBullet(SDL2pp::Renderer &renderer);

    void render(const BulletDTO& bullet);
};
#endif