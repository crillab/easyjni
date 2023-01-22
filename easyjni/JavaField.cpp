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

#include "JavaField.h"

using namespace easyjni;
using namespace std;

template<>
JavaField<jboolean> JavaField<jboolean>::newInstance(string name, jfieldID nativeField) {
    return JavaField(
            std::move(name), nativeField,
            [](JNIEnv *env, jobject obj, jfieldID fld) {
                return env->GetBooleanField(obj, fld);
            },
            [](JNIEnv *env, jobject obj, jfieldID fld, jboolean val) {
                env->SetBooleanField(obj, fld, val);
            },
            [](JNIEnv *env, jclass cls, jfieldID fld) {
                return env->GetStaticBooleanField(cls, fld);
            },
            [](JNIEnv *env, jclass cls, jfieldID fld, jboolean val) {
                env->SetStaticBooleanField(cls, fld, val);
            });
}

template<>
JavaField<jbyte> JavaField<jbyte>::newInstance(string name, jfieldID nativeField) {
    return JavaField(
            std::move(name), nativeField,
            [](JNIEnv *env, jobject obj, jfieldID fld) {
                return env->GetByteField(obj, fld);
            },
            [](JNIEnv *env, jobject obj, jfieldID fld, jbyte val) {
                env->SetByteField(obj, fld, val);
            },
            [](JNIEnv *env, jclass cls, jfieldID fld) {
                return env->GetStaticByteField(cls, fld);
            },
            [](JNIEnv *env, jclass cls, jfieldID fld, jbyte val) {
                env->SetStaticByteField(cls, fld, val);
            });
}

template<>
JavaField<jchar> JavaField<jchar>::newInstance(string name, jfieldID nativeField) {
    return JavaField(
            std::move(name), nativeField,
            [](JNIEnv *env, jobject obj, jfieldID fld) {
                return env->GetCharField(obj, fld);
            },
            [](JNIEnv *env, jobject obj, jfieldID fld, jchar val) {
                env->SetCharField(obj, fld, val);
            },
            [](JNIEnv *env, jclass cls, jfieldID fld) {
                return env->GetStaticCharField(cls, fld);
            },
            [](JNIEnv *env, jclass cls, jfieldID fld, jchar val) {
                env->SetStaticCharField(cls, fld, val);
            });
}

template<>
JavaField<jshort> JavaField<jshort>::newInstance(string name, jfieldID nativeField) {
    return JavaField(
            std::move(name), nativeField,
            [](JNIEnv *env, jobject obj, jfieldID fld) {
                return env->GetShortField(obj, fld);
            },
            [](JNIEnv *env, jobject obj, jfieldID fld, jshort val) {
                env->SetShortField(obj, fld, val);
            },
            [](JNIEnv *env, jclass cls, jfieldID fld) {
                return env->GetStaticShortField(cls, fld);
            },
            [](JNIEnv *env, jclass cls, jfieldID fld, jshort val) {
                env->SetStaticShortField(cls, fld, val);
            });
}

template<>
JavaField<jint> JavaField<jint>::newInstance(string name, jfieldID nativeField) {
    return JavaField(
            std::move(name), nativeField,
            [](JNIEnv *env, jobject obj, jfieldID fld) {
                return env->GetIntField(obj, fld);
            },
            [](JNIEnv *env, jobject obj, jfieldID fld, jint val) {
                env->SetIntField(obj, fld, val);
            },
            [](JNIEnv *env, jclass cls, jfieldID fld) {
                return env->GetStaticIntField(cls, fld);
            },
            [](JNIEnv *env, jclass cls, jfieldID fld, jint val) {
                env->SetStaticIntField(cls, fld, val);
            });
}

template<>
JavaField<jlong> JavaField<jlong>::newInstance(string name, jfieldID nativeField) {
    return JavaField(
            std::move(name), nativeField,
            [](JNIEnv *env, jobject obj, jfieldID fld) {
                return env->GetLongField(obj, fld);
            },
            [](JNIEnv *env, jobject obj, jfieldID fld, jlong val) {
                env->SetLongField(obj, fld, val);
            },
            [](JNIEnv *env, jclass cls, jfieldID fld) {
                return env->GetStaticLongField(cls, fld);
            },
            [](JNIEnv *env, jclass cls, jfieldID fld, jlong val) {
                env->SetStaticLongField(cls, fld, val);
            });
}

template<>
JavaField<jfloat> JavaField<jfloat>::newInstance(string name, jfieldID nativeField) {
    return JavaField(
            std::move(name), nativeField,
            [](JNIEnv *env, jobject obj, jfieldID fld) {
                return env->GetFloatField(obj, fld);
            },
            [](JNIEnv *env, jobject obj, jfieldID fld, jfloat val) {
                env->SetFloatField(obj, fld, val);
            },
            [](JNIEnv *env, jclass cls, jfieldID fld) {
                return env->GetStaticFloatField(cls, fld);
            },
            [](JNIEnv *env, jclass cls, jfieldID fld, jfloat val) {
                env->SetStaticFloatField(cls, fld, val);
            });
}

template<>
JavaField<jdouble> JavaField<jdouble>::newInstance(string name, jfieldID nativeField) {
    return JavaField(
            std::move(name), nativeField,
            [](JNIEnv *env, jobject obj, jfieldID fld) {
                return env->GetDoubleField(obj, fld);
            },
            [](JNIEnv *env, jobject obj, jfieldID fld, jdouble val) {
                env->SetDoubleField(obj, fld, val);
            },
            [](JNIEnv *env, jclass cls, jfieldID fld) {
                return env->GetStaticDoubleField(cls, fld);
            },
            [](JNIEnv *env, jclass cls, jfieldID fld, jdouble val) {
                env->SetStaticDoubleField(cls, fld, val);
            });
}

template<>
JavaField<JavaObject> JavaField<JavaObject>::newInstance(string name, jfieldID nativeField) {
    return JavaField(
            std::move(name), nativeField,
            [](JNIEnv *env, jobject obj, jfieldID fld) {
                jobject res = env->GetObjectField(obj, fld);
                return JavaObject(res);
            },
            [](JNIEnv *env, jobject obj, jfieldID fld, JavaObject val) {
                env->SetObjectField(obj, fld, *val);
            },
            [](JNIEnv *env, jclass cls, jfieldID fld) {
                jobject res = env->GetStaticObjectField(cls, fld);
                return JavaObject(res);
            },
            [](JNIEnv *env, jclass cls, jfieldID fld, JavaObject val) {
                env->SetStaticObjectField(cls, fld, *val);
            });
}
