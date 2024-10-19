//
// Created by fran on 20/05/24.
//

#ifndef TP_FINAL_LOBBY_CLIENT_H
#define TP_FINAL_LOBBY_CLIENT_H

class Lobby;

#include "common/protocol/protocol.h"
#include "common/socket/socket.h"
#include "common/thread.h"
#include <atomic>

const int SIN_CODIGO = 0;

class LobbyClient : public Thread {
private:
  Socket client;
  Protocol protocol;
  Lobby *lobby;
  std::atomic<bool> is_running;
  std::atomic<bool> is_connected;

public:
  explicit LobbyClient(Socket &&client, Lobby *lobby);
  void run() override;

  bool is_closed() const;

  void close();

    void game_setup(u_int32_t game_code);
};

#endif // TP_FINAL_LOBBY_CLIENT_H
