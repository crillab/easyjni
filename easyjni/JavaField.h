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

#ifndef EASYJNI_JAVAFIELD_H
#define EASYJNI_JAVAFIELD_H

#include <functional>
#include <string>

#include <jni.h>

#include "JavaClass.h"
#include "JavaElement.h"
#include "JavaObject.h"
#include "JniException.h"

namespace easyjni {

    /**
     * The JavaField represents a field that is defined in a Java class.
     * It also allows to access to this field from the C++ code, which may break
     * encapsulation on the Java side.
     *
     * @tparam T The declared type of the field.
     *
     * @author Romain Wallon
     *
     * @version 0.1.0
     */
    template<typename T>
    class JavaField : public easyjni::JavaElement {

    private:

        /**
         * The native pointer to the field in the Java Virtual Machine.
         */
        jfieldID nativeField;

        /**
         * The function to use to get the value of this field for a particular object.
         */
        std::function<T(JNIEnv *, jobject, jfieldID)> getter;

        /**
         * The function to use to set the value of this field for a particular object.
         */
        std::function<void(JNIEnv *, jobject, jfieldID, T)> setter;

        /**
         * The function to use to get the static value of this field in the class.
         */
        std::function<T(JNIEnv *, jclass, jfieldID)> staticGetter;

        /**
         * The function to use to set the static value of this field in the class.
         */
        std::function<void(JNIEnv *, jclass, jfieldID, T)> staticSetter;

    private:

        /**
         * Creates a new JavaField.
         *
         * @param environment The Java environment in which the field has been declared.
         * @param name The name of the field.
         * @param nativeField The native pointer to the field in the Java Virtual Machine.
         * @param getter The function to use to get the value of the field for a particular object.
         * @param setter The function to use to set the value of the field for a particular object.
         * @param staticGetter The function to use to get the static value of the field in the class.
         * @param staticSetter The function to use to set the static value of the field in the class.
         */
        JavaField( std::string name, jfieldID nativeField,
                  std::function<T(JNIEnv *, jobject, jfieldID)> getter,
                  std::function<void(JNIEnv *, jobject, jfieldID, T)> setter,
                  std::function<T(JNIEnv *, jclass, jfieldID)> staticGetter,
                  std::function<void(JNIEnv *, jclass, jfieldID, T)> staticSetter) :
                JavaElement(std::move(name)),
                nativeField(nativeField),
                getter(getter),
                setter(setter),
                staticGetter(staticGetter),
                staticSetter(staticSetter) {
            // Nothing to do: everything is already initialized.
        }

        /**
         * Creates a new JavaField.
         *
         * @param environment The Java environment in which the field has been declared.
         * @param name The name of the field.
         * @param nativeField The native pointer to the field in the Java Virtual Machine.
         *
         * @return The created JavaField.
         */
        static JavaField<T> newInstance(std::string name, jfieldID nativeField);

    public:

        /**
         * Gets the value of this field for the given object.
         *
         * @param object The object of which to get the value of this field.
         *
         * @return The value of this field for the given object.
         *
         * @throws JniException If an error occurred while getting the field.
         */
        T get(easyjni::JavaObject &object) {
            return getter(getEnvironment(), object.nativeObject, nativeField);
        }

        /**
         * Sets the value of this field for the given object.
         *
         * @param object The object of which to set the value of this field.
         * @param value The new value for this field.
         *
         * @throws JniException If an error occurred while setting the field.
         */
        void set(easyjni::JavaObject &object, T value) {
            setter(getEnvironment(), object.nativeObject, nativeField, value);
        }

        /**
         * Gets the value of this static field for the given class.
         *
         * @param clazz The class of which to get the value of this field.
         *
         * @return The value of this field for the given class.
         *
         * @throws JniException If an error occurred while getting the field.
         */
        T getStatic(easyjni::JavaClass &clazz) {
            return staticGetter(getEnvironment(), clazz.nativeClass, nativeField);
        }

        /**
         * Sets the value of this static field for the given class.
         *
         * @param clazz The class of which to set the value of this field.
         * @param value The new value for this field.
         *
         * @throws JniException If an error occurred while setting the field.
         */
        void setStatic(easyjni::JavaClass &clazz, T value) {
            staticSetter(getEnvironment(), clazz.nativeClass, value);
        }

        /**
         * The JavaClass is a friend class, which uses JavaField to represent
         * the fields it declares.
         */
        friend class JavaClass;

    };

}

#endif
