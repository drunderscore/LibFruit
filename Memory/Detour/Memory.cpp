#include "Memory.h"
#include "subhook/subhook.h"

namespace LibFruit::Detour
{
    Memory::Memory(void* src, void* detour, bool enable_now)
    {
        m_hook = subhook_new(src, detour, static_cast<subhook_flags_t>(0));
        if(enable_now)
            enable();
    }

    void Memory::enable()
    {
        subhook_install(m_hook);
    }

    void Memory::disable()
    {
        subhook_remove(m_hook);
    }

    void* Memory::original()
    {
        return subhook_get_trampoline(m_hook);
    }

    bool Memory::is_enabled()
    {
        return subhook_is_installed(m_hook);
    }

    Memory::~Memory()
    {
        disable();
        subhook_free(m_hook);
    }
}
