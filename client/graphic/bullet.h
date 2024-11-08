#ifndef BULLET_H
#define BULLET_H

#include <SDL2pp/SDL2pp.hh>
#include <map>

class Bullet{
    private:
    std::map<int, SDL2pp::Texture> textures;

    SDL2_pp::Renderer &renderer;

    public:
    Bullet(Renderer &renderer);

    void render(int x, int y, int facing, int bullet_id);
};
#endif