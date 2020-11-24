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

#include "Virtual.h"
#include "Memory/Protection.h"
#include "Log.h"

namespace LibFruit::Detour
{
    Virtual::Virtual(VTable vtable, u32 index, void* detour, bool enable_now) : m_vtable(vtable), m_index(index), m_detour(detour)
    {
        if(enable_now)
            enable();
    }

    Virtual::~Virtual()
    {
        if(is_enabled())
            disable();
    }

    void Virtual::enable()
    {
        if(is_enabled())
            return;

        void* addr = &m_vtable[m_index];
        Protection prot(addr, Protection::Type::ReadWrite);
        if(!prot.is_applied())
        {
            Logger::error().println("Unable to get protection for vtable write at address {} (index {}), bailing.", addr, m_index);
            return;
        }
        m_original = m_vtable[m_index];
        m_vtable[m_index] = m_detour;
        m_enabled = true;
        Logger::dbg().println("Virtual detour of {} (index {}) enabled", addr, m_index);
    }

    void Virtual::disable()
    {
        if(!is_enabled())
            return;

        void* addr = &m_vtable[m_index];
        Protection prot(addr, Protection::Type::ReadWrite);
        if(!prot.is_applied())
        {
            Logger::error().println("Unable to get protection for vtable write at address {} (index {}), bailing.", addr, m_index);
            return;
        }
        m_vtable[m_index] = m_original;
        m_enabled = false;
        Logger::dbg().println("Virtual detour of {} (index {}) disabled", addr, m_index);
    }
}
