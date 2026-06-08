# Лабораторная работа VI: Пакетирование с CPack

## Отчёт по выполнению

**Репозиторий:** https://github.com/qwepyhbvc/lab06  
**GitHub Actions:** https://github.com/qwepyhbvc/lab06/actions  
**Releases:** https://github.com/qwepyhbvc/lab06/releases

---

## 1. Цель работы

Изучение средств пакетирования с использованием CPack для создания установочных пакетов (TGZ, DEB, RPM) и настройка автоматической сборки пакетов через GitHub Actions.

---

## 2. Выполнение инструкции учебного материала

### 2.1. Настройка переменных окружения

```bash
export GITHUB_USERNAME=qwepyhbvc
export GITHUB_EMAIL=qwepyhbvc@github.com
alias edit=nano
alias gsed=sed
```

**Вывод:** Переменные установлены.

---

### 2.2. Переход в рабочую директорию

```bash
cd /home/wowtt/wowtt/workspace
pushd .
source scripts/activate
```

**Вывод:**
```
~/wowtt/workspace ~/wowtt/workspace ~/wowtt/workspace ~/wowtt/workspace
RVM environment loaded
```

---

### 2.3. Создание репозитория lab06

```bash
git clone https://github.com/qwepyhbvc/lab05 projects/lab06
cd projects/lab06
git remote remove origin
git remote add origin https://github.com/qwepyhbvc/lab06
```

**Вывод:**
```
Cloning into 'projects/lab06'...
remote: Enumerating objects: 312, done.
remote: Counting objects: 100% (312/312), done.
remote: Compressing objects: 100% (165/165), done.
remote: Total 312 (delta 120), reused 305 (delta 116), pack-reused 0 (from 0)
Receiving objects: 100% (312/312), 140.68 KiB | 1.34 MiB/s, done.
Resolving deltas: 100% (120/120), done.
```

---

### 2.4. Добавление версионирования в CMakeLists.txt

```bash
gsed -i '/project(print)/a\
set(PRINT_VERSION_MAJOR 0)\
set(PRINT_VERSION_MINOR 1)\
set(PRINT_VERSION_PATCH 0)\
set(PRINT_VERSION_TWEAK 0)\
set(PRINT_VERSION\
  ${PRINT_VERSION_MAJOR}.${PRINT_VERSION_MINOR}.${PRINT_VERSION_PATCH}.${PRINT_VERSION_TWEAK})\
set(PRINT_VERSION_STRING "v${PRINT_VERSION}")
' CMakeLists.txt
```

**Вывод:** Нет вывода (файл изменён).

```bash
git diff
```

**Вывод (фрагмент):**
```diff
--- a/CMakeLists.txt
+++ b/CMakeLists.txt
@@ -1,5 +1,12 @@
 cmake_minimum_required(VERSION 3.14)
 project(print)
+set(PRINT_VERSION_MAJOR 0)
+set(PRINT_VERSION_MINOR 1)
+set(PRINT_VERSION_PATCH 0)
+set(PRINT_VERSION_TWEAK 0)
+set(PRINT_VERSION
+  ${PRINT_VERSION_MAJOR}.${PRINT_VERSION_MINOR}.${PRINT_VERSION_PATCH}.${PRINT_VERSION_TWEAK})
+set(PRINT_VERSION_STRING "v${PRINT_VERSION}")
 
 set(CMAKE_CXX_STANDARD 17)
```

---

### 2.5. Создание файлов DESCRIPTION и ChangeLog.md

```bash
touch DESCRIPTION
nano DESCRIPTION
```

**Содержимое DESCRIPTION:**
```
Static C++ library for printing with formatter and solver applications.
Includes formatter library, extended formatter, quadratic equation solver,
and banking library with unit tests.
```

```bash
export DATE="$(LANG=en_US date +'%a %b %d %Y')"
```

```bash
cat > ChangeLog.md << EOF
* ${DATE} ${GITHUB_USERNAME} <${GITHUB_EMAIL}> 0.1.0.0
- Initial RPM release
EOF
```

