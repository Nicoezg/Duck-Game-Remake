#ifndef TALLER_TP_GAME_H
#define TALLER_TP_GAME_H

#include <list>
#include <map>

#include "common/actions/connection/create.h"
#include "common/socket/socket.h"
#include "logic/duck.h"
#include "logic/game_map.h"
#include "notifier.h"

class Game : public Thread {
private:
  Queue<std::shared_ptr<Action>> commands;

  Notifier notifier;

  std::atomic<bool> running;

  std::atomic<int> next_player_id;

  std::map<int, PlayerDTO> players;

  std::atomic<int> actual_players;

  int max_players;
  bool started;

  std::list<int> admin_ids;

  GameMap gameMap;

  /**
   * @brief Lee los eventos de la cola de eventos los ejecuta.
   */
  void read_actions();

  void process_action(std::shared_ptr<Action> &action);

public:
  explicit Game(int max_players);

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

  std::list<PlayerDTO> get_players();

  int get_max_players() const;
  int get_actual_players() const;

  bool is_full(int new_players) const;

  bool is_started() const;

  void start_game();

  void add_admin_id(int id);

  void valid_start();

    void notify_state();
};

#endif // TALLER_TP_GAME_H
