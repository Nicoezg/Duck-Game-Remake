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

        actions/action.cpp
        actions/create.cpp
        actions/join.cpp

        events/event.cpp
        events/game_creation.cpp
        events/game_join.cpp

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

        actions/action.h
        actions/join.h
        actions/action_macros.h
        actions/create.h

        events/event.h
        events/game_creation.h
        events/game_join.h

        game_mode.h

    )
