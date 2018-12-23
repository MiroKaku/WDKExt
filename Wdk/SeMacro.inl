#pragma once


/////////////////////////////////////////////////////////////////////////////
//                                                                         //
// Universal well-known SIDs                                               //
//                                                                         //
//     Null SID                     S-1-0-0                                //
//     World                        S-1-1-0                                //
//     Local                        S-1-2-0                                //
//     Creator Owner ID             S-1-3-0                                //
//     Creator Group ID             S-1-3-1                                //
//     Creator Owner Server ID      S-1-3-2                                //
//     Creator Group Server ID      S-1-3-3                                //
//                                                                         //
//     (Non-unique IDs)             S-1-4                                  //
//                                                                         //
/////////////////////////////////////////////////////////////////////////////


#define Security$NullSidAuthority           {0,0,0,0,0,0}
#define Security$WorldSidAuthority          {0,0,0,0,0,1}
#define Security$LocalSidAuthority          {0,0,0,0,0,2}
#define Security$CreatorSidAuthority        {0,0,0,0,0,3}
#define Security$NonUniqueAuthority         {0,0,0,0,0,4}
#define Security$ResourceManagerAuthority   {0,0,0,0,0,9}


#define Security$NullRid                    (0x00000000L)
#define Security$WorldRid                   (0x00000000L)
#define Security$LocalRid                   (0x00000000L)
#define Security$LocalLogonRid              (0x00000001L)

#define Security$CreatorOwnerRid            (0x00000000L)
#define Security$CreatorGroupRid            (0x00000001L)

#define Security$CreatorOwnerServerRid      (0x00000002L)
#define Security$CreatorGroupServerRid      (0x00000003L)

#define Security$CreatorOwnerRightsRid      (0x00000004L)


///////////////////////////////////////////////////////////////////////////////
//                                                                           //
// NT well-known SIDs                                                        //
//                                                                           //
//     NT Authority            S-1-5                                         //
//     Dialup                  S-1-5-1                                       //
//                                                                           //
//     Network                 S-1-5-2                                       //
//     Batch                   S-1-5-3                                       //
//     Interactive             S-1-5-4                                       //
//     (Logon IDs)             S-1-5-5-X-Y                                   //
//     Service                 S-1-5-6                                       //
//     AnonymousLogon          S-1-5-7       (aka null logon session)        //
//     Proxy                   S-1-5-8                                       //
//     Enterprise DC (EDC)     S-1-5-9       (aka domain controller account) //
//     Self                    S-1-5-10      (self RID)                      //
//     Authenticated User      S-1-5-11      (Authenticated user somewhere)  //
//     Restricted Code         S-1-5-12      (Running restricted code)       //
//     Terminal Server         S-1-5-13      (Running on Terminal Server)    //
//     Remote Logon            S-1-5-14      (Remote Interactive Logon)      //
//     This Organization       S-1-5-15                                      //
//                                                                           //
//     IUser                   S-1-5-17
//     Local System            S-1-5-18                                      //
//     Local Service           S-1-5-19                                      //
//     Network Service         S-1-5-20                                      //
//                                                                           //
//     (NT non-unique IDs)     S-1-5-0x15-... (NT Domain Sids)               //
//                                                                           //
//     (Built-in domain)       S-1-5-0x20                                    //
//                                                                           //
//     (Security Package IDs)  S-1-5-0x40                                    //
//     NTLM Authentication     S-1-5-0x40-10                                 //
//     SChannel Authentication S-1-5-0x40-14                                 //
//     Digest Authentication   S-1-5-0x40-21                                 //
//                                                                           //
//     Other Organization      S-1-5-1000    (>=1000 can not be filtered)    //
//                                                                           //
//                                                                           //
// NOTE: the relative identifier values (RIDs) determine which security      //
//       boundaries the SID is allowed to cross.  Before adding new RIDs,    //
//       a determination needs to be made regarding which range they should  //
//       be added to in order to ensure proper "SID filtering"               //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////


#define Security$NtAuthority                {0,0,0,0,0,5}   // ntifs

#define Security$DialupRid                  (0x00000001L)
#define Security$NetworkRid                 (0x00000002L)
#define Security$BatchRid                   (0x00000003L)
#define Security$InteractiveRid             (0x00000004L)

#define Security$LogonIdsRid                (0x00000005L)
#define Security$LogonIdsRidCount           (3L)

