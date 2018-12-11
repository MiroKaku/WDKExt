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
        _Inout_ PKNORMAL_ROUTINE* NormalRoutine,
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
    // DRIVER_OBJECT::DriverSection
    typedef struct _KLDR_DATA_TABLE_ENTRY
    {
        struct _LIST_ENTRY InLoadOrderLinks;
        VOID* ExceptionTable;
        UINT32 ExceptionTableSize;
        VOID* GpValue;
        struct _NON_PAGED_DEBUG_INFO* NonPagedDebugInfo;
        VOID* DllBase;
        VOID* EntryPoint;
        UINT32 SizeOfImage;
        struct _UNICODE_STRING FullDllName;
        struct _UNICODE_STRING BaseDllName;
        union
        {
            enum : UINT32
            {
                KLDR_STATIC_LINK                = 0x00000002,
                KLDR_IMAGE_DLL                  = 0x00000004,

                KLDR_INTEGRITY_CHECK            = 0x00000020,
                
                KLDR_LOAD_IN_PROGRESS           = 0x00001000,
                KLDR_UNLOAD_IN_PROGRESS         = 0x00002000,
                KLDR_ENTRY_PROCESSED            = 0x00004000,
                KLDR_ENTRY_INSERTED             = 0x00008000,

                KLDR_DEBUG_SYMBOLS_LOADED       = 0x00100000,

                KLDR_SYSTEM_MAPPED              = 0x01000000,
                KLDR_IMAGE_VERIFYING            = 0x02000000,
                KLDR_DRIVER_DEPENDENT_DLL       = 0x04000000,
                KLDR_ENTRY_NATIVE               = 0x08000000,

                KLDR_REDIRECTED                 = 0x10000000,
                KLDR_NON_PAGED_DEBUG_INFO       = 0x20000000,
                KLDR_MM_LOADED                  = 0x40000000,
                KLDR_COMPAT_DATABASE_PROCESSED  = 0x80000000,
            };

            UINT32      Flags;
            struct
            {
                UINT32 ReservedFlags0 : 1; /* bit position: 0 */
                UINT32 StaticImport : 1; /* bit position: 1 */
                UINT32 ImageDll : 1; /* bit position: 2 */
                UINT32 ReservedFlags1 : 1; /* bit position: 3 */

                UINT32 ReservedFlags2 : 1; /* bit position: 4 */
                UINT32 IntegrityCheck : 1; /* bit position: 5 */
                UINT32 ReservedFlags3 : 2; /* bit position: 6 */

                UINT32 ReservedFlags4 : 4; /* bit position: 8 */

                UINT32 LoadInProgress : 1; /* bit position: 12 */
                UINT32 UnloadInProgress : 1; /* bit position: 13 */
                UINT32 EntryProcessed : 1; /* bit position: 14 */
                UINT32 EntryInserted : 1; /* bit position: 15 */

                UINT32 ReservedFlags5 : 4; /* bit position: 16 */

                UINT32 DebugSymbolsLoaded : 1; /* bit position: 20 */
                UINT32 ReservedFlags6 : 3; /* bit position: 21 */

                UINT32 SystemMapped : 1; /* bit position: 24 */
                UINT32 ImageVerifying : 1; /* bit position: 25 */
                UINT32 DriverDependentDll : 1; /* bit position: 26 */
                UINT32 EntryNative : 1; /* bit position: 27 */

                UINT32 Redirected : 1; /* bit position: 28 */
                UINT32 NonPagedDebugInfo : 1; /* bit position: 29 */
                UINT32 MmLoaded : 1; /* bit position: 30 */
                UINT32 CompatDatabaseProcessed : 1; /* bit position: 31 */
            }FlagsField;
        };
        UINT16 LoadCount;
        union
        {
            union
            {
                struct
                {
                    UINT16 SignatureLevel : 4; /* bit position: 0 */
                    UINT16 SignatureType : 3; /* bit position: 4 */
                    UINT16 Unused : 9; /* bit position: 7 */
                };
                UINT16 EntireField;
            }; /* size: 0x0002 */
        }u1;
        VOID* SectionPointer;
        UINT32 CheckSum;
        UINT32 CoverageSectionSize;
        VOID* CoverageSection;
        VOID* LoadedImports;
        VOID* Spare;
        UINT32 SizeOfImageNotRounded;
        UINT32 TimeDateStamp;
    } KLDR_DATA_TABLE_ENTRY, *PKLDR_DATA_TABLE_ENTRY; /* size: 0x00a0 */ /* size: 0x005c */
    static_assert(sizeof(KLDR_DATA_TABLE_ENTRY) == (sizeof(SIZE_T) == sizeof(UINT64) ? 0xA0 : 0x5C));
#pragma endregion
       

#pragma region Lock
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


#pragma region Execute Options
    typedef union _KEXECUTE_OPTIONS
    {
        union
        {
            struct
            {
                UINT8 ExecuteDisable : 1; /* bit position: 0 */
                UINT8 ExecuteEnable : 1; /* bit position: 1 */
                UINT8 DisableThunkEmulation : 1; /* bit position: 2 */
                UINT8 Permanent : 1; /* bit position: 3 */
                UINT8 ExecuteDispatchEnable : 1; /* bit position: 4 */
                UINT8 ImageDispatchEnable : 1; /* bit position: 5 */
                UINT8 DisableExceptionChainValidation : 1; /* bit position: 6 */
                UINT8 Spare : 1; /* bit position: 7 */
            };
            volatile UINT8 ExecuteOptions;
            UINT8 ExecuteOptionsNV;
        }; /* size: 0x0001 */
    } KEXECUTE_OPTIONS, *PKEXECUTE_OPTIONS; /* size: 0x0001 */
    static_assert(sizeof(KEXECUTE_OPTIONS) == 0x0001);
