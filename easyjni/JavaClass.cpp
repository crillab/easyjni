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

#include "JavaClass.h"
#include "JavaField.h"
#include "JavaMethod.h"
#include "JniException.h"

using namespace easyjni;
using namespace std;

JavaClass::JavaClass( string name, jclass nativeClass) :
        JavaElement( std::move(name)),
        nativeClass(nativeClass) {
    // Nothing to do: everything is already initialized.
}

jclass JavaClass::operator*() {
    return nativeClass;
}

JavaObject JavaClass::asObject() {
    return JavaObject(nativeClass);
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
    return JavaField<jboolean>::newInstance(name, field);
}

JavaField<jbyte> JavaClass::getByteField(const string &name) {
    jfieldID field = getFieldID(name, BYTE);
    return JavaField<jbyte>::newInstance(name, field);
}

JavaField<jchar> JavaClass::getCharField(const string &name) {
    jfieldID field = getFieldID(name, CHARACTER);
    return JavaField<jchar>::newInstance( name, field);
}

JavaField<jshort> JavaClass::getShortField(const string &name) {
    jfieldID field = getFieldID(name, SHORT);
    return JavaField<jshort>::newInstance( name, field);
}

JavaField<jint> JavaClass::getIntField(const string &name) {
    jfieldID field = getFieldID(name, INTEGER);
    return JavaField<jint>::newInstance( name, field);
}

JavaField<jlong> JavaClass::getLongField(const string &name) {
    jfieldID field = getFieldID(name, LONG);
    return JavaField<jlong>::newInstance( name, field);
}

JavaField<jfloat> JavaClass::getFloatField(const string &name) {
    jfieldID field = getFieldID(name, FLOAT);
    return JavaField<jfloat>::newInstance( name, field);
}

JavaField<jdouble> JavaClass::getDoubleField(const string &name) {
    jfieldID field = getFieldID(name, DOUBLE);
    return JavaField<jdouble>::newInstance( name, field);
}

JavaField<JavaObject> JavaClass::getObjectField(const string &name, const string &signature) {
    jfieldID field = getFieldID(name, signature);
    return JavaField<JavaObject>::newInstance( name, field);
}

JavaField<jboolean> JavaClass::getStaticBooleanField(const string &name) {
    jfieldID field = getStaticFieldID(name, BOOLEAN);
    return JavaField<jboolean>::newInstance( name, field);
}

JavaField<jbyte> JavaClass::getStaticByteField(const string &name) {
    jfieldID field = getStaticFieldID(name, BYTE);
    return JavaField<jbyte>::newInstance( name, field);
}

JavaField<jchar> JavaClass::getStaticCharField(const string &name) {
    jfieldID field = getStaticFieldID(name, CHARACTER);
    return JavaField<jchar>::newInstance( name, field);
}

JavaField<jshort> JavaClass::getStaticShortField(const string &name) {
    jfieldID field = getStaticFieldID(name, SHORT);
    return JavaField<jshort>::newInstance( name, field);
}

JavaField<jint> JavaClass::getStaticIntField(const string &name) {
    jfieldID field = getStaticFieldID(name, INTEGER);
    return JavaField<jint>::newInstance( name, field);
}

JavaField<jlong> JavaClass::getStaticLongField(const string &name) {
    jfieldID field = getStaticFieldID(name, LONG);
    return JavaField<jlong>::newInstance( name, field);
}

JavaField<jfloat> JavaClass::getStaticFloatField(const string &name) {
    jfieldID field = getStaticFieldID(name, FLOAT);
    return JavaField<jfloat>::newInstance( name, field);
}

JavaField<jdouble> JavaClass::getStaticDoubleField(const string &name) {
    jfieldID field = getStaticFieldID(name, DOUBLE);
    return JavaField<jdouble>::newInstance( name, field);
}

JavaField<JavaObject> JavaClass::getStaticObjectField(const string &name, const string &signature) {
    jfieldID field = getStaticFieldID(name, signature);
    return JavaField<JavaObject>::newInstance( name, field);
}

JavaMethod<JavaObject> JavaClass::getConstructor(const string &signature) {
    jmethodID constructor = getMethodID("<init>", signature);
    return JavaMethod<JavaObject>(

        "<init>",
        constructor,
        [](JNIEnv *env, jobject obj, jmethodID mtd, va_list args) -> JavaObject {
            throw JniException("Cannot invoke a constructor on an instance");
        },
        [](JNIEnv *env, jclass cls, jmethodID mtd, va_list args) -> JavaObject {
            jobject res = env->NewObjectV(cls, mtd, args);
            return JavaObject(res);
        }
    );
}

JavaObject JavaClass::newInstance() {
    // Invoking the default constructor.
    jmethodID constructor = getMethodID("<init>", CONSTRUCTOR());
    jobject nativeObject = getEnvironment()->NewObject(nativeClass, constructor);

    // Checking if an exception occurred.
    checkException();
    return JavaObject(nativeObject);
}

JavaMethod<void *> JavaClass::getMethod(const string &name, const string &signature) {
    jmethodID method = getMethodID(name, signature);
    return JavaMethod<void *>::newInstance( name, method);
}

JavaMethod<jboolean> JavaClass::getBooleanMethod(const string &name, const string &signature) {
    jmethodID method = getMethodID(name, signature);
    return JavaMethod<jboolean>::newInstance( name, method);
}

