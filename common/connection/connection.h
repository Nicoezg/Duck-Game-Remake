//
// Created by fran on 22/10/24.
//

#ifndef TALLER_TP_CONNECTION_H
#define TALLER_TP_CONNECTION_H

#include "common/socket/socket.h"
#include "reader.h"
#include "sender.h"
#include <sys/socket.h>

template<typename T, typename U, typename V>
class Connection : public Thread {
private:
    Socket socket;
    T protocol;
    Reader<T, U> reader;
    Sender<T, V> sender;

    std::atomic<bool> was_closed;

public:
    Connection(Socket &&socket, Encoder encoder, Queue<U> *commands,
               Queue<V> *states)
            : socket(std::move(socket)), protocol(&this->socket, encoder),
              reader(&this->protocol, commands), sender(&this->protocol, states),
              was_closed(false) {}

    virtual void run() override {
       reader.start();
       sender.run();
       reader.join();
       was_closed = true;
    }

    bool is_open() { return reader.is_open() && sender.is_open(); }

    void push(V element) { sender.push(element); }

    void push(U element) { reader.push(element); }

    bool is_connected() { return reader.is_connected(); }

    bool is_closed() const { return was_closed; }

    void close() {
        was_closed = true;
        protocol.close();
        socket.shutdown_and_close(SHUT_RDWR);
        reader.close();
        sender.close();
    }
};


#endif // TALLER_TP_CONNECTION_H
