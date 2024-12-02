//
// Created by fran on 22/10/24.
//

#ifndef TALLER_TP_SENDER_H
#define TALLER_TP_SENDER_H

#include "common/actions/base/action.h"
#include "common/protocol/common/encoder.h"
#include "common/protocol/common/protocol_error.h"
#include "common/queue.h"
#include "common/socket/socket.h"
#include "common/thread.h"

template <typename T, typename U> class Sender : public Thread {
private:
  T *protocol;
  Queue<U> *queue;

public:
  explicit Sender(T *protocol, Queue<U> *queue)
      : protocol(protocol), queue(queue) {}

  virtual void run() override {
    try {
      while (protocol->is_open()) {
        U element = queue->pop();
        protocol->send_element(element);
      }
    } catch (const ProtocolError &e) {
      // se cerro el protrocolo al terminar la conexion
    } catch (const ClosedQueue &e) {
      // se cerro la cola de escritura
    } catch (std::exception &e) {
      std::cerr << "Error sender thread: " << e.what() << std::endl;
    } catch (...) {
      std::cerr << "Error desconocido sender thread" << std::endl;
    }
  }

  void push(U element) { queue->push(element); }

  void close() { queue->close(); }
};

#endif // TALLER_TP_SENDER_H