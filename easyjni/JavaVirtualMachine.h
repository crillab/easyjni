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

#ifndef EASYJNI_JAVAVIRTUALMACHINE_H
#define EASYJNI_JAVAVIRTUALMACHINE_H

#include <string>

#include <jni.h>


namespace easyjni {
    template<typename T> class JavaArray;
    class JavaObject;
    class JavaClass;
    /**
     * The JavaVirtualMachine class encapsulates the instance of the Java
     * Virtual Machine to use to run Java code.
     *
     * @author Romain Wallon
     *
     * @version 0.1.0
     */
    class JavaVirtualMachine {

    private:

        /**
         * The native Java Virtual Machine provided by JNI.
         */
        JavaVM *jvm;

        /**
         * The native Java Environment provided by JNI.
         */
        JNIEnv *env;

        /**
         * Whether this Java Virtual Machine is the main one.
         */
        bool main;

    private:

        /**
         * Creates a new Java Virtual Machine.
         *
         * @param jvm The native Java Virtual Machine provided by JNI.
         * @param env The native Java Environment provided by JNI.
         * @param main Whether the Java Virtual Machine is the main one.
         */
        JavaVirtualMachine(JavaVM *jvm, JNIEnv *env, bool main = true);

    public:

        /**
         * Forbids the copy of an instance of Java Virtual Machine.
         */
        JavaVirtualMachine(JavaVirtualMachine &) = delete;

        /**
         * Forbids the copy of an instance of a Java Virtual Machine.
         */
        JavaVirtualMachine &operator=(JavaVirtualMachine &) = delete;

        /**
         * Destroys this Java Virtual Machine.
         */
        ~JavaVirtualMachine();

        /**
         * Gives the version of this Java Virtual Machine, represented with
         * the pair (major, minor).
         *
         * @return The version of this Java Virtual Machine.
         */
        std::pair<int, int> getVersion();

        /**
         * Loads a class from this Java Virtual Machine.
         *
         * @param name The name of the class to load.
         *
         * @return The class object representing the loaded class.
         *
         * @throws JniException If the class cannot be loaded.
         */
        easyjni::JavaClass loadClass(const std::string &name);

        /**
         * Converts a string into a Java string.
         *
         * @param str The string to convert to a Java string.
         *
         * @return A Java representation of the string.
         */
        easyjni::JavaObject toJavaString(const std::string &str);

        /**
         * Converts a string into a Java string.
         *
         * @param str The string to convert to a Java string.
         *
         * @return A Java representation of the string.
         */
        easyjni::JavaObject toJavaString(const char *str);

        /**
         * Wraps a boolean value into an object.
         *
         * @param b The value to wrap.
         *
         * @return The wrapped value.
         *
         * @throws JniException If an error occurred while wrapping the value.
         */
        easyjni::JavaObject wrap(jboolean b);

        /**
         * Wraps a byte value into an object.
         *
         * @param b The value to wrap.
         *
         * @return The wrapped value.
         *
         * @throws JniException If an error occurred while wrapping the value.
         */
        easyjni::JavaObject wrap(jbyte b);

        /**
         * Wraps a char value into an object.
         *
         * @param c The value to wrap.
         *
         * @return The wrapped value.
         *
         * @throws JniException If an error occurred while wrapping the value.
         */
        easyjni::JavaObject wrap(jchar c);

        /**
         * Wraps a short value into an object.
         *
         * @param s The value to wrap.
         *
         * @return The wrapped value.
         *
         * @throws JniException If an error occurred while wrapping the value.
         */
        easyjni::JavaObject wrap(jshort s);

        /**
         * Wraps an int value into an object.
         *
         * @param i The value to wrap.
         *
         * @return The wrapped value.
         *
         * @throws JniException If an error occurred while wrapping the value.
         */
        easyjni::JavaObject wrap(jint i);

        /**
         * Wraps a long value into an object.
         *
         * @param l The value to wrap.
         *
         * @return The wrapped value.
         *
         * @throws JniException If an error occurred while wrapping the value.
         */
        easyjni::JavaObject wrap(jlong l);

        /**
         * Wraps a float value into an object.
         *
         * @param f The value to wrap.
         *
         * @return The wrapped value.
         *
         * @throws JniException If an error occurred while wrapping the value.
         */
        easyjni::JavaObject wrap(jfloat f);

        /**
         * Wraps a double value into an object.
         *
         * @param d The value to wrap.
         *
         * @return The wrapped value.
         *
         * @throws JniException If an error occurred while wrapping the value.
         */
        easyjni::JavaObject wrap(jdouble d);

