#include "../../../common/events/map.h"
#include <SDL2pp/SDL2pp.hh>
#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <vector>
#include <yaml-cpp/yaml.h>

class DrawMap {
private:
  std::map<int, std::shared_ptr<SDL2pp::Texture>> textures;

  SDL2pp::Renderer &renderer;

  std::list<Tile> platforms;

  int backgroundId;

  int height;

  int width;

public:
  explicit DrawMap(SDL2pp::Renderer &renderer);

  void load(const Event &map);

  void render();
};