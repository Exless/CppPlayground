cmake_minimum_required(VERSION 3.29)
project(JsonParser)


# clangd integration
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)



# package definitions
find_package(easyloggingpp)
find_package(CURL)
find_package(fmt)
find_package(nlohmann_json)
find_package(GTest)
find_package(fruit)

set(CMAKE_CXX_STANDARD 20)

# main program
add_executable(JsonParser src/main.cpp
        src/Vertex.cpp
        src/Vertex.h)

target_link_libraries(JsonParser
        easyloggingpp::easyloggingpp
        CURL::libcurl
        fmt::fmt
        nlohmann_json::nlohmann_json
        fruit::fruit
)

# tests
add_executable(Tests
        test/advanced_tests.cpp
        test/tests.cpp
)
target_link_libraries(Tests
        fmt::fmt
        gtest::gtest
        easyloggingpp::easyloggingpp
        fruit::fruit
)


