#include "configurations.h"

static const std::string configPath = "../server/logic/configurations.yaml";

Configurations *Configurations::instance = nullptr;
bool Configurations::loaded = false;

Configurations& Configurations::configurations() {
  if (!loaded) {
    throw std::runtime_error("No se cargó el archivo de configuraciones");
  }

  static Configurations instance(YAML::LoadFile(configPath));
  return instance;
}

void Configurations::loadConfig() {
  if (!loaded) {
    static Configurations instance(YAML::LoadFile(configPath));
    loaded = true;
  }
}


Configurations::~Configurations(){}

Configurations::Configurations(const YAML::Node &configurations) {

  // duck
  speed_x = configurations["duck"]["speed_x"].as<int>();
  speed_y = configurations["duck"]["speed_y"].as<int>();
  flapping_speed = configurations["duck"]["flapping"].as<int>();
  gravity = configurations["duck"]["gravity"].as<int>();

  // bullets

  bullet_speed = configurations["bullet"]["speed"].as<int>();

  // weapons
  pewpewlaser_reach = configurations["pewpewlaser"]["reach"].as<int>();
  pewpewlaser_ammo = configurations["pewpewlaser"]["ammo"].as<int>();
  grenade_reach = configurations["grenade"]["reach"].as<int>();
  grenade_ammo = configurations["grenade"]["ammo"].as<int>();
  banana_reach = configurations["banana"]["reach"].as<int>();
  banana_ammo = configurations["banana"]["ammo"].as<int>();
  laserrifle_reach = configurations["laserrifle"]["reach"].as<int>();
  laserrifle_ammo = configurations["laserrifle"]["ammo"].as<int>();
  ak47_reach = configurations["ak47"]["reach"].as<int>();
  ak47_ammo = configurations["ak47"]["ammo"].as<int>();
  duels_reach = configurations["duelos"]["reach"].as<int>();
  duels_ammo = configurations["duelos"]["ammo"].as<int>();
  cowboy_reach = configurations["cowboy"]["reach"].as<int>();
  cowboy_ammo = configurations["cowboy"]["ammo"].as<int>();
  magnum_reach = configurations["magnum"]["reach"].as<int>();
  magnum_ammo = configurations["magnum"]["ammo"].as<int>();
  shotgun_reach = configurations["escopeta"]["reach"].as<int>();
  shotgun_ammo = configurations["escopeta"]["ammo"].as<int>();
  sniper_reach = configurations["sniper"]["reach"].as<int>();
  sniper_ammo = configurations["sniper"]["ammo"].as<int>();
}
