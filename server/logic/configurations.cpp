#include "configurations.h"

static const std::string configPath = "/home/fran/Documents/Facultad/Taller_Programacion/2024C2/TP_Final/server/logic/configurations.yaml";

Configurations *Configurations::instance = nullptr;
bool Configurations::loaded = false;

Configurations &Configurations::configurations() {
  if (!loaded) {
    throw std::runtime_error("No se cargo el archivo de configuraciones");
  }

  return *instance;
}

void Configurations::loadConfig() {
  if (!loaded) {
    instance = new Configurations(YAML::LoadFile(configPath));
    loaded = true;
  }
}

Configurations::Configurations(const YAML::Node &configurations) {

  // duck
  speed_x = configurations["duck"]["speed_x"].as<int>();
  speed_y = configurations["duck"]["speed_y"].as<int>();
  flapping_speed = configurations["duck"]["flapping"].as<int>();
  gravity = configurations["duck"]["gravity"].as<int>();

  // weapons
  pewpewlaser_reach = configurations["pewpewlaser"]["reach"].as<int>();
  pewpewlaser_ammo = configurations["pewpewlaser"]["ammo"].as<int>();
}