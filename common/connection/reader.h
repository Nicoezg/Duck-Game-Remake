//
// Created by fran on 22/10/24.
//

#ifndef TALLER_TP_READER_H
#define TALLER_TP_READER_H

#include "common/thread.h"
#include "common/queue.h"
#include "common/protocol/common/protocol_error.h"
#include "common/protocol/common/protocol.h"


template<typename T, typename U>
class Reader : public Thread {
private:
    T* protocol;
    Queue<U>* queue;

public:
    explicit Reader(T* protocol, Queue<U>* queue) : protocol(protocol), queue(queue) {}

    virtual void run() override {
        try {
            while (protocol->is_open()) {
                U element = protocol->read_element();
                queue->push(element);
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

    void close() {
        queue->close();
    }

};


#endif //TALLER_TP_READER_H
