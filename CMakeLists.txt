cmake_minimum_required(VERSION 3.0)

SET_PROPERTY(GLOBAL PROPERTY TARGET_SUPPORTS_SHARED_LIBS "TRUE")

find_package(sdbus-c++ REQUIRED)

project(dbusExample VERSION 1.0.0 LANGUAGES C CXX)

add_executable(opener opener.cpp)
add_executable(server server.cpp)
add_executable(registrator registrator.cpp)

add_subdirectory(services)

target_link_libraries(opener PRIVATE SDBusCpp::sdbus-c++)
target_link_libraries(server PRIVATE SDBusCpp::sdbus-c++)
target_link_libraries(registrator PRIVATE SDBusCpp::sdbus-c++)

set_property(TARGET opener PROPERTY CXX_STANDARD 17)
set_property(TARGET server PROPERTY CXX_STANDARD 17)
set_property(TARGET registrator PROPERTY CXX_STANDARD 17)