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

#include "JavaVirtualMachineRegistry.h"
#include "JniException.h"

using namespace easyjni;
using namespace std;

JavaVirtualMachine *JavaVirtualMachineRegistry::mainJvm = nullptr;
map<thread::id, JavaVirtualMachine *> JavaVirtualMachineRegistry::jvmByThread;
mutex JavaVirtualMachineRegistry::mutex;

void JavaVirtualMachineRegistry::set(JavaVirtualMachine *jvm) {
    mutex.lock();

    if (mainJvm != nullptr) {
        // We cannot overwrite the existing main JVM.
        mutex.unlock();
        throw JniException("A Java Virtual Machine already exists");
    }

    // The JVM is saved, and attached to the current thread.
    mainJvm = jvm;
    jvmByThread[this_thread::get_id()] = jvm;

    mutex.unlock();
}

JavaVirtualMachine *JavaVirtualMachineRegistry::get() {
    mutex.lock();

    // If there is no JVM at all, there is nothing to return.
    if (mainJvm == nullptr) {
        mutex.unlock();
        return nullptr;
    }

    // If the current thread is already attached to a JVM, this JVM is returned.
    auto jvm = jvmByThread.find(this_thread::get_id());
    if (jvm != jvmByThread.end()) {
        mutex.unlock();
        return jvm->second;
    }

    // The current thread has to be attached to a "new" JVM.
    JNIEnv *env;
    mainJvm->jvm->AttachCurrentThread((void **) &env, nullptr);
    auto newJvm = new JavaVirtualMachine(mainJvm->jvm, env, false);
    jvmByThread[this_thread::get_id()] = newJvm;

    mutex.unlock();
    return newJvm;
}

JNIEnv *JavaVirtualMachineRegistry::getEnvironment() {
    auto jvm = get();
    if (jvm == nullptr) {
        return nullptr;
    }
    return jvm->env;
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
    if (jvm->second == mainJvm) {
        mutex.unlock();
        throw JniException("Cannot detach the main thread");
    }

    // Otherwise, the thread is detached and its JavaVirtualMachine is deleted.
    mainJvm->jvm->DetachCurrentThread();
    delete jvm->second;
    jvmByThread.erase(this_thread::get_id());

    mutex.unlock();
}

void JavaVirtualMachineRegistry::clear() {
    mutex.lock();

    if (mainJvm != nullptr) {
        // Each JVM must be destroyed.
        delete mainJvm;
        for (auto &jvm : jvmByThread) {
            delete jvm.second;
        }

        // We restore all fields to their initial state.
        mainJvm = nullptr;
        jvmByThread.clear();
    }

    mutex.unlock();
}
