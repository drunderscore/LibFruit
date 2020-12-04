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
#include "Data/Stream.h"
#include <vector>
#include <optional>

namespace LibFruit
{
    template<typename TInstruction>
    class Disassembler
    {
    public:
        Disassembler(std::vector<u8> data) : m_data(std::move(data)), m_stream(m_data.data(), m_data.size(), false) {}
        virtual ~Disassembler() {}

        virtual std::optional<TInstruction> disassemble_one() = 0;
        virtual std::optional<std::vector<TInstruction>> disassemble() = 0;

        bool has_error() { return m_error; }
    protected:
        bool m_error = false;
        std::vector<u8> m_data;
        Stream m_stream;
    };
}
