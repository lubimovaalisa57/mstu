cmake_minimum_required(VERSION 3.15)
project(online_store)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES
        src/main.cpp
        src/User.cpp
        src/Admin.cpp
        src/Manager.cpp
        src/Customer.cpp
        src/PaymentStrategy.cpp
)

add_executable(online_store ${SOURCE_FILES})

# Включаем директории
target_include_directories(online_store PRIVATE
        /opt/homebrew/include
        /opt/homebrew/Cellar/libpqxx/7.10.5/include
        /opt/homebrew/Cellar/libpq/18.1/include
        ${CMAKE_SOURCE_DIR}/include
        ${CMAKE_SOURCE_DIR}/src
)

# Подключаем библиотеки по правильным путям
target_link_libraries(online_store
        /opt/homebrew/Cellar/libpqxx/7.10.5/lib/libpqxx-7.10.dylib
        /opt/homebrew/Cellar/libpq/18.1/lib/libpq.5.dylib
        pthread
)