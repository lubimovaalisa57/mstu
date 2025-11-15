#include <iostream>
#include <memory>
#include <vector>
#include <algorithm>

int main() 
{
    // Исходный вектор логов
    std::vector<std::string> logs = {
        "INFO: Start",
        "ERROR: Disk failure",
        "WARNING: Low memory",
        "ERROR: Disk failure",
        "INFO: Stop"
    };
    
    // Обертка в shared_ptr
    auto pLogs = std::make_shared<std::vector<std::string>>(logs);
    
    // Фильтрация ошибок с помощью лямбды
    std::vector<std::string> errors;
    std::copy_if(pLogs->begin(), pLogs->end(), std::back_inserter(errors),
        [](const std::string& log) {
            return log.find("ERROR") != std::string::npos;
        });
    
    // Удаление дубликатов
    std::sort(errors.begin(), errors.end());
    auto last = std::unique(errors.begin(), errors.end());
    errors.erase(last, errors.end());
    
    // Вывод исходного журнала
    std::cout << "Исходный журнал:" << std::endl;
    for (const auto& log : *pLogs) {
        std::cout << log << std::endl;
    }
    
    // Вывод ошибок
    std::cout << "Ошибки:" << std::endl;
    for (const auto& error : errors) {
        std::cout << error << std::endl;
    }
    
    return 0;
}