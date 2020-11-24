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
    class VTable
    {
    public:
        void* vtable_entry(u32 index)
        {
            return m_obj[index];
        }

        template<typename TFuncDec>
        TFuncDec vtable_entry_as_function(u32 index)
        {
            return reinterpret_cast<TFuncDec>(vtable_entry(index));
        }

    private:
        void** m_obj;
    };

    template<typename T>
    class ObjectPointer
    {
    public:
        ObjectPointer(T obj) : m_obj(obj) {}

        VTable* vtable()
        {
            return reinterpret_cast<VTable*>(m_obj);
        }

    protected:
        T m_obj;
    };
}
