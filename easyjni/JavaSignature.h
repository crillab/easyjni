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

#ifndef EASYJNI_JAVASIGNATURE_H
#define EASYJNI_JAVASIGNATURE_H

#include <jni.h>

#define BOOLEAN     "Z"
#define BYTE        "B"
#define CHARACTER   "C"
#define SHORT       "S"
#define INTEGER     "I"
#define LONG        "J"
#define FLOAT       "F"
#define DOUBLE      "D"
#define VOID        "V"

#define ARRAY(t)    "[" t

#define CLASS(t)    "L" #t ";"

#define CONSTRUCTOR(arguments)      "(" arguments ")V"
#define METHOD(returnType, ...)     "(" __VA_ARGS__ ")" returnType

#endif
