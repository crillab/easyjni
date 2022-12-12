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

#ifndef EASYJNI_JAVACLASS_H
#define EASYJNI_JAVACLASS_H

#include <jni.h>

#include "JavaElement.h"
#include "JavaObject.h"
#include "JavaSignature.h"

namespace easyjni {

    /**
     * Forward declaration of JavaField, which represents a field that is defined
     * in a Java class.
     *
     * @tparam T The declared type of the field.
     */
    template<typename T> class JavaField;

    /**
     * Forward declaration of JavaMethod, which represents a method that is defined
     * in a Java class.
     *
     * @tparam T The return type of the method.
     */
    template<typename T> class JavaMethod;

    /**
     * The JavaClass represents a class that is defined in the Java code.
     *
     * @author Romain Wallon
     *
     * @version 0.1.0
     */
    class JavaClass : public easyjni::JavaElement {

    private:

        /**
         * The native pointer to the class in the Java Virtual Machine.
         */
        jclass nativeClass;

    private:

        /**
         * Creates a new JavaClass.
         *
         * @param environment The Java environment in which the class has been declared.
         * @param name The name of the class.
         * @param nativeClass The native pointer to the class in the Java Virtual Machine.
         */
        JavaClass(std::string name, jclass nativeClass);

    public:

        /**
         * Gives this class viewed as a Java object (i.e., the so-called "metaclass").
         *
         * @return The object view of this class.
         */
        easyjni::JavaObject asObject();

        /**
         * Checks whether this class represents an array type.
         *
         * @return Whether this class represents an array type.
         */
        bool isArray();

        /**
         * Gives the canonical name of the underlying class, as defined by the
         * Java Language Specification.
         *
         * @return The canonical name of this class, or an empty string if it does
         *         not have a canonical name.
         */
        std::string getCanonicalName();

        /**
         * Checks whether a JavaClass is a subclass of this class.
         *
         * @param clazz The class to check.
         *
         * @return Whether a JavaClass is a subclass of this class.
         */
        bool isAssignableFrom(easyjni::JavaClass &clazz);

        /**
         * Checks whether a JavaObject is an instance of this class.
         *
         * @param object The object to check.
         *
         * @return Whether a JavaObject is an instance of this class.
         */
        bool isInstance(easyjni::JavaObject &object);

        /**
         * Gives the field with the given name that is declared in this class.
         *
         * @param name The name of the field to get.
         *
         * @return The field with the given name.
         *
         * @throws JniException If an error occurred while getting the field.
         */
        easyjni::JavaField<jboolean> getBooleanField(const std::string &name);

        /**
         * Gives the field with the given name that is declared in this class.
         *
         * @param name The name of the field to get.
         *
         * @return The field with the given name.
         *
         * @throws JniException If an error occurred while getting the field.
         */
        easyjni::JavaField<jbyte> getByteField(const std::string &name);

        /**
         * Gives the field with the given name that is declared in this class.
         *
         * @param name The name of the field to get.
         *
         * @return The field with the given name.
         *
         * @throws JniException If an error occurred while getting the field.
         */
        easyjni::JavaField<jchar> getCharField(const std::string &name);

        /**
         * Gives the field with the given name that is declared in this class.
         *
         * @param name The name of the field to get.
         *
         * @return The field with the given name.
         *
         * @throws JniException If an error occurred while getting the field.
         */
        easyjni::JavaField<jshort> getShortField(const std::string &name);

        /**
         * Gives the field with the given name that is declared in this class.
         *
         * @param name The name of the field to get.
         *
         * @return The field with the given name.
         *
         * @throws JniException If an error occurred while getting the field.
         */
        easyjni::JavaField<jint> getIntField(const std::string &name);

        /**
         * Gives the field with the given name that is declared in this class.
         *
         * @param name The name of the field to get.
         *
         * @return The field with the given name.
         *
         * @throws JniException If an error occurred while getting the field.
         */
        easyjni::JavaField<jlong> getLongField(const std::string &name);

        /**
         * Gives the field with the given name that is declared in this class.
         *
         * @param name The name of the field to get.
         *
         * @return The field with the given name.
         *
         * @throws JniException If an error occurred while getting the field.
         */
        easyjni::JavaField<jfloat> getFloatField(const std::string &name);

        /**
         * Gives the field with the given name that is declared in this class.
         *
         * @param name The name of the field to get.
         *
         * @return The field with the given name.
         *
         * @throws JniException If an error occurred while getting the field.
         */
        easyjni::JavaField<jdouble> getDoubleField(const std::string &name);

