#pragma once


/*
 * PDB file: \Nt-Crucial-Modules\Ntoskrnl\10.0.17763.55\
 * Dumped by pdbex tool v0.4, by wbenny
 */


namespace wdk::build_17763
{

    SameDefine$(build_17134, KTHREAD);


    typedef struct _ETHREAD
    {
        struct _KTHREAD Tcb;
        union _LARGE_INTEGER CreateTime;
        union
        {
            union _LARGE_INTEGER ExitTime;
            struct _LIST_ENTRY KeyedWaitChain;
        };
#ifdef _X86_
        VOID* ChargeOnlySession;
#endif
        union
        {
            struct _LIST_ENTRY PostBlockList;
            struct
            {
                VOID* ForwardLinkShadow;
                VOID* StartAddress;
            };
        };
        union
        {
            struct _TERMINATION_PORT* TerminationPort;
            struct _ETHREAD* ReaperLink;
            VOID* KeyedWaitValue;
        };
        SIZE_T ActiveTimerListLock;
        struct _LIST_ENTRY ActiveTimerListHead;
        struct _CLIENT_ID Cid;
        union
        {
            struct _KSEMAPHORE KeyedWaitSemaphore;
            struct _KSEMAPHORE AlpcWaitSemaphore;
        };
        union _PS_CLIENT_SECURITY_CONTEXT ClientSecurity;
        struct _LIST_ENTRY IrpList;
        SIZE_T TopLevelIrp;
        struct _DEVICE_OBJECT* DeviceToVerify;
        VOID* Win32StartAddress;
#ifdef _WIN64
        VOID* ChargeOnlySession;
#endif
        VOID* LegacyPowerObject;
        struct _LIST_ENTRY ThreadListEntry;
        struct _EX_RUNDOWN_REF RundownProtect;
        struct _EX_PUSH_LOCK ThreadLock;
        UINT32 ReadClusterSize;
        volatile INT32 MmLockOrdering;
        union
        {
            UINT32 CrossThreadFlags;
            struct /* bitfield */
            {
                UINT32 Terminated : 1; /* bit position: 0 */
                UINT32 ThreadInserted : 1; /* bit position: 1 */
                UINT32 HideFromDebugger : 1; /* bit position: 2 */
                UINT32 ActiveImpersonationInfo : 1; /* bit position: 3 */
                UINT32 HardErrorsAreDisabled : 1; /* bit position: 4 */
                UINT32 BreakOnTermination : 1; /* bit position: 5 */
                UINT32 SkipCreationMsg : 1; /* bit position: 6 */
                UINT32 SkipTerminationMsg : 1; /* bit position: 7 */
                UINT32 CopyTokenOnOpen : 1; /* bit position: 8 */
                UINT32 ThreadIoPriority : 3; /* bit position: 9 */
                UINT32 ThreadPagePriority : 3; /* bit position: 12 */
                UINT32 RundownFail : 1; /* bit position: 15 */
                UINT32 UmsForceQueueTermination : 1; /* bit position: 16 */
                UINT32 IndirectCpuSets : 1; /* bit position: 17 */
                UINT32 DisableDynamicCodeOptOut : 1; /* bit position: 18 */
                UINT32 ExplicitCaseSensitivity : 1; /* bit position: 19 */
                UINT32 PicoNotifyExit : 1; /* bit position: 20 */
                UINT32 DbgWerUserReportActive : 1; /* bit position: 21 */
                UINT32 ForcedSelfTrimActive : 1; /* bit position: 22 */
                UINT32 SamplingCoverage : 1; /* bit position: 23 */
                UINT32 ReservedCrossThreadFlags : 8; /* bit position: 24 */
            }; /* bitfield */
        }; /* size: 0x0004 */
        union
        {
            UINT32 SameThreadPassiveFlags;
            struct /* bitfield */
            {
                UINT32 ActiveExWorker : 1; /* bit position: 0 */
                UINT32 MemoryMaker : 1; /* bit position: 1 */
                UINT32 StoreLockThread : 2; /* bit position: 2 */
                UINT32 ClonedThread : 1; /* bit position: 4 */
                UINT32 KeyedEventInUse : 1; /* bit position: 5 */
                UINT32 SelfTerminate : 1; /* bit position: 6 */
                UINT32 RespectIoPriority : 1; /* bit position: 7 */
                UINT32 ActivePageLists : 1; /* bit position: 8 */
                UINT32 SecureContext : 1; /* bit position: 9 */
                UINT32 ZeroPageThread : 1; /* bit position: 10 */
                UINT32 WorkloadClass : 1; /* bit position: 11 */
                UINT32 ReservedSameThreadPassiveFlags : 20; /* bit position: 12 */
            }; /* bitfield */
        }; /* size: 0x0004 */
        union
        {
            UINT32 SameThreadApcFlags;
            struct
            {
                struct /* bitfield */
                {
                    UINT8 OwnsProcessAddressSpaceExclusive : 1; /* bit position: 0 */
                    UINT8 OwnsProcessAddressSpaceShared : 1; /* bit position: 1 */
                    UINT8 HardFaultBehavior : 1; /* bit position: 2 */
                    volatile UINT8 StartAddressInvalid : 1; /* bit position: 3 */
                    UINT8 EtwCalloutActive : 1; /* bit position: 4 */
                    UINT8 SuppressSymbolLoad : 1; /* bit position: 5 */
                    UINT8 Prefetching : 1; /* bit position: 6 */
                    UINT8 OwnsVadExclusive : 1; /* bit position: 7 */
                }; /* bitfield */
                struct /* bitfield */
                {
                    UINT8 SystemPagePriorityActive : 1; /* bit position: 0 */
                    UINT8 SystemPagePriority : 3; /* bit position: 1 */
                    UINT8 AllowWritesToExecutableMemory : 1; /* bit position: 4 */
                    UINT8 OwnsVadShared : 1; /* bit position: 5 */
                }; /* bitfield */
            }; /* size: 0x0002 */
        }; /* size: 0x0004 */
        UINT8 CacheManagerActive;
        UINT8 DisablePageFaultClustering;
        UINT8 ActiveFaultCount;
        UINT8 LockOrderState;
        SIZE_T AlpcMessageId;
        union
        {
            VOID* AlpcMessage;
            UINT32 AlpcReceiveAttributeSet;
        };
        struct _LIST_ENTRY AlpcWaitListEntry;
        INT32 ExitStatus;
        UINT32 CacheManagerCount;
        UINT32 IoBoostCount;
        UINT32 IoQoSBoostCount;
        UINT32 IoQoSThrottleCount;
        UINT32 KernelStackReference;
        struct _LIST_ENTRY BoostList;
        struct _LIST_ENTRY DeboostList;
        EX_PUSH_LOCK BoostListLock;
        EX_PUSH_LOCK IrpListLock;
        VOID* ReservedForSynchTracking;
        struct _SINGLE_LIST_ENTRY CmCallbackListHead;
        const struct _GUID* ActivityId;
        struct _SINGLE_LIST_ENTRY SeLearningModeListHead;
        VOID* VerifierContext;
        VOID* AdjustedClientToken;
        VOID* WorkOnBehalfThread;
        struct _PS_PROPERTY_SET PropertySet;
        VOID* PicoContext;
        SIZE_T UserFsBase;
        SIZE_T UserGsBase;
        struct _THREAD_ENERGY_VALUES* EnergyValues;
        VOID* CmDbgInfo;
        union
        {
            SIZE_T SelectedCpuSets;
            SIZE_T* SelectedCpuSetsIndirect;
        };
        struct _EJOB* Silo;
        struct _UNICODE_STRING* ThreadName;
#ifdef _WIN64
        struct _CONTEXT* SetContextState;
#endif
        UINT32 LastExpectedRunTime;
        UINT32 HeapData;
        struct _LIST_ENTRY OwnerEntryListHead;
        SIZE_T DisownedOwnerEntryListLock;
        struct _LIST_ENTRY DisownedOwnerEntryListHead;
    } ETHREAD, *PETHREAD; /* size: 0x0810 */ /* size: 0x0480 */
    static_assert(sizeof(ETHREAD) == (sizeof(SIZE_T) == sizeof(UINT64) ? 0x0810 : 0x0480));


}
