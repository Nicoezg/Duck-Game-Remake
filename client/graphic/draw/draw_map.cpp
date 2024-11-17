#include "draw_map.h"

#define DATA_PATH "../client/sprites/maps/tiles/"

DrawMap::DrawMap(SDL2pp::Renderer& renderer) : textures(), renderer(renderer), backgroundId(0), height(0), width(0) {
    for (int i = 0; i < 96; i++){
        std::string filePath = std::string(DATA_PATH) + std::to_string(i) + ".png";
        this->textures[i] = std::make_shared<SDL2pp::Texture>(renderer, SDL2pp::Surface(filePath).SetColorKey(true, 0));
    }

}

void DrawMap::load(const Map& map){
    this->height = map.get_length();
    this->width = map.get_width();
    this->platforms = map.get_platforms();
    this->backgroundId = map.get_background_id();  
}

/* void DrawMap::loadFromYaml(const std::string& filepath) {
    try {
        YAML::Node config = YAML::LoadFile(filepath);

        width = config["width"].as<int>();
        std::cout << "Width: " << width << std::endl;
        height = config["height"].as<int>();
        
        std::cout << "Height: " << height << std::endl;
        
        const YAML::Node& tiles = config["tiles"];
        for (const auto& tile : tiles) {
            int startX = tile["start_x"].as<int>();
            int endX = tile["end_x"].as<int>();
            int y = tile["y"].as<int>();
            int tileId = tile["tile"].as<int>();
            Tile platform(startX, endX, y, tileId);
            platforms.push_back(platform);            
        }
        height = height * textures[0]->GetHeight();
        width = width * textures[0]->GetWidth();
    } catch (const YAML::Exception& e) {
        std::cerr << "Error parsing YAML file: " << e.what() << std::endl;
        throw;
    }
} */

void DrawMap::render(){
    /* SDL2pp::Texture& background = *textures[backgroundId];
    SDL2pp::Rect backgroundRect(0, 0, width, height);
    renderer.Copy(background, backgroundRect); */
    SDL2pp::Rect src(0, 0, 16, 16);
    for (auto& platform : platforms){
        SDL2pp::Texture& texture = *textures[platform.get_tile_id()];
        int width = texture.GetWidth();
        int height = texture.GetHeight();
        int y = platform.get_y();
        for (int i = platform.get_start_x(); i < platform.get_end_x() + 1; i ++){
            SDL2pp::Rect dest(i * width, y * height, width, height);
            std::cout << dest.x << " " << dest.y << " " << dest.w << " " << dest.h << std::endl;
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