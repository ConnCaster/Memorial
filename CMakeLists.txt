cmake_minimum_required(VERSION 3.31)
project(Memorial)

set(CMAKE_CXX_STANDARD 20)

#set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/output)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/output)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/output)

add_subdirectory(3rd_party/OpenXLSX)
add_executable(Memorial main.cpp)
target_include_directories(Memorial PRIVATE inludes)

target_link_libraries(Memorial OpenXLSX::OpenXLSX)