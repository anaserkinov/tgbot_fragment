cmake_minimum_required(VERSION 3.10)

project(Test)

set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

add_executable(Main ${SOURCE_DIR}/Test.cpp)

target_link_libraries(Main 
tgbot_fragment)