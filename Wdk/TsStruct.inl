#pragma once
#include "KeStruct.inl"


namespace wdk
{
    
#pragma region AccessMask
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
#pragma endregion


#pragma region Context
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
#pragma endregion


#pragma region General TEB
    template<typename T = PVOID>
    struct ACTIVATION_CONTEXT_STACK_T
    {
        using LIST_ENTRY = LIST_ENTRY_T<T>;

        T /*struct _RTL_ACTIVATION_CONTEXT_STACK_FRAME**/ ActiveFrame;
        LIST_ENTRY FrameListCache;
        UINT32 Flags;
        UINT32 NextCookieSequenceNumber;
        UINT32 StackId;
    }; /* size: 0x0028 */ /* size: 0x0018 */
    
    using ACTIVATION_CONTEXT_STACK   = ACTIVATION_CONTEXT_STACK_T<PVOID>;
    using ACTIVATION_CONTEXT_STACK32 = ACTIVATION_CONTEXT_STACK_T<PVOID32>;
    using ACTIVATION_CONTEXT_STACK64 = ACTIVATION_CONTEXT_STACK_T<PVOID64>;

    using PACTIVATION_CONTEXT_STACK   = ACTIVATION_CONTEXT_STACK * ;
    using PACTIVATION_CONTEXT_STACK32 = ACTIVATION_CONTEXT_STACK32 * ;
    using PACTIVATION_CONTEXT_STACK64 = ACTIVATION_CONTEXT_STACK64 * ;

    static_assert(sizeof(ACTIVATION_CONTEXT_STACK32) == 0x0018);
    static_assert(sizeof(ACTIVATION_CONTEXT_STACK64) == 0x0028);


    template<typename I = SIZE_T>
    struct GDI_TEB_BATCH_T
    {
        struct /* bitfield */
        {
            UINT32 Offset : 31; /* bit position: 0 */
            UINT32 HasRenderingCommand : 1; /* bit position: 31 */
        }; /* bitfield */
        I HDC;
        UINT32 Buffer[310];
    }; /* size: 0x04e8 */ /* size: 0x04e0 */

    using GDI_TEB_BATCH = GDI_TEB_BATCH_T<SIZE_T>;
    using GDI_TEB_BATCH32 = GDI_TEB_BATCH_T<UINT32>;
    using GDI_TEB_BATCH64 = GDI_TEB_BATCH_T<UINT64>;

    using PGDI_TEB_BATCH = GDI_TEB_BATCH * ;
    using PGDI_TEB_BATCH32 = GDI_TEB_BATCH32 * ;
    using PGDI_TEB_BATCH64 = GDI_TEB_BATCH64 * ;

    static_assert(sizeof(GDI_TEB_BATCH32) == 0x04e0);
    static_assert(sizeof(GDI_TEB_BATCH64) == 0x04e8);


