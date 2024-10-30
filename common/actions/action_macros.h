
#ifndef TALLER_TP_ACTION_MACROS_H
#define TALLER_TP_ACTION_MACROS_H

#define ACTION_EXIT "Salir"
#define ACTION_CREATE "Crear"
#define ACTION_JOIN "Unirse"

#define ACTION_MOVE "Mover"
#define ACTION_JUMP "Saltar"
#define ACTION_SHOOT "Disparar"

enum ActionType {
  CREATE_REQUEST = 0x01,
  JOIN_REQUEST = 0x02,
  MOVE = 0x03,
  SHOOT = 0x04,
  JUMP = 0x05,
  PLAY_DEAD = 0x06,
  JUMP_FLAP = 0x07,
  AIM_UPWARDS = 0x08,
  PICK_DROP = 0x09
};

#endif // TALLER_TP_ACTION_MACROS_H
