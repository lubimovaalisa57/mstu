#!/bin/bash

echo "Введите число для обратного отсчета:"
read number

echo "Обратный отсчет:"

for ((i=number; i>=1; i--)); do
    echo "$i"
done

echo "Готово!"
