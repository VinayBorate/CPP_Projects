

---

# File Processing System

## Project Description

The **File Processing System** is a robust and efficient solution designed to handle the creation, writing, reading, and processing of files. It consists of two main applications:

- **Sender**: Responsible for creating and writing files.
- **Receiver**: Responsible for reading and deleting these files.

The system is designed to run each application on its own thread, ensuring efficient file handling and processing. The project includes features such as configurable file sizes, logging, and performance benchmarking. This system is ideal for scenarios where files need to be generated, monitored, and processed in real-time.

## Technology and Frameworks Used

- **C++**: The primary programming language used for the project.
- **CMake**: A cross-platform build system used to compile the project.
- **Google Test (gtest)**: A framework for writing and running C++ unit tests.
- **spdlog**: A fast C++ logging library.

## Project Structure

```
├── CMakeLists.txt
├── Readme.md
├── build
│   ├── CMakeCache.txt
│   ├── CMakeFiles
│   ├── Makefile
│   ├── cmake_install.cmake
│   ├── config
│   ├── liblogger.a
│   ├── receiver
│   ├── sender
│   ├── test_receiver
│   └── test_sender
├── common
│   ├── include
│   │   ├── config.h
│   │   └── logger.h
│   └── src
│       ├── config.cpp
│       └── logger.cpp
├── config
│   └── values.config
├── lib
│   ├── gtest
│   ├── libgtest.a
│   ├── libgtest_main.a
│   ├── libspdlog.a
│   └── spdlog
├── receiver
│   ├── include
│   │   └── receiver.h
│   ├── src
│   │   └── receiver.cpp
│   └── tests
│       ├── main
│       ├── main.cpp
│       └── test_receiver.cpp
└── sender
    ├── include
    │   └── sender.h
    ├── src
    │   └── sender.cpp
    └── tests
        └── test_sender.cpp
```

---
Sure, here's the second part of the README file:

---

## Project Images

*Include relevant images or diagrams of your project here.*

## Steps to Run the Project

1. **Clone the repository**:
    ```sh
    git clone <repository_url>
    cd <repository_directory>
    ```

2. **Build the project using CMake**:
    ```sh
    mkdir build
    cd build
    cmake ..
    make
    ```

3. **Run the Sender application**:
    ```sh
    ./sender
    ```

4. **Run the Receiver application**:
    ```sh
    ./receiver
    ```

5. **Run the tests**:
    ```sh
    ./test_sender
    ./test_receiver
    ```

## Technical Details

### Sender Application

- **create_directory_if_not_exists_by_sender**: Creates a directory if it does not exist.
    ```cpp
    void create_directory_if_not_exists_by_sender(const std::string &path);
    ```
    - **Parameters**: `path` - The directory path to be created.
    - **Description**: Checks if the directory exists, and if not, creates it. Logs any errors encountered during the process.

- **create_file**: Creates a file of a specified size.
    ```cpp
    void create_file(const std::string &file_path, int size_mb);
    ```
    - **Parameters**: `file_path` - The path of the file to be created, `size_mb` - The size of the file in megabytes.
    - **Description**: Creates a file with the specified size filled with dummy data.

- **rename_file**: Renames a file.
    ```cpp
    void rename_file(const std::string &old_path, const std::string &new_path);
    ```
    - **Parameters**: `old_path` - The current path of the file, `new_path` - The new path of the file.
    - **Description**: Renames the file from `old_path` to `new_path`.

- **sender**: Main function to handle file creation and renaming.
    ```cpp
    int sender(bool waitForUserInput);
    ```
    - **Parameters**: `waitForUserInput` - A boolean flag to wait for user input before exiting.
    - **Description**: Manages the creation and renaming of files based on configuration settings. Logs statistics and prompts the user to continue creating files.

---

Here's the third part of the README file:

---

### Receiver Application

- **create_directory_if_not_exists_by_receiver**: Creates a directory if it does not exist.
    ```cpp
    void create_directory_if_not_exists_by_receiver(const std::string &path);
    ```
    - **Parameters**: `path` - The directory path to be created.
    - **Description**: Checks if the directory exists, and if not, creates it. Logs any errors encountered during the process.

- **read_file**: Reads the content of a file.
    ```cpp
    std::vector<char> read_file(const std::string &file_path, long long &read_time_ms);
    ```
    - **Parameters**: `file_path` - The path of the file to be read, `read_time_ms` - Reference to store the time taken to read the file.
    - **Description**: Reads the file content into a buffer and logs the time taken.

- **delete_file**: Deletes a file.
    ```cpp
    void delete_file(const std::string &file_path, long long &delete_time_ms);
    ```
    - **Parameters**: `file_path` - The path of the file to be deleted, `delete_time_ms` - Reference to store the time taken to delete the file.
    - **Description**: Deletes the specified file and logs the time taken.

- **process_file**: Reads and deletes a file.
    ```cpp
    void process_file(const std::string &file_path);
    ```
    - **Parameters**: `file_path` - The path of the file to be processed.
    - **Description**: Reads the file content and then deletes the file. Logs the operations performed.

