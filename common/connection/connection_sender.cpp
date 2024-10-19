
#include "common/connection/connection_sender.h"
#include "common/protocol/protocol_error.h"
#include "common/socket/liberror.h"
#include <netinet/in.h>
#include <utility>

#include "common/connection/connection_reader.h"

ConnectionSender::ConnectionSender(Socket &&socket, Queue<Action> &reader_queue, Encoder encoder)
        : socket(std::move(socket)), protocol(&this->socket, encoder),
          sender_queue(), reader_queue(reader_queue), was_closed(false), mtx() {}

void ConnectionSender::connect_to_game(u_int32_t &game_code,
                                       u_int16_t &player_id) {
    protocol.send_game_code(game_code);
    protocol.read_game_data(game_code, player_id);
}

void ConnectionSender::run() {
    ConnectionReader reader(protocol, reader_queue);
    reader.start();
    try {
        send();
    } catch (const ProtocolError &e) {
    } catch (const ClosedQueue &e) {
    } catch (const std::exception &e) {
        std::cerr << "Unexpected error: " << e.what() << std::endl;
    }
    if (!was_closed) {
        close();
    }
    reader.join();
}

bool ConnectionSender::is_closed() { return was_closed; }

void ConnectionSender::push_action(const Action &action) {
    sender_queue.push(action);
}

void ConnectionSender::send() {
    while (!was_closed && protocol.is_open()) {
        Action action = sender_queue.pop();
        protocol.send_action(action);
    }
}

void ConnectionSender::close() {
    std::lock_guard<std::mutex> lck(mtx);
    if (was_closed) {
        return;
    }
    was_closed = true;
    sender_queue.close();
    try {
        socket.shutdown(SHUT_RDWR);
    } catch (const LibError &e) {
        std::cout << "Error al hacer shutdown al socket" << std::endl;
    }
    socket.close();
}
