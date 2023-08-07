# Mandelfash DLL

## Description

The idea here is a simple to use DLL file to integrate in languages with support to it to calculate a slash of the mandelfash fractal doing every pixel asynchronously.

This runs with high precision math (using Boost C++ Library) and many small optmizations to decrease the processing time.

This was originally coded by demand for Dave Fashenpour on 2018 as the final product of my hire.

## Usage

This project is separate in two parts.

The DLL that can be compiled and added to any other project and a C# system to make testing the DLL easier with visual interface.

To use the C# program, first you have to compile the DLL with target to Release - x64.

Besides that, after compiling the DLL, you should be able to use it according to the original documentations:

[Tutorial](./Mandelfash.dll%20Tutorial.pdf)

[Documentation](./Mandelfash.dll%20Documentation.pdf)

## Credits

Dave Fashenpour (Mathematician/Code Engineer): The contractor for this project and orginal coder that had a version of this calculator done in Basic which was used as an example on how to make this. This source was uploaded publicly with his permission.

## MIT License

Copyright (c) 2023 Erik Marques Schroeder

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
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
