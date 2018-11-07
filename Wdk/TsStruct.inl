#pragma once
#include "KeStruct.inl"


namespace wdk
{
    
    enum TsAccessMask : ACCESS_MASK
    {
        ThreadTerminate                 = 0x0001,
        ThreadSuspendResume             = 0x0002,
        ThreadAlert                     = 0x0004,
        ThreadGetContext                = 0x0008,
        ThreadSetContext                = 0x0010,
        ThreadSetInformation            = 0x0020,
        ThreadQueryInformation          = 0x0040,
        ThreadSetThreadToken            = 0x0080,
        ThreadImpersonate               = 0x0100,
        ThreadDirectImpersonation       = 0x0200,
        
        ThreadSetLimitedInformation     = 0x0400,
        ThreadQueryLimitedInformation   = 0x0800,
        ThreadResume                    = 0x1000,

        ThreadAllAccess = (STANDARD_RIGHTS_REQUIRED | SYNCHRONIZE | 0xFFFF)
    };


    enum : UINT32
    {
        MaximumContextExtension = 512,
    };

    enum Context32Flags : long
    {
        // i386
        CONTEXT_ARCH_I386           = 0x00010000L,

        CONTEXT32_CONTROL           = (CONTEXT_ARCH_I386 | 0x00000001L),
        CONTEXT32_INTEGER           = (CONTEXT_ARCH_I386 | 0x00000002L),
        CONTEXT32_SEGMENTS          = (CONTEXT_ARCH_I386 | 0x00000004L),
        CONTEXT32_FLOATING_POINT    = (CONTEXT_ARCH_I386 | 0x00000008L),
        CONTEXT32_DEBUG_REGISTERS   = (CONTEXT_ARCH_I386 | 0x00000010L),

        CONTEXT32_FULL      = (CONTEXT32_CONTROL | CONTEXT32_INTEGER | CONTEXT32_FLOATING_POINT),
        CONTEXT32_ALL       = (CONTEXT32_CONTROL | CONTEXT32_INTEGER | CONTEXT32_SEGMENTS | CONTEXT32_FLOATING_POINT | CONTEXT32_DEBUG_REGISTERS),

        CONTEXT32_XSTATE    = (CONTEXT_ARCH_I386 | 0x00000040L),
    };

    enum Context64Flags : long
    {
        // AMD64
        CONTEXT_ARCH_AMD64          = 0x00100000L,

        CONTEXT64_CONTROL           = (CONTEXT_ARCH_AMD64 | 0x00000001L),
        CONTEXT64_INTEGER           = (CONTEXT_ARCH_AMD64 | 0x00000002L),
        CONTEXT64_SEGMENTS          = (CONTEXT_ARCH_AMD64 | 0x00000004L),
        CONTEXT64_FLOATING_POINT    = (CONTEXT_ARCH_AMD64 | 0x00000008L),
        CONTEXT64_DEBUG_REGISTERS   = (CONTEXT_ARCH_AMD64 | 0x00000010L),

        CONTEXT64_FULL      = (CONTEXT64_CONTROL | CONTEXT64_INTEGER | CONTEXT64_FLOATING_POINT),
        CONTEXT64_ALL       = (CONTEXT64_CONTROL | CONTEXT64_INTEGER | CONTEXT64_SEGMENTS | CONTEXT64_FLOATING_POINT | CONTEXT64_DEBUG_REGISTERS),

        CONTEXT64_XSTATE    = (CONTEXT_ARCH_AMD64 | 0x00000040L),
    };

