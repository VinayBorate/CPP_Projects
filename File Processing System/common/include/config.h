#ifndef CONFIG_H
#define CONFIG_H

#include <string>
#include <map>
#include <vector>

extern std::string BUFFER_DIR;
extern std::map<std::string, std::string> configMap;
extern std::string FINAL_FILE_EXTENSION;
extern std::string FILE_NAME;
extern std::string LOGGER_LEVEL_SET;

void loadConfig();
std::string getConfigValue(const std::string& key, const std::string& defaultValue = "");
std::vector<int> splitAndConvertToIntArray(const std::string& str, char delimiter = '|');

#endif // CONFIG_H