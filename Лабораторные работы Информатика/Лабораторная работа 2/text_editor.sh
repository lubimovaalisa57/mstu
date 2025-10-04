#!/bin/bash
echo "Текстовый редактор запущен. Вводите текст (для завершения введите 'exit'):"
while true; do
	 read input_text
	if [ "$input_text" = "exit" ]; then
        	break
	fi
echo "$input_text" >> notes.txt
done

echo ""
echo "Содержимое файла notes.txt:"
echo "==========================="

cat notes.txt

echo ""
echo "Удаление файла notes.txt..."

rm notes.txt

echo "Файл notes.txt удален. Программа завершена."