        /**
         * Gives the field with the given name that is declared in this class.
         *
         * @param name The name of the field to get.
         * @param signature The name of the declared type of the field.
         *
         * @return The field with the given name.
         *
         * @throws JniException If an error occurred while getting the field.
         */
        easyjni::JavaField<easyjni::JavaObject> getObjectField(const std::string &name, const std::string &signature);

        /**
         * Gives the static field with the given name that is declared in this class.
         *
         * @param name The name of the field to get.
         *
         * @return The field with the given name.
         *
         * @throws JniException If an error occurred while getting the field.
         */
        easyjni::JavaField<jboolean> getStaticBooleanField(const std::string &name);

        /**
         * Gives the static field with the given name that is declared in this class.
         *
         * @param name The name of the field to get.
         *
         * @return The field with the given name.
         *
         * @throws JniException If an error occurred while getting the field.
         */
        easyjni::JavaField<jbyte> getStaticByteField(const std::string &name);

        /**
         * Gives the static field with the given name that is declared in this class.
         *
         * @param name The name of the field to get.
         *
         * @return The field with the given name.
         *
         * @throws JniException If an error occurred while getting the field.
         */
        easyjni::JavaField<jchar> getStaticCharField(const std::string &name);

        /**
         * Gives the static field with the given name that is declared in this class.
         *
         * @param name The name of the field to get.
         *
         * @return The field with the given name.
         *
         * @throws JniException If an error occurred while getting the field.
         */
        easyjni::JavaField<jshort> getStaticShortField(const std::string &name);

        /**
         * Gives the static field with the given name that is declared in this class.
         *
         * @param name The name of the field to get.
         *
         * @return The field with the given name.
         *
         * @throws JniException If an error occurred while getting the field.
         */
        easyjni::JavaField<jint> getStaticIntField(const std::string &name);

        /**
         * Gives the static field with the given name that is declared in this class.
         *
         * @param name The name of the field to get.
         *
         * @return The field with the given name.
         *
         * @throws JniException If an error occurred while getting the field.
         */
        easyjni::JavaField<jlong> getStaticLongField(const std::string &name);

        /**
         * Gives the static field with the given name that is declared in this class.
         *
         * @param name The name of the field to get.
         *
         * @return The field with the given name.
         *
         * @throws JniException If an error occurred while getting the field.
         */
        easyjni::JavaField<jfloat> getStaticFloatField(const std::string &name);

        /**
         * Gives the static field with the given name that is declared in this class.
         *
         * @param name The name of the field to get.
         *
         * @return The field with the given name.
         *
         * @throws JniException If an error occurred while getting the field.
         */
        easyjni::JavaField<jdouble> getStaticDoubleField(const std::string &name);

        /**
         * Gives the static field with the given name that is declared in this class.
         *
         * @param name The name of the field to get.
         * @param signature The name of the declared type of the field.
         *
         * @return The field with the given name.
         *
         * @throws JniException If an error occurred while getting the field.
         */
        easyjni::JavaField<easyjni::JavaObject> getStaticObjectField(
                const std::string &name, const std::string &signature);

        /**
         * Gives the constructor defined in this class with the given signature.
         *
         * @param signature The signature of the constructor to get.
         *
         * @return The constructor for this class with the given signature.
         *
         * @throws JniException If an error occurred while getting the constructor.
         */
        easyjni::JavaMethod<easyjni::JavaObject> getConstructor(const std::string &signature = CONSTRUCTOR());

        /**
         * Creates a new instance of this class in the Java Virtual Machine.
         * This method assumes there exists an empty constructor for this class.
         *
         * @return The object created by the instantiation.
         *
         * @throws JniException If an error occurred while instantiating the object.
         */
        JavaObject newInstance();

        /**
         * Gives the method defined in this class with the given name and signature.
         *
         * @param name The name of the method to get.
         * @param signature The signature of the method to get.
         *
         * @return The method of this class with the given name and signature.
         *
         * @throws JniException If an error occurred while getting the method.
         */
        easyjni::JavaMethod<void *> getMethod(
                const std::string &name, const std::string &signature = METHOD(VOID));

        /**
         * Gives the method defined in this class with the given name and signature.
         *
         * @param name The name of the method to get.
         * @param signature The signature of the method to get.
         *
         * @return The method of this class with the given name and signature.
         *
         * @throws JniException If an error occurred while getting the method.
         */
        easyjni::JavaMethod<jboolean> getBooleanMethod(
                const std::string &name, const std::string &signature = METHOD(BOOLEAN));

        /**
         * Gives the method defined in this class with the given name and signature.
         *
         * @param name The name of the method to get.
         * @param signature The signature of the method to get.
         *
         * @return The method of this class with the given name and signature.
         *
         * @throws JniException If an error occurred while getting the method.
         */
        easyjni::JavaMethod<jbyte> getByteMethod(
                const std::string &name, const std::string &signature = METHOD(BYTE));

