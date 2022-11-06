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

#include "JavaClass.h"
#include "JavaField.h"
#include "JavaMethod.h"
#include "JniException.h"

using namespace easyjni;
using namespace std;

JavaClass::JavaClass(JNIEnv *environment, string name, jclass nativeClass) :
        JavaElement(environment, std::move(name)),
        nativeClass(nativeClass) {
    // Nothing to do: everything is already initialized.
}

JavaObject JavaClass::asObject() {
    return JavaObject(environment, nativeClass);
}

bool JavaClass::isArray() {
    auto metaClass = asObject();
    auto rootClass = metaClass.getClass();
    auto method = rootClass.getBooleanMethod("isArray");
    return method.invoke(metaClass);
}

string JavaClass::getCanonicalName() {
    auto metaClass = asObject();
    auto rootClass = metaClass.getClass();
    auto method = rootClass.getObjectMethod("getCanonicalName", METHOD(CLASS(java/lang/String)));
    auto canonicalName = method.invoke(metaClass);
    return canonicalName.toString();
}

bool JavaClass::isAssignableFrom(JavaClass &cls) {
    auto metaClass = asObject();
    auto rootClass = metaClass.getClass();
    auto method = rootClass.getBooleanMethod("isAssignableFrom", METHOD(CLASS(java/lang/Class)));
    return method.invoke(metaClass, cls.nativeClass);
}

bool JavaClass::isInstance(JavaObject &object) {
    auto metaClass = asObject();
    auto rootClass = metaClass.getClass();
    auto method = rootClass.getBooleanMethod("isInstance", METHOD(CLASS(java/lang/Object)));
    return method.invoke(metaClass, *object);
}

JavaField<jboolean> JavaClass::getBooleanField(const string &name) {
    jfieldID field = getFieldID(name, BOOLEAN);
    return JavaField<jboolean>::newInstance(environment, name, field);
}

JavaField<jbyte> JavaClass::getByteField(const string &name) {
    jfieldID field = getFieldID(name, BYTE);
    return JavaField<jbyte>::newInstance(environment, name, field);
}

JavaField<jchar> JavaClass::getCharField(const string &name) {
    jfieldID field = getFieldID(name, CHARACTER);
    return JavaField<jchar>::newInstance(environment, name, field);
}

JavaField<jshort> JavaClass::getShortField(const string &name) {
    jfieldID field = getFieldID(name, SHORT);
    return JavaField<jshort>::newInstance(environment, name, field);
}

JavaField<jint> JavaClass::getIntField(const string &name) {
    jfieldID field = getFieldID(name, INTEGER);
    return JavaField<jint>::newInstance(environment, name, field);
}

JavaField<jlong> JavaClass::getLongField(const string &name) {
    jfieldID field = getFieldID(name, LONG);
    return JavaField<jlong>::newInstance(environment, name, field);
}

JavaField<jfloat> JavaClass::getFloatField(const string &name) {
    jfieldID field = getFieldID(name, FLOAT);
    return JavaField<jfloat>::newInstance(environment, name, field);
}

JavaField<jdouble> JavaClass::getDoubleField(const string &name) {
    jfieldID field = getFieldID(name, DOUBLE);
    return JavaField<jdouble>::newInstance(environment, name, field);
}

JavaField<JavaObject> JavaClass::getObjectField(const string &name, const string &signature) {
    jfieldID field = getFieldID(name, signature);
    return JavaField<JavaObject>::newInstance(environment, name, field);
}

JavaField<jboolean> JavaClass::getStaticBooleanField(const string &name) {
    jfieldID field = getStaticFieldID(name, BOOLEAN);
    return JavaField<jboolean>::newInstance(environment, name, field);
}

JavaField<jbyte> JavaClass::getStaticByteField(const string &name) {
    jfieldID field = getStaticFieldID(name, BYTE);
    return JavaField<jbyte>::newInstance(environment, name, field);
}

JavaField<jchar> JavaClass::getStaticCharField(const string &name) {
    jfieldID field = getStaticFieldID(name, CHARACTER);
    return JavaField<jchar>::newInstance(environment, name, field);
}

JavaField<jshort> JavaClass::getStaticShortField(const string &name) {
    jfieldID field = getStaticFieldID(name, SHORT);
    return JavaField<jshort>::newInstance(environment, name, field);
}

