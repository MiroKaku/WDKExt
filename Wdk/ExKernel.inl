#pragma once
#include "ExStruct.inl"


namespace wdk
{
    extern"C"
    {

        extern POBJECT_TYPE* ExWindowStationObjectType;
        

        int NTAPI
            ExSystemExceptionFilter(
                VOID
            );


        BOOLEAN NTAPI
            ExEnumHandleTable(
                _In_ struct _HANDLE_TABLE*  HandleTable,
                _In_ ExEnumHandleRoutine    EnumHandleProcedure,
                _In_ PVOID EnumParameter,
                _Out_opt_ PHANDLE Handle
            );


        PEX_PUSH_LOCK_CACHE_AWARE NTAPI
            ExAllocateCacheAwarePushLock(
                VOID
            );

        VOID NTAPI
            ExFreeCacheAwarePushLock(
                _Inout_ PEX_PUSH_LOCK_CACHE_AWARE PushLock
            );

        VOID NTAPI
            ExAcquireCacheAwarePushLockExclusive(
                _Inout_ PEX_PUSH_LOCK_CACHE_AWARE CacheAwarePushLock
            );

        VOID NTAPI
            ExReleaseCacheAwarePushLockExclusive(
                _Inout_ PEX_PUSH_LOCK_CACHE_AWARE CacheAwarePushLock
            );
        
        VOID FASTCALL
            ExEnterCriticalRegionAndAcquireFastMutexUnsafe(
                _Inout_ PFAST_MUTEX FastMutex
            );

        VOID NTAPI
            ExInitializePushLock(
                _Out_ PEX_PUSH_LOCK PushLock
            );

        VOID FASTCALL 
            ExfAcquirePushLockExclusive(
                _Inout_ PEX_PUSH_LOCK aPushLock
            );

        VOID FASTCALL
            ExfReleasePushLockExclusive(
                _Inout_ PEX_PUSH_LOCK aPushLock);

        VOID FASTCALL 
            ExfAcquirePushLockShared(
                _Inout_ PEX_PUSH_LOCK aPushLock
            );

        VOID FASTCALL
            ExfReleasePushLockShared(
                _Inout_ PEX_PUSH_LOCK aPushLock);

        BOOLEAN FASTCALL
            ExfTryAcquirePushLockShared(
                _Inout_ PEX_PUSH_LOCK aPushLock);

        VOID FASTCALL
            ExfTryToWakePushLock(
                _Inout_ PEX_PUSH_LOCK aPushLock);

        VOID FASTCALL
            ExfReleasePushLock(
                _Inout_ PEX_PUSH_LOCK aPushLock
            );

        // since win8.1
        VOID FASTCALL
            ExAcquirePushLockExclusiveEx(
                _Inout_ _Requires_lock_not_held_(*_Curr_) _Acquires_lock_(*_Curr_)
                PEX_PUSH_LOCK PushLock,
                _In_ ULONG Flags
            );

        // since win8.1
        VOID FASTCALL
            ExAcquirePushLockSharedEx(
                _Inout_ _Requires_lock_not_held_(*_Curr_) _Acquires_lock_(*_Curr_)
                PEX_PUSH_LOCK PushLock,
                _In_ ULONG Flags
            );

        // since win8.1
        VOID FASTCALL
            ExReleasePushLockExclusiveEx(
                _Inout_ _Requires_lock_held_(*_Curr_) _Releases_lock_(*_Curr_)
                PEX_PUSH_LOCK PushLock,
                _In_ ULONG Flags
            );

        // since win8.1
        VOID FASTCALL
            ExReleasePushLockSharedEx(
                _Inout_ _Requires_lock_held_(*_Curr_) _Releases_lock_(*_Curr_)
                PEX_PUSH_LOCK PushLock,
                _In_ ULONG Flags
            );
    }
}

