#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

int main() 
{
    std::vector<std::vector<double>> temp(5, std::vector<double>(30));
    std::vector<std::vector<double>> pressure(5, std::vector<double>(100));
    
    // Пример данных для температур (5 каналов по 30 значений)
    temp[0] = {25.1, 25.3, 25.5, 25.7, 25.9, 26.1, 26.3, 26.5, 26.7, 26.9,
               27.1, 27.3, 27.5, 27.7, 27.9, 28.1, 28.3, 28.5, 28.7, 28.9,
               29.1, 29.3, 29.5, 29.7, 29.9, 30.1, 30.3, 30.5, 30.7, 30.9};
               
    temp[1] = {20.5, 21.0, 21.5, 22.0, 22.5, 23.0, 23.5, 24.0, 24.5, 25.0,
               25.5, 26.0, 26.5, 27.0, 27.5, 28.0, 28.5, 29.0, 29.5, 30.0,
               30.5, 31.0, 31.5, 32.0, 32.5, 33.0, 33.5, 34.0, 34.5, 35.0};
               
    temp[2] = {30.0, 30.2, 30.4, 30.6, 30.8, 31.0, 31.2, 31.4, 31.6, 31.8,
               32.0, 32.2, 32.4, 32.6, 32.8, 33.0, 33.2, 33.4, 33.6, 33.8,
               34.0, 34.2, 34.4, 34.6, 34.8, 35.0, 35.2, 35.4, 35.6, 35.8};
               
    temp[3] = {15.0, 16.0, 17.0, 18.0, 19.0, 20.0, 21.0, 22.0, 23.0, 24.0,
               25.0, 26.0, 27.0, 28.0, 29.0, 30.0, 31.0, 32.0, 33.0, 34.0,
               35.0, 36.0, 37.0, 38.0, 39.0, 40.0, 41.0, 42.0, 43.0, 44.0};
               
    temp[4] = {28.0, 28.1, 28.2, 28.3, 28.4, 28.5, 28.6, 28.7, 28.8, 28.9,
               29.0, 29.1, 29.2, 29.3, 29.4, 29.5, 29.6, 29.7, 29.8, 29.9,
               30.0, 30.1, 30.2, 30.3, 30.4, 30.5, 30.6, 30.7, 30.8, 30.9};
    
    // Пример данных для давлений (5 каналов по 100 значений)
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 100; ++j) {
            pressure[i][j] = (i + 1) * 2.0 + j * 0.1;
        }
    }
    
    // Средняя температура для каждого канала
    std::vector<double> avg_temp(5);
    std::transform(temp.begin(), temp.end(), avg_temp.begin(),
                  [](const std::vector<double>& channel) {
                      return std::accumulate(channel.begin(), channel.end(), 0.0) / channel.size();
                  });
    
    std::cout << "\nСредние температуры по каналам: ";
    for (int i = 0; i < 5; ++i) {
        std::cout << "Канал " << i << ": " << avg_temp[i] << "°C";
        if (i < 4) std::cout << ", ";
    }
    std::cout << std::endl;
    
    // Минимальное давление для каждого канала
    std::vector<double> min_pressure(5);
    std::transform(pressure.begin(), pressure.end(), min_pressure.begin(),
                  [](const std::vector<double>& channel) {
                      return *std::min_element(channel.begin(), channel.end());
                  });
    
    // Максимальное давление для каждого канала
    std::vector<double> max_pressure(5);
    std::transform(pressure.begin(), pressure.end(), max_pressure.begin(),
                  [](const std::vector<double>& channel) {
                      return *std::max_element(channel.begin(), channel.end());
                  });
    
    std::cout << "\nМинимальные давления: ";
    for (int i = 0; i < 5; ++i) {
        std::cout << "Канал " << i << ": " << min_pressure[i] << " бар";
        if (i < 4) std::cout << ", ";
    }
    std::cout << std::endl;
    
    std::cout << "Максимальные давления: ";
    for (int i = 0; i < 5; ++i) {
        std::cout << "Канал " << i << ": " << max_pressure[i] << " бар";
        if (i < 4) std::cout << ", ";
    }
    std::cout << std::endl;
    
    // Канал с наибольшей вариацией температуры
    std::vector<double> temp_variation(5);
    std::transform(temp.begin(), temp.end(), temp_variation.begin(),
                  [](const std::vector<double>& channel) {
                      auto min_it = std::min_element(channel.begin(), channel.end());
                      auto max_it = std::max_element(channel.begin(), channel.end());
                      return *max_it - *min_it;
                  });
    
    auto max_var_it = std::max_element(temp_variation.begin(), temp_variation.end());
    int max_var_channel = std::distance(temp_variation.begin(), max_var_it);
    std::cout << "\nКанал с наибольшей вариацией температуры: " << max_var_channel 
              << " (вариация: " << *max_var_it << "°C)" << std::endl;
    
    // Нормализация давлений
    std::vector<std::vector<double>> normalized_pressure(5, std::vector<double>(100));
    for (int i = 0; i < 5; ++i) {
        double min_val = min_pressure[i];
        double max_val = max_pressure[i];
        std::transform(pressure[i].begin(), pressure[i].end(), normalized_pressure[i].begin(),
                      [min_val, max_val](double val) { 
                          return (val - min_val) / (max_val - min_val); 
                      });
    }
    
    // Пики давления после нормализации (> 0.9)
    std::cout << "\nПики давления (нормализованные > 0.9):" << std::endl;
    for (int i = 0; i < 5; ++i) {
        std::cout << "Канал " << i << ": ";
        std::for_each(normalized_pressure[i].begin(), normalized_pressure[i].end(),
                     [](double val) { 
                         if (val > 0.9) {
                             std::cout << val << " ";
                         }
                     });
        std::cout << std::endl;
    }
    
    // Канал с максимальной средней температурой
    std::vector<int> indices(5);
    std::iota(indices.begin(), indices.end(), 0);
    std::sort(indices.begin(), indices.end(),
             [&avg_temp](int a, int b) { return avg_temp[a] > avg_temp[b]; });
    
    std::cout << "\nКанал с максимальной средней температурой: " << indices[0] 
              << " (температура: " << avg_temp[indices[0]] << "°C)" << std::endl;
    
    return 0;
}