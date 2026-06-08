# Lab05: Unit Testing with Google Test

[![CI](https://github.com/qwepyhbvc/lab05/actions/workflows/ci.yml/badge.svg)](https://github.com/qwepyhbvc/lab05/actions/workflows/ci.yml)

## Project Structure
lab05/
├── banking_lib/ # Banking library (Homework)
│ ├── include/
│ │ ├── Account.h
│ │ └── Transaction.h
│ ├── src/
│ │ ├── Account.cpp
│ │ └── Transaction.cpp
│ └── tests/
│ ├── test_account.cpp
│ └── test_transaction.cpp
├── sources/ # Print library
│ └── print.cpp
├── include/
│ └── print.hpp
├── tests/
│ └── test_print.cpp
└── CMakeLists.txt
## Tests Coverage

### Print Library (3 tests)
- ✅ `Print.InFileStream` - write to file
- ✅ `Print.CoutStream` - write to console
- ✅ `Print.OStringStream` - write to string stream

### Banking Library (18 tests)

**Account Class (10 tests):**
- ✅ Constructor with initial balance
- ✅ Constructor with zero balance
- ✅ Deposit positive amount
- ✅ Deposit zero amount
- ✅ Deposit negative amount
- ✅ Withdraw valid amount
- ✅ Withdraw exact balance
- ✅ Withdraw insufficient funds
- ✅ Withdraw negative amount
- ✅ Withdraw zero amount

**Transaction Class (8 tests):**
- ✅ Execute valid transaction
- ✅ Execute with insufficient funds
- ✅ Execute with zero amount
- ✅ Execute with negative amount
- ✅ Execute already completed transaction
- ✅ Revert completed transaction
- ✅ Revert not completed transaction
- ✅ Get timestamp

## Build and Run

```bash
# Build print tests
mkdir build-print && cd build-print
cmake .. -DBUILD_TESTS=ON
cmake --build .
ctest --verbose

# Build banking tests
mkdir build-banking && cd build-banking
cmake .. -DBUILD_BANKING_TESTS=ON
cmake --build .
ctest --verbose

# Build all tests
mkdir build && cd build
cmake .. -DBUILD_TESTS=ON -DBUILD_BANKING_TESTS=ON
cmake --build .
ctest --verbose
CI Pipeline

GitHub Actions runs:

    Print library tests (GCC and Clang)

    Banking library tests (GCC and Clang)

    Windows tests (MSVC)
    EOF
