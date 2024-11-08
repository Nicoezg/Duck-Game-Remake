#ifndef BULLET_H
#define BULLET_H

#include <SDL2pp/SDL2pp.hh>
#include <map>
#include <memory>

class Bullet{
    private:
    std::map<int, std::shared_ptr<SDL2pp::Texture>> textures;

    SDL2pp::Renderer &renderer;


    public:
    Bullet(SDL2pp::Renderer &renderer);

    void render(int x, int y, int facing, int bullet_id);
};
#endif