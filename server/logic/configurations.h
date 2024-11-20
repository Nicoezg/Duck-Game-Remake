#ifndef CONFIGURATIONS_H
#define CONFIGURATIONS_H

#include <string>
#include <yaml-cpp/yaml.h>

class Configurations {
private:
  int speed_x;
  int speed_y;
  int flapping_speed;
  int gravity;

  int bullet_speed;
  
  int pewpewlaser_reach;
  int pewpewlaser_ammo;
  int grenade_reach;
  int grenade_ammo;
  int banana_reach;
  int banana_ammo;
  int laserrifle_reach;
  int laserrifle_ammo;
  int ak47_reach;
  int ak47_ammo;
  int duels_reach;
  int duels_ammo;
  int cowboy_reach;
  int cowboy_ammo;
  int magnum_reach;
  int magnum_ammo;
  int shotgun_reach;
  int shotgun_ammo;
  int sniper_reach;
  int sniper_ammo;
  int sniper_cooldown;

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

  int getBulletSpeed() const { return bullet_speed; }

  int getPewPewLaserReach() const { return pewpewlaser_reach; }
  int getPewPewLaserAmmo() const { return pewpewlaser_ammo; }
  int getGrenadeReach() const { return grenade_reach; }
  int getGrenadeAmmo() const { return grenade_ammo; }
  int getBananaReach() const { return banana_reach; }
  int getBananaAmmo() const { return banana_ammo; }
  int getLaserRifleReach() const { return laserrifle_reach; }
  int getLaserRifleAmmo() const { return laserrifle_ammo; }
  int getAk47Reach() const { return ak47_reach; }
  int getAk47Ammo() const { return ak47_ammo; }
  int getDuelsReach() const { return duels_reach; }
  int getDuelsAmmo() const { return duels_ammo; }
  int getCowboyReach() const { return cowboy_reach; }
  int getCowboyAmmo() const { return cowboy_ammo; }
  int getMagnumReach() const { return magnum_reach; }
  int getMagnumAmmo() const { return magnum_ammo; }
  int getShotgunReach() const { return shotgun_reach; }
  int getShotgunAmmo() const { return shotgun_ammo; }
  int getSniperReach() const { return sniper_reach; }
  int getSniperAmmo() const { return sniper_ammo; }
  int getSniperCooldown() const;


  Configurations(const Configurations &) = delete;
  Configurations &operator=(const Configurations &) = delete;

  ~Configurations();
};

#endif // CONFIGURATIONS_H
