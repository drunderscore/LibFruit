// Copyright James Puleo 2020
// Copyright LibFruit 2020

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

#pragma once
#include <stdio.h>
#include "fmt/core.h"

namespace LibFruit
{
    class Logger
    {
    public:
        Logger(FILE* handle) : m_handle(handle) {}

        template<typename... TArgs>
        void println(const char* msg, TArgs&&... args)
        {
            fmt::print(m_handle, msg, args...);
            fmt::print(m_handle, "\n");
        }

        static Logger& out() { return m_out; }
        static Logger& error() { return m_err; }

    private:
        static Logger m_out;
        static Logger m_err;
        FILE* m_handle;
    };
}
using LibFruit::Logger;

// Macros are ugly, but we need them for logging compile-time data.
#define FRUIT_STRINGIFY_(x) #x
#define FRUIT_STRINGIFY(x) FRUIT_STRINGIFY_(x)
#define CHECK(condition) CHECK_MSG(condition, "???")
#define CHECK_MSG(condition, msg, ...) \
if(!(condition)) \
{ \
    LibFruit::Logger::error().println("Assertion failed: " FRUIT_STRINGIFY(condition)); \
    LibFruit::Logger::error().println("\tWhat: {}", fmt::format(msg, __VA_ARGS__) ); \
    LibFruit::Logger::error().println("\tFile: " FRUIT_STRINGIFY(__FILE__)); \
    LibFruit::Logger::error().println("\tFunction: " __FUNCTION__); \
    LibFruit::Logger::error().println("\tLine: " FRUIT_STRINGIFY(__LINE__)); \
    abort(); \
}
