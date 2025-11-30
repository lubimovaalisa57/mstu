cmake_minimum_required(VERSION 3.10)
project(my_app)

# Автоматически находим все .cpp файлы в src/
file(GLOB SOURCES "src/*.cpp")
file(GLOB HEADERS "include/*.h")

find_package(libpqxx CONFIG REQUIRED)
add_executable(my_app ${SOURCES} ${HEADERS})

# Добавляем include директорию
target_include_directories(my_app PRIVATE include)
target_link_libraries(my_app PRIVATE libpqxx::pqxx)

set(CMAKE_CXX_STANDARD 17)