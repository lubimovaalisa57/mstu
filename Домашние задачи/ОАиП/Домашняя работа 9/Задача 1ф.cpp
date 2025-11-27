#include <iostream>
#include <fstream>
#include <string>
#include <vector>

int main() 
{
    std::ifstream file("book.txt");
    std::string word = "герой";
    std::vector<std::pair<int, int>> positions;
    int count = 0;

    std::string line;
    int lineNumber = 1;
    
    while (std::getline(file, line)) {
        size_t pos = 0;
        while ((pos = line.find(word, pos)) != std::string::npos) {
            positions.push_back({lineNumber, static_cast<int>(pos) + 1});
            count++;
            pos += word.length();
        }
        lineNumber++;
    }
    file.close();

    std::ofstream out("results.txt");
    for (const auto& p : positions) {
        out << p.first << " " << p.second << " " << word << std::endl;
    }
    out.close();

    std::cout << "Total: " << count << std::endl;
    return 0;
}