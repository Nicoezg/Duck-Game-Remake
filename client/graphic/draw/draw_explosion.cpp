#include "draw_explosion.h"

DrawExplosion::DrawExplosion(SDL2pp::Renderer &renderer) : renderer(renderer), texture(std::make_shared<SDL2pp::Texture>(renderer, SDL2pp::Surface("../client/sprites/weapons/explosion.png"))), sound(std::make_shared<SDL2pp::Chunk>("../client/graphic/audio/explode.wav")), explosionClip() {
    for (int i = 0; i < 6; i++){
        explosionClip[i].x = i * 64;
        explosionClip[i].y = 0;
        explosionClip[i].w = 64;
        explosionClip[i].h = 64;
    }
}

void DrawExplosion::render(const ExplosionDTO& explosion){
    SDL2pp::Rect dest(explosion.get_position_x(), explosion.get_position_y(), 64, 64);
    if (explosion.get_current_duration() == 0){
        sound.play();
    }

    renderer.Copy(*texture, explosionClip[explosion.get_current_duration()], dest); // Puede cambiar
}