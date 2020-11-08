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
#include "Parser.h"
#include <cstring>

namespace LibFruit
{
    Parser::Parser(const char* chars) : m_characters(chars) {}

    char Parser::consume()
    {
        return m_characters[m_index++];
    }

    char Parser::peek()
    {
        return m_characters[m_index];
    }

    char Parser::backpeek()
    {
        return m_characters[m_index - 1];
    }

    char Parser::consume_while(char c, std::function<void(char)> fn)
    {
        char consumed;
        while((consumed = consume()) == c)
        {
            if(fn)
                fn(consumed);
        }

        return consumed;
    }

    char Parser::consume_until(char c, std::function<void(char)> fn)
    {
        char consumed;
        while((consumed = consume()) != c)
        {
            if(fn)
                fn(consumed);
        }

        return consumed;
    }

    bool Parser::finished()
    {
        return m_index >= strlen(m_characters);
    }

    void Parser::reset()
    {
        m_index = 0;
    }
}
