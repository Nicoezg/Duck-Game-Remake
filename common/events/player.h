//
// Created by fran on 24/10/24.
//

#ifndef TALLER_TP_PLAYER_H
#define TALLER_TP_PLAYER_H


#include <string>

class Player {
private:
    int player_id;
    int position_x;
    int position_y;

public:
    Player(int player_id, int position_x, int position_y);

    int get_player_id() const;

    int get_position_x() const;

    int get_position_y() const;

    std::string get_text() const;

    void move(bool is_right);

};


#endif //TALLER_TP_PLAYER_H
