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

#ifndef EASYJNI_JAVAARRAY_H
#define EASYJNI_JAVAARRAY_H

#include <jni.h>

#include "JavaVirtualMachineRegistry.h"

namespace easyjni {

    /**
     * Forward declaration of JavaVirtualMachine, the class that encapsulates the
     * instance of the Java Virtual Machine to use to run Java code.
     */
    class JavaVirtualMachine;

    /**
     * Forward declaration of JavaObject, the class that represents an object
     * from the Java Virtual Machine.
     */
    class JavaObject;

    /**
     * The JavaArray represents an array in the Java Virtual Machine.
     *
     * @tparam T The type of the elements in the array.
     *
     * @author Romain Wallon
     *
     * @version 0.1.0
     */
    template<typename T>
    class JavaArray {

    private:

        /**
         * The native pointer to the array in the Java Virtual Machine.
         */
        jarray array;

    private:

        /**
         * Creates a new JavaArray.
         *
         * @param array The native pointer to the array in the Java Virtual Machine.
         */
        explicit JavaArray(jarray array) :
                array(array) {
            // Nothing to do: everything is already initialized.
        }

        /**
         * Creates a new JavaArray.
         *
         * @param object The native pointer to the array in the Java Virtual Machine, as an object.
         *
         * @return The created JavaArray.
         */
        static JavaArray<T> asArray(jobject object) {
            return JavaArray((jarray) object);
        }

    public:

        /**
         * Gives the element at the specified index in this array.
         *
         * @param index The index of the element to get.
         *
         * @return The element at the specified index.
         */
        T get(int index);

        /**
         * Sets the element at the specified index in this array.
         *
         * @param index The index of the element to set.
         * @param elt The element to set at the specified index.
         */
        void set(int index, T elt);

        /**
         * Gives the length of this array.
         *
         * @return The length of this array.
         */
        int length() {
            return JavaVirtualMachineRegistry::getEnvironment()->GetArrayLength(array);
        }

        /**
         * Gives the native pointer to the array in the Java Virtual Machine.
         *
         * @return The native pointer to the array in the Java Virtual Machine.
         */
        jarray operator*() {
            return array;
        }

        /**
         * The JavaVirtualMachine is a friend class, which allows to build instances
         * of JavaArray by creating arrays in the JVM.
         */
        friend class JavaVirtualMachine;

        /**
         * The JavaObject is a friend class, which may also represent instances
         * of JavaArray, that are not known yet to be arrays.
         */
        friend class JavaObject;

    };

}

#endif