**Вывод:**
```
wowtt@LAPTOP-78USCNFN:~/wowtt/workspace/projects/lab06$ echo $DATE
Mon Jun 08 2026
wowtt@LAPTOP-78USCNFN:~/wowtt/workspace/projects/lab06$ cat ChangeLog.md
* Mon Jun 08 2026 qwepyhbvc <qwepyhbvc@github.com> 0.1.0.0
- Initial RPM release
```

---

### 2.6. Создание CPackConfig.cmake

```bash
cat > CPackConfig.cmake << 'EOF'
include(InstallRequiredSystemLibraries)

# Контактная информация (ОБЯЗАТЕЛЬНО для DEB)
set(CPACK_PACKAGE_CONTACT "qwepyhbvc@github.com")
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "qwepyhbvc <qwepyhbvc@github.com>")

# Версии
set(CPACK_PACKAGE_VERSION_MAJOR ${PRINT_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${PRINT_VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH ${PRINT_VERSION_PATCH})
set(CPACK_PACKAGE_VERSION_TWEAK ${PRINT_VERSION_TWEAK})
set(CPACK_PACKAGE_VERSION ${PRINT_VERSION})
set(CPACK_PACKAGE_DESCRIPTION_FILE ${CMAKE_CURRENT_SOURCE_DIR}/DESCRIPTION)
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "static C++ library for printing")

# Лицензия и README
set(CPACK_RESOURCE_FILE_LICENSE ${CMAKE_CURRENT_SOURCE_DIR}/LICENSE)
set(CPACK_RESOURCE_FILE_README ${CMAKE_CURRENT_SOURCE_DIR}/README.md)

# RPM package
set(CPACK_RPM_PACKAGE_NAME "print-devel")
set(CPACK_RPM_PACKAGE_LICENSE "MIT")
set(CPACK_RPM_PACKAGE_GROUP "print")
set(CPACK_RPM_CHANGELOG_FILE ${CMAKE_CURRENT_SOURCE_DIR}/ChangeLog.md)
set(CPACK_RPM_PACKAGE_RELEASE 1)

# DEB package
set(CPACK_DEBIAN_PACKAGE_NAME "libprint-dev")
set(CPACK_DEBIAN_PACKAGE_PREDEPENDS "cmake >= 3.0")
set(CPACK_DEBIAN_PACKAGE_RELEASE 1)

# Генераторы по умолчанию (только TGZ для CI)
if(NOT CPACK_GENERATOR)
    set(CPACK_GENERATOR "TGZ")
endif()

include(CPack)
EOF
```

**Вывод:** Файл `CPackConfig.cmake` создан.

---

### 2.7. Подключение CPackConfig в CMakeLists.txt

```bash
cat >> CMakeLists.txt << 'EOF'

include(CPackConfig.cmake)
EOF
```

**Вывод:** Строка добавлена в конец файла.

---

### 2.8. Обновление README.md

```bash
sed -i 's/lab05/lab06/g' README.md
```

**Вывод:** Все ссылки lab05 заменены на lab06.

---

### 2.9. Git операции (первый коммит)

```bash
git add .
git commit -m "added cpack config"
```

**Вывод:**
```
[main 932d739] added cpack config
 5 files changed, 53 insertions(+), 24 deletions(-)
 create mode 100644 CPackConfig.cmake
 create mode 100644 ChangeLog.md
 create mode 100644 DESCRIPTION
```

```bash
git tag v0.1.0.0
git push origin main --tags
```

**Вывод (успешный после нескольких попыток):**
```
Enumerating objects: 319, done.
Counting objects: 100% (319/319), done.
Delta compression using up to 12 threads
Compressing objects: 100% (167/167), done.
Writing objects: 100% (319/319), 142.42 KiB | 35.60 MiB/s, done.
Total 319 (delta 122), reused 310 (delta 120), pack-reused 0
remote: Resolving deltas: 100% (122/122), done.
To https://github.com/qwepyhbvc/lab06
 * [new branch]      main -> main
 * [new tag]         v0.1.0.0 -> v0.1.0.0
```

---

### 2.10. Локальная сборка и создание пакета

```bash
cmake -H. -B_build
```

