#include <iostream>
#include <fstream>

int main() 
{
    int numbers[] = {15, 23, 7, 42, 18, 91, 3, 56, 77, 10};
    
    // Запись в бинарный файл
    std::ofstream out("numbers.bin", std::ios::binary);
    out.write(reinterpret_cast<char*>(numbers), sizeof(numbers));
    out.close();
    
    // Чтение из бинарного файла
    std::ifstream in("numbers.bin", std::ios::binary);
    in.seekg(0, std::ios::end);
    size_t file_size = in.tellg();
    in.seekg(0, std::ios::beg);
    
    int buffer[10];
    in.read(reinterpret_cast<char*>(buffer), sizeof(buffer));
    in.close();
    
    // Вывод результатов
    int sum = 0;
    for (int i = 0; i < 10; i++) {
        std::cout << buffer[i] << " ";
        sum += buffer[i];
    }
    std::cout << std::endl;
    
    std::cout << "Размер файла: " << file_size << " байт" << std::endl;
    std::cout << "Сумма чисел: " << sum << std::endl;
    
    return 0;
}