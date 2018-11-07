#pragma once


/*
 * PDB file: \Nt-Crucial-Modules\Ntoskrnl\6.3.9600.19038\
 * Dumped by pdbex tool v0.4, by wbenny
 */


namespace wdk::build_9600
{

    SameDefine$(build_9200, EXHANDLE);
    SameDefine$(build_9200, HANDLE_TABLE_FREE_LIST);
    SameDefine$(build_9200, HANDLE_TABLE);



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
                SIZE_T RefCnt : 16; /* bit position: 1 */
                SIZE_T Attributes : 3; /* bit position: 20 */
                SIZE_T ObjectPointerBits : sizeof(SIZE_T) * 8 - 20; /* bit position: 20 */
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
            EXHANDLE LeafHandleValue;
            struct
            {
                struct /* bitfield */
                {
                    UINT32 GrantedAccessBits : 25; /* bit position: 0 */
#ifdef _X86_
                    UINT32 ProtectFromClose : 1; /* bit position: 25 */
#endif
                    UINT32 NoRightsUpgrade : 1; /* bit position: 25/26 */
#ifdef _WIN64
                    UINT32 Spare : 6; /* bit position: 26 */
#else
                    UINT32 RefCnt : 5; /* bit position: 27 */
#endif
                }; /* bitfield */
#ifdef _WIN64
                UINT32 TypeInfo;
#endif
            };
        };
    } HANDLE_TABLE_ENTRY, *PHANDLE_TABLE_ENTRY; /* size: 0x0010 */ /* size: 0x0008 */
    static_assert(sizeof(HANDLE_TABLE_ENTRY) == (sizeof(SIZE_T) == sizeof(UINT64) ? 0x0010 : 0x0008));

}
