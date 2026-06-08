cmake_minimum_required(VERSION 3.14)
project(solver_app)

set(CMAKE_CXX_STANDARD 17)

add_executable(equation equation.cpp)

target_include_directories(equation PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../formatter_ex_lib
    ${CMAKE_CURRENT_SOURCE_DIR}/../solver_lib
)

target_link_libraries(equation
    formatter_ex
    solver
)

install(TARGETS equation
    RUNTIME DESTINATION bin
)
