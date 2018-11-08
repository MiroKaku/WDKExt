#pragma once


/*
 * PDB file: \Nt-Crucial-Modules\Ntoskrnl\10.0.17134.376\
 * Dumped by pdbex tool v0.4, by wbenny
 */


namespace wdk::build_17134
{

    typedef struct _MMSUPPORT_INSTANCE
    {
        UINT32 NextPageColor;
        UINT32 PageFaultCount;
        SIZE_T TrimmedPageCount;
        struct _MMWSL_INSTANCE* VmWorkingSetList;
        struct _LIST_ENTRY WorkingSetExpansionLinks;
        SIZE_T AgeDistribution[8];
        struct _KGATE* ExitOutswapGate;
        SIZE_T MinimumWorkingSetSize;
        SIZE_T WorkingSetLeafSize;
        SIZE_T WorkingSetLeafPrivateSize;
        SIZE_T WorkingSetSize;
        SIZE_T WorkingSetPrivateSize;
        SIZE_T MaximumWorkingSetSize;
        SIZE_T PeakWorkingSetSize;
        UINT32 HardFaultCount;
        UINT16 LastTrimStamp;
#ifdef _WIN64
        UINT16 PartitionId;
        UINT64 SelfmapLock;
#else
        UINT16 Unused0;
#endif
        struct _MMSUPPORT_FLAGS Flags;
    } MMSUPPORT_INSTANCE, *PMMSUPPORT_INSTANCE; /* size: 0x00c0 */ /* size: 0x0064 */
    static_assert(sizeof(MMSUPPORT_INSTANCE) == (sizeof(SIZE_T) == sizeof(UINT64) ? 0x00c0 : 0x0064));


    typedef struct _MMSUPPORT_SHARED
    {
        volatile INT32 WorkingSetLock;
        INT32 GoodCitizenWaiting;
        SIZE_T ReleasedCommitDebt;
        SIZE_T ResetPagesRepurposedCount;
        VOID* WsSwapSupport;
        VOID* CommitReleaseContext;
        volatile INT32 WorkingSetCoreLock;
        VOID* AccessLog;
        volatile SIZE_T ChargedWslePages;
        SIZE_T ActualWslePages;
        VOID* ShadowMapping;
    } MMSUPPORT_SHARED, *PMMSUPPORT_SHARED; /* size: 0x0050 */ /* size: 0x002c */
    static_assert(sizeof(MMSUPPORT_SHARED) == (sizeof(SIZE_T) == sizeof(UINT64) ? 0x0050 : 0x002c));


    typedef struct _MMSUPPORT_FULL
    {
        struct _MMSUPPORT_INSTANCE Instance;
        struct _MMSUPPORT_SHARED Shared;
    } MMSUPPORT_FULL, *PMMSUPPORT_FULL; /* size: 0x0110 */ /* size: 0x0090 */
    static_assert(sizeof(MMSUPPORT_FULL) == (sizeof(SIZE_T) == sizeof(UINT64) ? 0x0110 : 0x0090));


}
