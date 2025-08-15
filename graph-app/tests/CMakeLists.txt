find_package(GTest REQUIRED)

enable_testing()

include_directories(${CMAKE_SOURCE_DIR}/include)
add_executable(graph_test graph_tests.cpp)

target_link_libraries(graph_test PRIVATE gtest::gtest nlohmann_json::nlohmann_json)

include(GoogleTest)
add_test(NAME GraphTest COMMAND graph_test)
