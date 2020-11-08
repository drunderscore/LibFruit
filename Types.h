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
#include <cinttypes>

namespace LibFruit
{
    using u8 = uint8_t;
    using u16 = uint16_t;
    using u32 = uint32_t;
    using u64 = uint64_t;
}

// Specifying the namespace constantly isn't always the best,
// especially in incredibly common types like these.
#ifndef FRUIT_USE_NAMESPACED_TYPES
using u8 = LibFruit::u8;
using u16 = LibFruit::u16;
using u32 = LibFruit::u32;
using u64 = LibFruit::u64;
#endif
