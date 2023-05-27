cmake_minimum_required(VERSION 3.10)

project(TGBot_Fragment)

set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

add_library(tgbot_fragment STATIC
${SOURCE_DIR}/Fragment.cpp
)

target_link_libraries(
    tgbot_fragment 
    sqlite
)

include_directories(bito 
src/include
src/core
src/db
src/net
src/scheme
)

set(NATIVE_LIB "bitocore")
# add_library(${NATIVE_LIB} SHARED

# )
# target_link_libraries(${NATIVE_LIB}
# bito
# )

add_executable(Main ${SOURCE_DIR}/main.cpp)

target_link_libraries(Main 
curl
bito)