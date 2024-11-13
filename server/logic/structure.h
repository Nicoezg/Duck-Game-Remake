#ifndef STRUCTURE_H
#define STRUCTURE_H

struct Structure{
    int start_x;
    int end_x;
    int y;
    int id;
};

struct Ramp{
    int start_x;
    int end_x;
    int y;
    int id;
    int type;//type 0 es 30 grados y type 1 es 45 grados
};

struct Spawn{
    int x;
    int y;
};

struct Helmet{
    int x;
    int y;
};

struct Armor{
    int x;
    int y;
};

struct Box{
    int x;
    int y;
};



#endif // STRUCTURE_H