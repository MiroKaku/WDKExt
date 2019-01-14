#pragma once
#include "PsStruct.inl"
#include "TsKernel.inl"


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
        

        inline auto PsGetProcessRundownProtect(PEPROCESS aProcess)
            -> PEX_RUNDOWN_REF
        {
            auto vRundownProtect = PEX_RUNDOWN_REF();

            switch (GetSystemVersion())
            {
            default:
                break;
            case wdk::SystemVersion::Windows7:
                vRundownProtect = &reinterpret_cast<wdk::build_7600::PEPROCESS>(aProcess)->RundownProtect;
                break;
            case wdk::SystemVersion::Windows7_SP1:
                vRundownProtect = &reinterpret_cast<wdk::build_7601::PEPROCESS>(aProcess)->RundownProtect;
                break;
            case wdk::SystemVersion::Windows8:
                vRundownProtect = &reinterpret_cast<wdk::build_9200::PEPROCESS>(aProcess)->RundownProtect;
                break;
            case wdk::SystemVersion::Windows8_1:
                vRundownProtect = &reinterpret_cast<wdk::build_9600::PEPROCESS>(aProcess)->RundownProtect;
                break;
            case wdk::SystemVersion::Windows10_1507:
                vRundownProtect = &reinterpret_cast<wdk::build_10240::PEPROCESS>(aProcess)->RundownProtect;
                break;
            case wdk::SystemVersion::Windows10_1511:
                vRundownProtect = &reinterpret_cast<wdk::build_10586::PEPROCESS>(aProcess)->RundownProtect;
                break;
            case wdk::SystemVersion::Windows10_1607:
                vRundownProtect = &reinterpret_cast<wdk::build_14393::PEPROCESS>(aProcess)->RundownProtect;
                break;
            case wdk::SystemVersion::Windows10_1703:
                vRundownProtect = &reinterpret_cast<wdk::build_15063::PEPROCESS>(aProcess)->RundownProtect;
                break;
            case wdk::SystemVersion::Windows10_1709:
                vRundownProtect = &reinterpret_cast<wdk::build_16299::PEPROCESS>(aProcess)->RundownProtect;
                break;
            case wdk::SystemVersion::Windows10_1803:
                vRundownProtect = &reinterpret_cast<wdk::build_17134::PEPROCESS>(aProcess)->RundownProtect;
                break;
            case wdk::SystemVersion::Windows10_1809:
                vRundownProtect = &reinterpret_cast<wdk::build_17763::PEPROCESS>(aProcess)->RundownProtect;
                break;
            }

            return vRundownProtect;
        }


        inline auto PsGetProcessSectionObject(PEPROCESS aProcess)
            -> PVOID
        {
            auto vSectionObject = PVOID();

            switch (GetSystemVersion())
            {
            default:
                break;
            case wdk::SystemVersion::Windows7:
                vSectionObject = reinterpret_cast<wdk::build_7600::PEPROCESS>(aProcess)->SectionObject;
                break;
            case wdk::SystemVersion::Windows7_SP1:
                vSectionObject = reinterpret_cast<wdk::build_7601::PEPROCESS>(aProcess)->SectionObject;
                break;
            case wdk::SystemVersion::Windows8:
                vSectionObject = reinterpret_cast<wdk::build_9200::PEPROCESS>(aProcess)->SectionObject;
                break;
            case wdk::SystemVersion::Windows8_1:
                vSectionObject = reinterpret_cast<wdk::build_9600::PEPROCESS>(aProcess)->SectionObject;
                break;
            case wdk::SystemVersion::Windows10_1507:
                vSectionObject = reinterpret_cast<wdk::build_10240::PEPROCESS>(aProcess)->SectionObject;
                break;
            case wdk::SystemVersion::Windows10_1511:
                vSectionObject = reinterpret_cast<wdk::build_10586::PEPROCESS>(aProcess)->SectionObject;
                break;
            case wdk::SystemVersion::Windows10_1607:
                vSectionObject = reinterpret_cast<wdk::build_14393::PEPROCESS>(aProcess)->SectionObject;
                break;
            case wdk::SystemVersion::Windows10_1703:
                vSectionObject = reinterpret_cast<wdk::build_15063::PEPROCESS>(aProcess)->SectionObject;
                break;
            case wdk::SystemVersion::Windows10_1709:
                vSectionObject = reinterpret_cast<wdk::build_16299::PEPROCESS>(aProcess)->SectionObject;
                break;
            case wdk::SystemVersion::Windows10_1803:
                vSectionObject = reinterpret_cast<wdk::build_17134::PEPROCESS>(aProcess)->SectionObject;
                break;
            case wdk::SystemVersion::Windows10_1809:
                vSectionObject = reinterpret_cast<wdk::build_17763::PEPROCESS>(aProcess)->SectionObject;
                break;
            }

            return vSectionObject;
        }


        inline auto PsGetProcessFlags(PEPROCESS aProcess)
            -> UINT32
        {
            auto vFlags = UINT32();

            switch (GetSystemVersion())
            {
            default:
                break;
            case wdk::SystemVersion::Windows7:
                vFlags = reinterpret_cast<wdk::build_7600::PEPROCESS>(aProcess)->Flags;
                break;
            case wdk::SystemVersion::Windows7_SP1:
                vFlags = reinterpret_cast<wdk::build_7601::PEPROCESS>(aProcess)->Flags;
                break;
            case wdk::SystemVersion::Windows8:
                vFlags = reinterpret_cast<wdk::build_9200::PEPROCESS>(aProcess)->Flags;
                break;
            case wdk::SystemVersion::Windows8_1:
                vFlags = reinterpret_cast<wdk::build_9600::PEPROCESS>(aProcess)->Flags;
                break;
            case wdk::SystemVersion::Windows10_1507:
                vFlags = reinterpret_cast<wdk::build_10240::PEPROCESS>(aProcess)->Flags;
                break;
            case wdk::SystemVersion::Windows10_1511:
                vFlags = reinterpret_cast<wdk::build_10586::PEPROCESS>(aProcess)->Flags;
                break;
            case wdk::SystemVersion::Windows10_1607:
                vFlags = reinterpret_cast<wdk::build_14393::PEPROCESS>(aProcess)->Flags;
                break;
            case wdk::SystemVersion::Windows10_1703:
                vFlags = reinterpret_cast<wdk::build_15063::PEPROCESS>(aProcess)->Flags;
                break;
            case wdk::SystemVersion::Windows10_1709:
                vFlags = reinterpret_cast<wdk::build_16299::PEPROCESS>(aProcess)->Flags;
                break;
            case wdk::SystemVersion::Windows10_1803:
                vFlags = reinterpret_cast<wdk::build_17134::PEPROCESS>(aProcess)->Flags;
                break;
            case wdk::SystemVersion::Windows10_1809:
                vFlags = reinterpret_cast<wdk::build_17763::PEPROCESS>(aProcess)->Flags;
                break;
            }

            return vFlags;
        }


        inline auto PsSetProcessFlags(PEPROCESS aProcess, UINT32 aFlags)
            -> UINT32
        {
            auto vFlags = (UINT32*)(nullptr);

            switch (GetSystemVersion())
            {
            default:
                break;
            case wdk::SystemVersion::Windows7:
                vFlags = &reinterpret_cast<wdk::build_7600::PEPROCESS>(aProcess)->Flags;
                break;
            case wdk::SystemVersion::Windows7_SP1:
                vFlags = &reinterpret_cast<wdk::build_7601::PEPROCESS>(aProcess)->Flags;
                break;
            case wdk::SystemVersion::Windows8:
                vFlags = &reinterpret_cast<wdk::build_9200::PEPROCESS>(aProcess)->Flags;
                break;
            case wdk::SystemVersion::Windows8_1:
                vFlags = &reinterpret_cast<wdk::build_9600::PEPROCESS>(aProcess)->Flags;
                break;
            case wdk::SystemVersion::Windows10_1507:
                vFlags = &reinterpret_cast<wdk::build_10240::PEPROCESS>(aProcess)->Flags;
                break;
            case wdk::SystemVersion::Windows10_1511:
                vFlags = &reinterpret_cast<wdk::build_10586::PEPROCESS>(aProcess)->Flags;
                break;
            case wdk::SystemVersion::Windows10_1607:
                vFlags = &reinterpret_cast<wdk::build_14393::PEPROCESS>(aProcess)->Flags;
                break;
            case wdk::SystemVersion::Windows10_1703:
                vFlags = &reinterpret_cast<wdk::build_15063::PEPROCESS>(aProcess)->Flags;
                break;
            case wdk::SystemVersion::Windows10_1709:
                vFlags = &reinterpret_cast<wdk::build_16299::PEPROCESS>(aProcess)->Flags;
                break;
            case wdk::SystemVersion::Windows10_1803:
                vFlags = &reinterpret_cast<wdk::build_17134::PEPROCESS>(aProcess)->Flags;
                break;
            case wdk::SystemVersion::Windows10_1809:
                vFlags = &reinterpret_cast<wdk::build_17763::PEPROCESS>(aProcess)->Flags;
                break;
            }

            if (vFlags)
            {
                return RtlInterlockedSetBits(vFlags, aFlags);
            }

            return 0;
        }
        

        inline auto PsClearProcessFlags(PEPROCESS aProcess, UINT32 aFlags)
            -> UINT32
        {
            auto vFlags = (UINT32*)(nullptr);

            switch (GetSystemVersion())
            {
            default:
                break;
            case wdk::SystemVersion::Windows7:
                vFlags = &reinterpret_cast<wdk::build_7600::PEPROCESS>(aProcess)->Flags;
                break;
            case wdk::SystemVersion::Windows7_SP1:
                vFlags = &reinterpret_cast<wdk::build_7601::PEPROCESS>(aProcess)->Flags;
                break;
            case wdk::SystemVersion::Windows8:
                vFlags = &reinterpret_cast<wdk::build_9200::PEPROCESS>(aProcess)->Flags;
                break;
            case wdk::SystemVersion::Windows8_1:
                vFlags = &reinterpret_cast<wdk::build_9600::PEPROCESS>(aProcess)->Flags;
                break;
            case wdk::SystemVersion::Windows10_1507:
                vFlags = &reinterpret_cast<wdk::build_10240::PEPROCESS>(aProcess)->Flags;
                break;
            case wdk::SystemVersion::Windows10_1511:
                vFlags = &reinterpret_cast<wdk::build_10586::PEPROCESS>(aProcess)->Flags;
                break;
            case wdk::SystemVersion::Windows10_1607:
                vFlags = &reinterpret_cast<wdk::build_14393::PEPROCESS>(aProcess)->Flags;
                break;
            case wdk::SystemVersion::Windows10_1703:
                vFlags = &reinterpret_cast<wdk::build_15063::PEPROCESS>(aProcess)->Flags;
                break;
            case wdk::SystemVersion::Windows10_1709:
                vFlags = &reinterpret_cast<wdk::build_16299::PEPROCESS>(aProcess)->Flags;
                break;
            case wdk::SystemVersion::Windows10_1803:
                vFlags = &reinterpret_cast<wdk::build_17134::PEPROCESS>(aProcess)->Flags;
                break;
            case wdk::SystemVersion::Windows10_1809:
                vFlags = &reinterpret_cast<wdk::build_17763::PEPROCESS>(aProcess)->Flags;
                break;
            }

            if (vFlags)
            {
                return RtlInterlockedClearBits(vFlags, aFlags);
            }

            return 0;
        }


        inline auto PsSetProcessExitTime(PEPROCESS aProcess)
            -> VOID
        {
            auto vExitTime = (PLARGE_INTEGER)(nullptr);

            switch (GetSystemVersion())
            {
            default:
                break;
            case wdk::SystemVersion::Windows7:
                vExitTime = &reinterpret_cast<wdk::build_7600::PEPROCESS>(aProcess)->ExitTime;
                break;
            case wdk::SystemVersion::Windows7_SP1:
                vExitTime = &reinterpret_cast<wdk::build_7601::PEPROCESS>(aProcess)->ExitTime;
                break;
            case wdk::SystemVersion::Windows8:
                vExitTime = &reinterpret_cast<wdk::build_9200::PEPROCESS>(aProcess)->ExitTime;
                break;
            case wdk::SystemVersion::Windows8_1:
                vExitTime = &reinterpret_cast<wdk::build_9600::PEPROCESS>(aProcess)->ExitTime;
                break;
            case wdk::SystemVersion::Windows10_1507:
                vExitTime = &reinterpret_cast<wdk::build_10240::PEPROCESS>(aProcess)->ExitTime;
                break;
            case wdk::SystemVersion::Windows10_1511:
                vExitTime = &reinterpret_cast<wdk::build_10586::PEPROCESS>(aProcess)->ExitTime;
                break;
            case wdk::SystemVersion::Windows10_1607:
                vExitTime = &reinterpret_cast<wdk::build_14393::PEPROCESS>(aProcess)->ExitTime;
                break;
            case wdk::SystemVersion::Windows10_1703:
                vExitTime = &reinterpret_cast<wdk::build_15063::PEPROCESS>(aProcess)->ExitTime;
                break;
            case wdk::SystemVersion::Windows10_1709:
                vExitTime = &reinterpret_cast<wdk::build_16299::PEPROCESS>(aProcess)->ExitTime;
                break;
            case wdk::SystemVersion::Windows10_1803:
                vExitTime = &reinterpret_cast<wdk::build_17134::PEPROCESS>(aProcess)->ExitTime;
                break;
            case wdk::SystemVersion::Windows10_1809:
                vExitTime = &reinterpret_cast<wdk::build_17763::PEPROCESS>(aProcess)->ExitTime;
                break;
            }

            if (vExitTime)
            {
                KeQuerySystemTime(vExitTime);
            }
        }


        inline auto PsGetProcessActiveThreads(PEPROCESS aProcess)
            -> INT32
        {
            auto vActiveThreads = INT32();
            
            switch (GetSystemVersion())
            {
            default:
                break;
            case wdk::SystemVersion::Windows7:
                vActiveThreads = reinterpret_cast<wdk::build_7600::PEPROCESS>(aProcess)->ActiveThreads;
                break;
            case wdk::SystemVersion::Windows7_SP1:
                vActiveThreads = reinterpret_cast<wdk::build_7601::PEPROCESS>(aProcess)->ActiveThreads;
                break;
            case wdk::SystemVersion::Windows8:
                vActiveThreads = reinterpret_cast<wdk::build_9200::PEPROCESS>(aProcess)->ActiveThreads;
                break;
            case wdk::SystemVersion::Windows8_1:
                vActiveThreads = reinterpret_cast<wdk::build_9600::PEPROCESS>(aProcess)->ActiveThreads;
                break;
            case wdk::SystemVersion::Windows10_1507:
                vActiveThreads = reinterpret_cast<wdk::build_10240::PEPROCESS>(aProcess)->ActiveThreads;
                break;
            case wdk::SystemVersion::Windows10_1511:
                vActiveThreads = reinterpret_cast<wdk::build_10586::PEPROCESS>(aProcess)->ActiveThreads;
                break;
            case wdk::SystemVersion::Windows10_1607:
                vActiveThreads = reinterpret_cast<wdk::build_14393::PEPROCESS>(aProcess)->ActiveThreads;
                break;
            case wdk::SystemVersion::Windows10_1703:
                vActiveThreads = reinterpret_cast<wdk::build_15063::PEPROCESS>(aProcess)->ActiveThreads;
                break;
            case wdk::SystemVersion::Windows10_1709:
                vActiveThreads = reinterpret_cast<wdk::build_16299::PEPROCESS>(aProcess)->ActiveThreads;
                break;
            case wdk::SystemVersion::Windows10_1803:
                vActiveThreads = reinterpret_cast<wdk::build_17134::PEPROCESS>(aProcess)->ActiveThreads;
                break;
            case wdk::SystemVersion::Windows10_1809:
                vActiveThreads = reinterpret_cast<wdk::build_17763::PEPROCESS>(aProcess)->ActiveThreads;
                break;
            }

            return vActiveThreads;
        }


        inline auto PsGetProcessLastThreadExitStatus(PEPROCESS aProcess)
            -> NTSTATUS
        {
            auto vExitStatus = NTSTATUS();

            switch (GetSystemVersion())
            {
            default:
                break;
            case wdk::SystemVersion::Windows7:
                vExitStatus = reinterpret_cast<wdk::build_7600::PEPROCESS>(aProcess)->LastThreadExitStatus;
                break;
            case wdk::SystemVersion::Windows7_SP1:
                vExitStatus = reinterpret_cast<wdk::build_7601::PEPROCESS>(aProcess)->LastThreadExitStatus;
                break;
            case wdk::SystemVersion::Windows8:
                vExitStatus = reinterpret_cast<wdk::build_9200::PEPROCESS>(aProcess)->LastThreadExitStatus;
                break;
            case wdk::SystemVersion::Windows8_1:
                vExitStatus = reinterpret_cast<wdk::build_9600::PEPROCESS>(aProcess)->LastThreadExitStatus;
                break;
            case wdk::SystemVersion::Windows10_1507:
                vExitStatus = reinterpret_cast<wdk::build_10240::PEPROCESS>(aProcess)->LastThreadExitStatus;
                break;
            case wdk::SystemVersion::Windows10_1511:
                vExitStatus = reinterpret_cast<wdk::build_10586::PEPROCESS>(aProcess)->LastThreadExitStatus;
                break;
            case wdk::SystemVersion::Windows10_1607:
                vExitStatus = reinterpret_cast<wdk::build_14393::PEPROCESS>(aProcess)->LastThreadExitStatus;
                break;
            case wdk::SystemVersion::Windows10_1703:
                vExitStatus = reinterpret_cast<wdk::build_15063::PEPROCESS>(aProcess)->LastThreadExitStatus;
                break;
            case wdk::SystemVersion::Windows10_1709:
                vExitStatus = reinterpret_cast<wdk::build_16299::PEPROCESS>(aProcess)->LastThreadExitStatus;
                break;
            case wdk::SystemVersion::Windows10_1803:
                vExitStatus = reinterpret_cast<wdk::build_17134::PEPROCESS>(aProcess)->LastThreadExitStatus;
                break;
            case wdk::SystemVersion::Windows10_1809:
                vExitStatus = reinterpret_cast<wdk::build_17763::PEPROCESS>(aProcess)->LastThreadExitStatus;
                break;
            }

            return vExitStatus;
        }


        inline auto PsSetProcessDebugPort(PEPROCESS aProcess, PVOID aDebugPort)
            -> NTSTATUS
        {
            void** vDebugPort = nullptr;

            switch (GetSystemVersion())
            {
            default:
                break;
            case wdk::SystemVersion::Windows7:
                vDebugPort = &reinterpret_cast<wdk::build_7600::PEPROCESS>(aProcess)->DebugPort;
                break;
            case wdk::SystemVersion::Windows7_SP1:
                vDebugPort = &reinterpret_cast<wdk::build_7601::PEPROCESS>(aProcess)->DebugPort;
                break;
            case wdk::SystemVersion::Windows8:
                vDebugPort = &reinterpret_cast<wdk::build_9200::PEPROCESS>(aProcess)->DebugPort;
                break;
            case wdk::SystemVersion::Windows8_1:
                vDebugPort = &reinterpret_cast<wdk::build_9600::PEPROCESS>(aProcess)->DebugPort;
                break;
            case wdk::SystemVersion::Windows10_1507:
                vDebugPort = &reinterpret_cast<wdk::build_10240::PEPROCESS>(aProcess)->DebugPort;
                break;
            case wdk::SystemVersion::Windows10_1511:
                vDebugPort = &reinterpret_cast<wdk::build_10586::PEPROCESS>(aProcess)->DebugPort;
                break;
            case wdk::SystemVersion::Windows10_1607:
                vDebugPort = &reinterpret_cast<wdk::build_14393::PEPROCESS>(aProcess)->DebugPort;
                break;
            case wdk::SystemVersion::Windows10_1703:
                vDebugPort = &reinterpret_cast<wdk::build_15063::PEPROCESS>(aProcess)->DebugPort;
                break;
            case wdk::SystemVersion::Windows10_1709:
                vDebugPort = &reinterpret_cast<wdk::build_16299::PEPROCESS>(aProcess)->DebugPort;
                break;
            case wdk::SystemVersion::Windows10_1803:
                vDebugPort = &reinterpret_cast<wdk::build_17134::PEPROCESS>(aProcess)->DebugPort;
                break;
            case wdk::SystemVersion::Windows10_1809:
                vDebugPort = &reinterpret_cast<wdk::build_17763::PEPROCESS>(aProcess)->DebugPort;
                break;
            }

            if (vDebugPort)
            {
                InterlockedExchangePointer(vDebugPort, aDebugPort);
                return STATUS_SUCCESS;
            }

            return STATUS_NOT_SUPPORTED;
        }


        inline auto PsGetProcessExceptionPort(PEPROCESS aProcess)
            ->PVOID
        {
            auto vPort = SIZE_T();

            switch (GetSystemVersion())
            {
            default:
                break;
            case wdk::SystemVersion::Windows7:
                vPort = reinterpret_cast<wdk::build_7600::PEPROCESS>(aProcess)->ExceptionPortValue;
                break;
            case wdk::SystemVersion::Windows7_SP1:
                vPort = reinterpret_cast<wdk::build_7601::PEPROCESS>(aProcess)->ExceptionPortValue;
                break;
            case wdk::SystemVersion::Windows8:
                vPort = reinterpret_cast<wdk::build_9200::PEPROCESS>(aProcess)->ExceptionPortValue;
                break;
            case wdk::SystemVersion::Windows8_1:
                vPort = reinterpret_cast<wdk::build_9600::PEPROCESS>(aProcess)->ExceptionPortValue;
                break;
            case wdk::SystemVersion::Windows10_1507:
                vPort = reinterpret_cast<wdk::build_10240::PEPROCESS>(aProcess)->ExceptionPortValue;
                break;
            case wdk::SystemVersion::Windows10_1511:
                vPort = reinterpret_cast<wdk::build_10586::PEPROCESS>(aProcess)->ExceptionPortValue;
                break;
            case wdk::SystemVersion::Windows10_1607:
                vPort = reinterpret_cast<wdk::build_14393::PEPROCESS>(aProcess)->ExceptionPortValue;
                break;
            case wdk::SystemVersion::Windows10_1703:
                vPort = reinterpret_cast<wdk::build_15063::PEPROCESS>(aProcess)->ExceptionPortValue;
                break;
            case wdk::SystemVersion::Windows10_1709:
                vPort = reinterpret_cast<wdk::build_16299::PEPROCESS>(aProcess)->ExceptionPortValue;
                break;
            case wdk::SystemVersion::Windows10_1803:
                vPort = reinterpret_cast<wdk::build_17134::PEPROCESS>(aProcess)->ExceptionPortValue;
                break;
            case wdk::SystemVersion::Windows10_1809:
                vPort = reinterpret_cast<wdk::build_17763::PEPROCESS>(aProcess)->ExceptionPortValue;
                break;
            }

            return (PVOID)vPort;
        }


        __declspec(selectany) PVOID PsSystemDllBase = nullptr;


        inline auto PsInitSystem() -> NTSTATUS
        {
            auto vStatus  = STATUS_SUCCESS;
            auto vProcess = PEPROCESS();
            auto vApcState= KAPC_STATE{};
            for (;;)
            {
                for (auto vProcessId = 500; vProcessId < 20000; vProcessId += 4)
                {
                    wdk::PsLookupProcessByProcessId((HANDLE)vProcessId, &vProcess);
                    if (vProcess)
                    {
                        break;
                    }
                }
                if (!vProcess)
                {
                    vStatus = STATUS_NOT_FOUND;
                    break;
                }

                KeStackAttachProcess((PKPROCESS)vProcess, &vApcState);

                auto vPeb = (PPEB)PsGetProcessPeb(vProcess);
                auto vLdr = (PPEB_LDR_DATA)vPeb->Ldr;
                auto vLdrHead = (PLIST_ENTRY)&vLdr->InLoadOrderModuleList;

                for (auto vLdrNext = vLdrHead->Flink; vLdrNext != vLdrHead; vLdrNext = vLdrNext->Flink)
                {
                    auto vLdrEntry = CONTAINING_RECORD(vLdrNext, LDR_DATA_TABLE_ENTRY, InLoadOrderLinks);
                    auto vDllName = (PUNICODE_STRING)&vLdrEntry->BaseDllName;

                    if (wcsncmp(vDllName->Buffer, L"ntdll.dll", vDllName->Length / sizeof(wchar_t)) == 0)
                    {
                        PsSystemDllBase = vLdrEntry->DllBase;
                        break;
                    }
                }
                if (nullptr == PsSystemDllBase)
                {
                    vStatus = STATUS_NOT_FOUND;
                    break;
                }

                break;
            }
            if (vProcess) 
            {
                KeUnstackDetachProcess(&vApcState);

                ObDereferenceObject(vProcess);
                vProcess = nullptr;
            }

            return vStatus;
        }
    }
}
