#include "draw_crate.h"

#define DATA_PATH "../sprites/"

DrawCrate::DrawCrate(SDL2pp::Renderer &renderer) : renderer(renderer) {
    texture = std::make_shared<SDL2pp::Texture>(renderer, SDL2pp::Surface(DATA_PATH "crate.png").SetColorKey(true, 0));
    for (int i = 0; i < 4; i++){
        crateClip[i].x = i * 16;
        crateClip[i].y = 0;
        crateClip[i].w = 16;
        crateClip[i].h = 16;
    }
    breakingSound = std::make_shared<SDL2pp::Chunk>(DATA_PATH "../audio/crateDestroy.WAV");
    hitSound = std::make_shared<SDL2pp::Chunk>(DATA_PATH "../audio/crateHit.WAV");
}

void DrawCrate::render(const Crate& crate){
    SDL2pp::Rect dest(crate.get_position_x(), crate.get_position_y(), 16, 16);
    if (crate.get_hp() == 0){
        sound.change(breakingSound);
        return;
    }
    // if (crate.was_hit()){ // Implementar en DTO
    //     sound.change(hitSound);
    // }
    renderer.Copy(*texture, crateClip[4 - crate.get_hp()], dest);
}