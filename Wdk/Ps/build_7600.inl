#pragma once


/*
 * PDB file: \Nt-Crucial-Modules\Ntoskrnl\6.1.7600.17795\
 * Dumped by pdbex tool v0.4, by wbenny
 */


namespace wdk::build_7600
{


    enum : UINT32
    {
        NumberOfProcessor32 = 1,
        NumberOfProcessor64 = 4,

        NumberOfProcessor = (sizeof(PVOID) == sizeof(UINT32)) ? NumberOfProcessor32 : NumberOfProcessor64,
    };


    typedef struct _KAFFINITY_EX
    {
        UINT16 Count;
        UINT16 Size;
        UINT32 Reserved;
        SIZE_T Bitmap[NumberOfProcessor];
    } KAFFINITY_EX, *PKAFFINITY_EX;
    static_assert(sizeof(KAFFINITY_EX) == (sizeof(SIZE_T) == sizeof(UINT64) ? 0x28 : 0xC));


    typedef struct _KPROCESS
    {
        struct _DISPATCHER_HEADER Header;
        struct _LIST_ENTRY ProfileListHead;
        SIZE_T DirectoryTableBase;
#ifdef _X86_
        struct _KGDTENTRY LdtDescriptor;
        struct _KIDTENTRY Int21Descriptor;
#endif
        struct _LIST_ENTRY ThreadListHead;
        SIZE_T ProcessLock;
        struct _KAFFINITY_EX Affinity;
        struct _LIST_ENTRY ReadyListHead;
        struct _SINGLE_LIST_ENTRY SwapListEntry;
        volatile struct _KAFFINITY_EX ActiveProcessors;
        union
        {
            struct /* bitfield */
            {
                volatile INT32 AutoAlignment : 1; /* bit position: 0 */
                volatile INT32 DisableBoost : 1; /* bit position: 1 */
                volatile INT32 DisableQuantum : 1; /* bit position: 2 */
                volatile UINT32 ActiveGroupsMask : NumberOfProcessor; /* bit position: 3 */
                volatile INT32 ReservedFlags : sizeof(UINT32) * 8 - 3 - NumberOfProcessor; /* bit position: 7 */ /* bit position: 4 */
            }; /* bitfield */
            volatile INT32 ProcessFlags;
        }; /* size: 0x0004 */
        CHAR BasePriority;
        CHAR QuantumReset;
        UINT8 Visited;
        UINT8 Unused3;
        UINT32 ThreadSeed[NumberOfProcessor];
        UINT16 IdealNode[NumberOfProcessor];
        UINT16 IdealGlobalNode;
        union _KEXECUTE_OPTIONS Flags;
        UINT8 Unused1;
#ifdef _WIN64
        UINT32 Unused2;
#else
        UINT16 IopmOffset;
#endif
        UINT32 Unused4;
        union _KSTACK_COUNT StackCount;
        struct _LIST_ENTRY ProcessListEntry;
        volatile UINT64 CycleTime;
        UINT32 KernelTime;
        UINT32 UserTime;
#ifdef _WIN64
        VOID* InstrumentationCallback;
        union _KGDTENTRY64 LdtSystemDescriptor;
        VOID* LdtBaseAddress;
        struct _KGUARDED_MUTEX LdtProcessLock;
        UINT16 LdtFreeSelectorHint;
        UINT16 LdtTableLength;
#else
        VOID* VdmTrapcHandler;
#endif  
    } KPROCESS, *PKPROCESS; /* size: 0x0160 */ /* size: 0x0098 */
    static_assert(sizeof(KPROCESS) == (sizeof(SIZE_T) == sizeof(UINT64) ? 0x0160 : 0x0098));


