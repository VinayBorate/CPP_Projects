#include <gtest/gtest.h>
#include <filesystem>
#include <fstream>
#include <iostream>
#include "../include/receiver.h"
#include "../../sender/include/sender.h"

namespace fs = std::filesystem;

const std::string BUFFER_DIR = "./VijayBuffer";

////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////UNIT TESTING //////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////

// Test file reading
TEST(ReceiverTest, ReadFileTest) {
    std::cout << "//////////////////////////////////Unit Testing /////////////////////////////////////";
    std::cout << std::endl << std::endl;
    create_directory_if_not_exists_by_receiver(BUFFER_DIR);
    std::string file_path = BUFFER_DIR + "/test_file.txt";
    create_file(file_path, 10);  // Create a 10 MB file
    long long read_time_ms = 0;
    auto file_content = read_file(file_path, read_time_ms);
    ASSERT_FALSE(file_content.empty());
    std::cout << std::endl << std::endl;
    fs::remove(file_path);  // Clean up
}

// Test file deletion
TEST(ReceiverTest, DeleteFileTest) {
    std::cout << std::endl;
    create_directory_if_not_exists_by_receiver(BUFFER_DIR);
    std::string file_path = BUFFER_DIR + "/test_file.txt";
    create_file(file_path, 10);  // Create a 10 MB file
    long long delete_time_ms = 0;
    delete_file(file_path, delete_time_ms);
    ASSERT_FALSE(fs::exists(file_path));
    std::cout << std::endl << std::endl;
}

// Test file processing (read + delete)
TEST(ReceiverTest, ProcessFileTest) {
    std::cout << std::endl;
    create_directory_if_not_exists_by_receiver(BUFFER_DIR);
    std::string file_path = BUFFER_DIR + "/test_file.txt";
    create_file(file_path, 10);  // Create a 10 MB file
    process_file(file_path);
    ASSERT_FALSE(fs::exists(file_path));
    std::cout << std::endl << std::endl;
}

// Test directory creation
TEST(ReceiverTest, DirectoryCreationTest) {
    std::cout << std::endl;
    std::string test_dir = "./TestBuffer";
    if (fs::exists(test_dir)) {
        fs::remove_all(test_dir);
    }
    create_directory_if_not_exists_by_receiver(test_dir);
    ASSERT_TRUE(fs::exists(test_dir));
    fs::remove_all(test_dir);  // Clean up
    std::cout << std::endl << std::endl << std::endl;

    std::cout << "//////////////////////////////////Performance Testing ==> Starts /////////////////////////////////////";
    std::cout << std::endl;
}

////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////Performance Testing /////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////

// Performance test for file reading
TEST(ReceiverPerformanceTest, FileReadingTime) {
    std::cout << std::endl;
    create_directory_if_not_exists_by_receiver(BUFFER_DIR);
    std::string file_path = BUFFER_DIR + "/perf_test_file.txt";
    create_file(file_path, 100);  // Create a 100 MB file

    long long read_time_ms = 0;
    auto start_time = std::chrono::high_resolution_clock::now();
    auto file_content = read_file(file_path, read_time_ms);
    auto end_time = std::chrono::high_resolution_clock::now();

    long long duration_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();
    std::cout << "Time taken to read 100 MB file: " << duration_ms << " ms" << std::endl;

    fs::remove(file_path);  // Clean up

    // Assert that the file reading time is within an acceptable range
    ASSERT_LT(duration_ms, 500);  // Example threshold

    std::cout << std::endl << std::endl;
}

// Performance test for file deletion
TEST(ReceiverPerformanceTest, FileDeletionTime) {
    std::cout << std::endl;
    create_directory_if_not_exists_by_receiver(BUFFER_DIR);
    std::string file_path = BUFFER_DIR + "/perf_test_file.txt";
    create_file(file_path, 100);  // Create a 100 MB file

    long long delete_time_ms = 0;
    auto start_time = std::chrono::high_resolution_clock::now();
    delete_file(file_path, delete_time_ms);
    auto end_time = std::chrono::high_resolution_clock::now();

    long long duration_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();
    std::cout << "Time taken to delete 100 MB file: " << duration_ms << " ms" << std::endl;

    // Assert that the file deletion time is within an acceptable range
    ASSERT_LT(duration_ms, 100);  // Example threshold
    std::cout << std::endl << std::endl;
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
