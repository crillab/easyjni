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

#include <jni.h>

#include "crillab-easyjni/JniException.h"

using namespace easyjni;
using namespace std;

/**
 * Looks up the error message string corresponding to an error number.
 *
 * @param errorNumber The error number produced by JNI.
 *
 * @return The message describing the error.
 */
static string jerror(int errorNumber) {
    switch (errorNumber) {
        case JNI_OK:
            return "success";

        case JNI_EDETACHED:
            return "thread detached from the VM";

        case JNI_EVERSION:
            return "JNI version error";

        case JNI_ENOMEM:
            return "not enough memory";

        case JNI_EEXIST:
            return "VM already created";

        case JNI_EINVAL:
            return "invalid arguments";

        default:
            return "unknown error";
    }
}

JniException::JniException(int errorCode, const string &when) {
    if (!when.empty()) {
        message = when + ": ";
    }
    message += jerror(errorCode);
}

JniException::JniException(string message) :
        message(std::move(message)) {
    // Nothing to do: everything is already initialized.
}

const char *JniException::what() const noexcept {
    return message.c_str();
}
