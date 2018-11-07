#pragma once


/*
 * PDB file: \Nt-Crucial-Modules\Ntoskrnl\6.2.9200.17581\
 * Dumped by pdbex tool v0.4, by wbenny
 */


namespace wdk::build_9200
{

    typedef struct _MM_AVL_NODE
    {
        union // _TAG_UNNAMED_65
        {
            union
            {
                SSIZE_T Balance : 2; /* bit position: 0 */
                struct _MM_AVL_NODE* Parent;
            };
        }  u1;
        struct _MM_AVL_NODE* LeftChild;
        struct _MM_AVL_NODE* RightChild;
    } MM_AVL_NODE, *PMM_AVL_NODE; /* size: 0x0018 */ /* size: 0x000c */
    static_assert(sizeof(MM_AVL_NODE) == (sizeof(SIZE_T) == sizeof(UINT64) ? 0x0018 : 0x000c));


    typedef struct _MM_AVL_TABLE
    {
        struct _MM_AVL_NODE BalancedRoot;
        struct /* bitfield */
        {
            SIZE_T DepthOfTree : 5; /* bit position: 0 */
            SIZE_T TableType : 3; /* bit position: 5 */
            SIZE_T NumberGenericTableElements : sizeof(SIZE_T) * 8 - 8; /* bit position: 8 */
        }; /* bitfield */
        VOID* NodeHint;
        VOID* NodeFreeHint;
    } MM_AVL_TABLE, *PMM_AVL_TABLE; /* size: 0x0030 */ /* size: 0x0018 */
    static_assert(sizeof(MM_AVL_TABLE) == (sizeof(SIZE_T) == sizeof(UINT64) ? 0x0030 : 0x0018));


    typedef struct _MMSUPPORT
    {
        struct _EX_PUSH_LOCK WorkingSetMutex;
        struct _KGATE* ExitGate;
        VOID* AccessLog;
        struct _LIST_ENTRY WorkingSetExpansionLinks;
        UINT32 AgeDistribution[7];
        UINT32 MinimumWorkingSetSize;
        UINT32 WorkingSetSize;
        UINT32 WorkingSetPrivateSize;
        UINT32 MaximumWorkingSetSize;
        UINT32 ChargedWslePages;
        UINT32 ActualWslePages;
        UINT32 WorkingSetSizeOverhead;
        UINT32 PeakWorkingSetSize;
        UINT32 HardFaultCount;
        struct _MMWSL* VmWorkingSetList;
        UINT16 NextPageColor;
        UINT16 LastTrimStamp;
        UINT32 PageFaultCount;
        UINT32 TrimmedPageCount;
#ifdef _WIN64
        UINT32 Spare;
#endif
        UINT32 ForceTrimPages;
        struct _MMSUPPORT_FLAGS Flags;
        VOID* WsSwapSupport;
    } MMSUPPORT, *PMMSUPPORT; /* size: 0x0090 */ /* size: 0x0070 */
    static_assert(sizeof(MMSUPPORT) == (sizeof(SIZE_T) == sizeof(UINT64) ? 0x0090 : 0x0070));


}
