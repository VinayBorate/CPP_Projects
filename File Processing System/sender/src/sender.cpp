#include "../include/sender.h"
#include "../../common/include/config.h"
#include "../../common/include/logger.h"
#include <iostream>
#include <fstream>
#include <filesystem>
#include <stdexcept>
#include <chrono>
#include <vector>
#include <map>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/basic_file_sink.h>

namespace fs = std::filesystem;

std::vector<int> FILE_SIZES_MB;

void create_directory_if_not_exists_by_sender(const std::string &path) {
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

void create_file(const std::string &file_path, int size_mb) {
    std::ofstream file(file_path, std::ios::binary);

    if (!file) {
        throw std::runtime_error("Failed to create file: " + file_path);
    }

    std::vector<char> file_create_buffer(size_mb * 1024 * 1024, 'A');
    file.write(file_create_buffer.data(), file_create_buffer.size());
    file.close();
}

void rename_file(const std::string &old_path, const std::string &new_path) {
    fs::rename(old_path, new_path);
}

int sender(bool waitForUserInput) {
    int no_of_time_user_enter_Yes = 1;
    loadConfig();
    BUFFER_DIR = getConfigValue("BUFFER_DIR");
    create_directory_if_not_exists_by_sender(BUFFER_DIR);

    int files_created = 0;
    long long total_time_ms = 0;
    bool continue_creating = true;
    FILE_SIZES_MB = splitAndConvertToIntArray(getConfigValue("FILE_SIZES_MB"), '|');
    std::string FILE_NAME = getConfigValue("FILE_NAME");
    std::string TEMP_FILE_EXTENSION = getConfigValue("TEMP_FILE_EXTENSION");
    FINAL_FILE_EXTENSION = getConfigValue("FINAL_FILE_EXTENSION");
    int NO_OF_FILE_SEN_GENERATE;
    NO_OF_FILE_SEN_GENERATE = std::stoi(getConfigValue("NO_OF_FILE_SEN_GENERATE"));
    while (continue_creating) {
        if (NO_OF_FILE_SEN_GENERATE <= FILE_SIZES_MB.size()) {
            for (int i = 0; i < NO_OF_FILE_SEN_GENERATE; i++) {
                std::string tmp_file_path = BUFFER_DIR + "/" + FILE_NAME + std::to_string(files_created + 1) + TEMP_FILE_EXTENSION;
                std::string txt_file_path = BUFFER_DIR + "/" + FILE_NAME + std::to_string(files_created + 1) + FINAL_FILE_EXTENSION;

                auto start_time = std::chrono::high_resolution_clock::now();

                create_file(tmp_file_path, FILE_SIZES_MB[i]);
                rename_file(tmp_file_path, txt_file_path);

                auto end_time = std::chrono::high_resolution_clock::now();
                long long file_time_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();
                total_time_ms += file_time_ms;

                std::cout << "Created file: " << txt_file_path << " with size " << FILE_SIZES_MB[i] << " MB in " << file_time_ms << " ms" << std::endl;
                spdlog::info("Created file: {} with size {} MB in {} ms", txt_file_path, FILE_SIZES_MB[i], file_time_ms);

                files_created++;

                if (files_created % NO_OF_FILE_SEN_GENERATE == 0) {
                    double avg_time_ms = static_cast<double>(total_time_ms) / files_created;
                    std::cout << "Statistics after " << files_created << " files:" << std::endl;
                    std::cout << "Average time per file: " << avg_time_ms << " ms" << std::endl;
                    std::cout << "Number of files sent: " << files_created << std::endl;
                    spdlog::info("Statistics after {} files:", files_created);
                    spdlog::info("Average time per file: {} ms", avg_time_ms);
                    spdlog::info("Number of files sent: {}", files_created);
                }
            }
        } else {
            int x = NO_OF_FILE_SEN_GENERATE;
            while (NO_OF_FILE_SEN_GENERATE) {
                for (int size : FILE_SIZES_MB) {
                    std::string tmp_file_path = BUFFER_DIR + "/" + FILE_NAME + std::to_string(files_created + 1) + TEMP_FILE_EXTENSION;
                    std::string txt_file_path = BUFFER_DIR + "/" + FILE_NAME + std::to_string(files_created + 1) + FINAL_FILE_EXTENSION;

                    auto start_time = std::chrono::high_resolution_clock::now();

                    create_file(tmp_file_path, size);
                    rename_file(tmp_file_path, txt_file_path);

                    auto end_time = std::chrono::high_resolution_clock::now();
                    long long file_time_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();
                    total_time_ms += file_time_ms;

                    std::cout << "Created file: " << txt_file_path << " with size " << size << " MB in " << file_time_ms << " ms" << std::endl;
                    spdlog::info("Created file: {} with size {} MB in {} ms", txt_file_path, size, file_time_ms);

                    files_created++;
                    NO_OF_FILE_SEN_GENERATE--;
                    if (NO_OF_FILE_SEN_GENERATE == 0) {
                        break;
                    }

                    if (files_created % x == 0) {
                        double avg_time_ms = static_cast<double>(total_time_ms) / files_created;
                        std::cout << "Statistics after " << files_created << " files:" << std::endl;
                        std::cout << "Average time per file: " << avg_time_ms << " ms" << std::endl;
                        std::cout << "Number of files sent: " << files_created << std::endl;
                        spdlog::info("Statistics after {} files:", files_created);
                        spdlog::info("Average time per file: {} ms", avg_time_ms);
                        spdlog::info("Number of files sent: {}", files_created);
                    }
                }
            }
        }

        char choice;
        std::cout << "Do you want to create more files? (Y/N): ";
        std::cin >> choice;
        if (choice == 'N' || choice == 'n') {
            continue_creating = false;
        } else {
            NO_OF_FILE_SEN_GENERATE = std::stoi(getConfigValue("NO_OF_FILE_SEN_GENERATE"));
            no_of_time_user_enter_Yes++;
        }
    }

    if (waitForUserInput) {
        std::cout << "Press any key to exit...";
        std::cin.ignore();
        std::cin.get();
    }
    return no_of_time_user_enter_Yes;
}

#ifndef UNIT_TEST
int main() {
    loadConfig();
     LOGGER_LEVEL_SET = getConfigValue("LOGGER_LEVEL_SET");
    try {
        setup_logger("sender_logger", "senderlog.txt",LOGGER_LEVEL_SET);
       
        spdlog::trace("================================================================================");
        spdlog::trace("==========================Starting sender.cp====================================");
        spdlog::trace("================================================================================");
        sender(true);
    } catch (const std::exception &e) {
        spdlog::error("Error: {}", e.what());
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

        
        spdlog::trace("================================================================================");
        spdlog::trace("==========================Ending  sender.cp====================================");
        spdlog::trace("================================================================================");
    return 0;
}
#endif