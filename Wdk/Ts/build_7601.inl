#pragma once


/*
 * PDB file: \Nt-Crucial-Modules\Ntoskrnl\6.1.7601.24260\
 * Dumped by pdbex tool v0.4, by wbenny
 */


namespace wdk::build_7601
{


    typedef struct _KTHREAD
    {
        struct _DISPATCHER_HEADER Header;
        volatile UINT64 CycleTime;
#ifdef _X86_
        volatile UINT32 HighCycleTime;
#endif
        UINT64 QuantumTarget;
        VOID* InitialStack;
        VOID* volatile StackLimit;
        VOID* KernelStack;
        EX_PUSH_LOCK ThreadLock;
        _KWAIT_STATUS_REGISTER WaitRegister;
        volatile UINT8 Running;
        UINT8 Alerted[MaximumMode];
        union
        {
            struct /* bitfield */
            {
                UINT32 KernelStackResident : 1; /* bit position: 0 */
                UINT32 ReadyTransition : 1; /* bit position: 1 */
                UINT32 ProcessReadyQueue : 1; /* bit position: 2 */
                UINT32 WaitNext : 1; /* bit position: 3 */
                UINT32 SystemAffinityActive : 1; /* bit position: 4 */
                UINT32 Alertable : 1; /* bit position: 5 */
                UINT32 GdiFlushActive : 1; /* bit position: 6 */
                UINT32 UserStackWalkActive : 1; /* bit position: 7 */
                UINT32 ApcInterruptRequest : 1; /* bit position: 8 */
                UINT32 ForceDeferSchedule : 1; /* bit position: 9 */
                UINT32 QuantumEndMigrate : 1; /* bit position: 10 */
                UINT32 UmsDirectedSwitchEnable : 1; /* bit position: 11 */
                UINT32 TimerActive : 1; /* bit position: 12 */
                UINT32 SystemThread : 1; /* bit position: 13 */
                UINT32 Reserved : 18; /* bit position: 14 */
            }; /* bitfield */
            INT32 MiscFlags;
        }; /* size: 0x0004 */
        union
        {
            struct _KAPC_STATE ApcState;
            struct
            {
                UINT8 ApcStateFill[ApcStateActualSize];
                CHAR Priority;
#ifdef _WIN64
                volatile UINT32 NextProcessor;
#endif
            }; /* size: 0x0030 */ /* size: 0x0018 */
        }; /* size: 0x0030 */ /* size: 0x0018 */
#ifdef _X86_
        volatile UINT32 NextProcessor;
#endif
        volatile UINT32 DeferredProcessor;
        SIZE_T ApcQueueLock;
#ifdef _X86_
        UINT32 ContextSwitches;
        volatile UINT8 State;
        CHAR NpxState;
        UINT8 WaitIrql;
        KPROCESSOR_MODE WaitMode;
#endif
        volatile SSIZE_T WaitStatus;
        struct _KWAIT_BLOCK* WaitBlockList;
        union
        {
            struct _LIST_ENTRY WaitListEntry;
            struct _SINGLE_LIST_ENTRY SwapListEntry;
        }; /* size: 0x0010 */ /* size: 0x0008 */
        struct _KQUEUE* volatile Queue;
#ifdef _X86_
        UINT32 WaitTime;
        union
        {
            struct
            {
                INT16 KernelApcDisable;
                INT16 SpecialApcDisable;
            };
            UINT32 CombinedApcDisable;
        };
#endif
        VOID* Teb;
        struct _KTIMER Timer;
        union
        {
            struct /* bitfield */
            {
                volatile UINT32 AutoAlignment : 1; /* bit position: 0 */
                volatile UINT32 DisableBoost : 1; /* bit position: 1 */
                volatile UINT32 EtwStackTraceApc1Inserted : 1; /* bit position: 2 */
                volatile UINT32 EtwStackTraceApc2Inserted : 1; /* bit position: 3 */
                volatile UINT32 CalloutActive : 1; /* bit position: 4 */
                volatile UINT32 ApcQueueable : 1; /* bit position: 5 */
                volatile UINT32 EnableStackSwap : 1; /* bit position: 6 */
                volatile UINT32 GuiThread : 1; /* bit position: 7 */
                volatile UINT32 UmsPerformingSyscall : 1; /* bit position: 8 */
                volatile UINT32 VdmSafe : 1; /* bit position: 9 */
                volatile UINT32 UmsDispatched : 1; /* bit position: 10 */
                volatile UINT32 ReservedFlags : 21; /* bit position: 11 */
            }; /* bitfield */
            volatile INT32 ThreadFlags;
        }; /* size: 0x0004 */
#ifdef _WIN64
        UINT32 Spare0;
        union
        {
            struct _KWAIT_BLOCK WaitBlock[THREAD_WAIT_OBJECTS + 1];
            struct
            {
                UINT8 WaitBlockFill4[44];
                UINT32 ContextSwitches;
            }; /* size: 0x0030 */
            struct
            {
                UINT8 WaitBlockFill5[92];
                volatile UINT8 State;
                CHAR NpxState;
                UINT8 WaitIrql;
                CHAR WaitMode;
            }; /* size: 0x0060 */
            struct
            {
                UINT8 WaitBlockFill6[140];
                UINT32 WaitTime;
            }; /* size: 0x0090 */
            struct
            {
                UINT8 WaitBlockFill7[168];
                VOID* TebMappedLowVa;
                struct _UMS_CONTROL_BLOCK* Ucb;
            }; /* size: 0x00b8 */
            struct
            {
                UINT8 WaitBlockFill8[188];
                union
                {
                    struct
                    {
                        INT16 KernelApcDisable;
                        INT16 SpecialApcDisable;
                    }; /* size: 0x0004 */
                    UINT32 CombinedApcDisable;
                }; /* size: 0x0004 */
            }; /* size: 0x00c0 */
        }; /* size: 0x00c0 */

#else
        VOID* ServiceTable;
        struct _KWAIT_BLOCK WaitBlock[THREAD_WAIT_OBJECTS + 1];
#endif
        struct _LIST_ENTRY QueueListEntry;
        struct _KTRAP_FRAME* TrapFrame;
        VOID* FirstArgument;
        union
        {
            VOID* CallbackStack;
            SIZE_T CallbackDepth;
        };
        UINT8 ApcStateIndex;
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
        CHAR PreviousMode;
        CHAR Saturation;
        UINT32 SystemCallNumber;
        UINT32 FreezeCount;
        volatile struct _GROUP_AFFINITY UserAffinity;
        struct _KPROCESS* Process;
        volatile struct _GROUP_AFFINITY Affinity;
        UINT32 IdealProcessor;
        UINT32 UserIdealProcessor;
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
                CHAR Spare1;
                UINT8 CodePatchInProgress;
#endif
            };
        };
