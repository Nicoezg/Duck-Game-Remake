#include "draw_chestplate.h"
#include <memory>
#include <iostream>
#define DATA_PATH "../client/sprites/"

DrawChestplate::DrawChestplate(SDL2pp::Renderer &renderer, bool equipped) : renderer(renderer), equipped(equipped) {
    this->textures[0] = std::make_shared<SDL2pp::Texture>(renderer, SDL2pp::Surface(DATA_PATH "equipment/chestplate.png").SetColorKey(true, 0));
    this->textures[1] = std::make_shared<SDL2pp::Texture>(renderer, SDL2pp::Surface(DATA_PATH "equipment/chestplate-equipped.png").SetColorKey(true, 0));
}

void DrawChestplate::render(int x, int y){
    int chestplateId = equipped ? 1 : 0;
    std::shared_ptr<SDL2pp::Texture> texture = this->textures[chestplateId];
    SDL2pp::Rect dest(x, y, texture->GetWidth(), texture->GetHeight());
    renderer.Copy(*texture, SDL2pp::NullOpt, dest);
}

void DrawChestplate::update(const Chestplate &chestplate){
    equipped = chestplate.is_equipped();
}

bool DrawChestplate::isEquipped(){
    return equipped;
}