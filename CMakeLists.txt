cmake_minimum_required(VERSION 3.30)
project(etl_engine)

set(CMAKE_CXX_STANDARD 20)

find_package(CURL REQUIRED)

add_executable(etl_engine src/main.cpp
        src/api_client.cpp
        src/api_client.h)

target_include_directories(etl_engine PRIVATE ${CURL_INCLUDE_DIRS})
target_link_libraries(etl_engine ${CURL_LIBRARIES})