        /**
         * Unwraps a boolean value from an object.
         *
         * @param b The object wrapping the value.
         *
         * @return The unwrapped value.
         *
         * @throws JniException If an error occurred while unwrapping the value.
         */
        jboolean unwrapAsBoolean(const easyjni::JavaObject &b);

        /**
         * Unwraps a byte value from an object.
         *
         * @param b The object wrapping the value.
         *
         * @return The unwrapped value.
         *
         * @throws JniException If an error occurred while unwrapping the value.
         */
        jbyte unwrapAsByte(const easyjni::JavaObject &b);

        /**
         * Unwraps a char value from an object.
         *
         * @param c The object wrapping the value.
         *
         * @return The unwrapped value.
         *
         * @throws JniException If an error occurred while unwrapping the value.
         */
        jchar unwrapAsChar(const easyjni::JavaObject &c);

        /**
         * Unwraps a short value from an object.
         *
         * @param s The object wrapping the value.
         *
         * @return The unwrapped value.
         *
         * @throws JniException If an error occurred while unwrapping the value.
         */
        jshort unwrapAsShort(const easyjni::JavaObject &s);

        /**
         * Unwraps a int value from an object.
         *
         * @param i The object wrapping the value.
         *
         * @return The unwrapped value.
         *
         * @throws JniException If an error occurred while unwrapping the value.
         */
        jint unwrapAsInt(const easyjni::JavaObject &i);

        /**
         * Unwraps a long value from an object.
         *
         * @param l The object wrapping the value.
         *
         * @return The unwrapped value.
         *
         * @throws JniException If an error occurred while unwrapping the value.
         */
        jlong unwrapAsLong(const easyjni::JavaObject &l);

        /**
         * Unwraps a float value from an object.
         *
         * @param f The object wrapping the value.
         *
         * @return The unwrapped value.
         *
         * @throws JniException If an error occurred while unwrapping the value.
         */
        jfloat unwrapAsFloat(const easyjni::JavaObject &f);

        /**
         * Unwraps a double value from an object.
         *
         * @param d The object wrapping the value.
         *
         * @return The unwrapped value.
         *
         * @throws JniException If an error occurred while unwrapping the value.
         */
        jdouble unwrapAsDouble(const easyjni::JavaObject &d);

        /**
         * Creates an array of boolean values in the Java Virtual Machine.
         *
         * @param size The size of the array.
         *
         * @return The created array.
         */
        easyjni::JavaArray<jboolean> createBooleanArray(int size);

        /**
         * Creates an array of byte values in the Java Virtual Machine.
         *
         * @param size The size of the array.
         *
         * @return The created array.
         */
        easyjni::JavaArray<jbyte> createByteArray(int size);

        /**
         * Creates an array of char values in the Java Virtual Machine.
         *
         * @param size The size of the array.
         *
         * @return The created array.
         */
        easyjni::JavaArray<jchar> createCharArray(int size);

        /**
         * Creates an array of short values in the Java Virtual Machine.
         *
         * @param size The size of the array.
         *
         * @return The created array.
         */
        easyjni::JavaArray<jshort> createShortArray(int size);

        /**
         * Creates an array of int values in the Java Virtual Machine.
         *
         * @param size The size of the array.
         *
         * @return The created array.
         */
        easyjni::JavaArray<jint> createIntArray(int size);

        /**
         * Creates an array of long values in the Java Virtual Machine.
         *
         * @param size The size of the array.
         *
         * @return The created array.
         */
        easyjni::JavaArray<jlong> createLongArray(int size);

        /**
         * Creates an array of float values in the Java Virtual Machine.
         *
         * @param size The size of the array.
         *
         * @return The created array.
         */
        easyjni::JavaArray<jfloat> createFloatArray(int size);

        /**
         * Creates an array of double values in the Java Virtual Machine.
         *
         * @param size The size of the array.
         *
         * @return The created array.
         */
        easyjni::JavaArray<jdouble> createDoubleArray(int size);

        /**
         * Creates an array of objects in the Java Virtual Machine.
         *
         * @param size The size of the array.
         *
         * @return The created array.
         */
        easyjni::JavaArray<easyjni::JavaObject> createObjectArray(int size, const easyjni::JavaClass &clazz);

        /**
         * Checks whether an exception occurred in this Java Virtual Machine,
         * and throws it when this is the case.
         */
        void checkException();

        /**
         * The JavaVirtualMachineBuilder is a friend class, which allows
         * to build instances of JavaVirtualMachine.
         */
        friend class JavaVirtualMachineBuilder;

        /**
         * The JavaVirtualMachineRegistry is a friend class, which allows
         * to attach a thread to a JavaVirtualMachine.
         */
        friend class JavaVirtualMachineRegistry;

    };

}

#endif
