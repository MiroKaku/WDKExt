#pragma once
#include "MmStruct.inl"
#include "KeStruct.inl"
#include "TsStruct.inl"


namespace wdk
{

    constexpr char      WOW64_SYSTEM_DIRECTORY[]    = "SysWOW64";
    constexpr wchar_t   WOW64_SYSTEM_DIRECTORY_U[]  = L"SysWOW64";
    constexpr char      WOW64_X86_TAG[]             = " (x86)";
    constexpr wchar_t   WOW64_X86_TAG_U[]           = L" (x86)";

    constexpr UNICODE_STRING PsNtDllPathName        = RTL_CONSTANT_STRING(L"\\SystemRoot\\System32\\ntdll.dll");
    

#pragma region AccessMask
    enum PsAccessMask : ACCESS_MASK
    {
        ProcessTerminate        = 0x0001,
        ProcessCreateThread     = 0x0002,
        ProcessSetSessionId     = 0x0004,
        ProcessVmOperation      = 0x0008,
        ProcessVmRead           = 0x0010,
        ProcessVmWrite          = 0x0020,
        ProcessDuplicateHandle  = 0x0040,
        ProcessCreateProcess    = 0x0080,
        ProcessSetQuota         = 0x0100,
        ProcessSetInformation   = 0x0200,
        ProcessQueryInformation = 0x0400,
        ProcessSuspendResume    = 0x0800,
        ProcessSetPort          = 0x0800,
        ProcessQueryLimitedInformation = 0x1000,
        ProcessAllAccess        = (StandardRightsRequired | Synchronize | 0xFFFF)
    };


    enum JobAccessMask : ACCESS_MASK
    {
        JobObjectAssignProcess = 0x0001,
        JobObjectSetAttributes = 0x0002,
        JobObjectQuery = 0x0004,
        JobObjectTerminate = 0x0008,
        JobObjectSetSecurityAttribute = 0x0010,
        JobObjectAllAccess = (StandardRightsRequired | Synchronize | 0x1F)
    };
#pragma endregion


#pragma region Process
    typedef enum _PS_PROTECTED_TYPE : UINT8
    {
        PsProtectedTypeNone,
        PsProtectedTypeProtectedLight,
        PsProtectedTypeProtected,
        PsProtectedTypeMax
    } PS_PROTECTED_TYPE;

    typedef enum _PS_PROTECTED_SIGNER : UINT8
    {
        PsProtectedSignerNone,
        PsProtectedSignerAuthenticode,
        PsProtectedSignerCodeGen,
        PsProtectedSignerAntimalware,
        PsProtectedSignerLsa,
        PsProtectedSignerWindows,
        PsProtectedSignerWinTcb,
        PsProtectedSignerWinSystem,
        PsProtectedSignerApp,
        PsProtectedSignerMax
    } PS_PROTECTED_SIGNER;

    enum PsProtectedMask : UINT8
    {
        PsProtectedSignerMask   = 0xFF,
        PsProtectedAuditMask    = 0x08,
        PsProtectedTypeMask     = 0x07,
    };

    typedef struct _PS_PROTECTION
    {
        union
        {
            UINT8 Level;
            struct
            {
                UINT8 Type  : 3;
                UINT8 Audit : 1;
                UINT8 Signer: 4;
            };
        };
    } PS_PROTECTION, *PPS_PROTECTION;


    typedef union _PS_INTERLOCKED_TIMER_DELAY_VALUES
    {
        union
        {
            struct /* bitfield */
            {
                UINT64 DelayMs : 30; /* bit position: 0 */
                UINT64 CoalescingWindowMs : 30; /* bit position: 30 */
                UINT64 Reserved : 1; /* bit position: 60 */
                UINT64 NewTimerWheel : 1; /* bit position: 61 */
                UINT64 Retry : 1; /* bit position: 62 */
                UINT64 Locked : 1; /* bit position: 63 */
            }; /* bitfield */
            UINT64 All;
        }; /* size: 0x0008 */
    } PS_INTERLOCKED_TIMER_DELAY_VALUES, *PPS_INTERLOCKED_TIMER_DELAY_VALUES; /* size: 0x0008 */


    typedef struct _JOBOBJECT_WAKE_FILTER
    {
        ULONG HighEdgeFilter;
        ULONG LowEdgeFilter;
    } JOBOBJECT_WAKE_FILTER, *PJOBOBJECT_WAKE_FILTER;

