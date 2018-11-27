#pragma once


/*
 * PDB file: \Nt-Crucial-Modules\Ntoskrnl\10.0.17763.55\
 * Dumped by pdbex tool v0.4, by wbenny
 */


namespace wdk::build_17763
{


    using build_17134::NumberOfProcessor;
    SameDefine$(build_17134, KAFFINITY_EX);
    SameDefine$(build_17134, KPROCESS);


    typedef struct _EPROCESS
    {
        struct _KPROCESS Pcb;
        struct _EX_PUSH_LOCK ProcessLock;
        VOID* UniqueProcessId;
        struct _LIST_ENTRY ActiveProcessLinks;
        struct _EX_RUNDOWN_REF RundownProtect;
#ifdef _X86_
        VOID* VdmObjects;
#endif
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
                UINT32 ForceWakeCharge : 1; /* bit position: 6 */
                UINT32 CrossSessionCreate : 1; /* bit position: 7 */
                UINT32 NeedsHandleRundown : 1; /* bit position: 8 */
                UINT32 RefTraceEnabled : 1; /* bit position: 9 */
                UINT32 PicoCreated : 1; /* bit position: 10 */
                UINT32 EmptyJobEvaluated : 1; /* bit position: 11 */
                UINT32 DefaultPagePriority : 3; /* bit position: 12 */
                UINT32 PrimaryTokenFrozen : 1; /* bit position: 15 */
                UINT32 ProcessVerifierTarget : 1; /* bit position: 16 */
                UINT32 RestrictSetThreadContext : 1; /* bit position: 17 */
                UINT32 AffinityPermanent : 1; /* bit position: 18 */
                UINT32 AffinityUpdateEnable : 1; /* bit position: 19 */
                UINT32 PropagateNode : 1; /* bit position: 20 */
                UINT32 ExplicitAffinity : 1; /* bit position: 21 */
                UINT32 ProcessExecutionState : 2; /* bit position: 22 */
                UINT32 EnableReadVmLogging : 1; /* bit position: 24 */
                UINT32 EnableWriteVmLogging : 1; /* bit position: 25 */
                UINT32 FatalAccessTerminationRequested : 1; /* bit position: 26 */
                UINT32 DisableSystemAllowedCpuSet : 1; /* bit position: 27 */
                UINT32 ProcessStateChangeRequest : 2; /* bit position: 28 */
                UINT32 ProcessStateChangeInProgress : 1; /* bit position: 30 */
                UINT32 InPrivate : 1; /* bit position: 31 */
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
                UINT32 ManageExecutableMemoryWrites : 1; /* bit position: 4 */
                UINT32 VmDeleted : 1; /* bit position: 5 */
                UINT32 OutswapEnabled : 1; /* bit position: 6 */
                UINT32 Outswapped : 1; /* bit position: 7 */
                UINT32 FailFastOnCommitFail : 1; /* bit position: 8 */
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
                UINT32 Background : 1; /* bit position: 20 */
                UINT32 VmTopDown : 1; /* bit position: 21 */
                UINT32 ImageNotifyDone : 1; /* bit position: 22 */
                UINT32 PdeUpdateNeeded : 1; /* bit position: 23 */
                UINT32 VdmAllowed : 1; /* bit position: 24 */
                UINT32 ProcessRundown : 1; /* bit position: 25 */
                UINT32 ProcessInserted : 1; /* bit position: 26 */
                UINT32 DefaultIoPriority : 3; /* bit position: 27 */
                UINT32 ProcessSelfDelete : 1; /* bit position: 30 */
                UINT32 SetTimerResolutionLink : 1; /* bit position: 31 */
            }; /* bitfield */
        }; /* size: 0x0004 */
        union _LARGE_INTEGER CreateTime;
        SIZE_T ProcessQuotaUsage[2];
        SIZE_T ProcessQuotaPeak[2];
        SIZE_T PeakVirtualSize;
        SIZE_T VirtualSize;
        struct _LIST_ENTRY SessionProcessLinks;
        union
        {
            VOID* ExceptionPortData;
            SIZE_T ExceptionPortValue : sizeof(SIZE_T) * 8 - 3;
            SIZE_T ExceptionPortState : 3; /* bit position: 0 */
        };
        struct _EX_FAST_REF Token;
        SIZE_T MmReserved;
        struct _EX_PUSH_LOCK AddressCreationLock;
        struct _EX_PUSH_LOCK PageTableCommitmentLock;
        struct _ETHREAD* RotateInProgress;
        struct _ETHREAD* ForkInProgress;
        struct _EJOB* volatile CommitChargeJob;
        struct _RTL_AVL_TREE CloneRoot;
        volatile SIZE_T NumberOfPrivatePages;
        volatile SIZE_T NumberOfLockedPages;
        VOID* Win32Process;
        struct _EJOB* volatile Job;
        VOID* SectionObject;
        VOID* SectionBaseAddress;
        UINT32 Cookie;
        struct _PAGEFAULT_HISTORY* WorkingSetWatch;
        VOID* Win32WindowStation;
        VOID* InheritedFromUniqueProcessId;
        VOID* LdtInformation;
        volatile SIZE_T OwnerProcessId;
        struct _PEB* Peb;
        struct _MM_SESSION_SPACE* Session;
        VOID* AweInfo;
        struct _EPROCESS_QUOTA_BLOCK* QuotaBlock;
        struct _HANDLE_TABLE* ObjectTable;
        VOID* DebugPort;
