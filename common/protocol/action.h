#ifndef TP_2_ACTION_H
#define TP_2_ACTION_H

#include <string>
#include <cstdint>

class Action {
private:
  uint16_t id;
  std::string name;
  uint32_t game_code;

public:
  /**
   * Constructor para acciones de tipo "Leer".
   */
  Action(std::string name, std::string event_type);

  /**
   * Constructor para acciones de tipo "Atacar" y "Salir".
   * No se especifica la cantidad de enemigos vivos y muertos.
   */
  Action(uint16_t id, std::string name);
  explicit Action(std::string name);

  Action();

  std::string get_name() const;

  bool is_attack() const;

  bool is_broadcast() const;

  uint32_t get_game_code() const;

  std::string print_game_code() const;

  bool is_connect() const;

    std::string get_text() const;
};

#endif // TP_2_ACTION_H
