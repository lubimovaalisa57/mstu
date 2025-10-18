#!/bin/bash

# Проверяем, что аргумент передан
if [ $# -eq 0 ]; then
    echo "Ошибка: Пожалуйста, укажите имя процесса в качестве аргумента"
    exit 1
fi

# Сохраняем имя процесса в переменную
process_name=$1

# Используем pgrep для поиска процесса
if pgrep "$process_name" > /dev/null; then
    echo "Процесс '$process_name' запущен"
else
    echo "Процесс '$process_name' не найден"
fi
