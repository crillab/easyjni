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

#ifndef EASYJNI_JNIEXCEPTION_H
#define EASYJNI_JNIEXCEPTION_H

#include <exception>
#include <string>

namespace easyjni {

    /**
     * The JniException defines an exception that is thrown when an error
     * occurs while trying to retrieve or execute Java code from the C++ side.
     *
     * @author Romain Wallon
     *
     * @version 0.1.0
     */
    class JniException : public std::exception {

    private:

        /**
         * The error message describing the problem that occurred.
         */
        std::string message;

    public:

        /**
         * Creates a new JniException.
         *
         * @param message The error message describing the problem that occurred.
         */
        explicit JniException(std::string message);

        /**
         * Gives the error message of this exception.
         *
         * @return The error message describing the problem that occurred.
         */
        [[nodiscard]] const char *what() const noexcept override;

    };

}

#endif
