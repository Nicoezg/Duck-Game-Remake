#ifndef TP_2_COMMON_GAME_H
#define TP_2_COMMON_GAME_H

#include <list>

#include "notifier.h"
#include "common/protocol/action.h"
#include "common/socket/socket.h"

class Game : public Thread {
private:
  Queue<Action> commands;
  Queue<Action> events;

  Notifier notifier;

  std::atomic<bool> running;

  std::atomic<u_int16_t> next_player_id;


  /**
   * @brief Lee los eventos de la cola de eventos los ejecuta.
   */
  void read_actions();


public:
  explicit Game();

  /**
   * @brief Inicia el hilo del notifier y al finalizar se encarga de
   * liberar los recursos utilizados.
   * Inicia el game loop del juego que consiste en el llamado
   * a update() y read_actions(). Cada loop se ejecuta con un sleep de 200 ms.
   * En cada loop ejecuta la totalidad de commandos existentes en la cola de
   * comandos.
   */
  void run() override;

  bool is_running() const;

  /**
   * @brief Cierra las colas de eventos, comandos y el Notifier.
   *
   */
  void close();

  /**
   * @brief Suscribe un socket al Notifier.
   *
   * @param socket: Socket de lectura y escritura de un cliente.
   */
  void add(Socket &&socket);

  void position_command(Action &action);

  /**
   * @brief Incrementa el id del proximo jugador y lo devuelve.
   *
   * @return u_int16_t: id del proximo jugador.
   */
  u_int16_t get_next_player_id();
};

#endif // TP_2_COMMON_GAME_H
