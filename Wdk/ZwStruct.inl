#pragma once


namespace wdk
{

#pragma region Memory Partition
    typedef enum _MEMORY_PARTITION_INFORMATION_CLASS : UINT32
    {
        SystemMemoryPartitionInformation,       // q: MEMORY_PARTITION_CONFIGURATION_INFORMATION
        SystemMemoryPartitionMoveMemory,        // s: MEMORY_PARTITION_TRANSFER_INFORMATION
        SystemMemoryPartitionAddPagefile,       // s: MEMORY_PARTITION_PAGEFILE_INFORMATION
        SystemMemoryPartitionCombineMemory,     // q; s: MEMORY_PARTITION_PAGE_COMBINE_INFORMATION
        SystemMemoryPartitionInitialAddMemory,  // q; s: MEMORY_PARTITION_INITIAL_ADD_INFORMATION
        SystemMemoryPartitionGetMemoryEvents,   // MEMORY_PARTITION_MEMORY_EVENTS_INFORMATION // since REDSTONE2
        SystemMemoryPartitionMax
    } MEMORY_PARTITION_INFORMATION_CLASS;
    
    typedef struct _MEMORY_PARTITION_CONFIGURATION_INFORMATION
    {
        ULONG Flags;
        ULONG NumaNode;
        ULONG Channel;
        ULONG NumberOfNumaNodes;
        ULONG_PTR ResidentAvailablePages;
        ULONG_PTR CommittedPages;
        ULONG_PTR CommitLimit;
        ULONG_PTR PeakCommitment;
        ULONG_PTR TotalNumberOfPages;
        ULONG_PTR AvailablePages;
        ULONG_PTR ZeroPages;
        ULONG_PTR FreePages;
        ULONG_PTR StandbyPages;
        ULONG_PTR StandbyPageCountByPriority[8]; // since REDSTONE2
        ULONG_PTR RepurposedPagesByPriority[8];
        ULONG_PTR MaximumCommitLimit;
        ULONG_PTR DonatedPagesToPartitions;
        ULONG PartitionId; // since REDSTONE3
    } MEMORY_PARTITION_CONFIGURATION_INFORMATION, *PMEMORY_PARTITION_CONFIGURATION_INFORMATION;

    typedef struct _MEMORY_PARTITION_TRANSFER_INFORMATION
    {
        ULONG_PTR NumberOfPages;
        ULONG NumaNode;
        ULONG Flags;
    } MEMORY_PARTITION_TRANSFER_INFORMATION, *PMEMORY_PARTITION_TRANSFER_INFORMATION;

    typedef struct _MEMORY_PARTITION_PAGEFILE_INFORMATION
    {
        UNICODE_STRING PageFileName;
        LARGE_INTEGER MinimumSize;
        LARGE_INTEGER MaximumSize;
        ULONG Flags;
    } MEMORY_PARTITION_PAGEFILE_INFORMATION, *PMEMORY_PARTITION_PAGEFILE_INFORMATION;

    typedef struct _MEMORY_PARTITION_PAGE_COMBINE_INFORMATION
    {
        HANDLE StopHandle;
        ULONG Flags;
        ULONG_PTR TotalNumberOfPages;
    } MEMORY_PARTITION_PAGE_COMBINE_INFORMATION, *PMEMORY_PARTITION_PAGE_COMBINE_INFORMATION;

    typedef struct _MEMORY_PARTITION_PAGE_RANGE
    {
        ULONG_PTR StartPage;
        ULONG_PTR NumberOfPages;
    } MEMORY_PARTITION_PAGE_RANGE, *PMEMORY_PARTITION_PAGE_RANGE;

    typedef struct _MEMORY_PARTITION_INITIAL_ADD_INFORMATION
    {
        ULONG Flags;
        ULONG NumberOfRanges;
        ULONG_PTR NumberOfPagesAdded;
        MEMORY_PARTITION_PAGE_RANGE PartitionRanges[1];
    } MEMORY_PARTITION_INITIAL_ADD_INFORMATION, *PMEMORY_PARTITION_INITIAL_ADD_INFORMATION;

    typedef struct _MEMORY_PARTITION_MEMORY_EVENTS_INFORMATION
    {
        union
        {
            struct
            {
                ULONG CommitEvents : 1;
                ULONG Spare : 31;
            };
            ULONG AllFlags;
        } Flags;

        ULONG HandleAttributes;
        ULONG DesiredAccess;
        HANDLE LowCommitCondition;      // \KernelObjects\LowCommitCondition
        HANDLE HighCommitCondition;     // \KernelObjects\HighCommitCondition
        HANDLE MaximumCommitCondition;  // \KernelObjects\MaximumCommitCondition
    } MEMORY_PARTITION_MEMORY_EVENTS_INFORMATION, *PMEMORY_PARTITION_MEMORY_EVENTS_INFORMATION;
#pragma endregion


#pragma region Job
    typedef enum _JOBOBJECTINFOCLASS : UINT32
    {
        JobObjectBasicAccountingInformation = 1,    // JOBOBJECT_BASIC_ACCOUNTING_INFORMATION
        JobObjectBasicLimitInformation,             // JOBOBJECT_BASIC_LIMIT_INFORMATION
        JobObjectBasicProcessIdList,                // JOBOBJECT_BASIC_PROCESS_ID_LISTv
        JobObjectBasicUIRestrictions,               // JOBOBJECT_BASIC_UI_RESTRICTIONS
        JobObjectSecurityLimitInformation,          // JOBOBJECT_SECURITY_LIMIT_INFORMATION
        JobObjectEndOfJobTimeInformation,           // JOBOBJECT_END_OF_JOB_TIME_INFORMATION
        JobObjectAssociateCompletionPortInformation,// JOBOBJECT_ASSOCIATE_COMPLETION_PORT
        JobObjectBasicAndIoAccountingInformation,   // JOBOBJECT_BASIC_AND_IO_ACCOUNTING_INFORMATION
        JobObjectExtendedLimitInformation,          // JOBOBJECT_EXTENDED_LIMIT_INFORMATION
        JobObjectJobSetInformation,                 // JOBOBJECT_JOBSET_INFORMATION
        JobObjectGroupInformation,                  // USHORT
        JobObjectNotificationLimitInformation,      // JOBOBJECT_NOTIFICATION_LIMIT_INFORMATION
        JobObjectLimitViolationInformation,         // JOBOBJECT_LIMIT_VIOLATION_INFORMATION
        JobObjectGroupInformationEx,                // GROUP_AFFINITY (ARRAY)
        JobObjectCpuRateControlInformation,         // JOBOBJECT_CPU_RATE_CONTROL_INFORMATION
        JobObjectCompletionFilter,
        JobObjectCompletionCounter,
        JobObjectFreezeInformation,                 // JOBOBJECT_FREEZE_INFORMATION
        JobObjectExtendedAccountingInformation,     // JOBOBJECT_EXTENDED_ACCOUNTING_INFORMATION
        JobObjectWakeInformation,                   // JOBOBJECT_WAKE_INFORMATION
        JobObjectBackgroundInformation,
        JobObjectSchedulingRankBiasInformation,
        JobObjectTimerVirtualizationInformation,
        JobObjectCycleTimeNotification,
        JobObjectClearEvent,
        JobObjectInterferenceInformation,           // JOBOBJECT_INTERFERENCE_INFORMATION
        JobObjectClearPeakJobMemoryUsed,             
        JobObjectMemoryUsageInformation,            // JOBOBJECT_MEMORY_USAGE_INFORMATION // JOBOBJECT_MEMORY_USAGE_INFORMATION_V2
        JobObjectSharedCommit,
        JobObjectContainerId,
        JobObjectIoRateControlInformation,
        JobObjectNetRateControlInformation,         // JOBOBJECT_NET_RATE_CONTROL_INFORMATION
        JobObjectNotificationLimitInformation2,     // JOBOBJECT_NOTIFICATION_LIMIT_INFORMATION_2
        JobObjectLimitViolationInformation2,        // JOBOBJECT_LIMIT_VIOLATION_INFORMATION_2
        JobObjectCreateSilo,
        JobObjectSiloBasicInformation,              // SILOOBJECT_BASIC_INFORMATION
        JobObjectSiloRootDirectory,                 // SILOOBJECT_ROOT_DIRECTORY
        JobObjectServerSiloBasicInformation,        // SERVERSILO_BASIC_INFORMATION
        JobObjectServerSiloUserSharedData,          // SILO_USER_SHARED_DATA
        JobObjectServerSiloInitialize,
        JobObjectServerSiloRunningState,
        JobObjectIoAttribution,
        JobObjectMemoryPartitionInformation,
        JobObjectContainerTelemetryId,
        JobObjectSiloSystemRoot,
        JobObjectEnergyTrackingState,               // JOBOBJECT_ENERGY_TRACKING_STATE
        JobObjectThreadImpersonationInformation,
        MaxJobObjectInfoClass

    }JOBOBJECTINFOCLASS;
    
    typedef struct _JOBOBJECT_BASIC_ACCOUNTING_INFORMATION
    {
        LARGE_INTEGER TotalUserTime;
        LARGE_INTEGER TotalKernelTime;
        LARGE_INTEGER ThisPeriodTotalUserTime;
        LARGE_INTEGER ThisPeriodTotalKernelTime;
        DWORD         TotalPageFaultCount;
        DWORD         TotalProcesses;
        DWORD         ActiveProcesses;
        DWORD         TotalTerminatedProcesses;
    } JOBOBJECT_BASIC_ACCOUNTING_INFORMATION, *PJOBOBJECT_BASIC_ACCOUNTING_INFORMATION;

    typedef struct _JOBOBJECT_BASIC_LIMIT_INFORMATION
    {
        LARGE_INTEGER PerProcessUserTimeLimit;
        LARGE_INTEGER PerJobUserTimeLimit;
        DWORD         LimitFlags;
        SIZE_T        MinimumWorkingSetSize;
        SIZE_T        MaximumWorkingSetSize;
        DWORD         ActiveProcessLimit;
        ULONG_PTR     Affinity;
        DWORD         PriorityClass;
        DWORD         SchedulingClass;
    } JOBOBJECT_BASIC_LIMIT_INFORMATION, *PJOBOBJECT_BASIC_LIMIT_INFORMATION;

    typedef struct _JOBOBJECT_BASIC_PROCESS_ID_LIST
    {
        DWORD     NumberOfAssignedProcesses;
        DWORD     NumberOfProcessIdsInList;
        ULONG_PTR ProcessIdList[1];
    } JOBOBJECT_BASIC_PROCESS_ID_LIST, *PJOBOBJECT_BASIC_PROCESS_ID_LIST;

    typedef struct _JOBOBJECT_BASIC_UI_RESTRICTIONS
    {
        DWORD UIRestrictionsClass;
    } JOBOBJECT_BASIC_UI_RESTRICTIONS, *PJOBOBJECT_BASIC_UI_RESTRICTIONS;

    typedef struct _JOBOBJECT_SECURITY_LIMIT_INFORMATION
    {
        DWORD             SecurityLimitFlags;
        HANDLE            JobToken;
        PTOKEN_GROUPS     SidsToDisable;
        PTOKEN_PRIVILEGES PrivilegesToDelete;
        PTOKEN_GROUPS     RestrictedSids;
    } JOBOBJECT_SECURITY_LIMIT_INFORMATION, *PJOBOBJECT_SECURITY_LIMIT_INFORMATION;

    typedef struct _JOBOBJECT_END_OF_JOB_TIME_INFORMATION
    {
        DWORD EndOfJobTimeAction;
    } JOBOBJECT_END_OF_JOB_TIME_INFORMATION, *PJOBOBJECT_END_OF_JOB_TIME_INFORMATION;

    typedef struct _JOBOBJECT_ASSOCIATE_COMPLETION_PORT
    {
        PVOID  CompletionKey;
        HANDLE CompletionPort;
    } JOBOBJECT_ASSOCIATE_COMPLETION_PORT, *PJOBOBJECT_ASSOCIATE_COMPLETION_PORT;

    typedef struct _JOBOBJECT_BASIC_AND_IO_ACCOUNTING_INFORMATION
    {
        JOBOBJECT_BASIC_ACCOUNTING_INFORMATION BasicInfo;
        IO_COUNTERS                            IoInfo;
    } JOBOBJECT_BASIC_AND_IO_ACCOUNTING_INFORMATION, *PJOBOBJECT_BASIC_AND_IO_ACCOUNTING_INFORMATION;

    typedef struct _JOBOBJECT_EXTENDED_LIMIT_INFORMATION
    {
        JOBOBJECT_BASIC_LIMIT_INFORMATION BasicLimitInformation;
        IO_COUNTERS                       IoInfo;
        SIZE_T                            ProcessMemoryLimit;
        SIZE_T                            JobMemoryLimit;
        SIZE_T                            PeakProcessMemoryUsed;
        SIZE_T                            PeakJobMemoryUsed;
    } JOBOBJECT_EXTENDED_LIMIT_INFORMATION, *PJOBOBJECT_EXTENDED_LIMIT_INFORMATION;
    
    typedef enum _JOBOBJECT_RATE_CONTROL_TOLERANCE
    {
        ToleranceLow = 1,
        ToleranceMedium,
        ToleranceHigh
    } JOBOBJECT_RATE_CONTROL_TOLERANCE, *PJOBOBJECT_RATE_CONTROL_TOLERANCE;

    typedef enum _JOBOBJECT_RATE_CONTROL_TOLERANCE_INTERVAL
    {
        ToleranceIntervalShort = 1,
        ToleranceIntervalMedium,
        ToleranceIntervalLong
    } JOBOBJECT_RATE_CONTROL_TOLERANCE_INTERVAL, *PJOBOBJECT_RATE_CONTROL_TOLERANCE_INTERVAL;

    typedef struct _JOBOBJECT_NOTIFICATION_LIMIT_INFORMATION
    {
        DWORD64                                   IoReadBytesLimit;
        DWORD64                                   IoWriteBytesLimit;
        LARGE_INTEGER                             PerJobUserTimeLimit;
        DWORD64                                   JobMemoryLimit;
        JOBOBJECT_RATE_CONTROL_TOLERANCE          RateControlTolerance;
        JOBOBJECT_RATE_CONTROL_TOLERANCE_INTERVAL RateControlToleranceInterval;
        DWORD                                     LimitFlags;
    } JOBOBJECT_NOTIFICATION_LIMIT_INFORMATION, *PJOBOBJECT_NOTIFICATION_LIMIT_INFORMATION;

    typedef struct JOBOBJECT_NOTIFICATION_LIMIT_INFORMATION_2
    {
        DWORD64                                   IoReadBytesLimit;
        DWORD64                                   IoWriteBytesLimit;
        LARGE_INTEGER                             PerJobUserTimeLimit;
        union
        {
            DWORD64 JobHighMemoryLimit;
            DWORD64 JobMemoryLimit;
        } DUMMYUNIONNAME;
        union
        {
            JOBOBJECT_RATE_CONTROL_TOLERANCE RateControlTolerance;
            JOBOBJECT_RATE_CONTROL_TOLERANCE CpuRateControlTolerance;
        } DUMMYUNIONNAME2;
        union
        {
            JOBOBJECT_RATE_CONTROL_TOLERANCE_INTERVAL RateControlToleranceInterval;
            JOBOBJECT_RATE_CONTROL_TOLERANCE_INTERVAL CpuRateControlToleranceInterval;
        } DUMMYUNIONNAME3;
        DWORD                                     LimitFlags;
        JOBOBJECT_RATE_CONTROL_TOLERANCE          IoRateControlTolerance;
        DWORD64                                   JobLowMemoryLimit;
        JOBOBJECT_RATE_CONTROL_TOLERANCE_INTERVAL IoRateControlToleranceInterval;
        JOBOBJECT_RATE_CONTROL_TOLERANCE          NetRateControlTolerance;
        JOBOBJECT_RATE_CONTROL_TOLERANCE_INTERVAL NetRateControlToleranceInterval;
    } JOBOBJECT_NOTIFICATION_LIMIT_INFORMATION_2;

    typedef struct _JOBOBJECT_LIMIT_VIOLATION_INFORMATION
    {
        DWORD                            LimitFlags;
        DWORD                            ViolationLimitFlags;
        DWORD64                          IoReadBytes;
        DWORD64                          IoReadBytesLimit;
        DWORD64                          IoWriteBytes;
        DWORD64                          IoWriteBytesLimit;
        LARGE_INTEGER                    PerJobUserTime;
        LARGE_INTEGER                    PerJobUserTimeLimit;
        DWORD64                          JobMemory;
        DWORD64                          JobMemoryLimit;
        JOBOBJECT_RATE_CONTROL_TOLERANCE RateControlTolerance;
        JOBOBJECT_RATE_CONTROL_TOLERANCE RateControlToleranceLimit;
    } JOBOBJECT_LIMIT_VIOLATION_INFORMATION, *PJOBOBJECT_LIMIT_VIOLATION_INFORMATION;

    typedef struct JOBOBJECT_LIMIT_VIOLATION_INFORMATION_2
    {
        DWORD                            LimitFlags;
        DWORD                            ViolationLimitFlags;
        DWORD64                          IoReadBytes;
        DWORD64                          IoReadBytesLimit;
        DWORD64                          IoWriteBytes;
        DWORD64                          IoWriteBytesLimit;
        LARGE_INTEGER                    PerJobUserTime;
        LARGE_INTEGER                    PerJobUserTimeLimit;
        DWORD64                          JobMemory;
        union
        {
            DWORD64 JobHighMemoryLimit;
            DWORD64 JobMemoryLimit;
        } DUMMYUNIONNAME;
        union
        {
            JOBOBJECT_RATE_CONTROL_TOLERANCE RateControlTolerance;
            JOBOBJECT_RATE_CONTROL_TOLERANCE CpuRateControlTolerance;
        } DUMMYUNIONNAME2;
        union
        {
            JOBOBJECT_RATE_CONTROL_TOLERANCE RateControlToleranceLimit;
            JOBOBJECT_RATE_CONTROL_TOLERANCE CpuRateControlToleranceLimit;
        } DUMMYUNIONNAME3;
        DWORD64                          JobLowMemoryLimit;
        JOBOBJECT_RATE_CONTROL_TOLERANCE IoRateControlTolerance;
        JOBOBJECT_RATE_CONTROL_TOLERANCE IoRateControlToleranceLimit;
        JOBOBJECT_RATE_CONTROL_TOLERANCE NetRateControlTolerance;
        JOBOBJECT_RATE_CONTROL_TOLERANCE NetRateControlToleranceLimit;
    } JOBOBJECT_LIMIT_VIOLATION_INFORMATION_2;

