#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include <vector>

class Logger {
    private:
        std::vector<std::string> logi;

    public:
        void DodajLog(const std::string& log);
        void WyswietlLogi() const;
};

#endif