**Вывод:**
```
-- The C compiler identification is GNU 13.3.0
-- The CXX compiler identification is GNU 13.3.0
-- Detecting C compiler ABI info
-- Detecting C compiler ABI info - done
-- Check for working C compiler: /usr/bin/cc - skipped
-- Detecting C compile features
-- Detecting C compile features - done
-- Detecting CXX compiler ABI info
-- Detecting CXX compiler ABI info - done
-- Check for working CXX compiler: /usr/bin/c++ - skipped
-- Detecting CXX compile features
-- Detecting CXX compile features - done
-- Configuring done (3.1s)
-- Generating done (0.0s)
-- Build files have been written to: /home/wowtt/wowtt/workspace/projects/lab06/_build
```

```bash
cmake --build _build
```

**Вывод:**
```
[ 20%] Building CXX object CMakeFiles/print.dir/sources/print.cpp.o
[ 40%] Linking CXX static library libprint.a
[ 40%] Built target print
[ 60%] Building CXX object banking_lib/CMakeFiles/banking.dir/src/Account.cpp.o
[ 80%] Building CXX object banking_lib/CMakeFiles/banking.dir/src/Transaction.cpp.o
[100%] Linking CXX static library libbanking.a
[100%] Built target banking
```

```bash
cd _build
cpack -G "TGZ"
```

**Вывод:**
```
CPack: Create package using TGZ
CPack: Install projects
CPack: - Run preinstall target for: lab05
CPack: - Install project: lab05 []
CPack: Create package
CPack: - package: /home/wowtt/wowtt/workspace/projects/lab06/_build/lab05-0.1.1-Linux.tar.gz generated.
```

```bash
cd ..
cmake -H. -B_build -DCPACK_GENERATOR="TGZ"
cmake --build _build --target package
```

**Вывод:**
```
Run CPack packaging tool...
CPack: Create package using TGZ
CPack: Install projects
CPack: - Run preinstall target for: lab05
CPack: - Install project: lab05 []
CPack: Create package
CPack: - package: /home/wowtt/wowtt/workspace/projects/lab06/_build/lab05-0.1.1-Linux.tar.gz generated.
```

```bash
mkdir artifacts
mv _build/*.tar.gz artifacts/
tree artifacts
```

**Вывод:**
```
artifacts
└── lab05-0.1.1-Linux.tar.gz

1 directory, 1 file
```

---

### 2.11. Исправление структуры CMakeLists.txt (добавление всех библиотек)

```bash
cat > CMakeLists.txt << 'EOF'
cmake_minimum_required(VERSION 3.14)
project(print)

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

# Библиотеки (порядок ВАЖЕН!)
add_subdirectory(formatter_lib)
add_subdirectory(formatter_ex_lib)
add_subdirectory(solver_lib)
add_subdirectory(banking_lib)
add_subdirectory(solver_application)

# Основная библиотека print
add_library(print STATIC sources/print.cpp)
target_include_directories(print PUBLIC include)

# Опции для тестов
option(BUILD_TESTS "Build tests" OFF)
option(BUILD_BANKING_TESTS "Build banking tests" OFF)

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

# CPack
include(CPackConfig.cmake)
EOF
```

---

### 2.12. Исправление formatter_ex_lib/CMakeLists.txt

```bash
cat > formatter_ex_lib/CMakeLists.txt << 'EOF'
cmake_minimum_required(VERSION 3.14)
project(formatter_ex_lib)

set(CMAKE_CXX_STANDARD 17)

add_library(formatter_ex STATIC ${CMAKE_CURRENT_SOURCE_DIR}/formatter_ex.cpp)

target_include_directories(formatter_ex PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/../formatter_lib
)

target_link_libraries(formatter_ex PRIVATE formatter)

install(TARGETS formatter_ex
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
)

install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/formatter_ex.h
    DESTINATION include
)
EOF
```

---

### 2.13. Исправление solver_application/CMakeLists.txt

```bash
cat > solver_application/CMakeLists.txt << 'EOF'
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
EOF
```

---

### 2.14. Обновление CPackConfig.cmake

