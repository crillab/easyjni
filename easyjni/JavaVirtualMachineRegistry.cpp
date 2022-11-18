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

#include "JavaVirtualMachineRegistry.h"
#include "JniException.h"

using namespace easyjni;
using namespace std;

JavaVirtualMachine *JavaVirtualMachineRegistry::globalJvm = nullptr;
map<thread::id, JavaVirtualMachine *> JavaVirtualMachineRegistry::jvmByThread;
mutex JavaVirtualMachineRegistry::mutex;

void JavaVirtualMachineRegistry::set(JavaVirtualMachine *jvm) {
    mutex.lock();
    if (globalJvm != nullptr) {
        mutex.unlock();
        throw JniException("A Java Virtual Machine already exists");
    }

    globalJvm = jvm;
    jvmByThread[this_thread::get_id()] = jvm;

    mutex.unlock();
}

JavaVirtualMachine *JavaVirtualMachineRegistry::get() {
    mutex.lock();

    // If the current thread is already attached to a JVM, this JVM is returned.
    auto jvm = jvmByThread.find(this_thread::get_id());
    if (jvm != jvmByThread.end()) {
        mutex.unlock();
        return jvm->second;
    }

    // The current thread has to be attached to a "new" JVM.
    JNIEnv *env;
    globalJvm->jvm->AttachCurrentThread((void **) &env, nullptr);
    auto newJvm = new JavaVirtualMachine(globalJvm->jvm, env, false);
    jvmByThread[this_thread::get_id()] = newJvm;

    mutex.unlock();
    return newJvm;
}

void JavaVirtualMachineRegistry::detachCurrentThread() {
    mutex.lock();

    // If the current thread is not attached, there is nothing to do.
    auto jvm = jvmByThread.find(this_thread::get_id());
    if (jvm == jvmByThread.end()) {
        mutex.unlock();
        return;
    }

    // We make sure not do detach the main thread.
    if (jvm->second == globalJvm) {
        mutex.unlock();
        throw JniException("Cannot detach the main thread");
    }

    // Otherwise, the thread is detached and its JavaVirtualMachine is deleted.
    globalJvm->jvm->DetachCurrentThread();
    //delete jvm->second;
    jvmByThread.erase(this_thread::get_id());

    mutex.unlock();
}

void JavaVirtualMachineRegistry::clear() {
    if (globalJvm != nullptr) {
        mutex.lock();

        // Each JVM must be destroyed.
        for (auto &jvm : jvmByThread) {
            delete jvm.second;
        }

        // We restore all fields to their initial state.
        globalJvm = nullptr;
        jvmByThread.clear();

        mutex.unlock();
    }
}
