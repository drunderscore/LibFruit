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

namespace LibFruit
{
    class Protection
    {
    public:
        enum class Type : u32
        {
            NoAccess,
            Execute,
            ExecuteRead,
            ExecuteReadWrite,
            ReadWrite,
            ReadOnly,
        };

        Protection(void* address, u32 size, Type type);
        template<typename T>
        Protection(T address, Type type) : Protection(reinterpret_cast<void*>(address), sizeof(T), type) {}
        ~Protection();

        bool is_applied() { return m_applied; }

    private:
        void* m_address;
        u32 m_size;
        Type m_original_protection;
        bool m_applied = false;

        u32 translate_to_platform(Type);
        Type translate_from_platform(u32);
    };
}
