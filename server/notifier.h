//
// Created by fran on 21/04/24.
//

#ifndef TP_2_THREADS_SERVER_NOTIFIER_H
#define TP_2_THREADS_SERVER_NOTIFIER_H

#include <list>
#include <memory>

#include "common/connection/connection_sender.h"
#include "common/thread.h"
#include "common/protocol/action.h"
#include "common/queue.h"

class Notifier : public Thread {
private:
  std::list<std::shared_ptr<ConnectionSender>> clients;
  Queue<Action> &commands; // Comandos de los clientes
  Queue<Action> &events; // Eventos del juego
  std::atomic<bool> is_running;
  std::mutex mtx_client; // mutex para la lista de clientes

  /**
   * @brief Remueve las conexiones cerradas de la lista de clientes liberando
   * los recursos.
   */
  void remove_closed_connections();

public:
  /**
   * Constructor
   * @param commands cola de comandos donde los clientes escriben
   * @param events cola de eventos donde el juego escribe
   */
  Notifier(Queue<Action> &commands, Queue<Action> &events);

  /**
   * @brief Agrega un cliente a la lista de clientes.
   * Los clientes son agregados a traves de una ConnectionSender y se da
   * inicicio a su hilo. Las conexiones son agregadas a una lista. Las
   * conexiones son revisadas ante cada nuevo cliente y si estan cerradas son
   * removidas de la lista.
   * @param client socket del cliente para lectura y escritura
   * @see common_connection.h
   */
  void subscribe(Socket client);

  /**
   * @brief Publica una accion en la cola de cada cliente.
   * @param action accion a publicar.
   * @see common_action.h
   */
  void notify(const Action &action);

  /**
   * @brief Corre el hilo de Notifier.
   * Notifier corre en un loop y notifica a los clientes de la cola de eventos
   * cada accion recibida desde la cola de eventos del juego.
   */
  void run() override;

  /**
   * @brief Cambia el estado de is_running a false.
   * Notifier deja de correr y cierra cada hilo de los clientes.
   * Finalmente limpia la lista de clientes.
   */
  void close();
};

#endif // TP_2_THREADS_SERVER_NOTIFIER_H
