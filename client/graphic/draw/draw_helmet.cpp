#include "draw_helmet.h"
#include <memory>
#include <iostream>
#define DATA_PATH "../client/sprites/"

DrawHelmet::DrawHelmet(SDL2pp::Renderer &renderer, HelmetId helmetId) : renderer(renderer), helmetId(helmetId) {
    this->textures[0] = std::make_shared<SDL2pp::Texture>(renderer, SDL2pp::Surface(DATA_PATH "equipment/helmet.png").SetColorKey(true, 0));
    this->textures[1] = std::make_shared<SDL2pp::Texture>(renderer, SDL2pp::Surface(DATA_PATH "equipment/knight-helmet.png").SetColorKey(true, 0));
    this->textures[2] = std::make_shared<SDL2pp::Texture>(renderer, SDL2pp::Surface(DATA_PATH "equipment/helmet-equipped.png").SetColorKey(true, 0));
    this->textures[3] = std::make_shared<SDL2pp::Texture>(renderer, SDL2pp::Surface(DATA_PATH "equipment/knight-helmet-equipped.png").SetColorKey(true, 0));
}

void DrawHelmet::render(int x, int y){
    std::shared_ptr<SDL2pp::Texture> texture = this->textures[helmetId];
    SDL2pp::Rect dest(x, y, texture->GetWidth(), texture->GetHeight());
    renderer.Copy(*texture, SDL2pp::NullOpt, dest);
}

void DrawHelmet::update(const HelmetDTO &helmet){
    helmetId = helmet.get_id();
}

bool DrawHelmet::isEquipped(){
    return helmetId;
}