
#ifndef TP_2_THREADS_COMMON_ACTION_MACROS_H
#define TP_2_THREADS_COMMON_ACTION_MACROS_H

#define ACTION_READ "Leer"
#define ACTION_ATTACK "Atacar"
#define ACTION_BROADCAST "Notificar"
#define ACTION_EXIT "Salir"
#define ACTION_CREATE "Crear"
#define ACTION_JOIN "Unirse"

enum ActionCode {
  ATTACK = 0x03,
  BROADCAST = 0x06,
};

#endif // TP_2_THREADS_COMMON_ACTION_MACROS_H
