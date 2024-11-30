
---
# **Assignment - 1 **
# **File Processing System**  

## **Project Description**  
This project is a file processing system consisting of a **sender** and **receiver** that perform file operations such as **creation**, **reading**, **renaming**, and **deletion**. It also includes comprehensive **unit testing** and **performance testing** using **Google Test (GTest)** to ensure functionality and efficiency.  

---

## **Technology and Frameworks Used**  
- **Programming Language:** C++ (C++17)  
- **Build System:** CMake  
- **Testing Framework:** Google Test (GTest)  
- **Standard Libraries:** `<filesystem>`, `<fstream>`, `<iostream>`, `<chrono>`  
- **Development Environment:** Compatible with Linux and Windows  

---

## **Project Structure**  
```plaintext
.
├── CMakeLists.txt
├── Readme.md
├── build
├── lib
│   ├── gtest
│   ├── libgtest.a
│   └── libgtest_main.a
├── receiver
│   ├── include
│   │   └── receiver.h
│   ├── src
│   │   └── receiver.cpp
│   └── tests
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

## **Steps to Run the Project**  

1. **Clone the Repository**  
   ```bash
   git clone https://github.com/yourusername/yourproject.git
   cd yourproject
   ```

2. **Build the Project**  
   Ensure you have `CMake` installed on your system.  
   ```bash
   mkdir build
   cd build
   cmake ..
   make
   ```

3. **Run the Executables**  
   - **Sender:**  
     ```bash
     ./sender
     ```
   - **Receiver:**  
     ```bash
     ./receiver
     ```

4. **Run Tests**  
   Use Google Test for unit and performance testing:  
   - **Sender Tests:**  
     ```bash
     ./test_sender
     ```
   - **Receiver Tests:**  
     ```bash
     ./test_receiver
     ```

---

## **Technical Details**  

### **receiver.cpp**  
Handles tasks like:  
1. **Reading Files:** Reads files from the buffer directory.  
   - `read_file(const std::string &file_path, long long &read_time_ms)`  
2. **Deleting Files:** Deletes files after processing.  
   - `delete_file(const std::string &file_path, long long &delete_time_ms)`  
3. **Processing Files:** Combines reading and deleting operations with a simulated processing delay.  
   - `process_file(const std::string &file_path)`  
4. **Creating Directories:** Ensures the buffer directory exists.  
   - `create_directory_if_not_exists_by_receiver(const std::string &path)`  
5. **Logging Statistics:** Logs stats after processing a certain number of files.  
   - `log_statistics(int file_count, long long total_read_time_ms, long long total_delete_time_ms)`  

---

### **sender.cpp**  
Handles tasks like:  
1. **Creating Files:** Generates files of specified sizes.  
   - `create_file(const std::string &file_path, int size_in_mb)`  
2. **Renaming Files:** Renames temporary files to final names.  
   - `rename_file(const std::string &old_name, const std::string &new_name)`  
3. **Creating Directories:** Ensures the buffer directory exists.  
   - `create_directory_if_not_exists_by_sender(const std::string &path)`  
4. **Sending Files:** Manages the creation and renaming of files in a loop.  
   - `sender(bool waitForUserInput)`  
5. **Logging Statistics:** Logs statistics after creating a certain number of files.  

---

### **test_sender.cpp**  
Conducts the following tests:  
1. **File Generation Limit Test:** Verifies the sender creates the correct number of files.  
2. **File Creation Test:** Ensures files are created with the correct sizes.  
3. **Directory Creation Test:** Checks the buffer directory is created if it doesn't exist.  
4. **File Renaming Test:** Verifies files are renamed correctly.  
5. **File Creation Time Test:** Measures the time taken to create a file.  
6. **File Renaming Time Test:** Measures the time taken to rename a file.  

---

### **test_receiver.cpp**  
Conducts the following tests:  
1. **Read File Test:** Verifies that files are read correctly.  
2. **Delete File Test:** Ensures files are deleted after processing.  
3. **Process File Test:** Tests combined read and delete operations.  
4. **Directory Creation Test:** Ensures the buffer directory is created if it doesn't exist.  
5. **File Reading Time Test:** Measures the time taken to read a file.  
6. **File Deletion Time Test:** Measures the time taken to delete a file.  

---

## **Testing**  
This project includes comprehensive **unit testing** and **performance testing**:  
1. **Unit Testing:**  
   - Verifies individual components of `sender.cpp` and `receiver.cpp`.  
2. **Performance Testing:**  
   - Validates efficiency for large-scale file operations (e.g., creating, reading, deleting 100 MB files).  
   - Ensures operations are performed within acceptable thresholds.  

Run the test executables (`test_sender` and `test_receiver`) to see detailed logs and assertions.  

---

## **Goals and What I Learned**  

### **Goals Achieved**  
- Built a complete file processing system for handling real-world scenarios.  
- Ensured efficient file operations with detailed logging and performance metrics.  
- Designed a robust and testable system using Google Test and CMake.  

### **Lessons Learned**  
1. **Efficient File Handling:** Improved skills in handling file systems using C++.  
2. **Testing Practices:** Understood the value of rigorous unit and performance testing.  
3. **CMake Expertise:** Enhanced knowledge of multi-component build systems.  
4. **Problem-Solving Skills:** Gained experience in addressing concurrency and I/O challenges.  

---

Feel free to contribute or suggest improvements!  

**[Vinay Borate ](https://github.com/VinayBorate)**  

--- 
