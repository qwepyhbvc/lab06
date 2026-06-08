cmake_minimum_required(VERSION 3.14)
project(solver_app)

set(CMAKE_CXX_STANDARD 17)

# Добавляем пути к заголовочным файлам
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/../formatter_ex_lib
    ${CMAKE_CURRENT_SOURCE_DIR}/../solver_lib
)

add_executable(equation equation.cpp)

# Линкуем библиотеки
target_link_libraries(equation 
    formatter_ex
    solver
    banking
    print
)
