# Lab04: Continuous Integration

[![CI](https://github.com/qwepyhbvc/lab04/actions/workflows/ci.yml/badge.svg)](https://github.com/qwepyhbvc/lab04/actions/workflows/ci.yml)

## Build Status

✅ CI passing on Linux (GCC/Clang) and Windows

## Project Structure

- `formatter_lib/` - Static library for string formatting
- `formatter_ex_lib/` - Extended formatter library  
- `solver_lib/` - Quadratic equation solver library
- `hello_world_application/` - Hello World demo
- `solver_application/` - Interactive equation solver

## Local Build

```bash
mkdir build && cd build
cmake ..
cmake --build .
./hello_world_application/hello_world
echo "1 -3 2" | ./solver_application/equation
