#pragma once
#include "ExStruct.inl"


namespace wdk
{

#pragma region AccessMask
    enum ObjectAttributesMask : ACCESS_MASK
    {
        ObjectInherit           = 0x00000002,
        ObjectPermanent         = 0x00000010,
        ObjectExclusive         = 0x00000020,
        ObjectCaseInsensitive   = 0x00000040,
        ObjectOpenIf            = 0x00000080,
        ObjectOpenLink          = 0x00000100,
        ObjectKernelHandle      = 0x00000200,
        ObjectForceAccessCheck  = 0x00000400,
        ObjectIgnoreImpersonatedDevicemap = 0x00000800,
        ObjectDontReparse       = 0x00001000,
        ObjectValidAttributes   = 0x00001FF2,
    };
#pragma endregion


#pragma region Object Initializer
    typedef struct _OBJECT_DUMP_CONTROL
    {
        PVOID Stream;
        ULONG Detail;
    } OB_DUMP_CONTROL, *POB_DUMP_CONTROL;

    using ObDumpMethod = void(NTAPI *)(
        PVOID   aObject,
        POB_DUMP_CONTROL aControl);

    enum class OB_OPEN_REASON : UINT32
    {
        ObCreateHandle,
        ObOpenHandle,
        ObDuplicateHandle,
        ObInheritHandle,
        ObMaxOpenReason
    };

    using ObOpenMethod = NTSTATUS(NTAPI *)(
        OB_OPEN_REASON  aReason,
        KPROCESSOR_MODE aPreviousMode,
        PVOID           aProcess,
        PVOID           aObject,
        PACCESS_MASK    aGrantedAccess,
        ULONG           aHandleCount);

    using ObCloseMethod = void(NTAPI *)(
        PVOID   aProcess,
        PVOID   aObject,
        SIZE_T  aProcessHandleCount,
        SIZE_T  aSystemHandleCount);

    using ObDeleteMethod = void(NTAPI *)(
        PVOID aObject);

    using ObParseMethod = NTSTATUS(NTAPI *)(
        PVOID           aParseObject,
        PVOID           aObjectType,
        PACCESS_STATE   aAccessState,
        KPROCESSOR_MODE aPreviousMode,
        ULONG           aAttributes,
        PUNICODE_STRING aCompleteName,
        PUNICODE_STRING aRemainingName,
        PVOID           aContext,
        PSECURITY_QUALITY_OF_SERVICE aSecurityQos,
        PVOID*          aObject);

    typedef struct _OB_EXTENDED_PARSE_PARAMETERS
    {
        UINT16  Length;
        ULONG32 RestrictedAccessMask;
        struct _EJOB *Silo;
    } OB_EXTENDED_PARSE_PARAMETERS, *POB_EXTENDED_PARSE_PARAMETERS;

    using ObParseExMethod = NTSTATUS(NTAPI *)(
        PVOID           aParseObject,
        PVOID           aObjectType,
        PACCESS_STATE   aAccessState,
        KPROCESSOR_MODE aPreviousMode,
        ULONG           aAttributes,
        PUNICODE_STRING aCompleteName,
        PUNICODE_STRING aRemainingName,
        PVOID           aContext,
        PSECURITY_QUALITY_OF_SERVICE  aSecurityQos,
        POB_EXTENDED_PARSE_PARAMETERS aExtArgs,
        PVOID*          aObject);

    using ObSecurityMethod = NTSTATUS(NTAPI *)(
        PVOID                   aObject,
        SECURITY_OPERATION_CODE aOperationCode,
        PSECURITY_INFORMATION   aSecurityInformation,
        PSECURITY_DESCRIPTOR    aSecurityDescriptor,
        PULONG                  aCapturedLength,
        PSECURITY_DESCRIPTOR*   aObjectsSecurityDescriptor,
        POOL_TYPE               aPoolType,
        PGENERIC_MAPPING        aGenericMapping,
        KPROCESSOR_MODE         aPreviousMode);

