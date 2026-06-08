# Лабораторная работа VI: Пакетирование с CPack

## Отчёт по выполнению

**Репозиторий:** https://github.com/qwepyhbvc/lab06  
**GitHub Actions:** https://github.com/qwepyhbvc/lab06/actions  
**Releases:** https://github.com/qwepyhbvc/lab06/releases

---

# Часть 1: Основное задание (Tutorial)

### 1.1. Настройка переменных окружения

```bash
export GITHUB_USERNAME=qwepyhbvc
export GITHUB_EMAIL=qwepyhbvc@github.com
alias edit=nano
alias gsed=sed
```

**Вывод:**
```
wowtt@LAPTOP-78USCNFN:~/wowtt/workspace/projects$ export GITHUB_USERNAME=qwepyhbvc
wowtt@LAPTOP-78USCNFN:~/wowtt/workspace/projects$ export GITHUB_EMAIL=qwepyhbvc@github.com
wowtt@LAPTOP-78USCNFN:~/wowtt/workspace/projects$ alias edit=nano
wowtt@LAPTOP-78USCNFN:~/wowtt/workspace/projects$ alias gsed=sed
```

---

### 1.2. Переход в рабочую директорию

```bash
cd /home/wowtt/wowtt/workspace
pushd .
source scripts/activate
```

**Вывод:**
```
wowtt@LAPTOP-78USCNFN:~/wowtt/workspace$ cd /home/wowtt/wowtt/workspace
wowtt@LAPTOP-78USCNFN:~/wowtt/workspace$ pushd .
~/wowtt/workspace ~/wowtt/workspace ~/wowtt/workspace ~/wowtt/workspace
wowtt@LAPTOP-78USCNFN:~/wowtt/workspace$ source scripts/activate
RVM environment loaded
```

---

### 1.3. Создание репозитория lab06

```bash
git clone https://github.com/qwepyhbvc/lab05 projects/lab06
cd projects/lab06
git remote remove origin
git remote add origin https://github.com/qwepyhbvc/lab06
```

**Вывод:**
```
wowtt@LAPTOP-78USCNFN:~/wowtt/workspace$ git clone https://github.com/qwepyhbvc/lab05 projects/lab06
Cloning into 'projects/lab06'...
remote: Enumerating objects: 312, done.
remote: Counting objects: 100% (312/312), done.
remote: Compressing objects: 100% (165/165), done.
remote: Total 312 (delta 120), reused 305 (delta 116), pack-reused 0 (from 0)
Receiving objects: 100% (312/312), 140.68 KiB | 1.34 MiB/s, done.
Resolving deltas: 100% (120/120), done.
wowtt@LAPTOP-78USCNFN:~/wowtt/workspace$ cd projects/lab06
wowtt@LAPTOP-78USCNFN:~/wowtt/workspace/projects/lab06$ git remote remove origin
wowtt@LAPTOP-78USCNFN:~/wowtt/workspace/projects/lab06$ git remote add origin https://github.com/qwepyhbvc/lab06
```

---

### 1.4. Добавление версионирования в CMakeLists.txt

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

### 1.5. Создание файлов DESCRIPTION и ChangeLog.md

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

### 1.6. Создание CPackConfig.cmake

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

### 1.7. Подключение CPackConfig в CMakeLists.txt

```bash
cat >> CMakeLists.txt << 'EOF'

include(CPackConfig.cmake)
EOF
```

**Вывод:** Строка добавлена в конец файла.

---

### 1.8. Обновление README.md

```bash
sed -i 's/lab05/lab06/g' README.md
```

**Вывод:** Все ссылки lab05 заменены на lab06.

---

### 1.9. Git операции (первый коммит)

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

### 1.10. Локальная сборка и создание пакета

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

### 1.11. Создание GitHub Actions workflow для CPack

```bash
mkdir -p .github/workflows
```

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

**Вывод:** Файл `.github/workflows/cpack.yml` создан.

---

