#pragma once


/*
 * PDB file: \Nt-Crucial-Modules\Ntoskrnl\6.3.9600.19038\
 * Dumped by pdbex tool v0.4, by wbenny
 */


namespace wdk::build_9600
{

    typedef union _KWAIT_STATUS_REGISTER
    {
        union
        {
            UINT8 Flags;
            struct /* bitfield */
            {
                UINT8 State : 3; /* bit position: 0 */
                UINT8 Affinity : 1; /* bit position: 3 */
                UINT8 Priority : 1; /* bit position: 4 */
                UINT8 Apc : 1; /* bit position: 5 */
                UINT8 UserApc : 1; /* bit position: 6 */
                UINT8 Alert : 1; /* bit position: 7 */
            }; /* bitfield */
        }; /* size: 0x0001 */
    } KWAIT_STATUS_REGISTER, *PKWAIT_STATUS_REGISTER; /* size: 0x0001 */
    

    typedef struct _KLOCK_ENTRY_LOCK_STATE
    {
        union
        {
            struct /* bitfield */
            {
                SIZE_T Waiting : 1; /* bit position: 0 */
                SIZE_T Busy : 1; /* bit position: 1 */
                SIZE_T Spare : sizeof(SIZE_T) * 8 - 3; /* bit position: 2 */
                SIZE_T InTree : 1; /* bit position: 63 */ /* bit position: 31 */
            }; /* bitfield */
            VOID* LockState;
        };
        union
        {
            VOID* SessionState;
            struct
            {
                UINT32 SessionId;
#ifdef _WIN64
                UINT32 SessionPad;
#endif
            };
        };
    } KLOCK_ENTRY_LOCK_STATE, *PKLOCK_ENTRY_LOCK_STATE; /* size: 0x0010 */ /* size: 0x0008 */
    static_assert(sizeof(KLOCK_ENTRY_LOCK_STATE) == (sizeof(SIZE_T) == sizeof(UINT64) ? 0x0010 : 0x0008));


    typedef struct _KLOCK_ENTRY
    {
        union
        {
            struct _RTL_BALANCED_NODE TreeNode;
            struct _SINGLE_LIST_ENTRY FreeListEntry;
        };
        union
        {
            VOID* ThreadUnsafe;
            struct
            {
                volatile UINT8 HeadNodeByte;
                UINT8 Reserved1[sizeof(SIZE_T) - 2];
                volatile UINT8 AcquiredByte;
            };
        };
        union
        {
            struct _KLOCK_ENTRY_LOCK_STATE LockState;
            VOID* volatile LockUnsafe;
            struct
            {
                volatile UINT8 WaitingAndBusyByte;
                UINT8 Reserved[sizeof(SIZE_T) - 2];
                volatile UINT8 InTreeByte;
                union
                {
                    VOID* SessionState;
                    struct
                    {
                        UINT32 SessionId;
#ifdef _WIN64
                        UINT32 SessionPad;
#endif
                    };
                };
            };
        };
        union
        {
            struct
            {
                struct _RTL_RB_TREE OwnerTree;
                struct _RTL_RB_TREE WaiterTree;
            };
            CHAR CpuPriorityKey;
        };
        SIZE_T EntryLock;
        union
        {
            UINT16 AllBoosts;
            struct /* bitfield */
            {
                UINT16 IoBoost : 1; /* bit position: 0 */
                UINT16 CpuBoostsBitmap : 15; /* bit position: 1 */
            }; /* bitfield */
        }; /* size: 0x0002 */
#ifdef _WIN64
        UINT16 IoNormalPriorityWaiterCount;
        struct /* bitfield */
        {
            UINT8 IoPriorityBit : 1; /* bit position: 0 */
            UINT8 AbSpare : 7; /* bit position: 1 */
        }; /* bitfield */
        UINT8 SparePad[3];
#else
        struct /* bitfield */
        {
            UINT16 IoNormalPriorityWaiterCount : 15; /* bit position: 0 */
            UINT16 IoPriorityBit : 1; /* bit position: 15 */
        }; /* bitfield */
#endif
    } KLOCK_ENTRY, *PKLOCK_ENTRY; /* size: 0x0060 */ /* size: 0x0030 */
    static_assert(sizeof(KLOCK_ENTRY) == (sizeof(SIZE_T) == sizeof(UINT64) ? 0x0060 : 0x0030));


}
