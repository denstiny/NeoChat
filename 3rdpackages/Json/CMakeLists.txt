######################################################################
# @author      : aero (2254228017@qq.com)
# @file        : CMakeLists
# @created     : 星期五 4月 28, 2023 22:50:37 CST
######################################################################

cmake_minimum_required(VERSION 3.2)
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)
project(cppjson CXX)
set(CMAKE_CXX_STANDARD 11)

add_library(${PROJECT_NAME} json.hpp json_fwd.hpp)
set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)