#define Security$ServiceRid                 (0x00000006L)
#define Security$AnonymousLogonRid          (0x00000007L)
#define Security$ProxyRid                   (0x00000008L)
#define Security$EnterpriesControllersRid   (0x00000009L)
#define Security$ServerLogonRid             Security$EnterpriesControllersRid
#define Security$PrincipalSelfRid           (0x0000000AL)
#define Security$AuthenticatedUserRid       (0x0000000BL)
#define Security$RestrictedCodeRid          (0x0000000CL)
#define Security$TerminalServerRid          (0x0000000DL)
#define Security$RemoteLogonRid             (0x0000000EL)
#define Security$ThisOrganizationRid        (0x0000000FL)
#define Security$IUserRid                   (0x00000011L)
#define Security$LocalSystemRid             (0x00000012L)
#define Security$LocalServiceRid            (0x00000013L)
#define Security$NetworkServiceRid          (0x00000014L)

#define Security$NtNonUnique                (0x00000015L)
#define Security$NtNonUniqueSubAuthCount    (3L)

#define Security$EnterpriseReadonlyControllersRid (0x00000016L)

#define Security$BuiltinDomainRid           (0x00000020L)
#define Security$WriteRestrictedCodeRid     (0x00000021L)


#define Security$PackageBaseRid             (0x00000040L)
#define Security$PackageRidCount            (2L)
#define Security$PackageNtlmRid             (0x0000000AL)
#define Security$PackageSchannelRid         (0x0000000EL)
#define Security$PackageDigestRid           (0x00000015L)

#define Security$CredTypeBaseRid            (0x00000041L)
#define Security$CredTypeRidCount           (2L)
#define Security$CredTypeThisOrgCertRid     (0x00000001L)

#define Security$MinBaseRid                 (0x00000050L)

#define Security$ServiceIdBaseRid           (0x00000050L)
#define Security$ServiceIdRidCount          (6L)

#define Security$ReservedIdBaseRid          (0x00000051L)

#define Security$AppPoolIdBaseRid           (0x00000052L)
#define Security$AppPoolIdRidCount          (6L)

#define Security$VirtualServerIdBaseRid     (0x00000053L)
#define Security$VirtualServerIdRidCount    (6L)

#define Security$UserModeDriverHostIdBaseRid  (0x00000054L)
#define Security$UserModeDriverHostIdRidCount (6L)

#define Security$CloudInfrastructureServicesIdBaseRid  (0x00000055L)
#define Security$CloudInfrastructureServicesIdRidCount (6L)

#define Security$WmiHostIdBaseRid           (0x00000056L)
#define Security$WmiHostIdRidCount          (6L)

#define Security$TaskIdBaseRid              (0x00000057L)

#define Security$NfsIdBaseRid               (0x00000058L)

#define Security$ComIdBaseRid               (0x00000059L)

#define Security$WindowManagerBaseRid       (0x0000005AL)

#define Security$RdvGfxBaseRid              (0x0000005BL)

#define Security$DashostIdBaseRid           (0x0000005CL)
#define Security$DashostIdRidCount          (6L)

#define Security$UserManagerIdBaseRid       (0x0000005DL)
#define Security$UserManagerIdRidCount      (6L)

#define Security$WinRMIdBaseRid             (0x0000005EL)
#define Security$WinRMIdRidCount            (6L)

#define Security$CCGIdBaseRid               (0x0000005FL)
#define Security$UMFDBaseRid                (0x00000060L)

#define Security$VirualAccountIdRidCount    (6L)

//
// Virtual account logon is not limited to inbox callers.  Reserve base RID 0x6F for application usage.
//

#define Security$MaxBaseRid                 (0x0000006FL)
#define Security$MaxAlwaysFiltered          (0x000003E7L)
#define Security$MinNeverFiltered           (0x000003E8L)

#define Security$OtherOrganizationRid       (0x000003E8L)

//
//Service SID type RIDs are in the range 0x50- 0x6F.  Therefore, we are giving  the next available RID to Windows Mobile team.
//
#define Security$WindowSmobileIdBaseRid     (0x00000070L)

//
// Installer Capability Group Sid related. Currently Base RID is same as LOCAL DOMAIN.
//
#define Security$InstallerGroupCapabilityBase       (0x20)
#define Security$InstallerGroupCapabilityRidCount   (9)

// Note: This is because the App Capability Rid is S-1-15-3-1024-...
//       whereas the service group rid is          S-1-5-32-...
//	The number of RIDs from hash (8) are the same for both
#define Security$InstallerCapabilityRidCount        (10)

//
//Well-known group for local accounts
//
#define Security$LocalAccountRid            (0x00000071L)
#define Security$LocalAccountAndAdminRid    (0x00000072L)


/////////////////////////////////////////////////////////////////////////////
//                                                                         //
// well-known domain relative sub-authority values (RIDs)...               //
//                                                                         //
/////////////////////////////////////////////////////////////////////////////

#define Domain$GroupRid$AuthorizationDataIsCompounded           (0x000001F0L)
#define Domain$GroupRid$AuthorizationDataContainsClaims         (0x000001F1L)
#define Domain$GroupRid$EnterpriseReadOnlyDomainControllers     (0x000001F2L)

