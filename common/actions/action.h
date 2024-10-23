#ifndef TALLER_TP_ACTION_H
#define TALLER_TP_ACTION_H


#include <string>
#include "action_macros.h"

class Action {
private:
    std::string name;
    ActionType type;
    int player_id;

public:

    Action(std::string name, ActionType type, int player_id);

    std::string get_name() const;

    int get_player_id() const;

    ActionType get_type() const;

    virtual int get_game_code() const = 0;
    virtual bool is_x_direction() const = 0;
    virtual bool is_y_direction() const = 0;

    virtual ~Action() = default;
};


#endif //TALLER_TP_ACTION_H
