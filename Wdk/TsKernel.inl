#pragma once
#include "TsStruct.inl"


namespace wdk
{
    extern"C"
    {

        PVOID NTAPI
            PsGetCurrentThreadStackLimit(VOID);

        PVOID NTAPI
            PsGetCurrentThreadStackBase(VOID);

        KPROCESSOR_MODE NTAPI
            PsGetCurrentThreadPreviousMode(VOID);

        BOOLEAN NTAPI
            PsIsThreadTerminating(
                _In_ PETHREAD Thread
            );
        
        NTSTATUS NTAPI
            PsGetContextThread(
                __in PETHREAD Thread,
                __inout PCONTEXT ThreadContext,
                __in KPROCESSOR_MODE Mode
            );

        NTSTATUS NTAPI
            PsSetContextThread(
                __in PETHREAD Thread,
                __in PCONTEXT ThreadContext,
                __in KPROCESSOR_MODE Mode
            );
        
        VOID NTAPI
            PsSetThreadHardErrorsAreDisabled(
                __in PETHREAD Thread,
                __in BOOLEAN HardErrorsAreDisabled
            );

        VOID NTAPI
            PsSetThreadWin32Thread(
                __inout PETHREAD Thread,
                __in PVOID Win32Thread,
                __in PVOID PrevWin32Thread
            );

        CCHAR NTAPI
            PsGetThreadFreezeCount(
                __in PETHREAD Thread
            );

        BOOLEAN NTAPI
            PsGetThreadHardErrorsAreDisabled(
                __in PETHREAD Thread
            );

        PEPROCESS NTAPI
            PsGetThreadProcess(
                __in PETHREAD Thread
            );

        PEPROCESS NTAPI
            PsGetCurrentThreadProcess(
                VOID
            );

        HANDLE NTAPI
            PsGetCurrentThreadProcessId(
                VOID
            );
        
        inline CLIENT_ID NTAPI 
            PsGetThreadClientId(PETHREAD Thread)
        {
            return { PsGetThreadProcessId(Thread), PsGetThreadId(Thread) };
        }

        ULONG NTAPI
            PsGetThreadSessionId(
                __in PETHREAD Thread
            );

#define  PsGetThreadTcb(Thread) ((PKTHREAD)(Thread))

        PVOID NTAPI
            PsGetThreadTeb(
                __in PETHREAD Thread
            );

        PVOID NTAPI
            PsGetThreadWin32Thread(
                __in PETHREAD Thread
            );

        PVOID NTAPI
            PsGetCurrentThreadWin32Thread(
                VOID
            );

        PVOID NTAPI
            PsGetCurrentThreadWin32ThreadAndEnterCriticalRegion(
                __out PHANDLE ProcessId
            );

        BOOLEAN NTAPI
            PsIsSystemThread(
                __in PETHREAD Thread
            );

        BOOLEAN NTAPI
            PsIsThreadImpersonating(
                __in PETHREAD Thread
            );



    }
}

