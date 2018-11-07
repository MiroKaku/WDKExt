#pragma once


/*
 * PDB file: \Nt-Crucial-Modules\Ntoskrnl\6.3.9600.19038\
 * Dumped by pdbex tool v0.4, by wbenny
 */


namespace wdk::build_9600
{


    typedef struct _KTHREAD
    {
        struct _DISPATCHER_HEADER Header;
        VOID* SListFaultAddress;
        UINT64 QuantumTarget;
        VOID* InitialStack;
        VOID* volatile StackLimit;
        VOID* StackBase;
        EX_PUSH_LOCK ThreadLock;
        volatile UINT64 CycleTime;
#ifdef _X86_
        volatile UINT32 HighCycleTime;
        VOID* ServiceTable;
#endif
        UINT32 CurrentRunTime;
        UINT32 ExpectedRunTime;
        VOID* KernelStack;
        struct _XSAVE_FORMAT* StateSaveArea;
        struct _KSCHEDULING_GROUP* volatile SchedulingGroup;
        union _KWAIT_STATUS_REGISTER WaitRegister;
        volatile UINT8 Running;
        UINT8 Alerted[MaximumMode];
        union
        {
            struct /* bitfield */
            {
                UINT32 SpareMiscFlag0 : 1; /* bit position: 0 */
                UINT32 ReadyTransition : 1; /* bit position: 1 */
                UINT32 ProcessReadyQueue : 1; /* bit position: 2 */
                UINT32 WaitNext : 1; /* bit position: 3 */
                UINT32 SystemAffinityActive : 1; /* bit position: 4 */
                UINT32 Alertable : 1; /* bit position: 5 */
                UINT32 UserStackWalkActive : 1; /* bit position: 6 */
                UINT32 ApcInterruptRequest : 1; /* bit position: 7 */
                UINT32 QuantumEndMigrate : 1; /* bit position: 8 */
                UINT32 UmsDirectedSwitchEnable : 1; /* bit position: 9 */
                UINT32 TimerActive : 1; /* bit position: 10 */
                UINT32 SystemThread : 1; /* bit position: 11 */
                UINT32 ProcessDetachActive : 1; /* bit position: 12 */
                UINT32 CalloutActive : 1; /* bit position: 13 */
                UINT32 ScbReadyQueue : 1; /* bit position: 14 */
                UINT32 ApcQueueable : 1; /* bit position: 15 */
                UINT32 ReservedStackInUse : 1; /* bit position: 16 */
                UINT32 UmsPerformingSyscall : 1; /* bit position: 17 */
                UINT32 ApcPendingReload : 1; /* bit position: 18 */
                UINT32 TimerSuspended : 1; /* bit position: 19 */
                UINT32 SuspendedWaitMode : 1; /* bit position: 20 */
                UINT32 Reserved : 11; /* bit position: 21 */
            }; /* bitfield */
            INT32 MiscFlags;
        }; /* size: 0x0004 */
        union
        {
            struct /* bitfield */
            {
                UINT32 AutoAlignment : 1; /* bit position: 0 */
                UINT32 DisableBoost : 1; /* bit position: 1 */
                UINT32 UserAffinitySet : 1; /* bit position: 2 */
                UINT32 AlertedByThreadId : 1; /* bit position: 3 */
                UINT32 QuantumDonation : 1; /* bit position: 4 */
                UINT32 EnableStackSwap : 1; /* bit position: 5 */
                UINT32 GuiThread : 1; /* bit position: 6 */
                UINT32 DisableQuantum : 1; /* bit position: 7 */
                UINT32 ChargeOnlySchedulingGroup : 1; /* bit position: 8 */
                UINT32 DeferPreemption : 1; /* bit position: 9 */
                UINT32 QueueDeferPreemption : 1; /* bit position: 10 */
                UINT32 ForceDeferSchedule : 1; /* bit position: 11 */
                UINT32 SharedReadyQueueAffinity : 1; /* bit position: 12 */
                UINT32 FreezeCount : 1; /* bit position: 13 */
                UINT32 TerminationApcRequest : 1; /* bit position: 14 */
                UINT32 AutoBoostEntriesExhausted : 1; /* bit position: 15 */
                UINT32 KernelStackResident : 1; /* bit position: 16 */
                UINT32 EtwStackTraceApcInserted : 8; /* bit position: 17 */
                UINT32 ReservedFlags : 7; /* bit position: 25 */
            }; /* bitfield */
            volatile INT32 ThreadFlags;
        }; /* size: 0x0004 */
        UINT32 Spare0;
        UINT32 SystemCallNumber;
#ifdef _WIN64
        UINT32 Spare1;
#endif
        VOID* FirstArgument;
        struct _KTRAP_FRAME* TrapFrame;
        union
        {
            struct _KAPC_STATE ApcState;
            struct
            {
                UINT8 ApcStateFill[ApcStateActualSize];
                CHAR Priority;
#ifdef _WIN64
                UINT32 UserIdealProcessor;
#endif
            };
        };
#ifdef _X86_
        UINT32 UserIdealProcessor;
        UINT32 ContextSwitches;
        volatile UINT8 State;
        CHAR NpxState;
        UINT8 WaitIrql;
        CHAR WaitMode;
#endif
        volatile SSIZE_T WaitStatus;
        struct _KWAIT_BLOCK* WaitBlockList;
        union
        {
            struct _LIST_ENTRY WaitListEntry;
            struct _SINGLE_LIST_ENTRY SwapListEntry;
        };
        struct _DISPATCHER_HEADER* volatile Queue;
        VOID* Teb;
        UINT64 RelativeTimerBias;
        struct _KTIMER Timer;
#ifdef _WIN64
        union
        {
            struct _KWAIT_BLOCK WaitBlock[THREAD_WAIT_OBJECTS + 1];
            struct
            {
                UINT8 WaitBlockFill4[WaitBlockOffsetToLong0];
                UINT32 ContextSwitches;
            }; /* size: 0x0018 */
            struct
            {
                UINT8 WaitBlockFill5[WaitBlockOffsetToLong1];
                volatile UINT8 State;
                CHAR NpxState;
                UINT8 WaitIrql;
                CHAR WaitMode;
            }; /* size: 0x0048 */
            struct
            {
                UINT8 WaitBlockFill6[WaitBlockOffsetToLong2];
                UINT32 WaitTime;
            }; /* size: 0x0078 */
            struct
            {
                UINT8 WaitBlockFill7[WaitBlockOffsetToLong3];
                union
                {
                    struct
                    {
                        INT16 KernelApcDisable;
                        INT16 SpecialApcDisable;
                    }; /* size: 0x0004 */
                    UINT32 CombinedApcDisable;
                }; /* size: 0x0004 */
            }; /* size: 0x00a8 */
            struct
            {
                UINT8 WaitBlockFill8[WaitBlockOffsetToPtr0];
                struct _KTHREAD_COUNTERS* ThreadCounters;
            }; /* size: 0x0030 */
            struct
            {
                UINT8 WaitBlockFill9[WaitBlockOffsetToPtr1];
                struct _XSTATE_SAVE* XStateSave;
            }; /* size: 0x0060 */
            struct
            {
                UINT8 WaitBlockFill10[WaitBlockOffsetToPtr2];
                VOID* volatile Win32Thread;
            }; /* size: 0x0090 */
            struct
            {
                UINT8 WaitBlockFill11[WaitBlockOffsetToObject3];
                struct _UMS_CONTROL_BLOCK* Ucb;
                struct _KUMS_CONTEXT_HEADER* volatile Uch;
            }; /* size: 0x00c0 */
        }; /* size: 0x00c0 */
        VOID* TebMappedLowVa;
#else
        union
        {
            struct _KWAIT_BLOCK WaitBlock[THREAD_WAIT_OBJECTS + 1];
            struct
            {
                UINT8 WaitBlockFill8[WaitBlockOffsetToPtr0];
                struct _KTHREAD_COUNTERS* ThreadCounters;
            }; /* size: 0x0018 */
            struct
            {
                UINT8 WaitBlockFill9[WaitBlockOffsetToPtr1];
                struct _XSTATE_SAVE* XStateSave;
            }; /* size: 0x0030 */
            struct
            {
                UINT8 WaitBlockFill10[WaitBlockOffsetToPtr2];
                VOID* volatile Win32Thread;
            }; /* size: 0x0048 */
            struct
            {
                UINT8 WaitBlockFill11[WaitBlockOffsetToObject3];
                UINT32 WaitTime;
                union
                {
                    struct
                    {
                        INT16 KernelApcDisable;
                        INT16 SpecialApcDisable;
                    }; /* size: 0x0004 */
                    UINT32 CombinedApcDisable;
                }; /* size: 0x0004 */
            }; /* size: 0x0060 */
        }; /* size: 0x0060 */
#endif
        struct _LIST_ENTRY QueueListEntry;
        union
        {
            volatile UINT32 NextProcessor;
            struct /* bitfield */
            {
                UINT32 NextProcessorNumber : 31; /* bit position: 0 */
                UINT32 SharedReadyQueue : 1; /* bit position: 31 */
            }; /* bitfield */
        }; /* size: 0x0004 */
        INT32 QueuePriority;
        struct _KPROCESS* Process;
        union
        {
            struct _GROUP_AFFINITY UserAffinity;
            struct
            {
                UINT8 UserAffinityFill[GroupAffinityFillSize];
                CHAR PreviousMode;
                CHAR BasePriority;
                union
                {
                    CHAR PriorityDecrement;
                    struct /* bitfield */
                    {
                        UINT8 ForegroundBoost : 4; /* bit position: 0 */
                        UINT8 UnusualBoost : 4; /* bit position: 4 */
                    }; /* bitfield */
                }; /* size: 0x0001 */
                UINT8 Preempted;
                UINT8 AdjustReason;
                CHAR AdjustIncrement;
            };
        };
        union
        {
            struct _GROUP_AFFINITY Affinity;
            struct
            {
                UINT8 AffinityFill[GroupAffinityFillSize];
                UINT8 ApcStateIndex;
                UINT8 WaitBlockCount;
                UINT32 IdealProcessor;
            };
        };
        struct _KAPC_STATE* ApcStatePointer[MaximumMode];
        union
        {
            struct _KAPC_STATE SavedApcState;
            struct
            {
                UINT8 SavedApcStateFill[ApcStateActualSize];
                UINT8 WaitReason;
#ifdef _WIN64
                CHAR SuspendCount;
                CHAR Saturation;
                UINT16 SListFaultCount;
#endif
            };
        };
#ifdef _X86_
        CHAR SuspendCount;
        CHAR Saturation;
        UINT16 SListFaultCount;
#endif
        union
        {
            struct _KAPC SchedulerApc;
            struct
            {
                UINT8 SchedulerApcFill0[ApcOffsetToSpareByte0];
                UINT8 ResourceIndex;
            }; /* size: 0x0002 */
            struct
            {
                UINT8 SchedulerApcFill1[ApcOffsetToSpareByte1];
                UINT8 QuantumReset;
            }; /* size: 0x0004 */
            struct
            {
                UINT8 SchedulerApcFill2[ApcOffsetToSpareLong];
                UINT32 KernelTime;
            }; /* size: 0x0008 */
            struct
            {
                UINT8 SchedulerApcFill3[ApcOffsetToSystemArgument1];
                struct _KPRCB* volatile WaitPrcb;
            };
            struct
            {
                UINT8 SchedulerApcFill4[ApcOffsetToSystemArgument2];
                VOID* LegoData;
            };
            struct
            {
                UINT8 SchedulerApcFill5[ApcActualSize];
                UINT8 CallbackNestingLevel;
#ifdef _WIN64
                UINT32 UserTime;
#endif
            };
        };
#ifdef _X86_
        UINT32 UserTime;
#endif
        struct _KEVENT SuspendEvent;
        struct _LIST_ENTRY ThreadListEntry;
        struct _LIST_ENTRY MutantListHead;
        struct _SINGLE_LIST_ENTRY LockEntriesFreeList;
        struct _KLOCK_ENTRY LockEntries[6];
        struct _SINGLE_LIST_ENTRY PropagateBoostsEntry;
        struct _SINGLE_LIST_ENTRY IoSelfBoostsEntry;
        UINT8 PriorityFloorCounts[16];
        UINT32 PriorityFloorSummary;
        volatile INT32 AbCompletedIoBoostCount;
        volatile INT16 AbReferenceCount;
        UINT8 AbFreeEntryCount;
        UINT8 AbWaitEntryCount;
        UINT32 ForegroundLossTime;
        union
        {
            struct _LIST_ENTRY GlobalForegroundListEntry;
            struct
            {
                struct _SINGLE_LIST_ENTRY ForegroundDpcStackListEntry;
                SIZE_T InGlobalForegroundList;
            };
        };
#ifdef _WIN64
        INT64 ReadOperationCount;
        INT64 WriteOperationCount;
        INT64 OtherOperationCount;
        INT64 ReadTransferCount;
        INT64 WriteTransferCount;
        INT64 OtherTransferCount;
#endif
    } KTHREAD, *PKTHREAD; /* size: 0x05d0 */ /* size: 0x0338 */
    static_assert(sizeof(KTHREAD) == (sizeof(SIZE_T) == sizeof(UINT64) ? 0x05d0 : 0x0338));

    
    typedef struct _ETHREAD
    {
        struct _KTHREAD Tcb;
        union _LARGE_INTEGER CreateTime;
        union
        {
            union _LARGE_INTEGER ExitTime;
            struct _LIST_ENTRY KeyedWaitChain;
        };
        VOID* ChargeOnlySession;
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
        EX_PUSH_LOCK ActiveTimerListLock;
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
        VOID* LegacyPowerObject;
        struct _LIST_ENTRY ThreadListEntry;
        struct _EX_RUNDOWN_REF RundownProtect;
        struct _EX_PUSH_LOCK ThreadLock;
        UINT32 ReadClusterSize;
        volatile INT32 MmLockOrdering;
        volatile INT32 CmLockOrdering;
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
                UINT32 ReservedCrossThreadFlags : 15; /* bit position: 17 */
            }; /* bitfield */
        }; /* size: 0x0004 */
        union
        {
            UINT32 SameThreadPassiveFlags;
            struct /* bitfield */
            {
                UINT32 ActiveExWorker : 1; /* bit position: 0 */
                UINT32 MemoryMaker : 1; /* bit position: 1 */
                UINT32 ClonedThread : 1; /* bit position: 2 */
                UINT32 KeyedEventInUse : 1; /* bit position: 3 */
                UINT32 SelfTerminate : 1; /* bit position: 4 */
            }; /* bitfield */
        }; /* size: 0x0004 */
        union
        {
            UINT32 SameThreadApcFlags;
            struct
            {
                struct /* bitfield */
                {
                    UINT8 HardFaultBehavior : 1; /* bit position: 0 */
                    volatile UINT8 StartAddressInvalid : 1; /* bit position: 1 */
                    UINT8 EtwCalloutActive : 1; /* bit position: 2 */
                    UINT8 OwnsProcessWorkingSetExclusive : 1; /* bit position: 3 */
                    UINT8 OwnsProcessWorkingSetShared : 1; /* bit position: 4 */
                    UINT8 OwnsSystemCacheWorkingSetExclusive : 1; /* bit position: 5 */
                    UINT8 OwnsSystemCacheWorkingSetShared : 1; /* bit position: 6 */
                    UINT8 OwnsSessionWorkingSetExclusive : 1; /* bit position: 7 */
                }; /* bitfield */
                struct /* bitfield */
                {
                    UINT8 OwnsSessionWorkingSetShared : 1; /* bit position: 0 */
                    UINT8 OwnsProcessAddressSpaceExclusive : 1; /* bit position: 1 */
                    UINT8 OwnsProcessAddressSpaceShared : 1; /* bit position: 2 */
                    UINT8 SuppressSymbolLoad : 1; /* bit position: 3 */
                    UINT8 Prefetching : 1; /* bit position: 4 */
                    UINT8 OwnsVadExclusive : 1; /* bit position: 5 */
                    UINT8 OwnsChangeControlAreaExclusive : 1; /* bit position: 6 */
                    UINT8 OwnsChangeControlAreaShared : 1; /* bit position: 7 */
                }; /* bitfield */
                struct /* bitfield */
                {
                    UINT8 OwnsPagedPoolWorkingSetExclusive : 1; /* bit position: 0 */
                    UINT8 OwnsPagedPoolWorkingSetShared : 1; /* bit position: 1 */
                    UINT8 OwnsSystemPtesWorkingSetExclusive : 1; /* bit position: 2 */
                    UINT8 OwnsSystemPtesWorkingSetShared : 1; /* bit position: 3 */
                    UINT8 TrimTrigger : 2; /* bit position: 4 */
                    UINT8 Spare2 : 2; /* bit position: 6 */
                }; /* bitfield */
                struct /* bitfield */
                {
                    UINT8 SystemPagePriorityActive : 1; /* bit position: 0 */
                    UINT8 SystemPagePriority : 3; /* bit position: 1 */
                    UINT8 Spare3 : 4; /* bit position: 4 */
                }; /* bitfield */
            }; /* size: 0x0004 */
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
        INT32 ExitStatus;
        struct _LIST_ENTRY AlpcWaitListEntry;
        UINT32 CacheManagerCount;
        UINT32 IoBoostCount;
        struct _LIST_ENTRY BoostList;
        struct _LIST_ENTRY DeboostList;
        EX_PUSH_LOCK BoostListLock;
        EX_PUSH_LOCK IrpListLock;
        VOID* ReservedForSynchTracking;
        struct _SINGLE_LIST_ENTRY CmCallbackListHead;
        const struct _GUID* ActivityId;
        struct _SINGLE_LIST_ENTRY SeLearningModeListHead;
        VOID* VerifierContext;
        UINT32 KernelStackReference;
        VOID* AdjustedClientToken;
#ifdef _WIN64
        UINT32 UserFsBase;
        UINT64 UserGsBase;
        VOID* PicoContext;
#endif
    } ETHREAD, *PETHREAD; /* size: 0x0778 */ /* size: 0x0418 */
    static_assert(sizeof(ETHREAD) == (sizeof(SIZE_T) == sizeof(UINT64) ? 0x0778 : 0x0418));


}