    using ObQueryNameMethod = NTSTATUS(NTAPI *)(
        PVOID   aObject,
        BOOLEAN aHasObjectName,
        POBJECT_NAME_INFORMATION aObjectNameInfo,
        ULONG   aLength,
        PULONG  aReturnLength,
        KPROCESSOR_MODE aPreviousMode);

    using ObOkeyToCloseMethod = BOOLEAN(NTAPI *)(
        PEPROCESS   aProcess,
        PVOID       aObject,
        HANDLE      aHandle,
        KPROCESSOR_MODE aPreviousMode);

    typedef struct _OBJECT_TYPE_INITIALIZER
    {
        enum : UINT16
        {
            SizeOfInitializerWin7X64    = 0x70,
            SizeOfInitializerX64        = 0x78,

            SizeOfInitializerWin7X86    = 0x50,
            SizeOfInitializerX86        = 0x58,

            SizeOfInitializerWin7       = (sizeof(SIZE_T) == sizeof(UINT64) ? SizeOfInitializerWin7X64 : SizeOfInitializerWin7X86),
            SizeOfInitializer           = (sizeof(SIZE_T) == sizeof(UINT64) ? SizeOfInitializerX64 : SizeOfInitializerX86),
        };

        UINT16 Length;
        union
        {
            UINT16 ObjectTypeFlags;
            struct
            {
                struct
                {
                    UINT8 CaseInsensitive : 1;
                    UINT8 UnnamedObjectsOnly : 1;
                    UINT8 UseDefaultObject : 1;
                    UINT8 SecurityRequired : 1;
                    UINT8 MaintainHandleCount : 1;
                    UINT8 MaintainTypeList : 1;
                    UINT8 SupportsObjectCallbacks : 1;
                    UINT8 CacheAligned : 1;
                };
                struct
                {
                    UINT8 UseExtendedParameters : 1;
                    UINT8 Reserved : 7;
                };
            };
        };
        ULONG32         ObjectTypeCode;
        ULONG32         InvalidAttributes;
        GENERIC_MAPPING GenericMapping;
        ULONG32         ValidAccessMask;
        ULONG32         RetainAccess;
        POOL_TYPE       PoolType;
        ULONG32         DefaultPagedPoolCharge;
        ULONG32         DefaultNonPagedPoolCharge;
        ObDumpMethod    DumpProcedure;
        ObOpenMethod    OpenProcedure;
        ObCloseMethod   CloseProcedure;
        ObDeleteMethod  DeleteProcedure;
        union
        {
            ObParseMethod   ParseProcedure;
            ObParseExMethod ParseProcedureEx;
        };
        ObSecurityMethod    SecurityProcedure;
        ObQueryNameMethod   QueryNameProcedure;
        ObOkeyToCloseMethod OkayToCloseProcedure;
        ULONG32 WaitObjectFlagMask;
        UINT16  WaitObjectFlagOffset;
        UINT16  WaitObjectPointerOffset;
    } OBJECT_TYPE_INITIALIZER, *POBJECT_TYPE_INITIALIZER;
#pragma endregion


#pragma region Object Header
    enum ObInfoMask : UINT8
    {
        ObInfoMaskCreatorInfo           = 0x01,
        ObInfoMaskNameInfo              = 0x02,
        ObInfoMaskHandleInfo            = 0x04,
        ObInfoMaskQuotaInfo             = 0x08,
        ObInfoMaskProcessInfo           = 0x10,
        ObInfoMaskAuditInfo             = 0x20, // Windows 8
        ObInfoMaskHandleRevocationInfo  = 0x40, // Windows 10.0.10240~Windows 10.0.10586
        ObInfoMaskExtendedInfo          = 0x40, // Windows 10.0.14393
        ObInfoMaskPaddingInfoWin7x      = 0x20, // Windows 7~Windows 7.1
        ObInfoMaskPaddingInfoWin8x      = 0x40, // Windows 8~Windows 8.1
        ObInfoMaskPaddingInfo           = 0x80, // Windows 10
    };

