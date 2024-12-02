//
// Created by fran on 22/10/24.
//

#ifndef TALLER_TP_READER_H
#define TALLER_TP_READER_H

#include "common/protocol/common/protocol.h"
#include "common/protocol/common/protocol_error.h"
#include "common/queue.h"
#include "common/thread.h"

template <typename T, typename U> class Reader : public Thread {
private:
  T *protocol;
  Queue<U> *queue;
  std::atomic<bool> connected = true;

public:
  explicit Reader(T *protocol, Queue<U> *queue)
      : protocol(protocol), queue(queue) {}

  virtual void run() override {
    try {
      while (protocol->is_open()) {
        U element = protocol->read_element();
        queue->push(element);
      }
    } catch (ProtocolError &e) {
      // se cerro el protrocolo al terminar la conexion
    } catch (ClosedQueue &e) {
      // se cerro la cola de escritura
    } catch (std::exception &e) {
      std::cerr << "Error reader thread: " << e.what() << std::endl;
    } catch (...) {
      std::cerr << "Error desconocido reader thread" << std::endl;
    }
    connected = false;
  }

  void close() { queue->close(); }

  bool is_connected() { return connected; }
};

#endif // TALLER_TP_READER_H
