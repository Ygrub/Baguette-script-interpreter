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

## Installation

There are two options for running the interpreter:

1. Using the Compiled Executable (Windows):

a. Download the compiled executable (.exe) file.
b. Place the executable in the same folder as your baguette script file (.bgs).
c. Open a terminal or command prompt and navigate to the folder containing the executable.
d. Run the command:

  ```
  inte 'path\to\your\*.bgs\file'
  ```

  Replace `'path\to\your\*.bgs\file'` with the actual path to your baguette script file.

2. Using the Source Code:

a. Compile the source code (inte.cpp) using a C++ compiler.
b. Follow steps c and d from option 1, replacing inte with the name of your compiled executable.

## Usage

This interpreter can execute baguette script files. The script files should have the .bgs extension.

## Modifying the Source Code

The interpreter logic is contained in the inte.cpp file. You can modify this file to customize the interpreter's behavior. For example, you could change:

    Tokenization rules
    Optimization techniques
    Add new functionalities

## Note on Performance

The current implementation is a basic example and might not be optimized for speed. The provided example script (exemple1.bgs) takes approximately 3 seconds to run.

## License

**MIT License**

Copyright (c) [2024] [Ygrub]

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated
 documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

## Contributing

**We welcome contributions to the Baguette Script Interpreter!**

### Getting Started
1. Fork the repository.
2. Clone your forked repository to your local machine.
3. Set up your development environment (e.g., install dependencies).

### Code Style
* Use consistent indentation (4 spaces).
* Follow C++ coding conventions.

### Issues
To report a bug or request a feature, please open an issue on the GitHub repository.

### Pull Requests
* Fork the repository and create a feature branch.
* Write clear and concise commit messages.
* Submit a pull request with a detailed description of your changes.

### Code of Conduct
We follow the Contributor Covenant: [link to code of conduct]

**Thank you for contributing!**
