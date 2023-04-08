cmake_minimum_required(VERSION 3.2)

project(NeoChatCXX
  VERSION 1.0
  LANGUAGES CXX C
)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CONFIGPATH "/etc/neochat/default.conf" CACHE STRING "confpath")

if (NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug)
endif()

add_subdirectory(client)
add_subdirectory(server)
