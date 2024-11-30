cmake_minimum_required(VERSION 3.10)

project(Assignment_1)

# Set the C++ standard to 17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include directories for headers
include_directories(
    sender/include
    receiver/include
    lib/gtest
    lib
)

# Google Test library paths
set(GTEST_LIBS
    ${CMAKE_SOURCE_DIR}/lib/libgtest.a
    ${CMAKE_SOURCE_DIR}/lib/libgtest_main.a
)

# Define the sender and receiver executables
add_executable(sender sender/src/sender.cpp)
add_executable(receiver receiver/src/receiver.cpp)

# Define the test executables
add_executable(test_sender sender/tests/test_sender.cpp sender/src/sender.cpp)
target_compile_definitions(test_sender PRIVATE UNIT_TEST)
target_link_libraries(test_sender ${GTEST_LIBS} pthread)

add_executable(test_receiver receiver/tests/test_receiver.cpp receiver/src/receiver.cpp sender/src/sender.cpp)
target_compile_definitions(test_receiver PRIVATE UNIT_TEST)
target_link_libraries(test_receiver ${GTEST_LIBS} pthread)

# Include directories for test executables
target_include_directories(test_sender PRIVATE sender/include lib/gtest lib)
target_include_directories(test_receiver PRIVATE receiver/include sender/include lib/gtest lib)

# Set the output directory for executables
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build)