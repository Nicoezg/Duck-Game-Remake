
#include "common/connection/connection_reader.h"
#include "common/protocol/protocol_error.h"

ConnectionReader::ConnectionReader(Protocol &protocol, Queue<Action> &queue)
        : protocol(protocol), queue(queue) {}

void ConnectionReader::run() {
    try {
        while (protocol.is_open()) {
            Action action = protocol.read_action();
            queue.push(action);
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
