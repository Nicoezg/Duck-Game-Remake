#ifndef TALLER_TP_MAP_H
#define TALLER_TP_MAP_H

#include <string>
#include <vector>
#include "tile.h"

class Map {
private:
  std::vector<Tile> platforms; // Contiene todos los tiles del mapa

  int background_id; // Id del background del mapa

  int width; // Ancho del mapa

  int length;


public:
  Map(std::vector<Tile> platforms, int background_id, int width, int length);

  std::vector<Tile> get_platforms() const;

  int get_background_id() const;

  int get_width() const;

  int get_length() const;


};

#endif // TALLER_TP_MAP_H
