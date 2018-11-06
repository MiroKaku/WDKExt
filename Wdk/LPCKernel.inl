#pragma once
#include "LPCStruct.inl"


namespace wdk
{

    extern"C"
    {

        inline auto LPCInitSystem() -> NTSTATUS
        {
            return STATUS_SUCCESS;
        }
    }
}