#ifdef _WIN64
        struct _EWOW64PROCESS* WoW64Process;
#else
        VOID* PaeTop;
#endif
        VOID* DeviceMap;
        VOID* EtwDataSource;
        UINT64 PageDirectoryPte;
        struct _FILE_OBJECT* ImageFilePointer;
        UINT8 ImageFileName[15];
        UINT8 PriorityClass;
        VOID* SecurityPort;
        struct _SE_AUDIT_PROCESS_CREATION_INFO SeAuditProcessCreationInfo;
        struct _LIST_ENTRY JobLinks;
        VOID* HighestUserAddress;
        struct _LIST_ENTRY ThreadListHead;
        volatile UINT32 ActiveThreads;
        UINT32 ImagePathHash;
        UINT32 DefaultHardErrorProcessing;
        INT32 LastThreadExitStatus;
        struct _EX_FAST_REF PrefetchTrace;
        VOID* LockedPagesList;
        union _LARGE_INTEGER ReadOperationCount;
        union _LARGE_INTEGER WriteOperationCount;
        union _LARGE_INTEGER OtherOperationCount;
        union _LARGE_INTEGER ReadTransferCount;
        union _LARGE_INTEGER WriteTransferCount;
        union _LARGE_INTEGER OtherTransferCount;
        SIZE_T CommitChargeLimit;
        volatile SIZE_T CommitCharge;
        volatile SIZE_T CommitChargePeak;
        struct _MMSUPPORT_FULL Vm;
        struct _LIST_ENTRY MmProcessLinks;
        UINT32 ModifiedPageCount;
        INT32 ExitStatus;
        struct _RTL_AVL_TREE VadRoot;
        VOID* VadHint;
        SIZE_T VadCount;
        volatile SIZE_T VadPhysicalPages;
        SIZE_T VadPhysicalPagesLimit;
        struct _ALPC_PROCESS_CONTEXT AlpcContext;
        struct _LIST_ENTRY TimerResolutionLink;
        struct _PO_DIAG_STACK_RECORD* TimerResolutionStackRecord;
        UINT32 RequestedTimerResolution;
        UINT32 SmallestTimerResolution;
#ifdef _X86_
        UINT32 Padding0;
#endif
        union _LARGE_INTEGER ExitTime;
#ifdef _WIN64
        struct _INVERTED_FUNCTION_TABLE* InvertedFunctionTable;
        struct _EX_PUSH_LOCK InvertedFunctionTableLock;
