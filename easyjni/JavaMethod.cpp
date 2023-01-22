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

#include "JavaMethod.h"

using namespace easyjni;
using namespace std;

template<>
JavaMethod<void *> JavaMethod<void *>::newInstance(string name, jmethodID nativeMethod) {
    return JavaMethod(
            std::move(name), nativeMethod,
            [](JNIEnv *env, jobject obj, jmethodID mtd, va_list args) {
                env->CallVoidMethodV(obj, mtd, args);
                return nullptr;
            },
            [](JNIEnv *env, jclass cls, jmethodID mtd, va_list args) {
                env->CallStaticVoidMethodV(cls, mtd, args);
                return nullptr;
            });
}

template<>
JavaMethod<jboolean> JavaMethod<jboolean>::newInstance(string name, jmethodID nativeMethod) {
    return JavaMethod(
            std::move(name), nativeMethod,
            [](JNIEnv *env, jobject obj, jmethodID mtd, va_list args) {
                return env->CallBooleanMethodV(obj, mtd, args);
            },
            [](JNIEnv *env, jclass cls, jmethodID mtd, va_list args) {
                return env->CallStaticBooleanMethodV(cls, mtd, args);
            });
}

template<>
JavaMethod<jbyte> JavaMethod<jbyte>::newInstance(string name, jmethodID nativeMethod) {
    return JavaMethod(
            std::move(name), nativeMethod,
            [](JNIEnv *env, jobject obj, jmethodID mtd, va_list args) {
                return env->CallByteMethodV(obj, mtd, args);
            },
            [](JNIEnv *env, jclass cls, jmethodID mtd, va_list args) {
                return env->CallStaticByteMethodV(cls, mtd, args);
            });
}

template<>
JavaMethod<jchar> JavaMethod<jchar>::newInstance(string name, jmethodID nativeMethod) {
    return JavaMethod(
            std::move(name), nativeMethod,
            [](JNIEnv *env, jobject obj, jmethodID mtd, va_list args) {
                return env->CallCharMethodV(obj, mtd, args);
            },
            [](JNIEnv *env, jclass cls, jmethodID mtd, va_list args) {
                return env->CallStaticCharMethodV(cls, mtd, args);
            });
}

template<>
JavaMethod<jshort> JavaMethod<jshort>::newInstance(string name, jmethodID nativeMethod) {
    return JavaMethod(
            std::move(name), nativeMethod,
            [](JNIEnv *env, jobject obj, jmethodID mtd, va_list args) {
                return env->CallShortMethodV(obj, mtd, args);
            },
            [](JNIEnv *env, jclass cls, jmethodID mtd, va_list args) {
                return env->CallStaticShortMethodV(cls, mtd, args);
            });
}

template<>
JavaMethod<jint> JavaMethod<jint>::newInstance(string name, jmethodID nativeMethod) {
    return JavaMethod(
            std::move(name), nativeMethod,
            [](JNIEnv *env, jobject obj, jmethodID mtd, va_list args) {
                return env->CallIntMethodV(obj, mtd, args);
            },
            [](JNIEnv *env, jclass cls, jmethodID mtd, va_list args) {
                return env->CallStaticIntMethodV(cls, mtd, args);
            });
}

template<>
JavaMethod<jlong> JavaMethod<jlong>::newInstance(string name, jmethodID nativeMethod) {
    return JavaMethod(
            std::move(name), nativeMethod,
            [](JNIEnv *env, jobject obj, jmethodID mtd, va_list args) {
                return env->CallLongMethodV(obj, mtd, args);
            },
            [](JNIEnv *env, jclass cls, jmethodID mtd, va_list args) {
                return env->CallStaticLongMethodV(cls, mtd, args);
            });
}

template<>
JavaMethod<jfloat> JavaMethod<jfloat>::newInstance(string name, jmethodID nativeMethod) {
    return JavaMethod(
            std::move(name), nativeMethod,
            [](JNIEnv *env, jobject obj, jmethodID mtd, va_list args) {
                return env->CallFloatMethodV(obj, mtd, args);
            },
            [](JNIEnv *env, jclass cls, jmethodID mtd, va_list args) {
                return env->CallStaticFloatMethodV(cls, mtd, args);
            });
}

template<>
JavaMethod<jdouble> JavaMethod<jdouble>::newInstance(string name, jmethodID nativeMethod) {
    return JavaMethod(
            std::move(name), nativeMethod,
            [](JNIEnv *env, jobject obj, jmethodID mtd, va_list args) {
                return env->CallDoubleMethodV(obj, mtd, args);
            },
            [](JNIEnv *env, jclass cls, jmethodID mtd, va_list args) {
                return env->CallStaticDoubleMethodV(cls, mtd, args);
            });
}

template<>
JavaMethod<JavaObject> JavaMethod<JavaObject>::newInstance(string name, jmethodID nativeMethod) {
    return JavaMethod(
            std::move(name), nativeMethod,
            [](JNIEnv *env, jobject obj, jmethodID mtd, va_list args) {
                jobject res = env->CallObjectMethodV(obj, mtd, args);
                return JavaObject(res);
            },
            [](JNIEnv *env, jclass cls, jmethodID mtd, va_list args) {
                jobject res = env->CallStaticObjectMethodV(cls, mtd, args);
                return JavaObject(res);
            });
}
