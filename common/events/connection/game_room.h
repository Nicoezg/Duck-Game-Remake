//
// Created by fran on 04/11/24.
//

#ifndef TALLER_TP_GAME_ROOM_H
#define TALLER_TP_GAME_ROOM_H

#include <string>

class GameRoom {
private:
    int game_code{};
    std::string game_name;
    int max_players{};
    int actual_players{};

public:
    GameRoom(int game_code, std::string game_name, int actual_players, int max_players);

    GameRoom();

    std::string get_game_name() const;

    int get_game_code() const;

    int get_max_players() const;

    int get_actual_players() const;

};


#endif //TALLER_TP_GAME_ROOM_H
