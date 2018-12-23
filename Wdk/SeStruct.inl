#pragma once


namespace wdk
{

#pragma region SID
    enum : UINT32
    {
        SidRevision = 1,
        SidMaxSubAuthorities = 15,
        SidRecommendedSubAuthorities = 1,
    };


    typedef struct SID_IDENTIFIER_AUTHORITY
    {
        UCHAR Value[6];
    }*PSID_IDENTIFIER_AUTHORITY;
    

    typedef struct SID
    {
        UCHAR Revision;
        UCHAR SubAuthorityCount;
        SID_IDENTIFIER_AUTHORITY IdentifierAuthority;
        ULONG SubAuthority[SidRecommendedSubAuthorities];
    }*PSID, *PISID;


    typedef struct MAX_SID
    {
        UINT8                       Revision;
        UINT8                       SubAuthorityCount;
        SID_IDENTIFIER_AUTHORITY    IdentifierAuthority;
        UINT32                      SubAuthority[SidMaxSubAuthorities];
    }*PMAX_SID, SE_SID, *PSE_SID;


#ifndef SECURITY_SID_SIZE
#define SECURITY_SID_SIZE(SubAuthorityCount_) (sizeof(SID) - sizeof(ULONG) + \
                                                (SubAuthorityCount_) * sizeof(ULONG))
#endif

