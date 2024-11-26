target_sources(SERVER
    PRIVATE
    # .cpp files
        main.cpp
        game.cpp
        monitor_lobby.cpp
        monitor_games.cpp
        lobby.cpp
        notifier.cpp
        maploader.cpp
        server.cpp
        server_protocol.cpp

        logic/game_map.cpp
        logic/box.cpp
        logic/duck.cpp
        logic/explosion.cpp
        logic/itemspawn.cpp

        logic/weapons/weapon.cpp
        logic/weapons/shotgun.cpp
        logic/weapons/ak47.cpp
        logic/weapons/laser_rifle.cpp
        logic/weapons/pewpewlaser.cpp
        logic/weapons/cowboy.cpp
        logic/weapons/duelos.cpp
        logic/weapons/magnum.cpp
        logic/weapons/sniper.cpp
        logic/weapons/grenade.cpp
        logic/weapons/no_weapon.cpp
        logic/weapons/banana.cpp
        logic/weapons/no_weapon.h
        logic/bullets/bullet.cpp
        logic/throwables/throwable.cpp
        logic/throwables/grenade.cpp
        logic/throwables/banana.cpp

        logic/collisions/collision_radius.cpp
        logic/collisions/collision_radius.h
        logic/collisions/coordinate.cpp
        logic/collisions/coordinate.h
        logic/collisions/position.cpp
        logic/collisions/position.h


        configs/configurations.cpp
        configs/bullet_config.cpp
        configs/duck_config.cpp

    PUBLIC
    # .h files
        game.h
        monitor_lobby.h
        monitor_lobby.h
        lobby.h
        notifier.h
        maploader.h
        server.h
        server_protocol.h

        logic/game_map.h
        logic/duck.h
        logic/box.h
        logic/explosion.h
        logic/itemspawn.h

        logic/weapons/weapon.h
        logic/weapons/pewpewlaser.h
        logic/weapons/shotgun.h
        logic/weapons/ak47.h
        logic/weapons/cowboy.h
        logic/weapons/duelos.h
        logic/weapons/magnum.h
        logic/weapons/sniper.h
        logic/weapons/grenade.h
        logic/weapons/banana.h
        logic/bullets/bullet.h
        logic/throwables/throwable.h
        logic/throwables/grenade.h
        logic/throwables/banana.h


        configs/configurations.h
        configs/bullet_config.h
        configs/duck_config.h
    )

find_package(yaml-cpp REQUIRED)
target_link_libraries(SERVER yaml-cpp)
