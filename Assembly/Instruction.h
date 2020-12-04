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
#include <vector>
#include "Types.h"

namespace LibFruit
{
    template<typename TOpcode>
    class Instruction
    {
    public:
        TOpcode opcode() { return m_opcode; }
        const std::vector<u8> operands() const { return m_operands; }

    protected:
        Instruction(TOpcode op, std::vector<u8> operands);

    private:
        TOpcode m_opcode;
        std::vector<u8> m_operands;
    };
}
