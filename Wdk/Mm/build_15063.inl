#pragma once


/*
 * PDB file: \Nt-Crucial-Modules\Ntoskrnl\10.0.15063.1418\
 * Dumped by pdbex tool v0.4, by wbenny
 */


namespace wdk::build_15063
{

    typedef struct _MMSUPPORT_INSTANCE
    {
        UINT16 NextPageColor;
        UINT16 LastTrimStamp;
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
#ifdef _WIN64
        UINT16 PartitionId;
        UINT16 Pad0;
#endif
        union // _TAG_UNNAMED_21
        {
            VOID* InstancedWorkingSet;
        } u1;
        SIZE_T Reserved0;
        struct _MMSUPPORT_FLAGS Flags;
    } MMSUPPORT_INSTANCE, *PMMSUPPORT_INSTANCE; /* size: 0x00c8 */ /* size: 0x0068 */
    static_assert(sizeof(MMSUPPORT_INSTANCE) == (sizeof(SIZE_T) == sizeof(UINT64) ? 0x00c8 : 0x0068));


    typedef struct _MMSUPPORT_SHARED
    {
        volatile INT32 WorkingSetLock;
        INT32 GoodCitizenWaiting;
        SIZE_T ReleasedCommitDebt;
        SIZE_T ResetPagesRepurposedCount;
        VOID* WsSwapSupport;
        VOID* CommitReleaseContext;
        VOID* AccessLog;
        SIZE_T ChargedWslePages;
        SIZE_T ActualWslePages;
        VOID* ShadowMapping;
    } MMSUPPORT_SHARED, *PMMSUPPORT_SHARED; /* size: 0x0048 */ /* size: 0x0028 */
    static_assert(sizeof(MMSUPPORT_SHARED) == (sizeof(SIZE_T) == sizeof(UINT64) ? 0x0048 : 0x0028));


    typedef struct _MMSUPPORT_FULL
    {
        struct _MMSUPPORT_INSTANCE Instance;
        struct _MMSUPPORT_SHARED Shared;
    } MMSUPPORT_FULL, *PMMSUPPORT_FULL; /* size: 0x0110 */ /* size: 0x0090 */
    static_assert(sizeof(MMSUPPORT_FULL) == (sizeof(SIZE_T) == sizeof(UINT64) ? 0x0110 : 0x0090));



}
