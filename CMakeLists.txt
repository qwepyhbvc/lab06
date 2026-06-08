cmake_minimum_required(VERSION 3.14)
project(lab06)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Версионирование
set(PRINT_VERSION_MAJOR 0)
set(PRINT_VERSION_MINOR 1)
set(PRINT_VERSION_PATCH 0)
set(PRINT_VERSION_TWEAK 0)
set(PRINT_VERSION
  ${PRINT_VERSION_MAJOR}.${PRINT_VERSION_MINOR}.${PRINT_VERSION_PATCH}.${PRINT_VERSION_TWEAK})
set(PRINT_VERSION_STRING "v${PRINT_VERSION}")

# Основная библиотека print
add_library(print STATIC sources/print.cpp)
target_include_directories(print PUBLIC include)

# Библиотека banking
add_subdirectory(banking_lib)

# formatter_ex_lib (если существует)
if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/formatter_ex_lib/CMakeLists.txt)
    add_subdirectory(formatter_ex_lib)
endif()

# solver_lib (если существует)
if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/solver_lib/CMakeLists.txt)
    add_subdirectory(solver_lib)
endif()

# solver_application (если существует)
if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/solver_application/CMakeLists.txt)
    add_subdirectory(solver_application)
endif()

# Опции для тестов
option(BUILD_TESTS "Build tests for print" OFF)
option(BUILD_BANKING_TESTS "Build tests for banking" OFF)

# Тесты для print
if(BUILD_TESTS)
    enable_testing()
    
    include(FetchContent)
    FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG v1.15.2
    )
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)
    
    file(GLOB TEST_SOURCES "tests/*.cpp")
    add_executable(check ${TEST_SOURCES})
    target_link_libraries(check print gtest_main)
    add_test(NAME check COMMAND check)
endif()

# Подключаем CPack
include(CPackConfig.cmake)
