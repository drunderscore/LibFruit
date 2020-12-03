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


#include "Memory.h"
#include "subhook/subhook.h"

namespace LibFruit::Detour
{
    Memory::Memory(void* src, void* detour, bool enable_now)
    {
        m_hook = subhook_new(src, detour, static_cast<subhook_flags_t>(0));
        if(enable_now)
            enable();
    }

    void Memory::enable()
    {
        subhook_install(m_hook);
    }

    void Memory::disable()
    {
        subhook_remove(m_hook);
    }

    void* Memory::original()
    {
        return subhook_get_trampoline(m_hook);
    }

    bool Memory::is_enabled()
    {
        return subhook_is_installed(m_hook);
    }

    Memory::~Memory()
    {
        disable();
        subhook_free(m_hook);
    }
}
