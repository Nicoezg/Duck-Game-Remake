#include "draw_map.h"

#define DATA_PATH "../client/assets/sprites/maps/tiles/"
#define TILE_HEIGHT 16
#define TILE_WIDTH 16

DrawMap::DrawMap(SDL2pp::Renderer &renderer)
    : textures(), renderer(renderer), backgroundId(0), height(0), width(0) {
  for (int i = 0; i < 48; i++) {
    std::string filePath = std::string(DATA_PATH) + std::to_string(i) + ".png";
    this->textures[i] =
        std::make_shared<SDL2pp::Texture>(renderer, SDL2pp::Surface(filePath));
  }
  this->textures[48] = std::make_shared<SDL2pp::Texture>(
      renderer,
      SDL2pp::Surface("../client/assets/sprites/maps/background/forest.png"));
  this->textures[49] = std::make_shared<SDL2pp::Texture>(
      renderer,
      SDL2pp::Surface("../client/assets/sprites/maps/background/lava.png"));
  this->textures[50] = std::make_shared<SDL2pp::Texture>(
      renderer,
      SDL2pp::Surface("../client/assets/sprites/maps/background/nieve.png"));
}

void DrawMap::load(const Event &map) {
  this->height = map.get_length() * TILE_HEIGHT;
  this->width = map.get_width() * TILE_WIDTH;
  this->platforms = map.get_platforms();
  this->backgroundId = map.get_background_id();
}

void DrawMap::render() {
  SDL2pp::Texture &background = *textures[backgroundId + 48];
  SDL2pp::Rect backgroundRect(0, 0, width, height);
  renderer.Copy(background, backgroundRect);
  SDL2pp::Rect src(0, 0, TILE_WIDTH, TILE_HEIGHT);
  for (auto &platform : platforms) {
    SDL2pp::Texture &texture = *textures[platform.get_tile_id()];
    int textureWidth = texture.GetWidth();
    int textureHeight = texture.GetHeight();
    for (int i = platform.get_start_x(); i < platform.get_end_x() + 1; i++) {
      for (int j = platform.get_start_y(); j < platform.get_end_y() + 1; j++) {
        SDL2pp::Rect dest(i * textureWidth, j * textureHeight, textureWidth,
                          textureHeight);
        renderer.Copy(texture, src, dest);
      }
    }
  }
}