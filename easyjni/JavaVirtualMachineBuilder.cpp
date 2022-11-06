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

#include <filesystem>
#include <iterator>
#include <sstream>

#include "JavaVirtualMachineBuilder.h"
#include "JniException.h"

#ifdef _WIN32
#define CLASSPATH_SEPARATOR ";"
#else
#define CLASSPATH_SEPARATOR ":"
#endif

using namespace easyjni;
using namespace std;

JavaVirtualMachineBuilder::JavaVirtualMachineBuilder() :
        version(JNI_VERSION_1_8),
        classpath(),
        options() {
    // Nothing to do: everything is already initialized.
}

JavaVirtualMachineBuilder &JavaVirtualMachineBuilder::setVersion(int version) {
    this->version = version;
    return *this;
}

JavaVirtualMachineBuilder &JavaVirtualMachineBuilder::addToClasspath(const string &path) {
    filesystem::path filepath(path);
    filepath = filepath.make_preferred();
    classpath.push_back(filepath.string());
    return *this;
}

JavaVirtualMachineBuilder &JavaVirtualMachineBuilder::addOption(const string &name) {
    options.emplace_back(name);
    return *this;
}

JavaVirtualMachineBuilder &JavaVirtualMachineBuilder::addOption(const string &name, const string &value) {
    options.emplace_back(name + "=" + value);
    return *this;
}

JavaVirtualMachine *JavaVirtualMachineBuilder::buildJavaVirtualMachine() {
    // Adding the classpath as an option.
    if (!classpath.empty()) {
        addOption("-Djava.class.path", buildClasspath());
    }

    // Building the options for the JVM.
    auto *vmOptions = new JavaVMOption[options.size()];
    for (int i = 0; i < options.size(); i++) {
        vmOptions[i].optionString = (char *) options[i].c_str();
    }

    // Building the JVM arguments.
    JavaVMInitArgs jvmArgs;
    jvmArgs.version = version;
    jvmArgs.options = vmOptions;
    jvmArgs.nOptions = (jint) options.size();
    jvmArgs.ignoreUnrecognized = false;

    // Creating the JVM.
    JavaVM *jvm;
    JNIEnv *env;
    jint result = JNI_CreateJavaVM(&jvm, (void**) &env, &jvmArgs);
    delete[] vmOptions;
    if (result == JNI_OK) {
        return new JavaVirtualMachine(jvm, env);
    }

    // The JVM could not be created.
    throw JniException("Could not create a Java Virtual Machine");
}

string JavaVirtualMachineBuilder::buildClasspath() {
    stringstream result;
    copy(classpath.begin(), classpath.end(), ostream_iterator<string>(result, CLASSPATH_SEPARATOR));
    return result.str();
}