    typedef struct _TEB
    {
        enum : UINT32
        {
            StaticUnicodeBufferSize = 260 + 1, // MAX_PATH + 1

            SystemReserveed1SizeX86 = 26,
            SystemReserveed1SizeX64 = 30,
            SystemReserveed1Size = sizeof(SIZE_T) == sizeof(UINT64) ? SystemReserveed1SizeX64 : SystemReserveed1SizeX86,

            InstrumentationX86 = 9,
            InstrumentationX64 = 11,
            InstrumentationCount = sizeof(SIZE_T) == sizeof(UINT64) ? InstrumentationX64 : InstrumentationX86,
        };

        struct _NT_TIB NtTib;
        VOID* EnvironmentPointer;
        struct _CLIENT_ID ClientId;
        VOID* ActiveRpcHandle;
        VOID* ThreadLocalStoragePointer;
        struct _PEB* ProcessEnvironmentBlock;
        UINT32 LastErrorValue;
        UINT32 CountOfOwnedCriticalSections;
        VOID* CsrClientThread;
        VOID* Win32ThreadInfo;
        UINT32 User32Reserved[26];
        UINT32 UserReserved[5];
        VOID* WOW32Reserved;
        UINT32 CurrentLocale;
        UINT32 FpSoftwareStatusRegister;
        VOID* ReservedForDebuggerInstrumentation[16];
        VOID* SystemReserved1[SystemReserveed1Size];
        CHAR PlaceholderCompatibilityMode;
        UINT8 PlaceholderHydrationAlwaysExplicit;
        CHAR PlaceholderReserved[10];
        UINT32 ProxiedProcessId;
        ACTIVATION_CONTEXT_STACK _ActivationStack;
        UINT8 WorkingOnBehalfTicket[8];
        INT32 ExceptionCode;
        struct _ACTIVATION_CONTEXT_STACK* ActivationContextStackPointer;
        SIZE_T InstrumentationCallbackSp;
        SIZE_T InstrumentationCallbackPreviousPc;
        SIZE_T InstrumentationCallbackPreviousSp;
#ifdef _WIN64
        UINT32 TxFsContext;
#endif
        UINT8 InstrumentationCallbackDisabled;
#ifdef _WIN64
        UINT8 UnalignedLoadStoreExceptions;
#else
        UINT8 SpareBytes[23];
        UINT32 TxFsContext;
#endif
        GDI_TEB_BATCH GdiTebBatch;
        struct _CLIENT_ID RealClientId;
        VOID* GdiCachedProcessHandle;
        UINT32 GdiClientPID;
        UINT32 GdiClientTID;
        VOID* GdiThreadLocalInfo;
        SIZE_T Win32ClientInfo[62];
        VOID* glDispatchTable[233];
        SIZE_T glReserved1[29];
        VOID* glReserved2;
        VOID* glSectionInfo;
        VOID* glSection;
        VOID* glTable;
        VOID* glCurrentRC;
        VOID* glContext;
        UINT32 LastStatusValue;
        struct _UNICODE_STRING StaticUnicodeString;
        WCHAR StaticUnicodeBuffer[StaticUnicodeBufferSize];
        VOID* DeallocationStack;
        VOID* TlsSlots[64];
        struct _LIST_ENTRY TlsLinks;
        VOID* Vdm;
        VOID* ReservedForNtRpc;
        VOID* DbgSsReserved[2];
        UINT32 HardErrorMode;
        VOID* Instrumentation[InstrumentationCount];
        struct _GUID ActivityId;
        VOID* SubProcessTag;
        VOID* PerflibData;
        VOID* EtwTraceData;
        VOID* WinSockData;
        UINT32 GdiBatchCount;
        union
        {
            struct _PROCESSOR_NUMBER CurrentIdealProcessor;
            UINT32 IdealProcessorValue;
            struct
            {
                UINT8 ReservedPad0;
                UINT8 ReservedPad1;
                UINT8 ReservedPad2;
                UINT8 IdealProcessor;
            }; /* size: 0x0004 */
        }; /* size: 0x0004 */
        UINT32 GuaranteedStackBytes;
        VOID* ReservedForPerf;
        VOID* ReservedForOle;
        UINT32 WaitingOnLoaderLock;
        VOID* SavedPriorityState;
        SIZE_T ReservedForCodeCoverage;
        VOID* ThreadPoolData;
        VOID** TlsExpansionSlots;
#ifdef _WIN64
        VOID* DeallocationBStore;
        VOID* BStoreLimit;
#endif
        UINT32 MuiGeneration;
        UINT32 IsImpersonating;
        VOID* NlsCache;
        VOID* pShimData;
        UINT32 HeapData;
        VOID* CurrentTransactionHandle;
        struct _TEB_ACTIVE_FRAME* ActiveFrame;
        VOID* FlsData;
        VOID* PreferredLanguages;
        VOID* UserPrefLanguages;
        VOID* MergedPrefLanguages;
        UINT32 MuiImpersonation;
        union
        {
            volatile UINT16 CrossTebFlags;
            UINT16 SpareCrossTebBits : 16; /* bit position: 0 */
        }; /* size: 0x0002 */
        union
        {
            UINT16 SameTebFlags;
            struct /* bitfield */
            {
                UINT16 SafeThunkCall : 1; /* bit position: 0 */
                UINT16 InDebugPrint : 1; /* bit position: 1 */
                UINT16 HasFiberData : 1; /* bit position: 2 */
                UINT16 SkipThreadAttach : 1; /* bit position: 3 */
                UINT16 WerInShipAssertCode : 1; /* bit position: 4 */
                UINT16 RanProcessInit : 1; /* bit position: 5 */
                UINT16 ClonedThread : 1; /* bit position: 6 */
                UINT16 SuppressDebugMsg : 1; /* bit position: 7 */
                UINT16 DisableUserStackWalk : 1; /* bit position: 8 */
                UINT16 RtlExceptionAttached : 1; /* bit position: 9 */
                UINT16 InitialThread : 1; /* bit position: 10 */
                UINT16 SessionAware : 1; /* bit position: 11 */
                UINT16 LoadOwner : 1; /* bit position: 12 */
                UINT16 LoaderWorker : 1; /* bit position: 13 */
                UINT16 SkipLoaderInit : 1; /* bit position: 14 */
                UINT16 SpareSameTebBits : 1; /* bit position: 15 */
            }; /* bitfield */
        }; /* size: 0x0002 */
        VOID* TxnScopeEnterCallback;
        VOID* TxnScopeExitCallback;
        VOID* TxnScopeContext;
        UINT32 LockCount;
        INT32 WowTebOffset;
    } TEB, *PTEB; /* size: 0x1810 */ /* size: 0x0fe0 */
    static_assert(sizeof(TEB) == (sizeof(SIZE_T) == sizeof(UINT64) ? 0x1810 : 0x0fe0));


