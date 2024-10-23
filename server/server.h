#ifndef TALLER_TP_SERVER_H
#define TALLER_TP_SERVER_H

#include "monitor_lobby.h"
#include "common/thread.h"

class Server : public Thread {
private:
  Socket socket;
  MonitorLobby lobby;
  std::atomic<bool> is_running;

public:
  explicit Server(const char *service_name);

  /**
   * @brief Corre el servidor.
   *
   * Inicia el juego y acepta conexiones de clientes suscribiendolos al juego.
   * Al finalizar, libera los recursos utilizados.
   * @see common_game.h
   */
  virtual void run() override;

  /**
   * @brief Cierra el servidor.
   *
   * Envia el mensaje de cierre al socket aceptador y al juego.
   */
  void close();
};

#endif // TALLER_TP_SERVER_H