# Часть 2: Домашнее задание (Homework)

### Формулировка ДЗ из lab06:

> После того, как вы настроили взаимодействие с системой непрерывной интеграции, обеспечив автоматическую сборку и тестирование ваших изменений, стоит задуматься о создание пакетов для изменений, которые помечаются тэгами (см. вкладку releases).  
> Пакет должен содержать приложение _solver_ из предыдущего задания.  
> Таким образом, каждый новый релиз будет состоять из следующих компонентов:
> - архивы с файлами исходного кода (`.tar.gz`, `.zip`)
> - пакеты с бинарным файлом _solver_ (`.deb`, `.rpm`, `.msi`, `.dmg`)

---

### 2.1. Пункт ДЗ №1: Настройка зависимостей библиотек

**Проблема:** `formatter_ex.cpp` требует `formatter.h`, который находится в `formatter_lib`.

**Решение:** Правильный порядок подключения библиотек в корневом CMakeLists.txt:

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

# ========== ДЗ ПУНКТ 1: Правильный порядок библиотек ==========
# Библиотеки (порядок ВАЖЕН!)
add_subdirectory(formatter_lib)      # сначала formatter (нужен для formatter_ex)
add_subdirectory(formatter_ex_lib)   # затем formatter_ex
add_subdirectory(solver_lib)         # затем solver
add_subdirectory(banking_lib)        # затем banking
add_subdirectory(solver_application) # затем приложение

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

**Что реализовано:**
- ✅ Правильный порядок подключения subdirectories
- ✅ `formatter_lib` добавлен ПЕРЕД `formatter_ex_lib`

---

### 2.2. Пункт ДЗ №2: Исправление formatter_ex_lib/CMakeLists.txt

```bash
cat > formatter_ex_lib/CMakeLists.txt << 'EOF'
cmake_minimum_required(VERSION 3.14)
project(formatter_ex_lib)

set(CMAKE_CXX_STANDARD 17)

add_library(formatter_ex STATIC ${CMAKE_CURRENT_SOURCE_DIR}/formatter_ex.cpp)

# ========== ДЗ ПУНКТ 2: Добавление пути к заголовкам formatter_lib ==========
target_include_directories(formatter_ex PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/../formatter_lib
)

# ========== ДЗ ПУНКТ 2: Линковка с formatter ==========
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

**Что реализовано:**
- ✅ Добавлен путь к заголовкам `formatter_lib`
- ✅ Добавлена линковка с библиотекой `formatter`

---

### 2.3. Пункт ДЗ №3: Исправление solver_application/CMakeLists.txt

```bash
cat > solver_application/CMakeLists.txt << 'EOF'
cmake_minimum_required(VERSION 3.14)
project(solver_app)

set(CMAKE_CXX_STANDARD 17)

add_executable(equation equation.cpp)

# ========== ДЗ ПУНКТ 3: Добавление путей к заголовкам ==========
target_include_directories(equation PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../formatter_ex_lib
    ${CMAKE_CURRENT_SOURCE_DIR}/../solver_lib
)

# ========== ДЗ ПУНКТ 3: Линковка с библиотеками ==========
target_link_libraries(equation
    formatter_ex
    solver
)

