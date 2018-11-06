#pragma once
#include "PsStruct.inl"


namespace wdk
{
    extern"C"
    {

        NTSTATUS NTAPI
            PsLookupProcessByProcessId(
                _In_ HANDLE ProcessId,
                _Outptr_ PEPROCESS *Process
            );

        NTSTATUS NTAPI
            PsLookupThreadByThreadId(
                _In_ HANDLE ThreadId,
                _Outptr_ PETHREAD *Thread
            );

        ULONG NTAPI
            PsGetCurrentProcessSessionId(VOID);

        NTSTATUS NTAPI
            PsAssignImpersonationToken(
                _In_ PETHREAD Thread,
                _In_opt_ HANDLE Token
            );

        PACCESS_TOKEN NTAPI
            PsReferencePrimaryToken(
                _Inout_ PEPROCESS Process
            );

        VOID NTAPI
            PsDereferencePrimaryToken(
                _In_ PACCESS_TOKEN PrimaryToken
            );

        VOID NTAPI
            PsDereferenceImpersonationToken(
                _In_ PACCESS_TOKEN ImpersonationToken
            );

        PACCESS_TOKEN NTAPI
            PsReferenceImpersonationToken(
                _Inout_ PETHREAD Thread,
                _Out_ PBOOLEAN CopyOnOpen,
                _Out_ PBOOLEAN EffectiveOnly,
                _Out_ PSECURITY_IMPERSONATION_LEVEL ImpersonationLevel
            );

        LARGE_INTEGER NTAPI
            PsGetProcessExitTime(VOID);

        NTSTATUS NTAPI
            PsImpersonateClient(
                _Inout_ PETHREAD Thread,
                _In_opt_ PACCESS_TOKEN Token,
                _In_ BOOLEAN CopyOnOpen,
                _In_ BOOLEAN EffectiveOnly,
                _In_ SECURITY_IMPERSONATION_LEVEL ImpersonationLevel
            );

        BOOLEAN NTAPI
            PsDisableImpersonation(
                _Inout_ PETHREAD Thread,
                _Inout_ PSE_IMPERSONATION_STATE ImpersonationState
            );

        VOID NTAPI
            PsRestoreImpersonation(
                _Inout_ PETHREAD Thread,
                _In_ PSE_IMPERSONATION_STATE ImpersonationState
            );

        VOID NTAPI
            PsRevertToSelf(
                VOID
            );

        PERESOURCE NTAPI
            PsGetJobLock(
                _In_ struct _EJOB* Job
            );

        ULONG NTAPI
            PsGetJobSessionId(
                _In_ struct _EJOB* Job
            );

        ULONG NTAPI
            PsGetJobUIRestrictionsClass(
                _In_ struct _EJOB* Job
            );

        LONGLONG NTAPI
            PsGetProcessCreateTimeQuadPart(
                _In_ PEPROCESS Process
            );

        PVOID NTAPI
            PsGetProcessDebugPort(
                _In_ PEPROCESS Process
            );

        BOOLEAN NTAPI
            PsIsProcessBeingDebugged(
                _In_ PEPROCESS Process
            );

        BOOLEAN NTAPI
            PsGetProcessExitProcessCalled(
                _In_ PEPROCESS Process
            );

        UCHAR * NTAPI
            PsGetProcessImageFileName(
                _In_ PEPROCESS Process
            );

#define PsGetCurrentProcessImageFileName() PsGetProcessImageFileName(PsGetCurrentProcess())

        HANDLE NTAPI
            PsGetProcessInheritedFromUniqueProcessId(
                _In_ PEPROCESS Process
            );

        struct _EJOB* NTAPI
            PsGetProcessJob(
                _In_ PEPROCESS Process
            );

        ULONG NTAPI
            PsGetProcessSessionId(
                _In_ PEPROCESS Process
            );

        // 区别在于 Ex 会返回 -1
        ULONG NTAPI
            PsGetProcessSessionIdEx(
                _In_ PEPROCESS Process
            );

        PVOID NTAPI
            PsGetProcessSectionBaseAddress(
                _In_ PEPROCESS Process
            );

#define PsGetProcessPcb(Process) ((PKPROCESS)(Process))

        struct _PEB* NTAPI
            PsGetProcessPeb(
                _In_ PEPROCESS Process
            );

        UCHAR NTAPI
            PsGetProcessPriorityClass(
                _In_ PEPROCESS Process
            );

        HANDLE NTAPI
            PsGetProcessWin32WindowStation(
                _In_ PEPROCESS Process
            );

#define PsGetCurrentProcessWin32WindowStation() PsGetProcessWin32WindowStation(PsGetCurrentProcess())

        PVOID NTAPI
            PsGetProcessWin32Process(
                _In_ PEPROCESS Process
            );

        PVOID NTAPI
            PsGetCurrentProcessWin32Process(
                VOID
            );

#ifdef _WIN64
        struct _PEB32* NTAPI
            PsGetProcessWow64Process(
                _In_ PEPROCESS Process
            );

        struct _PEB32* NTAPI
            PsGetCurrentProcessWow64Process(
                VOID
            );
#endif

        inline bool NTAPI 
            PsIsWow64Process(PEPROCESS aProcess)
        {
#ifdef _WIN64
            return !!PsGetProcessWow64Process(aProcess);
#else
            aProcess;
            return false;
#endif
        }

        BOOLEAN NTAPI
            PsIsSystemProcess(
                _In_ PEPROCESS Process
            );

        NTSTATUS NTAPI
            PsReferenceProcessFilePointer(
                _In_ PEPROCESS Process,
                _Out_ PFILE_OBJECT *pFilePointer
            );

        VOID NTAPI
            PsSetJobUIRestrictionsClass(
                _Out_ struct _EJOB* Job,
                _In_ ULONG UIRestrictionsClass
            );

        VOID NTAPI
            PsSetProcessPriorityClass(
                _Out_ PEPROCESS Process,
                _In_ UCHAR PriorityClass
            );

        NTSTATUS NTAPI
            PsSetProcessWin32Process(
                _In_ PEPROCESS Process,
                _In_ PVOID Win32Process,
                _In_ PVOID PrevWin32Process
            );

        VOID NTAPI
            PsSetProcessWindowStation(
                _Out_ PEPROCESS Process,
                _In_ HANDLE Win32WindowStation
            );

        PVOID NTAPI
            PsGetProcessSecurityPort(
                _In_ PEPROCESS Process
            );

        NTSTATUS NTAPI
            PsSuspendProcess(
                _In_ PEPROCESS Process
            );

        NTSTATUS NTAPI
            PsResumeProcess(
                _In_ PEPROCESS Process
            );

        VOID NTAPI
            PsChargePoolQuota(
                _In_ PEPROCESS Process,
                _In_ POOL_TYPE PoolType,
                _In_ ULONG_PTR Amount
            );

        NTSTATUS NTAPI
            PsChargeProcessPoolQuota(
                _In_ PEPROCESS Process,
                _In_ POOL_TYPE PoolType,
                _In_ ULONG_PTR Amount
            );

        VOID NTAPI
            PsReturnPoolQuota(
                _In_ PEPROCESS Process,
                _In_ POOL_TYPE PoolType,
                _In_ ULONG_PTR Amount
            );

        VOID NTAPI
            PsUpdateDiskCounters(
                _Inout_ PEPROCESS Process,
                _In_ ULONG64 BytesRead,
                _In_ ULONG64 BytesWritten,
                _In_ ULONG ReadOperationCount,
                _In_ ULONG WriteOperationCount,
                _In_ ULONG FlushOperationCount
            );

        BOOLEAN NTAPI
            PsIsDiskCountersEnabled(
                VOID
            );

    }
}

namespace wdk
{
    extern"C"
    {

        constexpr inline auto PsProtectedValue(PS_PROTECTED_SIGNER aSigner, BOOLEAN aAudit, PS_PROTECTED_TYPE aType)
            -> PS_PROTECTION
        {
            return 
            { 
                (UINT8)(
                    ((aSigner << 4) & PsProtectedSignerMask) | 
                    ((aAudit  << 3) & PsProtectedAuditMask ) |
                    ((aType   << 0) & PsProtectedTypeMask  ))
            };
        }

        inline auto InitializePsProtection(PS_PROTECTION* aValue, PS_PROTECTED_SIGNER aSigner, BOOLEAN aAudit, PS_PROTECTED_TYPE aType)
            -> PS_PROTECTION*
        {
            aValue->Signer  = aSigner;
            aValue->Audit   = aAudit;
            aValue->Type    = aType;

            return aValue;
        }
        

        inline auto PsInitSystem() -> NTSTATUS
        {
            return STATUS_SUCCESS;
        }
    }
}
