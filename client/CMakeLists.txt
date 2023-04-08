######################################################################
# @author      : aero (2254228017@qq.com)
# @file        : CMakeLists
# @created     : 星期日 4月 02, 2023 11:10:13 CST
######################################################################

cmake_minimum_required(VERSION 3.3)
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)
project(ChatClient CXX)

# set ui file search path
if(NOT CMAKE_BUILD_TYPE) 
  set(CMAKE_BUILD_TYPE Debug)
endif()
set(CMAKE_AUTOUIC_SEARCH_PATHS "${CMAKE_SOURCE_DIR}/src/modules/ui/")
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Core Network)
find_package(Qt${QT_VERSION_MAJOR} NAMES REQUIRED COMPONENTS Widgets Core Network)

file(GLOB_RECURSE source_src src/*hpp src/*.cpp)
file(GLOB_RECURSE UIS src/*.ui)
list(REMOVE_ITEM source_src ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp)
qt_add_resources(RESOURES src/modules/res/res.qrc)

include_directories("src/modules")
add_executable(${PROJECT_NAME} src/main.cpp ${source_src} ${RESOURES})

target_link_libraries(${PROJECT_NAME} PRIVATE 
  Qt${QT_VERSION_MAJOR}::Widgets
  Qt${QT_VERSION_MAJOR}::Network
  Qt${QT_VERSION_MAJOR}::Core
)
