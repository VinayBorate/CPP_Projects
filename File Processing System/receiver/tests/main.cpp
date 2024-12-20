#include <spdlog/spdlog.h>

int main() {
    spdlog::info("Welcome to spdlog!");
    spdlog::warn("This is a warning message.");
    spdlog::error("This is an error message.");
    return 0;
}



//g++ -I../../lib -I../../lib/spdlog main.cpp -o main -L../../lib -lspdlog