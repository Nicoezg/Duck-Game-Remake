#ifndef TALLER_TP_TILE_H
#define TALLER_TP_TILE_H

#include <string>
#include <vector>

class Tile {
    private:
    int start_x;
    int end_x;
    int y;
    int tile_id;


    public:
    Tile(int start_x, int end_x, int y, int tile_id);

    int get_start_x() const;

    int get_end_x() const;

    int get_y() const;

    int get_tile_id() const;
};

#endif // TALLER_TP_TILE_H
