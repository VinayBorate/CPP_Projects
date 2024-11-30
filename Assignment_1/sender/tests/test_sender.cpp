#include <gtest/gtest.h>
#include <filesystem>
#include <fstream>
#include <iostream>
#include "../../sender/include/sender.h"

namespace fs = std::filesystem;
const std::string BUFFER_DIR = "./VijayBuffer";

////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////UNIT TESTING //////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////

// Test file generation limit
TEST(SenderTest, FileGenerationLimitTest) {
    std::cout << "//////////////////////////////////Unit Testing /////////////////////////////////////";
    std::cout << std::endl << std::endl;
    create_directory_if_not_exists_by_sender(BUFFER_DIR);
    sender(false);  // Disable user input prompt
    int file_count = 0;
    for (const auto& entry : fs::directory_iterator(BUFFER_DIR)) {
        if (entry.path().extension() == ".txt") {
            file_count++;
        }
    }
    ASSERT_EQ(file_count, 10);  // Checking for 10 files whether it can generate?
    std::cout << std::endl << std::endl;
}

// Test file creation
TEST(SenderTest, FileCreationTest) {
    std::cout << std::endl;
    create_directory_if_not_exists_by_sender(BUFFER_DIR);
    sender(false);  // Disable user input prompt
    const int FILE_SIZES_MB[] = {10, 50, 100, 150, 200};  // File sizes to create
    for (int i = 1; i <= 10; ++i) {
        std::string file_path = BUFFER_DIR + "/file_" + std::to_string(i) + ".txt";
        ASSERT_TRUE(fs::exists(file_path));
        size_t expected_size = FILE_SIZES_MB[(i - 1) % 5] * 1024 * 1024;  // 10 MB, 50 MB, etc.
        size_t actual_size = fs::file_size(file_path);
        ASSERT_EQ(expected_size, actual_size);
        std::cout << std::endl << std::endl;
    }
}

// Test directory creation
TEST(SenderTest, DirectoryCreationTest) {
    std::cout << std::endl;
    std::string test_dir = "./TestBuffer";
    if (fs::exists(test_dir)) {
        fs::remove_all(test_dir);
    }
    create_directory_if_not_exists_by_sender(test_dir);
    ASSERT_TRUE(fs::exists(test_dir));
    fs::remove_all(test_dir);  // Clean up
    std::cout << std::endl << std::endl;
}

// Test file renaming
TEST(SenderTest, RenameFileTest) {
    std::cout << std::endl;
    create_directory_if_not_exists_by_sender(BUFFER_DIR);
    std::string tmp_file_path = BUFFER_DIR + "/test_file.tmp";
    std::string txt_file_path = BUFFER_DIR + "/test_file.txt";
    create_file(tmp_file_path, 10);  // Create a 10 MB .tmp file
    rename_file(tmp_file_path, txt_file_path);
    ASSERT_TRUE(fs::exists(txt_file_path));
    ASSERT_FALSE(fs::exists(tmp_file_path));
    fs::remove(txt_file_path);  // Clean up
    std::cout << "//////////////////////////////////Performance Testing STARTS=> /////////////////////////////////////";
    std::cout << std::endl;
}

////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////Performance Testing /////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////

// Performance test for file creation
TEST(SenderPerformanceTest, FileCreationTime) {
    std::cout << std::endl;
    create_directory_if_not_exists_by_sender(BUFFER_DIR);
    std::string file_path = BUFFER_DIR + "/perf_test_file.tmp";

    auto start_time = std::chrono::high_resolution_clock::now();
    create_file(file_path, 100);  // Create a 100 MB file
    auto end_time = std::chrono::high_resolution_clock::now();

    long long duration_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();
    std::cout << "Time taken to create 100 MB file: " << duration_ms << " ms" << std::endl;

    fs::remove(file_path);  // Clean up

    // Assert that the file creation time is within an acceptable range
    ASSERT_LT(duration_ms, 500);  // Assume threshold = 500 for file creation
    std::cout << std::endl << std::endl;
}

// Performance test for file renaming
TEST(SenderPerformanceTest, FileRenamingTime) {
    std::cout << std::endl;
    create_directory_if_not_exists_by_sender(BUFFER_DIR);
    std::string tmp_file_path = BUFFER_DIR + "/perf_test_file.tmp";
    std::string txt_file_path = BUFFER_DIR + "/perf_test_file.txt";
    create_file(tmp_file_path, 100);  // Create a 100 MB .tmp file

    auto start_time = std::chrono::high_resolution_clock::now();
    rename_file(tmp_file_path, txt_file_path);
    auto end_time = std::chrono::high_resolution_clock::now();

    long long duration_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();
    std::cout << "Time taken to rename 100 MB file: " << duration_ms << " ms" << std::endl;

    fs::remove(txt_file_path);  // Clean up

    // Assert that the file renaming time is within an acceptable range
    ASSERT_LT(duration_ms, 100);  // Example threshold
    std::cout << std::endl << std::endl;
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
