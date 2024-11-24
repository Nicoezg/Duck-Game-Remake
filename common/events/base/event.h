//
// Created by fran on 21/10/24.
//

#ifndef TALLER_TP_EVENT_H
#define TALLER_TP_EVENT_H

#include "../items/bullet_dto.h"
#include "../items/crate.h"
#include "../items/explosion.h"
#include "../tile.h"
#include "common/events/connection/game_room.h"
#include "common/events/items/weapon_dto.h"
#include "common/events/items/item_spawn.h"
#include "common/events/player.h"
#include "event_type.h"
#include "common/events/connection/player_data.h"
#include <list>
#include <vector>

#define SIN_ASIGNAR 0
class Event {
private:
  EventType type;

public:
  explicit Event(EventType type);

  EventType get_type() const ;

  virtual bool is_connected() const;

  virtual std::list<PlayerData> get_players_data() const;

  virtual int get_game_code() const;

  virtual int get_position_x() const;
  virtual int get_position_y() const;

  virtual int get_player_id_1() const;
  virtual int get_player_id_2() const;

  virtual std::list<PlayerDTO> get_players() const;

  virtual std::list<BulletDTO> get_bullets() const;

  virtual std::list<CrateDTO> get_crates() const;

  virtual std::list<ItemSpawnDTO> get_item_spawns() const;

  virtual std::list<ExplosionDTO> get_explosions() const;

  virtual int get_max_players() const;

  virtual int get_actual_players() const;

  virtual std::list<GameRoom> get_games() const;

  virtual GameRoom get_game_room() const;

  virtual std::list<Tile> get_platforms() const;

  virtual int get_background_id() const;

  virtual int get_width() const;

  virtual int get_length() const;

  virtual std::vector<std::string> get_names() const;

  virtual std::vector<int> get_scores() const;

  virtual std::string get_winner() const;

  virtual int get_score() const;

  virtual ~Event() = default;
};

#endif // TALLER_TP_EVENT_H
