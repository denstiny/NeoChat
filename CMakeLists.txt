cmake_minimum_required(VERSION 3.2)

project(NeoChatCXX
  VERSION 1.0
  LANGUAGES CXX C
)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


if (NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug)
endif()

add_subdirectory(3rdpackages/B-tree)
add_subdirectory(3rdpackages/Json)
# add_subdirectory(client)
add_subdirectory(server)
add_subdirectory(NeoChatClient)
