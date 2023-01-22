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
#include "JavaMethod.h"
#include "JavaObject.h"
#include "JavaVirtualMachineRegistry.h"

using namespace easyjni;
using namespace std;

JavaObject::JavaObject(jobject nativeObject) :
        nativeObject(nativeObject) {
    // Nothing to do: everything is already initialized.
}

jobject JavaObject::operator*() {
    return nativeObject;
}

bool JavaObject::isNull() {
    return nativeObject == nullptr;
}

JavaClass JavaObject::getClass() {
    jclass cls = JavaVirtualMachineRegistry::getEnvironment()->GetObjectClass(nativeObject);
    JavaVirtualMachineRegistry::get()->checkException();
    return JavaClass("<unknown-class>", cls);
}

int JavaObject::hashCode() {
    auto metaClass = getClass();
    auto method = metaClass.getIntMethod("hashCode");
    return method.invoke(*this);
}

bool JavaObject::equals(JavaObject &other) {
    auto metaClass = getClass();
    auto method = metaClass.getBooleanMethod("equals", METHOD(BOOLEAN, CLASS(java/lang/Object)));
    return method.invoke(*this, *other);
}

string JavaObject::toString() {
    // Invoking the toString() method on the Java object.
    auto metaClass = getClass();
    auto method = metaClass.getObjectMethod("toString", METHOD(CLASS(java/lang/String)));
    auto str = method.invoke(*this);
    auto javaString = (jstring) str.nativeObject;

    // Copying the Java string into a C++ string.
    const char *nativeString = JavaVirtualMachineRegistry::getEnvironment()->GetStringUTFChars(javaString, nullptr);
    JavaVirtualMachineRegistry::get()->checkException();
    string cppString(nativeString);
    JavaVirtualMachineRegistry::getEnvironment()->ReleaseStringUTFChars(javaString, nativeString);
    JavaVirtualMachineRegistry::get()->checkException();
    return cppString;
}
