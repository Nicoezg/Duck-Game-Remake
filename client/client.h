#ifndef TALLER_TP_CLIENT_H
#define TALLER_TP_CLIENT_H

#include <string>

#include "common/queue.h"
#include "common/connection/connection.h"
#include "client_protocol.h"
#include "common/events/event.h"
#include "common/actions/action.h"


using ClientConnection = Connection<ClientProtocol, std::shared_ptr<Event>, std::shared_ptr<Action>>;

class Client {
private:
    Queue<std::shared_ptr<Action>> commands;
    Queue<std::shared_ptr<Event>> events;
    ClientConnection connection;
    int game_code;
    int player_id;

    /**
     * @brief Ejecuta la accion de leer.
     * Lee del protocolo una accion con el estado del juego.
     * Imprime por salida estandar el estado del juego.
     */
    void action_read();

    /**
     * @brief Ejecuta la accion de un comando.
     */
    void run_command(const std::string &command);

    /**
     * Lee un comando de la entrada estandar.
     */
    std::string read_command();


public:
    Client(const char *hostname, const char *service_name);

    /**
     * @brief Inicia la ejecucion del cliente esperando
     * comandos por la entrada estandar.
     */
    void run();

    bool connect_to_game();

    std::string read_connect_command();

};

#endif // TALLER_TP_CLIENT_H