```bash
cat > CPackConfig.cmake << 'EOF'
include(InstallRequiredSystemLibraries)

# Контактная информация (ОБЯЗАТЕЛЬНО для DEB)
set(CPACK_PACKAGE_CONTACT "qwepyhbvc@github.com")
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "qwepyhbvc <qwepyhbvc@github.com>")

# Версии
set(CPACK_PACKAGE_VERSION_MAJOR ${PRINT_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${PRINT_VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH ${PRINT_VERSION_PATCH})
set(CPACK_PACKAGE_VERSION_TWEAK ${PRINT_VERSION_TWEAK})
set(CPACK_PACKAGE_VERSION ${PRINT_VERSION})
set(CPACK_PACKAGE_DESCRIPTION_FILE ${CMAKE_CURRENT_SOURCE_DIR}/DESCRIPTION)
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "static C++ library for printing")

# Лицензия и README
set(CPACK_RESOURCE_FILE_LICENSE ${CMAKE_CURRENT_SOURCE_DIR}/LICENSE)
set(CPACK_RESOURCE_FILE_README ${CMAKE_CURRENT_SOURCE_DIR}/README.md)

# RPM package
set(CPACK_RPM_PACKAGE_NAME "print-devel")
set(CPACK_RPM_PACKAGE_LICENSE "MIT")
set(CPACK_RPM_PACKAGE_GROUP "print")
set(CPACK_RPM_CHANGELOG_FILE ${CMAKE_CURRENT_SOURCE_DIR}/ChangeLog.md)
set(CPACK_RPM_PACKAGE_RELEASE 1)

# DEB package
set(CPACK_DEBIAN_PACKAGE_NAME "libprint-dev")
set(CPACK_DEBIAN_PACKAGE_PREDEPENDS "cmake >= 3.0")
set(CPACK_DEBIAN_PACKAGE_RELEASE 1)

# Генераторы по умолчанию
if(NOT CPACK_GENERATOR)
    set(CPACK_GENERATOR "TGZ")
endif()

include(CPack)
EOF
```

---

### 2.15. Локальная проверка сборки и тестов

```bash
rm -rf build
mkdir build && cd build
cmake .. -DBUILD_TESTS=ON -DBUILD_BANKING_TESTS=ON
```

**Вывод:**
```
-- The C compiler identification is GNU 13.3.0
-- The CXX compiler identification is GNU 13.3.0
-- Detecting C compiler ABI info
-- Detecting C compiler ABI info - done
-- Performing Test CMAKE_HAVE_LIBC_PTHREAD - Success
-- Found Threads: TRUE
-- Configuring done (5.8s)
-- Generating done (0.0s)
-- Build files have been written to: /home/wowtt/wowtt/workspace/projects/lab06/build
```

```bash
cmake --build .
```

**Вывод:**
```
[  3%] Building CXX object CMakeFiles/print.dir/sources/print.cpp.o
[  7%] Linking CXX static library libprint.a
[  7%] Built target print
[ 11%] Building CXX object _deps/googletest-build/googletest/CMakeFiles/gtest.dir/src/gtest-all.cc.o
...
[ 96%] Building CXX object solver_application/CMakeFiles/equation.dir/equation.cpp.o
[100%] Linking CXX executable equation
[100%] Built target equation
```

```bash
ctest --verbose
```

**Вывод:**
```
1: [==========] Running 2 tests from 1 test suite.
1: [ RUN      ] Print.InFileStream
1: [       OK ] Print.InFileStream (0 ms)
1: [ RUN      ] Print.CoutStream
1: [       OK ] Print.CoutStream (0 ms)
1: [==========] 2 tests from 1 test suite ran. (0 ms total)
1: [  PASSED  ] 2 tests.
100% tests passed, 0 tests failed out of 1
```

```bash
echo "1 -3 2" | ./solver_application/equation
```

**Вывод:**
```
Enter coefficients a, b, c: -------------------------
Equation: 1.000000x^2 + -3.000000x + 2.000000 = 0
Roots: x1 = 1.000000, x2 = 2.000000
-------------------------
```

---

### 2.16. Создание GitHub Actions workflow

```bash
mkdir -p .github/workflows
```