namespace wdk
{
    extern"C"
    {


        FORCEINLINE VOID ExReleasePushLock(
            PEX_PUSH_LOCK aPushLock)
        {
            EX_PUSH_LOCK_IMPL vOldValue{}, vNewValue{};

            vOldValue.Value = *aPushLock;

            if (vOldValue.Shared > 1)
            {
                vNewValue.Value = vOldValue.Value - EX_PUSH_LOCK_IMPL::LockFlagsShareInc;
            }
            else
            {
                vNewValue.Value = 0;
            }

            if (vOldValue.Waiting ||
                InterlockedCompareExchangePointer(
                    &reinterpret_cast<PEX_PUSH_LOCK_IMPL>(aPushLock)->Ptr,
                    vNewValue.Ptr,
                    vOldValue.Ptr) != vOldValue.Ptr)
            {
                ExfReleasePushLock(aPushLock);
            }
        }

#ifndef ExAcquirePushLockExclusive
        FORCEINLINE VOID ExAcquirePushLockExclusive(
            PEX_PUSH_LOCK aPushLock)
        {
#ifdef _WIN64
            if (InterlockedBitTestAndSet64((LONG64 *)&reinterpret_cast<PEX_PUSH_LOCK_IMPL>(aPushLock)->Value, EX_PUSH_LOCK_IMPL::LockFlagsShift))
#else
            if (InterlockedBitTestAndSet((LONG *)&reinterpret_cast<PEX_PUSH_LOCK_IMPL>(aPushLock)->Value, EX_PUSH_LOCK_IMPL::LockFlagsShift))
#endif
            {
                ExfAcquirePushLockExclusive(aPushLock);
            }
        }
#endif

#ifndef ExAcquirePushLockShared
        FORCEINLINE VOID ExAcquirePushLockShared(
            PEX_PUSH_LOCK aPushLock)
        {
            if (InterlockedCompareExchangePointer(
                &(reinterpret_cast<PEX_PUSH_LOCK_IMPL>(aPushLock)->Ptr),
                (PVOID)(EX_PUSH_LOCK_IMPL::LockFlagsShareInc | EX_PUSH_LOCK_IMPL::LockFlagsLock),
                nullptr) != nullptr)
            {
                ExfAcquirePushLockShared(aPushLock);
            }
        }
#endif

        FORCEINLINE BOOLEAN ExTryAcquirePushLockExclusive(
            PEX_PUSH_LOCK aPushLock)
        {
#ifdef _WIN64
            if (InterlockedBitTestAndSet64((LONG64 *)&reinterpret_cast<PEX_PUSH_LOCK_IMPL>(aPushLock)->Value, EX_PUSH_LOCK_IMPL::LockFlagsShift))
#else
            if (InterlockedBitTestAndSet((LONG *)&reinterpret_cast<PEX_PUSH_LOCK_IMPL>(aPushLock)->Value, EX_PUSH_LOCK_IMPL::LockFlagsShift))
#endif
            {
                return TRUE;
            }
            else
            {
                return FALSE;
            }
        }

        FORCEINLINE BOOLEAN ExTryAcquirePushLockShared(
            PEX_PUSH_LOCK aPushLock
        )
        {
            /* Fast path with the push lock not held at all. */
            if (InterlockedCompareExchangePointer(
                &reinterpret_cast<PEX_PUSH_LOCK_IMPL>(aPushLock)->Ptr,
                (PVOID)(EX_PUSH_LOCK_IMPL::LockFlagsShareInc | EX_PUSH_LOCK_IMPL::LockFlagsLock),
                nullptr) != nullptr)
            {
                return ExfTryAcquirePushLockShared(aPushLock);
            }

            return TRUE;
        }

#ifndef ExReleasePushLockExclusive
        VOID FORCEINLINE ExReleasePushLockExclusive(
            PEX_PUSH_LOCK aPushLock)
        {
            EX_PUSH_LOCK_IMPL OldValue;

#if defined (_WIN64)
            OldValue.Value = InterlockedExchangeAdd64((PLONG64)&reinterpret_cast<PEX_PUSH_LOCK_IMPL>(aPushLock)->Value, -(LONG64)EX_PUSH_LOCK_IMPL::LockFlagsLock);
#else
            OldValue.Value = InterlockedExchangeAdd((PLONG)&reinterpret_cast<PEX_PUSH_LOCK_IMPL>(aPushLock)->Value, -(LONG)EX_PUSH_LOCK_IMPL::LockFlagsLock);
#endif

            if (!OldValue.Waiting || OldValue.Waking)
            {
                return;
            }

            ExfTryToWakePushLock(aPushLock);
        }
#endif

#ifndef ExReleasePushLockShared
        VOID FORCEINLINE ExReleasePushLockShared(
            PEX_PUSH_LOCK aPushLock)
        {
            EX_PUSH_LOCK_IMPL OldValue, NewValue;

            OldValue.Value = EX_PUSH_LOCK_IMPL::LockFlagsShareInc | EX_PUSH_LOCK_IMPL::LockFlagsLock;
            NewValue.Value = 0;

            if (InterlockedCompareExchangePointer(&reinterpret_cast<PEX_PUSH_LOCK_IMPL>(aPushLock)->Ptr,
                NewValue.Ptr,
                OldValue.Ptr) != OldValue.Ptr)
            {
                ExfReleasePushLockShared(aPushLock);
            }
        }
#endif


        inline auto ExInitSystem() -> NTSTATUS
        {
            return STATUS_SUCCESS;
        }
    }
}
