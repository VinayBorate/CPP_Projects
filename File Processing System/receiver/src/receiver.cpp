#include "../include/receiver.h"
#include "../../common/include/config.h"
#include "../../common/include/logger.h"
#include <iostream>
#include <fstream>
#include <filesystem>
#include <chrono>
#include <thread>
#include <vector>
#include <map>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/basic_file_sink.h>

namespace fs = std::filesystem;

// ****************Will read this from Configuration file *************************** //

int LOG_STATS_AFTER_TIME_SEC; // Default value
int file_count = 0;
long long total_read_time_ms = 0;
long long total_delete_time_ms = 0; // no useeeee
long long final_delete_time_ms = 0;

void loggingFunction(int &file_count, long long &total_read_time_ms, long long &total_delete_time_ms) {
    while (true) {
        std::this_thread::sleep_for(std::chrono::seconds(LOG_STATS_AFTER_TIME_SEC));
        log_statistics(file_count, total_read_time_ms, total_delete_time_ms);
    }
}

void log_statistics(int file_count, long long total_read_time_ms, long long total_delete_time_ms) {
    double avg_read_time_ms;
    double avg_delete_time_ms;
    if (file_count == 0) {
        avg_read_time_ms = 0;
        avg_delete_time_ms = 0;
    } else {
        avg_read_time_ms = static_cast<double>(total_read_time_ms) / file_count;
        avg_delete_time_ms = static_cast<double>(final_delete_time_ms) / file_count;
    }
    std::cout << std::endl << "=====================================";
    std::cout << "Statistics after Every " << LOG_STATS_AFTER_TIME_SEC << " SECONDS" << std::endl;
    std::cout << "Average read time per file: " << avg_read_time_ms << " ms" << std::endl;
    std::cout << "Average delete time per file: " << avg_delete_time_ms << " ms" << std::endl;
    std::cout << "Number of files read: " << file_count << std::endl;
    std::cout << "Number of files deleted: " << file_count << std::endl;
    std::cout << std::endl << "=====================================";

    spdlog::info("=====================================");
    spdlog::info("Statistics after Every {} SECONDS", LOG_STATS_AFTER_TIME_SEC);
    spdlog::info("Average read time per file: {} ms", avg_read_time_ms);
    spdlog::info("Average delete time per file: {} ms", avg_delete_time_ms);
    spdlog::info("Number of files read: {}", file_count);
    spdlog::info("Number of files deleted: {}", file_count);
    spdlog::info("=====================================");
    spdlog::default_logger()->flush();
}

std::vector<char> read_file(const std::string &file_path, long long &read_time_ms) {
    auto start_time = std::chrono::high_resolution_clock::now();

    std::ifstream file(file_path, std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file " << file_path << std::endl;
        spdlog::error("Error: Unable to open file {}", file_path);
        return {};
    }

    file.seekg(0, std::ios::end);
    std::streampos file_size = file.tellg();
    file.seekg(0, std::ios::beg);

    std::vector<char> file_read_buffer(file_size);
    file.read(file_read_buffer.data(), file_size);
    file.close();

    auto end_time = std::chrono::high_resolution_clock::now();
    read_time_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();

    std::cout << "Read file: " << file_path << " in " << read_time_ms << " ms, Size: " << file_size / (1024 * 1024) << " MB" << std::endl;
    spdlog::info("Read file: {} in {} ms, Size: {} MB", file_path, read_time_ms, file_size / (1024 * 1024));
    return file_read_buffer;
}

void delete_file(const std::string &file_path, long long &delete_time_ms) {
    auto start_time = std::chrono::high_resolution_clock::now();

    if (fs::remove(file_path)) {
        auto end_time = std::chrono::high_resolution_clock::now();
        delete_time_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();
        std::cout << "Deleted file: " << file_path << " in " << delete_time_ms << " ms" << std::endl;
        spdlog::info("Deleted file: {} in {} ms", file_path, delete_time_ms);
        final_delete_time_ms += delete_time_ms;
    } else {
        std::cerr << "Error: Failed to delete file " << file_path << std::endl;
        spdlog::error("Error: Failed to delete file {}", file_path);
    }
}

void process_file(const std::string &file_path) {
    long long read_time_ms = 0;
    long long delete_time_ms = 0;

    auto file_content = read_file(file_path, read_time_ms);
    delete_file(file_path, delete_time_ms);
}

void create_directory_if_not_exists_by_receiver(const std::string &path) {
    try {
        if (!fs::exists(path)) {
            fs::create_directory(path);
        }
    } catch (const fs::filesystem_error &e) {
        std::cerr << "Error: Unable to create directory " << path << ": " << e.what() << std::endl;
        spdlog::error("Error: Unable to create directory {}: {}", path, e.what());
        throw;
    }
}

void receiver(bool waitForFiles) {
    BUFFER_DIR = getConfigValue("BUFFER_DIR");
    create_directory_if_not_exists_by_receiver(BUFFER_DIR);
    FINAL_FILE_EXTENSION = getConfigValue("FINAL_FILE_EXTENSION");
    std::cout << FINAL_FILE_EXTENSION << std::endl;
    spdlog::info("{}", FINAL_FILE_EXTENSION);
    while (true) {
        bool files_found = false;

        for (const auto &entry : fs::directory_iterator(BUFFER_DIR)) {
            if (entry.is_regular_file() && entry.path().extension() == FINAL_FILE_EXTENSION) {
                files_found = true;
                auto start_time = std::chrono::high_resolution_clock::now();

                process_file(entry.path().string());

                auto end_time = std::chrono::high_resolution_clock::now();
                long long file_time_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();
                total_read_time_ms += file_time_ms;

                file_count++;
            }
        }

        if (!files_found) {
            std::cout << "Waiting for sender to upload files..." << std::endl;
            spdlog::warn("Waiting for sender to upload files...");
            spdlog::default_logger()->flush();
        }

        if (!waitForFiles) {
            break;
        }

        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}


#ifndef UNIT_TEST
int main() {
    loadConfig();
    LOGGER_LEVEL_SET = getConfigValue("LOGGER_LEVEL_SET");
    try {
        setup_logger("receiver_logger", "receiverlog.txt",LOGGER_LEVEL_SET);
        spdlog::trace("================================================================================");
        spdlog::trace("==========================Starting receiver.cpp ====================================");
        spdlog::trace("================================================================================");


        std::string value = getConfigValue("LOG_STATS_AFTER_TIME_SEC");
        if (!value.empty()) {
            LOG_STATS_AFTER_TIME_SEC = std::stoi(value);
        } else {
            spdlog::error("Key not found: LOG_STATS_AFTER_TIME_SEC. Using default value : {}",LOG_STATS_AFTER_TIME_SEC);
            spdlog::warn("Key not found: LOG_STATS_AFTER_TIME_SEC. Using default value: {}", LOG_STATS_AFTER_TIME_SEC);
        }


        // Start the logging thread
        std::thread loggingThread(loggingFunction, std::ref(file_count), std::ref(total_read_time_ms), std::ref(total_delete_time_ms));

        receiver(true);

        // Join the logging thread to the main thread
        loggingThread.join();
    } catch (const std::exception &e) {
         spdlog::error("Error in receiver: {}", e.what());
       spdlog::error("Error in receiver: {}", e.what());
    }

      spdlog::trace("================================================================================");
        spdlog::trace("==========================Ending receiver.cpp====================================");
        spdlog::trace("================================================================================");


    return 0;
}
#endif