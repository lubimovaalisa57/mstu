cmake_minimum_required(VERSION 3.20)
project(dwh_postgresql)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

# Ищем PostgreSQL (пробуем разные пути)
find_package(PostgreSQL QUIET)

if(PostgreSQL_FOUND)
    message(STATUS "PostgreSQL найдена через find_package: ${PostgreSQL_VERSION}")
    include_directories(${PostgreSQL_INCLUDE_DIRS})
else()
    message(STATUS "Ищем PostgreSQL вручную...")

    # Пробуем разные пути
    set(POSSIBLE_PATHS
            "/Applications/Postgres.app/Contents/Versions/latest"
            "/usr/local/opt/postgresql"
            "/opt/homebrew/opt/postgresql"
            "/usr/local/pgsql"
    )

    foreach(PATH ${POSSIBLE_PATHS})
        if(EXISTS "${PATH}/include/libpq-fe.h")
            set(POSTGRESQL_INCLUDE_DIR "${PATH}/include")
            set(POSTGRESQL_LIBRARY "${PATH}/lib/libpq.dylib")
            message(STATUS "Нашел PostgreSQL в: ${PATH}")
            break()
        endif()
    endforeach()

    if(POSTGRESQL_INCLUDE_DIR)
        include_directories(${POSTGRESQL_INCLUDE_DIR})
        link_directories(${POSTGRESQL_LIBRARY})
    else()
        message(FATAL_ERROR "PostgreSQL не найдена!")
    endif()
endif()

# Все исходные файлы
set(SOURCE_FILES
        main.cpp
        csv_loader.cpp
        date_converter.cpp
        database.cpp
)

# Исполняемый файл
add_executable(dwh_postgresql ${SOURCE_FILES})

# Линковка с libpq
if(PostgreSQL_FOUND)
    target_link_libraries(dwh_postgresql ${PostgreSQL_LIBRARIES})
else()
    target_link_libraries(dwh_postgresql pq)
endif()

message(STATUS "Проект настроен успешно")