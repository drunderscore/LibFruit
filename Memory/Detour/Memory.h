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

struct subhook_struct;
typedef struct subhook_struct *subhook_t;

namespace LibFruit::Detour
{
    // TODO: Craft our own x86/x64 detouring
    class Memory
    {
    public:
        Memory(void*, void* detour, bool enable_now = true);
        ~Memory();

        void enable();
        void disable();
        void* original();
        bool is_enabled();

    private:
        subhook_t m_hook = nullptr;
    };

    template<typename TFuncDec>
    class SmartMemory : public Memory
    {
    public:
        SmartMemory(TFuncDec src, TFuncDec detour, bool enable_now = true) : Memory(reinterpret_cast<void*>(src), reinterpret_cast<void*>(detour), enable_now) {}

        TFuncDec call_original()
        {
            return reinterpret_cast<TFuncDec>(original());
        }
    };
}
