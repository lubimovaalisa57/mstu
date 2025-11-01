#include <iostream>

void parseTelemetry(const char* data) {
    const char* p = data;  // указатель для прохода по строке
    
    while (*p != '\0') {
        while (*p == ' ') p++;
        
        // Читаем имя параметра
        char name[32];
        char* name_ptr = name;
        while (*p != ':' && *p != '\0') {
            *name_ptr = *p;
            name_ptr++;
            p++;
        }
        *name_ptr = '\0';
        
        if (*p == ':') p++; 
        
        // Читаем значение параметра
        char value[32];
        char* value_ptr = value;
        while (*p != ';' && *p != '\0') {
            *value_ptr = *p;
            value_ptr++;
            p++;
        }
        *value_ptr = '\0';
        
        if (*p == ';') p++; 
        
        // Преобразуем сокращенные имена в полные
        const char* full_name = "";
        if (name[0] == 'T' && name[1] == 'E' && name[2] == 'M' && name[3] == 'P') {
            full_name = "Temperature";
        } else if (name[0] == 'P' && name[1] == 'R' && name[2] == 'E' && name[3] == 'S' && name[4] == 'S') {
            full_name = "Pressure";
        } else if (name[0] == 'H' && name[1] == 'U' && name[2] == 'M') {
            full_name = "Humidity";
        } else {
            full_name = name; 
        }
    
        std::cout << full_name << ": " << value << std::endl;
    }
}

int main() 
{
    const char* data = "TEMP:24.5;PRESS:101.3;HUM:55.2";
    parseTelemetry(data);
    
    return 0;
}