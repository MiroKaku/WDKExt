#pragma once
#include "WmiStruct.inl"


namespace wdk
{

    extern"C"
    {

        LONG64 FASTCALL
            WmiGetClock(
                _In_ WMI_CLOCK_TYPE ClockType,
                _In_ PVOID Context
            );

    }
}

namespace wdk
{
    extern"C"
    {
        inline auto WmiInitSystem() -> NTSTATUS
        {
            return STATUS_SUCCESS;
        }
    }
}
