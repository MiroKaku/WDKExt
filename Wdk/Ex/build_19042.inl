#pragma once


/*
 * PDB file: \Nt-Crucial-Modules\Ntoskrnl\10.0.18362.1\
 * Dumped by pdbex tool v0.4, by wbenny
 */


namespace wdk::build_19042
{

    SameDefine$(build_19041, EXHANDLE);
    SameDefine$(build_19041, HANDLE_TABLE_ENTRY);

    typedef struct _HANDLE_TABLE_FREE_LIST
    {
        struct _EX_PUSH_LOCK FreeListLock;
        struct _HANDLE_TABLE_ENTRY* FirstFreeHandleEntry;
        struct _HANDLE_TABLE_ENTRY* LastFreeHandleEntry;
        INT32 HandleCount;
        UINT32 HighWaterMark;
#ifdef _WIN64
        UINT32 Reserved[8];
#else
        UINT32 Reserved[11];
#endif
    } HANDLE_TABLE_FREE_LIST, * PHANDLE_TABLE_FREE_LIST; /* size: 0x0040 */
    static_assert(sizeof(HANDLE_TABLE_FREE_LIST) == 0x0040);

    typedef struct _HANDLE_TABLE
    {
        UINT32 NextHandleNeedingPool;
        INT32 ExtraInfoPages;
        volatile SIZE_T TableCode;
        struct _EPROCESS* QuotaProcess;
        struct _LIST_ENTRY HandleTableList;
        UINT32 UniqueProcessId;
        union
        {
            UINT32 Flags;
            struct /* bitfield */
            {
                UINT8 StrictFIFO : 1; /* bit position: 0 */
                UINT8 EnableHandleExceptions : 1; /* bit position: 1 */
                UINT8 Rundown : 1; /* bit position: 2 */
                UINT8 Duplicated : 1; /* bit position: 3 */
                UINT8 RaiseUMExceptionOnInvalidHandleClose : 1; /* bit position: 4 */
            }; /* bitfield */
        }; /* size: 0x0004 */
        struct _EX_PUSH_LOCK HandleContentionEvent;
        struct _EX_PUSH_LOCK HandleTableLock;
#if _X86_
        INT32 __PADDING__0[6];
#endif
        union
        {
            struct _HANDLE_TABLE_FREE_LIST FreeLists[1];
            struct
            {
                enum : UINT32
                {
                    ActualEntrySizeX86 = 20,
                    ActualEntrySizeX64 = 32,
                    ActualEntrySize = sizeof(SIZE_T) == sizeof(UINT64) ? ActualEntrySizeX64 : ActualEntrySizeX86
                };

                UINT8 ActualEntry[ActualEntrySize];
                struct _HANDLE_TRACE_DEBUG_INFO* DebugInfo;

#if _X86_
                INT32 __PADDING__1[10];
#endif
            };
        };
    } HANDLE_TABLE, * PHANDLE_TABLE; /* size: 0x0080 */
    static_assert(sizeof(HANDLE_TABLE) == 0x0080);

}
