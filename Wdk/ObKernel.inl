#pragma once
#include "ObStruct.inl"
#include "RtlKernel.inl"


namespace wdk
{

    extern"C"
    {

        __declspec(selectany) UINT8 ObInfoMaskToOffset[UINT8(~UINT8(0u)) + 1u]{};
        inline auto ObInitInfoBlockOffsets() -> NTSTATUS
        {
            auto vVer = GetSystemVersion();
            if (vVer == SystemVersion::Unknown)
            {
                return STATUS_NOT_SUPPORTED;
            }

            for (auto vMask = 0u; vMask < _countof(ObInfoMaskToOffset); ++vMask)
            {
                auto vOffset = UINT8();

                if (vMask & ObInfoMask::ObInfoMaskCreatorInfo)
                {
                    vOffset += sizeof(OBJECT_HEADER_CREATOR_INFO);
                }
                if (vMask & ObInfoMask::ObInfoMaskNameInfo)
                {
                    vOffset += sizeof(OBJECT_HEADER_NAME_INFO);
                }
                if (vMask & ObInfoMask::ObInfoMaskHandleInfo)
                {
                    vOffset += sizeof(OBJECT_HEADER_HANDLE_INFO);
                }
                if (vMask & ObInfoMask::ObInfoMaskQuotaInfo)
                {
                    vOffset += sizeof(OBJECT_HEADER_QUOTA_INFO);
                }
                if (vMask & ObInfoMask::ObInfoMaskProcessInfo)
                {
                    vOffset += sizeof(OBJECT_HEADER_PROCESS_INFO);
                }

                if (vVer >= SystemVersion::Windows8)
                {
                    if (vMask & ObInfoMask::ObInfoMaskAuditInfo)
                    {
                        vOffset += sizeof(OBJECT_HEADER_AUDIT_INFO);
                    }
                }

                if (vVer >= SystemVersion::Windows10_1507 && vVer <= SystemVersion::Windows10_1511)
                {
                    if (vMask & ObInfoMask::ObInfoMaskHandleRevocationInfo)
                    {
                        vOffset += sizeof(OBJECT_HEADER_HANDLE_REVOCATION_INFO);
                    }
                }

                if (vVer >= SystemVersion::Windows10_1607)
                {
                    if (vMask & ObInfoMask::ObInfoMaskExtendedInfo)
                    {
                        vOffset += sizeof(OBJECT_HEADER_EXTENDED_INFO);
                    }
                }

                if (vVer >= SystemVersion::Windows7 && vVer <= SystemVersion::Windows7_SP1)
                {
                    if (vMask & ObInfoMask::ObInfoMaskPaddingInfoWin7x)
                    {
                        vOffset += sizeof(OBJECT_HEADER_PADDING_INFO);
                    }
                }

                if (vVer >= SystemVersion::Windows8 && vVer <= SystemVersion::Windows8_1)
                {
                    if (vMask & ObInfoMask::ObInfoMaskPaddingInfoWin8x)
                    {
                        vOffset += sizeof(OBJECT_HEADER_PADDING_INFO);
                    }
                }

                if (vVer >= SystemVersion::Windows10_1507)
                {
                    if (vMask & ObInfoMask::ObInfoMaskPaddingInfo)
                    {
                        vOffset += sizeof(OBJECT_HEADER_PADDING_INFO);
                    }
                }

                ObInfoMaskToOffset[vMask] = vOffset;
            }

            return STATUS_SUCCESS;
        }

        inline auto ObGetObjectHeader(PVOID aObject) -> POBJECT_HEADER
        {
            return CONTAINING_RECORD(aObject, OBJECT_HEADER, Body);
        }

        inline auto ObGetObjectHeaderInfo(PVOID aObject, ObInfoMask aMask)
            -> PVOID
        {
            auto vInfo = PVOID{};
            auto vHeader = ObGetObjectHeader(aObject);

            if (vHeader->InfoMask & aMask)
            {
                auto vMaxMask = (aMask | (aMask - 1));
                vInfo = (UINT8*)vHeader - ObInfoMaskToOffset[vHeader->InfoMask & vMaxMask];
            }
            return vInfo;
        }

        NTSTATUS NTAPI
            ObCreateObjectType(
                __in PUNICODE_STRING            aTypeName,
                __in POBJECT_TYPE_INITIALIZER   aObjectTypeInitializer,
                __in_opt PSECURITY_DESCRIPTOR   aSecurityDescriptor,
                __out POBJECT_TYPE *            aObjectType
            );

        NTSTATUS NTAPI
            ObCreateObject(
                __in KPROCESSOR_MODE ProbeMode,
                __in POBJECT_TYPE    ObjectType,
                __in POBJECT_ATTRIBUTES ObjectAttributes,
                __in KPROCESSOR_MODE OwnershipMode,
                __inout_opt  PVOID   ParseContext,
                __in ULONG           ObjectBodySize,
                __in ULONG           PagedPoolCharge,
                __in ULONG           NonPagedPoolCharge,
                __out PVOID *        Object
            );

        NTSTATUS NTAPI
            ObInsertObject(
                __in PVOID              Object,
                __in_opt PACCESS_STATE  PassedAccessState,
                __in_opt ACCESS_MASK    DesiredAccess,
                __in ULONG              ObjectPointerBias,
                __out_opt PVOID *       NewObject,
                __out_opt PHANDLE       Handle
            );

        NTSTATUS NTAPI
            ObOpenObjectByName(
                __in POBJECT_ATTRIBUTES ObjectAttributes,
                __in_opt POBJECT_TYPE ObjectType,
                __in KPROCESSOR_MODE AccessMode,
                __inout_opt PACCESS_STATE AccessState,
                __in_opt ACCESS_MASK DesiredAccess,
                __inout_opt PVOID ParseContext,
                __out PHANDLE Handle
            );

        NTSTATUS NTAPI
            ObOpenObjectByPointer(
                __in PVOID              aObject,
                __in ULONG              aHandleAttributes,
                __in_opt PACCESS_STATE  aPassedAccessState,
                __in ACCESS_MASK        aDesiredAccess,
                __in_opt POBJECT_TYPE   aObjectType,
                __in KPROCESSOR_MODE    aAccessMode,
                __out PHANDLE           aHandle
            );

        NTSTATUS NTAPI
            ObOpenObjectByPointerWithTag(
                __in PVOID              aObject,
                __in ULONG              aHandleAttributes,
                __in_opt PACCESS_STATE  aPassedAccessState,
                __in ACCESS_MASK        aDesiredAccess,
                __in_opt POBJECT_TYPE   aObjectType,
                __in KPROCESSOR_MODE    aAccessMode,
                __in ULONG              aTag,
                __out PHANDLE           aHandle
            );

        VOID NTAPI
            ObMakeTemporaryObject(
                __in PVOID Object
            );

        BOOLEAN NTAPI
            ObFindHandleForObject(
                __in PEPROCESS Process,
                __in PVOID Object,
                __in_opt POBJECT_TYPE ObjectType,
                __in_opt POBJECT_HANDLE_INFORMATION MatchCriteria,
                __out PHANDLE Handle
            );

        // begin win8
        BOOLEAN FASTCALL
            ObReferenceObjectSafe(
                _In_ PVOID Object
            );

        // begin win8
        BOOLEAN FASTCALL
            ObReferenceObjectSafeWithTag(
                _In_ PVOID Object,
                _In_ ULONG Tag
            );

        NTSTATUS NTAPI
            ObQueryNameString(
                _In_ PVOID Object,
                _Out_writes_bytes_opt_(Length) POBJECT_NAME_INFORMATION ObjectNameInfo,
                _In_ ULONG Length,
                _Out_ PULONG ReturnLength
            );

        BOOLEAN NTAPI
            ObIsKernelHandle(
                _In_ HANDLE Handle
            );

        struct _OBJECT_HEADER_NAME_INFO* NTAPI
            ObQueryNameInfo(
                _In_ PVOID Object
            );

    }
}

namespace wdk
{
    extern"C"
    {
        inline auto ObInitSystem() -> NTSTATUS
        {
            return ObInitInfoBlockOffsets();
        }
    }
}