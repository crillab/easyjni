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

#include "JavaMethod.h"
#include "JavaVirtualMachine.h"
#include "JniException.h"
#include "JavaClass.h"
#include "JavaObject.h"
#include "JavaArray.h"

using namespace easyjni;
using namespace std;

JavaVirtualMachine::JavaVirtualMachine(JavaVM *jvm, JNIEnv *env, bool main) :
        jvm(jvm),
        env(env),
        main(main) {
    // Nothing to do: everything is already initialized.
}

JavaVirtualMachine::~JavaVirtualMachine() {
    if (main) {
        jvm->DestroyJavaVM();
    }
}

pair<int, int> JavaVirtualMachine::getVersion() {
    int version = env->GetVersion();
    int major = (version >> 16) & 0x0f;
    int minor = version & 0x0f;
    return pair(major, minor);
}

JavaClass JavaVirtualMachine::loadClass(const string &name) {
    jclass nativeClass = env->FindClass(name.c_str());
    if (nativeClass == nullptr) {
        if (env->ExceptionCheck()) {
            JavaObject except(env->ExceptionOccurred());
            env->ExceptionClear();
            throw JniException(except.toString());
        }
        throw JniException("Could not load class " + name);
    }
    return JavaClass(name, nativeClass);
}

JavaObject JavaVirtualMachine::toJavaString(const string &str) {
    return toJavaString(str.c_str());
}

JavaObject JavaVirtualMachine::toJavaString(const char *str) {
    return JavaObject(env->NewStringUTF(str));
}

JavaObject JavaVirtualMachine::wrap(jboolean b) {
    auto cls = loadClass("java/lang/Boolean");
    auto mtd = cls.getStaticObjectMethod("valueOf", METHOD(CLASS(java/lang/Boolean), BOOLEAN));
    return mtd.invokeStatic(cls, b);
}

JavaObject JavaVirtualMachine::wrap(jbyte b) {
    auto cls = loadClass("java/lang/Byte");
    auto mtd = cls.getStaticObjectMethod("valueOf", METHOD(CLASS(java/lang/Byte), BYTE));
    return mtd.invokeStatic(cls, b);
}

JavaObject JavaVirtualMachine::wrap(jchar c) {
    auto cls = loadClass("java/lang/Character");
    auto mtd = cls.getStaticObjectMethod("valueOf", METHOD(CLASS(java/lang/Character), CHARACTER));
    return mtd.invokeStatic(cls, c);
}

JavaObject JavaVirtualMachine::wrap(jshort s) {
    auto cls = loadClass("java/lang/Short");
    auto mtd = cls.getStaticObjectMethod("valueOf", METHOD(CLASS(java/lang/Short), SHORT));
    return mtd.invokeStatic(cls, s);
}

JavaObject JavaVirtualMachine::wrap(jint i) {
    auto cls = loadClass("java/lang/Integer");
    auto mtd = cls.getStaticObjectMethod("valueOf", METHOD(CLASS(java/lang/Integer), INTEGER));
    return mtd.invokeStatic(cls, i);
}

JavaObject JavaVirtualMachine::wrap(jlong l) {
    auto cls = loadClass("java/lang/Long");
    auto mtd = cls.getStaticObjectMethod("valueOf", METHOD(CLASS(java/lang/Long), LONG));
    return mtd.invokeStatic(cls, l);
}

JavaObject JavaVirtualMachine::wrap(jfloat f) {
    auto cls = loadClass("java/lang/Float");
    auto mtd = cls.getStaticObjectMethod("valueOf", METHOD(CLASS(java/lang/Float), FLOAT));
    return mtd.invokeStatic(cls, f);
}

JavaObject JavaVirtualMachine::wrap(jdouble d) {
    auto cls = loadClass("java/lang/Double");
    auto mtd = cls.getStaticObjectMethod("valueOf", METHOD(CLASS(java/lang/Double), DOUBLE));
    return mtd.invokeStatic(cls, d);
}

jboolean JavaVirtualMachine::unwrapAsBoolean(const JavaObject &b) {
    auto cls = loadClass("java/lang/Boolean");
    auto mtd = cls.getBooleanMethod("booleanValue");
    return mtd.invoke(b);
}

jbyte JavaVirtualMachine::unwrapAsByte(const JavaObject &b) {
    auto cls = loadClass("java/lang/Number");
    auto mtd = cls.getByteMethod("byteValue");
    return mtd.invoke(b);
}

jchar JavaVirtualMachine::unwrapAsChar(const JavaObject &c) {
    auto cls = loadClass("java/lang/Character");
    auto mtd = cls.getCharMethod("charValue");
    return mtd.invoke(c);
}

jshort JavaVirtualMachine::unwrapAsShort(const JavaObject &s) {
    auto cls = loadClass("java/lang/Number");
    auto mtd = cls.getShortMethod("shortValue");
    return mtd.invoke(s);
}

jint JavaVirtualMachine::unwrapAsInt(const JavaObject &i) {
    auto cls = loadClass("java/lang/Number");
    auto mtd = cls.getIntMethod("intValue");
    return mtd.invoke(i);
}

jlong JavaVirtualMachine::unwrapAsLong(const JavaObject &l) {
    auto cls = loadClass("java/lang/Number");
    auto mtd = cls.getLongMethod("longValue");
    return mtd.invoke(l);
}

jfloat JavaVirtualMachine::unwrapAsFloat(const JavaObject &f) {
    auto cls = loadClass("java/lang/Number");
    auto mtd = cls.getFloatMethod("floatValue");
    return mtd.invoke(f);
}

jdouble JavaVirtualMachine::unwrapAsDouble(const JavaObject &d) {
    auto cls = loadClass("java/lang/Number");
    auto mtd = cls.getDoubleMethod("doubleValue");
    return mtd.invoke(d);
}

JavaArray<jboolean> JavaVirtualMachine::createBooleanArray(int size) {
    auto array = env->NewBooleanArray(size);
    return JavaArray<jboolean>(array);
}

JavaArray<jbyte> JavaVirtualMachine::createByteArray(int size) {
    auto array = env->NewByteArray(size);
    return JavaArray<jbyte>(array);
}

JavaArray<jchar> JavaVirtualMachine::createCharArray(int size) {
    auto array = env->NewCharArray(size);
    return JavaArray<jchar>( array);
}

JavaArray<jshort> JavaVirtualMachine::createShortArray(int size) {
    auto array = env->NewShortArray(size);
    return JavaArray<jshort>( array);
}

JavaArray<jint> JavaVirtualMachine::createIntArray(int size) {
    auto array = env->NewIntArray(size);
    return JavaArray<jint>( array);
}

JavaArray<jlong> JavaVirtualMachine::createLongArray(int size) {
    auto array = env->NewLongArray(size);
    return JavaArray<jlong>( array);
}

JavaArray<jfloat> JavaVirtualMachine::createFloatArray(int size) {
    auto array = env->NewFloatArray(size);
    return JavaArray<jfloat>( array);
}

JavaArray<jdouble> JavaVirtualMachine::createDoubleArray(int size) {
    auto array = env->NewDoubleArray(size);
    return JavaArray<jdouble>( array);
}

JavaArray<JavaObject> JavaVirtualMachine::createObjectArray(int size, const JavaClass &clazz) {
    auto array = env->NewObjectArray(size, clazz.nativeClass, nullptr);
    return JavaArray<JavaObject>( array);
}
