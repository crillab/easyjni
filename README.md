# EasyJNI - Invoking Java code from C++ made easy

## Description

This project provides a wrapper for the Java Native Interface (JNI) to provide
a more user-friendly interface to interact with Java code from C++.
This interface is designed to be closer to the reflection API provided by Java.

## Building EasyJNI

`EasyJNI` requires a JDK to be installed on your computer.

`EasyJNI` is developed using [C++ 17](https://en.cppreference.com/w/cpp/17) and
[CMake 3.23](https://cmake.org/).
Installing CMake is required if you want to build from source.
To do so, after having installed all the needed tools, you will need to clone
the project:

```bash
git clone https://github.com/crillab/easyjni.git
cd easyjni
mkdir build
cd build
cmake .. -DCMAKE_BUILD_TYPE=RELEASE
cmake --build .
```

## Using EasyJNI as a library

This library is designed for simplified use in projects using CMake.
To use this project, it is possible to create a submodule in your project
with the following commands:

```bash
git submodule add https://github.com/crillab/easyjni.git libs/easyjni
git submodule update --remote --init --recursive
```

And then, add the following instructions in your `CMakeLists.txt` file:

```cmake
add_subdirectory(libs/easyjni)
add_executable(your_app your_app.h your_app.cpp)
target_link_libraries(your_app libeasyjni)
```

## Example

A built-in example can be found [here](main.cpp).
This example allows to run any Java program as follows:

```bash
./build/easyjni-demo -c a/classpath/entry -c a/file.jar -m my/awesome/MainClass -- arg1 arg2 arg3
```

The command above runs the main method defined in the Java class
`my.awesome.MainClass`, and passes `arg1`, `arg2` and `arg3` as arguments
to this program.
The classpath for running this program is made of `a/classpath/entry` and
`a/file.jar`.

> **Note**
>
> The built-in example can only be built on UNIX systems, as it uses `getopt()`
> to parse the command line, which is not available on Windows.
> However, the library itself may be compiled and used on any operating
> system.
