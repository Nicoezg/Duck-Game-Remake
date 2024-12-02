#include "configurations.h"

#define CONFIG_PATH "../common/configs/configurations.yaml"

DuckConfig Configurations::read_duck_config(const YAML::Node &configurations) {
  auto duck_config = configurations["duck"];
  return {duck_config["speed_x"].as<int>(),  duck_config["speed_y"].as<int>(),
          duck_config["flapping"].as<int>(), duck_config["gravity"].as<int>(),
          duck_config["width"].as<int>(),    duck_config["height"].as<int>(),
          duck_config["center_x"].as<int>(), duck_config["center_y"].as<int>()};
}

std::map<std::string, BulletConfig>
Configurations::read_weapons_configs(const YAML::Node &configurations) {
  int bullet_height = configurations["bullet"]["height"].as<int>();
  int bullet_width = configurations["bullet"]["width"].as<int>();

  std::map<std::string, BulletConfig> weapons_configs;
  for (const auto &weapon : configurations["weapons"]) {
    weapons.insert_or_assign(weapon.first.as<std::string>(),
                             BulletConfig(weapon.second["ammo"].as<int>(),
                                          weapon.second["reach"].as<int>(),
                                          weapon.second["cooldown"].as<int>(),
                                          bullet_height, bullet_width));
  }
  return weapons_configs;
}

Configurations::Configurations(const YAML::Node &configurations)
    : duck(read_duck_config(configurations)),
      weapons(read_weapons_configs(configurations)) {

  // bullets
  bullet_speed_x = configurations["bullet"]["speed_x"].as<int>();
  bullet_speed_y = configurations["bullet"]["speed_y"].as<int>();
}

const BulletConfig &
Configurations::getBulletConfig(const std::string &weapon_name) const {
  return weapons.at(weapon_name);
}

const DuckConfig &Configurations::getDuckConfig() const { return duck; }

int Configurations::getBulletSpeedX() const { return bullet_speed_x; }

int Configurations::getBulletSpeedY() const { return bullet_speed_y; }

const Configurations &Configurations::configurations() {
  static Configurations instance = Configurations(YAML::LoadFile(CONFIG_PATH));

  return instance;
}
