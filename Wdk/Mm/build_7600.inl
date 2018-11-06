#pragma once


/*
 * PDB file: \Nt-Crucial-Modules\Ntoskrnl\6.1.7600.17795\
 * Dumped by pdbex tool v0.4, by wbenny
 */


namespace wdk::build_7600
{

    typedef struct _MMADDRESS_NODE
    {
        union
        {
            union
            {
                SIZE_T Balance : 2; /* bit position: 0 */
                struct _MMADDRESS_NODE* Parent;
            };
        } u1;
        struct _MMADDRESS_NODE* LeftChild;
        struct _MMADDRESS_NODE* RightChild;
        SIZE_T StartingVpn;
        SIZE_T EndingVpn;
    } MMADDRESS_NODE, *PMMADDRESS_NODE; /* size: 0x0028 */ /* size: 0x0014 */
    static_assert(sizeof(MMADDRESS_NODE) == (sizeof(SIZE_T) == sizeof(UINT64) ? 0x0028 : 0x0014));


    typedef struct _MM_AVL_TABLE
    {
        struct _MMADDRESS_NODE BalancedRoot;
        struct /* bitfield */
        {
            SIZE_T DepthOfTree : 5; /* bit position: 0 */
            SIZE_T Unused : 3; /* bit position: 5 */
            SIZE_T NumberGenericTableElements : (sizeof(SIZE_T) * 8) - 8; /* bit position: 8 */
        }; /* bitfield */
        VOID* NodeHint;
        VOID* NodeFreeHint;
    } MM_AVL_TABLE, *PMM_AVL_TABLE; /* size: 0x0040 */ /* size: 0x0020 */
    static_assert(sizeof(MM_AVL_TABLE) == (sizeof(SIZE_T) == sizeof(UINT64) ? 0x0040 : 0x0020));


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
        UINT32 RepurposeCount;
        UINT32 Spare[sizeof(SIZE_T) / sizeof(UINT32)];
        struct _MMSUPPORT_FLAGS Flags;
    } MMSUPPORT, *PMMSUPPORT; /* size: 0x0088 */ /* size: 0x006c */
    static_assert(sizeof(MMSUPPORT) == (sizeof(SIZE_T) == sizeof(UINT64) ? 0x0088 : 0x006c));

}
