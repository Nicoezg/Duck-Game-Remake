target_sources(SERVER
    PRIVATE
    # .cpp files
    main.cpp
        game.cpp
        monitor_lobby.cpp
        monitor_games.cpp
        lobby.cpp
        notifier.cpp
        server.cpp
        server_protocol.cpp
        logic/game_map.cpp
        logic/duck.cpp

    PUBLIC
    # .h files
        game.h
        monitor_lobby.h
        monitor_lobby.h
        lobby.h
        notifier.h
        server.h
        server_protocol.h
        logic/game_map.h
        logic/duck.h
    )
