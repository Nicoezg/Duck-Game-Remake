target_sources(CLIENT
    PRIVATE
    # .cpp files
    action_handler.cpp
    duck.cpp
    game.cpp
    animation_movement.cpp
    sound.cpp
        updater_game.cpp
    
    PUBLIC
    action_handler.h
    duck.h
    game.h
    animation_movement.h
    sound.h
        updater_game.h
    # .h files
    )