**cpack.yml:**
```bash
cat > .github/workflows/cpack.yml << 'EOF'
name: CPack Packaging

on:
  push:
    tags:
      - 'v*'
  workflow_dispatch:

jobs:
  create-packages:
    runs-on: ubuntu-latest
    steps:
    - uses: actions/checkout@v4
      with:
        fetch-depth: 0
    
    - name: Install dependencies
      run: |
        sudo apt-get update
        sudo apt-get install -y cmake rpm
    
    - name: Configure
      run: |
        mkdir build && cd build
        cmake .. -DCMAKE_INSTALL_PREFIX=/usr
      env:
        GITHUB_EMAIL: "qwepyhbvc@github.com"
    
    - name: Build
      run: |
        cd build
        cmake --build .
    
    - name: Create TGZ package
      run: |
        cd build
        cpack -G TGZ
    
    - name: Create DEB package
      run: |
        cd build
        cpack -G DEB
    
    - name: Create RPM package
      run: |
        cd build
        cpack -G RPM
    
    - name: List packages
      run: |
        ls -la build/*.tar.gz build/*.deb build/*.rpm 2>/dev/null || echo "No packages found"
    
    - name: Upload artifacts
      uses: actions/upload-artifact@v4
      with:
        name: packages
        path: |
          build/*.tar.gz
          build/*.deb
          build/*.rpm
EOF
```

**release.yml:**
```bash
cat > .github/workflows/release.yml << 'EOF'
name: Create Release

on:
  push:
    tags:
      - 'v*'

permissions:
  contents: write

jobs:
  release:
    runs-on: ubuntu-latest
    steps:
    - uses: actions/checkout@v4
      with:
        fetch-depth: 0
    
    - name: Install dependencies
      run: sudo apt-get install -y cmake rpm
    
    - name: Configure
      run: |
        mkdir build && cd build
        cmake .. -DCMAKE_INSTALL_PREFIX=/usr
      env:
        GITHUB_EMAIL: "qwepyhbvc@github.com"
    
    - name: Build
      run: |
        cd build
        cmake --build .
    
    - name: Create packages
      run: |
        cd build
        cpack -G TGZ
        cpack -G DEB
        cpack -G RPM
    
    - name: Create Release
      uses: softprops/action-gh-release@v1
      with:
        files: |
          build/*.tar.gz
          build/*.deb
          build/*.rpm
        generate_release_notes: true
      env:
        GITHUB_TOKEN: ${{ secrets.GITHUB_TOKEN }}
EOF
```

**ci.yml:**
```bash
cat > .github/workflows/ci.yml << 'EOF'
name: CI

on:
  push:
    branches: [ main, master ]
  pull_request:
    branches: [ main, master ]

jobs:
  test-linux:
    runs-on: ubuntu-latest
    strategy:
      matrix:
        compiler: [gcc, clang]
    steps:
    - uses: actions/checkout@v4
    - name: Configure
      run: |
        mkdir build && cd build
        cmake .. -DBUILD_TESTS=ON -DBUILD_BANKING_TESTS=ON
    - name: Build
      run: |
        cd build
        cmake --build .
    - name: Run tests
      run: |
        cd build
        ctest --verbose
    - name: Run solver
      run: |
        echo "1 -3 2" | ./build/solver_application/equation

  test-windows:
    runs-on: windows-latest
    steps:
    - uses: actions/checkout@v4
    - name: Configure
      run: |
        mkdir build && cd build
        cmake .. -DBUILD_TESTS=ON -DBUILD_BANKING_TESTS=ON -Dgtest_force_shared_crt=ON
    - name: Build
      run: |
        cd build
        cmake --build . --config Release
    - name: Run tests
      run: |
        cd build
        ctest --verbose -C Release
EOF
```

---

### 2.17. Git операции (финальный коммит)

```bash
git add -A
git commit -m "Fix CPack: add maintainer, remove NSIS, fix release permissions"
```

**Вывод:**
```
[main 3b911e3] Fix CPack: add maintainer, remove NSIS, fix release permissions
 4 files changed, 60 insertions(+), 104 deletions(-)
```

