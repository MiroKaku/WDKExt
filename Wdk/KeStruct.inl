#pragma once
#include "RtlStruct.inl"


namespace wdk
{

#pragma region System Service Table
    enum : UINT32
    {
        SystemServiceIndex,
        Win32kServiceIndex,
        NumberServiceTables,
    };

    typedef struct _KSERVICE_TABLE_DESCRIPTOR
    {
        PULONG_PTR  Base;   // SSDT Base , signed long
        PULONG      Count;
        ULONG       Limit;  // Descriptor Count and Limit.
        UINT8*      Number;
    } KSERVICE_TABLE_DESCRIPTOR, *PKSERVICE_TABLE_DESCRIPTOR;
#pragma endregion


#pragma region APC
    typedef struct _KAPC_STATE
    {
        LIST_ENTRY ApcListHead[MaximumMode];
        struct _KPROCESS *Process;
        union
        {
            UCHAR InProgressFlags;
            struct
            {
                BOOLEAN KernelApcInProgress : 1;
                BOOLEAN SpecialApcInProgress : 1;
            };
        };

        BOOLEAN KernelApcPending;
        BOOLEAN UserApcPending;
    } KAPC_STATE, *PKAPC_STATE, *PRKAPC_STATE;


    enum : UINT32
    {
        ApcStateActualSize          = offsetof(KAPC_STATE, UserApcPending) + sizeof(BOOLEAN),

        ApcOffsetToSpareByte0       = offsetof(KAPC, SpareByte0),
        ApcOffsetToSpareByte1       = offsetof(KAPC, SpareByte1),
        ApcOffsetToSpareLong        = offsetof(KAPC, SpareLong0),
        ApcOffsetToSystemArgument1  = offsetof(KAPC, SystemArgument1),
        ApcOffsetToSystemArgument2  = offsetof(KAPC, SystemArgument2),
        ApcOffsetToApcStateIndex    = offsetof(KAPC, ApcStateIndex),
        ApcActualSize               = offsetof(KAPC, Inserted) + sizeof(BOOLEAN),
    };


    typedef enum KAPC_ENVIRONMENT
    {
        OriginalApcEnvironment,
        AttachedApcEnvironment,
        CurrentApcEnvironment,
        InsertApcEnvironment
    }*PKAPC_ENVIRONMENT;

    using PKNORMAL_ROUTINE = void (NTAPI*)(
        _In_ PVOID NormalContext,
        _In_ PVOID SystemArgument1,
        _In_ PVOID SystemArgument2);

    using PKKERNEL_ROUTINE = void (NTAPI*)(
        _In_ PRKAPC Apc,
        _Inout_ PKNORMAL_ROUTINE NormalRoutine,
        _Inout_ PVOID *NormalContext,
        _Inout_ PVOID *SystemArgument1,
        _Inout_ PVOID *SystemArgument2);

    using PKRUNDOWN_ROUTINE = void (NTAPI*)(
        _In_ PRKAPC Apc);
#pragma endregion


#pragma region Semaphore
    enum : UINT32
    {
        SemaphoreActualSize = offsetof(KSEMAPHORE, Limit) + sizeof(LONG),
    };
#pragma endregion


#pragma region WaitBlock
    enum : UINT32
    {
#ifdef _WIN64
        WaitBlockOffsetToLong0 = offsetof(KWAIT_BLOCK, SpareLong) + sizeof(KWAIT_BLOCK) * 0,
        WaitBlockOffsetToLong1 = offsetof(KWAIT_BLOCK, SpareLong) + sizeof(KWAIT_BLOCK) * 1,
        WaitBlockOffsetToLong2 = offsetof(KWAIT_BLOCK, SpareLong) + sizeof(KWAIT_BLOCK) * 2,
        WaitBlockOffsetToLong3 = offsetof(KWAIT_BLOCK, SpareLong) + sizeof(KWAIT_BLOCK) * 3,
#endif

        WaitBlockOffsetToPtr0 = offsetof(KWAIT_BLOCK, SparePtr) + sizeof(KWAIT_BLOCK) * 0,
        WaitBlockOffsetToPtr1 = offsetof(KWAIT_BLOCK, SparePtr) + sizeof(KWAIT_BLOCK) * 1,
        WaitBlockOffsetToPtr2 = offsetof(KWAIT_BLOCK, SparePtr) + sizeof(KWAIT_BLOCK) * 2,
        WaitBlockOffsetToPtr3 = offsetof(KWAIT_BLOCK, SparePtr) + sizeof(KWAIT_BLOCK) * 3,

