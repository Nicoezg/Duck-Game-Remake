#ifndef TALLER_TP_BULLET_MACROS_H
#define TALLER_TP_BULLET_MACROS_H

enum BulletId{
  SHOT = 0x00, // Bala de AK-47, Magnum, Duel Pistol, Cowboy Pistol, Sniper
  LASER_BEAM = 0x01, // Pew Pew Laser y Laser Rifle
  LASER_REBOUND = 0x02, // El pew pew laser rebota en las paredes y cuando pasa
  // eso cambia la textura a esta
  THROWN_GRENADE = 0x03,
  THROWN_BANANA = 0x04,
};

#endif // TALLER_TP_BULLET_MACROS_H