# Doubly Linked Sorted List

This project is a C++ implementation of a Doubly Linked Sorted List. It demonstrates the use of modern C++ features, including smart pointers, exception handling, and multithreading. The project also includes comprehensive unit tests using Google Test.

## Features

- Implementation of a Doubly Linked Sorted List in C++.
- Use of modern C++ features like smart pointers for automatic memory management.
- Exception handling to manage runtime errors.
- Multithreading for efficient insertion of nodes in the list.
- Comprehensive unit tests using Google Test.
- Use of CMake for build system.

## Getting Started

### Prerequisites

- C++ compiler with support for C++20; tested on: 
  - gcc 13.2.0
  - clang 17.0.6
- CMake 3.26 or higher.

### Building the Project

1. Clone the repository.
2. Navigate to the project directory.
3. Run `cmake --preset <chosen-preset-build-to-find-in-CMakePresets.json>` to generate the build files.
4. cd to root build directory
5. Run `cmake --build --target main` to build the main binary.
5. Run ```cmake --build --target testsTarget``` to build tests binary.

## Running the Tests

After building the project, you can run the tests by executing the test binary in the `test` directory.

## Contributing

Contributions are welcome. Please open an issue to discuss your proposed changes or create a pull request.