JavaField<jint> JavaClass::getStaticIntField(const string &name) {
    jfieldID field = getStaticFieldID(name, INTEGER);
    return JavaField<jint>::newInstance(environment, name, field);
}

JavaField<jlong> JavaClass::getStaticLongField(const string &name) {
    jfieldID field = getStaticFieldID(name, LONG);
    return JavaField<jlong>::newInstance(environment, name, field);
}

JavaField<jfloat> JavaClass::getStaticFloatField(const string &name) {
    jfieldID field = getStaticFieldID(name, FLOAT);
    return JavaField<jfloat>::newInstance(environment, name, field);
}

JavaField<jdouble> JavaClass::getStaticDoubleField(const string &name) {
    jfieldID field = getStaticFieldID(name, DOUBLE);
    return JavaField<jdouble>::newInstance(environment, name, field);
}

JavaField<JavaObject> JavaClass::getStaticObjectField(const string &name, const string &signature) {
    jfieldID field = getStaticFieldID(name, signature);
    return JavaField<JavaObject>::newInstance(environment, name, field);
}

JavaMethod<JavaObject> JavaClass::getConstructor(const string &signature) {
    jmethodID constructor = getMethodID("<init>", signature);
    return {
        environment,
        "<init>",
        constructor,
        [](JNIEnv *env, jobject obj, jmethodID mtd, va_list args) -> JavaObject {
            throw JniException("Cannot invoke a constructor on an instance");
        },
        [](JNIEnv *env, jclass cls, jmethodID mtd, va_list args) -> JavaObject {
            jobject res = env->NewObjectV(cls, mtd, args);
            return JavaObject(env, res);
        }
    };
}

JavaObject JavaClass::newInstance() {
    // Invoking the default constructor.
    jmethodID constructor = getMethodID("<init>", CONSTRUCTOR());
    jobject nativeObject = environment->NewObject(nativeClass, constructor);

    // Checking if an exception occurred.
    if (environment->ExceptionCheck()) {
        JavaObject except(environment, environment->ExceptionOccurred());
        environment->ExceptionClear();
        throw JniException(except.toString());
    }

    return JavaObject(environment, nativeObject);
}

JavaMethod<void *> JavaClass::getMethod(const string &name, const string &signature) {
    jmethodID method = getMethodID(name, signature);
    return JavaMethod<void *>::newInstance(environment, name, method);
}

JavaMethod<jboolean> JavaClass::getBooleanMethod(const string &name, const string &signature) {
    jmethodID method = getMethodID(name, signature);
    return JavaMethod<jboolean>::newInstance(environment, name, method);
}

JavaMethod<jbyte> JavaClass::getByteMethod(const string &name, const string &signature) {
    jmethodID method = getMethodID(name, signature);
    return JavaMethod<jbyte>::newInstance(environment, name, method);
}

JavaMethod<jchar> JavaClass::getCharMethod(const string &name, const string &signature) {
    jmethodID method = getMethodID(name, signature);
    return JavaMethod<jchar>::newInstance(environment, name, method);
}

JavaMethod<jshort> JavaClass::getShortMethod(const string &name, const string &signature) {
    jmethodID method = getMethodID(name, signature);
    return JavaMethod<jshort>::newInstance(environment, name, method);
}

JavaMethod<jint> JavaClass::getIntMethod(const string &name, const string &signature) {
    jmethodID method = getMethodID(name, signature);
    return JavaMethod<jint>::newInstance(environment, name, method);
}

JavaMethod<jlong> JavaClass::getLongMethod(const string &name, const string &signature) {
    jmethodID method = getMethodID(name, signature);
    return JavaMethod<jlong>::newInstance(environment, name, method);
}

JavaMethod<jfloat> JavaClass::getFloatMethod(const string &name, const string &signature) {
    jmethodID method = getMethodID(name, signature);
    return JavaMethod<jfloat>::newInstance(environment, name, method);
}

JavaMethod<jdouble> JavaClass::getDoubleMethod(const string &name, const string &signature) {
    jmethodID method = getMethodID(name, signature);
    return JavaMethod<jdouble>::newInstance(environment, name, method);
}

JavaMethod<JavaObject> JavaClass::getObjectMethod(const string &name, const string &signature) {
    jmethodID method = getMethodID(name, signature);
    return JavaMethod<JavaObject>::newInstance(environment, name, method);
}

