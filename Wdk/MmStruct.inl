#pragma once


namespace wdk
{

#pragma region PTE
    typedef struct _HARDWARE_PTE
    {
        enum : UINT64 { HARDWARE_PTE_WORKING_SET_BITS = 11 };

        UINT64 Valid : 1;
        UINT64 Write : 1;                // UP version
        UINT64 Owner : 1;
        UINT64 WriteThrough : 1;
        UINT64 CacheDisable : 1;
        UINT64 Accessed : 1;
        UINT64 Dirty : 1;
        UINT64 LargePage : 1;
        UINT64 Global : 1;
        UINT64 CopyOnWrite : 1;          // software field
        UINT64 Prototype : 1;            // software field
        UINT64 reserved0 : 1;            // software field
        UINT64 PageFrameNumber : 36;
        UINT64 reserved1 : 4;
        UINT64 SoftwareWsIndex : HARDWARE_PTE_WORKING_SET_BITS;
        UINT64 NoExecute : 1;
    } HARDWARE_PTE, *PHARDWARE_PTE;
    static_assert(sizeof(HARDWARE_PTE) == 8, "sizeof(HARDWARE_PTE) != 8");
#pragma endregion

    
#pragma region Page
    enum PageAccessMask : ACCESS_MASK
    {
        PageNoAccess                = 0x00000001,
        PageReadOnly                = 0x00000002,
        PageReadWrite               = 0x00000004,
        PageWriteCopy               = 0x00000008,

        PageExecute                 = 0x00000010,
        PageExecuteRead             = 0x00000020,
        PageExecuteReadWrite        = 0x00000040,
        PageExecuteWriteCopy        = 0x00000080,

        PageGuard                   = 0x00000100,
        PageNoCache                 = 0x00000200,
        PageWriteCombine            = 0x00000400,

        PageEnclaveDecommit         = 0x10000000,
        PageEnclaveUnvalidated      = 0x20000000,
        PageTargetsNoUpdate         = 0x40000000,
        PageTargetsInvalid          = 0x40000000,
        PageEnclaveThreadControl    = 0x80000000,
        PageRevertToFileMap         = 0x80000000,
    };

    
    enum SecType : UINT32
    {
        SecFile             = 0x00800000,
        SecImage            = 0x01000000,
        SecProtectedImage   = 0x02000000,
        SecReserve          = 0x04000000,
        SecCommit           = 0x08000000,
        SecNoCache          = 0x10000000,
        SecWriteCombine     = 0x40000000,
        SecLargePages       = 0x80000000,
        SecImageNoExecute   = (SecImage | SecNoCache),
    };


    enum MemType : UINT32
    {
        MemCommit               = 0x00001000,
        MemReserve              = 0x00002000,
        MemDecommit             = 0x00004000,
        MemRelease              = 0x00008000,

        MemFree                 = 0x00010000,
        MemPrivate              = 0x00020000,
        MemMapped               = 0x00040000,
        MemReset                = 0x00080000,

        MemTopDown              = 0x00100000,
        MemWriteWatch           = 0x00200000,
        MemPhysical             = 0x00400000,
        MemRotate               = 0x00800000,
        MemDifferentImageBaseOk = 0x00800000,

        MemResetUndo            = 0x01000000,
        
        MemLargePages           = 0x20000000,
        Mem4MBPages             = 0x80000000,
        Mem64KPages             = (MemLargePages | MemPhysical),

        MemImage                = SecImage,
    };


    __declspec(selectany) ULONG MmProtectToValue[32] =
    {
        PAGE_NOACCESS,
        PAGE_READONLY,
        PAGE_EXECUTE,
        PAGE_EXECUTE_READ,
        PAGE_READWRITE,
        PAGE_WRITECOPY,
        PAGE_EXECUTE_READWRITE,
        PAGE_EXECUTE_WRITECOPY,
        PAGE_NOACCESS,
        PAGE_NOCACHE | PAGE_READONLY,
        PAGE_NOCACHE | PAGE_EXECUTE,
        PAGE_NOCACHE | PAGE_EXECUTE_READ,
        PAGE_NOCACHE | PAGE_READWRITE,
        PAGE_NOCACHE | PAGE_WRITECOPY,
        PAGE_NOCACHE | PAGE_EXECUTE_READWRITE,
        PAGE_NOCACHE | PAGE_EXECUTE_WRITECOPY,
        PAGE_NOACCESS,
        PAGE_GUARD | PAGE_READONLY,
        PAGE_GUARD | PAGE_EXECUTE,
        PAGE_GUARD | PAGE_EXECUTE_READ,
        PAGE_GUARD | PAGE_READWRITE,
        PAGE_GUARD | PAGE_WRITECOPY,
        PAGE_GUARD | PAGE_EXECUTE_READWRITE,
        PAGE_GUARD | PAGE_EXECUTE_WRITECOPY,
        PAGE_NOACCESS,
        PAGE_WRITECOMBINE | PAGE_READONLY,
        PAGE_WRITECOMBINE | PAGE_EXECUTE,
        PAGE_WRITECOMBINE | PAGE_EXECUTE_READ,
        PAGE_WRITECOMBINE | PAGE_READWRITE,
        PAGE_WRITECOMBINE | PAGE_WRITECOPY,
        PAGE_WRITECOMBINE | PAGE_EXECUTE_READWRITE,
        PAGE_WRITECOMBINE | PAGE_EXECUTE_WRITECOPY
    };
#pragma endregion


#pragma region Mm Flags
    typedef struct _MMSUPPORT_FLAGS
    {
        union
        {
            struct
            {
                struct
                {
                    UINT8 WorkingSetType : 3; /* bit position: 0 */
                    UINT8 Reserved0 : 3; /* bit position: 3 */
                    UINT8 MaximumWorkingSetHard : 1; /* bit position: 6 */
                    UINT8 MinimumWorkingSetHard : 1; /* bit position: 7 */
                };
                struct
                {
                    UINT8 SessionMaster : 1; /* bit position: 0 */
                    UINT8 TrimmerState : 2; /* bit position: 1 */
                    UINT8 Reserved : 1; /* bit position: 3 */
                    UINT8 PageStealers : 4; /* bit position: 4 */
                };
            }; /* size: 0x0002 */
            UINT16 u1;
        }; /* size: 0x0002 */
        UINT8 MemoryPriority;
        union
        {
            struct
            {
                UINT8 WsleDeleted : 1; /* bit position: 0 */
                UINT8 SvmEnabled : 1; /* bit position: 1 */
                UINT8 ForceAge : 1; /* bit position: 2 */
                UINT8 ForceTrim : 1; /* bit position: 3 */
                UINT8 NewMaximum : 1; /* bit position: 4 */
                UINT8 CommitReleaseState : 2; /* bit position: 5 */
            };
            UINT8 u2;
        }; /* size: 0x0001 */
    } MMSUPPORT_FLAGS, *PMMSUPPORT_FLAGS; /* size: 0x0004 */
    static_assert(sizeof(MMSUPPORT_FLAGS) == 0x0004);
#pragma endregion



}

#include "Mm\build_7600.inl"
#include "Mm\build_7601.inl"
#include "Mm\build_9200.inl"
#include "Mm\build_9600.inl"
#include "Mm\build_10240.inl"
#include "Mm\build_10586.inl"
#include "Mm\build_14393.inl"
#include "Mm\build_15063.inl"
#include "Mm\build_16299.inl"
#include "Mm\build_17134.inl"
#include "Mm\build_17763.inl"
