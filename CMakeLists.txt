# Configuring CMake.
cmake_minimum_required(VERSION 3.23)
set(CMAKE_CXX_STANDARD 17)

# Declaring the project.
project(easyjni)
set(LIBRARY_NAME easyjni)

# Configuring the use of JNI.
find_package(JNI REQUIRED)
include_directories(${JNI_INCLUDE_DIRS})

# Adding the library to the build targets.
add_library(${LIBRARY_NAME}

        easyjni/JavaArray.h easyjni/JavaArray.cpp
        easyjni/JavaClass.h easyjni/JavaClass.cpp
        easyjni/JavaElement.h easyjni/JavaElement.cpp
        easyjni/JavaField.h easyjni/JavaField.cpp
        easyjni/JavaMethod.h easyjni/JavaMethod.cpp
        easyjni/JavaObject.h easyjni/JavaObject.cpp
        easyjni/JavaSignature.h

        easyjni/JavaVirtualMachine.h easyjni/JavaVirtualMachine.cpp
        easyjni/JavaVirtualMachineBuilder.h easyjni/JavaVirtualMachineBuilder.cpp
        easyjni/JavaVirtualMachineRegistry.h easyjni/JavaVirtualMachineRegistry.cpp

        easyjni/JniException.h easyjni/JniException.cpp)
target_link_libraries(${LIBRARY_NAME} ${JNI_LIBRARIES})

# Adding the executable (for demonstration purposes) to the build targets.
# It is only built on UNIX systems because of the use of getopt().
if (UNIX)
    add_executable(${LIBRARY_NAME}-demo main.cpp)
    target_link_libraries(${LIBRARY_NAME}-demo ${LIBRARY_NAME})
endif (UNIX)
