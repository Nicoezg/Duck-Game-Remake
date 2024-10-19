#ifndef TP_2_CONNECTION_H
#define TP_2_CONNECTION_H

#include <atomic>
#include <string>

#include "common/protocol/action.h"
#include "common/protocol/protocol.h"
#include "common/queue.h"
#include "common/socket/socket.h"
#include "common/thread.h"

class ConnectionSender : public Thread {
private:
  Socket socket;
  Protocol protocol;
  Queue<Action> sender_queue;
  Queue<Action> &reader_queue;
  std::atomic<bool> was_closed;
  std::mutex mtx;

  /**
   * @brief Popea acciones de la cola de eventos y las envía por el protocolo a
   * través del socket a los clientes.
   */
  void send();

public:
  ConnectionSender(Socket &&socket, Queue<Action> &reader_queue, Encoder encoder);

  void connect_to_game(u_int32_t &game_code, u_int16_t &player_id);

  /**
   * @brief Pushea una acción a la cola de eventos.
   * @param action Acción a notificar.
   */
  void push_action(const Action &action);

  /**
   * @brief  Inicia un ConnectionReader, luego llama a send() y
   * al finalizar libera los recursos.
   */
  void run() override;

  bool is_closed();

  /**
   * @brief Cierra la conexión cerrando el protocolo y la cola de eventos.
   */
  void close();
};

#endif // TP_2_CONNECTION_H
