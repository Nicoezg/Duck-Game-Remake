
target_sources(CLIENT
        PRIVATE
        # .cpp files
        client.cpp
        client_protocol.cpp

        PUBLIC
        # .h files
        client.h
        client_protocol.h
)