    typedef struct _EPROCESS
    {
        struct _KPROCESS Pcb;
        struct _EX_PUSH_LOCK ProcessLock;
#ifdef _X86_
        UINT32 Padding;
#endif
        union _LARGE_INTEGER CreateTime;
        union _LARGE_INTEGER ExitTime;
        struct _EX_RUNDOWN_REF RundownProtect;
        VOID* UniqueProcessId;
        struct _LIST_ENTRY ActiveProcessLinks;
        SIZE_T ProcessQuotaUsage[2];
        SIZE_T ProcessQuotaPeak[2];
        volatile SIZE_T CommitCharge;
        struct _EPROCESS_QUOTA_BLOCK* QuotaBlock;
        struct _PS_CPU_QUOTA_BLOCK* CpuQuotaBlock;
        SIZE_T PeakVirtualSize;
        SIZE_T VirtualSize;
        struct _LIST_ENTRY SessionProcessLinks;
        VOID* DebugPort;
        union
        {
            VOID*  ExceptionPortData;
            SIZE_T ExceptionPortValue : sizeof(SIZE_T) * 8 - 3;
            SIZE_T ExceptionPortState : 3; /* bit position: 0 */
        };
        struct _HANDLE_TABLE* ObjectTable;
        struct _EX_FAST_REF Token;
        SIZE_T WorkingSetPage;
        struct _EX_PUSH_LOCK AddressCreationLock;
        struct _ETHREAD* RotateInProgress;
        struct _ETHREAD* ForkInProgress;
        SIZE_T HardwareTrigger;
        struct _MM_AVL_TABLE* PhysicalVadRoot;
        VOID* CloneRoot;
        volatile SIZE_T NumberOfPrivatePages;
        volatile SIZE_T NumberOfLockedPages;
        VOID* Win32Process;
        struct _EJOB* volatile Job;
        VOID* SectionObject;
        VOID* SectionBaseAddress;
        UINT32 Cookie;
#ifdef _WIN64
        UINT32 UmsScheduledThreads;
#else
        UINT32 Spare8;
#endif
        struct _PAGEFAULT_HISTORY* WorkingSetWatch;
        VOID* Win32WindowStation;
        VOID* InheritedFromUniqueProcessId;
        VOID* LdtInformation;
#ifdef _WIN64
        VOID* Spare;
#else
        VOID* VdmObjects;
#endif
        SIZE_T ConsoleHostProcess;
        VOID* DeviceMap;
        VOID* EtwDataSource;
        VOID* FreeTebHint;
#ifdef _WIN64
        VOID* FreeUmsTebHint;
#endif
        union
        {
            struct _HARDWARE_PTE PageDirectoryPte;
            UINT64 Filler;
        }; /* size: 0x0008 */
        VOID* Session;
        UINT8 ImageFileName[15];
        UINT8 PriorityClass;
        struct _LIST_ENTRY JobLinks;
        VOID* LockedPagesList;
        struct _LIST_ENTRY ThreadListHead;
        VOID* SecurityPort;
#ifdef _WIN64
        VOID* Wow64Process;
#else
        VOID* PaeTop;
#endif
        volatile UINT32 ActiveThreads;
        UINT32 ImagePathHash;
        UINT32 DefaultHardErrorProcessing;
        INT32 LastThreadExitStatus;
        struct _PEB* Peb;
        struct _EX_FAST_REF PrefetchTrace;
        union _LARGE_INTEGER ReadOperationCount;
        union _LARGE_INTEGER WriteOperationCount;
        union _LARGE_INTEGER OtherOperationCount;
        union _LARGE_INTEGER ReadTransferCount;
        union _LARGE_INTEGER WriteTransferCount;
        union _LARGE_INTEGER OtherTransferCount;
        SIZE_T CommitChargeLimit;
        volatile SIZE_T CommitChargePeak;
        VOID* AweInfo;
        struct _SE_AUDIT_PROCESS_CREATION_INFO SeAuditProcessCreationInfo;
        struct _MMSUPPORT Vm;
        struct _LIST_ENTRY MmProcessLinks;
        VOID* HighestUserAddress;
        UINT32 ModifiedPageCount;
        union
        {
            UINT32 Flags2;
            struct /* bitfield */
            {
                UINT32 JobNotReallyActive : 1; /* bit position: 0 */
                UINT32 AccountingFolded : 1; /* bit position: 1 */
                UINT32 NewProcessReported : 1; /* bit position: 2 */
                UINT32 ExitProcessReported : 1; /* bit position: 3 */
                UINT32 ReportCommitChanges : 1; /* bit position: 4 */
                UINT32 LastReportMemory : 1; /* bit position: 5 */
                UINT32 ReportPhysicalPageChanges : 1; /* bit position: 6 */
                UINT32 HandleTableRundown : 1; /* bit position: 7 */
                UINT32 NeedsHandleRundown : 1; /* bit position: 8 */
                UINT32 RefTraceEnabled : 1; /* bit position: 9 */
                UINT32 NumaAware : 1; /* bit position: 10 */
                UINT32 ProtectedProcess : 1; /* bit position: 11 */
                UINT32 DefaultPagePriority : 3; /* bit position: 12 */
                UINT32 PrimaryTokenFrozen : 1; /* bit position: 15 */
                UINT32 ProcessVerifierTarget : 1; /* bit position: 16 */
                UINT32 StackRandomizationDisabled : 1; /* bit position: 17 */
                UINT32 AffinityPermanent : 1; /* bit position: 18 */
                UINT32 AffinityUpdateEnable : 1; /* bit position: 19 */
                UINT32 PropagateNode : 1; /* bit position: 20 */
                UINT32 ExplicitAffinity : 1; /* bit position: 21 */
                UINT32 Spare1 : 1; /* bit position: 22 */
                UINT32 ForceRelocateImages : 1; /* bit position: 23 */
                UINT32 DisallowStrippedImages : 1; /* bit position: 24 */
                UINT32 LowVaAccessible : 1; /* bit position: 25 */
            }; /* bitfield */
        }; /* size: 0x0004 */
        union
        {
            UINT32 Flags;
            struct /* bitfield */
            {
                UINT32 CreateReported : 1; /* bit position: 0 */
                UINT32 NoDebugInherit : 1; /* bit position: 1 */
                UINT32 ProcessExiting : 1; /* bit position: 2 */
                UINT32 ProcessDelete : 1; /* bit position: 3 */
                UINT32 Wow64SplitPages : 1; /* bit position: 4 */
                UINT32 VmDeleted : 1; /* bit position: 5 */
                UINT32 OutswapEnabled : 1; /* bit position: 6 */
                UINT32 Outswapped : 1; /* bit position: 7 */
                UINT32 ForkFailed : 1; /* bit position: 8 */
                UINT32 Wow64VaSpace4Gb : 1; /* bit position: 9 */
                UINT32 AddressSpaceInitialized : 2; /* bit position: 10 */
                UINT32 SetTimerResolution : 1; /* bit position: 12 */
                UINT32 BreakOnTermination : 1; /* bit position: 13 */
                UINT32 DeprioritizeViews : 1; /* bit position: 14 */
                UINT32 WriteWatch : 1; /* bit position: 15 */
                UINT32 ProcessInSession : 1; /* bit position: 16 */
                UINT32 OverrideAddressSpace : 1; /* bit position: 17 */
                UINT32 HasAddressSpace : 1; /* bit position: 18 */
                UINT32 LaunchPrefetched : 1; /* bit position: 19 */
                UINT32 InjectInpageErrors : 1; /* bit position: 20 */
                UINT32 VmTopDown : 1; /* bit position: 21 */
                UINT32 ImageNotifyDone : 1; /* bit position: 22 */
                UINT32 PdeUpdateNeeded : 1; /* bit position: 23 */
                UINT32 VdmAllowed : 1; /* bit position: 24 */
                UINT32 CrossSessionCreate : 1; /* bit position: 25 */
                UINT32 ProcessInserted : 1; /* bit position: 26 */
                UINT32 DefaultIoPriority : 3; /* bit position: 27 */
                UINT32 ProcessSelfDelete : 1; /* bit position: 30 */
                UINT32 SetTimerResolutionLink : 1; /* bit position: 31 */
            }; /* bitfield */
        }; /* size: 0x0004 */
        INT32 ExitStatus;
        struct _MM_AVL_TABLE VadRoot;
        struct _ALPC_PROCESS_CONTEXT AlpcContext;
        struct _LIST_ENTRY TimerResolutionLink;
        UINT32 RequestedTimerResolution;
        UINT32 ActiveThreadsHighWatermark;
        UINT32 SmallestTimerResolution;
        struct _PO_DIAG_STACK_RECORD* TimerResolutionStackRecord;
    } EPROCESS, *PEPROCESS; /* size: 0x04d0 */ /* size: 0x02c0 */
    static_assert(sizeof(EPROCESS) == (sizeof(SIZE_T) == sizeof(UINT64) ? 0x04d0 : 0x02c0));
    
}
