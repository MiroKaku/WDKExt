#pragma once


namespace wdk
{

#pragma region Handle
    using ExEnumHandleRoutineWin7 = BOOLEAN(*)(
        _Inout_ struct _HANDLE_TABLE_ENTRY* HandleTableEntry,
        _In_ HANDLE Handle,
        _In_ PVOID EnumParameter
        );

    // since Windows 8
    using ExEnumHandleRoutine = BOOLEAN(*)(
        _In_ struct _HANDLE_TABLE* HandleTable,
        _Inout_ struct _HANDLE_TABLE_ENTRY* HandleTableEntry,
        _In_ HANDLE Handle,
        _In_ PVOID EnumParameter
        );
#pragma endregion


#pragma region Lock
#ifndef EX_PUSH_LOCK
#define EX_PUSH_LOCK    ULONG_PTR
#define PEX_PUSH_LOCK   ULONG_PTR*
#endif


    typedef struct _EX_PUSH_LOCK
    {
        enum : ULONG_PTR
        {
            LockFlagsShift          = 0x0000,
            LockFlagsLock           = 0x0001,
            LockFlagsWaiting        = 0x0002,
            LockFlagsWaking         = 0x0004,
            LockFlagsMultipleShared = 0x0008,
            LockFlagsShareInc       = 0x0010,
            LockFlagsPtrBits        = 0x000F,
        };

        union
        {
            struct
            {
                ULONG_PTR Locked   : 1; /* bit position: 0 */
                ULONG_PTR Waiting  : 1; /* bit position: 1 */
                ULONG_PTR Waking   : 1; /* bit position: 2 */
                ULONG_PTR MultipleShared : 1; /* bit position: 3 */
                ULONG_PTR Shared   : (sizeof(ULONG_PTR) * 8) - 4; /* bit position: 4 */
            }; /* bitfield */

            ULONG_PTR   Value;
            void*       Ptr;
        };
    } EX_PUSH_LOCK_IMPL, *PEX_PUSH_LOCK_IMPL;


    enum : UINT32
    {
        ExCacheLineSize         = 128,
        ExPushLockFannedCOunt   = (PAGE_SIZE / ExCacheLineSize),
    };

    typedef struct EX_PUSH_LOCK_CACHE_AWARE
    {
        PEX_PUSH_LOCK Locks[ExPushLockFannedCOunt];
    }*PEX_PUSH_LOCK_CACHE_AWARE;


    typedef struct _EX_FAST_REF
    {
        enum : UINT32
        {
            BitOfRefCount = (sizeof(ULONG_PTR) == sizeof(UINT32)) ? 3 : 4,
        };

        union
        {
            VOID *      Object;
            ULONG_PTR   RefCnt : BitOfRefCount;
            ULONG_PTR   Value;
        };
    } EX_FAST_REF, *PEX_FAST_REF;
#pragma endregion

}

#include "Ex\build_7600.inl"
#include "Ex\build_7601.inl"
#include "Ex\build_9200.inl"
#include "Ex\build_9600.inl"
#include "Ex\build_10240.inl"
#include "Ex\build_10586.inl"
#include "Ex\build_14393.inl"
#include "Ex\build_15063.inl"
#include "Ex\build_16299.inl"
#include "Ex\build_17134.inl"
#include "Ex\build_17763.inl"
