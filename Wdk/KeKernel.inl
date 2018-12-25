#pragma once
#include "KeStruct.inl"


namespace wdk
{

    extern"C"
    {
        
        BOOLEAN NTAPI
            KeAddSystemServiceTable(
                _In_ PULONG_PTR aBase,
                _In_opt_ PULONG aCount,
                _In_ ULONG      aLimit,
                _In_ PUCHAR     aNumber,
                _In_ ULONG      aIndex
            );


#ifndef KeGetPreviousMode
#define KeGetPreviousMode ExGetPreviousMode
#endif


        void NTAPI
            KeStackAttachProcess(
                _In_  PKPROCESS PROCESS,
                _Out_ PRKAPC_STATE ApcState
            );


        void NTAPI
            KeUnstackDetachProcess(
                _In_ PRKAPC_STATE ApcState
            );


        VOID NTAPI
            KeInitializeApc(
                _Out_ PRKAPC aApc,
                _In_ PRKTHREAD aThread,
                _In_ KAPC_ENVIRONMENT aEnvironment,
                _In_ PKKERNEL_ROUTINE aKernelRoutine,
                _In_opt_ PKRUNDOWN_ROUTINE aRundownRoutine,
                _In_opt_ PKNORMAL_ROUTINE aNormalRoutine,
                _In_opt_ KPROCESSOR_MODE aProcessorMode,
                _In_opt_ PVOID aNormalContext
            );


        BOOLEAN NTAPI
            KeInsertQueueApc(
                _Inout_ PRKAPC aApc,
                _In_opt_ PVOID aSystemArgument1,
                _In_opt_ PVOID aSystemArgument2,
                _In_ KPRIORITY aIncrement
            );


        //BOOLEAN NTAPI
        //    KeRemoveQueueApc(
        //        _Inout_ PKAPC Apc
        //    );


        BOOLEAN NTAPI
            KeTestAlertThread(
                _In_ KPROCESSOR_MODE AlertMode
            );

        VOID NTAPI
            KeGenericCallDpc(
                _In_ PKDEFERRED_ROUTINE Routine,
                _In_opt_ PVOID Context
            );

        VOID NTAPI
            KeSignalCallDpcDone(
                _In_ PVOID SystemArgument1
            );

        LOGICAL NTAPI
            KeSignalCallDpcSynchronize(
                _In_ PVOID SystemArgument2
            );

    }
}

namespace wdk
{
    extern"C"
    {
        inline auto KeInitSystem() -> NTSTATUS
        {
            return STATUS_SUCCESS;
        }
    }
}
