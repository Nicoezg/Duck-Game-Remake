cmake_minimum_required(VERSION 3.13)

if (POLICY CMP0135)
    cmake_policy(SET CMP0135 NEW)
endif()

if (NOT DEFINED CMAKE_CXX_STANDARD)
    set(CMAKE_CXX_STANDARD 20)
    add_definitions(-D_POSIX_C_SOURCE=200809L)
endif()

# strongly encouraged to enable this globally to avoid conflicts between
# -Wpedantic being enabled and -std=c++20 and -std=gnu++20 for example
# when compiling with PCH enabled
set(CMAKE_CXX_EXTENSIONS OFF)

project(taller_tp
        VERSION 1.0
        HOMEPAGE_URL "https://github.com/URL-HERE"
        LANGUAGES CXX
)

option(TESTS "Enable / disable tests." ON)
option(CLIENT "Enable / disable client program." ON)
option(SERVER "Enable / disable server program." ON)
option(EDITOR "Enable / disable editor program." ON)
option(TALLER_MAKE_WARNINGS_AS_ERRORS "Enable / disable warnings as errors." ON)

message(CMAKE_CXX_COMPILER_ID="${CMAKE_CXX_COMPILER_ID}")

# Define target: lib common between client, server and editor programs
add_library(COMMON STATIC
        common/actions/join.cpp
        common/actions/join.h
        client/client_protocol.cpp
        client/client_protocol.h
        common/connection/reader.h
        common/connection/sender.h
        common/connection/connection.h
        common/game_mode.h
        common/actions/move.cpp
        common/actions/move.h)

# add the source files that make the lib
add_subdirectory(common/)

# set compiler warnings to the targets
include(cmake/CompilerWarnings.cmake)
set_project_warnings(COMMON ${TALLER_MAKE_WARNINGS_AS_ERRORS} FALSE)

# Say where the headers will be found required by library target
# Make this PUBLIC so any dependant linking lib will inherit this
# location (so our dependants will not have to explicitly request this)
target_include_directories(COMMON PUBLIC .)

# Install libSDL2pp (for client or editor)
if(CLIENT OR EDITOR)
    include(FetchContent)
    FetchContent_Declare(
            libSDL2pp
            URL https://github.com/libSDL2pp/libSDL2pp/archive/cc198c9a5657048bee67ece82de620b2d5661084.zip
    )

    # set up SDL2pp library
    set(SDL2PP_WITH_IMAGE YES)
    set(SDL2PP_WITH_TTF YES)
    set(SDL2PP_WITH_MIXER YES)

    FetchContent_MakeAvailable(libSDL2pp)
endif()

# Program section
# ---------------
if(CLIENT)
    add_executable(CLIENT
            common/events/event.cpp
            common/events/event.h
            common/events/event_type.h
            common/events/game_creation.cpp
            common/events/game_creation.h
            common/events/game_join.cpp
            common/events/game_join.h
            common/protocol/actions/actions_protocol.cpp
            common/protocol/actions/actions_protocol.h
            common/protocol/events/events_protocol.cpp
            common/protocol/events/events_protocol.h
            common/events/broadcast.cpp
            common/events/broadcast.h
            common/events/player.cpp
            common/events/player.h
            client/printer.cpp
            client/printer.h)

    # Make them depend on COMMON lib
    add_dependencies(CLIENT COMMON SDL2pp::SDL2pp)

    # Add source files and enable warnings
    add_subdirectory(client)

    set_project_warnings(CLIENT ${TALLER_MAKE_WARNINGS_AS_ERRORS} FALSE)

    # add libSDL2pp's headers
    target_include_directories(CLIENT PRIVATE ${libSDL2pp_SOURCE_DIR})

    # Link the COMMON lib target
    target_link_libraries(CLIENT COMMON SDL2pp::SDL2pp)
endif()

if(SERVER)
    add_executable(SERVER
            server/server_protocol.cpp
            server/server_protocol.h
    )

    # Make them depend on common lib
    add_dependencies(SERVER COMMON)

    # Add source files and enable warnings
    add_subdirectory(server)

    set_project_warnings(SERVER ${TALLER_MAKE_WARNINGS_AS_ERRORS} FALSE)

    # Link the common lib target
    target_link_libraries(SERVER COMMON)
endif()

if(EDITOR)
    add_executable(EDITOR)

    # Make them depend on common lib
    add_dependencies(EDITOR COMMON SDL2pp::SDL2pp)

    # Add source files and enable warnings
    add_subdirectory(editor)

    set_project_warnings(EDITOR ${TALLER_MAKE_WARNINGS_AS_ERRORS} FALSE)

    # add libSDL2pp's headers
    target_include_directories(EDITOR PRIVATE ${libSDL2pp_SOURCE_DIR})

    # Link the common lib target
    target_link_libraries(EDITOR COMMON SDL2pp::SDL2pp)
endif()


# Testing section
# ---------------

if(TESTS)
    # Let's use google test
    include(FetchContent)
    FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
    )

    # For Windows: Prevent overriding the parent project's compiler/linker settings
    # (borrowed from https://google.github.io/googletest/quickstart-cmake.html)
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)
    include(GoogleTest)

    # target for testing
    add_executable(TESTS)

    # HEY!! TODO XXX: I'm assuming that the code under testing is in common
    # Change this if you have to.
    add_dependencies(TESTS COMMON)

    # Say where to find the xoz headers
    target_include_directories(TESTS PUBLIC .)

    # Add the source files to the TESTS target
    add_subdirectory(tests/)

    # Set the compiler warnings to the tests target (but be a little lesser strict)
    set_project_warnings(TESTS ${TALLER_MAKE_WARNINGS_AS_ERRORS} TRUE)

    # Say where googletest headers can be found
    target_include_directories(TESTS
        PUBLIC
        ${gtest_SOURCE_DIR}/include
        ${gmock_SOURCE_DIR}/include
        )

    # HEY!! TODO XXX: I'm assuming that the code under testing is in common
    # Change this if you have to.
    target_link_libraries(TESTS
        COMMON
        GTest::gtest_main
    )
endif()
