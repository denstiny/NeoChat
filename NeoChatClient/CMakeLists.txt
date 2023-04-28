cmake_minimum_required(VERSION 3.16)

project(NeoChatClient VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.4 REQUIRED COMPONENTS Quick Multimedia)

qt_standard_project_setup()

qt_add_executable(appNeoChatClient
  main.cpp clientnetwork.cpp clientnetwork.h
)

qt_add_qml_module(appNeoChatClient
    URI NeoChatClient
    VERSION 1.0
    QML_FILES Main.qml LoginWindow.qml MessageWindow.qml ChatListMenu.qml ChatWindow.qml LeftMenu.qml Leftmenubutton.qml NeoChat.qml
    QML_FILES ${QMLFILES}
)

set(RESOURCES_PATH "${CMAKE_CURRENT_SOURCE_DIR}/res/")

add_definitions(-DRESOURCES="${RESOURCES_PATH}")

set_target_properties(appNeoChatClient PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appNeoChatClient
    PRIVATE Qt6::Quick
)

install(TARGETS appNeoChatClient
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
