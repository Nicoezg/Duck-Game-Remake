
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
  MOVE_REQUEST = 0x03,
  SHOOT_REQUEST = 0x04,
  JUMP_REQUEST = 0x05,
};

#endif // TALLER_TP_ACTION_MACROS_H
