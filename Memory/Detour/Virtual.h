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

namespace LibFruit::Detour
{
    class Virtual
    {
    public:
        using VTable = void**;

        Virtual(VTable, u32 index, void* detour, bool enable_now = true);
        ~Virtual();

        void enable();
        void disable();

        void* original() { return m_original; }
        bool is_enabled() { return m_enabled; }

    protected:
        VTable m_vtable;
        u32 m_index;
        void* m_original;
        void* m_detour;
        bool m_enabled = false;
    };

    template<typename T, typename TFuncDec>
    class SmartVirtual : public Virtual
    {
    public:
        SmartVirtual(T obj, u32 index, TFuncDec detour, bool enable_now = true) : Virtual(*reinterpret_cast<void***>(obj), index, reinterpret_cast<void*>(detour), enable_now) {}

        TFuncDec call_original()
        {
            return reinterpret_cast<TFuncDec>(m_original);
        }
    };
}
