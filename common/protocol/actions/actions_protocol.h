//
// Created by fran on 22/10/24.
//

#ifndef TALLER_TP_ACTIONS_PROTOCOL_H
#define TALLER_TP_ACTIONS_PROTOCOL_H


#include <atomic>
#include <memory>
#include "common/socket/socket.h"
#include "common/protocol/common/encoder.h"
#include "common/protocol/common/protocol.h"

class ActionsProtocol : public Protocol {
private:

    Encoder encoder;

    ActionType read_action_type();

    void send_create_action(const std::shared_ptr<Action> &action);

    void send_join_action(const std::shared_ptr<Action> &action);

    std::shared_ptr<Action> read_create_action();

    std::shared_ptr<Action> read_join_action();


public:
    ActionsProtocol(Socket *socket, Encoder encoder);

    /**
     * @brief Lee una accion del socket.
     * @return Accion leida.
     */
    std::shared_ptr<Action> read_element();

    /**
     * @brief Envia una accion a traves del socket codificandola.
     * @param action Accion a enviar.
     */
    void send_element(const std::shared_ptr<Action> &action);

    void send_move_action(const std::shared_ptr <Action> &action);

    std::shared_ptr<Action> read_move_action();
};



#endif //TALLER_TP_ACTIONS_PROTOCOL_H
