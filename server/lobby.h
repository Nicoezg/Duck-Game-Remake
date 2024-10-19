//
// Created by fran on 19/05/24.
//

#ifndef TP_FINAL_LOBBY_H
#define TP_FINAL_LOBBY_H

#include "server/game.h"
#include "server/lobby_client.h"
#include <atomic>
#include <list>
#include <map>
#include <memory>
#include <mutex>

class Lobby {
private:
    std::mutex mtx;
    std::map<u_int32_t, std::unique_ptr<Game>> games;
    u_int32_t last_game_id;
    std::list<std::unique_ptr<LobbyClient>> clients;

public:
    Lobby();

    void close();

    /**
     * @brief Agrega un cliente al lobby.
     * @param client El cliente a agregar.
     */
    void add_client(Socket &&client);


    /**
     * @brief Agrega un cliente a un juego.
     * @param game_id El id del juego al que se va a unir el cliente.
     * @param client El cliente a agregar.
     */
    void add_to_game(u_int32_t game_id, Socket &&client);

    /**
     * @brief Crea un nuevo juego y lo agrega al lobby.
     * @return El id del juego creado.
     */
    u_int32_t create_game();

    /**
     * @brief Verifica si un cliente está cerrado y lo elimina.
     */
    void clean_closed_clients();

    /**
     * @brief Verifica si un juego existe.
     * @param game_id El id del juego a verificar.
     * @return True si el juego existe, false en caso contrario.
     */
    bool game_exists(u_int32_t game_id);


    /**
     * @brief Limpia los juegos cerrados.
     */
    void clean_closed_games();


    /**
     * @brief Asigna un id de jugador.
     * @param game_id El id del juego al que se va a unir el cliente.
     * @param player_id El id de jugador asignado.
     */
    void set_player_id(u_int32_t game_id, u_int16_t &player_id);


    /**
     * @brief Cierra y limpia los juegos.
     */
    void close_and_clean_games();

    /**
     * @brief Cierra y limpia los clientes.
     */
    void close_and_clean_clients();
};

#endif // TP_FINAL_LOBBY_H
