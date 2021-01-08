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

#include "DataSize.h"
#include <cmath>
#include <fmt/core.h>

namespace LibFruit
{
    // Instead of kB / MB and so on, ISO/IEC 80000 calls these
    // types 'kibi' and 'mebi' and so on. This is to avoid confusion
    // with SI types.
    const char* DataSize::m_type_suffix[] = {"B", "KiB", "MiB", "GiB", "TiB", "PiB"};

    DataSize::DataSize(u64 size) : m_size(size)
    {
        if(m_size < 1024)
        {
            m_most_fitting = display(Type::Byte);
        }
        else
        {
            auto exp = 1;

            while(m_size + 1 > std::powl(1024, exp))
                exp++;

            exp--;

            m_most_fitting = display(static_cast<Type>(exp));
        }
    }

    inline double DataSize::convert(Type t)
    {
        if(t == Type::Byte)
            return static_cast<double>(m_size);

        auto exp = static_cast<u32>(t);
        auto val = std::powl(1024, exp);
        return m_size / val;
    }

    inline std::string DataSize::display(Type t, bool include_suffix)
    {
        if(!include_suffix)
            return std::to_string(convert(t));

        return fmt::format("{:.2f} {}", convert(t), m_type_suffix[static_cast<u32>(t)]);
    }
}