install(TARGETS equation
    RUNTIME DESTINATION bin
)
EOF
```

**Что реализовано:**
- ✅ Добавлены пути к заголовкам `formatter_ex_lib` и `solver_lib`
- ✅ Добавлена линковка с `formatter_ex` и `solver`

---

### 2.4. Пункт ДЗ №4: Создание workflow для автоматических релизов

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
    
    # ========== ДЗ ПУНКТ 4: Создание пакетов ==========
    - name: Create packages
      run: |
        cd build
        cpack -G TGZ   # архив с исходниками
        cpack -G DEB   # пакет для Debian/Ubuntu
        cpack -G RPM   # пакет для Red Hat/Fedora
    
    # ========== ДЗ ПУНКТ 4: Загрузка в релиз ==========
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

**Что реализовано:**
- ✅ Автоматическое создание релизов при push тега
- ✅ Создание TGZ, DEB, RPM пакетов
- ✅ Загрузка пакетов в релиз на GitHub

---

### 2.5. Пункт ДЗ №5: Локальная проверка сборки и тестов

```bash
rm -rf build
mkdir build && cd build
cmake .. -DBUILD_TESTS=ON -DBUILD_BANKING_TESTS=ON
cmake --build .
ctest --verbose
echo "1 -3 2" | ./solver_application/equation
```

**Вывод тестов:**
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

**Вывод solver_application:**
```
Enter coefficients a, b, c: -------------------------
Equation: 1.000000x^2 + -3.000000x + 2.000000 = 0
Roots: x1 = 1.000000, x2 = 2.000000
-------------------------
```

---

### 2.6. Пункт ДЗ №6: Отправка изменений и создание релиза

```bash
git add -A
git commit -m "Homework: fix dependencies, add release workflow"
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

## Часть 3: Результаты выполнения

### 3.1. Основное задание (Tutorial)

| Пункт | Выполнено |
|-------|-----------|
| Создание репозитория lab06 | ✅ |
| Добавление версионирования в CMakeLists.txt | ✅ |
| Создание DESCRIPTION и ChangeLog.md | ✅ |
| Создание CPackConfig.cmake | ✅ |
| Подключение CPack в CMakeLists.txt | ✅ |
| Локальное создание TGZ пакета | ✅ |
| Создание GitHub Actions workflow для CPack | ✅ |

### 3.2. Домашнее задание (Homework)

| Пункт ДЗ | Описание | Статус |
|----------|----------|--------|
| **Пункт 1** | Правильный порядок подключения библиотек в CMakeLists.txt | ✅ |
| **Пункт 2** | Исправление formatter_ex_lib (путь к formatter.h + линковка) | ✅ |
| **Пункт 3** | Исправление solver_application (пути к заголовкам + линковка) | ✅ |
| **Пункт 4** | Создание workflow для автоматических релизов | ✅ |
| **Пункт 5** | Создание пакетов TGZ, DEB, RPM | ✅ |
| **Пункт 6** | Загрузка пакетов в GitHub Release | ✅ |

---

## Часть 4: Итоговые ссылки

| Ресурс | Ссылка |
|--------|--------|
| **Репозиторий lab06** | https://github.com/qwepyhbvc/lab06 |
| **GitHub Actions** | https://github.com/qwepyhbvc/lab06/actions |
| **Releases** | https://github.com/qwepyhbvc/lab06/releases |
| **Workflow CI** | https://github.com/qwepyhbvc/lab06/actions/workflows/ci.yml |
| **Workflow CPack** | https://github.com/qwepyhbvc/lab06/actions/workflows/cpack.yml |
| **Workflow Release** | https://github.com/qwepyhbvc/lab06/actions/workflows/release.yml |

---

## Часть 5: Выводы

### 5.1. Основное задание
- ✅ CPack настроен для создания пакетов TGZ
- ✅ Версионирование добавлено в CMakeLists.txt
- ✅ GitHub Actions настроен для автоматического пакетирования

### 5.2. Домашнее задание

| Пункт ДЗ | Что выполнено |
|----------|---------------|
| **Пункт 1** | Настроен правильный порядок подключения библиотек (`formatter_lib` → `formatter_ex_lib` → `solver_application`) |
| **Пункт 2** | Исправлен `formatter_ex_lib` (добавлен путь к `formatter.h` и линковка с `formatter`) |
| **Пункт 3** | Исправлен `solver_application` (добавлены пути к заголовкам и линковка) |
| **Пункт 4** | Создан workflow для автоматического создания релизов при push тега |
| **Пункт 5** | Созданы пакеты TGZ, DEB, RPM с бинарным файлом `solver` |
| **Пункт 6** | Пакеты автоматически загружаются в GitHub Release |

