#include "configurations.h"

#define CONFIG_PATH "../server/configs/configurations.yaml"

Configurations::Configurations(const YAML::Node &configurations) {

    // duck
    auto duck_config = configurations["duck"];
    duck = DuckConfig(duck_config["speed_x"].as<int>(),
                      duck_config["speed_y"].as<int>(),
                      duck_config["flapping"].as<int>(),
                      duck_config["gravity"].as<int>());

    // bullets
    bullet_speed = configurations["bullet"]["speed"].as<int>();

    // weapons
    weapons = std::map<std::string, BulletConfig>();
    for (const auto &weapon: configurations["weapons"]) {
        weapons.insert_or_assign(weapon.first.as<std::string>(),
                                 BulletConfig(weapon.second["ammo"].as<int>(),
                                              weapon.second["reach"].as<int>(),
                                              weapon.second["cooldown"].as<int>()));
    }
}

const BulletConfig &Configurations::getBulletConfig(const std::string &weapon_name) const {
    return weapons.at(weapon_name);
}

const DuckConfig &Configurations::getDuckConfig() const {
    return duck;
}

int Configurations::getBulletSpeed() const {
    return bullet_speed;
}


const Configurations &Configurations::configurations() {
    static Configurations instance = Configurations(YAML::LoadFile(CONFIG_PATH));

    return instance;
}
