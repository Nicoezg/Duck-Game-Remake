#include "common/socket/liberror.h"
#include "server/server.h"

#define ARGUMENTO_PUERTO 1
#define EXIT_CODE 'q'

int main(int argc, const char *argv[]) try {

  // Verifico que se haya pasado como argumento el puerto
  if (argc != 2) {
    throw std::runtime_error("invalid arguments quantity");
  }

  // inicia el hilo del servidor
  Server server(argv[ARGUMENTO_PUERTO]);
  server.start();

  // Espera a que el usuario presione 'q' para cerrar el servidor
  char exit;
  std::cin.get(exit);
  while (exit != EXIT_CODE) {
    std::cin.get(exit);
  }

  // Cierra el servidor
  server.close();
  server.join();

  return 0;
} catch (const LibError &e) {
  std::cout << "Critical error: " << e.what() << std::endl;
  return 1;
} catch (const std::exception &e) {
  return 1;
} catch (...) {
  return 1;
}
