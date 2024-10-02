## Description

This project implements a simple program to manipulate and calculate properties of a triangle defined by three points in 3D space. The program allows the user to translate the triangle along the x, y, or z axis, display the coordinates of the triangle's vertices, and calculate the area of the triangle.

## Files

- `Point.h`: Header file for the Point class.
- `Point.cpp`: Implementation file for the Point class.
- `Triangle.h`: Header file for the Triangle class.
- `Triangle.cpp`: Implementation file for the Triangle class.
- `main.cpp`: Main driver file that provides a menu for interacting with the triangle.
- `Part1.cpp`: Main driver file for Part 1, which includes functions to create, initialize, print, and delete a dynamic array.
- `ExampleRun1.txt`: A sample run that shows all the functionalities of Part 1.
- `ExampleRun2.txt`: A sample run that shows all the functionalities of Part 2.

## Requirements

- g++ (MinGW-w64) or any C++ compiler
- Windows 10 (or any other OS with a compatible compiler)

## Setup and Compilation

### Using MinGW on Windows

1. **Install MinGW-w64**:
   - Download and install MinGW-w64 from [Mingw-w64](https://www.mingw-w64.org/).
   - Add the `bin` directory of MinGW-w64 to your system's `PATH` environment variable.

2. **Clone or Download the Repository**:
   - If you have `git` installed, you can clone the repository:
     ```sh
     git clone https://github.com/yourusername/3D-Triangle-Operations.git
     ```
   - Alternatively, download the ZIP file and extract it.

3. **Navigate to the Project Directory**:
   ```sh
   cd path_to_project_directory

4. **Compile the Code for Part 1**:
   ```sh
   g++ -o Part1 Part1.cpp

6. **Compile the Code for Part 2**:
   ```sh
   g++ -o Part2 Point.cpp Triangle.cpp main.cpp

8. **Run the Code for Part 1**:
   ```sh
   .\Part1.exe

9. **Run the Code for Part 2**:
   ```sh
   .\Part2.exe
