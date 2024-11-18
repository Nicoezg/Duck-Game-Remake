#include "draw_map.h"

#define DATA_PATH "../client/sprites/maps/tiles/"

DrawMap::DrawMap(SDL2pp::Renderer& renderer) : textures(), renderer(renderer), backgroundId(0), height(0), width(0) {
    for (int i = 0; i < 96; i++){
        std::string filePath = std::string(DATA_PATH) + std::to_string(i) + ".png";
        this->textures[i] = std::make_shared<SDL2pp::Texture>(renderer, SDL2pp::Surface(filePath).SetColorKey(true, 0));
    }
    this->textures[96] = std::make_shared<SDL2pp::Texture>(renderer, SDL2pp::Surface("../editor/images/forest.png").SetColorKey(true, 0));
    this->textures[97] = std::make_shared<SDL2pp::Texture>(renderer, SDL2pp::Surface("../editor/images/lava.png").SetColorKey(true, 0));

}

void DrawMap::load(const Event& map){
    this->height = map.get_length() * 16;
    this->width = map.get_width() * 16;
    this->platforms = map.get_platforms();
    this->backgroundId = map.get_background_id();  
}


void DrawMap::render(){
    SDL2pp::Texture& background = *textures[backgroundId + 96];
    SDL2pp::Rect backgroundRect(0, 0, 640, 480);
    renderer.Copy(background, backgroundRect);
    SDL2pp::Rect src(0, 0, 16, 16);
    for (auto& platform : platforms){
        std::cout << platform.get_tile_id() << std::endl;
        SDL2pp::Texture& texture = *textures[platform.get_tile_id()];
        int width = texture.GetWidth();
        int height = texture.GetHeight();
        int y = platform.get_y();
        for (int i = platform.get_start_x(); i < platform.get_end_x() + 1; i ++){
            SDL2pp::Rect dest(i * width, y * height, width, height);
            std::cout << "coordx " << dest.x << "coordy " << dest.y << std::endl;
            std::cout << "ancho " << dest.w << " " << "alto " << dest.h << std::endl;
            renderer.Copy(texture, src, dest);
        }
    }
}

int DrawMap::getHeight() const {
    return height;
}

int DrawMap::getWidth() const {
    return width;
}