    typedef struct _JOBOBJECT_CPU_RATE_CONTROL_INFORMATION
    {
        DWORD ControlFlags;
        union
        {
            DWORD CpuRate;
            DWORD Weight;
            struct
            {
                WORD MinRate;
                WORD MaxRate;
            } DUMMYSTRUCTNAME;
        } DUMMYUNIONNAME;
    } JOBOBJECT_CPU_RATE_CONTROL_INFORMATION, *PJOBOBJECT_CPU_RATE_CONTROL_INFORMATION;
    
    typedef enum JOB_OBJECT_NET_RATE_CONTROL_FLAGS
    {
        JOB_OBJECT_NET_RATE_CONTROL_ENABLE          = 0x1,
        JOB_OBJECT_NET_RATE_CONTROL_MAX_BANDWIDTH   = 0x2,
        JOB_OBJECT_NET_RATE_CONTROL_DSCP_TAG        = 0x4,
        JOB_OBJECT_NET_RATE_CONTROL_VALID_FLAGS     = 0x7,
    } JOB_OBJECT_NET_RATE_CONTROL_FLAGS;

    typedef struct JOBOBJECT_NET_RATE_CONTROL_INFORMATION
    {
        DWORD64                           MaxBandwidth;
        JOB_OBJECT_NET_RATE_CONTROL_FLAGS ControlFlags;
        BYTE                              DscpTag;
    } JOBOBJECT_NET_RATE_CONTROL_INFORMATION;

    // private
    typedef struct _JOBOBJECT_EXTENDED_ACCOUNTING_INFORMATION
    {
        JOBOBJECT_BASIC_ACCOUNTING_INFORMATION BasicInfo;
        IO_COUNTERS IoInfo;
        PROCESS_DISK_COUNTERS DiskIoInfo;
        ULONG64 ContextSwitches;
        LARGE_INTEGER TotalCycleTime;
        ULONG64 ReadyTime;
        PROCESS_ENERGY_VALUES EnergyValues;
    } JOBOBJECT_EXTENDED_ACCOUNTING_INFORMATION, *PJOBOBJECT_EXTENDED_ACCOUNTING_INFORMATION;

    // private
    typedef struct _JOBOBJECT_WAKE_INFORMATION
    {
        HANDLE NotificationChannel;
        ULONG64 WakeCounters[7];
    } JOBOBJECT_WAKE_INFORMATION, *PJOBOBJECT_WAKE_INFORMATION;

    // private
    typedef struct _JOBOBJECT_WAKE_INFORMATION_V1
    {
        HANDLE NotificationChannel;
        ULONG64 WakeCounters[4];
    } JOBOBJECT_WAKE_INFORMATION_V1, *PJOBOBJECT_WAKE_INFORMATION_V1;

    // private
    typedef struct _JOBOBJECT_INTERFERENCE_INFORMATION
    {
        ULONG64 Count;
    } JOBOBJECT_INTERFERENCE_INFORMATION, *PJOBOBJECT_INTERFERENCE_INFORMATION;

    // private
    typedef struct _JOBOBJECT_FREEZE_INFORMATION
    {
        union
        {
            ULONG Flags;
            struct
            {
                ULONG FreezeOperation : 1;
                ULONG FilterOperation : 1;
                ULONG SwapOperation : 1;
                ULONG Reserved : 29;
            };
        };
        BOOLEAN Freeze;
        BOOLEAN Swap;
        UCHAR Reserved0[2];
        JOBOBJECT_WAKE_FILTER WakeFilter;
    } JOBOBJECT_FREEZE_INFORMATION, *PJOBOBJECT_FREEZE_INFORMATION;

    // private
    typedef struct _JOBOBJECT_MEMORY_USAGE_INFORMATION
    {
        ULONG64 JobMemory;
        ULONG64 PeakJobMemoryUsed;
    } JOBOBJECT_MEMORY_USAGE_INFORMATION, *PJOBOBJECT_MEMORY_USAGE_INFORMATION;

    // private
    typedef struct _JOBOBJECT_MEMORY_USAGE_INFORMATION_V2
    {
        JOBOBJECT_MEMORY_USAGE_INFORMATION BasicInfo;
        ULONG64 JobSharedMemory;
        ULONG64 Reserved[2];
    } JOBOBJECT_MEMORY_USAGE_INFORMATION_V2, *PJOBOBJECT_MEMORY_USAGE_INFORMATION_V2;

    // private
    typedef struct _SILO_USER_SHARED_DATA
    {
        ULONG64 ServiceSessionId;
        ULONG ActiveConsoleId;
        LONGLONG ConsoleSessionForegroundProcessId;
        NT_PRODUCT_TYPE NtProductType;
        ULONG SuiteMask;
        ULONG SharedUserSessionId;
        BOOLEAN IsMultiSessionSku;
        WCHAR NtSystemRoot[260];
        USHORT UserModeGlobalLogger[16];
    } SILO_USER_SHARED_DATA, *PSILO_USER_SHARED_DATA;

    // private
    typedef struct _SILOOBJECT_ROOT_DIRECTORY
    {
        ULONG ControlFlags;
        UNICODE_STRING Path;
    } SILOOBJECT_ROOT_DIRECTORY, *PSILOOBJECT_ROOT_DIRECTORY;

    // private
    typedef struct _JOBOBJECT_ENERGY_TRACKING_STATE
    {
        ULONG64 Value;
        ULONG UpdateMask;
        ULONG DesiredState;
    } JOBOBJECT_ENERGY_TRACKING_STATE, *PJOBOBJECT_ENERGY_TRACKING_STATE;
#pragma endregion


#pragma region Section
    typedef enum _SECTION_INFORMATION_CLASS
    {
        SectionBasicInformation,        // q; SECTION_BASIC_INFORMATION
        SectionImageInformation,        // q; SECTION_IMAGE_INFORMATION
        SectionRelocationInformation,   // name:wow64:whNtQuerySection_SectionRelocationInformation
        SectionOriginalBaseInformation, // PVOID BaseAddress
        SectionInternalImageInformation,// SECTION_INTERNAL_IMAGE_INFORMATION // since REDSTONE2
        MaxSectionInfoClass
    } SECTION_INFORMATION_CLASS;

    typedef struct _SECTION_BASIC_INFORMATION
    {
        PVOID BaseAddress;
        ULONG AllocationAttributes;
        LARGE_INTEGER MaximumSize;
    } SECTION_BASIC_INFORMATION, *PSECTION_BASIC_INFORMATION;

    // symbols
    typedef struct _SECTION_IMAGE_INFORMATION
    {
        PVOID TransferAddress;
        ULONG ZeroBits;
        SIZE_T MaximumStackSize;
        SIZE_T CommittedStackSize;
        ULONG SubSystemType;
        union
        {
            struct
            {
                USHORT SubSystemMinorVersion;
                USHORT SubSystemMajorVersion;
            };
            ULONG SubSystemVersion;
        };
        union
        {
            struct
            {
                USHORT MajorOperatingSystemVersion;
                USHORT MinorOperatingSystemVersion;
            };
            ULONG OperatingSystemVersion;
        };
        USHORT ImageCharacteristics;
        USHORT DllCharacteristics;
        USHORT Machine;
        BOOLEAN ImageContainsCode;
        union
        {
            UCHAR ImageFlags;
            struct
            {
                UCHAR ComPlusNativeReady : 1;
                UCHAR ComPlusILOnly : 1;
                UCHAR ImageDynamicallyRelocated : 1;
                UCHAR ImageMappedFlat : 1;
                UCHAR BaseBelow4gb : 1;
                UCHAR ComPlusPrefer32bit : 1;
                UCHAR Reserved : 2;
            };
        };
        ULONG LoaderFlags;
        ULONG ImageFileSize;
        ULONG CheckSum;
    } SECTION_IMAGE_INFORMATION, *PSECTION_IMAGE_INFORMATION;