namespace wdk
{
    extern"C"
    {

        inline auto NtCurrentTeb(VOID)
            -> struct _TEB*
        {
#ifdef _WIN64
            return (struct _TEB *)__readgsqword(offsetof(NT_TIB, Self));
#else
            return (struct _TEB *)__readfsdword(offsetof(NT_TIB, Self));
#endif
        }

        inline auto PsGetThreadRundownProtect(PETHREAD aThread) 
            -> PEX_RUNDOWN_REF
        {
            auto vRundownProtect = PEX_RUNDOWN_REF();

            switch (GetSystemVersion())
            {
            default:
                break;
            case wdk::SystemVersion::Windows7:
                vRundownProtect = &reinterpret_cast<wdk::build_7600::PETHREAD>(aThread)->RundownProtect;
                break;
            case wdk::SystemVersion::Windows7_SP1:
                vRundownProtect = &reinterpret_cast<wdk::build_7601::PETHREAD>(aThread)->RundownProtect;
                break;
            case wdk::SystemVersion::Windows8:
                vRundownProtect = &reinterpret_cast<wdk::build_9200::PETHREAD>(aThread)->RundownProtect;
                break;
            case wdk::SystemVersion::Windows8_1:
                vRundownProtect = &reinterpret_cast<wdk::build_9600::PETHREAD>(aThread)->RundownProtect;
                break;
            case wdk::SystemVersion::Windows10_1507:
                vRundownProtect = &reinterpret_cast<wdk::build_10240::PETHREAD>(aThread)->RundownProtect;
                break;
            case wdk::SystemVersion::Windows10_1511:
                vRundownProtect = &reinterpret_cast<wdk::build_10586::PETHREAD>(aThread)->RundownProtect;
                break;
            case wdk::SystemVersion::Windows10_1607:
                vRundownProtect = &reinterpret_cast<wdk::build_14393::PETHREAD>(aThread)->RundownProtect;
                break;
            case wdk::SystemVersion::Windows10_1703:
                vRundownProtect = &reinterpret_cast<wdk::build_15063::PETHREAD>(aThread)->RundownProtect;
                break;
            case wdk::SystemVersion::Windows10_1709:
                vRundownProtect = &reinterpret_cast<wdk::build_16299::PETHREAD>(aThread)->RundownProtect;
                break;
            case wdk::SystemVersion::Windows10_1803:
                vRundownProtect = &reinterpret_cast<wdk::build_17134::PETHREAD>(aThread)->RundownProtect;
                break;
            case wdk::SystemVersion::Windows10_1809:
                vRundownProtect = &reinterpret_cast<wdk::build_17763::PETHREAD>(aThread)->RundownProtect;
                break;
            }

            return vRundownProtect;
        }


        inline auto PsGetThreadCrossFlags(PETHREAD aThread)
            -> UINT32
        {
            auto vFlags = UINT32();

            switch (GetSystemVersion())
            {
            default:
                break;
            case wdk::SystemVersion::Windows7:
                vFlags = reinterpret_cast<wdk::build_7600::PETHREAD>(aThread)->CrossThreadFlags;
                break;
            case wdk::SystemVersion::Windows7_SP1:
                vFlags = reinterpret_cast<wdk::build_7601::PETHREAD>(aThread)->CrossThreadFlags;
                break;
            case wdk::SystemVersion::Windows8:
                vFlags = reinterpret_cast<wdk::build_9200::PETHREAD>(aThread)->CrossThreadFlags;
                break;
            case wdk::SystemVersion::Windows8_1:
                vFlags = reinterpret_cast<wdk::build_9600::PETHREAD>(aThread)->CrossThreadFlags;
                break;
            case wdk::SystemVersion::Windows10_1507:
                vFlags = reinterpret_cast<wdk::build_10240::PETHREAD>(aThread)->CrossThreadFlags;
                break;
            case wdk::SystemVersion::Windows10_1511:
                vFlags = reinterpret_cast<wdk::build_10586::PETHREAD>(aThread)->CrossThreadFlags;
                break;
            case wdk::SystemVersion::Windows10_1607:
                vFlags = reinterpret_cast<wdk::build_14393::PETHREAD>(aThread)->CrossThreadFlags;
                break;
            case wdk::SystemVersion::Windows10_1703:
                vFlags = reinterpret_cast<wdk::build_15063::PETHREAD>(aThread)->CrossThreadFlags;
                break;
            case wdk::SystemVersion::Windows10_1709:
                vFlags = reinterpret_cast<wdk::build_16299::PETHREAD>(aThread)->CrossThreadFlags;
                break;
            case wdk::SystemVersion::Windows10_1803:
                vFlags = reinterpret_cast<wdk::build_17134::PETHREAD>(aThread)->CrossThreadFlags;
                break;
            case wdk::SystemVersion::Windows10_1809:
                vFlags = reinterpret_cast<wdk::build_17763::PETHREAD>(aThread)->CrossThreadFlags;
                break;
            }

            if (!IsWindows8OrGreater())
            {
                if (reinterpret_cast<wdk::build_7600::PETHREAD>(aThread)->HardErrorsAreDisabled)
                {
                    vFlags |= PsCrossThreadFlagsHardErrorsAreDisabled;
                }
                if (reinterpret_cast<wdk::build_7600::PETHREAD>(aThread)->BreakOnTermination)
                {
                    vFlags |= PsCrossThreadFlagsBreakOnTermination;
                }
                if (reinterpret_cast<wdk::build_7600::PETHREAD>(aThread)->SkipCreationMsg)
                {
                    vFlags |= PsCrossThreadFlagsSkipCreationMsg;
                }
                if (reinterpret_cast<wdk::build_7600::PETHREAD>(aThread)->SkipTerminationMsg)
                {
                    vFlags |= PsCrossThreadFlagsSkipTerminationMsg;
                }
            }

            return vFlags;
        }


        inline auto PsSetThreadCrossFlags(PETHREAD aThread, UINT32 aFlags)
            -> VOID
        {
            auto vFlags = (UINT32*)(nullptr);

            switch (GetSystemVersion())
            {
            default:
                break;
            case wdk::SystemVersion::Windows7:
                vFlags = &reinterpret_cast<wdk::build_7600::PETHREAD>(aThread)->CrossThreadFlags;
                break;
            case wdk::SystemVersion::Windows7_SP1:
                vFlags = &reinterpret_cast<wdk::build_7601::PETHREAD>(aThread)->CrossThreadFlags;
                break;
            case wdk::SystemVersion::Windows8:
                vFlags = &reinterpret_cast<wdk::build_9200::PETHREAD>(aThread)->CrossThreadFlags;
                break;
            case wdk::SystemVersion::Windows8_1:
                vFlags = &reinterpret_cast<wdk::build_9600::PETHREAD>(aThread)->CrossThreadFlags;
                break;
            case wdk::SystemVersion::Windows10_1507:
                vFlags = &reinterpret_cast<wdk::build_10240::PETHREAD>(aThread)->CrossThreadFlags;
                break;
            case wdk::SystemVersion::Windows10_1511:
                vFlags = &reinterpret_cast<wdk::build_10586::PETHREAD>(aThread)->CrossThreadFlags;
                break;
            case wdk::SystemVersion::Windows10_1607:
                vFlags = &reinterpret_cast<wdk::build_14393::PETHREAD>(aThread)->CrossThreadFlags;
                break;
            case wdk::SystemVersion::Windows10_1703:
                vFlags = &reinterpret_cast<wdk::build_15063::PETHREAD>(aThread)->CrossThreadFlags;
                break;
            case wdk::SystemVersion::Windows10_1709:
                vFlags = &reinterpret_cast<wdk::build_16299::PETHREAD>(aThread)->CrossThreadFlags;
                break;
            case wdk::SystemVersion::Windows10_1803:
                vFlags = &reinterpret_cast<wdk::build_17134::PETHREAD>(aThread)->CrossThreadFlags;
                break;
            case wdk::SystemVersion::Windows10_1809:
                vFlags = &reinterpret_cast<wdk::build_17763::PETHREAD>(aThread)->CrossThreadFlags;
                break;
            }

            if (vFlags)
            {
                if (IsWindows8OrGreater())
                {
                    RtlInterlockedSetBitsDiscardReturn(vFlags, aFlags);
                }
                else
                {
                    if (aFlags & PsCrossThreadFlagsHardErrorsAreDisabled)
                    {
                        reinterpret_cast<wdk::build_7600::PETHREAD>(aThread)->HardErrorsAreDisabled = true;
                    }
                    if (aFlags & PsCrossThreadFlagsBreakOnTermination)
                    {
                        reinterpret_cast<wdk::build_7600::PETHREAD>(aThread)->BreakOnTermination = true;
                    }
                    if (aFlags & PsCrossThreadFlagsSkipCreationMsg)
                    {
                        reinterpret_cast<wdk::build_7600::PETHREAD>(aThread)->SkipCreationMsg = true;
                    }
                    if (aFlags & PsCrossThreadFlagsSkipTerminationMsg)
                    {
                        reinterpret_cast<wdk::build_7600::PETHREAD>(aThread)->SkipTerminationMsg = true;
                    }
                }
            }
        }


        inline auto PsGetThreadStartAddress(PETHREAD aThread)
            -> PVOID
        {
            auto vStartAddress = PVOID();

            switch (GetSystemVersion())
            {
            default:
                break;
            case wdk::SystemVersion::Windows7:
                vStartAddress = reinterpret_cast<wdk::build_7600::PETHREAD>(aThread)->StartAddress;
                break;
            case wdk::SystemVersion::Windows7_SP1:
                vStartAddress = reinterpret_cast<wdk::build_7601::PETHREAD>(aThread)->StartAddress;
                break;
            case wdk::SystemVersion::Windows8:
                vStartAddress = reinterpret_cast<wdk::build_9200::PETHREAD>(aThread)->StartAddress;
                break;
            case wdk::SystemVersion::Windows8_1:
                vStartAddress = reinterpret_cast<wdk::build_9600::PETHREAD>(aThread)->StartAddress;
                break;
            case wdk::SystemVersion::Windows10_1507:
                vStartAddress = reinterpret_cast<wdk::build_10240::PETHREAD>(aThread)->StartAddress;
                break;
            case wdk::SystemVersion::Windows10_1511:
                vStartAddress = reinterpret_cast<wdk::build_10586::PETHREAD>(aThread)->StartAddress;
                break;
            case wdk::SystemVersion::Windows10_1607:
                vStartAddress = reinterpret_cast<wdk::build_14393::PETHREAD>(aThread)->StartAddress;
                break;
            case wdk::SystemVersion::Windows10_1703:
                vStartAddress = reinterpret_cast<wdk::build_15063::PETHREAD>(aThread)->StartAddress;
                break;
            case wdk::SystemVersion::Windows10_1709:
                vStartAddress = reinterpret_cast<wdk::build_16299::PETHREAD>(aThread)->StartAddress;
                break;
            case wdk::SystemVersion::Windows10_1803:
                vStartAddress = reinterpret_cast<wdk::build_17134::PETHREAD>(aThread)->StartAddress;
                break;
            case wdk::SystemVersion::Windows10_1809:
                vStartAddress = reinterpret_cast<wdk::build_17763::PETHREAD>(aThread)->StartAddress;
                break;
            }

            return vStartAddress;
        }


        inline auto TsInitSystem() -> NTSTATUS
        {
            return STATUS_SUCCESS;
        }
    }
}