    typedef struct _OBJECT_HEADER_CREATOR_INFO
    {
        LIST_ENTRY  TypeList;
        HANDLE      CreatorUniqueProcess;
        USHORT      CreatorBackTraceIndex;
        USHORT      Reserved1;
#ifdef _WIN64
        ULONG       Reserved2;
#endif
    } OBJECT_HEADER_CREATOR_INFO, *POBJECT_HEADER_CREATOR_INFO;
    static_assert(sizeof(OBJECT_HEADER_CREATOR_INFO) == (sizeof(void*) == sizeof(__int32) ? 0x0010 : 0x0020),
        "sizeof(OBJECT_CREATE_INFORMATION) wrong! ");

    typedef struct _OBJECT_HEADER_NAME_INFO
    {
        struct _OBJECT_DIRECTORY* Directory;
        UNICODE_STRING     Name;
        LONG               ReferenceCount;
#ifdef _WIN64
        ULONG              Reserved;
#endif
    } OBJECT_HEADER_NAME_INFO, *POBJECT_HEADER_NAME_INFO;
    static_assert(sizeof(OBJECT_HEADER_NAME_INFO) == (sizeof(void*) == sizeof(__int32) ? 0x0010 : 0x0020),
        "sizeof(OBJECT_HEADER_NAME_INFO) wrong! ");

    typedef struct _OBJECT_HANDLE_COUNT_ENTRY
    {
        PEPROCESS Process;
        struct
        {
            ULONG HandleCount : 24;
            ULONG LockCount : 8;
        };
    } OBJECT_HANDLE_COUNT_ENTRY, *POBJECT_HANDLE_COUNT_ENTRY;
    static_assert(sizeof(OBJECT_HANDLE_COUNT_ENTRY) == (sizeof(void*) == sizeof(__int32) ? 0x0008 : 0x0010),
        "sizeof(OBJECT_HANDLE_COUNT_ENTRY) wrong! ");

    typedef struct _OBJECT_HANDLE_COUNT_DATABASE
    {
        ULONG CountEntries;
        OBJECT_HANDLE_COUNT_ENTRY HandleCountEntries[1];
    } OBJECT_HANDLE_COUNT_DATABASE, *POBJECT_HANDLE_COUNT_DATABASE;
    static_assert(sizeof(OBJECT_HANDLE_COUNT_DATABASE) == (sizeof(void*) == sizeof(__int32) ? 0x000C : 0x0018),
        "sizeof(OBJECT_HANDLE_COUNT_DATABASE) wrong! ");

    typedef struct _OBJECT_HEADER_HANDLE_INFO
    {
        union
        {
            POBJECT_HANDLE_COUNT_DATABASE  HandleCountDataBase;
            OBJECT_HANDLE_COUNT_ENTRY      SingleEntry;
        };
    } OBJECT_HEADER_HANDLE_INFO, *POBJECT_HEADER_HANDLE_INFO;
    static_assert(sizeof(OBJECT_HEADER_HANDLE_INFO) == (sizeof(void*) == sizeof(__int32) ? 0x0008 : 0x0010),
        "sizeof(OBJECT_HEADER_HANDLE_INFO) wrong! ");

    typedef struct _OBJECT_HEADER_QUOTA_INFO
    {
        ULONG PagedPoolCharge;
        ULONG NonPagedPoolCharge;
        ULONG SecurityDescriptorCharge;
#ifdef _WIN64
        ULONG Reserved1;
        PVOID SecurityDescriptorQuotaBlock;
        ULONG64 Reserved2;
#else
        PVOID SecurityDescriptorQuotaBlock;
#endif
    } OBJECT_HEADER_QUOTA_INFO, *POBJECT_HEADER_QUOTA_INFO;
    static_assert(sizeof(OBJECT_HEADER_QUOTA_INFO) == (sizeof(void*) == sizeof(__int32) ? 0x0010 : 0x0020),
        "sizeof(OBJECT_HEADER_QUOTA_INFO) wrong! ");

