#ifndef TALLER_TP_GAME_H
#define TALLER_TP_GAME_H

#include <list>
#include <map>

#include "common/actions/create.h"
#include "common/socket/socket.h"
#include "notifier.h"

class Game : public Thread {
private:
  Queue<std::shared_ptr<Action>> commands;

  Notifier notifier;

  std::atomic<bool> running;

  std::atomic<int> next_player_id;

  std::map<int, Player> players;

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

  void notify_event(std::shared_ptr<Event> &event);

  /**
   * @brief Incrementa el player_id del proximo jugador y lo devuelve.
   *
   * @return u_int16_t: player_id del proximo jugador.
   */
  int get_next_player_id();

  std::list<Player> get_players();
};

#endif // TALLER_TP_GAME_H
