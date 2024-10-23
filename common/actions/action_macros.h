
#ifndef TALLER_TP_ACTION_MACROS_H
#define TALLER_TP_ACTION_MACROS_H

#define ACTION_READ "Leer"
#define ACTION_MOVE "Atacar"
#define ACTION_BROADCAST "Notificar"
#define ACTION_EXIT "Salir"
#define ACTION_CREATE "Crear"
#define ACTION_JOIN "Unirse"

enum ActionType {
  CREATE_REQUEST = 0x01,
  JOIN_REQUEST = 0x02,
};

#endif // TALLER_TP_ACTION_MACROS_H
