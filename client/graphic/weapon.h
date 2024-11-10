#ifndef WEAPON_H
#define WEAPON_H

#include <SDL2pp/SDL2pp.hh>
#include <map>

class Weapon {
    private:
    std::map<int, SDL2pp::Texture> textures;

    SDL2pp::Renderer &renderer;

    public:
    Weapon(SDL2pp::Renderer &renderer);

    void render(int x, int y, int weapon_id);

};
#endif