    struct DECLSPEC_ALIGN(16) XSAVE_FORMAT64
    {
        UINT16  ControlWord;
        UINT16  StatusWord;
        UINT8   TagWord;
        UINT8   Reserved1;
        UINT16  ErrorOpcode;
        UINT32  ErrorOffset;
        UINT16  ErrorSelector;
        UINT16  Reserved2;
        UINT32  DataOffset;
        UINT16  DataSelector;
        UINT16  Reserved3;
        UINT32  MxCsr;
        UINT32  MxCsr_Mask;
        M128A   FloatRegisters[8];
        M128A   XmmRegisters[16];
        UINT8   Reserved4[96];

    };
    using PXSAVE_FORMAT64   = XSAVE_FORMAT64 * ;
    using XMM_SAVE_AREA64   = XSAVE_FORMAT64;
    using PXMM_SAVE_AREA64  = XMM_SAVE_AREA64 * ;

    typedef struct DECLSPEC_ALIGN(16) CONTEXT64
    {
        //
        // Register parameter home addresses.
        //
        // N.B. These fields are for convience - they could be used to extend the
        //      context record in the future.
        //

        UINT64 P1Home;
        UINT64 P2Home;
        UINT64 P3Home;
        UINT64 P4Home;
        UINT64 P5Home;
        UINT64 P6Home;

        //
        // Control flags.
        //

        UINT32 ContextFlags;
        UINT32 MxCsr;

        //
        // Segment Registers and processor flags.
        //

        UINT16 SegCs;
        UINT16 SegDs;
        UINT16 SegEs;
        UINT16 SegFs;
        UINT16 SegGs;
        UINT16 SegSs;
        UINT32 EFlags;

        //
        // Debug registers
        //

        UINT64 Dr0;
        UINT64 Dr1;
        UINT64 Dr2;
        UINT64 Dr3;
        UINT64 Dr6;
        UINT64 Dr7;

        //
        // Integer registers.
        //

        UINT64 Rax;
        UINT64 Rcx;
        UINT64 Rdx;
        UINT64 Rbx;
        UINT64 Rsp;
        UINT64 Rbp;
        UINT64 Rsi;
        UINT64 Rdi;
        UINT64 R8;
        UINT64 R9;
        UINT64 R10;
        UINT64 R11;
        UINT64 R12;
        UINT64 R13;
        UINT64 R14;
        UINT64 R15;

        //
        // Program counter.
        //

        UINT64 Rip;

        //
        // Floating point state.
        //

        union
        {
            XMM_SAVE_AREA64 FltSave;
            struct
            {
                M128A Header[2];
                M128A Legacy[8];
                M128A Xmm0;
                M128A Xmm1;
                M128A Xmm2;
                M128A Xmm3;
                M128A Xmm4;
                M128A Xmm5;
                M128A Xmm6;
                M128A Xmm7;
                M128A Xmm8;
                M128A Xmm9;
                M128A Xmm10;
                M128A Xmm11;
                M128A Xmm12;
                M128A Xmm13;
                M128A Xmm14;
                M128A Xmm15;
            } DUMMYSTRUCTNAME;
        } DUMMYUNIONNAME;

        //
        // Vector registers.
        //

        M128A VectorRegister[26];
        UINT64 VectorControl;

        //
        // Special debug control registers.
        //

        UINT64 DebugControl;
        UINT64 LastBranchToRip;
        UINT64 LastBranchFromRip;
        UINT64 LastExceptionToRip;
        UINT64 LastExceptionFromRip;
    }*PCONTEXT64;


    struct FLOATING_SAVE_AREA
    {
        enum : UINT32
        {
            SizeOf80387Registers = 80,
        };

