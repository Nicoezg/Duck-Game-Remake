#ifndef TALLER_TP_MAP_H
#define TALLER_TP_MAP_H

#include "base/event.h"
#include "tile.h"
#include <string>
#include <vector>

class MapDTO : public Event {
private:
  std::list<Tile> platforms;

  int background_id;

  int width;

  int length;

public:
  MapDTO(std::list<Tile> &&platforms, int background_id, int width, int length);

  std::list<Tile> get_platforms() const override;

  int get_background_id() const override;

  int get_width() const override;

  int get_length() const override;
};

#endif // TALLER_TP_MAP_H
