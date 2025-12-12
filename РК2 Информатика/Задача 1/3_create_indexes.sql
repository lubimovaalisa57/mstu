-- Индекс для быстрого поиска одногруппников
CREATE INDEX idx_students_group_number ON students(group_number);

-- Индекс для ускорения агрегированных запросов оценок
CREATE INDEX idx_grades_student_id ON grades(student_id);

-- Индекс для ускорения поиска по предметам
CREATE INDEX idx_grades_subject_id ON grades(subject_id);

-- Добавляем колонку для полнотекстового поиска
ALTER TABLE notes ADD COLUMN IF NOT EXISTS note_text_tsvector TSVECTOR;

-- Обновляем новую колонку с tsvector данными
UPDATE notes SET note_text_tsvector = to_tsvector('russian', note_text);

-- Создаем индекс GIN для полнотекстового поиска
CREATE INDEX idx_notes_note_text_gin ON notes USING GIN(note_text_tsvector);

-- Создаем триггер для автоматического обновления tsvector
CREATE OR REPLACE FUNCTION notes_tsvector_update() RETURNS TRIGGER AS $$
BEGIN
    NEW.note_text_tsvector = to_tsvector('russian', NEW.note_text);
    RETURN NEW;
END;
$$ LANGUAGE plpgsql;

CREATE TRIGGER notes_tsvector_update_trigger
    BEFORE INSERT OR UPDATE ON notes
    FOR EACH ROW
    EXECUTE FUNCTION notes_tsvector_update();