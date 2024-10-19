target_sources(SERVER
    PRIVATE
    # .cpp files
    main.cpp
        game.cpp
        lobby.cpp
        lobby_client.cpp
        notifier.cpp
        server.cpp

    PUBLIC
    # .h files
        game.h
        lobby.h
        lobby_client.h
        notifier.h
        server.h
    )
