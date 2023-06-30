/**
 * EasyJNI - Invoking Java code from C++ made easy.
 * Copyright (c) 2022 - Univ Artois & CNRS & Exakis Nelite.
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

#ifndef EASYJNI_JAVAVIRTUALMACHINEBUILDER_H
#define EASYJNI_JAVAVIRTUALMACHINEBUILDER_H

#include <string>
#include <vector>

#include <jni.h>

#include "JavaVirtualMachine.h"

namespace easyjni {

    /**
     * The JavaVirtualMachineBuilder provides a user-friendly interface for
     * building instances of Java Virtual Machines with the needed options.
     *
     * @author Romain Wallon
     *
     * @version 0.1.0
     */
    class JavaVirtualMachineBuilder {

    private:

        /**
         * The wanted version for the Java Virtual Machine.
         */
        jint version;

        /**
         * The path of the files to put in the classpath of the Java Virtual Machine.
         */
        std::vector<std::string> classpath;

        /**
         * The other options for the Java Virtual Machine.
         */
        std::vector<std::string> options;

    public:

        /**
         * Creates a new JavaVirtualMachineBuilder.
         * The default version for the Java Virtual Machine is 1.8.
         */
        JavaVirtualMachineBuilder();

        /**
         * Sets the wanted version for the Java Virtual Machine.
         *
         * @param version The wanted version for the Java Virtual Machine.
         *
         * @return This builder.
         */
        JavaVirtualMachineBuilder &setVersion(int version);

        /**
         * Adds a file to the classpath of the Java Virtual Machine.
         *
         * @param path The path of the file to add to the classpath.
         *
         * @return This builder.
         */
        JavaVirtualMachineBuilder &addToClasspath(const std::string &path);

        /**
         * Adds an option for the Java Virtual Machine.
         *
         * @param name The name of the option to add.
         *
         * @return This builder.
         */
        JavaVirtualMachineBuilder &addOption(const std::string &name);

        /**
         * Adds an option for the Java Virtual Machine.
         *
         * @param name The name of the option to add.
         * @param value The value of the option to add.
         *
         * @return This builder.
         */
        JavaVirtualMachineBuilder &addOption(const std::string &name, const std::string &value);

        /**
         * Builds the instance of Java Virtual Machine that has been set up.
         *
         * @return The created Java Virtual Machine.
         */
        JavaVirtualMachine *buildJavaVirtualMachine();

    private:

        /**
         * Builds the classpath string to use as option to the Java Virtual Machine.
         *
         * @return The classpath string.
         */
        std::string buildClasspath();

    };

}

#endif
