#pragma once
#include "MmStruct.inl"
#include "KeStruct.inl"
#include "TsStruct.inl"


namespace wdk
{

    constexpr auto WOW64_SYSTEM_DIRECTORY   = "SysWOW64";
    constexpr auto WOW64_SYSTEM_DIRECTORY_U = L"SysWOW64";
    constexpr auto WOW64_X86_TAG            = " (x86)";
    constexpr auto WOW64_X86_TAG_U          = L" (x86)";


    enum PsAccessMask : ACCESS_MASK
    {
        ProcessTerminate        = 0x0001,
        ProcessCreateThread     = 0x0002,
        ProcessSetSessionId     = 0x0004,
        ProcessVmOperation      = 0x0008,
        ProcessVmRead           = 0x0010,
        ProcessVmWrite          = 0x0020,
        ProcessDuplicateHandle  = 0x0040,
        ProcessCreateProcess    = 0x0080,
        ProcessSetQuota         = 0x0100,
        ProcessSetInformation   = 0x0200,
        ProcessQueryInformation = 0x0400,
        ProcessSuspendResume    = 0x0800,
        ProcessSetPort          = 0x0800,
        ProcessQueryLimitedInformation = 0x1000,
        ProcessAllAccess        = (StandardRightsRequired | Synchronize | 0xFFFF)
    };


    enum JobAccessMask : ACCESS_MASK
    {
        JobObjectAssignProcess          = 0x0001,
        JobObjectSetAttributes          = 0x0002,
        JobObjectQuery                  = 0x0004,
        JobObjectTerminate              = 0x0008,
        JobObjectSetSecurityAttribute   = 0x0010,
        JobObjectAllAccess = (StandardRightsRequired | Synchronize | 0x1F)
    };

    
    typedef enum _PS_PROTECTED_TYPE : UINT8
    {
        PsProtectedTypeNone,
        PsProtectedTypeProtectedLight,
        PsProtectedTypeProtected,
        PsProtectedTypeMax
    } PS_PROTECTED_TYPE;

    typedef enum _PS_PROTECTED_SIGNER : UINT8
    {
        PsProtectedSignerNone,
        PsProtectedSignerAuthenticode,
        PsProtectedSignerCodeGen,
        PsProtectedSignerAntimalware,
        PsProtectedSignerLsa,
        PsProtectedSignerWindows,
        PsProtectedSignerWinTcb,
        PsProtectedSignerWinSystem,
        PsProtectedSignerApp,
        PsProtectedSignerMax
    } PS_PROTECTED_SIGNER;

    enum PsProtectedMask : UINT8
    {
        PsProtectedSignerMask   = 0xFF,
        PsProtectedAuditMask    = 0x08,
        PsProtectedTypeMask     = 0x07,
    };

    typedef struct _PS_PROTECTION
    {
        union
        {
            UINT8 Level;
            struct
            {
                UINT8 Type  : 3;
                UINT8 Audit : 1;
                UINT8 Signer: 4;
            };
        };
    } PS_PROTECTION, *PPS_PROTECTION;
       

    typedef union _KEXECUTE_OPTIONS
    {
        union
        {
            struct
            {
                UINT8 ExecuteDisable : 1; /* bit position: 0 */
                UINT8 ExecuteEnable : 1; /* bit position: 1 */
                UINT8 DisableThunkEmulation : 1; /* bit position: 2 */
                UINT8 Permanent : 1; /* bit position: 3 */
                UINT8 ExecuteDispatchEnable : 1; /* bit position: 4 */
                UINT8 ImageDispatchEnable : 1; /* bit position: 5 */
                UINT8 DisableExceptionChainValidation : 1; /* bit position: 6 */
                UINT8 Spare : 1; /* bit position: 7 */
            };
            volatile UINT8 ExecuteOptions;
            UINT8 ExecuteOptionsNV;
        }; /* size: 0x0001 */
    } KEXECUTE_OPTIONS, *PKEXECUTE_OPTIONS; /* size: 0x0001 */
    static_assert(sizeof(KEXECUTE_OPTIONS) == 0x0001);


    typedef union _KSTACK_COUNT
    {
        union
        {
            INT32 Value;
            struct
            {
                UINT32 State : 3; /* bit position: 0 */
                UINT32 StackCount : 29; /* bit position: 3 */
            };
        };
    } KSTACK_COUNT, *PKSTACK_COUNT; /* size: 0x0004 */
    static_assert(sizeof(KSTACK_COUNT) == 0x0004);