    // symbols
    typedef struct _SECTION_INTERNAL_IMAGE_INFORMATION
    {
        SECTION_IMAGE_INFORMATION SectionInformation;
        union
        {
            ULONG ExtendedFlags;
            struct
            {
                ULONG ImageExportSuppressionEnabled : 1;
                ULONG Reserved : 31;
            };
        };
    } SECTION_INTERNAL_IMAGE_INFORMATION, *PSECTION_INTERNAL_IMAGE_INFORMATION;
#pragma endregion


#pragma region System
    // rev
    // private
    typedef enum _SYSTEM_INFORMATION_CLASS
    {
        SystemBasicInformation, // q: SYSTEM_BASIC_INFORMATION
        SystemProcessorInformation, // q: SYSTEM_PROCESSOR_INFORMATION
        SystemPerformanceInformation, // q: SYSTEM_PERFORMANCE_INFORMATION
        SystemTimeOfDayInformation, // q: SYSTEM_TIMEOFDAY_INFORMATION
        SystemPathInformation, // not implemented
        SystemProcessInformation, // q: SYSTEM_PROCESS_INFORMATION
        SystemCallCountInformation, // q: SYSTEM_CALL_COUNT_INFORMATION
        SystemDeviceInformation, // q: SYSTEM_DEVICE_INFORMATION
        SystemProcessorPerformanceInformation, // q: SYSTEM_PROCESSOR_PERFORMANCE_INFORMATION
        SystemFlagsInformation, // q: SYSTEM_FLAGS_INFORMATION
        SystemCallTimeInformation, // not implemented // SYSTEM_CALL_TIME_INFORMATION // 10
        SystemModuleInformation, // q: RTL_PROCESS_MODULES
        SystemLocksInformation, // q: RTL_PROCESS_LOCKS
        SystemStackTraceInformation, // q: RTL_PROCESS_BACKTRACES
        SystemPagedPoolInformation, // not implemented
        SystemNonPagedPoolInformation, // not implemented
        SystemHandleInformation, // q: SYSTEM_HANDLE_INFORMATION
        SystemObjectInformation, // q: SYSTEM_OBJECTTYPE_INFORMATION mixed with SYSTEM_OBJECT_INFORMATION
        SystemPageFileInformation, // q: SYSTEM_PAGEFILE_INFORMATION
        SystemVdmInstemulInformation, // q
        SystemVdmBopInformation, // not implemented // 20
        SystemFileCacheInformation, // q: SYSTEM_FILECACHE_INFORMATION; s (requires SeIncreaseQuotaPrivilege) (info for WorkingSetTypeSystemCache)
        SystemPoolTagInformation, // q: SYSTEM_POOLTAG_INFORMATION
        SystemInterruptInformation, // q: SYSTEM_INTERRUPT_INFORMATION
        SystemDpcBehaviorInformation, // q: SYSTEM_DPC_BEHAVIOR_INFORMATION; s: SYSTEM_DPC_BEHAVIOR_INFORMATION (requires SeLoadDriverPrivilege)
        SystemFullMemoryInformation, // not implemented
        SystemLoadGdiDriverInformation, // s (kernel-mode only)
        SystemUnloadGdiDriverInformation, // s (kernel-mode only)
        SystemTimeAdjustmentInformation, // q: SYSTEM_QUERY_TIME_ADJUST_INFORMATION; s: SYSTEM_SET_TIME_ADJUST_INFORMATION (requires SeSystemtimePrivilege)
        SystemSummaryMemoryInformation, // not implemented
        SystemMirrorMemoryInformation, // s (requires license value "Kernel-MemoryMirroringSupported") (requires SeShutdownPrivilege) // 30
        SystemPerformanceTraceInformation, // q; s: (type depends on EVENT_TRACE_INFORMATION_CLASS)
        SystemObsolete0, // not implemented
        SystemExceptionInformation, // q: SYSTEM_EXCEPTION_INFORMATION
        SystemCrashDumpStateInformation, // s (requires SeDebugPrivilege)
        SystemKernelDebuggerInformation, // q: SYSTEM_KERNEL_DEBUGGER_INFORMATION
        SystemContextSwitchInformation, // q: SYSTEM_CONTEXT_SWITCH_INFORMATION
        SystemRegistryQuotaInformation, // q: SYSTEM_REGISTRY_QUOTA_INFORMATION; s (requires SeIncreaseQuotaPrivilege)
        SystemExtendServiceTableInformation, // s (requires SeLoadDriverPrivilege) // loads win32k only
        SystemPrioritySeperation, // s (requires SeTcbPrivilege)
        SystemVerifierAddDriverInformation, // s (requires SeDebugPrivilege) // 40
        SystemVerifierRemoveDriverInformation, // s (requires SeDebugPrivilege)
        SystemProcessorIdleInformation, // q: SYSTEM_PROCESSOR_IDLE_INFORMATION
        SystemLegacyDriverInformation, // q: SYSTEM_LEGACY_DRIVER_INFORMATION
        SystemCurrentTimeZoneInformation, // q; s: RTL_TIME_ZONE_INFORMATION
        SystemLookasideInformation, // q: SYSTEM_LOOKASIDE_INFORMATION
        SystemTimeSlipNotification, // s (requires SeSystemtimePrivilege)
        SystemSessionCreate, // not implemented
        SystemSessionDetach, // not implemented
        SystemSessionInformation, // not implemented (SYSTEM_SESSION_INFORMATION)
        SystemRangeStartInformation, // q: SYSTEM_RANGE_START_INFORMATION // 50
        SystemVerifierInformation, // q: SYSTEM_VERIFIER_INFORMATION; s (requires SeDebugPrivilege)
        SystemVerifierThunkExtend, // s (kernel-mode only)
        SystemSessionProcessInformation, // q: SYSTEM_SESSION_PROCESS_INFORMATION
        SystemLoadGdiDriverInSystemSpace, // s (kernel-mode only) (same as SystemLoadGdiDriverInformation)
        SystemNumaProcessorMap, // q
        SystemPrefetcherInformation, // q: PREFETCHER_INFORMATION; s: PREFETCHER_INFORMATION // PfSnQueryPrefetcherInformation
        SystemExtendedProcessInformation, // q: SYSTEM_PROCESS_INFORMATION
        SystemRecommendedSharedDataAlignment, // q
        SystemComPlusPackage, // q; s
        SystemNumaAvailableMemory, // 60
        SystemProcessorPowerInformation, // q: SYSTEM_PROCESSOR_POWER_INFORMATION
        SystemEmulationBasicInformation, // q
        SystemEmulationProcessorInformation,
        SystemExtendedHandleInformation, // q: SYSTEM_HANDLE_INFORMATION_EX
        SystemLostDelayedWriteInformation, // q: ULONG
        SystemBigPoolInformation, // q: SYSTEM_BIGPOOL_INFORMATION
        SystemSessionPoolTagInformation, // q: SYSTEM_SESSION_POOLTAG_INFORMATION
        SystemSessionMappedViewInformation, // q: SYSTEM_SESSION_MAPPED_VIEW_INFORMATION
        SystemHotpatchInformation, // q; s: SYSTEM_HOTPATCH_CODE_INFORMATION
        SystemObjectSecurityMode, // q: ULONG // 70
        SystemWatchdogTimerHandler, // s (kernel-mode only)
        SystemWatchdogTimerInformation, // q (kernel-mode only); s (kernel-mode only)
        SystemLogicalProcessorInformation, // q: SYSTEM_LOGICAL_PROCESSOR_INFORMATION
        SystemWow64SharedInformationObsolete, // not implemented
        SystemRegisterFirmwareTableInformationHandler, // s (kernel-mode only)
        SystemFirmwareTableInformation, // SYSTEM_FIRMWARE_TABLE_INFORMATION
        SystemModuleInformationEx, // q: RTL_PROCESS_MODULE_INFORMATION_EX
        SystemVerifierTriageInformation, // not implemented
        SystemSuperfetchInformation, // q; s: SUPERFETCH_INFORMATION // PfQuerySuperfetchInformation
        SystemMemoryListInformation, // q: SYSTEM_MEMORY_LIST_INFORMATION; s: SYSTEM_MEMORY_LIST_COMMAND (requires SeProfileSingleProcessPrivilege) // 80
        SystemFileCacheInformationEx, // q: SYSTEM_FILECACHE_INFORMATION; s (requires SeIncreaseQuotaPrivilege) (same as SystemFileCacheInformation)
        SystemThreadPriorityClientIdInformation, // s: SYSTEM_THREAD_CID_PRIORITY_INFORMATION (requires SeIncreaseBasePriorityPrivilege)
        SystemProcessorIdleCycleTimeInformation, // q: SYSTEM_PROCESSOR_IDLE_CYCLE_TIME_INFORMATION[]
        SystemVerifierCancellationInformation, // not implemented // name:wow64:whNT32QuerySystemVerifierCancellationInformation
        SystemProcessorPowerInformationEx, // not implemented
        SystemRefTraceInformation, // q; s: SYSTEM_REF_TRACE_INFORMATION // ObQueryRefTraceInformation
        SystemSpecialPoolInformation, // q; s (requires SeDebugPrivilege) // MmSpecialPoolTag, then MmSpecialPoolCatchOverruns != 0
        SystemProcessIdInformation, // q: SYSTEM_PROCESS_ID_INFORMATION
        SystemErrorPortInformation, // s (requires SeTcbPrivilege)
        SystemBootEnvironmentInformation, // q: SYSTEM_BOOT_ENVIRONMENT_INFORMATION // 90
        SystemHypervisorInformation, // q; s (kernel-mode only)
        SystemVerifierInformationEx, // q; s: SYSTEM_VERIFIER_INFORMATION_EX
        SystemTimeZoneInformation, // s (requires SeTimeZonePrivilege)
        SystemImageFileExecutionOptionsInformation, // s: SYSTEM_IMAGE_FILE_EXECUTION_OPTIONS_INFORMATION (requires SeTcbPrivilege)
        SystemCoverageInformation, // q; s // name:wow64:whNT32QuerySystemCoverageInformation; ExpCovQueryInformation
        SystemPrefetchPatchInformation, // not implemented
        SystemVerifierFaultsInformation, // s (requires SeDebugPrivilege)
        SystemSystemPartitionInformation, // q: SYSTEM_SYSTEM_PARTITION_INFORMATION
        SystemSystemDiskInformation, // q: SYSTEM_SYSTEM_DISK_INFORMATION
        SystemProcessorPerformanceDistribution, // q: SYSTEM_PROCESSOR_PERFORMANCE_DISTRIBUTION // 100
        SystemNumaProximityNodeInformation, // q
        SystemDynamicTimeZoneInformation, // q; s (requires SeTimeZonePrivilege)
        SystemCodeIntegrityInformation, // q: SYSTEM_CODEINTEGRITY_INFORMATION // SeCodeIntegrityQueryInformation
        SystemProcessorMicrocodeUpdateInformation, // s
        SystemProcessorBrandString, // q // HaliQuerySystemInformation -> HalpGetProcessorBrandString, info class 23
        SystemVirtualAddressInformation, // q: SYSTEM_VA_LIST_INFORMATION[]; s: SYSTEM_VA_LIST_INFORMATION[] (requires SeIncreaseQuotaPrivilege) // MmQuerySystemVaInformation
        SystemLogicalProcessorAndGroupInformation, // q: SYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX // since WIN7 // KeQueryLogicalProcessorRelationship
        SystemProcessorCycleTimeInformation, // q: SYSTEM_PROCESSOR_CYCLE_TIME_INFORMATION[]
        SystemStoreInformation, // q; s // SmQueryStoreInformation
        SystemRegistryAppendString, // s: SYSTEM_REGISTRY_APPEND_STRING_PARAMETERS // 110
        SystemAitSamplingValue, // s: ULONG (requires SeProfileSingleProcessPrivilege)
        SystemVhdBootInformation, // q: SYSTEM_VHD_BOOT_INFORMATION
        SystemCpuQuotaInformation, // q; s // PsQueryCpuQuotaInformation
        SystemNativeBasicInformation, // not implemented
        SystemSpare1, // not implemented
        SystemLowPriorityIoInformation, // q: SYSTEM_LOW_PRIORITY_IO_INFORMATION
        SystemTpmBootEntropyInformation, // q: TPM_BOOT_ENTROPY_NT_RESULT // ExQueryTpmBootEntropyInformation
        SystemVerifierCountersInformation, // q: SYSTEM_VERIFIER_COUNTERS_INFORMATION
        SystemPagedPoolInformationEx, // q: SYSTEM_FILECACHE_INFORMATION; s (requires SeIncreaseQuotaPrivilege) (info for WorkingSetTypePagedPool)
        SystemSystemPtesInformationEx, // q: SYSTEM_FILECACHE_INFORMATION; s (requires SeIncreaseQuotaPrivilege) (info for WorkingSetTypeSystemPtes) // 120
        SystemNodeDistanceInformation, // q
        SystemAcpiAuditInformation, // q: SYSTEM_ACPI_AUDIT_INFORMATION // HaliQuerySystemInformation -> HalpAuditQueryResults, info class 26
        SystemBasicPerformanceInformation, // q: SYSTEM_BASIC_PERFORMANCE_INFORMATION // name:wow64:whNtQuerySystemInformation_SystemBasicPerformanceInformation
        SystemQueryPerformanceCounterInformation, // q: SYSTEM_QUERY_PERFORMANCE_COUNTER_INFORMATION // since WIN7 SP1
        SystemSessionBigPoolInformation, // q: SYSTEM_SESSION_POOLTAG_INFORMATION // since WIN8
        SystemBootGraphicsInformation, // q; s: SYSTEM_BOOT_GRAPHICS_INFORMATION (kernel-mode only)
        SystemScrubPhysicalMemoryInformation, // q; s: MEMORY_SCRUB_INFORMATION
        SystemBadPageInformation,
        SystemProcessorProfileControlArea, // q; s: SYSTEM_PROCESSOR_PROFILE_CONTROL_AREA
        SystemCombinePhysicalMemoryInformation, // s: MEMORY_COMBINE_INFORMATION, MEMORY_COMBINE_INFORMATION_EX, MEMORY_COMBINE_INFORMATION_EX2 // 130
        SystemEntropyInterruptTimingCallback,
        SystemConsoleInformation, // q: SYSTEM_CONSOLE_INFORMATION
        SystemPlatformBinaryInformation, // q: SYSTEM_PLATFORM_BINARY_INFORMATION
        SystemThrottleNotificationInformation,
        SystemHypervisorProcessorCountInformation, // q: SYSTEM_HYPERVISOR_PROCESSOR_COUNT_INFORMATION
        SystemDeviceDataInformation, // q: SYSTEM_DEVICE_DATA_INFORMATION
        SystemDeviceDataEnumerationInformation,
        SystemMemoryTopologyInformation, // q: SYSTEM_MEMORY_TOPOLOGY_INFORMATION
        SystemMemoryChannelInformation, // q: SYSTEM_MEMORY_CHANNEL_INFORMATION
        SystemBootLogoInformation, // q: SYSTEM_BOOT_LOGO_INFORMATION // 140
        SystemProcessorPerformanceInformationEx, // q: SYSTEM_PROCESSOR_PERFORMANCE_INFORMATION_EX // since WINBLUE
        SystemSpare0,
        SystemSecureBootPolicyInformation, // q: SYSTEM_SECUREBOOT_POLICY_INFORMATION
        SystemPageFileInformationEx, // q: SYSTEM_PAGEFILE_INFORMATION_EX
        SystemSecureBootInformation, // q: SYSTEM_SECUREBOOT_INFORMATION
        SystemEntropyInterruptTimingRawInformation,
        SystemPortableWorkspaceEfiLauncherInformation, // q: SYSTEM_PORTABLE_WORKSPACE_EFI_LAUNCHER_INFORMATION
        SystemFullProcessInformation, // q: SYSTEM_PROCESS_INFORMATION with SYSTEM_PROCESS_INFORMATION_EXTENSION (requires admin)
        SystemKernelDebuggerInformationEx, // q: SYSTEM_KERNEL_DEBUGGER_INFORMATION_EX
        SystemBootMetadataInformation, // 150
        SystemSoftRebootInformation,
        SystemElamCertificateInformation, // s: SYSTEM_ELAM_CERTIFICATE_INFORMATION
        SystemOfflineDumpConfigInformation,
        SystemProcessorFeaturesInformation, // q: SYSTEM_PROCESSOR_FEATURES_INFORMATION
        SystemRegistryReconciliationInformation,
        SystemEdidInformation,
        SystemManufacturingInformation, // q: SYSTEM_MANUFACTURING_INFORMATION // since THRESHOLD
        SystemEnergyEstimationConfigInformation, // q: SYSTEM_ENERGY_ESTIMATION_CONFIG_INFORMATION
        SystemHypervisorDetailInformation, // q: SYSTEM_HYPERVISOR_DETAIL_INFORMATION
        SystemProcessorCycleStatsInformation, // q: SYSTEM_PROCESSOR_CYCLE_STATS_INFORMATION // 160
        SystemVmGenerationCountInformation,
        SystemTrustedPlatformModuleInformation, // q: SYSTEM_TPM_INFORMATION
        SystemKernelDebuggerFlags,
        SystemCodeIntegrityPolicyInformation, // q: SYSTEM_CODEINTEGRITYPOLICY_INFORMATION
        SystemIsolatedUserModeInformation, // q: SYSTEM_ISOLATED_USER_MODE_INFORMATION
        SystemHardwareSecurityTestInterfaceResultsInformation,
        SystemSingleModuleInformation, // q: SYSTEM_SINGLE_MODULE_INFORMATION
        SystemAllowedCpuSetsInformation,
        SystemDmaProtectionInformation, // q: SYSTEM_DMA_PROTECTION_INFORMATION
        SystemInterruptCpuSetsInformation, // q: SYSTEM_INTERRUPT_CPU_SET_INFORMATION // 170
        SystemSecureBootPolicyFullInformation, // q: SYSTEM_SECUREBOOT_POLICY_FULL_INFORMATION
        SystemCodeIntegrityPolicyFullInformation,
        SystemAffinitizedInterruptProcessorInformation,
        SystemRootSiloInformation, // q: SYSTEM_ROOT_SILO_INFORMATION
        SystemCpuSetInformation, // q: SYSTEM_CPU_SET_INFORMATION // since THRESHOLD2
        SystemCpuSetTagInformation, // q: SYSTEM_CPU_SET_TAG_INFORMATION
        SystemWin32WerStartCallout,
        SystemSecureKernelProfileInformation, // q: SYSTEM_SECURE_KERNEL_HYPERGUARD_PROFILE_INFORMATION
        SystemCodeIntegrityPlatformManifestInformation, // q: SYSTEM_SECUREBOOT_PLATFORM_MANIFEST_INFORMATION // since REDSTONE
        SystemInterruptSteeringInformation, // 180
        SystemSupportedProcessorArchitectures,
        SystemMemoryUsageInformation, // q: SYSTEM_MEMORY_USAGE_INFORMATION
        SystemCodeIntegrityCertificateInformation, // q: SYSTEM_CODEINTEGRITY_CERTIFICATE_INFORMATION
        SystemPhysicalMemoryInformation, // q: SYSTEM_PHYSICAL_MEMORY_INFORMATION // since REDSTONE2
        SystemControlFlowTransition,
        SystemKernelDebuggingAllowed,
        SystemActivityModerationExeState, // SYSTEM_ACTIVITY_MODERATION_EXE_STATE
        SystemActivityModerationUserSettings, // SYSTEM_ACTIVITY_MODERATION_USER_SETTINGS
        SystemCodeIntegrityPoliciesFullInformation,
        SystemCodeIntegrityUnlockInformation, // SYSTEM_CODEINTEGRITY_UNLOCK_INFORMATION // 190
        SystemIntegrityQuotaInformation,
        SystemFlushInformation, // q: SYSTEM_FLUSH_INFORMATION
        SystemProcessorIdleMaskInformation, // since REDSTONE3
        SystemSecureDumpEncryptionInformation,
        SystemWriteConstraintInformation, // SYSTEM_WRITE_CONSTRAINT_INFORMATION
        SystemKernelVaShadowInformation, // SYSTEM_KERNEL_VA_SHADOW_INFORMATION
        SystemHypervisorSharedPageInformation, // SYSTEM_HYPERVISOR_SHARED_PAGE_INFORMATION // since REDSTONE4
        SystemFirmwareBootPerformanceInformation,
        SystemCodeIntegrityVerificationInformation, // SYSTEM_CODEINTEGRITYVERIFICATION_INFORMATION
        SystemFirmwarePartitionInformation, // 200
        SystemSpeculationControlInformation, // SYSTEM_SPECULATION_CONTROL_INFORMATION // (CVE-2017-5715) REDSTONE3 and above.
        SystemDmaGuardPolicyInformation, // SYSTEM_DMA_GUARD_POLICY_INFORMATION
        SystemEnclaveLaunchControlInformation, // SYSTEM_ENCLAVE_LAUNCH_CONTROL_INFORMATION
        MaxSystemInfoClass
    } SYSTEM_INFORMATION_CLASS;

    typedef struct _SYSTEM_BASIC_INFORMATION
    {
        ULONG Reserved;
        ULONG TimerResolution;
        ULONG PageSize;
        ULONG NumberOfPhysicalPages;
        ULONG LowestPhysicalPageNumber;
        ULONG HighestPhysicalPageNumber;
        ULONG AllocationGranularity;
        ULONG_PTR MinimumUserModeAddress;
        ULONG_PTR MaximumUserModeAddress;
        ULONG_PTR ActiveProcessorsAffinityMask;
        CCHAR NumberOfProcessors;
    } SYSTEM_BASIC_INFORMATION, *PSYSTEM_BASIC_INFORMATION;

    typedef struct _SYSTEM_PROCESSOR_INFORMATION
    {
        USHORT ProcessorArchitecture;
        USHORT ProcessorLevel;
        USHORT ProcessorRevision;
        USHORT MaximumProcessors;
        ULONG ProcessorFeatureBits;
    } SYSTEM_PROCESSOR_INFORMATION, *PSYSTEM_PROCESSOR_INFORMATION;

    typedef struct _SYSTEM_PERFORMANCE_INFORMATION
    {
        LARGE_INTEGER IdleProcessTime;
        LARGE_INTEGER IoReadTransferCount;
        LARGE_INTEGER IoWriteTransferCount;
        LARGE_INTEGER IoOtherTransferCount;
        ULONG IoReadOperationCount;
        ULONG IoWriteOperationCount;
        ULONG IoOtherOperationCount;
        ULONG AvailablePages;
        ULONG CommittedPages;
        ULONG CommitLimit;
        ULONG PeakCommitment;
        ULONG PageFaultCount;
        ULONG CopyOnWriteCount;
        ULONG TransitionCount;
        ULONG CacheTransitionCount;
        ULONG DemandZeroCount;
        ULONG PageReadCount;
        ULONG PageReadIoCount;
        ULONG CacheReadCount;
        ULONG CacheIoCount;
        ULONG DirtyPagesWriteCount;
        ULONG DirtyWriteIoCount;
        ULONG MappedPagesWriteCount;
        ULONG MappedWriteIoCount;
        ULONG PagedPoolPages;
        ULONG NonPagedPoolPages;
        ULONG PagedPoolAllocs;
        ULONG PagedPoolFrees;
        ULONG NonPagedPoolAllocs;
        ULONG NonPagedPoolFrees;
        ULONG FreeSystemPtes;
        ULONG ResidentSystemCodePage;
        ULONG TotalSystemDriverPages;
        ULONG TotalSystemCodePages;
        ULONG NonPagedPoolLookasideHits;
        ULONG PagedPoolLookasideHits;
        ULONG AvailablePagedPoolPages;
        ULONG ResidentSystemCachePage;
        ULONG ResidentPagedPoolPage;
        ULONG ResidentSystemDriverPage;
        ULONG CcFastReadNoWait;
        ULONG CcFastReadWait;
        ULONG CcFastReadResourceMiss;
        ULONG CcFastReadNotPossible;
        ULONG CcFastMdlReadNoWait;
        ULONG CcFastMdlReadWait;
        ULONG CcFastMdlReadResourceMiss;
        ULONG CcFastMdlReadNotPossible;
        ULONG CcMapDataNoWait;
        ULONG CcMapDataWait;
        ULONG CcMapDataNoWaitMiss;
        ULONG CcMapDataWaitMiss;
        ULONG CcPinMappedDataCount;
        ULONG CcPinReadNoWait;
        ULONG CcPinReadWait;
        ULONG CcPinReadNoWaitMiss;
        ULONG CcPinReadWaitMiss;
        ULONG CcCopyReadNoWait;
        ULONG CcCopyReadWait;
        ULONG CcCopyReadNoWaitMiss;
        ULONG CcCopyReadWaitMiss;
        ULONG CcMdlReadNoWait;
        ULONG CcMdlReadWait;
        ULONG CcMdlReadNoWaitMiss;
        ULONG CcMdlReadWaitMiss;
        ULONG CcReadAheadIos;
        ULONG CcLazyWriteIos;
        ULONG CcLazyWritePages;
        ULONG CcDataFlushes;
        ULONG CcDataPages;
        ULONG ContextSwitches;
        ULONG FirstLevelTbFills;
        ULONG SecondLevelTbFills;
        ULONG SystemCalls;
        ULONGLONG CcTotalDirtyPages; // since THRESHOLD
        ULONGLONG CcDirtyPageThreshold; // since THRESHOLD
        LONGLONG ResidentAvailablePages; // since THRESHOLD
        ULONGLONG SharedCommittedPages; // since THRESHOLD
    } SYSTEM_PERFORMANCE_INFORMATION, *PSYSTEM_PERFORMANCE_INFORMATION;

    typedef struct _SYSTEM_TIMEOFDAY_INFORMATION
    {
        LARGE_INTEGER BootTime;
        LARGE_INTEGER CurrentTime;
        LARGE_INTEGER TimeZoneBias;
        ULONG TimeZoneId;
        ULONG Reserved;
        ULONGLONG BootTimeBias;
        ULONGLONG SleepTimeBias;
    } SYSTEM_TIMEOFDAY_INFORMATION, *PSYSTEM_TIMEOFDAY_INFORMATION;

    typedef struct _SYSTEM_THREAD_INFORMATION
    {
        LARGE_INTEGER KernelTime;
        LARGE_INTEGER UserTime;
        LARGE_INTEGER CreateTime;
        ULONG WaitTime;
        PVOID StartAddress;
        CLIENT_ID ClientId;
        KPRIORITY Priority;
        LONG BasePriority;
        ULONG ContextSwitches;
        ULONG ThreadState;
        KWAIT_REASON WaitReason;
    } SYSTEM_THREAD_INFORMATION, *PSYSTEM_THREAD_INFORMATION;

    typedef struct _TEB *PTEB;

    // private
    typedef struct _SYSTEM_EXTENDED_THREAD_INFORMATION
    {
        SYSTEM_THREAD_INFORMATION ThreadInfo;
        PVOID StackBase;
        PVOID StackLimit;
        PVOID Win32StartAddress;
        PTEB TebBase; // since VISTA
        ULONG_PTR Reserved2;
        ULONG_PTR Reserved3;
        ULONG_PTR Reserved4;
    } SYSTEM_EXTENDED_THREAD_INFORMATION, *PSYSTEM_EXTENDED_THREAD_INFORMATION;

