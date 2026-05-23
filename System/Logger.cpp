#include "Logger.h"
#include <iostream>

void Logger::DodajLog(const std::string& log) {
    logi.push_back(log);
}

void Logger::WyswietlLogi() const {
    for (const auto& log : logi) {
        std::cout << log << std::endl;
    }
}