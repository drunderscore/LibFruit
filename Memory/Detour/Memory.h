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