#define Domain$ForestUserRidMax                     (0x000001F3L)

// Well-known users ...

#define Domain$UserRid$Admin                        (0x000001F4L)
#define Domain$UserRid$Guest                        (0x000001F5L)
#define Domain$UserRid$Krbtgt                       (0x000001F6L)
#define Domain$UserRid$DefaultAccount               (0x000001F7L)
#define Domain$UserRid$WDAGAccount                  (0x000001F8L) // Windows Defender Application Guard

#define Domain$UserRid$Max                          (0x000003E7L)

// well-known groups ...

#define Domain$GroupRid$Admins                      (0x00000200L)
#define Domain$GroupRid$Users                       (0x00000201L)
#define Domain$GroupRid$Guests                      (0x00000202L)
#define Domain$GroupRid$Computers                   (0x00000203L)
#define Domain$GroupRid$Controllers                 (0x00000204L)
#define Domain$GroupRid$CertAdmins                  (0x00000205L)
#define Domain$GroupRid$SchemaAdmins                (0x00000206L)
#define Domain$GroupRid$EnterpriseAdmins            (0x00000207L)
#define Domain$GroupRid$PolicyAdmins                (0x00000208L)
#define Domain$GroupRid$ReadonlyControllers         (0x00000209L)
#define Domain$GroupRid$ClonerableControllers       (0x0000020AL)
#define Domain$GroupRid$CdcReserved                 (0x0000020CL)
#define Domain$GroupRid$ProtectedUsers              (0x0000020DL)
#define Domain$GroupRid$KeyAdmins                   (0x0000020EL)
#define Domain$GroupRid$EnterpriseKeyAdmins         (0x0000020FL)

// well-known aliases ...

#define Domain$AliasRid$Admins                      (0x00000220L)
#define Domain$AliasRid$Users                       (0x00000221L)
#define Domain$AliasRid$Guests                      (0x00000222L)
#define Domain$AliasRid$PowerUsers                  (0x00000223L)

#define Domain$AliasRid$AccountOps                  (0x00000224L)
#define Domain$AliasRid$SystemOps                   (0x00000225L)
#define Domain$AliasRid$PrintOps                    (0x00000226L)
#define Domain$AliasRid$BackupOps                   (0x00000227L)

#define Domain$AliasRid$Replicator                  (0x00000228L)
#define Domain$AliasRid$RasServers                  (0x00000229L)
#define Domain$AliasRid$Prew2kCompAccess            (0x0000022AL)
#define Domain$AliasRid$RemoteDesktopUsers          (0x0000022BL)
#define Domain$AliasRid$NetworkConfigurationOps     (0x0000022CL)
#define Domain$AliasRid$IncomingForestTrustBuilders (0x0000022DL)

#define Domain$AliasRid$MonitoringUsers             (0x0000022EL)
#define Domain$AliasRid$LoggingUsers                (0x0000022FL)
#define Domain$AliasRid$AuthorizationAccess         (0x00000230L)
#define Domain$AliasRid$TsLicenseServers            (0x00000231L)
#define Domain$AliasRid$DcomUsers                   (0x00000232L)
#define Domain$AliasRid$IUsers                      (0x00000238L)
#define Domain$AliasRid$CryptoOperators             (0x00000239L)
#define Domain$AliasRid$CacheablePrincipalsGroup    (0x0000023BL)
#define Domain$AliasRid$NonCacheablePrincipalsGroup (0x0000023CL)
#define Domain$AliasRid$EventLogReadersGroup        (0x0000023DL)
#define Domain$AliasRid$CertsvcDcomAccessGroup      (0x0000023EL)
#define Domain$AliasRid$RdsRemoteAccessServers      (0x0000023FL)
#define Domain$AliasRid$RdsEndpointServers          (0x00000240L)
#define Domain$AliasRid$RdsManagementServers        (0x00000241L)
#define Domain$AliasRid$HyperVAdmins                (0x00000242L)
#define Domain$AliasRid$AccessControlAssistanceOps  (0x00000243L)
#define Domain$AliasRid$RemoveManagementUsers       (0x00000244L)
#define Domain$AliasRid$DefaultAccount              (0x00000245L)
#define Domain$AliasRid$StorageReplicaAdmins        (0x00000246L)
#define Domain$AliasRid$DeviceOwners                (0x00000247L)

//
// Application Package Authority.
//

#define Security$AppPackageAuthority        {0,0,0,0,0,15}

#define Security$AppPackageBaseRid          (0x00000002L)
#define Security$BuiltinAppPackageRidCount  (2L)
#define Security$AppPackageRidCount         (8L)
#define Security$CapabilityBaseRid          (0x00000003L)
#define Security$CapabilityAppRid           (0x000000400)
#define Security$BuiltinCapabilityRidCount  (2L)
#define Security$CapabilityRidCount         (5L)
#define Security$ParentPackageRidCount      (Security$AppPackageRidCount)
#define Security$ChildPackageRidCount       (12L)

