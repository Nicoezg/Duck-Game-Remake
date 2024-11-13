#include "draw_explosion.h"

#define DATA_PATH "../sprites/"

DrawExplosion::DrawExplosion(SDL2pp::Renderer &renderer) : renderer(renderer) {
    texture = std::make_shared<SDL2pp::Texture>(renderer, SDL2pp::Surface(DATA_PATH "explosion.png").SetColorKey(true, 0));
    for (int i = 0; i < 6; i++){
        explosionClip[i].x = i * 64;
        explosionClip[i].y = 0;
        explosionClip[i].w = 64;
        explosionClip[i].h = 64;
    }
}

void DrawExplosion::render(const Explosion& explosion){
    SDL2pp::Rect dest(x, y, 64, 64);

    renderer.Copy(*texture, explosionClip[explosion.get_duration()], dest); // Puede cambiar
}