-- Таблица авторов
CREATE TABLE authors (
    id SERIAL PRIMARY KEY,
    name VARCHAR(100) NOT NULL,
    birth_year INT
);

-- Таблица книг
CREATE TABLE books (
    id SERIAL PRIMARY KEY,
    title VARCHAR(200) NOT NULL,
    author_id INT,
    publication_year INT,
    genre VARCHAR(50),
    FOREIGN KEY (author_id) REFERENCES authors(id)
);

-- Таблица пользователей
CREATE TABLE users (
    id SERIAL PRIMARY KEY,
    name VARCHAR(100) NOT NULL,
    registration_date DATE
);

-- Таблица выданных книг
CREATE TABLE borrowed_books (
    user_id INT,
    book_id INT,
    borrow_date DATE NOT NULL,
    return_date DATE,
    PRIMARY KEY (user_id, book_id, borrow_date),
    FOREIGN KEY (user_id) REFERENCES users(id),
    FOREIGN KEY (book_id) REFERENCES books(id)
);

-- 2. Заполнение данными

-- Добавление авторов
INSERT INTO authors (name, birth_year) VALUES
('Лев Толстой', 1828),
('Федор Достоевский', 1821),
('Антон Чехов', 1860);

-- Добавление книг
INSERT INTO books (title, author_id, publication_year, genre) VALUES
('Война и мир', 1, 1869, 'Роман-эпопея'),
('Анна Каренина', 1, 1877, 'Роман'),
('Преступление и наказание', 2, 1866, 'Психологический роман'),
('Идиот', 2, 1869, 'Роман'),
('Вишневый сад', 3, 1904, 'Пьеса'),
('Чайка', 3, 1896, 'Пьеса');

-- Добавление пользователей
INSERT INTO users (name, registration_date) VALUES
('Иван Петров', '2023-01-15'),
('Мария Сидорова', '2023-02-20'),
('Алексей Козлов', '2023-03-10');

-- Добавление записей о выданных книгах
INSERT INTO borrowed_books (user_id, book_id, borrow_date, return_date) VALUES
(1, 1, '2024-01-10', '2024-01-25'),
(1, 3, '2024-02-01', NULL),
(2, 2, '2024-01-20', '2024-02-05'),
(3, 5, '2024-02-15', NULL);

-- 3. ЗАПРОСЫ

-- 1. Список всех книг определенного автора (Льва Толстого)
SELECT '=== Книги Льва Толстого ===';
SELECT b.title, b.publication_year, b.genre
FROM books b
JOIN authors a ON b.author_id = a.id
WHERE a.name = 'Лев Толстой';

-- 2. Поиск книг по определенному жанру (Роман)
SELECT '=== Книги жанра "Роман" ===';
SELECT b.title, a.name as author, b.publication_year
FROM books b
JOIN authors a ON b.author_id = a.id
WHERE b.genre = 'Роман';

-- 3. Список пользователей, зарегистрированных в определенный период
SELECT '=== Пользователи (январь-февраль 2023) ===';
SELECT name, registration_date
FROM users
WHERE registration_date BETWEEN '2023-01-01' AND '2023-02-28'
ORDER BY registration_date;

-- 4. Список книг, которые были взяты и еще не возвращены
SELECT '=== Не возвращенные книги ===';
SELECT u.name as user_name, b.title as book_title, a.name as author, bb.borrow_date
FROM borrowed_books bb
JOIN users u ON bb.user_id = u.id
JOIN books b ON bb.book_id = b.id
JOIN authors a ON b.author_id = a.id
WHERE bb.return_date IS NULL;

-- 5. ДОПОЛНИТЕЛЬНЫЕ ЗАДАНИЯ

-- Отчет о количестве книг, взятых каждым пользователем
SELECT '=== Статистика по пользователям ===';
SELECT u.name as user_name, 
       COUNT(bb.book_id) as books_borrowed,
       COUNT(CASE WHEN bb.return_date IS NULL THEN 1 END) as books_not_returned
FROM users u
LEFT JOIN borrowed_books bb ON u.id = bb.user_id
GROUP BY u.id, u.name
ORDER BY books_borrowed DESC;

-- Обновление информации о пользователе
SELECT '=== Обновление пользователя ===';
UPDATE users 
SET name = 'Иван Петров-Иванов', 
    registration_date = '2023-01-20'
WHERE id = 1;

-- Проверка обновления
SELECT name, registration_date FROM users WHERE id = 1;

-- Просмотр всех данных (для проверки)
SELECT '=== ВСЕ АВТОРЫ ===';
SELECT * FROM authors;

SELECT '=== ВСЕ КНИГИ ===';
SELECT * FROM books;

SELECT '=== ВСЕ ПОЛЬЗОВАТЕЛИ ===';
SELECT * FROM users;

SELECT '=== ВСЕ ВЫДАННЫЕ КНИГИ ===';
SELECT * FROM borrowed_books;