//
// Built-in Packages.
//

#define Security$BuiltinPackage$AnyPackage           (0x00000001L)
#define Security$BuiltinPackage$AnyRestrictedPackage (0x00000002L)

//
// Built-in Capabilities.
//

#define Security$Capability$InternetClient              (0x00000001L)
#define Security$Capability$InternetClientServer        (0x00000002L)
#define Security$Capability$PrivateNetworkClientServer  (0x00000003L)
#define Security$Capability$PicturesLibrary             (0x00000004L)
#define Security$Capability$VideosLibrary               (0x00000005L)
#define Security$Capability$MusicLibrary                (0x00000006L)
#define Security$Capability$DocumentsLibrary            (0x00000007L)
#define Security$Capability$EnterpriseAuthentication    (0x00000008L)
#define Security$Capability$SharedUserCertificates      (0x00000009L)
#define Security$Capability$RemovableStorage            (0x0000000AL)
#define Security$Capability$Appointments                (0x0000000BL)
#define Security$Capability$Contacts                    (0x0000000CL)

#define Security$Capability$InternetExplorer            (0x00001000L)

//
// Mandatory Label Authority.
//

#define Security$MandatoryLabelAuthority          {0,0,0,0,0,16}
#define Security$MandatoryUntrustedRid            (0x00000000L)
#define Security$MandatoryLowRid                  (0x00001000L)
#define Security$MandatoryMediumRid               (0x00002000L)
#define Security$MandatoryMediusPlusRid           (Security$MandatoryMediumRid + 0x100)
#define Security$MandatoryHighRid                 (0x00003000L)
#define Security$MandatorySystemRid               (0x00004000L)
#define Security$MandatoryProtectedProcessRid     (0x00005000L)

//
// SECURITY_MANDATORY_MAXIMUM_USER_RID is the highest RID that
// can be set by a usermode caller.
//

#define Security$MandatoryMaximumUserRid    Security$MandatorySystemRid

#define Mandatory$LevelToRid(IL)            (IL  * 0x1000)
#define Mandatory$RidToLevel(Rid)           (Rid / 0x1000)

#define Security$ScopedPolicyIdAuthority    {0,0,0,0,0,17}

//
// Authentication Authority
//

#define Security$Authentication$Authority                   {0,0,0,0,0,18}
#define Security$Authentication$AuthorityRidCound           (1L)
#define Security$Authentication$AuthorityAssertedRid        (0x00000001L)
#define Security$Authentication$ServiceAssertedRid          (0x00000002L)
#define Security$Authentication$FreshKeyAuthRid             (0x00000003L)
#define Security$Authentication$KeyTrustRid                 (0x00000004L)
#define Security$Authentication$KeyPropertyMFARid           (0x00000005L)
#define Security$Authentication$KeyPropertyAttestationRid   (0x00000006L)

//
// Process Trust Authority
//

#define Security$ProcessTrustAuthority                  {0,0,0,0,0,19}
#define Security$ProcessTrustAuthorityRidCount          (2L)

#define Security$ProcessProtectionType$FullRid          (0x00000400L)
#define Security$ProcessProtectionType$LiteRid          (0x00000200L)
#define Security$ProcessProtectionType$NoneRid          (0x00000000L)

#define Security$ProcessProtectionLevel$WintcbRid       (0x00002000L)
#define Security$ProcessProtectionLevel$WindowsRid      (0x00001000L)
#define Security$ProcessProtectionLevel$AppRid          (0x00000800L)
#define Security$ProcessProtectionLevel$AntimalwareRid  (0x00000600L)
#define Security$ProcessProtectionLevel$AuthenticodeRid (0x00000400L)
#define Security$ProcessProtectionLevel$NoneRid         (0x00000000L)

//
// Trusted Installer RIDs
//

#define Security$TrustedInstallerRid1 956008885
#define Security$TrustedInstallerRid2 3418522649
#define Security$TrustedInstallerRid3 1831038044
#define Security$TrustedInstallerRid4 1853292631
#define Security$TrustedInstallerRid5 2271478464

//
// Allocate the System Luid.  The first 1000 LUIDs are reserved.
// Use #999 here (0x3e7 = 999)
//

#define Security$SystemLuid             { 0x3e7, 0x0 }
#define Security$AnonymousLogonLuid     { 0x3e6, 0x0 }
#define Security$LocalServiceLuid       { 0x3e5, 0x0 }
#define Security$NetworkServiceLuid     { 0x3e4, 0x0 }
#define Security$IUserLuid              { 0x3e3, 0x0 }
#define Security$ProtectedToSystemLuid  { 0x3e2, 0x0 }
