#include <iostream>
#include <memory>
#include <vector>
#include <string>

int main() 
{
    // Создание частей отчета
    auto part1 = std::make_unique<std::string>("Sensor data:");
    auto part2 = std::make_unique<std::string>("Voltage stable.");
    auto part3 = std::make_unique<std::string>("System nominal.");
    
    // Вектор умных указателей
    std::vector<std::unique_ptr<std::string>> reportParts;
    reportParts.push_back(std::move(part1));
    reportParts.push_back(std::move(part2));
    reportParts.push_back(std::move(part3));
    
    // Лямбда для объединения строк
    auto concatParts = [&]() -> std::string {
        std::string result;
        for (const auto& part : reportParts) {
            result += *part + "\n";
        }
        return result;
    };
    
    // Лямбда для подсчета слова
    auto countWord = [](const std::string& text, const std::string& word) -> int {
        int count = 0;
        size_t pos = 0;
        while ((pos = text.find(word, pos)) != std::string::npos) {
            count++;
            pos += word.length();
        }
        return count;
    };
    
    // Выполнение операций
    std::string report = concatParts();
    int dataCount = countWord(report, "data");
    
    // Вывод результатов
    std::cout << "Отчёт:\n" << report;
    std::cout << "Слово \"data\" встречается " << dataCount << " раз" << std::endl;
    
    return 0;
}