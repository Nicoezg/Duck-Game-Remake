
#ifndef TALLER_TP_NOTIFIER_H
#define TALLER_TP_NOTIFIER_H

#include <list>
#include <memory>

#include "common/connection/connection.h"
#include "common/events/base/event.h"
#include "common/queue.h"
#include "common/thread.h"
#include "server_protocol.h"

using ServerConnection =
    Connection<ServerProtocol, std::shared_ptr<Action>, std::shared_ptr<Event>>;

class Notifier {
private:
  std::list<std::shared_ptr<ServerConnection>> clients;
  Queue<std::shared_ptr<Action>> *commands;
  Queue<std::shared_ptr<Event>> events;
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
  explicit Notifier(Queue<std::shared_ptr<Action>> *commands);

  /**
   * @brief Agrega un cliente a la lista de clientes.
   * Los clientes son agregados a traves de una ConnectionSender y se da
   * inicicio a su hilo. Las conexiones son agregadas a una lista. Las
   * conexiones son revisadas ante cada nuevo cliente y si estan cerradas son
   * removidas de la lista.
   * @param client socket del cliente para lectura y escritura
   * @see common_connection.h
   */
  void subscribe(Socket &&client);

  /**
   * @brief Publica un evento en la cola de cada cliente.
   * @param action accion a publicar.
   * @see common_action.h
   */
  void notify(const std::shared_ptr<Event> &event);

  /**
   * @brief Cambia el estado de is_running a false.
   * Notifier deja de correr y cierra cada hilo de los clientes.
   * Finalmente limpia la lista de clientes.
   */
  void close();
};

#endif // TALLER_TP_NOTIFIER_H
