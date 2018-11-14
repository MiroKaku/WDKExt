#pragma once
#include "DbgStruct.inl"


namespace wdk
{
    extern"C"
    {
        inline auto DbgInitSystem() -> NTSTATUS
        {
            return STATUS_SUCCESS;
        }
    }
}
