#ifndef CONFIGURATIONS_H
#define CONFIGURATIONS_H

#include "bullet_config.h"
#include "duck_config.h"
#include <string>
#include <yaml-cpp/yaml.h>

#define SNIPER_NAME "sniper"
#define PEW_PEW_LASER_NAME "pewpewlaser"
#define GRENADE_NAME "grenade"
#define BANANA_NAME "banana"
#define LASER_RIFLE_NAME "laserrifle"
#define AK47_NAME "ak47"
#define DUELOS_NAME "duelos"
#define COWBOY_NAME "cowboy"
#define MAGNUM_NAME "magnum"
#define SHOTGUN_NAME "escopeta"
#define BANANA_NAME "banana"

#define CONFIG Configurations::configurations()

class Configurations {
private:
  int bullet_speed_y;
  int bullet_speed_x;

  DuckConfig duck;

  std::map<std::string, BulletConfig> weapons;

public:
  static const Configurations &configurations();

  const BulletConfig &getBulletConfig(const std::string &weapon_name) const;

  const DuckConfig &getDuckConfig() const;

  int getBulletSpeedX() const;

  int getBulletSpeedY() const;

  explicit Configurations(const YAML::Node &configurations);

  DuckConfig read_duck_config(const YAML::Node &configurations);

  std::map<std::string, BulletConfig>
  read_weapons_configs(const YAML::Node &configurations);
};

#endif // CONFIGURATIONS_H
