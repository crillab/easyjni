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

#ifndef EASYJNI_JAVAELEMENT_H
#define EASYJNI_JAVAELEMENT_H

#include <string>

#include <jni.h>

namespace easyjni {

    /**
     * The JavaElement is the parent class of all Java elements extracted
     * from the Java Virtual Machine.
     *
     * @author Romain Wallon
     *
     * @version 0.1.0
     */
    class JavaElement {

    protected:

        /**
         * The name of this element.
         */
        std::string name;

    protected:

        /**
         * Creates a new JavaElement.
         *
         * @param environment The Java environment in which the element has been declared.
         * @param name The name of the element.
         */
        explicit JavaElement(std::string name);

        static JNIEnv* getEnvironment();

    public:

        /**
         * Gives the name of this Java element.
         *
         * @return The name of this element.
         */
        [[nodiscard]] const std::string &getName() const;

    };

}

#endif
