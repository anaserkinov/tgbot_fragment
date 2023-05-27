cmake_minimum_required(VERSION 3.10)

project(TGBot_Fragment)

set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

#sqlite
add_library(sqlite STATIC ${SOURCE_DIR}/db/SQLite/sqlite3.c)
target_compile_options(sqlite PUBLIC -fno-strict-aliasing -Os)


add_library(bito STATIC
${SOURCE_DIR}/core/BTObject.cpp
${SOURCE_DIR}/core/BuffersStorage.cpp
${SOURCE_DIR}/core/ByteArray.cpp
${SOURCE_DIR}/core/FileLog.cpp
${SOURCE_DIR}/core/NativeByteBuffer.cpp

${SOURCE_DIR}/net/CURLManager.cpp
${SOURCE_DIR}/net/requests.cpp

${SOURCE_DIR}/db/SQLitePreparedStatement.cpp
${SOURCE_DIR}/db/SQLiteCursor.cpp
${SOURCE_DIR}/db/SQLiteDatabase.cpp
${SOURCE_DIR}/db/PreparedStatement.cpp
${SOURCE_DIR}/db/Cursor.cpp
${SOURCE_DIR}/db/Database.cpp

${SOURCE_DIR}/core/Base.cpp
${SOURCE_DIR}/core/Warehouse.cpp

)

target_link_libraries(
    bito 
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