    typedef struct _SYSTEM_PROCESS_INFORMATION
    {
        ULONG NextEntryOffset;
        ULONG NumberOfThreads;
        LARGE_INTEGER WorkingSetPrivateSize; // since VISTA
        ULONG HardFaultCount; // since WIN7
        ULONG NumberOfThreadsHighWatermark; // since WIN7
        ULONGLONG CycleTime; // since WIN7
        LARGE_INTEGER CreateTime;
        LARGE_INTEGER UserTime;
        LARGE_INTEGER KernelTime;
        UNICODE_STRING ImageName;
        KPRIORITY BasePriority;
        HANDLE UniqueProcessId;
        HANDLE InheritedFromUniqueProcessId;
        ULONG HandleCount;
        ULONG SessionId;
        ULONG_PTR UniqueProcessKey; // since VISTA (requires SystemExtendedProcessInformation)
        SIZE_T PeakVirtualSize;
        SIZE_T VirtualSize;
        ULONG PageFaultCount;
        SIZE_T PeakWorkingSetSize;
        SIZE_T WorkingSetSize;
        SIZE_T QuotaPeakPagedPoolUsage;
        SIZE_T QuotaPagedPoolUsage;
        SIZE_T QuotaPeakNonPagedPoolUsage;
        SIZE_T QuotaNonPagedPoolUsage;
        SIZE_T PagefileUsage;
        SIZE_T PeakPagefileUsage;
        SIZE_T PrivatePageCount;
        LARGE_INTEGER ReadOperationCount;
        LARGE_INTEGER WriteOperationCount;
        LARGE_INTEGER OtherOperationCount;
        LARGE_INTEGER ReadTransferCount;
        LARGE_INTEGER WriteTransferCount;
        LARGE_INTEGER OtherTransferCount;
        SYSTEM_THREAD_INFORMATION Threads[1]; // SystemProcessInformation
        // SYSTEM_EXTENDED_THREAD_INFORMATION Threads[1]; // SystemExtendedProcessinformation
        // SYSTEM_EXTENDED_THREAD_INFORMATION + SYSTEM_PROCESS_INFORMATION_EXTENSION // SystemFullProcessInformation
    } SYSTEM_PROCESS_INFORMATION, *PSYSTEM_PROCESS_INFORMATION;

    typedef struct _SYSTEM_CALL_COUNT_INFORMATION
    {
        ULONG Length;
        ULONG NumberOfTables;
    } SYSTEM_CALL_COUNT_INFORMATION, *PSYSTEM_CALL_COUNT_INFORMATION;

    typedef struct _SYSTEM_DEVICE_INFORMATION
    {
        ULONG NumberOfDisks;
        ULONG NumberOfFloppies;
        ULONG NumberOfCdRoms;
        ULONG NumberOfTapes;
        ULONG NumberOfSerialPorts;
        ULONG NumberOfParallelPorts;
    } SYSTEM_DEVICE_INFORMATION, *PSYSTEM_DEVICE_INFORMATION;

    typedef struct _SYSTEM_PROCESSOR_PERFORMANCE_INFORMATION
    {
        LARGE_INTEGER IdleTime;
        LARGE_INTEGER KernelTime;
        LARGE_INTEGER UserTime;
        LARGE_INTEGER DpcTime;
        LARGE_INTEGER InterruptTime;
        ULONG InterruptCount;
    } SYSTEM_PROCESSOR_PERFORMANCE_INFORMATION, *PSYSTEM_PROCESSOR_PERFORMANCE_INFORMATION;

    typedef struct _SYSTEM_FLAGS_INFORMATION
    {
        ULONG Flags; // NtGlobalFlag
    } SYSTEM_FLAGS_INFORMATION, *PSYSTEM_FLAGS_INFORMATION;

    // private
    typedef struct _SYSTEM_CALL_TIME_INFORMATION
    {
        ULONG Length;
        ULONG TotalCalls;
        LARGE_INTEGER TimeOfCalls[1];
    } SYSTEM_CALL_TIME_INFORMATION, *PSYSTEM_CALL_TIME_INFORMATION;

    // private
    typedef struct _RTL_PROCESS_LOCK_INFORMATION
    {
        PVOID Address;
        USHORT Type;
        USHORT CreatorBackTraceIndex;
        HANDLE OwningThread;
        LONG LockCount;
        ULONG ContentionCount;
        ULONG EntryCount;
        LONG RecursionCount;
        ULONG NumberOfWaitingShared;
        ULONG NumberOfWaitingExclusive;
    } RTL_PROCESS_LOCK_INFORMATION, *PRTL_PROCESS_LOCK_INFORMATION;

    // private
    typedef struct _RTL_PROCESS_LOCKS
    {
        ULONG NumberOfLocks;
        RTL_PROCESS_LOCK_INFORMATION Locks[1];
    } RTL_PROCESS_LOCKS, *PRTL_PROCESS_LOCKS;

    // private
    typedef struct _RTL_PROCESS_BACKTRACE_INFORMATION
    {
        PCHAR SymbolicBackTrace;
        ULONG TraceCount;
        USHORT Index;
        USHORT Depth;
        PVOID BackTrace[32];
    } RTL_PROCESS_BACKTRACE_INFORMATION, *PRTL_PROCESS_BACKTRACE_INFORMATION;

    // private
    typedef struct _RTL_PROCESS_BACKTRACES
    {
        ULONG CommittedMemory;
        ULONG ReservedMemory;
        ULONG NumberOfBackTraceLookups;
        ULONG NumberOfBackTraces;
        RTL_PROCESS_BACKTRACE_INFORMATION BackTraces[1];
    } RTL_PROCESS_BACKTRACES, *PRTL_PROCESS_BACKTRACES;

    typedef struct _SYSTEM_HANDLE_TABLE_ENTRY_INFO
    {
        USHORT UniqueProcessId;
        USHORT CreatorBackTraceIndex;
        UCHAR ObjectTypeIndex;
        UCHAR HandleAttributes;
        USHORT HandleValue;
        PVOID Object;
        ULONG GrantedAccess;
    } SYSTEM_HANDLE_TABLE_ENTRY_INFO, *PSYSTEM_HANDLE_TABLE_ENTRY_INFO;

    typedef struct _SYSTEM_HANDLE_INFORMATION
    {
        ULONG NumberOfHandles;
        SYSTEM_HANDLE_TABLE_ENTRY_INFO Handles[1];
    } SYSTEM_HANDLE_INFORMATION, *PSYSTEM_HANDLE_INFORMATION;

    typedef struct _SYSTEM_OBJECTTYPE_INFORMATION
    {
        ULONG NextEntryOffset;
        ULONG NumberOfObjects;
        ULONG NumberOfHandles;
        ULONG TypeIndex;
        ULONG InvalidAttributes;
        GENERIC_MAPPING GenericMapping;
        ULONG ValidAccessMask;
        ULONG PoolType;
        BOOLEAN SecurityRequired;
        BOOLEAN WaitableObject;
        UNICODE_STRING TypeName;
    } SYSTEM_OBJECTTYPE_INFORMATION, *PSYSTEM_OBJECTTYPE_INFORMATION;

    typedef struct _SYSTEM_OBJECT_INFORMATION
    {
        ULONG NextEntryOffset;
        PVOID Object;
        HANDLE CreatorUniqueProcess;
        USHORT CreatorBackTraceIndex;
        USHORT Flags;
        LONG PointerCount;
        LONG HandleCount;
        ULONG PagedPoolCharge;
        ULONG NonPagedPoolCharge;
        HANDLE ExclusiveProcessId;
        PVOID SecurityDescriptor;
        UNICODE_STRING NameInfo;
    } SYSTEM_OBJECT_INFORMATION, *PSYSTEM_OBJECT_INFORMATION;

    typedef struct _SYSTEM_PAGEFILE_INFORMATION
    {
        ULONG NextEntryOffset;
        ULONG TotalSize;
        ULONG TotalInUse;
        ULONG PeakUsage;
        UNICODE_STRING PageFileName;
    } SYSTEM_PAGEFILE_INFORMATION, *PSYSTEM_PAGEFILE_INFORMATION;

#define MM_WORKING_SET_MAX_HARD_ENABLE 0x1
#define MM_WORKING_SET_MAX_HARD_DISABLE 0x2
#define MM_WORKING_SET_MIN_HARD_ENABLE 0x4
#define MM_WORKING_SET_MIN_HARD_DISABLE 0x8

    typedef struct _SYSTEM_FILECACHE_INFORMATION
    {
        SIZE_T CurrentSize;
        SIZE_T PeakSize;
        ULONG PageFaultCount;
        SIZE_T MinimumWorkingSet;
        SIZE_T MaximumWorkingSet;
        SIZE_T CurrentSizeIncludingTransitionInPages;
        SIZE_T PeakSizeIncludingTransitionInPages;
        ULONG TransitionRePurposeCount;
        ULONG Flags;
    } SYSTEM_FILECACHE_INFORMATION, *PSYSTEM_FILECACHE_INFORMATION;

    // Can be used instead of SYSTEM_FILECACHE_INFORMATION
    typedef struct _SYSTEM_BASIC_WORKING_SET_INFORMATION
    {
        SIZE_T CurrentSize;
        SIZE_T PeakSize;
        ULONG PageFaultCount;
    } SYSTEM_BASIC_WORKING_SET_INFORMATION, *PSYSTEM_BASIC_WORKING_SET_INFORMATION;

    typedef struct _SYSTEM_POOLTAG
    {
        union
        {
            UCHAR Tag[4];
            ULONG TagUlong;
        };
        ULONG PagedAllocs;
        ULONG PagedFrees;
        SIZE_T PagedUsed;
        ULONG NonPagedAllocs;
        ULONG NonPagedFrees;
        SIZE_T NonPagedUsed;
    } SYSTEM_POOLTAG, *PSYSTEM_POOLTAG;

    typedef struct _SYSTEM_POOLTAG_INFORMATION
    {
        ULONG Count;
        SYSTEM_POOLTAG TagInfo[1];
    } SYSTEM_POOLTAG_INFORMATION, *PSYSTEM_POOLTAG_INFORMATION;

    typedef struct _SYSTEM_INTERRUPT_INFORMATION
    {
        ULONG ContextSwitches;
        ULONG DpcCount;
        ULONG DpcRate;
        ULONG TimeIncrement;
        ULONG DpcBypassCount;
        ULONG ApcBypassCount;
    } SYSTEM_INTERRUPT_INFORMATION, *PSYSTEM_INTERRUPT_INFORMATION;

    typedef struct _SYSTEM_DPC_BEHAVIOR_INFORMATION
    {
        ULONG Spare;
        ULONG DpcQueueDepth;
        ULONG MinimumDpcRate;
        ULONG AdjustDpcThreshold;
        ULONG IdealDpcRate;
    } SYSTEM_DPC_BEHAVIOR_INFORMATION, *PSYSTEM_DPC_BEHAVIOR_INFORMATION;

    typedef struct _SYSTEM_QUERY_TIME_ADJUST_INFORMATION
    {
        ULONG TimeAdjustment;
        ULONG TimeIncrement;
        BOOLEAN Enable;
    } SYSTEM_QUERY_TIME_ADJUST_INFORMATION, *PSYSTEM_QUERY_TIME_ADJUST_INFORMATION;

    typedef struct _SYSTEM_QUERY_TIME_ADJUST_INFORMATION_PRECISE
    {
        ULONGLONG TimeAdjustment;
        ULONGLONG TimeIncrement;
        BOOLEAN Enable;
    } SYSTEM_QUERY_TIME_ADJUST_INFORMATION_PRECISE, *PSYSTEM_QUERY_TIME_ADJUST_INFORMATION_PRECISE;

    typedef struct _SYSTEM_SET_TIME_ADJUST_INFORMATION
    {
        ULONG TimeAdjustment;
        BOOLEAN Enable;
    } SYSTEM_SET_TIME_ADJUST_INFORMATION, *PSYSTEM_SET_TIME_ADJUST_INFORMATION;

    typedef struct _SYSTEM_SET_TIME_ADJUST_INFORMATION_PRECISE
    {
        ULONGLONG TimeAdjustment;
        BOOLEAN Enable;
    } SYSTEM_SET_TIME_ADJUST_INFORMATION_PRECISE, *PSYSTEM_SET_TIME_ADJUST_INFORMATION_PRECISE;

    typedef enum _EVENT_TRACE_INFORMATION_CLASS
    {
        EventTraceKernelVersionInformation, // EVENT_TRACE_VERSION_INFORMATION
        EventTraceGroupMaskInformation, // EVENT_TRACE_GROUPMASK_INFORMATION
        EventTracePerformanceInformation, // EVENT_TRACE_PERFORMANCE_INFORMATION
        EventTraceTimeProfileInformation, // EVENT_TRACE_TIME_PROFILE_INFORMATION
        EventTraceSessionSecurityInformation, // EVENT_TRACE_SESSION_SECURITY_INFORMATION
        EventTraceSpinlockInformation, // EVENT_TRACE_SPINLOCK_INFORMATION
        EventTraceStackTracingInformation, // EVENT_TRACE_SYSTEM_EVENT_INFORMATION
        EventTraceExecutiveResourceInformation, // EVENT_TRACE_EXECUTIVE_RESOURCE_INFORMATION
        EventTraceHeapTracingInformation, // EVENT_TRACE_HEAP_TRACING_INFORMATION
        EventTraceHeapSummaryTracingInformation, // EVENT_TRACE_HEAP_TRACING_INFORMATION
        EventTracePoolTagFilterInformation, // EVENT_TRACE_TAG_FILTER_INFORMATION
        EventTracePebsTracingInformation, // EVENT_TRACE_SYSTEM_EVENT_INFORMATION 
        EventTraceProfileConfigInformation, // EVENT_TRACE_PROFILE_COUNTER_INFORMATION
        EventTraceProfileSourceListInformation, // EVENT_TRACE_PROFILE_LIST_INFORMATION
        EventTraceProfileEventListInformation, // EVENT_TRACE_SYSTEM_EVENT_INFORMATION 
        EventTraceProfileCounterListInformation, // EVENT_TRACE_PROFILE_COUNTER_INFORMATION 
        EventTraceStackCachingInformation, // EVENT_TRACE_STACK_CACHING_INFORMATION
        EventTraceObjectTypeFilterInformation, // EVENT_TRACE_TAG_FILTER_INFORMATION
        EventTraceSoftRestartInformation, // EVENT_TRACE_SOFT_RESTART_INFORMATION
        EventTraceLastBranchConfigurationInformation, // REDSTONE3
        EventTraceLastBranchEventListInformation,
        EventTraceProfileSourceAddInformation, // EVENT_TRACE_PROFILE_ADD_INFORMATION // REDSTONE4
        EventTraceProfileSourceRemoveInformation, // EVENT_TRACE_PROFILE_REMOVE_INFORMATION
        EventTraceProcessorTraceConfigurationInformation,
        EventTraceProcessorTraceEventListInformation,
        EventTraceCoverageSamplerInformation, // EVENT_TRACE_COVERAGE_SAMPLER_INFORMATION
        MaxEventTraceInfoClass
    } EVENT_TRACE_INFORMATION_CLASS;

    typedef struct _EVENT_TRACE_VERSION_INFORMATION
    {
        EVENT_TRACE_INFORMATION_CLASS EventTraceInformationClass;
        ULONG EventTraceKernelVersion;
    } EVENT_TRACE_VERSION_INFORMATION, *PEVENT_TRACE_VERSION_INFORMATION;

    typedef struct _PERFINFO_GROUPMASK
    {
        ULONG Masks[8];
    } PERFINFO_GROUPMASK, *PPERFINFO_GROUPMASK;

    typedef struct _EVENT_TRACE_GROUPMASK_INFORMATION
    {
        EVENT_TRACE_INFORMATION_CLASS EventTraceInformationClass;
        HANDLE TraceHandle;
        PERFINFO_GROUPMASK EventTraceGroupMasks;
    } EVENT_TRACE_GROUPMASK_INFORMATION, *PEVENT_TRACE_GROUPMASK_INFORMATION;

    typedef struct _EVENT_TRACE_PERFORMANCE_INFORMATION
    {
        EVENT_TRACE_INFORMATION_CLASS EventTraceInformationClass;
        LARGE_INTEGER LogfileBytesWritten;
    } EVENT_TRACE_PERFORMANCE_INFORMATION, *PEVENT_TRACE_PERFORMANCE_INFORMATION;

    typedef struct _EVENT_TRACE_TIME_PROFILE_INFORMATION
    {
        EVENT_TRACE_INFORMATION_CLASS EventTraceInformationClass;
        ULONG ProfileInterval;
    } EVENT_TRACE_TIME_PROFILE_INFORMATION, *PEVENT_TRACE_TIME_PROFILE_INFORMATION;

    typedef struct _EVENT_TRACE_SESSION_SECURITY_INFORMATION
    {
        EVENT_TRACE_INFORMATION_CLASS EventTraceInformationClass;
        ULONG SecurityInformation;
        HANDLE TraceHandle;
        UCHAR SecurityDescriptor[1];
    } EVENT_TRACE_SESSION_SECURITY_INFORMATION, *PEVENT_TRACE_SESSION_SECURITY_INFORMATION;

    typedef struct _EVENT_TRACE_SPINLOCK_INFORMATION
    {
        EVENT_TRACE_INFORMATION_CLASS EventTraceInformationClass;
        ULONG SpinLockSpinThreshold;
        ULONG SpinLockAcquireSampleRate;
        ULONG SpinLockContentionSampleRate;
        ULONG SpinLockHoldThreshold;
    } EVENT_TRACE_SPINLOCK_INFORMATION, *PEVENT_TRACE_SPINLOCK_INFORMATION;

    typedef struct _EVENT_TRACE_SYSTEM_EVENT_INFORMATION
    {
        EVENT_TRACE_INFORMATION_CLASS EventTraceInformationClass;
        HANDLE TraceHandle;
        ULONG HookId[1];
    } EVENT_TRACE_SYSTEM_EVENT_INFORMATION, *PEVENT_TRACE_SYSTEM_EVENT_INFORMATION;