    typedef struct _TEB32
    {
        enum : UINT32
        {
            StaticUnicodeBufferSize = 260 + 1, // MAX_PATH + 1

            SystemReserveed1SizeX86 = 26,
            SystemReserveed1SizeX64 = 30,
            SystemReserveed1Size = sizeof(SIZE_T) == sizeof(UINT64) ? SystemReserveed1SizeX64 : SystemReserveed1SizeX86,

            InstrumentationX86 = 9,
            InstrumentationX64 = 11,
            InstrumentationCount = sizeof(SIZE_T) == sizeof(UINT64) ? InstrumentationX64 : InstrumentationX86,
        };

        struct _NT_TIB32 NtTib;
        PVOID32 EnvironmentPointer;
        CLIENT_ID32 ClientId;
        PVOID32 ActiveRpcHandle;
        PVOID32 ThreadLocalStoragePointer;
        PVOID32 /*struct _PEB32**/ ProcessEnvironmentBlock;
        UINT32 LastErrorValue;
        UINT32 CountOfOwnedCriticalSections;
        PVOID32 CsrClientThread;
        PVOID32 Win32ThreadInfo;
        UINT32 User32Reserved[26];
        UINT32 UserReserved[5];
        PVOID32 WOW32Reserved;
        UINT32 CurrentLocale;
        UINT32 FpSoftwareStatusRegister;
        PVOID32 ReservedForDebuggerInstrumentation[16];
        PVOID32 SystemReserved1[SystemReserveed1SizeX86];
        CHAR PlaceholderCompatibilityMode;
        UINT8 PlaceholderHydrationAlwaysExplicit;
        CHAR PlaceholderReserved[10];
        UINT32 ProxiedProcessId;
        ACTIVATION_CONTEXT_STACK32 _ActivationStack;
        UINT8 WorkingOnBehalfTicket[8];
        INT32 ExceptionCode;
        PVOID32 /*struct _ACTIVATION_CONTEXT_STACK32**/ ActivationContextStackPointer;
        UINT32 InstrumentationCallbackSp;
        UINT32 InstrumentationCallbackPreviousPc;
        UINT32 InstrumentationCallbackPreviousSp;
        UINT8 InstrumentationCallbackDisabled;
        UINT8 SpareBytes[23];
        UINT32 TxFsContext;
        GDI_TEB_BATCH32 GdiTebBatch;
        CLIENT_ID32 RealClientId;
        PVOID32 GdiCachedProcessHandle;
        UINT32 GdiClientPID;
        UINT32 GdiClientTID;
        PVOID32 GdiThreadLocalInfo;
        UINT32 Win32ClientInfo[62];
        PVOID32 glDispatchTable[233];
        UINT32 glReserved1[29];
        PVOID32 glReserved2;
        PVOID32 glSectionInfo;
        PVOID32 glSection;
        PVOID32 glTable;
        PVOID32 glCurrentRC;
        PVOID32 glContext;
        UINT32 LastStatusValue;
        UNICODE_STRING32 StaticUnicodeString;
        WCHAR StaticUnicodeBuffer[StaticUnicodeBufferSize];
        PVOID32 DeallocationStack;
        PVOID32 TlsSlots[64];
        LIST_ENTRY32 TlsLinks;
        PVOID32 Vdm;
        PVOID32 ReservedForNtRpc;
        PVOID32 DbgSsReserved[2];
        UINT32 HardErrorMode;
        PVOID32 Instrumentation[InstrumentationX86];
        struct _GUID ActivityId;
        PVOID32 SubProcessTag;
        PVOID32 PerflibData;
        PVOID32 EtwTraceData;
        PVOID32 WinSockData;
        UINT32 GdiBatchCount;
        union
        {
            struct _PROCESSOR_NUMBER CurrentIdealProcessor;
            UINT32 IdealProcessorValue;
            struct
            {
                UINT8 ReservedPad0;
                UINT8 ReservedPad1;
                UINT8 ReservedPad2;
                UINT8 IdealProcessor;
            }; /* size: 0x0004 */
        }; /* size: 0x0004 */
        UINT32 GuaranteedStackBytes;
        PVOID32 ReservedForPerf;
        PVOID32 ReservedForOle;
        UINT32 WaitingOnLoaderLock;
        PVOID32 SavedPriorityState;
        UINT32 ReservedForCodeCoverage;
        PVOID32 ThreadPoolData;
        PVOID32 /*VOID***/ TlsExpansionSlots;
        UINT32 MuiGeneration;
        UINT32 IsImpersonating;
        PVOID32 NlsCache;
        PVOID32 pShimData;
        UINT32 HeapData;
        PVOID32 CurrentTransactionHandle;
        PVOID32 /*struct _TEB_ACTIVE_FRAME**/ ActiveFrame;
        PVOID32 FlsData;
        PVOID32 PreferredLanguages;
        PVOID32 UserPrefLanguages;
        PVOID32 MergedPrefLanguages;
        UINT32 MuiImpersonation;
        union
        {
            volatile UINT16 CrossTebFlags;
            UINT16 SpareCrossTebBits : 16; /* bit position: 0 */
        }; /* size: 0x0002 */
        union
        {
            UINT16 SameTebFlags;
            struct /* bitfield */
            {
                UINT16 SafeThunkCall : 1; /* bit position: 0 */
                UINT16 InDebugPrint : 1; /* bit position: 1 */
                UINT16 HasFiberData : 1; /* bit position: 2 */
                UINT16 SkipThreadAttach : 1; /* bit position: 3 */
                UINT16 WerInShipAssertCode : 1; /* bit position: 4 */
                UINT16 RanProcessInit : 1; /* bit position: 5 */
                UINT16 ClonedThread : 1; /* bit position: 6 */
                UINT16 SuppressDebugMsg : 1; /* bit position: 7 */
                UINT16 DisableUserStackWalk : 1; /* bit position: 8 */
                UINT16 RtlExceptionAttached : 1; /* bit position: 9 */
                UINT16 InitialThread : 1; /* bit position: 10 */
                UINT16 SessionAware : 1; /* bit position: 11 */
                UINT16 LoadOwner : 1; /* bit position: 12 */
                UINT16 LoaderWorker : 1; /* bit position: 13 */
                UINT16 SkipLoaderInit : 1; /* bit position: 14 */
                UINT16 SpareSameTebBits : 1; /* bit position: 15 */
            }; /* bitfield */
        }; /* size: 0x0002 */
        PVOID32 TxnScopeEnterCallback;
        PVOID32 TxnScopeExitCallback;
        PVOID32 TxnScopeContext;
        UINT32 LockCount;
        INT32 WowTebOffset;
    } TEB32, *PTEB32; /* size: 0x1810 */ /* size: 0x0fe0 */
    static_assert(sizeof(TEB32) == 0x0fe0);


