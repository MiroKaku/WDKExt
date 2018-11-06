#pragma once
#include "CmStruct.inl"


namespace wdk
{
    extern"C"
    {

    }
}

namespace wdk
{
    extern"C"
    {
        inline auto CmInitSystem() -> NTSTATUS
        {
            return STATUS_SUCCESS;
        }
    }
}