    typedef struct _EVENT_TRACE_EXECUTIVE_RESOURCE_INFORMATION
    {
        EVENT_TRACE_INFORMATION_CLASS EventTraceInformationClass;
        ULONG ReleaseSamplingRate;
        ULONG ContentionSamplingRate;
        ULONG NumberOfExcessiveTimeouts;
    } EVENT_TRACE_EXECUTIVE_RESOURCE_INFORMATION, *PEVENT_TRACE_EXECUTIVE_RESOURCE_INFORMATION;

    typedef struct _EVENT_TRACE_HEAP_TRACING_INFORMATION
    {
        EVENT_TRACE_INFORMATION_CLASS EventTraceInformationClass;
        ULONG ProcessId;
    } EVENT_TRACE_HEAP_TRACING_INFORMATION, *PEVENT_TRACE_HEAP_TRACING_INFORMATION;

    typedef struct _EVENT_TRACE_TAG_FILTER_INFORMATION
    {
        EVENT_TRACE_INFORMATION_CLASS EventTraceInformationClass;
        HANDLE TraceHandle;
        ULONG Filter[1];
    } EVENT_TRACE_TAG_FILTER_INFORMATION, *PEVENT_TRACE_TAG_FILTER_INFORMATION;

    typedef struct _EVENT_TRACE_PROFILE_COUNTER_INFORMATION
    {
        EVENT_TRACE_INFORMATION_CLASS EventTraceInformationClass;
        HANDLE TraceHandle;
        ULONG ProfileSource[1];
    } EVENT_TRACE_PROFILE_COUNTER_INFORMATION, *PEVENT_TRACE_PROFILE_COUNTER_INFORMATION;

    typedef struct _EVENT_TRACE_PROFILE_LIST_INFORMATION
    {
        EVENT_TRACE_INFORMATION_CLASS EventTraceInformationClass;
        ULONG Spare;
        struct _PROFILE_SOURCE_INFO* Profile[1];
    } EVENT_TRACE_PROFILE_LIST_INFORMATION, *PEVENT_TRACE_PROFILE_LIST_INFORMATION;

    typedef struct _EVENT_TRACE_STACK_CACHING_INFORMATION
    {
        EVENT_TRACE_INFORMATION_CLASS EventTraceInformationClass;
        HANDLE TraceHandle;
        BOOLEAN Enabled;
        UCHAR Reserved[3];
        ULONG CacheSize;
        ULONG BucketCount;
    } EVENT_TRACE_STACK_CACHING_INFORMATION, *PEVENT_TRACE_STACK_CACHING_INFORMATION;

    typedef struct _EVENT_TRACE_SOFT_RESTART_INFORMATION
    {
        EVENT_TRACE_INFORMATION_CLASS EventTraceInformationClass;
        HANDLE TraceHandle;
        BOOLEAN PersistTraceBuffers;
        WCHAR FileName[1];
    } EVENT_TRACE_SOFT_RESTART_INFORMATION, *PEVENT_TRACE_SOFT_RESTART_INFORMATION;

    typedef struct _EVENT_TRACE_PROFILE_ADD_INFORMATION
    {
        EVENT_TRACE_INFORMATION_CLASS EventTraceInformationClass;
        BOOLEAN PerfEvtEventSelect;
        BOOLEAN PerfEvtUnitSelect;
        ULONG PerfEvtType;
        ULONG CpuInfoHierarchy[0x3];
        ULONG InitialInterval;
        BOOLEAN AllowsHalt;
        BOOLEAN Persist;
        WCHAR ProfileSourceDescription[0x1];
    } EVENT_TRACE_PROFILE_ADD_INFORMATION, *PEVENT_TRACE_PROFILE_ADD_INFORMATION;

    typedef struct _EVENT_TRACE_PROFILE_REMOVE_INFORMATION
    {
        EVENT_TRACE_INFORMATION_CLASS EventTraceInformationClass;
        KPROFILE_SOURCE ProfileSource;
        ULONG CpuInfoHierarchy[0x3];
    } EVENT_TRACE_PROFILE_REMOVE_INFORMATION, *PEVENT_TRACE_PROFILE_REMOVE_INFORMATION;

    typedef struct _EVENT_TRACE_COVERAGE_SAMPLER_INFORMATION
    {
        EVENT_TRACE_INFORMATION_CLASS EventTraceInformationClass;
        BOOLEAN CoverageSamplerInformationClass;
        UCHAR MajorVersion;
        UCHAR MinorVersion;
        UCHAR Reserved;
        HANDLE SamplerHandle;
    } EVENT_TRACE_COVERAGE_SAMPLER_INFORMATION, *PEVENT_TRACE_COVERAGE_SAMPLER_INFORMATION;

    typedef struct _SYSTEM_EXCEPTION_INFORMATION
    {
        ULONG AlignmentFixupCount;
        ULONG ExceptionDispatchCount;
        ULONG FloatingEmulationCount;
        ULONG ByteWordEmulationCount;
    } SYSTEM_EXCEPTION_INFORMATION, *PSYSTEM_EXCEPTION_INFORMATION;

    typedef struct _SYSTEM_KERNEL_DEBUGGER_INFORMATION
    {
        BOOLEAN KernelDebuggerEnabled;
        BOOLEAN KernelDebuggerNotPresent;
    } SYSTEM_KERNEL_DEBUGGER_INFORMATION, *PSYSTEM_KERNEL_DEBUGGER_INFORMATION;

    typedef struct _SYSTEM_CONTEXT_SWITCH_INFORMATION
    {
        ULONG ContextSwitches;
        ULONG FindAny;
        ULONG FindLast;
        ULONG FindIdeal;
        ULONG IdleAny;
        ULONG IdleCurrent;
        ULONG IdleLast;
        ULONG IdleIdeal;
        ULONG PreemptAny;
        ULONG PreemptCurrent;
        ULONG PreemptLast;
        ULONG SwitchToIdle;
    } SYSTEM_CONTEXT_SWITCH_INFORMATION, *PSYSTEM_CONTEXT_SWITCH_INFORMATION;

    typedef struct _SYSTEM_REGISTRY_QUOTA_INFORMATION
    {
        ULONG RegistryQuotaAllowed;
        ULONG RegistryQuotaUsed;
        SIZE_T PagedPoolSize;
    } SYSTEM_REGISTRY_QUOTA_INFORMATION, *PSYSTEM_REGISTRY_QUOTA_INFORMATION;

    typedef struct _SYSTEM_PROCESSOR_IDLE_INFORMATION
    {
        ULONGLONG IdleTime;
        ULONGLONG C1Time;
        ULONGLONG C2Time;
        ULONGLONG C3Time;
        ULONG C1Transitions;
        ULONG C2Transitions;
        ULONG C3Transitions;
        ULONG Padding;
    } SYSTEM_PROCESSOR_IDLE_INFORMATION, *PSYSTEM_PROCESSOR_IDLE_INFORMATION;

    typedef struct _SYSTEM_LEGACY_DRIVER_INFORMATION
    {
        ULONG VetoType;
        UNICODE_STRING VetoList;
    } SYSTEM_LEGACY_DRIVER_INFORMATION, *PSYSTEM_LEGACY_DRIVER_INFORMATION;

    typedef struct _SYSTEM_LOOKASIDE_INFORMATION
    {
        USHORT CurrentDepth;
        USHORT MaximumDepth;
        ULONG TotalAllocates;
        ULONG AllocateMisses;
        ULONG TotalFrees;
        ULONG FreeMisses;
        ULONG Type;
        ULONG Tag;
        ULONG Size;
    } SYSTEM_LOOKASIDE_INFORMATION, *PSYSTEM_LOOKASIDE_INFORMATION;

    // private
    typedef struct _SYSTEM_RANGE_START_INFORMATION
    {
        PVOID SystemRangeStart;
    } SYSTEM_RANGE_START_INFORMATION, *PSYSTEM_RANGE_START_INFORMATION;

    typedef struct _SYSTEM_VERIFIER_INFORMATION
    {
        ULONG NextEntryOffset;
        ULONG Level;
        UNICODE_STRING DriverName;

        ULONG RaiseIrqls;
        ULONG AcquireSpinLocks;
        ULONG SynchronizeExecutions;
        ULONG AllocationsAttempted;

        ULONG AllocationsSucceeded;
        ULONG AllocationsSucceededSpecialPool;
        ULONG AllocationsWithNoTag;
        ULONG TrimRequests;

        ULONG Trims;
        ULONG AllocationsFailed;
        ULONG AllocationsFailedDeliberately;
        ULONG Loads;

        ULONG Unloads;
        ULONG UnTrackedPool;
        ULONG CurrentPagedPoolAllocations;
        ULONG CurrentNonPagedPoolAllocations;

        ULONG PeakPagedPoolAllocations;
        ULONG PeakNonPagedPoolAllocations;

        SIZE_T PagedPoolUsageInBytes;
        SIZE_T NonPagedPoolUsageInBytes;
        SIZE_T PeakPagedPoolUsageInBytes;
        SIZE_T PeakNonPagedPoolUsageInBytes;
    } SYSTEM_VERIFIER_INFORMATION, *PSYSTEM_VERIFIER_INFORMATION;

    typedef struct _SYSTEM_SESSION_PROCESS_INFORMATION
    {
        ULONG SessionId;
        ULONG SizeOfBuf;
        PVOID Buffer;
    } SYSTEM_SESSION_PROCESS_INFORMATION, *PSYSTEM_SESSION_PROCESS_INFORMATION;

    typedef struct _SYSTEM_PROCESSOR_POWER_INFORMATION
    {
        UCHAR CurrentFrequency;
        UCHAR ThermalLimitFrequency;
        UCHAR ConstantThrottleFrequency;
        UCHAR DegradedThrottleFrequency;
        UCHAR LastBusyFrequency;
        UCHAR LastC3Frequency;
        UCHAR LastAdjustedBusyFrequency;
        UCHAR ProcessorMinThrottle;
        UCHAR ProcessorMaxThrottle;
        ULONG NumberOfFrequencies;
        ULONG PromotionCount;
        ULONG DemotionCount;
        ULONG ErrorCount;
        ULONG RetryCount;
        ULONGLONG CurrentFrequencyTime;
        ULONGLONG CurrentProcessorTime;
        ULONGLONG CurrentProcessorIdleTime;
        ULONGLONG LastProcessorTime;
        ULONGLONG LastProcessorIdleTime;
        ULONGLONG Energy;
    } SYSTEM_PROCESSOR_POWER_INFORMATION, *PSYSTEM_PROCESSOR_POWER_INFORMATION;

    typedef struct _SYSTEM_HANDLE_TABLE_ENTRY_INFO_EX
    {
        PVOID Object;
        ULONG_PTR UniqueProcessId;
        ULONG_PTR HandleValue;
        ULONG GrantedAccess;
        USHORT CreatorBackTraceIndex;
        USHORT ObjectTypeIndex;
        ULONG HandleAttributes;
        ULONG Reserved;
    } SYSTEM_HANDLE_TABLE_ENTRY_INFO_EX, *PSYSTEM_HANDLE_TABLE_ENTRY_INFO_EX;

    typedef struct _SYSTEM_HANDLE_INFORMATION_EX
    {
        ULONG_PTR NumberOfHandles;
        ULONG_PTR Reserved;
        SYSTEM_HANDLE_TABLE_ENTRY_INFO_EX Handles[1];
    } SYSTEM_HANDLE_INFORMATION_EX, *PSYSTEM_HANDLE_INFORMATION_EX;

    typedef struct _SYSTEM_BIGPOOL_ENTRY
    {
        union
        {
            PVOID VirtualAddress;
            ULONG_PTR NonPaged : 1;
        };
        SIZE_T SizeInBytes;
        union
        {
            UCHAR Tag[4];
            ULONG TagUlong;
        };
    } SYSTEM_BIGPOOL_ENTRY, *PSYSTEM_BIGPOOL_ENTRY;

    typedef struct _SYSTEM_BIGPOOL_INFORMATION
    {
        ULONG Count;
        SYSTEM_BIGPOOL_ENTRY AllocatedInfo[1];
    } SYSTEM_BIGPOOL_INFORMATION, *PSYSTEM_BIGPOOL_INFORMATION;

    typedef struct _SYSTEM_POOL_ENTRY
    {
        BOOLEAN Allocated;
        BOOLEAN Spare0;
        USHORT AllocatorBackTraceIndex;
        ULONG Size;
        union
        {
            UCHAR Tag[4];
            ULONG TagUlong;
            PVOID ProcessChargedQuota;
        };
    } SYSTEM_POOL_ENTRY, *PSYSTEM_POOL_ENTRY;

    typedef struct _SYSTEM_POOL_INFORMATION
    {
        SIZE_T TotalSize;
        PVOID FirstEntry;
        USHORT EntryOverhead;
        BOOLEAN PoolTagPresent;
        BOOLEAN Spare0;
        ULONG NumberOfEntries;
        SYSTEM_POOL_ENTRY Entries[1];
    } SYSTEM_POOL_INFORMATION, *PSYSTEM_POOL_INFORMATION;

    typedef struct _SYSTEM_SESSION_POOLTAG_INFORMATION
    {
        SIZE_T NextEntryOffset;
        ULONG SessionId;
        ULONG Count;
        SYSTEM_POOLTAG TagInfo[1];
    } SYSTEM_SESSION_POOLTAG_INFORMATION, *PSYSTEM_SESSION_POOLTAG_INFORMATION;

    typedef struct _SYSTEM_SESSION_MAPPED_VIEW_INFORMATION
    {
        SIZE_T NextEntryOffset;
        ULONG SessionId;
        ULONG ViewFailures;
        SIZE_T NumberOfBytesAvailable;
        SIZE_T NumberOfBytesAvailableContiguous;
    } SYSTEM_SESSION_MAPPED_VIEW_INFORMATION, *PSYSTEM_SESSION_MAPPED_VIEW_INFORMATION;

#if (PHNT_MODE != PHNT_MODE_KERNEL)
// private
    typedef enum _SYSTEM_FIRMWARE_TABLE_ACTION
    {
        SystemFirmwareTableEnumerate,
        SystemFirmwareTableGet,
        SystemFirmwareTableMax
    } SYSTEM_FIRMWARE_TABLE_ACTION;

    // private
    typedef struct _SYSTEM_FIRMWARE_TABLE_INFORMATION
    {
        ULONG ProviderSignature; // (same as the GetSystemFirmwareTable function)
        SYSTEM_FIRMWARE_TABLE_ACTION Action;
        ULONG TableID;
        ULONG TableBufferLength;
        UCHAR TableBuffer[1];
    } SYSTEM_FIRMWARE_TABLE_INFORMATION, *PSYSTEM_FIRMWARE_TABLE_INFORMATION;
#endif

// private
    typedef struct _SYSTEM_MEMORY_LIST_INFORMATION
    {
        ULONG_PTR ZeroPageCount;
        ULONG_PTR FreePageCount;
        ULONG_PTR ModifiedPageCount;
        ULONG_PTR ModifiedNoWritePageCount;
        ULONG_PTR BadPageCount;
        ULONG_PTR PageCountByPriority[8];
        ULONG_PTR RepurposedPagesByPriority[8];
        ULONG_PTR ModifiedPageCountPageFile;
    } SYSTEM_MEMORY_LIST_INFORMATION, *PSYSTEM_MEMORY_LIST_INFORMATION;

    // private
    typedef enum _SYSTEM_MEMORY_LIST_COMMAND
    {
        MemoryCaptureAccessedBits,
        MemoryCaptureAndResetAccessedBits,
        MemoryEmptyWorkingSets,
        MemoryFlushModifiedList,
        MemoryPurgeStandbyList,
        MemoryPurgeLowPriorityStandbyList,
        MemoryCommandMax
    } SYSTEM_MEMORY_LIST_COMMAND;

    // private
    typedef struct _SYSTEM_THREAD_CID_PRIORITY_INFORMATION
    {
        CLIENT_ID ClientId;
        KPRIORITY Priority;
    } SYSTEM_THREAD_CID_PRIORITY_INFORMATION, *PSYSTEM_THREAD_CID_PRIORITY_INFORMATION;

    // private
    typedef struct _SYSTEM_PROCESSOR_IDLE_CYCLE_TIME_INFORMATION
    {
        ULONGLONG CycleTime;
    } SYSTEM_PROCESSOR_IDLE_CYCLE_TIME_INFORMATION, *PSYSTEM_PROCESSOR_IDLE_CYCLE_TIME_INFORMATION;

    // private
    typedef struct _SYSTEM_REF_TRACE_INFORMATION
    {
        BOOLEAN TraceEnable;
        BOOLEAN TracePermanent;
        UNICODE_STRING TraceProcessName;
        UNICODE_STRING TracePoolTags;
    } SYSTEM_REF_TRACE_INFORMATION, *PSYSTEM_REF_TRACE_INFORMATION;

    // private
    typedef struct _SYSTEM_PROCESS_ID_INFORMATION
    {
        HANDLE ProcessId;
        UNICODE_STRING ImageName;
    } SYSTEM_PROCESS_ID_INFORMATION, *PSYSTEM_PROCESS_ID_INFORMATION;

    // private
    typedef struct _SYSTEM_BOOT_ENVIRONMENT_INFORMATION
    {
        GUID BootIdentifier;
        FIRMWARE_TYPE FirmwareType;
        union
        {
            ULONGLONG BootFlags;
            struct
            {
                ULONGLONG DbgMenuOsSelection : 1; // REDSTONE4
                ULONGLONG DbgHiberBoot : 1;
                ULONGLONG DbgSoftBoot : 1;
                ULONGLONG DbgMeasuredLaunch : 1;
            };
        };
    } SYSTEM_BOOT_ENVIRONMENT_INFORMATION, *PSYSTEM_BOOT_ENVIRONMENT_INFORMATION;