JavaMethod<jbyte> JavaClass::getByteMethod(const string &name, const string &signature) {
    jmethodID method = getMethodID(name, signature);
    return JavaMethod<jbyte>::newInstance( name, method);
}

JavaMethod<jchar> JavaClass::getCharMethod(const string &name, const string &signature) {
    jmethodID method = getMethodID(name, signature);
    return JavaMethod<jchar>::newInstance( name, method);
}

JavaMethod<jshort> JavaClass::getShortMethod(const string &name, const string &signature) {
    jmethodID method = getMethodID(name, signature);
    return JavaMethod<jshort>::newInstance( name, method);
}

JavaMethod<jint> JavaClass::getIntMethod(const string &name, const string &signature) {
    jmethodID method = getMethodID(name, signature);
    return JavaMethod<jint>::newInstance( name, method);
}

JavaMethod<jlong> JavaClass::getLongMethod(const string &name, const string &signature) {
    jmethodID method = getMethodID(name, signature);
    return JavaMethod<jlong>::newInstance( name, method);
}

JavaMethod<jfloat> JavaClass::getFloatMethod(const string &name, const string &signature) {
    jmethodID method = getMethodID(name, signature);
    return JavaMethod<jfloat>::newInstance( name, method);
}

JavaMethod<jdouble> JavaClass::getDoubleMethod(const string &name, const string &signature) {
    jmethodID method = getMethodID(name, signature);
    return JavaMethod<jdouble>::newInstance( name, method);
}

JavaMethod<JavaObject> JavaClass::getObjectMethod(const string &name, const string &signature) {
    jmethodID method = getMethodID(name, signature);
    return JavaMethod<JavaObject>::newInstance( name, method);
}

JavaMethod<void *> JavaClass::getStaticMethod(const string &name, const string &signature) {
    jmethodID method = getStaticMethodID(name, signature);
    return JavaMethod<void *>::newInstance( name, method);
}

JavaMethod<jboolean> JavaClass::getStaticBooleanMethod(const string &name, const string &signature) {
    jmethodID method = getStaticMethodID(name, signature);
    return JavaMethod<jboolean>::newInstance( name, method);
}

JavaMethod<jbyte> JavaClass::getStaticByteMethod(const string &name, const string &signature) {
    jmethodID method = getStaticMethodID(name, signature);
    return JavaMethod<jbyte>::newInstance( name, method);
}

JavaMethod<jchar> JavaClass::getStaticCharMethod(const string &name, const string &signature) {
    jmethodID method = getStaticMethodID(name, signature);
    return JavaMethod<jchar>::newInstance( name, method);
}

JavaMethod<jshort> JavaClass::getStaticShortMethod(const string &name, const string &signature) {
    jmethodID method = getStaticMethodID(name, signature);
    return JavaMethod<jshort>::newInstance( name, method);
}

JavaMethod<jint> JavaClass::getStaticIntMethod(const string &name, const string &signature) {
    jmethodID method = getStaticMethodID(name, signature);
    return JavaMethod<jint>::newInstance( name, method);
}

JavaMethod<jlong> JavaClass::getStaticLongMethod(const string &name, const string &signature) {
    jmethodID method = getStaticMethodID(name, signature);
    return JavaMethod<jlong>::newInstance( name, method);
}

JavaMethod<jfloat> JavaClass::getStaticFloatMethod(const string &name, const string &signature) {
    jmethodID method = getStaticMethodID(name, signature);
    return JavaMethod<jfloat>::newInstance( name, method);
}

JavaMethod<jdouble> JavaClass::getStaticDoubleMethod(const string &name, const string &signature) {
    jmethodID method = getStaticMethodID(name, signature);
    return JavaMethod<jdouble>::newInstance( name, method);
}

JavaMethod<JavaObject> JavaClass::getStaticObjectMethod(const string &name, const string &signature) {
    jmethodID method = getStaticMethodID(name, signature);
    return JavaMethod<JavaObject>::newInstance( name, method);
}

jfieldID JavaClass::getFieldID(const string &name, const string &signature) {
    jfieldID field = getEnvironment()->GetFieldID(nativeClass, name.c_str(), signature.c_str());
    if (field == nullptr) {
        checkException();
        throw JniException("Could not find field " + name + " for class " + getName());
    }
    return field;
}

jfieldID JavaClass::getStaticFieldID(const string &name, const string &signature) {
    jfieldID field = getEnvironment()->GetStaticFieldID(nativeClass, name.c_str(), signature.c_str());
    if (field == nullptr) {
        checkException();
        throw JniException("Could not find static field " + name + " for class " + getName());
    }
    return field;
}

jmethodID JavaClass::getMethodID(const string &name, const string &signature) {
    jmethodID method = getEnvironment()->GetMethodID(nativeClass, name.c_str(), signature.c_str());
    if (method == nullptr) {
        checkException();
        throw JniException("Could not find method " + name + " for class " + getName());
    }
    return method;
}

jmethodID JavaClass::getStaticMethodID(const string &name, const string &signature) {
    jmethodID method = getEnvironment()->GetStaticMethodID(nativeClass, name.c_str(), signature.c_str());
    if (method == nullptr) {
        checkException();
        throw JniException("Could not find static method " + name + " for class " + getName());
    }
    return method;
}