#pragma endregion


#pragma region Stack
    typedef union _KSTACK_COUNT
    {
        union
        {
            INT32 Value;
            struct
            {
                UINT32 State : 3; /* bit position: 0 */
                UINT32 StackCount : 29; /* bit position: 3 */
            };
        };
    } KSTACK_COUNT, *PKSTACK_COUNT; /* size: 0x0004 */
    static_assert(sizeof(KSTACK_COUNT) == 0x0004);
#pragma endregion


#pragma region GDT & IDT
    typedef struct _KGDTENTRY
    {
        UINT16 LimitLow;
        UINT16 BaseLow;
        union
        {
            union
            {
                struct
                {
                    UINT8 BaseMid;
                    UINT8 Flags1;
                    UINT8 Flags2;
                    UINT8 BaseHi;
                } /* size: 0x0004 */ Bytes;
                struct
                {
                    struct
                    {
                        UINT32 BaseMid : 8; /* bit position: 0 */
                        UINT32 Type : 5; /* bit position: 8 */
                        UINT32 Dpl : 2; /* bit position: 13 */
                        UINT32 Pres : 1; /* bit position: 15 */
                        UINT32 LimitHi : 4; /* bit position: 16 */
                        UINT32 Sys : 1; /* bit position: 20 */
                        UINT32 Reserved_0 : 1; /* bit position: 21 */
                        UINT32 Default_Big : 1; /* bit position: 22 */
                        UINT32 Granularity : 1; /* bit position: 23 */
                        UINT32 BaseHi : 8; /* bit position: 24 */
                    };
                } /* size: 0x0004 */ Bits;
            }; /* size: 0x0004 */
        } /* size: 0x0004 */ HighWord;
    } KGDTENTRY, *PKGDTENTRY; /* size: 0x0008 */
    static_assert(sizeof(KGDTENTRY) == 0x0008);


    typedef union _KGDTENTRY64
    {
        union
        {
            struct
            {
                UINT16 LimitLow;
                UINT16 BaseLow;
                union
                {
                    struct
                    {
                        UINT8 BaseMiddle;
                        UINT8 Flags1;
                        UINT8 Flags2;
                        UINT8 BaseHigh;
                    } /* size: 0x0004 */ Bytes;
                    struct
                    {
                        struct
                        {
                            struct
                            {
                                UINT32 BaseMiddle : 8; /* bit position: 0 */
                                UINT32 Type : 5; /* bit position: 8 */
                                UINT32 Dpl : 2; /* bit position: 13 */
                                UINT32 Present : 1; /* bit position: 15 */
                                UINT32 LimitHigh : 4; /* bit position: 16 */
                                UINT32 System : 1; /* bit position: 20 */
                                UINT32 LongMode : 1; /* bit position: 21 */
                                UINT32 DefaultBig : 1; /* bit position: 22 */
                                UINT32 Granularity : 1; /* bit position: 23 */
                                UINT32 BaseHigh : 8; /* bit position: 24 */
                            };
                        } /* size: 0x0004 */ Bits;
                        UINT32 BaseUpper;
                        UINT32 MustBeZero;
                    }; /* size: 0x000c */
                }; /* size: 0x000c */
            }; /* size: 0x0010 */
            struct
            {
                INT64 DataLow;
                INT64 DataHigh;
            }; /* size: 0x0010 */
        }; /* size: 0x0010 */
    } KGDTENTRY64, *PKGDTENTRY64; /* size: 0x0010 */
    static_assert(sizeof(KGDTENTRY64) == 0x0010);


    typedef struct _KIDTENTRY
    {
        UINT16 Offset;
        UINT16 Selector;
        UINT16 Access;
        UINT16 ExtendedOffset;
    } KIDTENTRY, *PKIDTENTRY; /* size: 0x0008 */
    static_assert(sizeof(KIDTENTRY) == 0x0008);


    typedef union _KIDTENTRY64
    {
        union
        {
            struct
            {
                UINT16 OffsetLow;
                UINT16 Selector;
                struct /* bitfield */
                {
                    UINT16 IstIndex : 3; /* bit position: 0 */
                    UINT16 Reserved0 : 5; /* bit position: 3 */
                    UINT16 Type : 5; /* bit position: 8 */
                    UINT16 Dpl : 2; /* bit position: 13 */
                    UINT16 Present : 1; /* bit position: 15 */
                }; /* bitfield */
                UINT16 OffsetMiddle;
                UINT32 OffsetHigh;
                UINT32 Reserved1;
            }; /* size: 0x0010 */
            UINT64 Alignment;
        }; /* size: 0x0010 */
    } KIDTENTRY64, *PKIDTENTRY64; /* size: 0x0010 */
    static_assert(sizeof(KIDTENTRY64) == 0x0010);
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
