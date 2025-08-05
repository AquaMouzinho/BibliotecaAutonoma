#pragma once
#include <ctime>
#include <iomanip>
#include <sstream>
#include <string>

class DateTimeUtils {
public:
    static std::string getCurrentDateTime() {
        auto now = std::time(nullptr);
        auto tm = *std::localtime(&now);
        std::ostringstream oss;
        oss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S");
        return oss.str();
    }
};