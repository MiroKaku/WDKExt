#pragma once


/*
 * PDB file: \Nt-Crucial-Modules\Ntoskrnl\6.1.7600.17795\
 * Dumped by pdbex tool v0.4, by wbenny
 */


namespace wdk::build_7600
{

    typedef struct _HANDLE_TABLE_ENTRY_INFO
    {
        UINT32 AuditMask;
    } HANDLE_TABLE_ENTRY_INFO, *PHANDLE_TABLE_ENTRY_INFO; /* size: 0x0004 */


    typedef struct _HANDLE_TABLE_ENTRY
    {
        union
        {
            VOID* Object;
            UINT32 ObAttributes;
            struct _HANDLE_TABLE_ENTRY_INFO* InfoTable;
            SIZE_T Value;
        }; /* size: 0x0008 */ /* size: 0x0004 */
        union
        {
            UINT32 GrantedAccess;
            struct
            {
                UINT16 GrantedAccessIndex;
                UINT16 CreatorBackTraceIndex;
            }; /* size: 0x0004 */
            UINT32 NextFreeTableEntry;
        }; /* size: 0x0004 */
    } HANDLE_TABLE_ENTRY, *PHANDLE_TABLE_ENTRY; /* size: 0x0010 */ /* size: 0x0008 */
    static_assert(sizeof(HANDLE_TABLE_ENTRY) == (sizeof(SIZE_T) == sizeof(UINT64) ? 0x0010 : 0x0008));


    typedef struct _HANDLE_TABLE
    {
        SIZE_T TableCode;
        struct _EPROCESS* QuotaProcess;
        VOID* UniqueProcessId;
        struct _EX_PUSH_LOCK HandleLock;
        struct _LIST_ENTRY HandleTableList;
        struct _EX_PUSH_LOCK HandleContentionEvent;
        struct _HANDLE_TRACE_DEBUG_INFO* DebugInfo;
        INT32 ExtraInfoPages;
        union
        {
            UINT32 Flags;
            UINT8 StrictFIFO : 1; /* bit position: 0 */
        }; /* size: 0x0004 */
        UINT32 FirstFreeHandle;
        struct _HANDLE_TABLE_ENTRY* LastFreeHandleEntry;
        UINT32 HandleCount;
        UINT32 NextHandleNeedingPool;
        UINT32 HandleCountHighWatermark;
    } HANDLE_TABLE, *PHANDLE_TABLE; /* size: 0x0068 */ /* size: 0x003c */
    static_assert(sizeof(HANDLE_TABLE) == (sizeof(SIZE_T) == sizeof(UINT64) ? 0x0068 : 0x003c));

}