- **receiver**: Main function to handle file reading and deleting.
    ```cpp
    void receiver(bool waitForFiles);
    ```
    - **Parameters**: `waitForFiles` - A boolean flag to keep the receiver running and waiting for new files.
    - **Description**: Monitors the directory for new files, processes them, and logs statistics.

### Test Sender Application

- **FileCountValidationTest**: Checks the count of files generated.
    ```cpp
    TEST(SenderTest, FileCountValidationTest);
    ```
    - **Description**: Validates the number of files created by the sender.

- **FileSizeValidationTest**: Validates the size of the files created.
    ```cpp
    TEST(SenderTest, FileSizeValidationTest);
    ```
    - **Description**: Ensures the files created are of the expected size.

- **DirectoryCreationTest**: Tests the creation of directories.
    ```cpp
    TEST(SenderTest, DirectoryCreationTest);
    ```
    - **Description**: Validates that directories are created correctly.

- **RenameFileTest**: Tests the renaming of files.
    ```cpp
    TEST(SenderTest, RenameFileTest);
    ```
    - **Description**: Ensures files are renamed correctly.

- **FileCreationTime**: Performance test for file creation.
    ```cpp
    TEST(SenderPerformanceTest, FileCreationTime);
    ```
    - **Description**: Measures the time taken to create files and ensures it is within acceptable limits.

- **FileRenamingTime**: Performance test for file renaming.
    ```cpp
    TEST(SenderPerformanceTest, FileRenamingTime);
    ```
    - **Description**: Measures the time taken to rename files and ensures it is within acceptable limits.

---

Here's the final part of the README file:

---

### Test Receiver Application

- **ReadFileTest**: Tests file reading.
    ```cpp
    TEST(ReceiverTest, ReadFileTest);
    ```
    - **Description**: Validates that files are read correctly.

- **DeleteFileTest**: Tests file deletion.
    ```cpp
    TEST(ReceiverTest, DeleteFileTest);
    ```
    - **Description**: Ensures files are deleted correctly.

- **ProcessFileTest**: Tests file processing (read + delete).
    ```cpp
    TEST(ReceiverTest, ProcessFileTest);
    ```
    - **Description**: Validates that files are processed correctly.

- **DirectoryCreationTest**: Tests the creation of directories.
    ```cpp
    TEST(ReceiverTest, DirectoryCreationTest);
    ```
    - **Description**: Validates that directories are created correctly.

- **FileReadingTime**: Performance test for file reading.
    ```cpp
    TEST(ReceiverPerformanceTest, FileReadingTime);
    ```
    - **Description**: Measures the time taken to read files and ensures it is within acceptable limits.

- **FileDeletionTime**: Performance test for file deletion.
    ```cpp
    TEST(ReceiverPerformanceTest, FileDeletionTime);
    ```
    - **Description**: Measures the time taken to delete files and ensures it is within acceptable limits.

## Logging Integration

The project integrates the **spdlog** library to handle logging. The logging configuration is flexible and can be adjusted through the configuration file.

### How to Integrate Logging

1. **Include the spdlog header**:
    ```cpp
    #include <spdlog/spdlog.h>
    #include <spdlog/sinks/basic_file_sink.h>
    ```

2. **Setup the logger**:
    ```cpp
    void setup_logger(const std::string &logger_name, const std::string &file_name, const std::string &log_level) {
        auto file_logger = spdlog::basic_logger_mt(logger_name, file_name);
        spdlog::set_default_logger(file_logger);
        spdlog::set_level(spdlog::level::from_str(log_level));
    }
    ```

3. **Use the logger in your code**:
    ```cpp
    spdlog::info("This is an info message");
    spdlog::error("This is an error message");
    ```

### Configurable Log Severity

The log severity can be configured through the `values.config` file:
```plaintext
LOGGER_LEVEL_SET trace
```
This setting allows you to control the verbosity of the logs, ranging from `trace` (most verbose) to `critical` (least verbose).

## Goals and What I Learned

### Goals

- Develop a robust file processing system that can handle file creation, writing, reading, and processing efficiently.
- Implement efficient file handling and logging mechanisms.
- Ensure the system is configurable and extensible to accommodate future changes and enhancements.
- Provide comprehensive unit and performance testing to ensure the reliability and efficiency of the system.

### What I Learned

- **CMake**: How to use CMake for building C++ projects, managing dependencies, and organizing project structure.
- **spdlog**: Implementing logging with spdlog to provide detailed logs and configurable log levels.
- **Google Test**: Writing unit tests with Google Test to ensure the correctness of the code and validate functionality.
- **File Operations**: Handling file operations such as creation, reading, renaming, and deletion in C++.
- **Multithreading**: Implementing multithreading to run the sender and receiver applications concurrently for efficient file processing.
- **Configuration Management**: Using configuration files to make the system flexible and easily configurable without modifying the code.

---





