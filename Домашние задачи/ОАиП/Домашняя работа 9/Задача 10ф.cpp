#include <iostream>
#include <fstream>
#include <string>

void createConfig() 
{
    std::ofstream file("config.json");
    file << "{\n";
    file << " \"app_name\": \"My Application\",\n";
    file << " \"version\": \"1.0.0\",\n";
    file << " \"settings\": {\n";
    file << " \"max_connections\": 100,\n";
    file << " \"timeout\": 30,\n";
    file << " \"debug_mode\": true\n";
    file << " },\n";
    file << " \"database\": {\n";
    file << " \"host\": \"localhost\",\n";
    file << " \"port\": 5432,\n";
    file << " \"username\": \"admin\"\n";
    file << " }\n";
    file << "}";
    file.close();
    std::cout << "Конфигурационный файл создан\n";
}

void readConfig() 
{
    std::ifstream file("config.json");
    std::string line;
    while (std::getline(file, line)) {
        std::cout << line << std::endl;
    }
    file.close();
}

void updateConfig() 
{
    std::ifstream in("config.json");
    std::string content;
    std::string line;
    
    while (std::getline(in, line)) {
        if (line.find("\"timeout\"") != std::string::npos) {
            line = " \"timeout\": 60,";
        }
        content += line + "\n";
    }
    in.close();
    
    std::ofstream out("config.json");
    out << content;
    out.close();
    std::cout << "Конфигурация обновлена\n";
}

int main() 
{
    createConfig();
    readConfig();
    updateConfig();
    readConfig();
    
    return 0;
}