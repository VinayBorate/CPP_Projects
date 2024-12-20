#include <gtest/gtest.h>
#include <filesystem>
#include <fstream>
#include <iostream>
#include "../../sender/include/sender.h"
#include "../../common/include/config.h"
#include "../../common/include/logger.h"
#include <spdlog/spdlog.h>
#include <spdlog/sinks/basic_file_sink.h>

namespace fs = std::filesystem;

// Global variables for configuration values
int PTEST_SEN_FILE_CREATE_OF_SIZE;
int PTEST_SEN_FILE_CREATE_OF_SIZE_THRESHOLD;
int PTEST_SEN_FILE_RENAME_THRESHOLD;
int no_of_time_user_enter_Yes;
int sender_file_creation_limit;
std::string sender_file_name;
std::vector<int> FILE_SIZES_MB_B;

int main(int argc, char **argv) {
    loadConfig();
   
     LOGGER_LEVEL_SET = getConfigValue("LOGGER_LEVEL_SET");
      setup_logger("test_sender_logger", "test_senderlog.txt",LOGGER_LEVEL_SET);
        spdlog::trace("================================================================================");
        spdlog::trace("==========================Starting test_sender.cpp =============================");
        spdlog::trace("================================================================================");
   
    BUFFER_DIR = getConfigValue("BUFFER_DIR");
    FILE_SIZES_MB_B = splitAndConvertToIntArray(getConfigValue("FILE_SIZES_MB"), '|');
    PTEST_SEN_FILE_CREATE_OF_SIZE = std::stoi(getConfigValue("PTEST_SEN_FILE_CREATE_OF_SIZE"));
    PTEST_SEN_FILE_CREATE_OF_SIZE_THRESHOLD = std::stoi(getConfigValue("PTEST_SEN_FILE_CREATE_OF_SIZE_THRESHOLD"));
    PTEST_SEN_FILE_RENAME_THRESHOLD = std::stoi(getConfigValue("PTEST_SEN_FILE_RENAME_THRESHOLD"));
    FINAL_FILE_EXTENSION = getConfigValue("FINAL_FILE_EXTENSION");
    sender_file_creation_limit = std::stoi(getConfigValue("NO_OF_FILE_SEN_GENERATE"));
    sender_file_name = getConfigValue("FILE_NAME");
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////UNIT TESTING //////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////

// Test FileCountValidationTest => checking the count of file generated
TEST(SenderTest, FileCountValidationTest) {
    std::cout << std::endl << std::endl;
    spdlog::info("Starting FileCountValidationTest");
    create_directory_if_not_exists_by_sender(BUFFER_DIR);
    no_of_time_user_enter_Yes = sender(false);  // Disable user input prompt
    int file_count = 0;
    for (const auto& entry : fs::directory_iterator(BUFFER_DIR)) {
        if (entry.path().extension() == FINAL_FILE_EXTENSION) {
            file_count++;
        }
    }
    ASSERT_EQ(file_count, no_of_time_user_enter_Yes * sender_file_creation_limit);
    fs::remove_all(BUFFER_DIR);  // Clean up
    std::cout << std::endl << std::endl;
    spdlog::info("Completed FileCountValidationTest");
}

// FileSizeValidationTest
TEST(SenderTest, FileSizeValidationTest) {
    create_directory_if_not_exists_by_sender(BUFFER_DIR);
    no_of_time_user_enter_Yes = sender(false);  // Disable user input prompt
    size_t expected_size = 0;
    size_t actual_size = 0;
    size_t final_actual_size = 0;
    for (int i = 0; i < no_of_time_user_enter_Yes * sender_file_creation_limit; ++i) {  // Checking file size, let's say 10 files in bulk
        std::string file_path = BUFFER_DIR + "/" + sender_file_name + std::to_string(i + 1) + FINAL_FILE_EXTENSION;
        std::cout << "PATH OF FILE IS ====>>>>" << file_path << std::endl;
        spdlog::info("PATH OF FILE IS ====>>>>{}", file_path);
        ASSERT_TRUE(fs::exists(file_path));

        // Calculate the expected size
        size_t current_file_size = FILE_SIZES_MB_B[i % FILE_SIZES_MB_B.size()] * 1024 * 1024;
        expected_size += current_file_size;
        actual_size = fs::file_size(file_path);
        final_actual_size += actual_size;

        // Debugging output
        std::cout << "File: " << file_path << ", Expected Size: " << current_file_size << " bytes, Actual Size: " << actual_size << " bytes" << std::endl;
        spdlog::info("File: {}, Expected Size: {} bytes, Actual Size: {} bytes", file_path, current_file_size, actual_size);
    }
    ASSERT_EQ(expected_size, final_actual_size);
    fs::remove_all(BUFFER_DIR);  // Clean up
    std::cout << std::endl << std::endl;
}

// Test directory creation
TEST(SenderTest, DirectoryCreationTest) {
    std::cout << "Sender DirectoryCreationTest PATH(BUFFER_DIR)=" << BUFFER_DIR << std::endl;
    spdlog::info("Sender DirectoryCreationTest PATH(BUFFER_DIR)={}", BUFFER_DIR);
    std::cout << std::endl;
    std::string test_dir = BUFFER_DIR;
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
    spdlog::info("Starting RenameFileTest");
    create_directory_if_not_exists_by_sender(BUFFER_DIR);
    std::string tmp_file_path = BUFFER_DIR + "/test_file.tmp";
    std::string txt_file_path = BUFFER_DIR + "/test_file.txt";
    create_file(tmp_file_path, 10);  // Create a 10 MB .tmp file
    rename_file(tmp_file_path, txt_file_path);
    ASSERT_TRUE(fs::exists(txt_file_path));
    ASSERT_FALSE(fs::exists(tmp_file_path));
    fs::remove(txt_file_path);  // Clean up
    fs::remove_all(BUFFER_DIR);
    std::cout << std::endl;
    spdlog::info("Completed RenameFileTest");
}

////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////Performance Testing /////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////

// Performance test for file creation
TEST(SenderPerformanceTest, FileCreationTime) {
    std::cout << std::endl;
    std::cout << "TIME LIMIT To Create " << PTEST_SEN_FILE_CREATE_OF_SIZE << " MB FILE IS => " << PTEST_SEN_FILE_CREATE_OF_SIZE_THRESHOLD << " ms" << std::endl;
    spdlog::info("TIME LIMIT To Create {} MB FILE IS => {} ms", PTEST_SEN_FILE_CREATE_OF_SIZE, PTEST_SEN_FILE_CREATE_OF_SIZE_THRESHOLD);
    create_directory_if_not_exists_by_sender(BUFFER_DIR);
    std::string file_path = BUFFER_DIR + "/perf_test_file.tmp";

    auto start_time = std::chrono::high_resolution_clock::now();
    create_file(file_path, PTEST_SEN_FILE_CREATE_OF_SIZE);  // Create a 100 MB file
    auto end_time = std::chrono::high_resolution_clock::now();

    long long duration_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();
    std::cout << "Time taken to create " << PTEST_SEN_FILE_CREATE_OF_SIZE << " MB file: " << duration_ms << " ms" << std::endl;
    spdlog::info("Time taken to create {} MB file: {} ms", PTEST_SEN_FILE_CREATE_OF_SIZE, duration_ms);

    fs::remove(file_path);  // Clean up
    fs::remove_all(BUFFER_DIR);

    // Assert that the file creation time is within an acceptable range
    ASSERT_LT(duration_ms, PTEST_SEN_FILE_CREATE_OF_SIZE_THRESHOLD);  // Assume threshold = 500 for file creation
    std::cout << std::endl << std::endl;
}

// Performance test for file renaming
TEST(SenderPerformanceTest, FileRenamingTime) {
    std::cout << std::endl;
    std::cout << "TIME LIMIT To Rename " << PTEST_SEN_FILE_CREATE_OF_SIZE << " MB FILE IS => " << PTEST_SEN_FILE_RENAME_THRESHOLD << " ms" << std::endl;
    spdlog::info("TIME LIMIT To Rename {} MB FILE IS => {} ms", PTEST_SEN_FILE_CREATE_OF_SIZE, PTEST_SEN_FILE_RENAME_THRESHOLD);
    create_directory_if_not_exists_by_sender(BUFFER_DIR);
    std::string tmp_file_path = BUFFER_DIR + "/perf_test_file.tmp";
    std::string txt_file_path = BUFFER_DIR + "/perf_test_file.txt";
    create_file(tmp_file_path, PTEST_SEN_FILE_CREATE_OF_SIZE);  // Create a 100 MB .tmp file

    auto start_time = std::chrono::high_resolution_clock::now();
    rename_file(tmp_file_path, txt_file_path);
    auto end_time = std::chrono::high_resolution_clock::now();

    long long duration_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();
    std::cout << "Time taken to rename " << PTEST_SEN_FILE_CREATE_OF_SIZE << " MB file: " << duration_ms << " ms" << std::endl;
    spdlog::info("Time taken to rename {} MB file: {} ms", PTEST_SEN_FILE_CREATE_OF_SIZE, duration_ms);

    fs::remove(txt_file_path);  // Clean up
    fs::remove_all(BUFFER_DIR);

    // Assert that the file renaming time is within an acceptable range
    ASSERT_LT(duration_ms, PTEST_SEN_FILE_RENAME_THRESHOLD);  // Example threshold
    std::cout << std::endl << std::endl;
}