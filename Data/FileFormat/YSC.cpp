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

#include "YSC.h"

namespace LibFruit::FileFormat
{
    std::optional<YSC> YSC::parse(std::istream& in_stream)
    {
        YSC script;
        Stream stream(in_stream);

        stream.read(script.m_header);
        if(script.m_header.m_magic != YSC::Header::MAGIC)
            return {};

        read_blocks(stream, script.m_code_blocks, script.m_header.code_blocks_ptr(), script.m_header.code_size());
        read_blocks(stream, script.m_strings.m_blocks, script.m_header.string_blocks_ptr(), script.m_header.string_size());
        script.m_strings.calculate();
        stream.seek(script.m_header.script_name_ptr());
        script.m_script_name = stream.read_null_terminated_string();

        // These native transformations serve no purpose BUT to make reverse engineering more difficult.
        stream.seek(script.m_header.natives_ptr());
        for(u32 i = 0; i < script.m_header.m_natives_count; i++)
            script.m_natives.push_back(rotl(stream.read<u64>(), script.m_header.code_size() + i));

        return script;
    }

    void YSC::read_blocks(Stream& stream, BlockMap& read_to, u64 base, u32 size)
    {
        std::vector<u64> ptrs;
        stream.seek(base);
        for(u32 i = 0; i < YSC::Header::block_count(size); i++)
            ptrs.push_back(YSC::Header::to_pointer(stream.read<u64>()));

        for(u32 i = 0; i < ptrs.size(); i++)
        {
            auto size_to_write = YSC::Header::block_size(i, size);
            auto& to = read_to[i];
            to.resize(size_to_write);
            stream.seek(ptrs[i]);
            stream.read(reinterpret_cast<u8*>(to.data()), size_to_write);
        }
    }

    void YSC::StringTable::calculate()
    {
        for(u32 block_index = 0; block_index < m_blocks.size(); ++block_index)
        {
            auto blk = m_blocks[block_index];
            auto ptr = blk.data();
            auto length = 0u;
            for(u32 string_index = 0; string_index < blk.size(); ++string_index)
            {
                if(ptr[string_index] == 0)
                {
                    m_string_indexes.push_back({block_index, string_index - length});
                    length = 0;
                }
                else
                {
                    length++;
                }
            }
        }
    }

    const char* YSC::StringTable::get(u32 index) const
    {
        auto str = m_string_indexes[index];
        return reinterpret_cast<const char*>(m_blocks.at(str.block_index).data() + str.string_index);
    }
}
