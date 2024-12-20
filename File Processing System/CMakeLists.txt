cmake_minimum_required(VERSION 3.10)

project(Assignment_3)

# Set the C++ standard to 17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include directories for headers
include_directories(
    sender/include
    receiver/include
    lib/gtest
    lib
    common/include
    lib/spdlog
)

# Google Test library paths
set(GTEST_LIBS
    ${CMAKE_SOURCE_DIR}/lib/libgtest.a
    ${CMAKE_SOURCE_DIR}/lib/libgtest_main.a
)

# SPDlog library path
set(SPDLOG_LIB ${CMAKE_SOURCE_DIR}/lib/libspdlog.a)

# Define the sender and receiver executables
add_executable(sender sender/src/sender.cpp common/src/config.cpp)
target_link_libraries(sender ${SPDLOG_LIB} logger)

add_executable(receiver receiver/src/receiver.cpp common/src/config.cpp)
target_link_libraries(receiver ${SPDLOG_LIB} logger)

# Define the test executables
add_executable(test_sender sender/tests/test_sender.cpp sender/src/sender.cpp common/src/config.cpp)
target_compile_definitions(test_sender PRIVATE UNIT_TEST)
target_link_libraries(test_sender ${GTEST_LIBS} pthread ${SPDLOG_LIB} logger)

add_executable(test_receiver receiver/tests/test_receiver.cpp receiver/src/receiver.cpp sender/src/sender.cpp common/src/config.cpp)
target_compile_definitions(test_receiver PRIVATE UNIT_TEST)
target_link_libraries(test_receiver ${GTEST_LIBS} pthread ${SPDLOG_LIB} logger)

# Add logger files
add_library(logger common/src/logger.cpp)

# Copy configuration files to the build directory
file(GLOB CONFIG_FILES "${CMAKE_SOURCE_DIR}/config/*")
foreach(CONFIG_FILE ${CONFIG_FILES})
    configure_file(${CONFIG_FILE} ${CMAKE_BINARY_DIR}/config/ COPYONLY)
endforeach()

# Set the output directory for executables
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build)