#ifdef _X86_
        CHAR SuspendCount;
        CHAR Spare1;
        UINT8 OtherPlatformFill;
#endif
        VOID* volatile Win32Thread;
        VOID* StackBase;
        union
        {
            struct _KAPC SuspendApc;
            struct
            {
                UINT8 SuspendApcFill0[ApcOffsetToSpareByte0];
                UINT8 ResourceIndex;
            }; /* size: 0x0002 */
            struct
            {
                UINT8 SuspendApcFill1[ApcOffsetToSpareByte1];
                UINT8 QuantumReset;
            }; /* size: 0x0004 */
            struct
            {
                UINT8 SuspendApcFill2[ApcOffsetToSpareLong];
                UINT32 KernelTime;
            }; /* size: 0x0008 */
            struct
            {
                UINT8 SuspendApcFill3[ApcOffsetToSystemArgument1];
                struct _KPRCB* volatile WaitPrcb;
            }; /* size: 0x0048 */ /* size: 0x0028 */
            struct
            {
                UINT8 SuspendApcFill4[ApcOffsetToSystemArgument2];
                VOID* LegoData;
            }; /* size: 0x0050 */ /* size: 0x002c */
            struct
            {
                UINT8 SuspendApcFill5[ApcActualSize];
                UINT8 LargeStack;
#ifdef _WIN64
                UINT32 UserTime;
#endif
            }; /* size: 0x0058 */ /* size: 0x0030 */
        }; /* size: 0x0058 */ /* size: 0x0030 */
#ifdef _X86_
        UINT32 UserTime;
