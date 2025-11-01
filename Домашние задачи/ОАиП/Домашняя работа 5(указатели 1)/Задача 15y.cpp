#include <iostream>
#include <vector>
#include <string>

struct Command 
{
    std::string name;  // название команды
    int value;         // числовой параметр (0, если нет)
};

// Функция разбора командной строки
void parseCommand(const char* input, std::vector<Command>& buffer) 
{
    const char* p = input;  // указатель для прохода по строке
    Command cmd;
    cmd.value = 0;  // значение по умолчанию
    
    // Считываем имя команды (до пробела)
    std::string name;
    while (*p != '\0' && *p != ' ') {
        name += *p;
        p++;
    }
    cmd.name = name;
    
    // Если есть пробел - считываем число
    if (*p == ' ') {
        p++; 
        
        int num = 0;
        // Считываем цифры и преобразуем в число
        while (*p != '\0' && *p >= '0' && *p <= '9') {
            num = num * 10 + (*p - '0');
            p++;
        }
        cmd.value = num;
    }
    
    // Добавляем команду в буфер
    buffer.push_back(cmd);
}

int main() 
{
    std::vector<Command> buffer;
    
    // Разбираем команды и добавляем в буфер
    parseCommand("FORWARD 10", buffer);
    parseCommand("TURN 90", buffer);
    parseCommand("STOP", buffer);
    
    // Выводим все команды из буфера
    for (const auto& cmd : buffer) {
        std::cout << "Command: " << cmd.name << ", Value: " << cmd.value << std::endl;
    }
    
    return 0;
}