    typedef struct _PS_PROCESS_WAKE_INFORMATION
    {
        UINT64 NotificationChannel;
        UINT32 WakeCounters[7];
        struct _JOBOBJECT_WAKE_FILTER WakeFilter;
        UINT32 NoWakeCounter;
    } PS_PROCESS_WAKE_INFORMATION, *PPS_PROCESS_WAKE_INFORMATION; /* size: 0x0030 */
    static_assert(sizeof(PS_PROCESS_WAKE_INFORMATION) == 0x0030);


    typedef struct _SE_AUDIT_PROCESS_CREATION_INFO
    {
        struct _OBJECT_NAME_INFORMATION* ImageFileName;
    } SE_AUDIT_PROCESS_CREATION_INFO, *PSE_AUDIT_PROCESS_CREATION_INFO;


    typedef struct _ALPC_PROCESS_CONTEXT
    {
        struct _EX_PUSH_LOCK Lock;
        struct _LIST_ENTRY ViewListHead;
        volatile SIZE_T PagedPoolQuotaCache;
    } ALPC_PROCESS_CONTEXT, *PALPC_PROCESS_CONTEXT; /* size: 0x0020 */ /* size: 0x0010 */
    static_assert(sizeof(ALPC_PROCESS_CONTEXT) == (sizeof(SIZE_T) == sizeof(UINT64) ? 0x0020 : 0x0010));


    enum PsProcessFlagMask : UINT32
    {
        PsProcessFlagsCreateReported = 0x00000001,
        PsProcessFlagsNoDebugInherit = 0x00000002,
        PsProcessFlagsProcessExiting = 0x00000004,
        PsProcessFlagsProcessDelete  = 0x00000008,
        
        // ...
    };
#pragma endregion
    

#pragma region Ldr
    // General part
    template<typename T = PVOID>
    struct LDR_DATA_TABLE_ENTRY_T
    {
        using LIST_ENTRY     = LIST_ENTRY_T<T>;
        using UNICODE_STRING = T_STRING<T>;

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
                UINT32 PackagedBinary : 1; /* bit position: 0 */
                UINT32 MarkedForRemoval : 1; /* bit position: 1 */
                UINT32 ImageDll : 1; /* bit position: 2 */
                UINT32 LoadNotificationsSent : 1; /* bit position: 3 */
                UINT32 TelemetryEntryProcessed : 1; /* bit position: 4 */
                UINT32 ProcessStaticImport : 1; /* bit position: 5 */
                UINT32 InLegacyLists : 1; /* bit position: 6 */
                UINT32 InIndexes : 1; /* bit position: 7 */
                UINT32 ShimDll : 1; /* bit position: 8 */
                UINT32 InExceptionTable : 1; /* bit position: 9 */
                UINT32 ReservedFlags1 : 2; /* bit position: 10 */
                UINT32 LoadInProgress : 1; /* bit position: 12 */
                UINT32 LoadConfigProcessed : 1; /* bit position: 13 */
                UINT32 EntryProcessed : 1; /* bit position: 14 */
                UINT32 ProtectDelayLoad : 1; /* bit position: 15 */
                UINT32 ReservedFlags3 : 2; /* bit position: 16 */
                UINT32 DontCallForThreads : 1; /* bit position: 18 */
                UINT32 ProcessAttachCalled : 1; /* bit position: 19 */
                UINT32 ProcessAttachFailed : 1; /* bit position: 20 */
                UINT32 CorDeferredValidate : 1; /* bit position: 21 */
                UINT32 CorImage : 1; /* bit position: 22 */
                UINT32 DontRelocate : 1; /* bit position: 23 */
                UINT32 CorILOnly : 1; /* bit position: 24 */
                UINT32 ChpeImage : 1; /* bit position: 25 */
                UINT32 ReservedFlags5 : 2; /* bit position: 26 */
                UINT32 Redirected : 1; /* bit position: 28 */
                UINT32 ReservedFlags6 : 2; /* bit position: 29 */
                UINT32 CompatDatabaseProcessed : 1; /* bit position: 31 */
            };
        };
        UINT16      ObsoleteLoadCount;
        UINT16      TlsIndex;
        LIST_ENTRY  HashLinks;
        UINT32      TimeDateStamp;
    };
    using LDR_DATA_TABLE_ENTRY   = LDR_DATA_TABLE_ENTRY_T<PVOID>;
    using LDR_DATA_TABLE_ENTRY32 = LDR_DATA_TABLE_ENTRY_T<PVOID32>;
    using LDR_DATA_TABLE_ENTRY64 = LDR_DATA_TABLE_ENTRY_T<PVOID64>;

    using PLDR_DATA_TABLE_ENTRY   = LDR_DATA_TABLE_ENTRY *;
    using PLDR_DATA_TABLE_ENTRY32 = LDR_DATA_TABLE_ENTRY32 * ;
    using PLDR_DATA_TABLE_ENTRY64 = LDR_DATA_TABLE_ENTRY64 * ;

    static_assert(sizeof(LDR_DATA_TABLE_ENTRY32) == 0x0048);
    static_assert(sizeof(LDR_DATA_TABLE_ENTRY64) == 0x0088);


    template<typename T = PVOID>
    struct PEB_LDR_DATA_T
    {
        using LIST_ENTRY = LIST_ENTRY_T<T>;

        UINT32      Length;
        UINT8       Initialized;
        T           SsHandle;
        LIST_ENTRY  InLoadOrderModuleList;
        LIST_ENTRY  InMemoryOrderModuleList;
        LIST_ENTRY  InInitializationOrderModuleList;
        T           EntryInProgress;
        UINT8       ShutdownInProgress;
        T           ShutdownThreadId;
    };
    using PEB_LDR_DATA   = PEB_LDR_DATA_T<PVOID>;
    using PEB_LDR_DATA32 = PEB_LDR_DATA_T<PVOID32>;
    using PEB_LDR_DATA64 = PEB_LDR_DATA_T<PVOID64>;

    using PPEB_LDR_DATA   = PEB_LDR_DATA * ;
    using PPEB_LDR_DATA32 = PEB_LDR_DATA32 * ;
    using PPEB_LDR_DATA64 = PEB_LDR_DATA64 * ;

    static_assert(sizeof(PEB_LDR_DATA32) == 0x0030);
    static_assert(sizeof(PEB_LDR_DATA64) == 0x0058);