    // private
    typedef struct _SYSTEM_IMAGE_FILE_EXECUTION_OPTIONS_INFORMATION
    {
        ULONG FlagsToEnable;
        ULONG FlagsToDisable;
    } SYSTEM_IMAGE_FILE_EXECUTION_OPTIONS_INFORMATION, *PSYSTEM_IMAGE_FILE_EXECUTION_OPTIONS_INFORMATION;

    // private
    typedef struct _SYSTEM_VERIFIER_INFORMATION_EX
    {
        ULONG VerifyMode;
        ULONG OptionChanges;
        UNICODE_STRING PreviousBucketName;
        ULONG IrpCancelTimeoutMsec;
        ULONG VerifierExtensionEnabled;
#ifdef _WIN64
        ULONG Reserved[1];
#else
        ULONG Reserved[3];
#endif
    } SYSTEM_VERIFIER_INFORMATION_EX, *PSYSTEM_VERIFIER_INFORMATION_EX;

    // private
    typedef struct _SYSTEM_SYSTEM_PARTITION_INFORMATION
    {
        UNICODE_STRING SystemPartition;
    } SYSTEM_SYSTEM_PARTITION_INFORMATION, *PSYSTEM_SYSTEM_PARTITION_INFORMATION;

    // private
    typedef struct _SYSTEM_SYSTEM_DISK_INFORMATION
    {
        UNICODE_STRING SystemDisk;
    } SYSTEM_SYSTEM_DISK_INFORMATION, *PSYSTEM_SYSTEM_DISK_INFORMATION;

    // private (Windows 8.1 and above)
    typedef struct _SYSTEM_PROCESSOR_PERFORMANCE_HITCOUNT
    {
        ULONGLONG Hits;
        UCHAR PercentFrequency;
    } SYSTEM_PROCESSOR_PERFORMANCE_HITCOUNT, *PSYSTEM_PROCESSOR_PERFORMANCE_HITCOUNT;

    // private (Windows 7 and Windows 8)
    typedef struct _SYSTEM_PROCESSOR_PERFORMANCE_HITCOUNT_WIN8
    {
        ULONG Hits;
        UCHAR PercentFrequency;
    } SYSTEM_PROCESSOR_PERFORMANCE_HITCOUNT_WIN8, *PSYSTEM_PROCESSOR_PERFORMANCE_HITCOUNT_WIN8;

    // private
    typedef struct _SYSTEM_PROCESSOR_PERFORMANCE_STATE_DISTRIBUTION
    {
        ULONG ProcessorNumber;
        ULONG StateCount;
        SYSTEM_PROCESSOR_PERFORMANCE_HITCOUNT States[1];
    } SYSTEM_PROCESSOR_PERFORMANCE_STATE_DISTRIBUTION, *PSYSTEM_PROCESSOR_PERFORMANCE_STATE_DISTRIBUTION;

    // private
    typedef struct _SYSTEM_PROCESSOR_PERFORMANCE_DISTRIBUTION
    {
        ULONG ProcessorCount;
        ULONG Offsets[1];
    } SYSTEM_PROCESSOR_PERFORMANCE_DISTRIBUTION, *PSYSTEM_PROCESSOR_PERFORMANCE_DISTRIBUTION;

    // private
    typedef struct _SYSTEM_CODEINTEGRITY_INFORMATION
    {
        ULONG Length;
        ULONG CodeIntegrityOptions;
    } SYSTEM_CODEINTEGRITY_INFORMATION, *PSYSTEM_CODEINTEGRITY_INFORMATION;

    // private
    typedef enum _SYSTEM_VA_TYPE
    {
        SystemVaTypeAll,
        SystemVaTypeNonPagedPool,
        SystemVaTypePagedPool,
        SystemVaTypeSystemCache,
        SystemVaTypeSystemPtes,
        SystemVaTypeSessionSpace,
        SystemVaTypeMax
    } SYSTEM_VA_TYPE, *PSYSTEM_VA_TYPE;

    // private
    typedef struct _SYSTEM_VA_LIST_INFORMATION
    {
        SIZE_T VirtualSize;
        SIZE_T VirtualPeak;
        SIZE_T VirtualLimit;
        SIZE_T AllocationFailures;
    } SYSTEM_VA_LIST_INFORMATION, *PSYSTEM_VA_LIST_INFORMATION;

    // private
    typedef struct _SYSTEM_REGISTRY_APPEND_STRING_PARAMETERS
    {
        HANDLE KeyHandle;
        PUNICODE_STRING ValueNamePointer;
        PULONG RequiredLengthPointer;
        PUCHAR Buffer;
        ULONG BufferLength;
        ULONG Type;
        PUCHAR AppendBuffer;
        ULONG AppendBufferLength;
        BOOLEAN CreateIfDoesntExist;
        BOOLEAN TruncateExistingValue;
    } SYSTEM_REGISTRY_APPEND_STRING_PARAMETERS, *PSYSTEM_REGISTRY_APPEND_STRING_PARAMETERS;

    // msdn
    typedef struct _SYSTEM_VHD_BOOT_INFORMATION
    {
        BOOLEAN OsDiskIsVhd;
        ULONG OsVhdFilePathOffset;
        WCHAR OsVhdParentVolume[ANYSIZE_ARRAY];
    } SYSTEM_VHD_BOOT_INFORMATION, *PSYSTEM_VHD_BOOT_INFORMATION;

    // private
    typedef struct _SYSTEM_LOW_PRIORITY_IO_INFORMATION
    {
        ULONG LowPriReadOperations;
        ULONG LowPriWriteOperations;
        ULONG KernelBumpedToNormalOperations;
        ULONG LowPriPagingReadOperations;
        ULONG KernelPagingReadsBumpedToNormal;
        ULONG LowPriPagingWriteOperations;
        ULONG KernelPagingWritesBumpedToNormal;
        ULONG BoostedIrpCount;
        ULONG BoostedPagingIrpCount;
        ULONG BlanketBoostCount;
    } SYSTEM_LOW_PRIORITY_IO_INFORMATION, *PSYSTEM_LOW_PRIORITY_IO_INFORMATION;

    // symbols
    typedef enum _TPM_BOOT_ENTROPY_RESULT_CODE
    {
        TpmBootEntropyStructureUninitialized,
        TpmBootEntropyDisabledByPolicy,
        TpmBootEntropyNoTpmFound,
        TpmBootEntropyTpmError,
        TpmBootEntropySuccess
    } TPM_BOOT_ENTROPY_RESULT_CODE;

    // Contents of KeLoaderBlock->Extension->TpmBootEntropyResult (TPM_BOOT_ENTROPY_LDR_RESULT).
    // EntropyData is truncated to 40 bytes.

    // private
    typedef struct _TPM_BOOT_ENTROPY_NT_RESULT
    {
        ULONGLONG Policy;
        TPM_BOOT_ENTROPY_RESULT_CODE ResultCode;
        NTSTATUS ResultStatus;
        ULONGLONG Time;
        ULONG EntropyLength;
        UCHAR EntropyData[40];
    } TPM_BOOT_ENTROPY_NT_RESULT, *PTPM_BOOT_ENTROPY_NT_RESULT;

    // private
    typedef struct _SYSTEM_VERIFIER_COUNTERS_INFORMATION
    {
        SYSTEM_VERIFIER_INFORMATION Legacy;
        ULONG RaiseIrqls;
        ULONG AcquireSpinLocks;
        ULONG SynchronizeExecutions;
        ULONG AllocationsWithNoTag;
        ULONG AllocationsFailed;
        ULONG AllocationsFailedDeliberately;
        SIZE_T LockedBytes;
        SIZE_T PeakLockedBytes;
        SIZE_T MappedLockedBytes;
        SIZE_T PeakMappedLockedBytes;
        SIZE_T MappedIoSpaceBytes;
        SIZE_T PeakMappedIoSpaceBytes;
        SIZE_T PagesForMdlBytes;
        SIZE_T PeakPagesForMdlBytes;
        SIZE_T ContiguousMemoryBytes;
        SIZE_T PeakContiguousMemoryBytes;
        ULONG ExecutePoolTypes; // REDSTONE2
        ULONG ExecutePageProtections;
        ULONG ExecutePageMappings;
        ULONG ExecuteWriteSections;
        ULONG SectionAlignmentFailures;
        ULONG UnsupportedRelocs;
        ULONG IATInExecutableSection;
    } SYSTEM_VERIFIER_COUNTERS_INFORMATION, *PSYSTEM_VERIFIER_COUNTERS_INFORMATION;

    // private
    typedef struct _SYSTEM_ACPI_AUDIT_INFORMATION
    {
        ULONG RsdpCount;
        ULONG SameRsdt : 1;
        ULONG SlicPresent : 1;
        ULONG SlicDifferent : 1;
    } SYSTEM_ACPI_AUDIT_INFORMATION, *PSYSTEM_ACPI_AUDIT_INFORMATION;

    // private
    typedef struct _SYSTEM_BASIC_PERFORMANCE_INFORMATION
    {
        SIZE_T AvailablePages;
        SIZE_T CommittedPages;
        SIZE_T CommitLimit;
        SIZE_T PeakCommitment;
    } SYSTEM_BASIC_PERFORMANCE_INFORMATION, *PSYSTEM_BASIC_PERFORMANCE_INFORMATION;

    // begin_msdn

    typedef struct _QUERY_PERFORMANCE_COUNTER_FLAGS
    {
        union
        {
            struct
            {
                ULONG KernelTransition : 1;
                ULONG Reserved : 31;
            };
            ULONG ul;
        };
    } QUERY_PERFORMANCE_COUNTER_FLAGS;

    typedef struct _SYSTEM_QUERY_PERFORMANCE_COUNTER_INFORMATION
    {
        ULONG Version;
        QUERY_PERFORMANCE_COUNTER_FLAGS Flags;
        QUERY_PERFORMANCE_COUNTER_FLAGS ValidFlags;
    } SYSTEM_QUERY_PERFORMANCE_COUNTER_INFORMATION, *PSYSTEM_QUERY_PERFORMANCE_COUNTER_INFORMATION;

    // end_msdn

    // private
    typedef enum _SYSTEM_PIXEL_FORMAT
    {
        SystemPixelFormatUnknown,
        SystemPixelFormatR8G8B8,
        SystemPixelFormatR8G8B8X8,
        SystemPixelFormatB8G8R8,
        SystemPixelFormatB8G8R8X8
    } SYSTEM_PIXEL_FORMAT;

    // private
    typedef struct _SYSTEM_BOOT_GRAPHICS_INFORMATION
    {
        LARGE_INTEGER FrameBuffer;
        ULONG Width;
        ULONG Height;
        ULONG PixelStride;
        ULONG Flags;
        SYSTEM_PIXEL_FORMAT Format;
        ULONG DisplayRotation;
    } SYSTEM_BOOT_GRAPHICS_INFORMATION, *PSYSTEM_BOOT_GRAPHICS_INFORMATION;

    // private
    typedef struct _MEMORY_SCRUB_INFORMATION
    {
        HANDLE Handle;
        ULONG PagesScrubbed;
    } MEMORY_SCRUB_INFORMATION, *PMEMORY_SCRUB_INFORMATION;

    // private
    typedef struct _PEBS_DS_SAVE_AREA
    {
        ULONGLONG BtsBufferBase;
        ULONGLONG BtsIndex;
        ULONGLONG BtsAbsoluteMaximum;
        ULONGLONG BtsInterruptThreshold;
        ULONGLONG PebsBufferBase;
        ULONGLONG PebsIndex;
        ULONGLONG PebsAbsoluteMaximum;
        ULONGLONG PebsInterruptThreshold;
        ULONGLONG PebsCounterReset0;
        ULONGLONG PebsCounterReset1;
        ULONGLONG PebsCounterReset2;
        ULONGLONG PebsCounterReset3;
    } PEBS_DS_SAVE_AREA, *PPEBS_DS_SAVE_AREA;

    // private
    typedef struct _PROCESSOR_PROFILE_CONTROL_AREA
    {
        PEBS_DS_SAVE_AREA PebsDsSaveArea;
    } PROCESSOR_PROFILE_CONTROL_AREA, *PPROCESSOR_PROFILE_CONTROL_AREA;

    // private
    typedef struct _SYSTEM_PROCESSOR_PROFILE_CONTROL_AREA
    {
        PROCESSOR_PROFILE_CONTROL_AREA ProcessorProfileControlArea;
        BOOLEAN Allocate;
    } SYSTEM_PROCESSOR_PROFILE_CONTROL_AREA, *PSYSTEM_PROCESSOR_PROFILE_CONTROL_AREA;

    // private
    typedef struct _MEMORY_COMBINE_INFORMATION
    {
        HANDLE Handle;
        ULONG_PTR PagesCombined;
    } MEMORY_COMBINE_INFORMATION, *PMEMORY_COMBINE_INFORMATION;

    // rev
#define MEMORY_COMBINE_FLAGS_COMMON_PAGES_ONLY 0x4

// private
    typedef struct _MEMORY_COMBINE_INFORMATION_EX
    {
        HANDLE Handle;
        ULONG_PTR PagesCombined;
        ULONG Flags;
    } MEMORY_COMBINE_INFORMATION_EX, *PMEMORY_COMBINE_INFORMATION_EX;

    // private
    typedef struct _MEMORY_COMBINE_INFORMATION_EX2
    {
        HANDLE Handle;
        ULONG_PTR PagesCombined;
        ULONG Flags;
        HANDLE ProcessHandle;
    } MEMORY_COMBINE_INFORMATION_EX2, *PMEMORY_COMBINE_INFORMATION_EX2;

    // private
    typedef struct _SYSTEM_CONSOLE_INFORMATION
    {
        ULONG DriverLoaded : 1;
        ULONG Spare : 31;
    } SYSTEM_CONSOLE_INFORMATION, *PSYSTEM_CONSOLE_INFORMATION;

    // private
    typedef struct _SYSTEM_PLATFORM_BINARY_INFORMATION
    {
        ULONG64 PhysicalAddress;
        PVOID HandoffBuffer;
        PVOID CommandLineBuffer;
        ULONG HandoffBufferSize;
        ULONG CommandLineBufferSize;
    } SYSTEM_PLATFORM_BINARY_INFORMATION, *PSYSTEM_PLATFORM_BINARY_INFORMATION;

    // private
    typedef struct _SYSTEM_HYPERVISOR_PROCESSOR_COUNT_INFORMATION
    {
        ULONG NumberOfLogicalProcessors;
        ULONG NumberOfCores;
    } SYSTEM_HYPERVISOR_PROCESSOR_COUNT_INFORMATION, *PSYSTEM_HYPERVISOR_PROCESSOR_COUNT_INFORMATION;

    // private
    typedef struct _SYSTEM_DEVICE_DATA_INFORMATION
    {
        UNICODE_STRING DeviceId;
        UNICODE_STRING DataName;
        ULONG DataType;
        ULONG DataBufferLength;
        PVOID DataBuffer;
    } SYSTEM_DEVICE_DATA_INFORMATION, *PSYSTEM_DEVICE_DATA_INFORMATION;

    // private
    typedef struct _PHYSICAL_CHANNEL_RUN
    {
        ULONG NodeNumber;
        ULONG ChannelNumber;
        ULONGLONG BasePage;
        ULONGLONG PageCount;
        ULONG Flags;
    } PHYSICAL_CHANNEL_RUN, *PPHYSICAL_CHANNEL_RUN;

    // private
    typedef struct _SYSTEM_MEMORY_TOPOLOGY_INFORMATION
    {
        ULONGLONG NumberOfRuns;
        ULONG NumberOfNodes;
        ULONG NumberOfChannels;
        PHYSICAL_CHANNEL_RUN Run[1];
    } SYSTEM_MEMORY_TOPOLOGY_INFORMATION, *PSYSTEM_MEMORY_TOPOLOGY_INFORMATION;

    // private
    typedef struct _SYSTEM_MEMORY_CHANNEL_INFORMATION
    {
        ULONG ChannelNumber;
        ULONG ChannelHeatIndex;
        ULONGLONG TotalPageCount;
        ULONGLONG ZeroPageCount;
        ULONGLONG FreePageCount;
        ULONGLONG StandbyPageCount;
    } SYSTEM_MEMORY_CHANNEL_INFORMATION, *PSYSTEM_MEMORY_CHANNEL_INFORMATION;

    // private
    typedef struct _SYSTEM_BOOT_LOGO_INFORMATION
    {
        ULONG Flags;
        ULONG BitmapOffset;
    } SYSTEM_BOOT_LOGO_INFORMATION, *PSYSTEM_BOOT_LOGO_INFORMATION;

    // private
    typedef struct _SYSTEM_PROCESSOR_PERFORMANCE_INFORMATION_EX
    {
        LARGE_INTEGER IdleTime;
        LARGE_INTEGER KernelTime;
        LARGE_INTEGER UserTime;
        LARGE_INTEGER DpcTime;
        LARGE_INTEGER InterruptTime;
        ULONG InterruptCount;
        ULONG Spare0;
        LARGE_INTEGER AvailableTime;
        LARGE_INTEGER Spare1;
        LARGE_INTEGER Spare2;
    } SYSTEM_PROCESSOR_PERFORMANCE_INFORMATION_EX, *PSYSTEM_PROCESSOR_PERFORMANCE_INFORMATION_EX;

    // private
    typedef struct _SYSTEM_SECUREBOOT_POLICY_INFORMATION
    {
        GUID PolicyPublisher;
        ULONG PolicyVersion;
        ULONG PolicyOptions;
    } SYSTEM_SECUREBOOT_POLICY_INFORMATION, *PSYSTEM_SECUREBOOT_POLICY_INFORMATION;

    // private
    typedef struct _SYSTEM_PAGEFILE_INFORMATION_EX
    {
        SYSTEM_PAGEFILE_INFORMATION Info;
        ULONG MinimumSize;
        ULONG MaximumSize;
    } SYSTEM_PAGEFILE_INFORMATION_EX, *PSYSTEM_PAGEFILE_INFORMATION_EX;

