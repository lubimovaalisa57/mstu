#include "date_converter.h"
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <ctime>

std::string convertToDateFormat(const std::string& date_str) {
    std::tm tm = {};
    std::stringstream ss(date_str);

    // Преобразование строки в структуру tm (формат: YYYY-MM-DD)
    ss >> std::get_time(&tm, "%Y-%m-%d");

    if (ss.fail()) {
        std::cerr << "Ошибка при преобразовании даты: " << date_str << std::endl;
        return "";
    }

    // Преобразуем обратно в строку для использования в запросах
    std::ostringstream oss;
    oss << std::put_time(&tm, "%Y-%m-%d");
    return oss.str();
}