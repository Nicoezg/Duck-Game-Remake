#ifndef TALLER_TP_PROTOCOL_H
#define TALLER_TP_PROTOCOL_H

#include <atomic>
#include <cstdint>
#include <mutex>
#include <string>
#include <vector>
#include <memory>

#include "common/actions/create.h"
#include "encoder.h"
#include "common/socket/socket.h"

class Protocol {
private:
    Socket *socket;
    std::atomic<bool> is_closed;

public:
    explicit Protocol(Socket *socket);

    /**
     * @brief Envia la cantidad de bytes especificada a traves del socket.
     */
    void send(void *data, size_t size);

    /**
     * @brief Lee del socket la cantidad de bytes especificada.
     */
    void read(void *data, size_t size);

    bool is_open();

    void close();
};

#endif // TALLER_TP_PROTOCOL_H