    // private
    typedef struct _SYSTEM_SECUREBOOT_INFORMATION
    {
        BOOLEAN SecureBootEnabled;
        BOOLEAN SecureBootCapable;
    } SYSTEM_SECUREBOOT_INFORMATION, *PSYSTEM_SECUREBOOT_INFORMATION;

    typedef struct _TIMELINE_BITMAP
    {
        ULONGLONG Value;
        ULONG EndTime;
        ULONG Bitmap;
    } TIMELINE_BITMAP, *PTIMELINE_BITMAP;

    typedef struct _PROCESS_ENERGY_VALUES_EXTENSION
    {
        union
        {
            TIMELINE_BITMAP Timelines[14]; // 9 for REDSTONE2, 14 for REDSTONE3
            struct
            {
                TIMELINE_BITMAP CpuTimeline;
                TIMELINE_BITMAP DiskTimeline;
                TIMELINE_BITMAP NetworkTimeline;
                TIMELINE_BITMAP MBBTimeline;
                TIMELINE_BITMAP ForegroundTimeline;
                TIMELINE_BITMAP DesktopVisibleTimeline;
                TIMELINE_BITMAP CompositionRenderedTimeline;
                TIMELINE_BITMAP CompositionDirtyGeneratedTimeline;
                TIMELINE_BITMAP CompositionDirtyPropagatedTimeline;
                TIMELINE_BITMAP InputTimeline; // REDSTONE3
                TIMELINE_BITMAP AudioInTimeline;
                TIMELINE_BITMAP AudioOutTimeline;
                TIMELINE_BITMAP DisplayRequiredTimeline;
                TIMELINE_BITMAP KeyboardInputTimeline;
            };
        };

        union // REDSTONE3
        {
            ENERGY_STATE_DURATION Durations[5];
            struct
            {
                ENERGY_STATE_DURATION InputDuration;
                ENERGY_STATE_DURATION AudioInDuration;
                ENERGY_STATE_DURATION AudioOutDuration;
                ENERGY_STATE_DURATION DisplayRequiredDuration;
                ENERGY_STATE_DURATION PSMBackgroundDuration;
            };
        };

        ULONG KeyboardInput;
        ULONG MouseInput;
    } PROCESS_ENERGY_VALUES_EXTENSION, *PPROCESS_ENERGY_VALUES_EXTENSION;

    typedef struct _PROCESS_EXTENDED_ENERGY_VALUES
    {
        PROCESS_ENERGY_VALUES Base;
        PROCESS_ENERGY_VALUES_EXTENSION Extension;
    } PROCESS_EXTENDED_ENERGY_VALUES, *PPROCESS_EXTENDED_ENERGY_VALUES;

    // private
    typedef enum _SYSTEM_PROCESS_CLASSIFICATION
    {
        SystemProcessClassificationNormal,
        SystemProcessClassificationSystem,
        SystemProcessClassificationSecureSystem,
        SystemProcessClassificationMemCompression,
        SystemProcessClassificationRegistry, // REDSTONE4
        SystemProcessClassificationMaximum
    } SYSTEM_PROCESS_CLASSIFICATION;

    // private
    typedef struct _SYSTEM_PROCESS_INFORMATION_EXTENSION
    {
        PROCESS_DISK_COUNTERS DiskCounters;
        ULONGLONG ContextSwitches;
        union
        {
            ULONG Flags;
            struct
            {
                ULONG HasStrongId : 1;
                ULONG Classification : 4; // SYSTEM_PROCESS_CLASSIFICATION
                ULONG BackgroundActivityModerated : 1;
                ULONG Spare : 26;
            };
        };
        ULONG UserSidOffset;
        ULONG PackageFullNameOffset; // since THRESHOLD
        PROCESS_ENERGY_VALUES EnergyValues; // since THRESHOLD
        ULONG AppIdOffset; // since THRESHOLD
        SIZE_T SharedCommitCharge; // since THRESHOLD2
        ULONG JobObjectId; // since REDSTONE
        ULONG SpareUlong; // since REDSTONE
        ULONGLONG ProcessSequenceNumber;
    } SYSTEM_PROCESS_INFORMATION_EXTENSION, *PSYSTEM_PROCESS_INFORMATION_EXTENSION;

    // private
    typedef struct _SYSTEM_PORTABLE_WORKSPACE_EFI_LAUNCHER_INFORMATION
    {
        BOOLEAN EfiLauncherEnabled;
    } SYSTEM_PORTABLE_WORKSPACE_EFI_LAUNCHER_INFORMATION, *PSYSTEM_PORTABLE_WORKSPACE_EFI_LAUNCHER_INFORMATION;

    // private
    typedef struct _SYSTEM_KERNEL_DEBUGGER_INFORMATION_EX
    {
        BOOLEAN DebuggerAllowed;
        BOOLEAN DebuggerEnabled;
        BOOLEAN DebuggerPresent;
    } SYSTEM_KERNEL_DEBUGGER_INFORMATION_EX, *PSYSTEM_KERNEL_DEBUGGER_INFORMATION_EX;

    // private
    typedef struct _SYSTEM_ELAM_CERTIFICATE_INFORMATION
    {
        HANDLE ElamDriverFile;
    } SYSTEM_ELAM_CERTIFICATE_INFORMATION, *PSYSTEM_ELAM_CERTIFICATE_INFORMATION;

    // private
    typedef struct _SYSTEM_PROCESSOR_FEATURES_INFORMATION
    {
        ULONGLONG ProcessorFeatureBits;
        ULONGLONG Reserved[3];
    } SYSTEM_PROCESSOR_FEATURES_INFORMATION, *PSYSTEM_PROCESSOR_FEATURES_INFORMATION;

    // private
    typedef struct _SYSTEM_MANUFACTURING_INFORMATION
    {
        ULONG Options;
        UNICODE_STRING ProfileName;
    } SYSTEM_MANUFACTURING_INFORMATION, *PSYSTEM_MANUFACTURING_INFORMATION;

    // private
    typedef struct _SYSTEM_ENERGY_ESTIMATION_CONFIG_INFORMATION
    {
        BOOLEAN Enabled;
    } SYSTEM_ENERGY_ESTIMATION_CONFIG_INFORMATION, *PSYSTEM_ENERGY_ESTIMATION_CONFIG_INFORMATION;

    // private
    typedef struct _HV_DETAILS
    {
        ULONG Data[4];
    } HV_DETAILS, *PHV_DETAILS;

    // private
    typedef struct _SYSTEM_HYPERVISOR_DETAIL_INFORMATION
    {
        HV_DETAILS HvVendorAndMaxFunction;
        HV_DETAILS HypervisorInterface;
        HV_DETAILS HypervisorVersion;
        HV_DETAILS HvFeatures;
        HV_DETAILS HwFeatures;
        HV_DETAILS EnlightenmentInfo;
        HV_DETAILS ImplementationLimits;
    } SYSTEM_HYPERVISOR_DETAIL_INFORMATION, *PSYSTEM_HYPERVISOR_DETAIL_INFORMATION;

    // private
    typedef struct _SYSTEM_PROCESSOR_CYCLE_STATS_INFORMATION
    {
        ULONGLONG Cycles[2][4];
    } SYSTEM_PROCESSOR_CYCLE_STATS_INFORMATION, *PSYSTEM_PROCESSOR_CYCLE_STATS_INFORMATION;

    // private
    typedef struct _SYSTEM_TPM_INFORMATION
    {
        ULONG Flags;
    } SYSTEM_TPM_INFORMATION, *PSYSTEM_TPM_INFORMATION;

    // private
    typedef struct _SYSTEM_DMA_PROTECTION_INFORMATION
    {
        BOOLEAN DmaProtectionsAvailable;
        BOOLEAN DmaProtectionsInUse;
    } SYSTEM_DMA_PROTECTION_INFORMATION, *PSYSTEM_DMA_PROTECTION_INFORMATION;

    // private
    typedef struct _SYSTEM_CODEINTEGRITYPOLICY_INFORMATION
    {
        ULONG Options;
        ULONG HVCIOptions;
        ULONGLONG Version;
        GUID PolicyGuid;
    } SYSTEM_CODEINTEGRITYPOLICY_INFORMATION, *PSYSTEM_CODEINTEGRITYPOLICY_INFORMATION;

    // private
    typedef struct _SYSTEM_ISOLATED_USER_MODE_INFORMATION
    {
        BOOLEAN SecureKernelRunning : 1;
        BOOLEAN HvciEnabled : 1;
        BOOLEAN HvciStrictMode : 1;
        BOOLEAN DebugEnabled : 1;
        BOOLEAN FirmwarePageProtection : 1;
        BOOLEAN SpareFlags : 1;
        BOOLEAN TrustletRunning : 1;
        BOOLEAN SpareFlags2 : 1;
        BOOLEAN Spare0[6];
        ULONGLONG Spare1;
    } SYSTEM_ISOLATED_USER_MODE_INFORMATION, *PSYSTEM_ISOLATED_USER_MODE_INFORMATION;

    // private
    typedef struct _SYSTEM_SINGLE_MODULE_INFORMATION
    {
        PVOID TargetModuleAddress;
        RTL_PROCESS_MODULE_INFORMATION_EX ExInfo;
    } SYSTEM_SINGLE_MODULE_INFORMATION, *PSYSTEM_SINGLE_MODULE_INFORMATION;

    // private
    typedef struct _SYSTEM_INTERRUPT_CPU_SET_INFORMATION
    {
        ULONG Gsiv;
        USHORT Group;
        ULONGLONG CpuSets;
    } SYSTEM_INTERRUPT_CPU_SET_INFORMATION, *PSYSTEM_INTERRUPT_CPU_SET_INFORMATION;

    // private
    typedef struct _SYSTEM_SECUREBOOT_POLICY_FULL_INFORMATION
    {
        SYSTEM_SECUREBOOT_POLICY_INFORMATION PolicyInformation;
        ULONG PolicySize;
        UCHAR Policy[1];
    } SYSTEM_SECUREBOOT_POLICY_FULL_INFORMATION, *PSYSTEM_SECUREBOOT_POLICY_FULL_INFORMATION;

    // private
    typedef struct _SYSTEM_ROOT_SILO_INFORMATION
    {
        ULONG NumberOfSilos;
        ULONG SiloIdList[1];
    } SYSTEM_ROOT_SILO_INFORMATION, *PSYSTEM_ROOT_SILO_INFORMATION;

    // private
    typedef struct _SYSTEM_CPU_SET_TAG_INFORMATION
    {
        ULONGLONG Tag;
        ULONGLONG CpuSets[1];
    } SYSTEM_CPU_SET_TAG_INFORMATION, *PSYSTEM_CPU_SET_TAG_INFORMATION;

    // private
    typedef struct _SYSTEM_SECURE_KERNEL_HYPERGUARD_PROFILE_INFORMATION
    {
        ULONG ExtentCount;
        ULONG ValidStructureSize;
        ULONG NextExtentIndex;
        ULONG ExtentRestart;
        ULONG CycleCount;
        ULONG TimeoutCount;
        ULONGLONG CycleTime;
        ULONGLONG CycleTimeMax;
        ULONGLONG ExtentTime;
        ULONG ExtentTimeIndex;
        ULONG ExtentTimeMaxIndex;
        ULONGLONG ExtentTimeMax;
        ULONGLONG HyperFlushTimeMax;
        ULONGLONG TranslateVaTimeMax;
        ULONGLONG DebugExemptionCount;
        ULONGLONG TbHitCount;
        ULONGLONG TbMissCount;
        ULONGLONG VinaPendingYield;
        ULONGLONG HashCycles;
        ULONG HistogramOffset;
        ULONG HistogramBuckets;
        ULONG HistogramShift;
        ULONG Reserved1;
        ULONGLONG PageNotPresentCount;
    } SYSTEM_SECURE_KERNEL_HYPERGUARD_PROFILE_INFORMATION, *PSYSTEM_SECURE_KERNEL_HYPERGUARD_PROFILE_INFORMATION;

    // private
    typedef struct _SYSTEM_SECUREBOOT_PLATFORM_MANIFEST_INFORMATION
    {
        ULONG PlatformManifestSize;
        UCHAR PlatformManifest[1];
    } SYSTEM_SECUREBOOT_PLATFORM_MANIFEST_INFORMATION, *PSYSTEM_SECUREBOOT_PLATFORM_MANIFEST_INFORMATION;

    // private
    typedef struct _SYSTEM_MEMORY_USAGE_INFORMATION
    {
        ULONGLONG TotalPhysicalBytes;
        ULONGLONG AvailableBytes;
        LONGLONG ResidentAvailableBytes;
        ULONGLONG CommittedBytes;
        ULONGLONG SharedCommittedBytes;
        ULONGLONG CommitLimitBytes;
        ULONGLONG PeakCommitmentBytes;
    } SYSTEM_MEMORY_USAGE_INFORMATION, *PSYSTEM_MEMORY_USAGE_INFORMATION;

    // private
    typedef struct _SYSTEM_CODEINTEGRITY_CERTIFICATE_INFORMATION
    {
        HANDLE ImageFile;
        ULONG Type; // REDSTONE4
    } SYSTEM_CODEINTEGRITY_CERTIFICATE_INFORMATION, *PSYSTEM_CODEINTEGRITY_CERTIFICATE_INFORMATION;

    // private
    typedef struct _SYSTEM_PHYSICAL_MEMORY_INFORMATION
    {
        ULONGLONG TotalPhysicalBytes;
        ULONGLONG LowestPhysicalAddress;
        ULONGLONG HighestPhysicalAddress;
    } SYSTEM_PHYSICAL_MEMORY_INFORMATION, *PSYSTEM_PHYSICAL_MEMORY_INFORMATION;

    // private
    typedef enum _SYSTEM_ACTIVITY_MODERATION_STATE
    {
        SystemActivityModerationStateSystemManaged,
        SystemActivityModerationStateUserManagedAllowThrottling,
        SystemActivityModerationStateUserManagedDisableThrottling,
        MaxSystemActivityModerationState
    } SYSTEM_ACTIVITY_MODERATION_STATE;

    // private - REDSTONE2
    typedef struct _SYSTEM_ACTIVITY_MODERATION_EXE_STATE // REDSTONE3: Renamed SYSTEM_ACTIVITY_MODERATION_INFO
    {
        UNICODE_STRING ExePathNt;
        SYSTEM_ACTIVITY_MODERATION_STATE ModerationState;
    } SYSTEM_ACTIVITY_MODERATION_EXE_STATE, *PSYSTEM_ACTIVITY_MODERATION_EXE_STATE;

    typedef enum _SYSTEM_ACTIVITY_MODERATION_APP_TYPE
    {
        SystemActivityModerationAppTypeClassic,
        SystemActivityModerationAppTypePackaged,
        MaxSystemActivityModerationAppType
    } SYSTEM_ACTIVITY_MODERATION_APP_TYPE;

    // private - REDSTONE3
    typedef struct _SYSTEM_ACTIVITY_MODERATION_INFO
    {
        UNICODE_STRING Identifier;
        SYSTEM_ACTIVITY_MODERATION_STATE ModerationState;
        SYSTEM_ACTIVITY_MODERATION_APP_TYPE AppType;
    } SYSTEM_ACTIVITY_MODERATION_INFO, *PSYSTEM_ACTIVITY_MODERATION_INFO;

    // private
    typedef struct _SYSTEM_ACTIVITY_MODERATION_USER_SETTINGS
    {
        HANDLE UserKeyHandle;
    } SYSTEM_ACTIVITY_MODERATION_USER_SETTINGS, *PSYSTEM_ACTIVITY_MODERATION_USER_SETTINGS;

    // private
    typedef struct _SYSTEM_CODEINTEGRITY_UNLOCK_INFORMATION
    {
        union
        {
            ULONG Flags;
            struct
            {
                ULONG Locked : 1;
                ULONG Unlockable : 1;
                ULONG UnlockApplied : 1;
                ULONG UnlockIdValid : 1; // REDSTONE4
                ULONG Reserved : 28;
            };
        };
        UCHAR UnlockId[32]; // REDSTONE4
    } SYSTEM_CODEINTEGRITY_UNLOCK_INFORMATION, *PSYSTEM_CODEINTEGRITY_UNLOCK_INFORMATION;

    // private
    typedef struct _SYSTEM_FLUSH_INFORMATION
    {
        ULONG SupportedFlushMethods;
        ULONG ProcessorCacheFlushSize;
        ULONGLONG SystemFlushCapabilities;
        ULONGLONG Reserved[2];
    } SYSTEM_FLUSH_INFORMATION, *PSYSTEM_FLUSH_INFORMATION;

    // private
    typedef struct _SYSTEM_WRITE_CONSTRAINT_INFORMATION
    {
        ULONG WriteConstraintPolicy;
        ULONG Reserved;
    } SYSTEM_WRITE_CONSTRAINT_INFORMATION, *PSYSTEM_WRITE_CONSTRAINT_INFORMATION;

    // private
    typedef struct _SYSTEM_KERNEL_VA_SHADOW_INFORMATION
    {
        union
        {
            ULONG Flags;
            struct
            {
                ULONG KvaShadowEnabled : 1;
                ULONG KvaShadowUserGlobal : 1;
                ULONG KvaShadowPcid : 1;
                ULONG KvaShadowInvpcid : 1;
                ULONG KvaShadowRequired : 1; // REDSTONE4
                ULONG KvaShadowRequiredAvailable : 1;
                ULONG Reserved : 26;
            };
        };
    } SYSTEM_KERNEL_VA_SHADOW_INFORMATION, *PSYSTEM_KERNEL_VA_SHADOW_INFORMATION;

    // private
    typedef struct _SYSTEM_CODEINTEGRITYVERIFICATION_INFORMATION
    {
        HANDLE FileHandle;
        ULONG ImageSize;
        PVOID Image;
    } SYSTEM_CODEINTEGRITYVERIFICATION_INFORMATION, *PSYSTEM_CODEINTEGRITYVERIFICATION_INFORMATION;

