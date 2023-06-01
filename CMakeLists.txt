cmake_minimum_required(VERSION 3.10)

project(TGBot_Fragment)

set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

add_library(tgbot_fragment STATIC
${SOURCE_DIR}/Fragment.cpp
${SOURCE_DIR}/FragmentManager.cpp
)

include_directories(
    tgbot_fragment
    "include"
)
add_subdirectory("tgbot-cpp")
target_link_libraries(tgbot_fragment PRIVATE TgBot)

target_include_directories(tgbot_fragment PUBLIC include)

add_subdirectory("test")