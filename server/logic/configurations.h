#ifndef CONFIGURATIONS_H
#define CONFIGURATIONS_H

#include <string>
#include <string>
#include <yaml-cpp/yaml.h>

class Configurations {
private:
  int speed_x;
  int speed_y;
  int flapping_speed;
  int gravity;


  int pewpewlaser_reach;
  int pewpewlaser_ammo;

  explicit Configurations(const YAML::Node &configurations);
  static Configurations *instance;
  static bool loaded;

public:
  static Configurations &configurations();
  static void loadConfig();


  int getSpeedX() const { return speed_x; }
  int getSpeedY() const { return speed_y; }
  int getFlappingSpeed() const { return flapping_speed; }
 
  int getGravity() const { return gravity; }
  int getPewPewLaserReach() const { return pewpewlaser_reach; }
  int getPewPewLaserAmmo() const { return pewpewlaser_ammo; }

  Configurations(const Configurations &) = delete;
  Configurations &operator=(const Configurations &) = delete;
};

#endif // CONFIGURATIONS_H
