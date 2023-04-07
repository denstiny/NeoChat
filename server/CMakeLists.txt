######################################################################
# @author      : aero (2254228017@qq.com)
# @file        : CMakeLists
# @created     : 星期六 4月 01, 2023 08:48:32 CST
######################################################################

cmake_minimum_required(VERSION 3.2)
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)
project(ChatServer CXX)
#set(CMAKE_CXX_COMPILER "g++")
set(CMAKE_BUILD_TYPE Debug)
include_directories(/usr/include/mysql)
# include_directories(/usr/local/include/mysql++)
include_directories("src/modules/")
include_directories(${MYSQL_INCLUDE_DIR})
# add google btree source
add_subdirectory(src/externa_module/B-tree)
file(GLOB_RECURSE source_src src/*.cpp src/*.hpp)
list(REMOVE_ITEM source_src ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp)
add_executable(${PROJECT_NAME} src/main.cpp ${source_src})
target_link_libraries(${PROJECT_NAME} mysqlclient)
# link google btree static link
target_link_libraries(${PROJECT_NAME} cppbtree)

# run test task
add_executable(test_mysql test/test_mysql.cpp ${source_src})
target_link_libraries(test_mysql mysqlclient)
add_test(NAME test_mysql COMMAND $<TARGET_FILE:test_mysql>)
add_custom_command(TARGET test_mysql POST_BUILD COMMAND cd ${CMAKE_CURRENT_SOURCE_DIR}/build && ctest -R test_mysql --output-on-failure)

#run test thread pool
add_executable(test_thread_pool test/test_thread_pool.cpp ./src/modules/tasks/tasks.cpp ./src/modules/tasks/tasks.hpp)
add_test(NAME test_thread_pool COMMAND $<TARGET_FILE:test_thread_pool>)
add_custom_command(TARGET test_thread_pool POST_BUILD COMMAND cd ${CMAKE_CURRENT_SOURCE_DIR}/build && ctest -R test_thread_pool --output-on-failure)
enable_testing()
add_definitions(-DCONFIGPATH="${CMAKE_CURRENT_SOURCE_DIR}/config/server")

add_executable(test_parser test/test_parseHeader.cpp ./src/modules/Message/MessageProcessor.hpp ./src/modules/Message/MessageProcessor.cpp)