    // private
    typedef struct _SYSTEM_HYPERVISOR_SHARED_PAGE_INFORMATION
    {
        PVOID HypervisorSharedUserVa;
    } SYSTEM_HYPERVISOR_SHARED_PAGE_INFORMATION, *PSYSTEM_HYPERVISOR_SHARED_PAGE_INFORMATION;

    // private
    typedef struct _SYSTEM_SPECULATION_CONTROL_INFORMATION
    {
        union
        {
            ULONG Flags;
            struct
            {
                ULONG BpbEnabled : 1;
                ULONG BpbDisabledSystemPolicy : 1;
                ULONG BpbDisabledNoHardwareSupport : 1;
                ULONG SpecCtrlEnumerated : 1;
                ULONG SpecCmdEnumerated : 1;
                ULONG IbrsPresent : 1;
                ULONG StibpPresent : 1;
                ULONG SmepPresent : 1;
                ULONG Reserved : 24;
            };
        };
    } SYSTEM_SPECULATION_CONTROL_INFORMATION, *PSYSTEM_SPECULATION_CONTROL_INFORMATION;

    // private
    typedef struct _SYSTEM_DMA_GUARD_POLICY_INFORMATION
    {
        BOOLEAN DmaGuardPolicyEnabled;
    } SYSTEM_DMA_GUARD_POLICY_INFORMATION, *PSYSTEM_DMA_GUARD_POLICY_INFORMATION;

    // private
    typedef struct _SYSTEM_ENCLAVE_LAUNCH_CONTROL_INFORMATION
    {
        UCHAR EnclaveLaunchSigner[32];
    } SYSTEM_ENCLAVE_LAUNCH_CONTROL_INFORMATION, *PSYSTEM_ENCLAVE_LAUNCH_CONTROL_INFORMATION;
#pragma endregion


#pragma region Port
    typedef enum _PORT_INFORMATION_CLASS
    {
        PortBasicInformation,
        PortDumpInformation
    } PORT_INFORMATION_CLASS;
#pragma endregion


#pragma region Object
    typedef enum _OBJECT_INFORMATION_CLASS
    {
        ObjectBasicInformation, // OBJECT_BASIC_INFORMATION
        ObjectNameInformation, // OBJECT_NAME_INFORMATION
        ObjectTypeInformation, // OBJECT_TYPE_INFORMATION
        ObjectTypesInformation, // OBJECT_TYPES_INFORMATION
        ObjectHandleFlagInformation, // OBJECT_HANDLE_FLAG_INFORMATION
        ObjectSessionInformation,
        ObjectSessionObjectInformation,
        MaxObjectInfoClass
    } OBJECT_INFORMATION_CLASS;

    typedef struct _OBJECT_BASIC_INFORMATION
    {
        ULONG Attributes;
        ACCESS_MASK GrantedAccess;
        ULONG HandleCount;
        ULONG PointerCount;
        ULONG PagedPoolCharge;
        ULONG NonPagedPoolCharge;
        ULONG Reserved[3];
        ULONG NameInfoSize;
        ULONG TypeInfoSize;
        ULONG SecurityDescriptorSize;
        LARGE_INTEGER CreationTime;
    } OBJECT_BASIC_INFORMATION, *POBJECT_BASIC_INFORMATION;

    typedef struct _OBJECT_TYPE_INFORMATION
    {
        UNICODE_STRING TypeName;
        ULONG TotalNumberOfObjects;
        ULONG TotalNumberOfHandles;
        ULONG TotalPagedPoolUsage;
        ULONG TotalNonPagedPoolUsage;
        ULONG TotalNamePoolUsage;
        ULONG TotalHandleTableUsage;
        ULONG HighWaterNumberOfObjects;
        ULONG HighWaterNumberOfHandles;
        ULONG HighWaterPagedPoolUsage;
        ULONG HighWaterNonPagedPoolUsage;
        ULONG HighWaterNamePoolUsage;
        ULONG HighWaterHandleTableUsage;
        ULONG InvalidAttributes;
        GENERIC_MAPPING GenericMapping;
        ULONG ValidAccessMask;
        BOOLEAN SecurityRequired;
        BOOLEAN MaintainHandleCount;
        UCHAR TypeIndex; // since WINBLUE
        CHAR ReservedByte;
        ULONG PoolType;
        ULONG DefaultPagedPoolCharge;
        ULONG DefaultNonPagedPoolCharge;
    } OBJECT_TYPE_INFORMATION, *POBJECT_TYPE_INFORMATION;

    typedef struct _OBJECT_TYPES_INFORMATION
    {
        ULONG NumberOfTypes;
    } OBJECT_TYPES_INFORMATION, *POBJECT_TYPES_INFORMATION;

    typedef struct _OBJECT_HANDLE_FLAG_INFORMATION
    {
        BOOLEAN Inherit;
        BOOLEAN ProtectFromClose;
    } OBJECT_HANDLE_FLAG_INFORMATION, *POBJECT_HANDLE_FLAG_INFORMATION;
#pragma endregion


#pragma region Memory
    typedef enum _MEMORY_INFORMATION_CLASS
    {
        MemoryBasicInformation, // MEMORY_BASIC_INFORMATION
        MemoryWorkingSetInformation, // MEMORY_WORKING_SET_INFORMATION
        MemoryMappedFilenameInformation, // MEMORY_MAPPED_FILE_NAME_INFORMATION
        MemoryRegionInformation, // MEMORY_REGION_INFORMATION
        MemoryWorkingSetExInformation, // MEMORY_WORKING_SET_EX_INFORMATION
        MemorySharedCommitInformation, // MEMORY_SHARED_COMMIT_INFORMATION
        MemoryImageInformation, // MEMORY_IMAGE_INFORMATION
        MemoryRegionInformationEx,
        MemoryPrivilegedBasicInformation,
        MemoryEnclaveImageInformation, // MEMORY_ENCLAVE_IMAGE_INFORMATION // since REDSTONE3
        MemoryBasicInformationCapped
    } MEMORY_INFORMATION_CLASS;

    typedef struct _MEMORY_BASIC_INFORMATION {
        PVOID BaseAddress;
        PVOID AllocationBase;
        ULONG AllocationProtect;
        SIZE_T RegionSize;
        ULONG State;
        ULONG Protect;
        ULONG Type;
    } MEMORY_BASIC_INFORMATION, *PMEMORY_BASIC_INFORMATION;

    typedef struct _MEMORY_WORKING_SET_BLOCK
    {
        ULONG_PTR Protection : 5;
        ULONG_PTR ShareCount : 3;
        ULONG_PTR Shared : 1;
        ULONG_PTR Node : 3;
#ifdef _WIN64
        ULONG_PTR VirtualPage : 52;
#else
        ULONG VirtualPage : 20;
#endif
    } MEMORY_WORKING_SET_BLOCK, *PMEMORY_WORKING_SET_BLOCK;

    typedef struct _MEMORY_WORKING_SET_INFORMATION
    {
        ULONG_PTR NumberOfEntries;
        MEMORY_WORKING_SET_BLOCK WorkingSetInfo[1];
    } MEMORY_WORKING_SET_INFORMATION, *PMEMORY_WORKING_SET_INFORMATION;
    
    typedef struct _MEMORY_MAPPED_FILE_NAME_INFORMATION
    {
        enum : UINT32 { MaxObjectName = 512 / sizeof(WCHAR) };

        UNICODE_STRING  Name;
        WCHAR           Buffer[MaxObjectName];
    } MEMORY_MAPPED_FILE_NAME_INFORMATION, *PMEMORY_MAPPED_FILE_NAME_INFORMATION;

    // private
    typedef struct _MEMORY_REGION_INFORMATION
    {
        PVOID AllocationBase;
        ULONG AllocationProtect;
        union
        {
            ULONG RegionType;
            struct
            {
                ULONG Private : 1;
                ULONG MappedDataFile : 1;
                ULONG MappedImage : 1;
                ULONG MappedPageFile : 1;
                ULONG MappedPhysical : 1;
                ULONG DirectMapped : 1;
                ULONG SoftwareEnclave : 1; // REDSTONE3
                ULONG PageSize64K : 1;
                ULONG PlaceholderReservation : 1; // REDSTONE4
                ULONG Reserved : 23;
            };
        };
        SIZE_T RegionSize;
        SIZE_T CommitSize;
    } MEMORY_REGION_INFORMATION, *PMEMORY_REGION_INFORMATION;

    // private 
    typedef enum _MEMORY_WORKING_SET_EX_LOCATION
    {
        MemoryLocationInvalid,
        MemoryLocationResident,
        MemoryLocationPagefile,
        MemoryLocationReserved
    } MEMORY_WORKING_SET_EX_LOCATION;

    // private
    typedef struct _MEMORY_WORKING_SET_EX_BLOCK
    {
        union
        {
            struct
            {
                ULONG_PTR Valid : 1;
                ULONG_PTR ShareCount : 3;
                ULONG_PTR Win32Protection : 11;
                ULONG_PTR Shared : 1;
                ULONG_PTR Node : 6;
                ULONG_PTR Locked : 1;
                ULONG_PTR LargePage : 1;
                ULONG_PTR Priority : 3;
                ULONG_PTR Reserved : 3;
                ULONG_PTR SharedOriginal : 1;
                ULONG_PTR Bad : 1;
#ifdef _WIN64
                ULONG_PTR ReservedUlong : 32;
#endif
            };
            struct
            {
                ULONG_PTR Valid : 1;
                ULONG_PTR Reserved0 : 14;
                ULONG_PTR Shared : 1;
                ULONG_PTR Reserved1 : 5;
                ULONG_PTR PageTable : 1;
                ULONG_PTR Location : 2;
                ULONG_PTR Priority : 3;
                ULONG_PTR ModifiedList : 1;
                ULONG_PTR Reserved2 : 2;
                ULONG_PTR SharedOriginal : 1;
                ULONG_PTR Bad : 1;
#ifdef _WIN64
                ULONG_PTR ReservedUlong : 32;
#endif
            } Invalid;
        };
    } MEMORY_WORKING_SET_EX_BLOCK, *PMEMORY_WORKING_SET_EX_BLOCK;

    // private
    typedef struct _MEMORY_WORKING_SET_EX_INFORMATION
    {
        PVOID VirtualAddress;
        union
        {
            MEMORY_WORKING_SET_EX_BLOCK VirtualAttributes;
            ULONG_PTR Long;
        } u1;
    } MEMORY_WORKING_SET_EX_INFORMATION, *PMEMORY_WORKING_SET_EX_INFORMATION;

    // private
    typedef struct _MEMORY_SHARED_COMMIT_INFORMATION
    {
        SIZE_T CommitSize;
    } MEMORY_SHARED_COMMIT_INFORMATION, *PMEMORY_SHARED_COMMIT_INFORMATION;

    // private
    typedef struct _MEMORY_IMAGE_INFORMATION
    {
        PVOID ImageBase;
        SIZE_T SizeOfImage;
        union
        {
            ULONG ImageFlags;
            struct
            {
                ULONG ImagePartialMap : 1;
                ULONG ImageNotExecutable : 1;
                ULONG ImageSigningLevel : 4; // REDSTONE3
                ULONG Reserved : 26;
            };
        };
    } MEMORY_IMAGE_INFORMATION, *PMEMORY_IMAGE_INFORMATION;
#pragma endregion


#pragma region Virtual Memory
    typedef enum _VIRTUAL_MEMORY_INFORMATION_CLASS
    {
        VmPrefetchInformation, // ULONG
        VmPagePriorityInformation,
        VmCfgCallTargetInformation, // CFG_CALL_TARGET_LIST_INFORMATION // REDSTONE2
        VmPageDirtyStateInformation // REDSTONE3
    } VIRTUAL_MEMORY_INFORMATION_CLASS;

    typedef struct _MEMORY_RANGE_ENTRY
    {
        PVOID VirtualAddress;
        SIZE_T NumberOfBytes;
    } MEMORY_RANGE_ENTRY, *PMEMORY_RANGE_ENTRY;

    typedef struct _CFG_CALL_TARGET_INFO
    {
        enum FlagsMask: ULONG_PTR
        {
            CFGCallTargetValid                          = 0x00000001,
            CFGCallTargetProcessed                      = 0x00000002,
            CFGCallTargetConvertExportSuppressedToValid = 0x00000004,
        };

        ULONG_PTR Offset;
        ULONG_PTR Flags;
    } CFG_CALL_TARGET_INFO, *PCFG_CALL_TARGET_INFO;

    typedef struct _CFG_CALL_TARGET_LIST_INFORMATION
    {
        ULONG NumberOfEntries;
        ULONG Reserved;
        PULONG NumberOfEntriesProcessed;
        PCFG_CALL_TARGET_INFO CallTargetInfo;
    } CFG_CALL_TARGET_LIST_INFORMATION, *PCFG_CALL_TARGET_LIST_INFORMATION;
#pragma endregion


#pragma region Token
    typedef enum _TOKEN_INFORMATION_CLASS
    {
        TokenUser = 1,
        TokenGroups,
        TokenPrivileges,
        TokenOwner,
        TokenPrimaryGroup,
        TokenDefaultDacl,
        TokenSource,
        TokenType,
        TokenImpersonationLevel,
        TokenStatistics,
        TokenRestrictedSids,
        TokenSessionId,
        TokenGroupsAndPrivileges,
        TokenSessionReference,
        TokenSandBoxInert,
        TokenAuditPolicy,
        TokenOrigin,
        TokenElevationType,
        TokenLinkedToken,
        TokenElevation,
        TokenHasRestrictions,
        TokenAccessInformation,
        TokenVirtualizationAllowed,
        TokenVirtualizationEnabled,
        TokenIntegrityLevel,
        TokenUIAccess,
        TokenMandatoryPolicy,
        TokenLogonSid,
        TokenIsAppContainer,
        TokenCapabilities,
        TokenAppContainerSid,
        TokenAppContainerNumber,
        TokenUserClaimAttributes,
        TokenDeviceClaimAttributes,
        TokenRestrictedUserClaimAttributes,
        TokenRestrictedDeviceClaimAttributes,
        TokenDeviceGroups,
        TokenRestrictedDeviceGroups,
        TokenSecurityAttributes,
        TokenIsRestricted,
        TokenProcessTrustLevel,
        TokenPrivateNameSpace,
        TokenSingletonAttributes,
        TokenBnoIsolation,
        TokenChildProcessFlags,
        MaxTokenInfoClass  // MaxTokenInfoClass should always be the last enum
    } TOKEN_INFORMATION_CLASS, *PTOKEN_INFORMATION_CLASS;
#pragma endregion


#pragma region Debug
    typedef enum _DEBUGOBJECTINFOCLASS : UINT32
    {
        DebugObjectFlags    = 0x00000001,

    } DEBUGOBJECTINFOCLASS, *PDEBUGOBJECTINFOCLASS;

    enum DebugObjectFlagsMask: ULONG
    {
        DEBUG_KILL_ON_CLOSE = 0x1
    };
#pragma endregion

#pragma region File
    typedef struct _FILE_LINK_INFORMATION {
        BOOLEAN ReplaceIfExists;// FileLinkInformation
        HANDLE  RootDirectory;
        ULONG   FileNameLength;
        WCHAR   FileName[1];
    } FILE_LINK_INFORMATION, *PFILE_LINK_INFORMATION;

    typedef struct _FILE_LINK_INFORMATION_EX {
        ULONG   Flags;          // FileLinkInformationEx
        HANDLE  RootDirectory;
        ULONG   FileNameLength;
        WCHAR   FileName[1];
    } FILE_LINK_INFORMATION_EX, *PFILE_LINK_INFORMATION_EX;

    typedef struct _FILE_RENAME_INFORMATION {
        BOOLEAN ReplaceIfExists;// FileRenameInformation
        HANDLE  RootDirectory;
        ULONG   FileNameLength;
        WCHAR   FileName[1];
    } FILE_RENAME_INFORMATION, *PFILE_RENAME_INFORMATION;

    typedef struct _FILE_RENAME_INFORMATION_EX {
        ULONG   Flags;          // FileRenameInformationEx
        HANDLE  RootDirectory;
        ULONG   FileNameLength;
        WCHAR   FileName[1];
    } FILE_RENAME_INFORMATION_EX, *PFILE_RENAME_INFORMATION_EX;
    
    typedef struct _FILE_ALLOCATION_INFORMATION {
        LARGE_INTEGER AllocationSize;
    } FILE_ALLOCATION_INFORMATION, *PFILE_ALLOCATION_INFORMATION;

    typedef struct _FILE_FULL_DIR_INFORMATION {
        ULONG NextEntryOffset;
        ULONG FileIndex;
        LARGE_INTEGER CreationTime;
        LARGE_INTEGER LastAccessTime;
        LARGE_INTEGER LastWriteTime;
        LARGE_INTEGER ChangeTime;
        LARGE_INTEGER EndOfFile;
        LARGE_INTEGER AllocationSize;
        ULONG FileAttributes;
        ULONG FileNameLength;
        ULONG EaSize;
        WCHAR FileName[1];
    } FILE_FULL_DIR_INFORMATION, *PFILE_FULL_DIR_INFORMATION;

    typedef struct _FILE_BOTH_DIR_INFORMATION {
        ULONG NextEntryOffset;
        ULONG FileIndex;
        LARGE_INTEGER CreationTime;
        LARGE_INTEGER LastAccessTime;
        LARGE_INTEGER LastWriteTime;
        LARGE_INTEGER ChangeTime;
        LARGE_INTEGER EndOfFile;
        LARGE_INTEGER AllocationSize;
        ULONG FileAttributes;
        ULONG FileNameLength;
        ULONG EaSize;
        CCHAR ShortNameLength;
        WCHAR ShortName[12];
        WCHAR FileName[1];
    } FILE_BOTH_DIR_INFORMATION, *PFILE_BOTH_DIR_INFORMATION;
#pragma endregion

}
