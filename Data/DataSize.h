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
#include "Types.h"
#include <string>

namespace LibFruit
{
    // TODO: Improve performance of this data by caching some values
    class DataSize
    {
    public:
        // Although these types follow SI naming scheme,
        // data sizes should (and are) interpreted binary wise,
        // following ISO/IEC 80000. This means that each
        // type is a multiple of 1024 (instead of 1000).
        enum class Type
        {
            Byte,
            Kilobyte,
            Megabyte,
            Gigabyte,
            Terrabyte,
            Petabyte
        };

        DataSize(u64 size) : m_size(size) {}
        u64 size() { return m_size; }

        inline double convert(Type);
        inline std::string display(Type, bool include_suffix = true);
        // Display this as the most fitting size.
        // Will pick the last size that displays a whole number.
        std::string display_most_fitting();
    private:
        static const char* m_type_suffix[];
        u64 m_size;
    };
}
