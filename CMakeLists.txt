cmake_minimum_required(VERSION 3.31)
project(Memorial)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(3rd_party/OpenXLSX)

# Поиск библиотек
find_library(MONGOCXX mongocxx)
find_library(BSONCXX bsoncxx)
find_library(MONGOC_C mongoc2 libmongoc2
        PATHS /usr/lib /usr/local/lib /usr/lib/x86_64-linux-gnu
        REQUIRED
        NO_DEFAULT_PATH
)
find_library(BSON_C bson2 libbson2
        PATHS /usr/lib /usr/local/lib /usr/lib/x86_64-linux-gnu
        REQUIRED
        NO_DEFAULT_PATH
)

if (NOT MONGOC_C OR NOT BSON_C)
    message(FATAL_ERROR "libmongoc2 или libbson2 не найдены")
endif()

# Проверка найденных путей
message(STATUS "MONGOCXX: ${MONGOCXX}")
message(STATUS "BSONCXX: ${BSONCXX}")
message(STATUS "MONGOC_C: ${MONGOC_C}")
message(STATUS "BSON_C: ${BSON_C}")

# Подключение заголовков
set(MONGOCXX_INCLUDE_DIRS "/usr/local/include/mongocxx/v_noabi")
set(BSONCXX_INCLUDE_DIRS "/usr/local/include/bsoncxx/v_noabi")

add_executable(Memorial
        main.cpp
        include/memorial/cxxopts/cxxopts.h
        )
target_include_directories(Memorial PRIVATE
        include
        ${MONGOCXX_INCLUDE_DIRS}
        ${BSONCXX_INCLUDE_DIRS}
)

# Линковка ВСЕХ необходимых библиотек
target_link_libraries(Memorial
        OpenXLSX::OpenXLSX
        ${MONGOCXX}
        ${BSONCXX}
        ${MONGOC_C}
        ${BSON_C}
)


include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/v1.17.0.zip
)


FetchContent_MakeAvailable(googletest)

if(WIN32)
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
endif()

add_executable(tests_google tests/google_tests.cpp)
target_include_directories(tests_google PUBLIC
        include
        ${MONGOCXX_INCLUDE_DIRS}
        ${BSONCXX_INCLUDE_DIRS}
)
target_link_libraries(tests_google
        gtest
        gtest_main
        OpenXLSX::OpenXLSX
        ${MONGOCXX}
        ${BSONCXX}
        ${MONGOC_C}
        ${BSON_C}
)
target_compile_definitions(tests_google PUBLIC BUILD_GOOGLE_TEST)
enable_testing()

#add_test(NAME UserLoggerTests COMMAND tests_google)