JavaMethod<void *> JavaClass::getStaticMethod(const string &name, const string &signature) {
    jmethodID method = getStaticMethodID(name, signature);
    return JavaMethod<void *>::newInstance(environment, name, method);
}

JavaMethod<jboolean> JavaClass::getStaticBooleanMethod(const string &name, const string &signature) {
    jmethodID method = getStaticMethodID(name, signature);
    return JavaMethod<jboolean>::newInstance(environment, name, method);
}

JavaMethod<jbyte> JavaClass::getStaticByteMethod(const string &name, const string &signature) {
    jmethodID method = getStaticMethodID(name, signature);
    return JavaMethod<jbyte>::newInstance(environment, name, method);
}

JavaMethod<jchar> JavaClass::getStaticCharMethod(const string &name, const string &signature) {
    jmethodID method = getStaticMethodID(name, signature);
    return JavaMethod<jchar>::newInstance(environment, name, method);
}

JavaMethod<jshort> JavaClass::getStaticShortMethod(const string &name, const string &signature) {
    jmethodID method = getStaticMethodID(name, signature);
    return JavaMethod<jshort>::newInstance(environment, name, method);
}

JavaMethod<jint> JavaClass::getStaticIntMethod(const string &name, const string &signature) {
    jmethodID method = getStaticMethodID(name, signature);
    return JavaMethod<jint>::newInstance(environment, name, method);
}

JavaMethod<jlong> JavaClass::getStaticLongMethod(const string &name, const string &signature) {
    jmethodID method = getStaticMethodID(name, signature);
    return JavaMethod<jlong>::newInstance(environment, name, method);
}

JavaMethod<jfloat> JavaClass::getStaticFloatMethod(const string &name, const string &signature) {
    jmethodID method = getStaticMethodID(name, signature);
    return JavaMethod<jfloat>::newInstance(environment, name, method);
}

JavaMethod<jdouble> JavaClass::getStaticDoubleMethod(const string &name, const string &signature) {
    jmethodID method = getStaticMethodID(name, signature);
    return JavaMethod<jdouble>::newInstance(environment, name, method);
}

JavaMethod<JavaObject> JavaClass::getStaticObjectMethod(const string &name, const string &signature) {
    jmethodID method = getStaticMethodID(name, signature);
    return JavaMethod<JavaObject>::newInstance(environment, name, method);
}

jfieldID JavaClass::getFieldID(const string &name, const string &signature) {
    jfieldID field = environment->GetFieldID(nativeClass, name.c_str(), signature.c_str());
    if (field == nullptr) {
        if (environment->ExceptionCheck()) {
            JavaObject except(environment, environment->ExceptionOccurred());
            environment->ExceptionClear();
            throw JniException(except.toString());
        }
        throw JniException("Could not find field " + name + " for class " + getName());
    }
    return field;
}

jfieldID JavaClass::getStaticFieldID(const string &name, const string &signature) {
    jfieldID field = environment->GetStaticFieldID(nativeClass, name.c_str(), signature.c_str());
    if (field == nullptr) {
        if (environment->ExceptionCheck()) {
            JavaObject except(environment, environment->ExceptionOccurred());
            environment->ExceptionClear();
            throw JniException(except.toString());
        }
        throw JniException("Could not find static field " + name + " for class " + getName());
    }
    return field;
}

jmethodID JavaClass::getMethodID(const string &name, const string &signature) {
    jmethodID method = environment->GetMethodID(nativeClass, name.c_str(), signature.c_str());
    if (method == nullptr) {
        if (environment->ExceptionCheck()) {
            JavaObject except(environment, environment->ExceptionOccurred());
            environment->ExceptionClear();
            throw JniException(except.toString());
        }
        throw JniException("Could not find method " + name + " for class " + getName());
    }
    return method;
}

jmethodID JavaClass::getStaticMethodID(const string &name, const string &signature) {
    jmethodID method = environment->GetStaticMethodID(nativeClass, name.c_str(), signature.c_str());
    if (method == nullptr) {
        if (environment->ExceptionCheck()) {
            JavaObject except(environment, environment->ExceptionOccurred());
            environment->ExceptionClear();
            throw JniException(except.toString());
        }
        throw JniException("Could not find static method " + name + " for class " + getName());
    }
    return method;
}