#pragma endregion


#pragma region General PEB
    enum : UINT32
    {
        GdiHandleBufferSizeX86 = 34,
        GdiHandleBufferSizeX64 = 60,
        GdiHandleBufferSize    = sizeof(SIZE_T) == sizeof(UINT64) ? GdiHandleBufferSizeX64 : GdiHandleBufferSizeX86 
    };

    enum : UINT32
    {
        FlsMaximumAvailable = 128,
        TlsMinimumAvailable = 64,
        TlsExpansionSlots   = 1024,
    };

    using PPS_POST_PROCESS_INIT_ROUTINE = VOID(NTAPI*)(VOID);

    template<typename T = PVOID, typename I = SIZE_T, UINT32 GDI_BUFF_SIZE = GdiHandleBufferSize>
    struct PEB_T
    {
        using UNICODE_STRING = T_STRING<T>;
        using LIST_ENTRY = LIST_ENTRY_T<T>;

        UINT8 InheritedAddressSpace;
        UINT8 ReadImageFileExecOptions;
        UINT8 BeingDebugged;
        union
        {
            UINT8 BitField;
            struct /* bitfield */
            {
                UINT8 ImageUsesLargePages : 1; /* bit position: 0 */
                UINT8 IsProtectedProcess : 1; /* bit position: 1 */
                UINT8 IsImageDynamicallyRelocated : 1; /* bit position: 2 */
                UINT8 SkipPatchingUser32Forwarders : 1; /* bit position: 3 */
                UINT8 IsPackagedProcess : 1; /* bit position: 4 */
                UINT8 IsAppContainer : 1; /* bit position: 5 */
                UINT8 IsProtectedProcessLight : 1; /* bit position: 6 */
                UINT8 IsLongPathAwareProcess : 1; /* bit position: 7 */
            }; /* bitfield */
        }; /* size: 0x0001 */
        T Mutant;
        T ImageBaseAddress;
        T /*struct _PEB_LDR_DATA**/ Ldr;
        T /*struct _RTL_USER_PROCESS_PARAMETERS**/ ProcessParameters;
        T SubSystemData;
        T ProcessHeap;
        T /*struct _RTL_CRITICAL_SECTION**/ FastPebLock;
        T /*union _SLIST_HEADER**/ volatile AtlThunkSListPtr;
        T IFEOKey;
        union
        {
            UINT32 CrossProcessFlags;
            struct /* bitfield */
            {
                UINT32 ProcessInJob : 1; /* bit position: 0 */
                UINT32 ProcessInitializing : 1; /* bit position: 1 */
                UINT32 ProcessUsingVEH : 1; /* bit position: 2 */
                UINT32 ProcessUsingVCH : 1; /* bit position: 3 */
                UINT32 ProcessUsingFTH : 1; /* bit position: 4 */
                UINT32 ProcessPreviouslyThrottled : 1; /* bit position: 5 */
                UINT32 ProcessCurrentlyThrottled : 1; /* bit position: 6 */
                UINT32 ProcessImagesHotPatched : 1; /* bit position: 7 */
                UINT32 ReservedBits0 : 24; /* bit position: 8 */
            }; /* bitfield */
        }; /* size: 0x0004 */
        union
        {
            T KernelCallbackTable;
            T UserSharedInfoPtr;
        };
        UINT32 SystemReserved;
        UINT32 AtlThunkSListPtr32;
        T ApiSetMap;
        UINT32 TlsExpansionCounter;
        T TlsBitmap;
        UINT32 TlsBitmapBits[2];
        T ReadOnlySharedMemoryBase;
        T SharedData;
        T /*VOID***/ ReadOnlyStaticServerData;
        T AnsiCodePageData;
        T OemCodePageData;
        T UnicodeCaseTableData;
        UINT32 NumberOfProcessors;
        UINT32 NtGlobalFlag;
        union _LARGE_INTEGER CriticalSectionTimeout;
        I HeapSegmentReserve;
        I HeapSegmentCommit;
        I HeapDeCommitTotalFreeThreshold;
        I HeapDeCommitFreeBlockThreshold;
        UINT32 NumberOfHeaps;
        UINT32 MaximumNumberOfHeaps;
        T /*VOID***/ ProcessHeaps;
        T GdiSharedHandleTable;
        T ProcessStarterHelper;
        UINT32 GdiDCAttributeList;
        T /*struct _RTL_CRITICAL_SECTION**/ LoaderLock;
        UINT32 OSMajorVersion;
        UINT32 OSMinorVersion;
        UINT16 OSBuildNumber;
        UINT16 OSCSDVersion;
        UINT32 OSPlatformId;
        UINT32 ImageSubsystem;
        UINT32 ImageSubsystemMajorVersion;
        UINT32 ImageSubsystemMinorVersion;
        I ActiveProcessAffinityMask;
        UINT32 GdiHandleBuffer[GDI_BUFF_SIZE];
        T /*PPS_POST_PROCESS_INIT_ROUTINE*/  PostProcessInitRoutine /* function */;
        T TlsExpansionBitmap;
        UINT32 TlsExpansionBitmapBits[32];
        UINT32 SessionId;
        union _ULARGE_INTEGER AppCompatFlags;
        union _ULARGE_INTEGER AppCompatFlagsUser;
        T pShimData;
        T AppCompatInfo;
        UNICODE_STRING CSDVersion;
        const T /*struct _ACTIVATION_CONTEXT_DATA**/ ActivationContextData;
        T /*struct _ASSEMBLY_STORAGE_MAP**/ ProcessAssemblyStorageMap;
        const T /*struct _ACTIVATION_CONTEXT_DATA**/ SystemDefaultActivationContextData;
        T /*struct _ASSEMBLY_STORAGE_MAP**/ SystemAssemblyStorageMap;
        I MinimumStackCommit;
        T /*struct _FLS_CALLBACK_INFO**/ FlsCallback;
        LIST_ENTRY FlsListHead;
        T FlsBitmap;
        UINT32 FlsBitmapBits[4];
        UINT32 FlsHighIndex;
        T WerRegistrationData;
        T WerShipAssertPtr;
        T pUnused;
        T pImageHeaderHash;
        union
        {
            UINT32 TracingFlags;
            struct /* bitfield */
            {
                UINT32 HeapTracingEnabled : 1; /* bit position: 0 */
                UINT32 CritSecTracingEnabled : 1; /* bit position: 1 */
                UINT32 LibLoaderTracingEnabled : 1; /* bit position: 2 */
                UINT32 SpareTracingBits : 29; /* bit position: 3 */
            }; /* bitfield */
        }; /* size: 0x0004 */
    }; /* size: 0x0380 */ /* size: 0x0248 */

    using PEB   = PEB_T<PVOID, SIZE_T, GdiHandleBufferSize>;
    using PEB32 = PEB_T<PVOID32, UINT32, GdiHandleBufferSizeX86>;
    using PEB64 = PEB_T<PVOID64, UINT64, GdiHandleBufferSizeX64>;

    using PPEB   = PEB * ;
    using PPEB32 = PEB32 * ;
    using PPEB64 = PEB64 * ;

    static_assert(sizeof(PEB32) == 0x0248);
    static_assert(sizeof(PEB64) == 0x0380);
#pragma endregion


}

#include "Ps\build_7600.inl"
#include "Ps\build_7601.inl"
#include "Ps\build_9200.inl"
#include "Ps\build_9600.inl"
#include "Ps\build_10240.inl"
#include "Ps\build_10586.inl"
#include "Ps\build_14393.inl"
#include "Ps\build_15063.inl"
#include "Ps\build_16299.inl"
#include "Ps\build_17134.inl"
#include "Ps\build_17763.inl"
