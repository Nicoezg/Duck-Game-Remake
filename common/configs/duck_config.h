//
// Created by fran on 21/11/24.
//

#ifndef TALLER_TP_DUCK_CONFIG_H
#define TALLER_TP_DUCK_CONFIG_H


class DuckConfig {
private:

    int speed_x;
    int speed_y;
    int flapping_speed;
    int gravity;
    int width;
    int height;
    int center_x;
    int center_y;
public:
    DuckConfig(int speed_x, int speed_y, int flapping_speed,
               int gravity, int width, int height, int center_x, int center_y);

    int getSpeedX() const;
    int getSpeedY() const;
    int getFlappingSpeed() const;
    int getGravity() const;
    int getWidth() const;
    int getHeight() const;
    int getCenterX() const;
    int getCenterY() const;
};


#endif //TALLER_TP_DUCK_CONFIG_H