        WaitBlockOffsetToObject0 = offsetof(KWAIT_BLOCK, Object) + sizeof(KWAIT_BLOCK) * 0,
        WaitBlockOffsetToObject1 = offsetof(KWAIT_BLOCK, Object) + sizeof(KWAIT_BLOCK) * 1,
        WaitBlockOffsetToObject2 = offsetof(KWAIT_BLOCK, Object) + sizeof(KWAIT_BLOCK) * 2,
        WaitBlockOffsetToObject3 = offsetof(KWAIT_BLOCK, Object) + sizeof(KWAIT_BLOCK) * 3,
    };
#pragma endregion


#pragma region Ldr
    // DriverSection
    typedef struct _KLDR_DATA_TABLE_ENTRY
    {
        LIST_ENTRY  InLoadOrderLinks;
        PVOID       ExceptionTable;
        UINT32      ExceptionTableSize;
        PVOID       GpValue;
        struct _NON_PAGED_DEBUG_INFO *NonPagedDebugInfo;
        PVOID       DllBase;
        PVOID       EntryPoint;
        UINT32      SizeOfImage;
        UNICODE_STRING FullDllName;
        UNICODE_STRING BaseDllName;
        union
        {
            UINT32      Flags;
            struct
            {
                UINT32 _ReservedFlags0 : 1;
                UINT32 StaticImport : 1;
                UINT32 ImageDll : 1;
                UINT32 _ReservedFlags1 : 2;
                UINT32 IntegrityCheck : 1;
                UINT32 _ReservedFlags2 : 8;
                UINT32 EntryProcessed : 1;
                UINT32 _ReservedFlags3 : 5;
                UINT32 DebugSymbolsLoaded : 1;
                UINT32 _ReservedFlags4 : 3;
                UINT32 SystemMapped : 1;
                UINT32 ImageVerifying : 1;
                UINT32 DriverDependentDll : 1;
                UINT32 EntryNative : 1;
                UINT32 Redirected : 1;
                UINT32 NonPagedDebug : 1;
                UINT32 MmLoaded : 1;
                UINT32 CompatDatabaseProcessed : 1;
            };
        };
        UINT16      LoadCount;
        union
        {
            struct
            {
                UINT16 SignatureLevel : 4;
                UINT16 SignatureType : 3;
                UINT16 Unused : 9;
            };
            UINT16 EntireField;
        } Signature;
        PVOID   SectionPointer;
        UINT32  CheckSum;
        UINT32  CoverageSectionSize;
        PVOID   CoverageSection;
        PVOID   LoadedImports;
        PVOID   Spare;
        UINT32  SizeOfImageNotRounded;
        UINT32  TimeDateStamp;
    } KLDR_DATA_TABLE_ENTRY, *PKLDR_DATA_TABLE_ENTRY;
    static_assert(sizeof(KLDR_DATA_TABLE_ENTRY) == (sizeof(SIZE_T) == sizeof(UINT64) ? 0xA0 : 0x5C));


    // General part
    template<typename T = PVOID>
    struct LDR_DATA_TABLE_ENTRY_T
    {
        using LIST_ENTRY        = LIST_ENTRY_T<T>;
        using UNICODE_STRING    = T_STRING<T>;

        LIST_ENTRY InLoadOrderLinks;
        LIST_ENTRY InMemoryOrderLinks;
        union
        {
            LIST_ENTRY InInitializationOrderLinks;
            LIST_ENTRY InProgressLinks;
        };
        T       DllBase;
        T       EntryPoint;
        UINT32  SizeOfImage;
        UNICODE_STRING FullDllName;
        UNICODE_STRING BaseDllName;
        union
        {
            UINT8  FlagGroup[4];
            UINT32 Flags;
            struct
            {
                UINT32 PackagedBinary : 1;
                UINT32 MarkedForRemoval : 1;
                UINT32 ImageDll : 1;
                UINT32 LoadNotificationsSent : 1;
                UINT32 TelemetryEntryProcessed : 1;
                UINT32 ProcessStaticImport : 1;
                UINT32 InLegacyLists : 1;
                UINT32 InIndexes : 1;
                UINT32 ShimDll : 1;
                UINT32 InExceptionTable : 1;
                UINT32 ReservedFlags1 : 2;
                UINT32 LoadInProgress : 1;
                UINT32 LoadConfigProcessed : 1;
                UINT32 EntryProcessed : 1;
                UINT32 ProtectDelayLoad : 1;
                UINT32 ReservedFlags3 : 2;
                UINT32 DontCallForThreads : 1;
                UINT32 ProcessAttachCalled : 1;
                UINT32 ProcessAttachFailed : 1;
                UINT32 CorDeferredValidate : 1;
                UINT32 CorImage : 1;
                UINT32 DontRelocate : 1;
                UINT32 CorILOnly : 1;
                UINT32 ReservedFlags5 : 3;
                UINT32 Redirected : 1;
                UINT32 ReservedFlags6 : 2;
                UINT32 CompatDatabaseProcessed : 1;
            };
        };
        UINT16      LoadCount;
        UINT16      TlsIndex;
        LIST_ENTRY  HashLinks;
        UINT32      TimeDateStamp;
    };
    using LDR_DATA_TABLE_ENTRY   = LDR_DATA_TABLE_ENTRY_T<PVOID>;
    using LDR_DATA_TABLE_ENTRY32 = LDR_DATA_TABLE_ENTRY_T<PVOID32>;
    using LDR_DATA_TABLE_ENTRY64 = LDR_DATA_TABLE_ENTRY_T<PVOID64>;
#pragma endregion
       

#pragma region Mutex
    typedef struct _KGUARDED_MUTEX
    {
        volatile INT32 Count;
        struct _KTHREAD* Owner;
        UINT32 Contention;
        struct _KGATE Gate;
        union
        {
            struct
            {
                INT16 KernelApcDisable;
                INT16 SpecialApcDisable;
            }; /* size: 0x0004 */
            UINT32 CombinedApcDisable;
        }; /* size: 0x0004 */
    } KGUARDED_MUTEX, *PKGUARDED_MUTEX; /* size: 0x0038 */ /* size: 0x0020 */
    static_assert(sizeof(KGUARDED_MUTEX) == (sizeof(SIZE_T) == sizeof(UINT64) ? 0x0038 : 0x0020));
#pragma endregion


}

#include "Ke\build_7600.inl"
#include "Ke\build_7601.inl"
#include "Ke\build_9200.inl"
#include "Ke\build_9600.inl"
#include "Ke\build_10240.inl"
#include "Ke\build_10586.inl"
#include "Ke\build_14393.inl"
#include "Ke\build_15063.inl"
#include "Ke\build_16299.inl"
#include "Ke\build_17134.inl"
#include "Ke\build_17763.inl"