    typedef struct _OBJECT_HEADER_PROCESS_INFO
    {
        PEPROCESS  ExclusiveProcess;
        SIZE_T     Reserved;
    } OBJECT_HEADER_PROCESS_INFO, *POBJECT_HEADER_PROCESS_INFO;
    static_assert(sizeof(OBJECT_HEADER_PROCESS_INFO) == (sizeof(void*) == sizeof(__int32) ? 0x0008 : 0x0010),
        "sizeof(OBJECT_HEADER_PROCESS_INFO) wrong! ");

    typedef struct _OBJECT_HEADER_AUDIT_INFO
    {
        PVOID  SecurityDescriptor;
        SIZE_T Reserved;
    } OBJECT_HEADER_AUDIT_INFO, *POBJECT_HEADER_AUDIT_INFO;
    static_assert(sizeof(OBJECT_HEADER_AUDIT_INFO) == (sizeof(void*) == sizeof(__int32) ? 0x0008 : 0x0010),
        "sizeof(OBJECT_HEADER_AUDIT_INFO) wrong! ");

    typedef struct _OBJECT_HEADER_HANDLE_REVOCATION_INFO
    {
        LIST_ENTRY ListEntry;
        struct _OB_HANDLE_REVOCATION_BLOCK* RevocationBlock;
        UINT8 Padding1[4];
#ifdef _WIN64
        UINT8 Padding2[4];
#endif
    } OBJECT_HEADER_HANDLE_REVOCATION_INFO, *POBJECT_HEADER_HANDLE_REVOCATION_INFO;
    static_assert(sizeof(OBJECT_HEADER_HANDLE_REVOCATION_INFO) == (sizeof(void*) == sizeof(__int32) ? 0x0010 : 0x0020),
        "sizeof(OBJECT_HEADER_HANDLE_REVOCATION_INFO) wrong! ");

    typedef struct _OBJECT_HEADER_EXTENDED_INFO
    {
        struct _OBJECT_FOOTER* Footer;
        SIZE_T Reserved;
    } OBJECT_HEADER_EXTENDED_INFO, *POBJECT_HEADER_EXTENDED_INFO;
    static_assert(sizeof(OBJECT_HEADER_EXTENDED_INFO) == (sizeof(void*) == sizeof(__int32) ? 0x0008 : 0x0010),
        "sizeof(OBJECT_HEADER_EXTENDED_INFO) wrong! ");

    typedef struct _OBJECT_HEADER_PADDING_INFO
    {
        ULONG PaddingAmount;
    } OBJECT_HEADER_PADDING_INFO, *POBJECT_HEADER_PADDING_INFO;
    static_assert(sizeof(OBJECT_HEADER_PADDING_INFO) == (sizeof(void*) == sizeof(__int32) ? 0x0004 : 0x0004),
        "sizeof(OBJECT_HEADER_PADDING_INFO) wrong! ");

    typedef struct _OBJECT_CREATE_INFORMATION
    {
        ULONG   Attributes;
        HANDLE  RootDirectory;
        KPROCESSOR_MODE ProbeMode;
        ULONG   PagedPoolCharge;
        ULONG   NonPagedPoolCharge;
        ULONG   SecurityDescriptorCharge;
        PVOID   SecurityDescriptor;
        PSECURITY_QUALITY_OF_SERVICE   SecurityQos;
        SECURITY_QUALITY_OF_SERVICE    SecurityQualityOfService;
    } OBJECT_CREATE_INFORMATION, *POBJECT_CREATE_INFORMATION;
    static_assert(sizeof(OBJECT_CREATE_INFORMATION) == (sizeof(void*) == sizeof(__int32) ? 0x002C : 0x0040),
        "sizeof(OBJECT_CREATE_INFORMATION) wrong! ");

