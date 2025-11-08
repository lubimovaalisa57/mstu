#include <iostream>

// Функция для сортировки указателей на строки
void sortWords(char **words, int n) 
{
    // Сортировка пузырьком указателей на строки
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            // Сравниваем строки с помощью strcmp
            if (strcmp(words[j], words[j + 1]) > 0) {
                // Меняем местами указатели на строки
                char *temp = words[j];
                words[j] = words[j + 1];
                words[j + 1] = temp;
            }
        }
    }
}

int main() 
{
    // Создаем массив из 7 строк
    const int n = 7;
    char **words = new char*[n];
    
    // Инициализируем строки
    words[0] = new char[10]; strcpy(words[0], "banana");
    words[1] = new char[10]; strcpy(words[1], "apple");
    words[2] = new char[10]; strcpy(words[2], "grape");
    words[3] = new char[10]; strcpy(words[3], "cherry");
    words[4] = new char[10]; strcpy(words[4], "orange");
    words[5] = new char[10]; strcpy(words[5], "pear");
    words[6] = new char[10]; strcpy(words[6], "kiwi");
    
    // Вывод исходного массива
    std::cout << "Исходный массив: " << std::endl;
    for (int i = 0; i < n; i++) {
        std::cout << words[i] << " ";
    }
    std::cout << std::endl;
    
    // Сортировка указателей на строки
    sortWords(words, n);
    
    // Вывод отсортированного массива
    std::cout << "Отсортированный массив:" << std::endl;
    for (int i = 0; i < n; i++) {
        std::cout << words[i] << " ";
    }
    std::cout << std::endl;
    
    // Освобождение памяти
    for (int i = 0; i < n; i++) {
        delete[] words[i];
    }
    delete[] words;
    
    return 0;
}