#ifndef SECURITY_MAX_SID_SIZE
#define SECURITY_MAX_SID_SIZE sizeof(SE_SID)
#endif

    enum class SidNameUseType
    {
        SidTypeUser = 1,
        SidTypeGroup,
        SidTypeDomain,
        SidTypeAlias,
        SidTypeWellKnownGroup,
        SidTypeDeletedAccount,
        SidTypeInvalid,
        SidTypeUnknown,
        SidTypeComputer,
        SidTypeLabel,
        SidTypeLogonSession
    };


    typedef struct SID_AND_ATTRIBUTES
    {
        PSID    Sid;
        ULONG   Attributes;
    }*PSID_AND_ATTRIBUTES;
    

    typedef ULONG_PTR SID_HASH_ENTRY, *PSID_HASH_ENTRY;
    typedef struct SID_AND_ATTRIBUTES_HASH
    {
        enum : UINT32
        {
            SidHashSize = 32
        };

        ULONG SidCount;
        PSID_AND_ATTRIBUTES SidAttr;
        SID_HASH_ENTRY Hash[SidHashSize];
    }*PSID_AND_ATTRIBUTES_HASH;

    /* WELL_KNOWN_SID_TYPE */
    enum class WellKnownSidType : UINT32
    {
        WinNullSid = 0,
        WinWorldSid,
        WinLocalSid,
        WinCreatorOwnerSid,
        WinCreatorGroupSid,
        WinCreatorOwnerServerSid,
        WinCreatorGroupServerSid,
        WinNtAuthoritySid,
        WinDialupSid,
        WinNetworkSid,
        WinBatchSid,
        WinInteractiveSid,
        WinServiceSid,
        WinAnonymousSid,
        WinProxySid,
        WinEnterpriseControllersSid,
        WinSelfSid,
        WinAuthenticatedUserSid,
        WinRestrictedCodeSid,
        WinTerminalServerSid,
        WinRemoteLogonIdSid,
        WinLogonIdsSid,
        WinLocalSystemSid,
        WinLocalServiceSid,
        WinNetworkServiceSid,
        WinBuiltinDomainSid,
        WinBuiltinAdministratorsSid,
        WinBuiltinUsersSid,
        WinBuiltinGuestsSid,
        WinBuiltinPowerUsersSid,
        WinBuiltinAccountOperatorsSid,
        WinBuiltinSystemOperatorsSid,
        WinBuiltinPrintOperatorsSid,
        WinBuiltinBackupOperatorsSid,
        WinBuiltinReplicatorSid,
        WinBuiltinPreWindows2000CompatibleAccessSid,
        WinBuiltinRemoteDesktopUsersSid,
        WinBuiltinNetworkConfigurationOperatorsSid,
        WinAccountAdministratorSid,
        WinAccountGuestSid,
        WinAccountKrbtgtSid,
        WinAccountDomainAdminsSid,
        WinAccountDomainUsersSid,
        WinAccountDomainGuestsSid,
        WinAccountComputersSid,
        WinAccountControllersSid,
        WinAccountCertAdminsSid,
        WinAccountSchemaAdminsSid,
        WinAccountEnterpriseAdminsSid,
        WinAccountPolicyAdminsSid,
        WinAccountRasAndIasServersSid,
        WinNTLMAuthenticationSid,
        WinDigestAuthenticationSid,
        WinSChannelAuthenticationSid,
        WinThisOrganizationSid,
        WinOtherOrganizationSid,
        WinBuiltinIncomingForestTrustBuildersSid,
        WinBuiltinPerfMonitoringUsersSid,
        WinBuiltinPerfLoggingUsersSid,
        WinBuiltinAuthorizationAccessSid,
        WinBuiltinTerminalServerLicenseServersSid,
        WinBuiltinDCOMUsersSid,
        WinBuiltinIUsersSid,
        WinIUserSid,
        WinBuiltinCryptoOperatorsSid,
        WinUntrustedLabelSid,
        WinLowLabelSid,
        WinMediumLabelSid,
        WinHighLabelSid,
        WinSystemLabelSid,
        WinWriteRestrictedCodeSid,
        WinCreatorOwnerRightsSid,
        WinCacheablePrincipalsGroupSid,
        WinNonCacheablePrincipalsGroupSid,
        WinEnterpriseReadonlyControllersSid,
        WinAccountReadonlyControllersSid,
        WinBuiltinEventLogReadersGroup,
        WinNewEnterpriseReadonlyControllersSid,
        WinBuiltinCertSvcDComAccessGroup,
        WinMediumPlusLabelSid,
        WinLocalLogonSid,
        WinConsoleLogonSid,
        WinThisOrganizationCertificateSid,
        WinApplicationPackageAuthoritySid,
        WinBuiltinAnyPackageSid,
        WinCapabilityInternetClientSid,
        WinCapabilityInternetClientServerSid,
        WinCapabilityPrivateNetworkClientServerSid,
        WinCapabilityPicturesLibrarySid,
        WinCapabilityVideosLibrarySid,
        WinCapabilityMusicLibrarySid,
        WinCapabilityDocumentsLibrarySid,
        WinCapabilitySharedUserCertificatesSid,
        WinCapabilityEnterpriseAuthenticationSid,
        WinCapabilityRemovableStorageSid,
        WinBuiltinRDSRemoteAccessServersSid,
        WinBuiltinRDSEndpointServersSid,
        WinBuiltinRDSManagementServersSid,
        WinUserModeDriversSid,
        WinBuiltinHyperVAdminsSid,
        WinAccountCloneableControllersSid,
        WinBuiltinAccessControlAssistanceOperatorsSid,
        WinBuiltinRemoteManagementUsersSid,
        WinAuthenticationAuthorityAssertedSid,
        WinAuthenticationServiceAssertedSid,
        WinLocalAccountSid,
        WinLocalAccountAndAdministratorSid,
        WinAccountProtectedUsersSid,
        WinCapabilityAppointmentsSid,
        WinCapabilityContactsSid,
        WinAccountDefaultSystemManagedSid,
        WinBuiltinDefaultSystemManagedGroupSid,
        WinBuiltinStorageReplicaAdminsSid,
        WinAccountKeyAdminsSid,
        WinAccountEnterpriseKeyAdminsSid,
        WinAuthenticationKeyTrustSid,
        WinAuthenticationKeyPropertyMFASid,
        WinAuthenticationKeyPropertyAttestationSid,
        WinAuthenticationFreshKeyAuthSid,
        WinBuiltinDeviceOwnersSid,
    };


    typedef struct WELL_KNOWN_SID
    {
        wchar_t             Identifier[2];
        WellKnownSidType    Type;
        MAX_SID             Sid;
    }*PWELL_KNOWN_SID;

    typedef struct WELL_KNOWN_RID
    {
        wchar_t             Identifier[2];
        WellKnownSidType    Type;
        UINT32              Rid;
    }*PWELL_KNOWN_RID;


    enum AccessControlEntryType : UINT8
    {
        AccessMinMSAceType,
        AccessAllowedAceType = AccessMinMSAceType,
        AccessDeniedAceType,
        SystemAuditAceType,
        SystemAlarmAceType,
        AccessMaxMSv2AceType = SystemAlarmAceType,

        /* version 3 */
        AccessAllowedCompoundAceType,
        AccessMaxMSv3AceType = AccessAllowedCompoundAceType,

        /* version 4 */
        AccessMinMSObjectAceType,
        AccessAllowedObjectAceType = AccessMinMSObjectAceType,
        AccessDeniedObjectAceType,
        SystemAuditObjectAceType,
        SystemAlarmObjectAceType,
        AccessMaxMSObjectAceType = SystemAlarmObjectAceType,
        AccessMaxMSv4AceType = SystemAlarmObjectAceType,

        /* version 5 */
        AccessAllowedCallbackAceType,
        AccessDediedCallbackAceType,
        AccessAllowedCallbackObjectAceType,
        AccessDeniedCallbackObjectAceType,
        SystemAuditCallbackAceType,
        SystemAlarmCallbackAceType,
        SystemAuditCallbackObjectAceType,
        SystemAlarmCallbackObjectAceType,

        SystemMandatoryLabelAceType,
        SystemResourceAttributeAceType,
        SystemScopedPolicyIdAceType,
        SystemProcessTrustLabelAceType,
        SystemAccessFilterAceType,
        AccessMaxMSv5AceType = SystemAccessFilterAceType,
    };
    

    enum AccessControlEntryFlags : UINT8
    {
        ObjectInheritAce        = 0x01,
        ContainerInheritAce     = 0x02,
        NoPropagateInheritAce   = 0x04,
        InheritOnlyAce          = 0x8,
        InheritedAce            = 0x10,
        ValidInheritFlags       = 0x1f,
        CriticalAce             = 0x20,
        TrustProtectedFilterAce = 0x40,

        SuccessfulAccessAceFlag = 0x40,
        FailedAccessAceFlag     = 0x80,
    };


    enum AdsRightsMask : UINT32
    {
        AdsRightDelete      = 0x00010000,
        AdsRightReadControl = 0x00020000,
        AdsRightWriteDac    = 0x00040000,
        AdsRightWriteOwner  = 0x00080000,
        AdsRightSynchronize = 0x00100000,

        AdsRightAccessSystemSecurity = 0x01000000,

        AdsRightGenericAll      = 0x10000000,
        AdsRightGenericExecute  = 0x20000000,
        AdsRightGenericWrite    = 0x40000000,
        AdsRightGenericRead     = 0x80000000,

        AdsRightDsCreateChild   = 0x00000001,
        AdsRightDsDeleteChild   = 0x00000002,
        AdsRightActrlDsList     = 0x00000004,
        AdsRightDsSelf          = 0x00000008,
        AdsRightDsReadProp      = 0x00000010,
        AdsRightDsWriteProp     = 0x00000020,
        AdsRightDsDeleteTree    = 0x00000040,
        AdsRightDsListObject    = 0x00000080,
        AdsRightDsControlAccess = 0x00000100
    };

