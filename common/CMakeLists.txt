target_sources(COMMON
    PRIVATE
    # .cpp files
    foo.cpp

        protocol/actions/actions_protocol.cpp
        protocol/events/events_protocol.cpp
        protocol/common/protocol.cpp
        protocol/common/encoder.cpp
        protocol/common/protocol_error.cpp
        socket/liberror.cpp
        socket/resolver.cpp
        socket/resolvererror.cpp
        socket/socket.cpp

        actions/base/action.cpp
        actions/connection/create.cpp
        actions/connection/join.cpp

        events/base/event.cpp
        events/connection/game_creation.cpp
        events/connection/game_join.cpp

        events/player.cpp
        events/broadcast.cpp

    PUBLIC
    # .h files
    foo.h
        connection/connection.h
        connection/reader.h
        connection/sender.h

        protocol/common/protocol.h
        protocol/common/encoder.h
        protocol/common/protocol_error.h
        protocol/actions/actions_protocol.h
        protocol/events/events_protocol.h

        socket/liberror.h
        socket/resolver.h
        socket/resolvererror.h
        socket/socket.h

        actions/base/action.h
        actions/connection/join.h
        actions/base/action_macros.h
        actions/connection/create.h

        events/base/event.h
        events/connection/game_creation.h
        events/connection/game_join.h

        game_mode.h

        events/player.h
        events/broadcast.h

    )
