target_sources(CLIENT
    PRIVATE
    # .cpp files
    main.cpp
    client.cpp
    client_protocol.cpp
    graphic/action_handler.cpp
    graphic/duck.cpp
    graphic/game.cpp
    PUBLIC
    client.h
    client_protocol.h
    graphic/action_handler.h
    graphic/duck.h
    graphic/game.h
    # .h files
    )
