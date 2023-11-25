# Bentomark 2

![Issues](https://img.shields.io/github/issues/taldoflemis/bentomark-2)
![Pull requests](https://img.shields.io/github/issues-pr/taldoflemis/bentomark-2)

Bentomark-2 is a C++ library for benchmarking numeric methods.

## Development

### Prerequisites

Make sure you have the following tools installed:

- [CMake](https://cmake.org/cmake/help/latest/command/install.html): Required for building the project
- [Make](https://stackoverflow.com/questions/32127524/how-to-install-and-use-make-in-windows): Build automation tool

### Running Locally

To run this project locally, follow these steps:

1. Use CMake to generate the Make build system:

   ```bash
   cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=ON .
   ```

   The `-DCMAKE_EXPORT_COMPILE_COMMANDS` flag is essential for your Language Server Protocol (LSP), such as CLANG, to acquire symbols.

2. Build the project with Make:

   ```bash
   make run_cli
   ```
