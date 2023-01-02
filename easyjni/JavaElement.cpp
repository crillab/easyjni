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

#include "JavaElement.h"
#include "JavaVirtualMachineRegistry.h"

using namespace easyjni;
using namespace std;

JavaElement::JavaElement(string name) :
        name(std::move(name)) {
    // Nothing to do: everything is already initialized.
}

JNIEnv *JavaElement::getEnvironment() {
    return JavaVirtualMachineRegistry::getEnvironment();
}

const string &JavaElement::getName() const {
    return name;
}