#ifndef SYSTEMANDATORY_LABEL_NO_WRITE_UP
#define SYSTEMANDATORY_LABEL_NO_WRITE_UP         0x1
#endif
#ifndef SYSTEMANDATORY_LABEL_NO_READ_UP
#define SYSTEMANDATORY_LABEL_NO_READ_UP          0x2
#endif
#ifndef SYSTEMANDATORY_LABEL_NO_EXECUTE_UP
#define SYSTEMANDATORY_LABEL_NO_EXECUTE_UP       0x4
#endif

    
    typedef struct WELL_KNOWN_ACE_FLAGS
    {
        const wchar_t*  Identifier;
        UINT32          Value;
    }*PWELL_KNOWN_ACE_FLAGS;
    typedef WELL_KNOWN_ACE_FLAGS WELL_KNOWN_ACE_TYPE , *PWELL_KNOWN_ACE_TYPE;
    typedef WELL_KNOWN_ACE_FLAGS WELL_KNOWN_ACE_RIGHT, *PWELL_KNOWN_ACE_RIGHT;


    typedef struct ACCESS_CONTROL_ENTRY_HEADER
    {
        UINT8   Type;     // AccessControlEntryType
        UINT8   Flags;    // AccessControlEntryFlags
        UINT16  Size;
    }*PACCESS_CONTROL_ENTRY_HEADER;

    typedef struct ACCESS_CONTROL_ENTRY
    {
        ACCESS_CONTROL_ENTRY_HEADER Header;
        UINT32                      AccessMask;
        UINT32                      SidStart;
    }*PACCESS_CONTROL_ENTRY, ACE, *PACE;

    typedef ACCESS_CONTROL_ENTRY ACCESS_ALLOWED_ACE , *PACCESS_ALLOWED_ACE;
    typedef ACCESS_CONTROL_ENTRY ACCESS_DENIED_ACE  , *PACCESS_DENIED_ACE;
    typedef ACCESS_CONTROL_ENTRY SYSTEM_AUDIT_ACE   , *PSYSTEM_AUDIT_ACE;
    typedef ACCESS_CONTROL_ENTRY SYSTEM_ALARM_ACE   , *PSYSTEM_ALARM_ACE;

    typedef ACCESS_CONTROL_ENTRY SYSTEM_RESOURCE_ATTRIBUTE_ACE  , *PSYSTEM_RESOURCE_ATTRIBUTE_ACE;
    typedef ACCESS_CONTROL_ENTRY SYSTEM_SCOPED_POLICY_ID_ACE    , *PSYSTEM_SCOPED_POLICY_ID_ACE;
    typedef ACCESS_CONTROL_ENTRY SYSTEM_MANDATORY_LABEL_ACE     , *PSYSTEM_MANDATORY_LABEL_ACE;
    typedef ACCESS_CONTROL_ENTRY SYSTEM_PROCESS_TRUST_LABEL_ACE , *PSYSTEM_PROCESS_TRUST_LABEL_ACE;
    typedef ACCESS_CONTROL_ENTRY SYSTEM_ACCESS_FILTER_ACE       , *PSYSTEM_ACCESS_FILTER_ACE;


    typedef struct ACCESS_CONTROL_LIST
    {
        enum : UINT8
        {
            AclRevision1 = 1,
            AclRevision2 = 2,
            AclRevision3 = 3,
            AclRevision4 = 4,

            AclRevision     = AclRevision2,
            MaxAclRevision  = AclRevision4,
        };

        UINT8   Revision; // AclRevision
        UINT8   Sbz1;
        UINT16  AclSize;
        UINT16  AceCount;
        UINT16  Sbz2;
    }*PACCESS_CONTROL_LIST;

    
    /* Security descriptor */
    enum SecurityDescriptorControlMask : UINT16
    {
        SeOwnerDefaulted        = 0x0001,
        SeGroupDefaulted        = 0x0002,
        SeDaclPresent           = 0x0004,
        SeDaclDefaulted         = 0x0008,
        SeSaclPresent           = 0x0010,
        SeSaclDefaulted         = 0x0020,
        SeDaclUntrusted         = 0x0040,
        SeServerSecurity        = 0x0080,
        SeDaclAutoInheritReq    = 0x0100,
        SeSaclAutoInheritReq    = 0x0200,
        SeDaclAutoInherited     = 0x0400,
        SeSaclAutoInherited     = 0x0800,
        SeDaclProtected         = 0x1000,
        SeSaclProtected         = 0x2000,
        SeRmControlValid        = 0x4000,
        SeSelfRelative          = 0x8000,
    };

    typedef struct SECURITY_DESCRIPTOR
    {
        enum : UINT8
        {
            SdRevision1 = 1,
            SdRevision  = SdRevision1,
        };

        UINT8   Revision;
        UINT8   Sbz1;
        UINT16  Control;      // SecurityDescriptorControlMask
        UINT32  OwnerOffset;  // SID* Offset
        UINT32  GroupOffset;  // SID* Offset
        UINT32  SaclOffset;   // ACL* Offset
        UINT32  DaclOffset;   // ACL* Offset
    }*PSECURITY_DESCRIPTOR;
