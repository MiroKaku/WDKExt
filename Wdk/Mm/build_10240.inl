#pragma once


/*
 * PDB file: \Nt-Crucial-Modules\Ntoskrnl\10.0.10240.17443\
 * Dumped by pdbex tool v0.4, by wbenny
 */


namespace wdk::build_10240
{

    typedef struct _MMSUPPORT
    {
        volatile INT32 WorkingSetLock;
        struct _KGATE* ExitOutswapGate;
        VOID* AccessLog;
        struct _LIST_ENTRY WorkingSetExpansionLinks;
        SIZE_T AgeDistribution[7];
        SIZE_T MinimumWorkingSetSize;
        SIZE_T WorkingSetLeafSize;
        SIZE_T WorkingSetLeafPrivateSize;
        SIZE_T WorkingSetSize;
        SIZE_T WorkingSetPrivateSize;
        SIZE_T MaximumWorkingSetSize;
        SIZE_T ChargedWslePages;
        SIZE_T ActualWslePages;
        SIZE_T WorkingSetSizeOverhead;
        SIZE_T PeakWorkingSetSize;
        UINT32 HardFaultCount;
#ifdef _WIN64
        UINT16 PartitionId;
        UINT16 Pad0;
#endif
        struct _MMWSL* VmWorkingSetList;
        UINT16 NextPageColor;
        UINT16 LastTrimStamp;
        UINT32 PageFaultCount;
        SIZE_T TrimmedPageCount;
        SIZE_T ForceTrimPages;
        struct _MMSUPPORT_FLAGS Flags;
        SIZE_T ReleasedCommitDebt;
        VOID* WsSwapSupport;
        VOID* CommitReAcquireFailSupport;
    } MMSUPPORT, *PMMSUPPORT; /* size: 0x00f8 */ /* size: 0x0080 */
    static_assert(sizeof(MMSUPPORT) == (sizeof(SIZE_T) == sizeof(UINT64) ? 0x00f8 : 0x0080));

}
