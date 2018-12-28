#pragma once
#include "ObStruct.inl"
#include "RtlKernel.inl"


namespace wdk
{

    extern"C"
    {

        NTSTATUS NTAPI
            ObCreateObjectType(
                _In_ PUNICODE_STRING            aTypeName,
                _In_ POBJECT_TYPE_INITIALIZER   aObjectTypeInitializer,
                _In_opt_ PSECURITY_DESCRIPTOR   aSecurityDescriptor,
                _Out_ POBJECT_TYPE *            aObjectType
            );

        NTSTATUS NTAPI
            ObCreateObject(
                _In_ KPROCESSOR_MODE ProbeMode,
                _In_ POBJECT_TYPE    ObjectType,
                _In_ POBJECT_ATTRIBUTES ObjectAttributes,
                _In_ KPROCESSOR_MODE OwnershipMode,
                _Inout_opt_  PVOID   ParseContext,
                _In_ ULONG           ObjectBodySize,
                _In_ ULONG           PagedPoolCharge,
                _In_ ULONG           NonPagedPoolCharge,
                _Out_ PVOID *        Object
            );

        NTSTATUS NTAPI
            ObInsertObject(
                _In_ PVOID              Object,
                _In_opt_ PACCESS_STATE  PassedAccessState,
                _In_opt_ ACCESS_MASK    DesiredAccess,
                _In_ ULONG              ObjectPointerBias,
                _Out_opt_ PVOID *       NewObject,
                _Out_opt_ PHANDLE       Handle
            );

        NTSTATUS NTAPI
            ObOpenObjectByName(
                _In_ POBJECT_ATTRIBUTES ObjectAttributes,
                _In_opt_ POBJECT_TYPE ObjectType,
                _In_ KPROCESSOR_MODE AccessMode,
                _Inout_opt_ PACCESS_STATE AccessState,
                _In_opt_ ACCESS_MASK DesiredAccess,
                _Inout_opt_ PVOID ParseContext,
                _Out_ PHANDLE Handle
            );

        NTSTATUS NTAPI
            ObOpenObjectByPointer(
                _In_ PVOID              aObject,
                _In_ ULONG              aHandleAttributes,
                _In_opt_ PACCESS_STATE  aPassedAccessState,
                _In_ ACCESS_MASK        aDesiredAccess,
                _In_opt_ POBJECT_TYPE   aObjectType,
                _In_ KPROCESSOR_MODE    aAccessMode,
                _Out_ PHANDLE           aHandle
            );

        NTSTATUS NTAPI
            ObOpenObjectByPointerWithTag(
                _In_ PVOID              aObject,
                _In_ ULONG              aHandleAttributes,
                _In_opt_ PACCESS_STATE  aPassedAccessState,
                _In_ ACCESS_MASK        aDesiredAccess,
                _In_opt_ POBJECT_TYPE   aObjectType,
                _In_ KPROCESSOR_MODE    aAccessMode,
                _In_ ULONG              aTag,
                _Out_ PHANDLE           aHandle
            );

        VOID NTAPI
            ObMakeTemporaryObject(
                _In_ PVOID Object
            );

        BOOLEAN NTAPI
            ObFindHandleForObject(
                _In_ PEPROCESS Process,
                _In_ PVOID Object,
                _In_opt_ POBJECT_TYPE ObjectType,
                _In_opt_ POBJECT_HANDLE_INFORMATION MatchCriteria,
                _Out_ PHANDLE Handle
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
            ObReferenceObjectByName(
                _In_ PUNICODE_STRING ObjectName,
                _In_ ULONG Attributes,
                _In_opt_ PACCESS_STATE AccessState,
                _In_opt_ ACCESS_MASK DesiredAccess,
                _In_ POBJECT_TYPE ObjectType,
                _In_ KPROCESSOR_MODE AccessMode,
                _Inout_opt_ PVOID ParseContext,
                _Out_ PVOID *Object
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

        POBJECT_TYPE NTAPI
            ObGetObjectType(
                _In_ PVOID Object
            );

        NTSTATUS NTAPI
            ObDuplicateObject(
                _In_ PEPROCESS SourceProcess,
                _In_ HANDLE SourceHandle,
                _In_opt_ PEPROCESS TargetProcess,
                _Out_opt_ PHANDLE TargetHandle,
                _In_ ACCESS_MASK DesiredAccess,
                _In_ ULONG HandleAttributes,
                _In_ ULONG Options,
                _In_ KPROCESSOR_MODE PreviousMode
            );
    }
}

namespace wdk
{
    extern"C"
    {
        inline auto ObMakeKernelHandle(HANDLE aHandle) -> HANDLE
        {
#ifdef _X86_
#define KERNEL_HANDLE_BIT (0x80000000)
#else
#define KERNEL_HANDLE_BIT (0xffffffff80000000)
#endif

            return ((HANDLE)((ULONG_PTR)(aHandle) | KERNEL_HANDLE_BIT));
        }

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


        __declspec(selectany) POBJECT_TYPE  _ObTypeObjectType   = nullptr;
        __declspec(selectany) POBJECT_TYPE * ObTypeObjectType   = &_ObTypeObjectType;


        inline auto ObInitSystem() -> NTSTATUS
        {
            auto vStatus = STATUS_SUCCESS;

            for (;;)
            {
                vStatus = ObInitInfoBlockOffsets();
                if (!NT_SUCCESS(vStatus))
                {
                    break;
                }

                _ObTypeObjectType = ObGetObjectType(*PsProcessType);
                break;
            }

            return vStatus;
        }
    }
}