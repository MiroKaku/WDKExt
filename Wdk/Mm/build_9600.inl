#pragma once


/*
 * PDB file: \Nt-Crucial-Modules\Ntoskrnl\6.3.9600.19038\
 * Dumped by pdbex tool v0.4, by wbenny
 */


namespace wdk::build_9600
{


    typedef struct _MMSUPPORT
    {
        struct _KGATE* ExitGate;
        VOID* AccessLog;
        struct _EX_PUSH_LOCK WorkingSetMutex;
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
        struct _MMWSL* VmWorkingSetList;
        UINT16 NextPageColor;
        UINT16 LastTrimStamp;
        UINT32 PageFaultCount;
        SIZE_T TrimmedPageCount;
        SIZE_T ForceTrimPages;
        struct _MMSUPPORT_FLAGS Flags;
        VOID* WsSwapSupport;
        VOID* ShadowMapping;
    } MMSUPPORT, *PMMSUPPORT; /* size: 0x00f0 */ /* size: 0x007c */
    static_assert(sizeof(MMSUPPORT) == (sizeof(SIZE_T) == sizeof(UINT64) ? 0x00f0 : 0x007c));

}