#pragma endregion


#pragma region Token
    typedef enum TOKEN_TYPE
    {
        TokenPrimary = 1,
        TokenImpersonation
    }*PTOKEN_TYPE;


    enum TokenAccessMask : ACCESS_MASK
    {
        TokenAssignPrimary          = 0x0001,
        TokenDuplicate              = 0x0002,
        TokenImpersonate            = 0x0004,
        TokenQuery                  = 0x0008,
        TokenQuerySource            = 0x0010,
        TokenAdjustPrivileges       = 0x0020,
        TokenAdjustGroups           = 0x0040,
        TokenAdjustDefault          = 0x0080,
        TokenAdjustSessionId        = 0x0100,

        TokenAllAccess              = (StandardRightsRequired | 0x01FF),

        TokenRead                   = (StandardRightsRequired | TokenQuery),
        TokenWrite                  = (StandardRightsRequired | TokenAdjustPrivileges | TokenAdjustGroups | TokenAdjustDefault),
        TokenExecute                = (StandardRightsExecute),

        TokenTrustConstraintMask    = (StandardRightsRead | TokenQuery | TokenQuerySource),
        TokenAccessPseudoHandle     = (TokenQuery | TokenQuerySource),
    };
    
    typedef enum TOKEN_ELEVATION_TYPE
    {
        TokenElevationTypeDefault = 1,
        TokenElevationTypeFull,
        TokenElevationTypeLimited,
    } *PTOKEN_ELEVATION_TYPE;
    
    typedef struct _TOKEN_USER
    {
        SID_AND_ATTRIBUTES User;
    } TOKEN_USER, *PTOKEN_USER;

    typedef struct _SE_TOKEN_USER
    {
        union
        {
            TOKEN_USER TokenUser;
            SID_AND_ATTRIBUTES User;
        };

        union
        {
            SID Sid;
            UCHAR Buffer[SECURITY_MAX_SID_SIZE];
        };

    } SE_TOKEN_USER, PSE_TOKEN_USER;

