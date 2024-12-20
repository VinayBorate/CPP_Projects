#include <gtest/gtest.h>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include "../include/receiver.h"
#include "../../sender/include/sender.h"
#include "../../common/include/config.h"
#include "../../common/include/logger.h"
#include <spdlog/spdlog.h>
#include <spdlog/sinks/basic_file_sink.h>

namespace fs = std::filesystem;

// Global variables for configuration values
int UTEST_REC_FILE_READ_OF_SIZE;
int UTEST_REC_FILE_DELETE_OF_SIZE;
int UTEST_REC_FILE_PROCESSING_OF_SIZE;
int PTEST_REC_FILE_READ_OF_SIZE;
int PTEST_REC_FILE_READ_OF_SIZE_THRESHOLD;
int PTEST_REC_FILE_DELETE_OF_SIZE;
int PTEST_REC_FILE_DELETE_OF_SIZE_THRESHOLD;

int main(int argc, char **argv) {
     loadConfig();
     LOGGER_LEVEL_SET = getConfigValue("LOGGER_LEVEL_SET");
    setup_logger("test_receiver_logger", "test_receiverlog.txt",LOGGER_LEVEL_SET);
        spdlog::trace("================================================================================");
        spdlog::trace("==========================Starting test_receiver.cpp ====================================");
        spdlog::trace("================================================================================");

   
    BUFFER_DIR = getConfigValue("BUFFER_DIR");
    UTEST_REC_FILE_READ_OF_SIZE = std::stoi(getConfigValue("UTEST_REC_FILE_READ_OF_SIZE"));
    UTEST_REC_FILE_DELETE_OF_SIZE = std::stoi(getConfigValue("UTEST_REC_FILE_DELETE_OF_SIZE"));
    UTEST_REC_FILE_PROCESSING_OF_SIZE = std::stoi(getConfigValue("UTEST_REC_FILE_PROCESSING_OF_SIZE"));
    FILE_NAME = getConfigValue("FILE_NAME");
    PTEST_REC_FILE_READ_OF_SIZE = std::stoi(getConfigValue("PTEST_REC_FILE_READ_OF_SIZE"));
    PTEST_REC_FILE_READ_OF_SIZE_THRESHOLD = std::stoi(getConfigValue("PTEST_REC_FILE_READ_OF_SIZE_THRESHOLD"));
    PTEST_REC_FILE_DELETE_OF_SIZE = std::stoi(getConfigValue("PTEST_REC_FILE_DELETE_OF_SIZE"));
    PTEST_REC_FILE_DELETE_OF_SIZE_THRESHOLD = std::stoi(getConfigValue("PTEST_REC_FILE_DELETE_OF_SIZE_THRESHOLD"));

    // Initialize Google Test
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////UNIT TESTING //////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////

// Test file reading
TEST(ReceiverTest, ReadFileTest) {
    std::cout << "ReadFileTest => SIZE LIMIT : (UTEST_REC_FILE_READ_OF_SIZE) = " << UTEST_REC_FILE_READ_OF_SIZE << std::endl;
    spdlog::info("ReadFileTest => SIZE LIMIT : (UTEST_REC_FILE_READ_OF_SIZE) = {}", UTEST_REC_FILE_READ_OF_SIZE);
    std::cout << std::endl << std::endl;
    create_directory_if_not_exists_by_receiver(BUFFER_DIR);
    std::string file_path = BUFFER_DIR + "/" + FILE_NAME;
    
    create_file(file_path, UTEST_REC_FILE_READ_OF_SIZE);  // Use the configured size
    long long read_time_ms = 0;
    auto file_content = read_file(file_path, read_time_ms);
    ASSERT_FALSE(file_content.empty());
    std::cout << std::endl << std::endl;
    fs::remove(file_path);  // Clean up
}

// Test file deletion
TEST(ReceiverTest, DeleteFileTest) {
    std::cout << "DeleteFileTest => SIZE LIMIT : (UTEST_REC_FILE_DELETE_OF_SIZE) = " << UTEST_REC_FILE_DELETE_OF_SIZE << std::endl;
    spdlog::info("DeleteFileTest => SIZE LIMIT : (UTEST_REC_FILE_DELETE_OF_SIZE) = {}", UTEST_REC_FILE_DELETE_OF_SIZE);
    std::cout << std::endl;
    create_directory_if_not_exists_by_receiver(BUFFER_DIR);
    std::string file_path = BUFFER_DIR + "/" + FILE_NAME;
    create_file(file_path, UTEST_REC_FILE_DELETE_OF_SIZE);  // Use the configured size
    long long delete_time_ms = 0;
    delete_file(file_path, delete_time_ms);
    ASSERT_FALSE(fs::exists(file_path));
    std::cout << std::endl << std::endl;
}

// Test file processing (read + delete)
TEST(ReceiverTest, ProcessFileTest) {
    std::cout << "ProcessFileTest => SIZE LIMIT : (UTEST_REC_FILE_PROCESSING_OF_SIZE) = " << UTEST_REC_FILE_PROCESSING_OF_SIZE << std::endl;
    spdlog::info("ProcessFileTest => SIZE LIMIT : (UTEST_REC_FILE_PROCESSING_OF_SIZE) = {}", UTEST_REC_FILE_PROCESSING_OF_SIZE);
    std::cout << std::endl;
    create_directory_if_not_exists_by_receiver(BUFFER_DIR);
    std::string file_path = BUFFER_DIR + "/" + FILE_NAME;
    create_file(file_path, UTEST_REC_FILE_PROCESSING_OF_SIZE);  // Use the configured size
    process_file(file_path);
    ASSERT_FALSE(fs::exists(file_path));
    std::cout << std::endl << std::endl;
}

// Test directory creation
TEST(ReceiverTest, DirectoryCreationTest) {
    std::cout << "DirectoryCreationTest PATH : =" << BUFFER_DIR << std::endl;
    spdlog::info("DirectoryCreationTest PATH : ={}", BUFFER_DIR);
    std::cout << std::endl;
    std::string test_dir = BUFFER_DIR;
    if (fs::exists(test_dir)) {
        fs::remove_all(test_dir);
    }
    create_directory_if_not_exists_by_receiver(test_dir);
    ASSERT_TRUE(fs::exists(test_dir));
    fs::remove_all(test_dir);  // Clean up
    std::cout << std::endl << std::endl << std::endl;
}

////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////Performance Testing /////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////

// Performance test for file reading
TEST(ReceiverPerformanceTest, FileReadingTime) {
    std::cout << "ReceiverFileReadingTime PerformanceTest, LIMIT : " << PTEST_REC_FILE_READ_OF_SIZE << " MB in " << PTEST_REC_FILE_READ_OF_SIZE_THRESHOLD << " ms " << std::endl;
    spdlog::info("ReceiverFileReadingTime PerformanceTest, LIMIT : {} MB in {} ms", PTEST_REC_FILE_READ_OF_SIZE, PTEST_REC_FILE_READ_OF_SIZE_THRESHOLD);
    std::cout << std::endl;
    std::cout << std::endl;
    create_directory_if_not_exists_by_receiver(BUFFER_DIR);
    std::string file_path = BUFFER_DIR + "/" + FILE_NAME;
    create_file(file_path, PTEST_REC_FILE_READ_OF_SIZE);  // Use the configured size

    long long read_time_ms = 0;
    auto start_time = std::chrono::high_resolution_clock::now();
    auto file_content = read_file(file_path, read_time_ms);
    auto end_time = std::chrono::high_resolution_clock::now();

    long long duration_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();
    std::cout << "Time taken to read " << PTEST_REC_FILE_READ_OF_SIZE << " MB file: " << duration_ms << " ms" << std::endl;
    spdlog::info("Time taken to read {} MB file: {} ms", PTEST_REC_FILE_READ_OF_SIZE, duration_ms);

    fs::remove(file_path);  // Clean up

    // Assert that the file reading time is within an acceptable range
    ASSERT_LT(duration_ms, PTEST_REC_FILE_READ_OF_SIZE_THRESHOLD);  // Example threshold

    std::cout << std::endl << std::endl;
}

// Performance test for file deletion
TEST(ReceiverPerformanceTest, FileDeletionTime) {
    std::cout << "ReceiverFileDeletionTime PerformanceTest, LIMIT :" << PTEST_REC_FILE_DELETE_OF_SIZE << " MB in " << PTEST_REC_FILE_DELETE_OF_SIZE_THRESHOLD << " ms " << std::endl;
    spdlog::info("ReceiverFileDeletionTime PerformanceTest, LIMIT : {} MB in {} ms", PTEST_REC_FILE_DELETE_OF_SIZE, PTEST_REC_FILE_DELETE_OF_SIZE_THRESHOLD);
    std::cout << std::endl;
    create_directory_if_not_exists_by_receiver(BUFFER_DIR);
    std::string file_path = BUFFER_DIR + "/" + FILE_NAME;
    create_file(file_path, PTEST_REC_FILE_DELETE_OF_SIZE);  // Use the configured size

    long long delete_time_ms = 0;
    auto start_time = std::chrono::high_resolution_clock::now();
    delete_file(file_path, delete_time_ms);
    auto end_time = std::chrono::high_resolution_clock::now();

    long long duration_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();
    std::cout << "Time taken to delete " << PTEST_REC_FILE_DELETE_OF_SIZE << " MB file: " << duration_ms << " ms" << std::endl;
    spdlog::info("Time taken to delete {} MB file: {} ms", PTEST_REC_FILE_DELETE_OF_SIZE, duration_ms);

    // Assert that the file deletion time is within an acceptable range
    ASSERT_LT(duration_ms, PTEST_REC_FILE_DELETE_OF_SIZE_THRESHOLD);  // Example threshold
       spdlog::info("Completed FileDeletionTime Performance Test SERVICE.............");

     spdlog::trace("================================================================================");
        spdlog::trace("==========================Ending test_receiver.cpp ====================================");
        spdlog::trace("================================================================================");
}