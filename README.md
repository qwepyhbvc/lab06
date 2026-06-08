# Lab05: Unit Testing with Google Test

[![CI](https://github.com/qwepyhbvc/lab05/actions/workflows/ci.yml/badge.svg)](https://github.com/qwepyhbvc/lab05/actions/workflows/ci.yml)

## About

This project demonstrates unit testing with Google Test framework.

## Build with Tests

```bash
mkdir build && cd build
cmake .. -DBUILD_TESTS=ON
cmake --build .
ctest --verbose
