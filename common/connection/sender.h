//
// Created by fran on 22/10/24.
//

#ifndef TALLER_TP_SENDER_H
#define TALLER_TP_SENDER_H

#include "common/thread.h"
#include "common/queue.h"
#include "common/protocol/common/protocol_error.h"
#include "common/socket/socket.h"
#include "common/actions/action.h"
#include "common/protocol/common/encoder.h"

template<typename T, typename U>
class Sender : public Thread {
private:
    T* protocol;
    Queue<U>* queue;

public:
    explicit Sender(T* protocol, Queue<U>* queue) : protocol(protocol), queue(queue) {}

    virtual void run() override {
        try {
            while (protocol->is_open()) {
                U element = queue->pop();
                protocol->send_element(element);
            }
        } catch (const ClosedQueue &e) {
            return;
        } catch (const ProtocolError &e) {
            return;
        } catch (const std::exception &e) {
            std::cerr << "Unexpected error: " << e.what() << std::endl;
            return;
        }
    }

    void push(U element) {
        queue->push(element);
    }

    void close() {
        queue->close();
    }

};

#endif //TALLER_TP_SENDER_H