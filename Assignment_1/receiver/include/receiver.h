#ifndef RECEIVER_H
#define RECEIVER_H

#include <string>
#include <vector>

// Function declarations
void log_statistics(int file_count, long long total_read_time_ms, long long total_delete_time_ms);
std::vector<char> read_file(const std::string &file_path, long long &read_time_ms);
void delete_file(const std::string &file_path, long long &delete_time_ms);
void process_file(const std::string &file_path);
void create_directory_if_not_exists_by_receiver(const std::string &path);
void receiver(bool waitForFiles);

#endif // RECEIVER_H