        /**
         * Gives the method defined in this class with the given name and signature.
         *
         * @param name The name of the method to get.
         * @param signature The signature of the method to get.
         *
         * @return The method of this class with the given name and signature.
         *
         * @throws JniException If an error occurred while getting the method.
         */
        easyjni::JavaMethod<jchar> getCharMethod(
                const std::string &name, const std::string &signature = METHOD(CHARACTER));

        /**
         * Gives the method defined in this class with the given name and signature.
         *
         * @param name The name of the method to get.
         * @param signature The signature of the method to get.
         *
         * @return The method of this class with the given name and signature.
         *
         * @throws JniException If an error occurred while getting the method.
         */
        easyjni::JavaMethod<jshort> getShortMethod(
                const std::string &name, const std::string &signature = METHOD(SHORT));

        /**
         * Gives the method defined in this class with the given name and signature.
         *
         * @param name The name of the method to get.
         * @param signature The signature of the method to get.
         *
         * @return The method of this class with the given name and signature.
         *
         * @throws JniException If an error occurred while getting the method.
         */
        easyjni::JavaMethod<jint> getIntMethod(
                const std::string &name, const std::string &signature = METHOD(INTEGER));

        /**
         * Gives the method defined in this class with the given name and signature.
         *
         * @param name The name of the method to get.
         * @param signature The signature of the method to get.
         *
         * @return The method of this class with the given name and signature.
         *
         * @throws JniException If an error occurred while getting the method.
         */
        easyjni::JavaMethod<jlong> getLongMethod(
                const std::string &name, const std::string &signature = METHOD(LONG));

        /**
         * Gives the method defined in this class with the given name and signature.
         *
         * @param name The name of the method to get.
         * @param signature The signature of the method to get.
         *
         * @return The method of this class with the given name and signature.
         *
         * @throws JniException If an error occurred while getting the method.
         */
        easyjni::JavaMethod<jfloat> getFloatMethod(
                const std::string &name, const std::string &signature = METHOD(FLOAT));

        /**
         * Gives the method defined in this class with the given name and signature.
         *
         * @param name The name of the method to get.
         * @param signature The signature of the method to get.
         *
         * @return The method of this class with the given name and signature.
         *
         * @throws JniException If an error occurred while getting the method.
         */
        easyjni::JavaMethod<jdouble> getDoubleMethod(
                const std::string &name, const std::string &signature = METHOD(DOUBLE));

        /**
         * Gives the method defined in this class with the given name and signature.
         *
         * @param name The name of the method to get.
         * @param signature The signature of the method to get.
         *
         * @return The method of this class with the given name and signature.
         *
         * @throws JniException If an error occurred while getting the method.
         */
        easyjni::JavaMethod<easyjni::JavaObject> getObjectMethod(
                const std::string &name, const std::string &signature = METHOD(CLASS(java/lang/Object)));

        /**
         * Gives the static method defined in this class with the given name and signature.
         *
         * @param name The name of the method to get.
         * @param signature The signature of the method to get.
         *
         * @return The method of this class with the given name and signature.
         *
         * @throws JniException If an error occurred while getting the method.
         */
        easyjni::JavaMethod<void *> getStaticMethod(
                const std::string &name, const std::string &signature = METHOD(VOID));

        /**
         * Gives the static method defined in this class with the given name and signature.
         *
         * @param name The name of the method to get.
         * @param signature The signature of the method to get.
         *
         * @return The method of this class with the given name and signature.
         *
         * @throws JniException If an error occurred while getting the method.
         */
        easyjni::JavaMethod<jboolean> getStaticBooleanMethod(
                const std::string &name, const std::string &signature = METHOD(BOOLEAN));

        /**
         * Gives the static method defined in this class with the given name and signature.
         *
         * @param name The name of the method to get.
         * @param signature The signature of the method to get.
         *
         * @return The method of this class with the given name and signature.
         *
         * @throws JniException If an error occurred while getting the method.
         */
        easyjni::JavaMethod<jbyte> getStaticByteMethod(
                const std::string &name, const std::string &signature = METHOD(BYTE));

        /**
         * Gives the static method defined in this class with the given name and signature.
         *
         * @param name The name of the method to get.
         * @param signature The signature of the method to get.
         *
         * @return The method of this class with the given name and signature.
         *
         * @throws JniException If an error occurred while getting the method.
         */
        easyjni::JavaMethod<jchar> getStaticCharMethod(
                const std::string &name, const std::string &signature = METHOD(CHARACTER));

