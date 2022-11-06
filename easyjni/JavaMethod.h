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

#ifndef EASYJNI_JAVAMETHOD_H
#define EASYJNI_JAVAMETHOD_H

#include <cstdarg>
#include <functional>
#include <string>

#include <jni.h>

#include "JavaClass.h"
#include "JavaElement.h"
#include "JavaObject.h"
#include "JniException.h"

namespace easyjni {

    /**
     * The JavaMethod represents a method that is defined in a Java class.
     * It allows to invoke this method from C++ code.
     *
     * @tparam T The return type of the method.
     *
     * @author Romain Wallon
     *
     * @version 0.1.0
     */
    template<typename T>
    class JavaMethod : public easyjni::JavaElement {

    private:

        /**
         * The native pointer to the method in the Java Virtual Machine.
         */
        jmethodID nativeMethod;

        /**
         * The function to use to invoke this method on a particular object.
         */
        std::function<T(JNIEnv *, jobject, jmethodID, va_list)> call;

        /**
         * The function to use to statically invoke this method on the class.
         */
        std::function<T(JNIEnv *, jclass, jmethodID, va_list)> staticCall;

    private:

        /**
         * Creates a new JavaMethod.
         *
         * @param environment The Java environment in which the method has been declared.
         * @param name The name of the method.
         * @param nativeMethod The native pointer to the method in the Java Virtual Machine.
         * @param call The function to use to invoke the method on a particular object.
         * @param staticCall The function to use to statically invoke the method on the class.
         */
        JavaMethod(JNIEnv *environment, std::string name, jmethodID nativeMethod,
                   std::function<T(JNIEnv *, jobject, jmethodID, va_list)> call,
                   std::function<T(JNIEnv *, jclass, jmethodID, va_list)> staticCall) :
                JavaElement(environment, std::move(name)),
                nativeMethod(nativeMethod),
                call(call),
                staticCall(staticCall) {
            // Nothing to do: everything is already initialized.
        }

        /**
         * Creates a new JavaMethod.
         *
         * @param environment The Java environment in which the method has been declared.
         * @param name The name of the method.
         * @param nativeMethod The native pointer to the method in the Java Virtual Machine.
         *
         * @return The created JavaMethod.
         */
        static JavaMethod<T> newInstance(JNIEnv *environment, std::string name, jmethodID nativeMethod);

    public:

        /**
         * Invokes this method on the given object.
         *
         * @param object The object on which to invoke this method.
         * @param ... The parameters to give to this method.
         *
         * @return The value returned by the method.
         *
         * @throws JniException If an error occurred while invoking the method.
         */
        T invoke(easyjni::JavaObject object, ...) {
            // Invoking the method.
            va_list args;
            va_start(args, object);
            T result = call(environment, object.nativeObject, nativeMethod, args);
            va_end(args);

            // Checking if an exception occurred.
            if (environment->ExceptionCheck()) {
                JavaObject except(environment, environment->ExceptionOccurred());
                environment->ExceptionClear();
                throw JniException(except.toString());
            }

            return result;
        }

        /**
         * Statically invokes this method on the given class.
         *
         * @param clazz The class on which to invoke this method.
         * @param ... The parameters to give to this method.
         *
         * @return The value returned by the method.
         *
         * @throws JniException If an error occurred while invoking the method.
         */
        T invokeStatic(easyjni::JavaClass clazz, ...) {
            // Invoking the method.
            va_list args;
            va_start(args, clazz);
            T result = staticCall(environment, clazz.nativeClass, nativeMethod, args);
            va_end(args);

            // Checking if an exception occurred.
            if (environment->ExceptionCheck()) {
                JavaObject except(environment, environment->ExceptionOccurred());
                environment->ExceptionClear();
                throw JniException(except.toString());
            }
            return result;
        }

        /**
         * The JavaClass is a friend class, which uses JavaMethod to represent
         * the methods it declares.
         */
        friend class JavaClass;

    };

}

#endif
