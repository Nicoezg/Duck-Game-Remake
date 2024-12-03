qt6_wrap_ui(UI_HEADERS editor.ui)
qt6_add_resources(RESOURCES resources.qrc)

target_include_directories(EDITOR
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)


target_sources(EDITOR
        PRIVATE
        # .cpp files
        editor.cpp
        mainwindow.cpp
        main.cpp
        yamlhandler.cpp

        PUBLIC
        # .h files
        editor.h
        editor.ui
        mainwindow.h
        mainwindow.ui
        yamlhandler.h

        resources.qrc
)
