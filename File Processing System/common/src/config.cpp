#include "config.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <filesystem>

std::string BUFFER_DIR;
std::map<std::string, std::string> configMap;
std::string FINAL_FILE_EXTENSION;
std::string FILE_NAME;
std::string LOGGER_LEVEL_SET;

void loadConfig() {
    try {
        std::cout << "Current working directory: " << std::filesystem::current_path() << std::endl;
        
        std::ifstream configFile("../config/values.config"); // Adjusted for running from build directory
        if (!configFile.is_open()) {
            throw std::runtime_error("Unable to open config file");
        }

        std::string line;
        while (std::getline(configFile, line)) {
            std::istringstream iss(line);
            std::string key, value;
            if (!(iss >> key >> value)) {
                std::cerr << "Skipping invalid line: " << line << std::endl;
                continue; // Skip lines that don't match the expected format
            }
            configMap[key] = value;
        }
        configFile.close();
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

std::string getConfigValue(const std::string& key, const std::string& defaultValue) {
    auto it = configMap.find(key);
    if (it != configMap.end()) {
        return it->second;
    } else {
        std::cerr << "Key not found: " << key << ". Using default value: " << defaultValue << std::endl;
        return defaultValue;
    }
}

std::vector<int> splitAndConvertToIntArray(const std::string& str, char delimiter) {
    std::vector<int> intArray;
    std::string token;
    std::istringstream tokenStream(str);
    while (std::getline(tokenStream, token, delimiter)) {
        try {
            intArray.push_back(std::stoi(token));
        } catch (const std::invalid_argument& e) {
            std::cerr << "Invalid number: " << token << std::endl;
        } catch (const std::out_of_range& e) {
            std::cerr << "Number out of range: " << token << std::endl;
        }
    }
    return intArray;
}