#endif
        union
        {
            struct _KSEMAPHORE SuspendSemaphore;
#ifdef _WIN64
            struct
            {
                UINT8 SuspendSemaphorefill[SemaphoreActualSize];
                UINT32 SListFaultCount;
            };
#else
            UINT8 SuspendSemaphorefill[SemaphoreActualSize];
#endif
        };
#ifdef _X86_
        UINT32 SListFaultCount;
#endif
        struct _LIST_ENTRY ThreadListEntry;
        struct _LIST_ENTRY MutantListHead;
        VOID* SListFaultAddress;
#ifdef _WIN64
        INT64 ReadOperationCount;
        INT64 WriteOperationCount;
        INT64 OtherOperationCount;
        INT64 ReadTransferCount;
        INT64 WriteTransferCount;
        INT64 OtherTransferCount;
#endif
        struct _KTHREAD_COUNTERS* ThreadCounters;
#ifdef _WIN64
        struct _XSAVE_FORMAT* StateSaveArea;
#endif
        struct _XSTATE_SAVE* XStateSave;
    } KTHREAD, *PKTHREAD; /* size: 0x0368 */ /* size: 0x0200 */
    static_assert(sizeof(KTHREAD) == (sizeof(SIZE_T) == sizeof(UINT64) ? 0x0368 : 0x0200));


    typedef struct _ETHREAD
    {
        struct _KTHREAD Tcb;
        union _LARGE_INTEGER CreateTime;
        union
        {
            union _LARGE_INTEGER ExitTime;
            struct _LIST_ENTRY KeyedWaitChain;
        };
        INT32 ExitStatus;
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
        union _PSP_CPU_QUOTA_APC* CpuQuotaApc;
        VOID* Win32StartAddress;
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
                UINT32 Reserved : 1; /* bit position: 4 */
                UINT32 HardErrorsAreDisabled : 1; /* bit position: 5 */
                UINT32 BreakOnTermination : 1; /* bit position: 6 */
                UINT32 SkipCreationMsg : 1; /* bit position: 7 */
                UINT32 SkipTerminationMsg : 1; /* bit position: 8 */
                UINT32 CopyTokenOnOpen : 1; /* bit position: 9 */
                UINT32 ThreadIoPriority : 3; /* bit position: 10 */
                UINT32 ThreadPagePriority : 3; /* bit position: 13 */
                UINT32 RundownFail : 1; /* bit position: 16 */
                UINT32 NeedsWorkingSetAging : 1; /* bit position: 17 */
            }; /* bitfield */
        }; /* size: 0x0004 */
        union
        {
            UINT32 SameThreadPassiveFlags;
            struct /* bitfield */
            {
                UINT32 ActiveExWorker : 1; /* bit position: 0 */
                UINT32 ExWorkerCanWaitUser : 1; /* bit position: 1 */
                UINT32 MemoryMaker : 1; /* bit position: 2 */
                UINT32 ClonedThread : 1; /* bit position: 3 */
                UINT32 KeyedEventInUse : 1; /* bit position: 4 */
                UINT32 RateApcState : 2; /* bit position: 5 */
                UINT32 SelfTerminate : 1; /* bit position: 7 */
            }; /* bitfield */
        }; /* size: 0x0004 */
        union
        {
            UINT32 SameThreadApcFlags;
            struct
            {
                struct /* bitfield */
                {
                    UINT8 Spare : 1; /* bit position: 0 */
                    volatile UINT8 StartAddressInvalid : 1; /* bit position: 1 */
                    UINT8 EtwPageFaultCalloutActive : 1; /* bit position: 2 */
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
                    UINT8 OwnsDynamicMemoryShared : 1; /* bit position: 5 */
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
                    UINT8 Spare1 : 2; /* bit position: 6 */
                }; /* bitfield */
                UINT8 PriorityRegionActive;
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
        struct _LIST_ENTRY AlpcWaitListEntry;
        UINT32 CacheManagerCount;
        UINT32 IoBoostCount;
        SIZE_T IrpListLock;
        VOID* ReservedForSynchTracking;
        struct _SINGLE_LIST_ENTRY CmCallbackListHead;
        UINT32 KernelStackReference;
    } ETHREAD, *PETHREAD; /* size: 0x04a8 */ /* size: 0x02b8 */
    static_assert(sizeof(ETHREAD) == (sizeof(SIZE_T) == sizeof(UINT64) ? 0x04a8 : 0x02b8));

}
