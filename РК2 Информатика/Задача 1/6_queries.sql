
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
SELECT 
    student_id,
    full_name,
    row_num
FROM ranked_students
WHERE row_num BETWEEN 
    (SELECT row_num FROM ranked_students WHERE student_id = 3) - 2
    AND 
    (SELECT row_num FROM ranked_students WHERE student_id = 3) + 3
AND student_id != 3  -- Исключаем самого студента
ORDER BY student_id
LIMIT 5;

SELECT
    full_name,
    group_number,
    average_grade,
    total_grades
FROM student_avg_grades
WHERE student_id = 2;

SELECT 
    s.subject_name,
    ROUND(AVG(g.grade)::numeric, 2) as average_grade,
    COUNT(g.grade_id) as total_grades,
    MIN(g.grade) as min_grade,
    MAX(g.grade) as max_grade,
    COUNT(CASE WHEN g.grade = 5 THEN 1 END) as excellent_count,
    COUNT(CASE WHEN g.grade = 2 THEN 1 END) as fail_count
FROM subjects s
JOIN grades g ON s.subject_id = g.subject_id
WHERE s.subject_name = 'Информатика'
GROUP BY s.subject_id, s.subject_name;

-- 4. Выполнить полнотекстовый поиск по заметкам, содержащим слово «Информатика»
-- Вариант 1: Используя GIN индекс (быстрее)
SELECT 
    n.note_id,
    s.full_name,
    s.group_number,
    n.note_text,
    n.created_at,
    ts_headline('russian', n.note_text, to_tsquery('russian', 'информатика')) as highlighted_text
FROM notes n
JOIN students s ON n.student_id = s.student_id
WHERE n.note_text_tsvector @@ to_tsquery('russian', 'информатика')
ORDER BY n.created_at DESC;

DO $$
BEGIN
    -- Начало транзакции
    BEGIN
        RAISE NOTICE 'Начало транзакции по обновлению посещаемости';
        
        -- Показываем текущее состояние
        RAISE NOTICE 'Текущая посещаемость студента 5 на 2024-03-01:';
        
        SELECT * INTO current_status 
        FROM attendance 
        WHERE student_id = 5 AND date_attended = '2024-03-01';
        
        -- Обновляем статус посещаемости
        UPDATE attendance 
        SET status = 'present'
        WHERE student_id = 5 AND date_attended = '2024-03-01';
        
        -- Проверяем, была ли обновлена запись
        IF NOT FOUND THEN
            -- Если записи не было, создаем новую
            INSERT INTO attendance (student_id, date_attended, status)
            VALUES (5, '2024-03-01', 'present');
            RAISE NOTICE 'Создана новая запись о посещаемости';
        ELSE
            RAISE NOTICE 'Запись о посещаемости обновлена';
        END IF;
        
        -- Фиксируем транзакцию
        COMMIT;
        
        -- Показываем результат
        RAISE NOTICE 'Результат после обновления:';
        
    EXCEPTION
        WHEN OTHERS THEN
            ROLLBACK;
            RAISE EXCEPTION 'Ошибка при обновлении посещаемости: %', SQLERRM;
    END;
END $$;

-- Дополнительные запросы для проверки

-- Просмотр всех студентов со средними баллами
SELECT * FROM student_avg_grades;

-- Топ-3 студента по успеваемости
SELECT * FROM student_avg_grades 
ORDER BY average_grade DESC 
LIMIT 3;

-- Статистика по группам
SELECT 
    group_number,
    COUNT(*) as student_count,
    ROUND(AVG(average_grade)::numeric, 2) as group_avg_grade
FROM student_avg_grades
GROUP BY group_number
ORDER BY group_avg_grade DESC;

-- Все оценки по информатике
SELECT * FROM detailed_grades 
WHERE subject_name = 'Информатика'
ORDER BY grade DESC;

-- Статистика посещаемости
SELECT * FROM attendance_stats;