#define TOKEN_USER_MAX_SIZE (sizeof(TOKEN_USER) + SECURITY_MAX_SID_SIZE)
    
    typedef struct _TOKEN_GROUPS
    {
        ULONG GroupCount;
        SID_AND_ATTRIBUTES Groups[ANYSIZE_ARRAY];
    } TOKEN_GROUPS, *PTOKEN_GROUPS;

    typedef struct _TOKEN_PRIVILEGES
    {
        ULONG PrivilegeCount;
        LUID_AND_ATTRIBUTES Privileges[ANYSIZE_ARRAY];
    } TOKEN_PRIVILEGES, *PTOKEN_PRIVILEGES;
    
    typedef struct _TOKEN_OWNER
    {
        PSID Owner;
    } TOKEN_OWNER, *PTOKEN_OWNER;

    typedef struct _TOKEN_SOURCE
    {
        enum : UINT32
        {
            TokenSourceLength = 8
        };

        CHAR SourceName[TokenSourceLength];
        LUID SourceIdentifier;
    } TOKEN_SOURCE, *PTOKEN_SOURCE;

    typedef struct _TOKEN_CONTROL
    {
        LUID TokenId;
        LUID AuthenticationId;
        LUID ModifiedId;
        TOKEN_SOURCE TokenSource;
    } TOKEN_CONTROL, *PTOKEN_CONTROL;
#pragma endregion


#pragma region Other
    typedef struct _SECURITY_CLIENT_CONTEXT
    {
        SECURITY_QUALITY_OF_SERVICE SecurityQos;
        PACCESS_TOKEN ClientToken;
        BOOLEAN DirectlyAccessClientToken;
        BOOLEAN DirectAccessEffectiveOnly;
        BOOLEAN ServerIsRemote;
        TOKEN_CONTROL ClientTokenControl;
    } SECURITY_CLIENT_CONTEXT, *PSECURITY_CLIENT_CONTEXT;
#pragma endregion

}

#include "Se\build_7600.inl"
#include "Se\build_7601.inl"
#include "Se\build_9200.inl"
#include "Se\build_9600.inl"
#include "Se\build_10240.inl"
#include "Se\build_10586.inl"
#include "Se\build_14393.inl"
#include "Se\build_15063.inl"
#include "Se\build_16299.inl"
#include "Se\build_17134.inl"
#include "Se\build_17763.inl"
