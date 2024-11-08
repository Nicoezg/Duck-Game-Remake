#include "crate.h"

#define DATA_PATH "../sprites/"

Crate::Crate(SDL2pp::Renderer &renderer) : renderer(renderer), state(0) {
    texture = std::make_shared<SDL2pp::Texture>(renderer, SDL2pp::Surface(DATA_PATH "crate.png").SetColorKey(true, 0));

}

// falta cambiarle algunas cosas
void Crate::render(int x, int y){
    state++;
    if (state == 4){
        return;
    }
    SDL2pp::Rect dest(x, y, texture->GetWidth(), texture->GetHeight());
    renderer.Copy(*texture, SDL2pp::NullOpt, dest);
}