#endif
        UINT32 ActiveThreadsHighWatermark;
        UINT32 LargePrivateVadCount;
        struct _EX_PUSH_LOCK ThreadListLock;
        VOID* WnfContext;
        struct _EJOB* ServerSilo;
        UINT8 SignatureLevel;
        UINT8 SectionSignatureLevel;
        struct _PS_PROTECTION Protection;
        struct /* bitfield */
        {
            UINT8 HangCount : 3; /* bit position: 0 */
            UINT8 GhostCount : 3; /* bit position: 3 */
            UINT8 PrefilterException : 1; /* bit position: 6 */
        }; /* bitfield */
        union
        {
            UINT32 Flags3;
            struct /* bitfield */
            {
                UINT32 Minimal : 1; /* bit position: 0 */
                UINT32 ReplacingPageRoot : 1; /* bit position: 1 */
                UINT32 Crashed : 1; /* bit position: 2 */
                UINT32 JobVadsAreTracked : 1; /* bit position: 3 */
                UINT32 VadTrackingDisabled : 1; /* bit position: 4 */
                UINT32 AuxiliaryProcess : 1; /* bit position: 5 */
                UINT32 SubsystemProcess : 1; /* bit position: 6 */
                UINT32 IndirectCpuSets : 1; /* bit position: 7 */
                UINT32 RelinquishedCommit : 1; /* bit position: 8 */
                UINT32 HighGraphicsPriority : 1; /* bit position: 9 */
                UINT32 CommitFailLogged : 1; /* bit position: 10 */
                UINT32 ReserveFailLogged : 1; /* bit position: 11 */
                UINT32 SystemProcess : 1; /* bit position: 12 */
                UINT32 HideImageBaseAddresses : 1; /* bit position: 13 */
                UINT32 AddressPolicyFrozen : 1; /* bit position: 14 */
                UINT32 ProcessFirstResume : 1; /* bit position: 15 */
                UINT32 ForegroundExternal : 1; /* bit position: 16 */
                UINT32 ForegroundSystem : 1; /* bit position: 17 */
                UINT32 HighMemoryPriority : 1; /* bit position: 18 */
                UINT32 EnableProcessSuspendResumeLogging : 1; /* bit position: 19 */
                UINT32 EnableThreadSuspendResumeLogging : 1; /* bit position: 20 */
                UINT32 SecurityDomainChanged : 1; /* bit position: 21 */
                UINT32 SecurityFreezeComplete : 1; /* bit position: 22 */
                UINT32 VmProcessorHost : 1; /* bit position: 23 */
            }; /* bitfield */
        }; /* size: 0x0004 */
        INT32 DeviceAsid;
        VOID* SvmData;
        struct _EX_PUSH_LOCK SvmProcessLock;
        SIZE_T SvmLock;
        struct _LIST_ENTRY SvmProcessDeviceListHead;
        UINT64 LastFreezeInterruptTime;
        struct _PROCESS_DISK_COUNTERS* DiskCounters;
        VOID* PicoContext;
#ifdef _WIN64
        VOID* EnclaveTable;
        UINT64 EnclaveNumber;
        struct _EX_PUSH_LOCK EnclaveLock;
#endif
        UINT32 HighPriorityFaultsAllowed;
#ifdef _X86_
        VOID* InstrumentationCallback;
