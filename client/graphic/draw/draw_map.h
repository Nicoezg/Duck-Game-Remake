#include <map>
#include <memory>
#include <string>
#include <vector>
#include <iostream>
#include <yaml-cpp/yaml.h>
#include <SDL2pp/SDL2pp.hh>
#include "../../../common/events/map.h"

class DrawMap{
    private:

    std::map<int, std::shared_ptr<SDL2pp::Texture>> textures;

    SDL2pp::Renderer& renderer;

    std::list<Tile> platforms;

    int backgroundId;

    int height;

    int width;

    public:

    DrawMap(SDL2pp::Renderer& renderer);

    void load(const Map& map);

    void render();

    int getHeight() const;

    int getWidth() const;
};