    typedef struct _TEB64
    {
        enum : UINT32
        {
            StaticUnicodeBufferSize = 260 + 1, // MAX_PATH + 1

            SystemReserveed1SizeX86 = 26,
            SystemReserveed1SizeX64 = 30,
            SystemReserveed1Size = sizeof(SIZE_T) == sizeof(UINT64) ? SystemReserveed1SizeX64 : SystemReserveed1SizeX86,

            InstrumentationX86 = 9,
            InstrumentationX64 = 11,
            InstrumentationCount = sizeof(SIZE_T) == sizeof(UINT64) ? InstrumentationX64 : InstrumentationX86,
        };

        struct _NT_TIB64 NtTib;
        PVOID64 EnvironmentPointer;
        CLIENT_ID64 ClientId;
        PVOID64 ActiveRpcHandle;
        PVOID64 ThreadLocalStoragePointer;
        PVOID64 /*struct _PEB64**/ ProcessEnvironmentBlock;
        UINT32 LastErrorValue;
        UINT32 CountOfOwnedCriticalSections;
        PVOID64 CsrClientThread;
        PVOID64 Win32ThreadInfo;
        UINT32 User32Reserved[26];
        UINT32 UserReserved[5];
        PVOID64 WOW32Reserved;
        UINT32 CurrentLocale;
        UINT32 FpSoftwareStatusRegister;
        PVOID64 ReservedForDebuggerInstrumentation[16];
        PVOID64 SystemReserved1[SystemReserveed1SizeX64];
        CHAR PlaceholderCompatibilityMode;
        UINT8 PlaceholderHydrationAlwaysExplicit;
        CHAR PlaceholderReserved[10];
        UINT32 ProxiedProcessId;
        ACTIVATION_CONTEXT_STACK64 _ActivationStack;
        UINT8 WorkingOnBehalfTicket[8];
        INT32 ExceptionCode;
        PVOID64 /*struct _ACTIVATION_CONTEXT_STACK64**/ ActivationContextStackPointer;
        UINT64 InstrumentationCallbackSp;
        UINT64 InstrumentationCallbackPreviousPc;
        UINT64 InstrumentationCallbackPreviousSp;
        UINT32 TxFsContext;
        UINT8 InstrumentationCallbackDisabled;
        UINT8 UnalignedLoadStoreExceptions;
        GDI_TEB_BATCH64 GdiTebBatch;
        CLIENT_ID64 RealClientId;
        PVOID64 GdiCachedProcessHandle;
        UINT32 GdiClientPID;
        UINT32 GdiClientTID;
        PVOID64 GdiThreadLocalInfo;
        UINT64 Win32ClientInfo[62];
        PVOID64 glDispatchTable[233];
        UINT64 glReserved1[29];
        PVOID64 glReserved2;
        PVOID64 glSectionInfo;
        PVOID64 glSection;
        PVOID64 glTable;
        PVOID64 glCurrentRC;
        PVOID64 glContext;
        UINT32 LastStatusValue;
        UNICODE_STRING64 StaticUnicodeString;
        WCHAR StaticUnicodeBuffer[StaticUnicodeBufferSize];
        PVOID64 DeallocationStack;
        PVOID64 TlsSlots[64];
        LIST_ENTRY64 TlsLinks;
        PVOID64 Vdm;
        PVOID64 ReservedForNtRpc;
        PVOID64 DbgSsReserved[2];
        UINT32 HardErrorMode;
        PVOID64 Instrumentation[InstrumentationX64];
        struct _GUID ActivityId;
        PVOID64 SubProcessTag;
        PVOID64 PerflibData;
        PVOID64 EtwTraceData;
        PVOID64 WinSockData;
        UINT32 GdiBatchCount;
        union
        {
            struct _PROCESSOR_NUMBER CurrentIdealProcessor;
            UINT32 IdealProcessorValue;
            struct
            {
                UINT8 ReservedPad0;
                UINT8 ReservedPad1;
                UINT8 ReservedPad2;
                UINT8 IdealProcessor;
            }; /* size: 0x0004 */
        }; /* size: 0x0004 */
        UINT32 GuaranteedStackBytes;
        PVOID64 ReservedForPerf;
        PVOID64 ReservedForOle;
        UINT32 WaitingOnLoaderLock;
        PVOID64 SavedPriorityState;
        UINT64 ReservedForCodeCoverage;
        PVOID64 ThreadPoolData;
        PVOID64 /*VOID***/ TlsExpansionSlots;
        PVOID64 DeallocationBStore;
        PVOID64 BStoreLimit;
        UINT32 MuiGeneration;
        UINT32 IsImpersonating;
        PVOID64 NlsCache;
        PVOID64 pShimData;
        UINT32 HeapData;
        PVOID64 CurrentTransactionHandle;
        PVOID64 /*struct _TEB_ACTIVE_FRAME**/ ActiveFrame;
        PVOID64 FlsData;
        PVOID64 PreferredLanguages;
        PVOID64 UserPrefLanguages;
        PVOID64 MergedPrefLanguages;
        UINT32 MuiImpersonation;
        union
        {
            volatile UINT16 CrossTebFlags;
            UINT16 SpareCrossTebBits : 16; /* bit position: 0 */
        }; /* size: 0x0002 */
        union
        {
            UINT16 SameTebFlags;
            struct /* bitfield */
            {
                UINT16 SafeThunkCall : 1; /* bit position: 0 */
                UINT16 InDebugPrint : 1; /* bit position: 1 */
                UINT16 HasFiberData : 1; /* bit position: 2 */
                UINT16 SkipThreadAttach : 1; /* bit position: 3 */
                UINT16 WerInShipAssertCode : 1; /* bit position: 4 */
                UINT16 RanProcessInit : 1; /* bit position: 5 */
                UINT16 ClonedThread : 1; /* bit position: 6 */
                UINT16 SuppressDebugMsg : 1; /* bit position: 7 */
                UINT16 DisableUserStackWalk : 1; /* bit position: 8 */
                UINT16 RtlExceptionAttached : 1; /* bit position: 9 */
                UINT16 InitialThread : 1; /* bit position: 10 */
                UINT16 SessionAware : 1; /* bit position: 11 */
                UINT16 LoadOwner : 1; /* bit position: 12 */
                UINT16 LoaderWorker : 1; /* bit position: 13 */
                UINT16 SkipLoaderInit : 1; /* bit position: 14 */
                UINT16 SpareSameTebBits : 1; /* bit position: 15 */
            }; /* bitfield */
        }; /* size: 0x0002 */
        PVOID64 TxnScopeEnterCallback;
        PVOID64 TxnScopeExitCallback;
        PVOID64 TxnScopeContext;
        UINT32 LockCount;
        INT32 WowTebOffset;
    } TEB64, *PTEB64; /* size: 0x1810 */ /* size: 0x0fe0 */
    static_assert(sizeof(TEB64) == 0x1810);
#pragma endregion


#pragma region Other
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


    enum PsThreadCrossFlagMask : UINT32
    {
        PsCrossThreadFlagsTerminated                = 0x00000001,
        PsCrossThreadFlagsThreadInserted            = 0x00000002,
        PsCrossThreadFlagsHideFromDebugger          = 0x00000004,
        PsCrossThreadFlagsActiveImpersonationInfo   = 0x00000008,
        PsCrossThreadFlagsHardErrorsAreDisabled     = 0x00000010,
        PsCrossThreadFlagsBreakOnTermination        = 0x00000020,
        PsCrossThreadFlagsSkipCreationMsg           = 0x00000040,
        PsCrossThreadFlagsSkipTerminationMsg        = 0x00000080,

        // ...
    };
#pragma endregion


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