    typedef struct _OBJECT_HEADER
    {
        SSIZE_T PointerCount;
        union
        {
            SSIZE_T  HandleCount;
            PVOID   NextToFree;
        };
        EX_PUSH_LOCK Lock;
        UINT8 TypeIndex;
        union
        {
            UINT8 TraceFlags;
            struct
            {
                UINT8 DbgRefTrace : 1;
                UINT8 DbgTracePermanent : 1;
            };
        };
        UINT8 InfoMask;
        union
        {
            UINT8 Flags;
            struct
            {
                UINT8 NewObject : 1;
                UINT8 KernelObject : 1;
                UINT8 KernelOnlyAccess : 1;
                UINT8 ExclusiveObject : 1;
                UINT8 PermanentObject : 1;
                UINT8 DefaultSecurityQuota : 1;
                UINT8 SingleHandleEntry : 1;
                UINT8 DeletedInline : 1;
            };
        };

#ifdef _WIN64
        ULONG Reserved;
#endif
        union
        {
            POBJECT_CREATE_INFORMATION ObjectCreateInfo;
            PVOID QuotaBlockCharged;
        };
        PVOID SecurityDescriptor;
        QUAD Body;
    } OBJECT_HEADER, *POBJECT_HEADER;
    static_assert(sizeof(OBJECT_HEADER) == (sizeof(void*) == sizeof(__int32) ? 0x0020 : 0x0038));
#pragma endregion


#pragma region ObRegisterCallbacks() Cookie
    // private
    // 
    // ObRegisterCallbacks() Cookie Memory layout
    //
    // +-------------------------------------------+
    // | OB_CALLBACK_OBJECT_HEADER                 |
    // +-------------------------------------------+
    // | OB_CALLBACK_OBJECT_BODY[Header.BodyCount] |
    // +-------------------------------------------+
    // | WCHAR AltitudeBuffer[Altitude.Length]     |
    // +-------------------------------------------+
    //
    struct OB_CALLBACK_OBJECT_HEADER;
    struct OB_CALLBACK_OBJECT_BODY
    {
        // all OB_CALLBACK_BODY
        // Header -> OBJECT_TYPE.CallbackList
        LIST_ENTRY	                ListEntry;

        OB_OPERATION                Operations;
        ULONG		                Always_1;

        // Self
        OB_CALLBACK_OBJECT_HEADER*  CallbackObject;

        POBJECT_TYPE                ObjectType;
        POB_PRE_OPERATION_CALLBACK  PreOperation;
        POB_POST_OPERATION_CALLBACK PostOperation;

        ULONG		                Reserved;
    };

    struct OB_CALLBACK_OBJECT_HEADER
    {
        // ObGetFilterVersion()
        USHORT          Version;
        USHORT          BodyCount;
        PVOID           RegistrationContext;
        UNICODE_STRING  Altitude;

        // OB_CALLBACK_OBJECT_BODY Body[BodyCount];
    };
#pragma endregion

    
#pragma region Other
    typedef struct _OBJECT_DIRECTORY_INFORMATION
    {
        UNICODE_STRING Name;
        UNICODE_STRING TypeName;
    } OBJECT_DIRECTORY_INFORMATION, *POBJECT_DIRECTORY_INFORMATION;
#pragma endregion


}

#include "Ob\build_7600.inl"
#include "Ob\build_7601.inl"
#include "Ob\build_9200.inl"
#include "Ob\build_9600.inl"
#include "Ob\build_10240.inl"
#include "Ob\build_10586.inl"
#include "Ob\build_14393.inl"
#include "Ob\build_15063.inl"
#include "Ob\build_16299.inl"
#include "Ob\build_17134.inl"
#include "Ob\build_17763.inl"
