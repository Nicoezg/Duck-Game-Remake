#ifndef CONFIGURATIONS_H
#define CONFIGURATIONS_H

#include <string>
#include <yaml-cpp/yaml.h>
#include "bullet_config.h"
#include "duck_config.h"

#define SNIPER_NAME "sniper"
#define PEW_PEW_LASER_NAME "pewpewlaser"
#define GRENADE_NAME "grenade"
#define BANANA_NAME "banana"
#define LASER_RIFLE_NAME "laserrifle"
#define AK47_NAME "ak47"
#define DUELOS_NAME "duelos"
#define COWBOY_NAME "cowboy"
#define MAGNUM_NAME "magnum"
#define ESCOPETA_NAME "escopeta"

#define CONFIG Configurations::configurations()

class Configurations {
private:
    int bullet_speed;

    DuckConfig duck;

    std::map<std::string, BulletConfig> weapons;

public:
    static const Configurations &configurations();

    int getBulletSpeed() const;

    const BulletConfig &getBulletConfig(const std::string &weapon_name) const;

    const DuckConfig &getDuckConfig() const;

    explicit Configurations(const YAML::Node &configurations);
};

#endif // CONFIGURATIONS_H
