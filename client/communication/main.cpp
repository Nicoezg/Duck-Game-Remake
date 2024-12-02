//
// Created by cafrada on 22/04/23.
//

// Using SDL, SDL_image, standard IO, and strings
#include "graphic/game.h"
#include <iostream>

#include "../../common/socket/liberror.h"
#include "client.h"

#define EXIT_CODE '|'

int main(int argc, const char *argv[]) try {
  if (argc != 3) {
    throw std::runtime_error("invalid arguments quantity");
  }
  Client client(argv[1], argv[2]);
  client.run();
  return 0;
} catch (const std::exception &e) {
  std::cout << "Critical error: " << e.what() << std::endl;
  return -1;
} catch (...) {
  std::cout << "Unknown critical error." << std::endl;
  return -1;
}
