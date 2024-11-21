#include "configurations.h"

#define CONFIG_PATH "../server/configs/configurations.yaml"

DuckConfig Configurations::read_duck_config(const YAML::Node &configurations) {
    auto duck_config = configurations["duck"];
    return {
            duck_config["speed_x"].as<int>(),
            duck_config["speed_y"].as<int>(),
            duck_config["flapping"].as<int>(),
            duck_config["gravity"].as<int>(),
            duck_config["width"].as<int>(),
            duck_config["height"].as<int>(),
            duck_config["center_x"].as<int>(),
            duck_config["center_y"].as<int>()
    };
}

std::map<std::string, BulletConfig> Configurations::read_weapons_configs(const YAML::Node &configurations) {
    std::map<std::string, BulletConfig> weapons_configs;
    for (const auto &weapon: configurations["weapons"]) {
        weapons.insert_or_assign(weapon.first.as<std::string>(), BulletConfig(
                weapon.second["ammo"].as<int>(),
                weapon.second["reach"].as<int>(),
                weapon.second["cooldown"].as<int>()
        ));
    }
    return weapons_configs;
}

Configurations::Configurations(const YAML::Node &configurations) :
        duck(read_duck_config(configurations)), weapons(read_weapons_configs(configurations)) {

    // bullets
    bullet_speed = configurations["bullet"]["speed"].as<int>();

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
