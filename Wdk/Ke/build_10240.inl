#pragma once


/*
 * PDB file: \Nt-Crucial-Modules\Ntoskrnl\10.0.10240.17443\
 * Dumped by pdbex tool v0.4, by wbenny
 */


namespace wdk::build_10240
{

    SameDefine$(build_9600, KWAIT_STATUS_REGISTER);


    typedef struct _KLOCK_ENTRY_LOCK_STATE
    {
        union
        {
            struct /* bitfield */
            {
                SIZE_T CrossThreadReleasable : 1; /* bit position: 0 */
                SIZE_T Busy : 1; /* bit position: 1 */
                SIZE_T Reserved : sizeof(SIZE_T) * 8 - 3; /* bit position: 2 */
                SIZE_T InTree : 1; /* bit position: 31 */
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
            UINT32 EntryFlags;
            struct
            {
                UINT8 EntryOffset;
                union
                {
                    UINT8 ThreadLocalFlags;
                    struct
                    {
                        struct /* bitfield */
                        {
                            UINT8 WaitingBit : 1; /* bit position: 0 */
                            UINT8 Spare0 : 7; /* bit position: 1 */
                        }; /* bitfield */
                        union
                        {
                            UINT8 AcquiredByte;
                            struct
                            {
                                UINT8 AcquiredBit : 1; /* bit position: 0 */
                                union
                                {
                                    UINT8 CrossThreadFlags;
                                    struct /* bitfield */
                                    {
                                        UINT8 HeadNodeBit : 1; /* bit position: 0 */
                                        UINT8 IoPriorityBit : 1; /* bit position: 1 */
                                        UINT8 Spare1 : 6; /* bit position: 2 */
                                    }; /* bitfield */
                                }; /* size: 0x0001 */
                            }; /* size: 0x0002 */
                        }; /* size: 0x0002 */
                    }; /* size: 0x0003 */
                }; /* size: 0x0003 */
            }; /* size: 0x0004 */
            struct /* bitfield */
            {
                UINT32 StaticState : 8; /* bit position: 0 */
                UINT32 AllFlags : 24; /* bit position: 8 */
            }; /* bitfield */
        }; /* size: 0x0004 */
#ifdef _WIN64
        UINT32 SpareFlags;
#endif
        union
        {
            struct _KLOCK_ENTRY_LOCK_STATE LockState;
            VOID* volatile LockUnsafe;
            struct
            {
                volatile UINT8 CrossThreadReleasableAndBusyByte;
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
        UINT16 IoNormalPriorityWaiterCount;
#ifdef _WIN64
        UINT16 SparePad;
#endif
    } KLOCK_ENTRY, *PKLOCK_ENTRY; /* size: 0x0060 */ /* size: 0x0030 */
    static_assert(sizeof(KLOCK_ENTRY) == (sizeof(SIZE_T) == sizeof(UINT64) ? 0x0060 : 0x0030));


}