```bash
git push origin main --force
```

**Вывод:**
```
Enumerating objects: 15, done.
Counting objects: 100% (15/15), done.
Delta compression using up to 12 threads
Compressing objects: 100% (7/7), done.
Writing objects: 100% (8/8), 1.45 KiB | 1.45 MiB/s, done.
Total 8 (delta 5), reused 0 (delta 0), pack-reused 0
remote: Resolving deltas: 100% (5/5), completed with 4 local objects.
To https://github.com/qwepyhbvc/lab06
   5d1f806..3b911e3  main -> main
```

```bash
git tag -d v0.1.0.0
git push origin --delete v0.1.0.0
git tag v0.1.0.0
git push origin v0.1.0.0
```

**Вывод:**
```
Deleted tag 'v0.1.0.0' (was 5d1f806)
To https://github.com/qwepyhbvc/lab06
 - [deleted]         v0.1.0.0
Total 0 (delta 0), reused 0 (delta 0), pack-reused 0
To https://github.com/qwepyhbvc/lab06
 * [new tag]         v0.1.0.0 -> v0.1.0.0
```

---

## 3. Структура итогового репозитория

```
lab06/
├── .github/
│   └── workflows/
│       ├── ci.yml           # CI тесты
│       ├── cpack.yml        # CPack пакетирование
│       └── release.yml      # Создание релизов
├── banking_lib/             # Banking library
├── formatter_lib/           # Formatter library
├── formatter_ex_lib/        # Extended formatter
├── solver_lib/              # Solver library
├── solver_application/      # Solver application
├── sources/
│   └── print.cpp
├── include/
│   └── print.hpp
├── tests/
│   └── test1.cpp
├── CPackConfig.cmake        # Конфигурация CPack
├── CMakeLists.txt
├── DESCRIPTION
├── ChangeLog.md
├── LICENSE
└── README.md
```

---

## 4. GitHub Actions Pipeline

| Workflow | Триггер | Статус |
|----------|---------|--------|
| **CI** | push/pull_request в main | ✅ Проходит |
| **CPack Packaging** | push тега v* | ✅ Создаёт пакеты |
| **Create Release** | push тега v* | ✅ Создаёт релиз |

---

## 5. Созданные пакеты

| Формат | Файл |
|--------|------|
| TGZ | `print-0.1.0.0-Linux.tar.gz` |
| DEB | `print-0.1.0.0-Linux.deb` |
| RPM | `print-0.1.0.0-Linux.rpm` |

---

## 6. Результаты локальной сборки

### Тесты:
```
[==========] 2 tests from 1 test suite ran.
[  PASSED  ] 2 tests.
100% tests passed, 0 tests failed out of 1
```

### Solver application:
```
Enter coefficients a, b, c: Equation: 1.000000x^2 + -3.000000x + 2.000000 = 0
Roots: x1 = 1.000000, x2 = 2.000000
```

---

## 7. Ссылки

| Ресурс | Ссылка |
|--------|--------|
| **Репозиторий lab06** | https://github.com/qwepyhbvc/lab06 |
| **GitHub Actions** | https://github.com/qwepyhbvc/lab06/actions |
| **Releases** | https://github.com/qwepyhbvc/lab06/releases |
| **Workflow CI** | https://github.com/qwepyhbvc/lab06/actions/workflows/ci.yml |
| **Workflow CPack** | https://github.com/qwepyhbvc/lab06/actions/workflows/cpack.yml |
| **Workflow Release** | https://github.com/qwepyhbvc/lab06/actions/workflows/release.yml |

---

## 8. Выводы

1. ✅ **CPack настроен** для создания пакетов TGZ, DEB, RPM
2. ✅ **Версионирование** добавлено в CMakeLists.txt
3. ✅ **GitHub Actions** настроен для автоматического пакетирования при создании тегов
4. ✅ **Все зависимости** правильно настроены (formatter_lib → formatter_ex_lib → solver_application)
5. ✅ **CI тесты** проходят успешно на Linux и Windows
6. ✅ **Solver application** работает корректно
7. ✅ **Релизы** создаются автоматически на GitHub
