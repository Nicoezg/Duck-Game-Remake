qt6_wrap_ui(UI_HEADERS mainwindow.ui)
qt6_add_resources(RESOURCES resources.qrc)

target_include_directories(CLIENT
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)


target_sources(CLIENT
        PRIVATE
        # .cpp files
        mainwindow.cpp
        ../main.cpp

        PUBLIC
        # .h files
        mainwindow.h

        mainwindow.ui

        resources.qrc
)
