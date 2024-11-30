#include "sender.h"
#include <iostream>
#include <fstream>
#include <filesystem>
#include <stdexcept>
#include <chrono>
#include <vector>

namespace fs = std::filesystem;
const std::string BUFFER_DIR = "./VijayBuffer";
const int FILE_SIZES_MB[] = {10, 50, 100, 150, 200};

void create_directory_if_not_exists_by_sender(const std::string &path) {
    try {
        if (!fs::exists(path)) {
            fs::create_directory(path);
        }
    } catch (const fs::filesystem_error &e) {
        std::cerr << "Error: Unable to create directory " << path << ": " << e.what() << std::endl;
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

void sender(bool waitForUserInput) {
    create_directory_if_not_exists_by_sender(BUFFER_DIR);

    int files_created = 0;
    long long total_time_ms = 0;
    bool continue_creating = true;

    while (continue_creating) {
        for (int size : FILE_SIZES_MB) {
            std::string tmp_file_path = BUFFER_DIR + "/file_" + std::to_string(files_created + 1) + ".tmp";
            std::string txt_file_path = BUFFER_DIR + "/file_" + std::to_string(files_created + 1) + ".txt";

            auto start_time = std::chrono::high_resolution_clock::now();

            create_file(tmp_file_path, size);
            rename_file(tmp_file_path, txt_file_path);

            auto end_time = std::chrono::high_resolution_clock::now();
            long long file_time_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();
            total_time_ms += file_time_ms;

            std::cout << "Created file: " << txt_file_path << " with size " << size << " MB in " << file_time_ms << " ms" << std::endl;

            files_created++;

            if (files_created % 5 == 0) {
                double avg_time_ms = static_cast<double>(total_time_ms) / files_created;
                std::cout << "Statistics after " << files_created << " files:" << std::endl;
                std::cout << "Average time per file: " << avg_time_ms << " ms" << std::endl;
                std::cout << "Number of files sent: " << files_created << std::endl;
            }
        }

        char choice;
        std::cout << "Do you want to create more files? (Y/N): ";
        std::cin >> choice;
        if (choice == 'N' || choice == 'n') {
            continue_creating = false;
        }
    }

    if (waitForUserInput) {
        std::cout << "Press any key to exit...";
        std::cin.ignore();
        std::cin.get();
    }
}

#ifndef UNIT_TEST
int main() {
    try {
        sender(true);
    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}
#endif
