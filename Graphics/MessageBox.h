// Copyright James Puleo 2020
// Copyright Riverbend 2020

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
#include <string>
#include "Types.h"

class MessageBox final
{
public:
    enum class Type : u32
    {
        Info,
        Error
    };

    enum class Button : u32
    {
        OK,
        OKCancel,
        YesNo,
    };

    static void open(std::string title, std::string text, Type, Button);
    
private:
    MessageBox() {}
};
