#pragma once


/*
 * PDB file: \Nt-Crucial-Modules\Ntoskrnl\10.0.10240.17443\
 * Dumped by pdbex tool v0.4, by wbenny
 */


namespace wdk::build_10240
{

    SameDefine$(build_9600, EXHANDLE);
    SameDefine$(build_9600, HANDLE_TABLE_FREE_LIST);


    typedef struct _HANDLE_TABLE_ENTRY
    {
        union
        {
            volatile SSIZE_T VolatileLowValue;
            SSIZE_T LowValue;
            struct
            {
                struct _HANDLE_TABLE_ENTRY_INFO* volatile InfoTable;
                union
                {
                    SSIZE_T HighValue;
                    struct _HANDLE_TABLE_ENTRY* NextFreeHandleEntry;
                    struct _EXHANDLE LeafHandleValue;
                };
            };
#ifdef _WIN64
            INT64 RefCountField;
#endif
            struct
            {
                struct /* bitfield */
                {
                    SIZE_T Unlocked : 1; /* bit position: 0 */
#ifdef _WIN64
                    SIZE_T RefCnt : 16; /* bit position: 1 */
                    SIZE_T Attributes : 3; /* bit position: 17 */
                    SIZE_T ObjectPointerBits : 44; /* bit position: 20 */
#else
                    SIZE_T Attributes : 2; /* bit position: 1 */
                    SIZE_T ObjectPointerBits : 29; /* bit position: 3 */
#endif
                }; /* bitfield */
#ifdef _WIN64
                struct /* bitfield */
                {
                    UINT32 GrantedAccessBits : 25; /* bit position: 0 */
                    UINT32 NoRightsUpgrade : 1; /* bit position: 25 */
                    UINT32 Spare1 : 6; /* bit position: 26 */
                }; /* bitfield */
                UINT32 Spare2;
#else
                union
                {
                    INT32 RefCountField;
                    struct /* bitfield */
                    {
                        UINT32 GrantedAccessBits : 25; /* bit position: 0 */
                        UINT32 ProtectFromClose : 1; /* bit position: 25 */
                        UINT32 NoRightsUpgrade : 1; /* bit position: 26 */
                        UINT32 RefCnt : 5; /* bit position: 27 */
                    }; /* bitfield */
                }; /* size: 0x0004 */
#endif
            };
        };
    } HANDLE_TABLE_ENTRY, *PHANDLE_TABLE_ENTRY; /* size: 0x0010 */ /* size: 0x0008 */
    static_assert(sizeof(HANDLE_TABLE_ENTRY) == (sizeof(SIZE_T) == sizeof(UINT64) ? 0x0010 : 0x0008));


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
