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

        inline auto TsInitSystem() -> NTSTATUS
        {
            return STATUS_SUCCESS;
        }
    }
}
