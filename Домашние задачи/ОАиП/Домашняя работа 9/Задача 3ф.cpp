#include <iostream>
#include <fstream>
#include <vector>
#include <string>

int main() 
{
    std::ifstream input("application.log");
    std::vector<std::string> parts;
    int partNum = 1;
    std::string line;
    
    while (std::getline(input, line)) {
        std::string filename = "log_part" + std::to_string(partNum) + ".txt";
        parts.push_back(filename);
        
        std::ofstream output(filename);
        output << line;
        output.close();
        
        partNum++;
    }
    
    input.close();
    
    std::ofstream index("log_index.txt");
    for (const auto& file : parts) {
        index << file << std::endl;
    }
    index.close();
    
    return 0;
}