        UINT32   ControlWord;
        UINT32   StatusWord;
        UINT32   TagWord;
        UINT32   ErrorOffset;
        UINT32   ErrorSelector;
        UINT32   DataOffset;
        UINT32   DataSelector;
        UINT8    RegisterArea[SizeOf80387Registers];
        UINT32   Spare0;
    };
    using PFLOATING_SAVE_AREA = FLOATING_SAVE_AREA * ;

#   pragma pack(push, 4)
    typedef struct DECLSPEC_ALIGN(4) CONTEXT32
    {
        //
        // The flags values within this flag control the contents of
        // a CONTEXT record.
        //
        // If the context record is used as an input parameter, then
        // for each portion of the context record controlled by a flag
        // whose value is set, it is assumed that that portion of the
        // context record contains valid context. If the context record
        // is being used to modify a threads context, then only that
        // portion of the threads context will be modified.
        //
        // If the context record is used as an IN OUT parameter to capture
        // the context of a thread, then only those portions of the thread's
        // context corresponding to set flags will be returned.
        //
        // The context record is never used as an OUT only parameter.
        //

        UINT32 ContextFlags;

        //
        // This section is specified/returned if CONTEXT_DEBUG_REGISTERS is
        // set in ContextFlags.  Note that CONTEXT_DEBUG_REGISTERS is NOT
        // included in CONTEXT_FULL.
        //

        UINT32   Dr0;
        UINT32   Dr1;
        UINT32   Dr2;
        UINT32   Dr3;
        UINT32   Dr6;
        UINT32   Dr7;

        //
        // This section is specified/returned if the
        // ContextFlags word contians the flag CONTEXT_FLOATING_POINT.
        //

        FLOATING_SAVE_AREA FloatSave;

        //
        // This section is specified/returned if the
        // ContextFlags word contians the flag CONTEXT_SEGMENTS.
        //

        UINT32   SegGs;
        UINT32   SegFs;
        UINT32   SegEs;
        UINT32   SegDs;

        //
        // This section is specified/returned if the
        // ContextFlags word contians the flag CONTEXT_INTEGER.
        //

        UINT32   Edi;
        UINT32   Esi;
        UINT32   Ebx;
        UINT32   Edx;
        UINT32   Ecx;
        UINT32   Eax;

        //
        // This section is specified/returned if the
        // ContextFlags word contians the flag CONTEXT_CONTROL.
        //

        UINT32   Ebp;
        UINT32   Eip;
        UINT32   SegCs;              // MUST BE SANITIZED
        UINT32   EFlags;             // MUST BE SANITIZED
        UINT32   Esp;
        UINT32   SegSs;

        //
        // This section is specified/returned if the ContextFlags word
        // contains the flag CONTEXT_EXTENDED_REGISTERS.
        // The format and contexts are processor specific
        //

        UINT8   ExtendedRegisters[MaximumContextExtension];

    } *PCONTEXT32;
#   pragma pack(pop)

       
    typedef union _PS_CLIENT_SECURITY_CONTEXT
    {
        union
        {
            SIZE_T ImpersonationData;
            VOID* ImpersonationToken;
            struct /* bitfield */
            {
                SIZE_T ImpersonationLevel : 2; /* bit position: 0 */
                SIZE_T EffectiveOnly : 1; /* bit position: 2 */
            }; /* bitfield */
        };
    } PS_CLIENT_SECURITY_CONTEXT, *PPS_CLIENT_SECURITY_CONTEXT; /* size: 0x0008 */ /* size: 0x0004 */
    static_assert(sizeof(PS_CLIENT_SECURITY_CONTEXT) == (sizeof(SIZE_T) == sizeof(UINT64) ? 0x0008 : 0x0004));


    enum : UINT32
    {
        GroupAffinityFillSize = offsetof(GROUP_AFFINITY, Reserved)
    };

    
    typedef struct _PS_PROPERTY_SET
    {
        struct _LIST_ENTRY ListHead;
        EX_PUSH_LOCK Lock;
    } PS_PROPERTY_SET, *PPS_PROPERTY_SET; /* size: 0x0018 */ /* size: 0x000c */


}

#include "Ts\build_7600.inl"
#include "Ts\build_7601.inl"
#include "Ts\build_9200.inl"
#include "Ts\build_9600.inl"
#include "Ts\build_10240.inl"
#include "Ts\build_10586.inl"
#include "Ts\build_14393.inl"
#include "Ts\build_15063.inl"
#include "Ts\build_16299.inl"
#include "Ts\build_17134.inl"
#include "Ts\build_17763.inl"
