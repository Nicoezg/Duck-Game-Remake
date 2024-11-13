#ifndef CONFIGURATIONS_H
#define CONFIGURATIONS_H

#include <yaml-cpp/yaml.h>
#include <string>

class Configurations {
private:
    int speed_x;
    int speed_y;
    int flapping_speed;
    int gravity;

    Configurations(const YAML::Node& configurations);
    static Configurations* instance;
    static bool loaded;

public:
    static Configurations& configurations();
    static void loadConfig();

    int getSpeedX() const { return speed_x; }
    int getSpeedY() const { return speed_y; }
    int getFlappingSpeed() const { return flapping_speed; }
    int getGravity() const { return gravity; }

    Configurations(const Configurations&) = delete;
    Configurations& operator=(const Configurations&) = delete;
  
};

#endif // CONFIGURATIONS_H
