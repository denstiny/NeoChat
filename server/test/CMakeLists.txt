set(BINNAME test)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
find_package(GTest REQUIRED)

pkg_check_modules(mariadb REQUIRED IMPORTED_TARGET libmariadb)

add_executable(${BINNAME}
  main.cpp
  test_mysql.cpp
  test_pwd.cpp
  test_tcpserver.cpp
  test_parseHeader.cpp
  test_thread_pool.cpp
  ${source_src}
)

target_link_libraries(${BINNAME}
  ${GTEST_LIBRARIES}
  PkgConfig::mariadb
)

target_include_directories(${BINNAME} PRIVATE
  ${GTest_INCLUDE_DIRS}
  ${CMAKE_CURRENT_LIST_DIR}/../src/modules
)

add_test(NAME ${BIN_NAME} COMMAND ${BIN_NAME})
