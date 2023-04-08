######################################################################
# @author      : aero (2254228017@qq.com)
# @file        : CMakeLists
# @created     : 星期日 4月 02, 2023 11:10:13 CST
######################################################################

set(BINNAME ChatClient)

set(CMAKE_AUTOUIC_SEARCH_PATHS "${CMAKE_CURRENT_LIST_DIR}/src/modules/ui/")
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Core Network)
find_package(Qt${QT_VERSION_MAJOR} NAMES REQUIRED COMPONENTS Widgets Core Network)

file(GLOB_RECURSE source_src src/*hpp src/*.cpp)
set(UIRes
  ${CMAKE_CURRENT_LIST_DIR}/./src/modules/ui/MainWindow.ui
  ${CMAKE_CURRENT_LIST_DIR}/./src/modules/ui/LoginWidget.ui
  ${CMAKE_CURRENT_LIST_DIR}/./src/modules/ui/UserMenuWidget.ui
)

qt6_wrap_ui(UI_HEADERS ${UIRes})
qt_add_executable(${BINNAME}
  ${source_src}
  ${UI_HEADERS}
  ./src/modules/res/res.qrc)

target_include_directories(${BINNAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/src/modules
  ${CMAKE_CURRENT_LIST_DIR}/src
)

target_link_libraries(${BINNAME} PRIVATE
  Qt${QT_VERSION_MAJOR}::Widgets
  Qt${QT_VERSION_MAJOR}::Network
  Qt${QT_VERSION_MAJOR}::Core)