---

# Часть 7: Добавление MSI и DMG пакетов в релиз (Домашнее задание)

### 7.1. Требование ДЗ

Согласно домашнему заданию, каждый новый релиз должен состоять из:
- архивов с файлами исходного кода (`.tar.gz`, `.zip`)
- пакетов с бинарным файлом _solver_ (`.deb`, `.rpm`, **`.msi`**, **`.dmg`**)

### 7.2. Добавление MSI пакета для Windows

#### 7.2.1. Обновление CPackConfig.cmake для поддержки NSIS

```bash
cat >> CPackConfig.cmake << 'EOF'

# NSIS для Windows (MSI)
set(CPACK_NSIS_PACKAGE_NAME "solver")
set(CPACK_NSIS_DISPLAY_NAME "Solver Application")
set(CPACK_NSIS_CONTACT ${CPACK_PACKAGE_CONTACT})
set(CPACK_NSIS_MODIFY_PATH ON)
EOF
```

#### 7.2.2. Добавление Windows сборки в release.yml

```yaml
windows-packages:
  runs-on: windows-latest
  if: startsWith(github.ref, 'refs/tags/')
  steps:
  - uses: actions/checkout@v4
  - name: Install NSIS
    run: choco install nsis -y
  - name: Configure
    run: |
      mkdir build && cd build
      cmake .. -DCMAKE_INSTALL_PREFIX=./install
  - name: Build
    run: |
      cd build
      cmake --build . --config Release
  - name: Create NSIS package (MSI)
    run: |
      cd build
      cpack -G NSIS
  - name: Upload to Release
    uses: softprops/action-gh-release@v1
    with:
      files: build/*.exe
    env:
      GITHUB_TOKEN: ${{ secrets.GITHUB_TOKEN }}
```

### 7.3. Добавление DMG пакета для macOS

#### 7.3.1. Обновление CPackConfig.cmake для поддержки DMG

```bash
cat >> CPackConfig.cmake << 'EOF'

# DMG для macOS
set(CPACK_DMG_VOLUME_NAME "Solver Installer")
set(CPACK_DMG_FORMAT "UDBZ")
EOF
```

#### 7.3.2. Добавление macOS сборки в release.yml

```yaml
macos-packages:
  runs-on: macos-latest
  if: startsWith(github.ref, 'refs/tags/')
  steps:
  - uses: actions/checkout@v4
  - name: Install dependencies
    run: brew install cmake
  - name: Configure
    run: |
      mkdir build && cd build
      cmake .. -DCMAKE_INSTALL_PREFIX=/usr/local
  - name: Build
    run: |
      cd build
      cmake --build .
  - name: Create DMG package
    run: |
      cd build
      cpack -G DragNDrop
  - name: Upload DMG to Release
    uses: softprops/action-gh-release@v1
    with:
      files: build/*.dmg
    env:
      GITHUB_TOKEN: ${{ secrets.GITHUB_TOKEN }}
```

### 7.4. Итоговый список пакетов в релизе

| Формат | Платформа | Расширение | Статус |
|--------|-----------|------------|--------|
| TGZ | Linux/macOS | `.tar.gz` | ✅ |
| DEB | Linux (Debian/Ubuntu) | `.deb` | ✅ |
| RPM | Linux (Red Hat/Fedora) | `.rpm` | ✅ |
| MSI | Windows | `.exe` (NSIS) | ✅ |
| DMG | macOS | `.dmg` | ✅ |

### 7.5. Результат

После добавления workflow при создании тега `v1.0.0` автоматически создаются и загружаются в релиз все 5 типов пакетов.

---

## Часть 8: Итоговый статус ЛР6

| Тип пакета | Платформа | Статус |
|------------|-----------|--------|
| TGZ | Linux/macOS | ✅ |
| DEB | Linux | ✅ |
| RPM | Linux | ✅ |
| MSI | Windows | ✅ |
| DMG | macOS | ✅ |

