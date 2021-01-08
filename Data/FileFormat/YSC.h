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

// YSC is the Rage engine script format. Used in GTA IV, V, and RDR and 2.
// Reference used: https://gtamods.com/wiki/Script_Container

#pragma once
#include <optional>
#include <map>
#include <vector>
#include "Types.h"
#include "Data/Stream.h"

namespace LibFruit::FileFormat
{
    // TODO: Statics, globals, start parameters
    class YSC
    {
    public:
        using BlockMap = std::map<u32, std::vector<u8>>;
        class Header
        {
        public:
            static constexpr u64 MAGIC = 0x1405A9ED0;
            friend class YSC;
            u32 page_map_ptr() { return to_pointer(m_page_map_pointer); }
            u32 code_blocks_ptr() { return to_pointer(m_code_blocks_base_pointer); }
            u32 statics_ptr() { return to_pointer(m_statics_pointer); }
            u32 globals_ptr() { return to_pointer(m_globals_pointer); }
            u32 natives_ptr() { return to_pointer(m_natives_pointer); }
            u32 script_name_ptr() { return to_pointer(m_script_name_pointer); }
            u32 string_blocks_ptr() { return to_pointer(m_string_blocks_base_pointer); }

            u32 code_size() { return m_code_size; }
            u32 string_size() { return m_string_size; }

            u32 code_block_count() { return block_count(m_code_size); }
            u32 string_block_count() { return block_count(m_string_size); }

        private:
            u64 m_magic;
            u64 m_page_map_pointer;
            u64 m_code_blocks_base_pointer;
            u32 m_globals_signature;
            u32 m_code_size;
            u32 m_parameter_count;
            u32 m_static_count;
            u32 m_global_count;
            u32 m_natives_count;
            u64 m_statics_pointer;
            u64 m_globals_pointer;
            u64 m_natives_pointer;
            u64 m_null1;
            u64 m_null2;
            u32 m_script_name_hash;
            u32 m_unk_usually_1;
            u64 m_script_name_pointer;
            u64 m_string_blocks_base_pointer;
            u32 m_string_size;
            u32 m_null3;
            u32 m_null4;
            u32 m_null5;

            // This is a pointer into the file itself, so it should be 32-bit
            static inline u32 to_pointer(u64 val)
            {
                return val & 0xFFFFFF;
            }

            static inline u32 block_count(u32 size)
            {
                return (size + 0x3FFF) >> 14;
            }

            static inline u32 block_size(u32 index, u32 total)
            {
                if(index > total >> 14)
                    return 0;

                if(index == total >> 14)
                    return total & 0x3FFF;

                return 0x4000;
            }
        };

        class StringTable
        {
        public:
            friend class YSC;
            const size_t size() const { return m_string_indexes.size(); }
            const char* get(u32 index) const;
        private:
            struct String
            {
                String(u32 blk_idx, u32 str_idx) : block_index(blk_idx), string_index(str_idx) {}

                u32 block_index;
                u32 string_index;
            };

            BlockMap m_blocks;
            std::vector<String> m_string_indexes;
            StringTable() {}
            void calculate();
        };

        const StringTable& strings() const { return m_strings; }
        const BlockMap& code_blocks() const { return m_code_blocks; }
        const std::string& script_name() const { return m_script_name; }
        const std::vector<u64> natives() const { return m_natives; }

        static std::optional<YSC> parse(std::istream&);

    private:
        Header m_header;
        BlockMap m_code_blocks;
        std::string m_script_name;
        StringTable m_strings;
        std::vector<u64> m_natives;

        YSC() {}
        static void read_blocks(Stream& stream, BlockMap& read_to, u32 base, u32 size);
        static inline u64 rotl(u64 val, u32 rotate)
        {
            rotate %= 64;
            return val << rotate | val >> ( 64 - rotate );
        }
    };
}
