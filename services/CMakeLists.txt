cmake_minimum_required(VERSION 3.0)

find_package(sdbus-c++ REQUIRED)

add_executable(Citius service1.cpp)
add_executable(Altius service2.cpp)
add_executable(Fortius service3.cpp)

target_link_libraries(Citius PRIVATE SDBusCpp::sdbus-c++)
target_link_libraries(Altius PRIVATE SDBusCpp::sdbus-c++)
target_link_libraries(Fortius PRIVATE SDBusCpp::sdbus-c++)

set_property(TARGET Citius PROPERTY CXX_STANDARD 17)
set_property(TARGET Altius PROPERTY CXX_STANDARD 17)
set_property(TARGET Fortius PROPERTY CXX_STANDARD 17)