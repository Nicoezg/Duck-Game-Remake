#ifndef TALLER_TP_MONITOR_GAMES_H
#define TALLER_TP_MONITOR_GAMES_H


#include <mutex>
#include <memory>
#include <map>
#include "game.h"

class MonitorGames {
private:
    std::mutex mtx;
    std::map<uint32_t , std::unique_ptr<Game>> games;
    int last_game_id;

public:

    MonitorGames();

    /**
     * @brief Crea un nuevo juego y lo agrega al lobby.
     * @return El player_id del juego creado.
     */
    int create_game();

    /**
     * @brief Verifica si un juego existe.
     * @param game_id El player_id del juego a verificar.
     * @return True si el juego existe, false en caso contrario.
     */
    bool game_exists(uint32_t game_id);

    /**
     * @brief Limpia los juegos cerrados.
     */
    void clean_closed_games();

    /**
     * @brief Asigna un player_id de jugador.
     * @param game_id El player_id del juego al que se va a unir el cliente.
     * @param player_id El player_id de jugador asignado.
     */
    uint16_t get_player_id(uint32_t game_id);

    /**
     * @brief Agrega un cliente a un juego.
     * @param game_id El player_id del juego al que se va a unir el cliente.
     * @param client El cliente a agregar.
     */
    void add_to_game(uint32_t game_id, Socket &&client);

    /**
     * @brief Cierra y limpia los juegos.
     */
    void close_and_clean_games();
};


#endif //TALLER_TP_MONITOR_GAMES_H