#endif
        struct _PO_PROCESS_ENERGY_CONTEXT* EnergyContext;
        VOID* VmContext;
        UINT64 SequenceNumber;
        UINT64 CreateInterruptTime;
        UINT64 CreateUnbiasedInterruptTime;
        UINT64 TotalUnbiasedFrozenTime;
        UINT64 LastAppStateUpdateTime;
        struct /* bitfield */
        {
            UINT64 LastAppStateUptime : 61; /* bit position: 0 */
            UINT64 LastAppState : 3; /* bit position: 61 */
        }; /* bitfield */
        volatile SIZE_T SharedCommitCharge;
        struct _EX_PUSH_LOCK SharedCommitLock;
        struct _LIST_ENTRY SharedCommitLinks;
        union
        {
            struct
            {
                SIZE_T AllowedCpuSets;
                SIZE_T DefaultCpuSets;
            };
            struct
            {
                SIZE_T* AllowedCpuSetsIndirect;
                SIZE_T* DefaultCpuSetsIndirect;
            };
        };
        VOID* DiskIoAttribution;
        VOID* DxgProcess;
        UINT32 Win32KFilterSet;
        volatile union _PS_INTERLOCKED_TIMER_DELAY_VALUES ProcessTimerDelay;
        volatile UINT32 KTimerSets;
        volatile UINT32 KTimer2Sets;
        volatile UINT32 ThreadTimerSets;
        SIZE_T VirtualTimerListLock;
        struct _LIST_ENTRY VirtualTimerListHead;
        union
        {
            struct _WNF_STATE_NAME WakeChannel;
            struct _PS_PROCESS_WAKE_INFORMATION WakeInfo;
        }; /* size: 0x0030 */
        union
        {
            UINT32 MitigationFlags;
            struct // _TAG_UNNAMED_88
            {
                struct /* bitfield */
                {
                    UINT32 ControlFlowGuardEnabled : 1; /* bit position: 0 */
                    UINT32 ControlFlowGuardExportSuppressionEnabled : 1; /* bit position: 1 */
                    UINT32 ControlFlowGuardStrict : 1; /* bit position: 2 */
                    UINT32 DisallowStrippedImages : 1; /* bit position: 3 */
                    UINT32 ForceRelocateImages : 1; /* bit position: 4 */
                    UINT32 HighEntropyASLREnabled : 1; /* bit position: 5 */
                    UINT32 StackRandomizationDisabled : 1; /* bit position: 6 */
                    UINT32 ExtensionPointDisable : 1; /* bit position: 7 */
                    UINT32 DisableDynamicCode : 1; /* bit position: 8 */
                    UINT32 DisableDynamicCodeAllowOptOut : 1; /* bit position: 9 */
                    UINT32 DisableDynamicCodeAllowRemoteDowngrade : 1; /* bit position: 10 */
                    UINT32 AuditDisableDynamicCode : 1; /* bit position: 11 */
                    UINT32 DisallowWin32kSystemCalls : 1; /* bit position: 12 */
                    UINT32 AuditDisallowWin32kSystemCalls : 1; /* bit position: 13 */
                    UINT32 EnableFilteredWin32kAPIs : 1; /* bit position: 14 */
                    UINT32 AuditFilteredWin32kAPIs : 1; /* bit position: 15 */
                    UINT32 DisableNonSystemFonts : 1; /* bit position: 16 */
                    UINT32 AuditNonSystemFontLoading : 1; /* bit position: 17 */
                    UINT32 PreferSystem32Images : 1; /* bit position: 18 */
                    UINT32 ProhibitRemoteImageMap : 1; /* bit position: 19 */
                    UINT32 AuditProhibitRemoteImageMap : 1; /* bit position: 20 */
                    UINT32 ProhibitLowILImageMap : 1; /* bit position: 21 */
                    UINT32 AuditProhibitLowILImageMap : 1; /* bit position: 22 */
                    UINT32 SignatureMitigationOptIn : 1; /* bit position: 23 */
                    UINT32 AuditBlockNonMicrosoftBinaries : 1; /* bit position: 24 */
                    UINT32 AuditBlockNonMicrosoftBinariesAllowStore : 1; /* bit position: 25 */
                    UINT32 LoaderIntegrityContinuityEnabled : 1; /* bit position: 26 */
                    UINT32 AuditLoaderIntegrityContinuity : 1; /* bit position: 27 */
                    UINT32 EnableModuleTamperingProtection : 1; /* bit position: 28 */
                    UINT32 EnableModuleTamperingProtectionNoInherit : 1; /* bit position: 29 */
                    UINT32 RestrictIndirectBranchPrediction : 1; /* bit position: 30 */
                    UINT32 IsolateSecurityDomain : 1; /* bit position: 31 */
                }; /* bitfield */
            } /* size: 0x0004 */ MitigationFlagsValues;
        }; /* size: 0x0004 */
        union
        {
            UINT32 MitigationFlags2;
            struct // _TAG_UNNAMED_89
            {
                struct /* bitfield */
                {
                    UINT32 EnableExportAddressFilter : 1; /* bit position: 0 */
                    UINT32 AuditExportAddressFilter : 1; /* bit position: 1 */
                    UINT32 EnableExportAddressFilterPlus : 1; /* bit position: 2 */
                    UINT32 AuditExportAddressFilterPlus : 1; /* bit position: 3 */
                    UINT32 EnableRopStackPivot : 1; /* bit position: 4 */
                    UINT32 AuditRopStackPivot : 1; /* bit position: 5 */
                    UINT32 EnableRopCallerCheck : 1; /* bit position: 6 */
                    UINT32 AuditRopCallerCheck : 1; /* bit position: 7 */
                    UINT32 EnableRopSimExec : 1; /* bit position: 8 */
                    UINT32 AuditRopSimExec : 1; /* bit position: 9 */
                    UINT32 EnableImportAddressFilter : 1; /* bit position: 10 */
                    UINT32 AuditImportAddressFilter : 1; /* bit position: 11 */
                    UINT32 DisablePageCombine : 1; /* bit position: 12 */
                    UINT32 SpeculativeStoreBypassDisable : 1; /* bit position: 13 */
                    UINT32 CetShadowStacks : 1; /* bit position: 14 */
                }; /* bitfield */
            } /* size: 0x0004 */ MitigationFlags2Values;
        }; /* size: 0x0004 */
        VOID* PartitionObject;
        UINT64 SecurityDomain;
        UINT64 ParentSecurityDomain;
        VOID* CoverageSamplerContext;
        VOID* MmHotPatchContext;
    } EPROCESS, *PEPROCESS; /* size: 0x0850 */ /* size: 0x0408 */
    static_assert(sizeof(EPROCESS) == (sizeof(SIZE_T) == sizeof(UINT64) ? 0x0850 : 0x0408));


}
