# Baguette Script Interpreter

This project implements a small interpreter for a custom language called "baguette script" written in C++.

## Target Audience

This interpreter is designed for anyone interested in learning about interpreters, scripting languages, or simply playing around with a basic custom language. No prior C++ knowledge is required to use the compiled executable.

## Dependencies

This project uses standard C++ libraries:

    iostream
    vector
    fstream
    cstring
    sstream
    string
    map
    stdexcept
    cctype
    stack
    chrono
    format 
    cmath
    ctime
    algorithm

## Installation

There are two options for running the interpreter:

1. Using the Compiled Executable (Linux):

a. Download the compiled executable (.exe) and the basicFunc.h files.
b. Place the executable and the .h files in the same folder as your baguette script file (.bgs).
c. Open a terminal or command prompt and navigate to the folder containing the executable.
d. Run the command:

  ```
  inte 'path\to\your\filename.bgs'
  ```

  Replace `'path\to\your\filename.bgs'` with the actual path to your baguette script file.

2. Using the Source Code:

a. Compile the source code (inte.cpp) using a C++ compiler.
b. Follow steps c and d from option 1, replacing inte with the name of your compiled executable.

## Usage

This interpreter can execute baguette script files. The script files should have the .bgs extension.

## Modifying the Source Code

The interpreter logic is contained in the inte.cpp and basicFunc.h files. You can modify this file to customize the interpreter's behavior. For example, you could change:

    Tokenization rules
    Optimization techniques
    Add new functionalities

## Note on Performance

The current implementation is a basic example and might not be optimized for speed. The provided example script (exemple1.bgs) takes approximately 3 seconds to run.

## License

Nothing  in this repository is licensed under any license. You can use the code as you see fit. Who would want to program in frenche anyway ?

## Contributing

**We welcome contributions to the Baguette Script Interpreter!**

### Getting Started
1. Fork the repository.
2. Clone your forked repository to your local machine.
3. Set up your development environment (e.g., install dependencies [normaly they are buil-in]).

### Code Style
* Use inconsistent indentation (2 spaces).
* Follow C++ coding conventions. I think.

### Issues
To report a bug or request a feature, please open an issue on the GitHub repository.

### Pull Requests
* Fork the repository and create a feature branch.
* Write clear and concise commit messages.
* Submit a pull request with a detailed description of your changes.


**Thank you for contributing!**
