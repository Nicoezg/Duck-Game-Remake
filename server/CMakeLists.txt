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
        logic/configurations.cpp

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
        logic/configurations.h
        logic/weapons/weapon.h
    )

find_package(yaml-cpp REQUIRED)
target_link_libraries(SERVER yaml-cpp)
