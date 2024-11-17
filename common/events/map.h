#ifndef TALLER_TP_MAP_H
#define TALLER_TP_MAP_H

#include <string>
#include <vector>
#include "tile.h"
#include "base/event.h"

class Map : public Event {
private:
  std::list<Tile> platforms; // Contiene todos los tiles del mapa

  int background_id; // Id del background del mapa

  int width; // Ancho del mapa

  int length;


public:
  Map(std::list<Tile> &&platforms, int background_id, int width, int length);

  std::list<Tile> get_platforms() const override;

  int get_background_id() const override;

  int get_width() const override;

  int get_length() const override;


};

#endif // TALLER_TP_MAP_H
