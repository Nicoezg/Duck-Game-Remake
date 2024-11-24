#ifndef TALLER_TP_MONITOR_GAMES_H
#define TALLER_TP_MONITOR_GAMES_H

#include "game.h"
#include <map>
#include <memory>
#include <mutex>

class MonitorGames {
private:
    std::mutex mtx;
    std::map<int, std::unique_ptr<Game>> games;
    int last_game_id;

public:
    MonitorGames();

    /**
     * @brief Crea un nuevo juego y lo agrega al lobby.
     * @return El player_id del juego creado.
     */
    int create_game(std::string game_name, int max_players);

    /**
     * @brief Verifica si un juego existe.
     * @param game_id El player_id del juego a verificar.
     * @return True si el juego existe, false en caso contrario.
     */
    bool game_exists(int game_id);

    /**
     * @brief Limpia los juegos cerrados.
     */
    void clean_closed_games();

    /**
     * @brief Asigna un player_id de jugador.
     * @param game_id El player_id del juego al que se va a unir el cliente.
     * @param player_id El player_id de jugador asignado.
     */
    int get_player_id(int game_id, int new_players, std::string player_name);

    /**
     * @brief Agrega un cliente a un juego.
     * @param game_id El player_id del juego al que se va a unir el cliente.
     * @param client El cliente a agregar.
     */
    void add_to_game(int game_id, Socket &&client);

    /**
     * @brief Cierra y limpia los juegos.
     */
    void close_and_clean_games();

    GameRoom get_game_room(int& game_code);

    std::list<GameRoom> get_not_started_games();

    std::list<PlayerData> get_players_data(int game_code);
};

#endif // TALLER_TP_MONITOR_GAMES_H
