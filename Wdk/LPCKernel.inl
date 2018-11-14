#pragma once
#include "LPCStruct.inl"


namespace wdk
{
    extern"C"
    {

        NTSTATUS  NTAPI
            LpcRequestPort(
                _In_ PVOID PortAddress,
                _In_ PPORT_MESSAGE RequestMessage
            );

        NTSTATUS NTAPI
            LpcRequestWaitReplyPort(
                _In_ PVOID PortAddress,
                _In_ PPORT_MESSAGE RequestMessage,
                _Out_ PPORT_MESSAGE ReplyMessage
            );

        NTSTATUS NTAPI
            LpcRequestWaitReplyPortEx(
                _In_  PVOID PortAddress,
                _In_  PPORT_MESSAGE RequestMessage,
                _Out_ PPORT_MESSAGE ReplyMessage
            );
    }
}


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
