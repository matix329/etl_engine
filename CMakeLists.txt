cmake_minimum_required(VERSION 3.26)
project(etl_engine)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_TOOLCHAIN_FILE "/Users/matix329/.vcpkg-clion/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "Vcpkg toolchain file")

find_package(CURL REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)
include_directories(/Users/matix329/.vcpkg-clion/vcpkg/packages/nlohmann-json_arm64-osx/include)

find_package(valijson CONFIG REQUIRED)
include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(/Users/matix329/.vcpkg-clion/vcpkg/packages/nlohmann-json_arm64-osx/include)


add_executable(etl_engine
        src/main.cpp
        src/api_client.cpp
        src/json_parser.cpp
        src/json_valid.cpp
)

target_link_libraries(etl_engine PRIVATE
        CURL::libcurl
        nlohmann_json::nlohmann_json
        valijson
)
