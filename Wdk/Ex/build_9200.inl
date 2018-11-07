#pragma once


/*
 * PDB file: \Nt-Crucial-Modules\Ntoskrnl\6.2.9200.17581\
 * Dumped by pdbex tool v0.4, by wbenny
 */


namespace wdk::build_9200
{

    SameDefine$(build_7601, HANDLE_TABLE_ENTRY_INFO);


    typedef struct _EXHANDLE
    {
        union
        {
            struct /* bitfield */
            {
                UINT32 TagBits : 2; /* bit position: 0 */
                UINT32 Index : 30; /* bit position: 2 */
            }; /* bitfield */
            VOID* GenericHandleOverlay;
            SIZE_T Value;
        };
    } EXHANDLE, *PEXHANDLE;  /* size: 0x0008 */ /* size: 0x0004 */
    static_assert(sizeof(EXHANDLE) == (sizeof(SIZE_T) == sizeof(UINT64) ? 0x0008 : 0x0004));


    typedef struct _HANDLE_TABLE_ENTRY
    {
        union
        {
            volatile SSIZE_T VolatileLowValue;
            SSIZE_T LowValue;
            struct _HANDLE_TABLE_ENTRY_INFO* volatile InfoTable;
            struct /* bitfield */
            {
                SIZE_T Unlocked : 1; /* bit position: 0 */
#ifdef _WIN64
                SIZE_T RefCnt : 19; /* bit position: 1 */
                SIZE_T Attributes : 3; /* bit position: 20 */
                SIZE_T ObjectPointerBits : sizeof(SIZE_T) * 8 - 23; /* bit position: 23 */
#else
                SIZE_T Attributes : 2; /* bit position: 1 */
                SIZE_T ObjectPointerBits : sizeof(SIZE_T) * 8 - 3; /* bit position: 3 */
#endif
            }; /* bitfield */
        };
        union
        {
            SSIZE_T HighValue;
            struct _HANDLE_TABLE_ENTRY* NextFreeHandleEntry;
            struct _EXHANDLE LeafHandleValue;
            struct
            {
                struct /* bitfield */
                {
                    UINT32 GrantedAccessBits : 25; /* bit position: 0 */
#ifdef _WIN64
                    UINT32 Spare : 7; /* bit position: 25 */
#else
                    UINT32 ProtectFromClose : 1; /* bit position: 25 */
                    UINT32 RefCnt : 6; /* bit position: 26 */
#endif
                }; /* bitfield */
#ifdef _WIN64
                UINT32 TypeInfo;
#endif
            };
        };
    } HANDLE_TABLE_ENTRY, *PHANDLE_TABLE_ENTRY; /* size: 0x0010 */ /* size: 0x0008 */
    static_assert(sizeof(HANDLE_TABLE_ENTRY) == (sizeof(SIZE_T) == sizeof(UINT64) ? 0x0010 : 0x0008));


    typedef struct _HANDLE_TABLE_FREE_LIST
    {
        struct _EX_PUSH_LOCK FreeListLock;
        struct _HANDLE_TABLE_ENTRY* FirstFreeHandleEntry;
        struct _HANDLE_TABLE_ENTRY* LastFreeHandleEntry;
        INT32 HandleCount;
        UINT32 HighWaterMark;
        UINT32 Reserved[8];
    } HANDLE_TABLE_FREE_LIST, *PHANDLE_TABLE_FREE_LIST; /* size: 0x0040 */ /* size: 0x0034 */
    static_assert(sizeof(HANDLE_TABLE_FREE_LIST) == (sizeof(SIZE_T) == sizeof(UINT64) ? 0x0040 : 0x0034));


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
            }; /* bitfield */
        }; /* size: 0x0004 */
        struct _EX_PUSH_LOCK HandleContentionEvent;
        struct _EX_PUSH_LOCK HandleTableLock;
        union
        {
            struct _HANDLE_TABLE_FREE_LIST FreeLists[1];
            struct
            {
                enum : UINT32
                {
                    ActualEntrySizeX86  = 20,
                    ActualEntrySizeX64  = 32,
                    ActualEntrySize     = sizeof(SIZE_T) == sizeof(UINT64) ? ActualEntrySizeX64 : ActualEntrySizeX86
                };

                UINT8 ActualEntry[ActualEntrySize];
                struct _HANDLE_TRACE_DEBUG_INFO* DebugInfo;
            };
        };
    } HANDLE_TABLE, *PHANDLE_TABLE; /* size: 0x0080 */ /* size: 0x005c */
    static_assert(sizeof(HANDLE_TABLE) == (sizeof(SIZE_T) == sizeof(UINT64) ? 0x0080 : 0x005c));

}
