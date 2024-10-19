#ifndef TP_2_COMMON_CONNECTION_TOPIC_H
#define TP_2_COMMON_CONNECTION_TOPIC_H

#include "common/protocol/protocol.h"
#include "common/queue.h"
#include "common/thread.h"

class ConnectionReader : public Thread {
private:
  Protocol &protocol;
  Queue<Action> &queue;

public:
  /**
   * @brief Constructor de la clase ConnectionReader.
   *
   * @param protocol Protocolo de comunicación con los clientes.
   * @param queue Cola de comunicación.
   */
  ConnectionReader(Protocol &protocol, Queue<Action> &queue);

  /**
   * @brief Lee comandos del protocolo y los pushea a la cola de comandos del
   * juego.
   */
  virtual void run() override;
};

#endif // TP_2_COMMON_CONNECTION_TOPIC_H
