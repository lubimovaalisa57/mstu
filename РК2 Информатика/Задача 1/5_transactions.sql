-- Добавление нового студента с оценками
DO $$
DECLARE
    new_student_id INTEGER;
BEGIN
    BEGIN
        -- Добавляем нового студента
        INSERT INTO students (full_name, group_number) 
        VALUES ('Новиков Дмитрий Сергеевич', 'ГР-101')
        RETURNING student_id INTO new_student_id;
        
        -- Добавляем оценки
        INSERT INTO grades (student_id, subject_id, grade) VALUES
        (new_student_id, 1, 4),  -- Математический анализ
        (new_student_id, 2, 5),  -- Аналитическая геометрия
        (new_student_id, 3, 4);  -- Информатика
        
        -- Добавляем посещаемость
        INSERT INTO attendance (student_id, date_attended, status) VALUES
        (new_student_id, '2024-03-01', 'present'),
        (new_student_id, '2024-03-02', 'present');
        
        -- Добавляем заметку
        INSERT INTO notes (student_id, note_text) 
        VALUES (new_student_id, 'Новый студент. Адаптируется хорошо. Проявляет интерес к информатике.');
        
        -- Фиксируем транзакцию
        COMMIT;
        
        RAISE NOTICE 'Студент успешно добавлен с ID: %', new_student_id;
        
    EXCEPTION
        WHEN OTHERS THEN
            -- Откатываем транзакцию при ошибке
            ROLLBACK;
            RAISE EXCEPTION 'Ошибка при добавлении студента: %', SQLERRM;
    END;
END $$;

-- Обновление оценки студента с проверкой
DO $$
BEGIN
    -- Начало транзакции
    BEGIN
        -- Проверяем существование студента и предмета
        IF NOT EXISTS (SELECT 1 FROM students WHERE student_id = 1) THEN
            RAISE EXCEPTION 'Студент с ID 1 не найден';
        END IF;
        
        IF NOT EXISTS (SELECT 1 FROM subjects WHERE subject_id = 3) THEN
            RAISE EXCEPTION 'Предмет с ID 3 не найден';
        END IF;
        
        -- Обновляем или добавляем оценку
        INSERT INTO grades (student_id, subject_id, grade)
        VALUES (1, 3, 5)
        ON CONFLICT (student_id, subject_id) 
        DO UPDATE SET grade = EXCLUDED.grade, created_at = CURRENT_TIMESTAMP;
        
        -- Фиксируем транзакцию
        COMMIT;
        
        RAISE NOTICE 'Оценка успешно обновлена';
        
    EXCEPTION
        WHEN OTHERS THEN
            ROLLBACK;
            RAISE EXCEPTION 'Ошибка при обновлении оценки: %', SQLERRM;
    END;
END $$;