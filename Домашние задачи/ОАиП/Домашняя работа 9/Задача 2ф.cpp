#include <iostream>
#include <fstream>
#include <string>

int main() 
{
    std::fstream file("config.txt", std::ios::in | std::ios::out);
    std::string key = "timeout=";
    std::string newValue = "60";

    std::string line;
    long pos;
    
    while (std::getline(file, line)) {
        if (line.find(key) == 0) {
            pos = file.tellp() - line.length() - 1;
            file.seekp(pos);
            file << key << newValue << std::endl;
            break;
        }
    }
    
    file.close();
    return 0;
}