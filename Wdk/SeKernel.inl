#pragma once
#include "SeMacro.inl"
#include "SeStruct.inl"


namespace wdk
{
    extern"C"
    {
        extern PACL SeSystemDefaultDacl;

        NTSTATUS NTAPI
            SeLocateProcessImageName(
                _Inout_ PEPROCESS Process,
                _Outptr_ PUNICODE_STRING *pImageFileName
            );

        SECURITY_IMPERSONATION_LEVEL NTAPI
            SeTokenImpersonationLevel(
                __in PACCESS_TOKEN Token
            );

        TOKEN_TYPE NTAPI
            SeTokenType(
                _In_ PACCESS_TOKEN Token
            );

        BOOLEAN NTAPI
            SeTokenIsAdmin(
                _In_ PACCESS_TOKEN Token
            );

        BOOLEAN NTAPI
            SeTokenIsRestricted(
                _In_ PACCESS_TOKEN Token
            );
    }
}

namespace wdk
{
    extern"C"
    {
        inline auto SeInitSystem() -> NTSTATUS
        {
            return STATUS_SUCCESS;
        }
    }
}
