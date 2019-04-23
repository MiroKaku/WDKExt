#pragma once


/*
 * PDB file: \Nt-Crucial-Modules\Ntoskrnl\10.0.18362.1\
 * Dumped by pdbex tool v0.4, by wbenny
 */


namespace wdk::build_18362
{

    SameDefine$(build_17763, MMSUPPORT_INSTANCE);

    typedef struct _MMSUPPORT_SHARED
    {
        volatile INT32 WorkingSetLock;
        INT32 GoodCitizenWaiting;
        SIZE_T ReleasedCommitDebt;
        SIZE_T ResetPagesRepurposedCount;
        VOID* WsSwapSupport;
        VOID* CommitReleaseContext;
        VOID* AccessLog;
        volatile SIZE_T ChargedWslePages;
        SIZE_T ActualWslePages;
#ifdef _X86_
        INT32 __Padding_0[7];
#endif
        SIZE_T WorkingSetCoreLock;
        VOID* ShadowMapping;
#ifdef _X86_
        INT32 __Padding_1[14];
#else
        INT32 __Padding_1[12];
#endif
    } MMSUPPORT_SHARED, * PMMSUPPORT_SHARED; /* size: 0x0080 */ /* size: 0x002c */
    static_assert(sizeof(MMSUPPORT_SHARED) == (sizeof(SIZE_T) == sizeof(UINT64) ? 0x0080 : 0x0080));

    typedef struct _MMSUPPORT_FULL
    {
        struct _MMSUPPORT_INSTANCE Instance;
#ifdef _X86_
        INT32 __Padding_0[7];
#endif
        struct _MMSUPPORT_SHARED Shared;
    } MMSUPPORT_FULL, * PMMSUPPORT_FULL; /* size: 0x0140 */ /* size: 0x0090 */
    static_assert(sizeof(MMSUPPORT_FULL) == (sizeof(SIZE_T) == sizeof(UINT64) ? 0x0140 : 0x00100));


}