    typedef struct _KGDTENTRY
    {
        UINT16 LimitLow;
        UINT16 BaseLow;
        union
        {
            union
            {
                struct
                {
                    UINT8 BaseMid;
                    UINT8 Flags1;
                    UINT8 Flags2;
                    UINT8 BaseHi;
                } /* size: 0x0004 */ Bytes;
                struct
                {
                    struct
                    {
                        UINT32 BaseMid : 8; /* bit position: 0 */
                        UINT32 Type : 5; /* bit position: 8 */
                        UINT32 Dpl : 2; /* bit position: 13 */
                        UINT32 Pres : 1; /* bit position: 15 */
                        UINT32 LimitHi : 4; /* bit position: 16 */
                        UINT32 Sys : 1; /* bit position: 20 */
                        UINT32 Reserved_0 : 1; /* bit position: 21 */
                        UINT32 Default_Big : 1; /* bit position: 22 */
                        UINT32 Granularity : 1; /* bit position: 23 */
                        UINT32 BaseHi : 8; /* bit position: 24 */
                    };
                } /* size: 0x0004 */ Bits;
            }; /* size: 0x0004 */
        } /* size: 0x0004 */ HighWord;
    } KGDTENTRY, *PKGDTENTRY; /* size: 0x0008 */
    static_assert(sizeof(KGDTENTRY) == 0x0008);


    typedef union _KGDTENTRY64
    {
        union
        {
            struct
            {
                UINT16 LimitLow;
                UINT16 BaseLow;
                union
                {
                    struct
                    {
                        UINT8 BaseMiddle;
                        UINT8 Flags1;
                        UINT8 Flags2;
                        UINT8 BaseHigh;
                    } /* size: 0x0004 */ Bytes;
                    struct
                    {
                        struct
                        {
                            struct
                            {
                                UINT32 BaseMiddle : 8; /* bit position: 0 */
                                UINT32 Type : 5; /* bit position: 8 */
                                UINT32 Dpl : 2; /* bit position: 13 */
                                UINT32 Present : 1; /* bit position: 15 */
                                UINT32 LimitHigh : 4; /* bit position: 16 */
                                UINT32 System : 1; /* bit position: 20 */
                                UINT32 LongMode : 1; /* bit position: 21 */
                                UINT32 DefaultBig : 1; /* bit position: 22 */
                                UINT32 Granularity : 1; /* bit position: 23 */
                                UINT32 BaseHigh : 8; /* bit position: 24 */
                            };
                        } /* size: 0x0004 */ Bits;
                        UINT32 BaseUpper;
                        UINT32 MustBeZero;
                    }; /* size: 0x000c */
                }; /* size: 0x000c */
            }; /* size: 0x0010 */
            struct
            {
                INT64 DataLow;
                INT64 DataHigh;
            }; /* size: 0x0010 */
        }; /* size: 0x0010 */
    } KGDTENTRY64, *PKGDTENTRY64; /* size: 0x0010 */
    static_assert(sizeof(KGDTENTRY64) == 0x0010);


    typedef struct _KIDTENTRY
    {
        UINT16 Offset;
        UINT16 Selector;
        UINT16 Access;
        UINT16 ExtendedOffset;
    } KIDTENTRY, *PKIDTENTRY; /* size: 0x0008 */
    static_assert(sizeof(KIDTENTRY) == 0x0008);


    typedef union _KIDTENTRY64
    {
        union
        {
            struct
            {
                UINT16 OffsetLow;
                UINT16 Selector;
                struct /* bitfield */
                {
                    UINT16 IstIndex : 3; /* bit position: 0 */
                    UINT16 Reserved0 : 5; /* bit position: 3 */
                    UINT16 Type : 5; /* bit position: 8 */
                    UINT16 Dpl : 2; /* bit position: 13 */
                    UINT16 Present : 1; /* bit position: 15 */
                }; /* bitfield */
                UINT16 OffsetMiddle;
                UINT32 OffsetHigh;
                UINT32 Reserved1;
            }; /* size: 0x0010 */
            UINT64 Alignment;
        }; /* size: 0x0010 */
    } KIDTENTRY64, *PKIDTENTRY64; /* size: 0x0010 */
    static_assert(sizeof(KIDTENTRY64) == 0x0010);


    typedef struct _SE_AUDIT_PROCESS_CREATION_INFO
    {
        struct _OBJECT_NAME_INFORMATION* ImageFileName;
    } SE_AUDIT_PROCESS_CREATION_INFO, *PSE_AUDIT_PROCESS_CREATION_INFO;


    typedef struct _ALPC_PROCESS_CONTEXT
    {
        struct _EX_PUSH_LOCK Lock;
        struct _LIST_ENTRY ViewListHead;
        volatile SIZE_T PagedPoolQuotaCache;
    } ALPC_PROCESS_CONTEXT, *PALPC_PROCESS_CONTEXT; /* size: 0x0020 */ /* size: 0x0010 */
    static_assert(sizeof(ALPC_PROCESS_CONTEXT) == (sizeof(SIZE_T) == sizeof(UINT64) ? 0x0020 : 0x0010));

}

#include "Ps\build_7600.inl"
#include "Ps\build_7601.inl"
#include "Ps\build_9200.inl"
#include "Ps\build_9600.inl"
#include "Ps\build_10240.inl"
#include "Ps\build_10586.inl"
#include "Ps\build_14393.inl"
#include "Ps\build_15063.inl"
#include "Ps\build_16299.inl"
#include "Ps\build_17134.inl"
#include "Ps\build_17763.inl"