        /**
         * Gives the static method defined in this class with the given name and signature.
         *
         * @param name The name of the method to get.
         * @param signature The signature of the method to get.
         *
         * @return The method of this class with the given name and signature.
         *
         * @throws JniException If an error occurred while getting the method.
         */
        easyjni::JavaMethod<jshort> getStaticShortMethod(
                const std::string &name, const std::string &signature = METHOD(SHORT));

        /**
         * Gives the static method defined in this class with the given name and signature.
         *
         * @param name The name of the method to get.
         * @param signature The signature of the method to get.
         *
         * @return The method of this class with the given name and signature.
         *
         * @throws JniException If an error occurred while getting the method.
         */
        easyjni::JavaMethod<jint> getStaticIntMethod(
                const std::string &name, const std::string &signature = METHOD(INTEGER));

        /**
         * Gives the static method defined in this class with the given name and signature.
         *
         * @param name The name of the method to get.
         * @param signature The signature of the method to get.
         *
         * @return The method of this class with the given name and signature.
         *
         * @throws JniException If an error occurred while getting the method.
         */
        easyjni::JavaMethod<jlong> getStaticLongMethod(
                const std::string &name, const std::string &signature = METHOD(LONG));

        /**
         * Gives the static method defined in this class with the given name and signature.
         *
         * @param name The name of the method to get.
         * @param signature The signature of the method to get.
         *
         * @return The method of this class with the given name and signature.
         *
         * @throws JniException If an error occurred while getting the method.
         */
        easyjni::JavaMethod<jfloat> getStaticFloatMethod(
                const std::string &name, const std::string &signature = METHOD(FLOAT));

        /**
         * Gives the static method defined in this class with the given name and signature.
         *
         * @param name The name of the method to get.
         * @param signature The signature of the method to get.
         *
         * @return The method of this class with the given name and signature.
         *
         * @throws JniException If an error occurred while getting the method.
         */
        easyjni::JavaMethod<jdouble> getStaticDoubleMethod(
                const std::string &name, const std::string &signature = METHOD(DOUBLE));

        /**
         * Gives the static method defined in this class with the given name and signature.
         *
         * @param name The name of the method to get.
         * @param signature The signature of the method to get.
         *
         * @return The method of this class with the given name and signature.
         *
         * @throws JniException If an error occurred while getting the method.
         */
        easyjni::JavaMethod<easyjni::JavaObject> getStaticObjectMethod(
                const std::string &name, const std::string &signature = METHOD(CLASS(java/lang/Object)));

    private:

        /**
         * Gives the native field with the given name and signature that is declared
         * in this class.
         *
         * @param name The name of the field to get.
         * @param signature The signature of the field to get.
         *
         * @return The field with the given name and signature.
         *
         * @throws JniException If an error occurred while getting the field.
         */
        jfieldID getFieldID(const std::string &name, const std::string &signature);

        /**
         * Gives the native static field with the given name and signature that is
         * declared in this class.
         *
         * @param name The name of the field to get.
         * @param signature The signature of the field to get.
         *
         * @return The field with the given name and signature.
         *
         * @throws JniException If an error occurred while getting the field.
         */
        jfieldID getStaticFieldID(const std::string &name, const std::string &signature);

        /**
         * Gives the native method with the given name and signature that is declared
         * in this class.
         *
         * @param name The name of the method to get.
         * @param signature The signature of the method to get.
         *
         * @return The method with the given name and signature.
         *
         * @throws JniException If an error occurred while getting the method.
         */
        jmethodID getMethodID(const std::string &name, const std::string &signature);

        /**
         * Gives the native static method with the given name and signature that is
         * declared in this class.
         *
         * @param name The name of the method to get.
         * @param signature The signature of the method to get.
         *
         * @return The method with the given name and signature.
         *
         * @throws JniException If an error occurred while getting the method.
         */
        jmethodID getStaticMethodID(const std::string &name, const std::string &signature);

        /**
         * The JavaVirtualMachine is a friend class, which allows to load
         * Java classes to create instances of JavaClass.
         */
        friend class JavaVirtualMachine;

        /**
         * The JavaObject is a friend class, which interacts with JavaClass to
         * retrieve the fields and methods of a Java object.
         */
        friend class JavaObject;

        /**
         * The JavaField is a friend class, which interacts with JavaClass to
         * represent the fields of such a class.
         */
        template<typename T> friend class JavaField;

        /**
         * The JavaMethod is a friend class, which interacts with JavaClass to
         * represent the methods of such a class.
         */
        template<typename T> friend class JavaMethod;

    };

}

#endif
