#include "draw_crate.h"

#define DATA_PATH "../client/assets/sprites/props/"

DrawCrate::DrawCrate(SDL2pp::Renderer &renderer)
    : renderer(renderer),
      texture(std::make_shared<SDL2pp::Texture>(
          renderer, SDL2pp::Surface(DATA_PATH "crate.png"))),
      breakingSound(std::make_shared<SDL2pp::Chunk>(
          "../client/assets/audio/crateDestroy.wav")),
      hitSound(std::make_shared<SDL2pp::Chunk>(
          "../client/assets/audio/crateHit.wav")) {
  for (int i = 0; i < 4; i++) {
    crateClip[i].x = i * 16;
    crateClip[i].y = 0;
    crateClip[i].w = 16;
    crateClip[i].h = 16;
  }
}

void DrawCrate::render(const CrateDTO &crate) {
  SDL2pp::Rect dest(crate.get_position_x(), crate.get_position_y(), 16, 16);
  if (crate.get_hp() == 0) {
    sound.change(breakingSound);
    sound.play();
    return;
  }
  if (crate.was_hit()) {
    sound.change(hitSound, 0);
  }
  sound.play();
  renderer.Copy(*texture, crateClip[4 - crate.get_hp()], dest);
}