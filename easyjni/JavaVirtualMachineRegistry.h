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

#ifndef EASYJNI_JAVAVIRTUALMACHINEREGISTRY_H
#define EASYJNI_JAVAVIRTUALMACHINEREGISTRY_H

#include <map>
#include <mutex>
#include <thread>

#include "JavaVirtualMachine.h"

namespace easyjni {

    /**
     * The JavaVirtualMachineRegistry allows to make instances of the Java
     * Virtual Machine globally accessible.
     *
     * @author Romain Wallon
     *
     * @version 0.1.0
     */
    class JavaVirtualMachineRegistry {

    private:

        /**
         * The main instance of Java Virtual Machine.
         */
        static easyjni::JavaVirtualMachine *mainJvm;

        /**
         * The Java Virtual Machines to which the different threads are attached.
         */
        static std::map<std::thread::id, easyjni::JavaVirtualMachine *> jvmByThread;

        /**
         * The mutex used to avoid concurrent accesses to the map of Java Virtual Machines.
         */
        static std::mutex mutex;

    public:

        /**
         * Disables instantiation.
         */
        JavaVirtualMachineRegistry() = delete;

        /**
         * Registers a global instance of Java Virtual Machine.
         *
         * @param jvm The Java Virtual Machine to register.
         *
         * @throws JniException If a Java Virtual Machine has already been registered.
         */
        static void set(JavaVirtualMachine *jvm);

        /**
         * Gives the instance of Java Virtual Machine attached to the current thread.
         *
         * @return The instance of Java Virtual Machine, or nullptr if no Java Virtual Machine
         *         has been registered yet.
         */
        static JavaVirtualMachine *get();

        /**
         * Gives the environment of the Java Virtual Machine attached to the current thread.
         *
         * @return The environment of the Java Virtual Machine, or nullptr if no Java Virtual
         *         Machine has been registered yet.
         */
        static JNIEnv *getEnvironment();

        /**
         * Detaches the current thread from the Java Virtual Machine.
         *
         * @throws JniException If the current thread is the main thread.
         */
        static void detachCurrentThread();

        /**
         * Destroys the main instance of Java Virtual Machine.
         */
        static void clear();

    };

}

#endif
