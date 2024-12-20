#ifndef SENDER_H
#define SENDER_H

#include <string>

// Function declarations
void create_directory_if_not_exists_by_sender(const std::string &path);
void create_file(const std::string &file_path, int size_mb);
void rename_file(const std::string &old_path, const std::string &new_path);
int sender(bool waitForUserInput);

#endif // SENDER_H