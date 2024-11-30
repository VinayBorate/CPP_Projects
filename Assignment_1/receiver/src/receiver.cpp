#include "../include/receiver.h"
#include <iostream>
#include <fstream>
#include <filesystem>
#include <chrono>
#include <thread>
#include <vector>

namespace fs = std::filesystem;

const std::string BUFFER_DIR = "./VijayBuffer";

void log_statistics(int file_count, long long total_read_time_ms, long long total_delete_time_ms) {
    if (file_count % 5 == 0) {
        double avg_read_time_ms = static_cast<double>(total_read_time_ms) / file_count;
        double avg_delete_time_ms = static_cast<double>(total_delete_time_ms) / file_count;
        std::cout << "Statistics after " << file_count << " files:" << std::endl;
        std::cout << "Average read time per file: " << avg_read_time_ms << " ms" << std::endl;
        std::cout << "Average delete time per file: " << avg_delete_time_ms << " ms" << std::endl;
        std::cout << "Number of files read: " << file_count << std::endl;
        std::cout << "Number of files deleted: " << file_count << std::endl;
    }
}

std::vector<char> read_file(const std::string &file_path, long long &read_time_ms) {
    auto start_time = std::chrono::high_resolution_clock::now();

    std::ifstream file(file_path, std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file " << file_path << std::endl;
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
    return file_read_buffer;
}

void delete_file(const std::string &file_path, long long &delete_time_ms) {
    auto start_time = std::chrono::high_resolution_clock::now();

    if (fs::remove(file_path)) {
        auto end_time = std::chrono::high_resolution_clock::now();
        delete_time_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();
        std::cout << "Deleted file: " << file_path << " in " << delete_time_ms << " ms" << std::endl;
    } else {
        std::cerr << "Error: Failed to delete file " << file_path << std::endl;
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
        throw;
    }
}

void receiver(bool waitForFiles) {
    int file_count = 0;
    long long total_read_time_ms = 0;
    long long total_delete_time_ms = 0;

    create_directory_if_not_exists_by_receiver(BUFFER_DIR);

    while (true) {
        bool files_found = false;

        for (const auto &entry : fs::directory_iterator(BUFFER_DIR)) {
            if (entry.is_regular_file() && entry.path().extension() == ".txt") {
                files_found = true;
                auto start_time = std::chrono::high_resolution_clock::now();

                process_file(entry.path().string());

                auto end_time = std::chrono::high_resolution_clock::now();
                long long file_time_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();
                total_read_time_ms += file_time_ms;

                file_count++;

                log_statistics(file_count, total_read_time_ms, total_delete_time_ms);
            }
        }

        if (!files_found) {
            std::cout << "Waiting for sender to upload files..." << std::endl;
        }

        if (!waitForFiles) {
            break;
        }

        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

#ifndef UNIT_TEST
int main() {
    try {
        receiver(true);
    } catch (const std::exception &e) {
        std::cerr << "Error in receiver: " << e.what() << std::endl;
    }

    return 0;
}
#endif
