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

#ifndef EASYJNI_JAVAOBJECT_H
#define EASYJNI_JAVAOBJECT_H

#include <string>

#include <jni.h>


namespace easyjni {
    template<typename T>
    class JavaArray;
    /**
     * Forward declaration of JavaClass, the class that represents the Java class of
     * an object from the Java Virtual Machine.
     */
    class JavaClass;

    /**
     * Forward declaration of JavaVirtualMachine, the class that encapsulates the instance
     * of the Java Virtual Machine to use to run Java code.
     */
    class JavaVirtualMachine;

    /**
     * The JavaObject represents an object from the Java Virtual Machine.
     *
     * @author Romain Wallon
     *
     * @version 0.1.0
     */
    class JavaObject {

    private:

        /**
         * The native pointer to the object in the Java Virtual Machine.
         */
        jobject nativeObject;

    private:

        /**
         * Creates a new JavaObject.
         *
         * @param environment The Java environment in which the object has been created.
         * @param nativeObject Tha native pointer to the object in the Java Virtual Machine.
         */
        JavaObject(jobject nativeObject);

    public:

        /**
         * Provides an object view of an array.
         *
         * @tparam T The type of the element in the array.
         *
         * @param array The array to give an object view of.
         *
         * @return The object view of the array.
         */
        template<typename T>
        static easyjni::JavaObject fromArray(JavaArray<T> array) {
            return JavaObject(array.array);
        }

        /**
         * Provides an array view of this object.
         *
         * @tparam T The type of the elements in the array.
         *
         * @return The array view of this object.
         */
        template<typename T>
        easyjni::JavaArray<T> toArray() {
            return JavaArray<T>::asArray(nativeObject);
        }

        /**
         * Checks whether this object is a null Java object.
         *
         * @return Whether this object is null.
         */
        bool isNull();

        /**
         * Gives the native pointer to the object in the Java Virtual Machine.
         *
         * @return The native pointer to the object in the Java Virtual Machine.
         */
        jobject operator*();

        /**
         * Gives the runtime class of this object.
         *
         * @return The Java class of this object.
         */
        easyjni::JavaClass getClass();

        /**
         * Gives a hash code value for this object.
         *
         * @return A hash code value for this object.
         */
        int hashCode();

        /**
         * Indicates whether some other object is "equal to" this one.
         *
         * @param other The reference object with which to compare.
         *
         * @return Whether this object is equal to the given one.
         */
        bool equals(easyjni::JavaObject &other);

        /**
         * Gives a string representation of this object.
         *
         * @return The representation of this object as a string.
         */
        std::string toString();

        /**
         * The JavaVirtualMachine is a friend class, which allows to create instances of
         * JavaObject by extracting objects from the JVM.
         */
        friend class JavaVirtualMachine;

        /**
         * The JavaClass is a friend class, which allows to build instances of JavaObject
         * by invoking methods on such objects.
         */
        friend class JavaClass;

        /**
         * The JavaArray is a friend class, which can create instances of JavaObject by
         * accessing to the elements of an array.
         */
        template<typename T> friend class JavaArray;

        /**
         * The JavaField is a friend class, which allows to access to the fields of
         * an object.
         */
        template<typename T> friend class JavaField;

        /**
         * The JavaMethod is a friend class, which allows to access to the methods of
         * an object.
         */
        template<typename T> friend class JavaMethod;

    };

}

#endif
