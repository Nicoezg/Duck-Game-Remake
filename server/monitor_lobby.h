#ifndef TALLER_TP_MONITOR_LOBBY_H
#define TALLER_TP_MONITOR_LOBBY_H

#include "server/game.h"
#include "server/lobby.h"
#include <atomic>
#include <list>
#include <map>
#include <memory>
#include <mutex>

class MonitorLobby {
private:
  std::mutex mtx;
  MonitorGames games;
  std::list<std::unique_ptr<Lobby>> clients;

public:
  MonitorLobby();

  void close();

  /**
   * @brief Agrega un cliente al lobby.
   * @param client El cliente a agregar.
   */
  void add_client(Socket &&client);

  /**
   * @brief Verifica si un cliente está cerrado y lo elimina.
   */
  void clean_closed_clients();

  /**
   * @brief Cierra y limpia los clientes.
   */
  void close_and_clean_clients();
};

#endif // TALLER_TP_MONITOR_LOBBY_H
