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
#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#endif

namespace LibFruit
{
    // Can't make templated methods virtual so... this will have to do...
    // Sadly this class has turned very ugly because the original design was singleton and inherited...
    // but because of the above issue, everything got worse.
    class DebugLogger
    {
        friend class Logger;
    public:
        template<typename... TArgs>
        void println(const char* msg, TArgs&&... args)
        {
#ifdef _DEBUG
            fmt::print(stdout, msg, args...);
            fmt::print(stdout, "\n");
#endif
#ifdef _WIN32
            OutputDebugStringA(fmt::format(msg, args...).c_str());
#endif
        }
    private:
        DebugLogger() {}
    };

    class ErrorLogger
    {
        friend class Logger;
    public:
        template<typename... TArgs>
        void println(const char* msg, TArgs&&... args)
        {
            fmt::print(stderr, msg, args...);
            fmt::print(stderr, "\n");
#ifdef _WIN32
            OutputDebugStringA(fmt::format(msg, args...).c_str());
#endif
        }
    private:
        ErrorLogger() {}
    };

    class Logger
    {
    public:
        template<typename... TArgs>
        void println(const char* msg, TArgs&&... args)
        {
            fmt::print(stdout, msg, args...);
            fmt::print(stdout, "\n");
        }

        static Logger& out() { return m_out; }
        static DebugLogger& dbg() { return m_dbg; }
        static ErrorLogger& error() { return m_err; }

    private:
        Logger() {}
        static Logger m_out;
        static ErrorLogger m_err;
        static DebugLogger m_dbg;
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
