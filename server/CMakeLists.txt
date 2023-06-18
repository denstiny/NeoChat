######################################################################
# @author      : aero (2254228017@qq.com)
# @file        : CMakeLists
# @created     : 星期六 4月 01, 2023 08:48:32 CST
######################################################################

set(BINNAME neochatcxxserver)

set(CONFIGPATH "${CMAKE_CURRENT_SOURCE_DIR}/config/server" CACHE STRING "confpath")
message(${CONFIGPATH})
add_definitions(-DCONFIGPATH="${CONFIGPATH}")

find_package(PkgConfig)

pkg_check_modules(MYSQL REQUIRED IMPORTED_TARGET mysqlclient)

include_directories(src/modules)
# add google btree source
file(GLOB_RECURSE source_src src/*.cpp src/*.hpp)
list(REMOVE_ITEM source_src ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp)
include_directories(${MYSQL_INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../3rdpackages/)
link_directories(${MYSQL_LIBRARY_DIRS})
add_executable(${BINNAME} src/main.cpp ${source_src})

target_include_directories(${BINNAME} PRIVATE ${MYSQL_INCLUDE_DIRS})

target_link_libraries(${BINNAME}
  #PkgConfig::mysqlclient
  ${MYSQL_LIBRARIES}
  cppbtree
  cppjson
  )

# # run test task
 # add_executable(test_mysql test/test_mysql.cpp ${source_src})
 # target_link_libraries(test_mysql mysqlclient)
 # add_test(NAME test_mysql COMMAND $<TARGET_FILE:test_mysql>)
 # add_custom_command(TARGET test_mysql POST_BUILD COMMAND cd ${CMAKE_CURRENT_SOURCE_DIR}/build && ctest -R test_mysql --output-on-failure)
 # 
 # #run test thread pool
 # add_executable(test_thread_pool test/test_thread_pool.cpp ./src/modules/tasks/tasks.cpp ./src/modules/tasks/tasks.hpp)
 # add_test(NAME test_thread_pool COMMAND $<TARGET_FILE:test_thread_pool>)
 # add_custom_command(TARGET test_thread_pool POST_BUILD COMMAND cd ${CMAKE_CURRENT_SOURCE_DIR}/build && ctest -R test_thread_pool --output-on-failure)
 # enable_testing()
 # add_definitions(-DCONFIGPATH="${CMAKE_CURRENT_SOURCE_DIR}/config/server")
 # 
 # add_executable(test_parser test/test_parseHeader.cpp ./src/modules/Message/MessageProcessor.hpp ./src/modules/Message/MessageProcessor.cpp)
