-- Отключаем предупреждения (опционально)
SET client_min_messages TO WARNING;

-- Запускаем все файлы по порядку
\i 1_create_tables.sql
\i 2_insert_data.sql
\i 3_create_indexes.sql
\i 4_create_views.sql
\i 5_transactions.sql

-- Проверяем создание
SELECT 'Таблицы:' as check_message;
SELECT table_name FROM information_schema.tables 
WHERE table_schema = 'public' 
ORDER BY table_name;

SELECT '' as check_message;
SELECT 'Индексы:' as check_message;
SELECT indexname, tablename FROM pg_indexes 
WHERE schemaname = 'public' 
ORDER BY tablename, indexname;

SELECT '' as check_message;
SELECT 'Представления:' as check_message;
SELECT table_name as view_name FROM information_schema.views 
WHERE table_schema = 'public';

-- Запускаем тестовые запросы
SELECT '' as check_message;
SELECT '=== ТЕСТОВЫЕ ЗАПРОСЫ ===' as check_message;

-- Запрос 1
SELECT '' as check_message;
SELECT '1. 5 одногруппников студента ID=3:' as check_message;
WITH student_group AS (
    SELECT student_id, full_name, group_number
    FROM students 
    WHERE group_number = (SELECT group_number FROM students WHERE student_id = 3)
),
ranked_students AS (
    SELECT 
        student_id,
        full_name,
        ROW_NUMBER() OVER (ORDER BY student_id) as row_num
    FROM student_group
)
SELECT student_id, full_name FROM ranked_students
WHERE row_num BETWEEN 
    (SELECT row_num FROM ranked_students WHERE student_id = 3) - 2
    AND 
    (SELECT row_num FROM ranked_students WHERE student_id = 3) + 3
AND student_id != 3
ORDER BY student_id
LIMIT 5;

-- Запрос 2
SELECT '' as check_message;
SELECT '2. Средний балл студента ID=2:' as check_message;
SELECT * FROM student_avg_grades WHERE student_id = 2;

-- Запрос 3
SELECT '' as check_message;
SELECT '3. Средний балл по Информатике:' as check_message;
SELECT 
    s.subject_name,
    ROUND(AVG(g.grade)::numeric, 2) as average_grade
FROM subjects s
JOIN grades g ON s.subject_id = g.subject_id
WHERE s.subject_name = 'Информатика'
GROUP BY s.subject_id, s.subject_name;

-- Запрос 4
SELECT '' as check_message;
SELECT '4. Поиск заметок по слову "информатика":' as check_message;
SELECT s.full_name, n.note_text 
FROM notes n
JOIN students s ON n.student_id = s.student_id
WHERE n.note_text_tsvector @@ to_tsquery('russian', 'информатика')
LIMIT 3;

SELECT '' as check_message;
SELECT '=== НАСТРОЙКА ЗАВЕРШЕНА ===' as check_message;