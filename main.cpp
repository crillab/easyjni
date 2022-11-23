/**
 * EasyJNI - Invoking Java code from C++ made easy.
 * Copyright (c) 2022 - Univ Artois & CNRS.
 * All rights reserved.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 3 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library.
 * If not, see {@link http://www.gnu.org/licenses}.
 */

#include <exception>
#include <getopt.h>
#include <string>

#include <jni.h>
#include <iostream>

#include "easyjni/JavaClass.h"
#include "easyjni/JavaMethod.h"
#include "easyjni/JavaVirtualMachine.h"
#include "easyjni/JavaVirtualMachineBuilder.h"
#include "easyjni/JavaVirtualMachineRegistry.h"

using namespace easyjni;
using namespace std;

/**
 * Builds a Java Virtual Machine from the given command line arguments.
 *
 * @param argc The number of arguments given to the program.
 * @param argv The command line arguments.
 * @param mainClass The reference where to store the name of the main class to run.
 *
 * @return The index of the first argument to pass to the Java program in argv.
 */
int buildJvmFromArguments(int argc, char *argv[], string &mainClass) {
    JavaVirtualMachineBuilder builder;
    builder.setVersion(JNI_VERSION_10);
    opterr = 0;

    // Parsing named arguments.
    for (int opt; (opt = getopt(argc, argv, ":c:m:")) != -1;) {
        if (opt == ':') {
            string message = "Missing argument for option `-";
            message += (char) optopt;
            message += '\'';
            throw invalid_argument(message);

        } else if (opt == 'c') {
            builder.addToClasspath(optarg);

        } else if (opt == 'm') {
            mainClass = string(optarg);

        } else {
            string message = "Unknown option `-";
            message += (char) optopt;
            message += '\'';
            throw invalid_argument(message);
        }
    }

    // Building the Java Virtual Machine.
    auto jvm = builder.buildJavaVirtualMachine();
    JavaVirtualMachineRegistry::set(jvm);
    return optind;
}

/**
 * Builds the array of (Java) strings to pass to the Java program.
 *
 * @param first The index of the first arguments for the Java program.
 * @param argc The number of arguments given to the program.
 * @param argv The command line arguments.
 *
 * @return The array of arguments to pass to the Java program.
 */
JavaArray<JavaObject> buildJavaArguments(int first, int argc, char *argv[]) {
    auto jvm = JavaVirtualMachineRegistry::get();
    auto args = jvm->createObjectArray(argc - optind, jvm->loadClass("java/lang/String"));
    for (int i = first; i < argc; i++) {
        args.set(i - first, jvm->toJavaString(argv[i]));
    }
    return args;
}

/**
 * Executes the main method of a Java class.
 *
 * @param mainClass The name of the Java main class.
 * @param args The command line arguments to pass to the main method.
 */
void javaMain(const string &mainClass, JavaArray<JavaObject> args) {
    auto cls = JavaVirtualMachineRegistry::get()->loadClass(mainClass);
    auto mtd = cls.getStaticObjectMethod("main", METHOD(VOID, ARRAY(CLASS(java/lang/String))));
    mtd.invokeStatic(cls, *args);
}

/**
 * Executes a demonstration of EasyJNI.
 *
 * @param argc The number of arguments given to the program.
 * @param argv The command line arguments.
 *
 * @return The value 0 upon success.
 */
int main(int argc, char *argv[]) {
    string mainClass;
    int firstJavaArg = buildJvmFromArguments(argc, argv, mainClass);
    auto args = buildJavaArguments(firstJavaArg, argc, argv);
    javaMain(mainClass, args);
    return 0;
}
