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
#include <optional>
#include <string>

namespace LibFruit
{
    template<typename T>
    class Result : public std::optional<T>
    {
    public:
        Result(T val) : std::optional<T>(val) {}
        Result(std::string error) : m_error(error) {}
        Result(const char* error) : m_error(error) {}

        std::string& error(){ return m_error; }

    private:
        std::string m_error;
    };
}

template<typename T>
using Result = LibFruit::Result<T>;
