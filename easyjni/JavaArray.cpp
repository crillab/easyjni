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

#include "JavaArray.h"
#include "JavaObject.h"

using namespace easyjni;
using namespace std;

template<>
jboolean JavaArray<jboolean>::get(int index) {
    jboolean b;
    JavaVirtualMachineRegistry::get()->env->GetBooleanArrayRegion((jbooleanArray) array, index, 1, &b);
    return b;
}

template<>
void JavaArray<jboolean>::set(int index, jboolean elt) {
    JavaVirtualMachineRegistry::get()->env->SetBooleanArrayRegion((jbooleanArray) array, index, 1, &elt);
}

template<>
jbyte JavaArray<jbyte>::get(int index) {
    jbyte b;
    JavaVirtualMachineRegistry::get()->env->GetByteArrayRegion((jbyteArray) array, index, 1, &b);
    return b;
}

template<>
void JavaArray<jbyte>::set(int index, jbyte elt) {
    JavaVirtualMachineRegistry::get()->env->SetByteArrayRegion((jbyteArray) array, index, 1, &elt);
}

template<>
jchar JavaArray<jchar>::get(int index) {
    jchar c;
    JavaVirtualMachineRegistry::get()->env->GetCharArrayRegion((jcharArray) array, index, 1, &c);
    return c;
}

template<>
void JavaArray<jchar>::set(int index, jchar elt) {
    JavaVirtualMachineRegistry::get()->env->SetCharArrayRegion((jcharArray) array, index, 1, &elt);
}

template<>
jshort JavaArray<jshort>::get(int index) {
    jshort s;
    JavaVirtualMachineRegistry::get()->env->GetShortArrayRegion((jshortArray) array, index, 1, &s);
    return s;
}

template<>
void JavaArray<jshort>::set(int index, jshort elt) {
    JavaVirtualMachineRegistry::get()->env->SetShortArrayRegion((jshortArray) array, index, 1, &elt);
}

template<>
jint JavaArray<jint>::get(int index) {
    jint i;
    JavaVirtualMachineRegistry::get()->env->GetIntArrayRegion((jintArray) array, index, 1, &i);
    return i;
}

template<>
void JavaArray<jint>::set(int index, jint elt) {
    JavaVirtualMachineRegistry::get()->env->SetIntArrayRegion((jintArray) array, index, 1, &elt);
}

template<>
jlong JavaArray<jlong>::get(int index) {
    jlong l;
    JavaVirtualMachineRegistry::get()->env->GetLongArrayRegion((jlongArray) array, index, 1, &l);
    return l;
}

template<>
void JavaArray<jlong>::set(int index, jlong elt) {
    JavaVirtualMachineRegistry::get()->env->SetLongArrayRegion((jlongArray) array, index, 1, &elt);
}

template<>
jfloat JavaArray<jfloat>::get(int index) {
    jfloat f;
    JavaVirtualMachineRegistry::get()->env->GetFloatArrayRegion((jfloatArray) array, index, 1, &f);
    return f;
}

template<>
void JavaArray<jfloat>::set(int index, jfloat elt) {
    JavaVirtualMachineRegistry::get()->env->SetFloatArrayRegion((jfloatArray) array, index, 1, &elt);
}

template<>
jdouble JavaArray<jdouble>::get(int index) {
    jdouble d;
    JavaVirtualMachineRegistry::get()->env->GetDoubleArrayRegion((jdoubleArray) array, index, 1, &d);
    return d;
}

template<>
void JavaArray<jdouble>::set(int index, jdouble elt) {
    JavaVirtualMachineRegistry::get()->env->SetDoubleArrayRegion((jdoubleArray) array, index, 1, &elt);
}

template<>
JavaObject JavaArray<JavaObject>::get(int index) {
    jobject obj = JavaVirtualMachineRegistry::get()->env->GetObjectArrayElement((jobjectArray) array, index);
    return JavaObject(obj);
}

template<>
void JavaArray<JavaObject>::set(int index, JavaObject elt) {
    JavaVirtualMachineRegistry::get()->env->SetObjectArrayElement((jobjectArray) array, index, elt.nativeObject);
}
