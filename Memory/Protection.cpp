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

#include "Protection.h"
#include "Log.h"

#ifdef _WIN32
#include <Windows.h>
#else
#error No memory protection API available for this platform.
#endif // _WIN32

namespace LibFruit
{
    Protection::Protection(void* address, u32 size, Type type) : m_address(address), m_size(size)
    {
        ul32 old_protection = 0;
        raw_ptr end_address = reinterpret_cast<raw_ptr>(m_address) + m_size;
        auto ret = VirtualProtect(m_address, m_size, translate_to_platform(type), &old_protection);
        if(!SUCCEEDED(ret))
            Logger::error().println("VirtualProtect failed to update memory protection of {}-{:#0x} to {}: {}", m_address, end_address, type, GetLastError());
        else
        {
            m_original_protection = translate_from_platform(old_protection);
            m_applied = true;
            Logger::dbg().println("Updated memory protection of {}-{:#0x} to {}", m_address, end_address, type);
        }
    }

    Protection::~Protection()
    {
        if(!m_applied)
            return;

        ul32 discard = 0;
        raw_ptr end_address = reinterpret_cast<raw_ptr>(m_address) + m_size;
        auto ret = VirtualProtect(m_address, m_size, translate_to_platform(m_original_protection), &discard);
        if(!SUCCEEDED(ret))
        {
            Logger::error().println("VirtualProtect failed to revert memory protection of {}-{:#0x} to {}", m_address, end_address, m_original_protection);
        }
        else
        {
            Logger::dbg().println("Reverting memory protection of {}-{:#0x} to {}", m_address, end_address, m_original_protection);
            m_applied = false;
        }
    }

    u32 Protection::translate_to_platform(Type t)
    {
        switch(t)
        {
            case Type::NoAccess:
                return PAGE_NOACCESS;
            case Type::Execute:
                return PAGE_EXECUTE;
            case Type::ExecuteRead:
                return PAGE_EXECUTE_READ;
            case Type::ExecuteReadWrite:
                return PAGE_EXECUTE_READWRITE;
            case Type::ReadWrite:
                return PAGE_READWRITE;
            case Type::ReadOnly:
                return PAGE_READONLY;
        }
        CHECK_MSG(false, "Unable to translate memory protection to platform ({})", t);
    }

    Protection::Type Protection::translate_from_platform(u32 prot)
    {
        switch(prot)
        {
            case PAGE_NOACCESS:
                return Type::NoAccess;
            case PAGE_EXECUTE:
                return Type::Execute;
            case PAGE_EXECUTE_READ:
                return Type::ExecuteRead;
            case PAGE_EXECUTE_READWRITE:
                return Type::ExecuteReadWrite;
            case PAGE_READWRITE:
                return Type::ReadWrite;
            case PAGE_READONLY:
                return Type::ReadOnly;
        }
        CHECK_MSG(false, "Unable to translate memory protection from platform ({})", prot);
    }
}
