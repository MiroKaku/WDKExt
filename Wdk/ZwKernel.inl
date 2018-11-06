#pragma once
#include "ZwStruct.inl"


namespace wdk
{
    extern"C"
    {

        NTSTATUS
            NTAPI
            ZwAdjustPrivilegesToken(
                _In_ HANDLE TokenHandle,
                _In_ BOOLEAN DisableAllPrivileges,
                _In_opt_ PTOKEN_PRIVILEGES NewState,
                _In_ ULONG BufferLength,
                _Out_writes_bytes_to_opt_(BufferLength, *ReturnLength) PTOKEN_PRIVILEGES PreviousState,
                _Out_ _When_(PreviousState == NULL, _Out_opt_) PULONG ReturnLength
            );


        NTSTATUS
            NTAPI
            ZwAlertThread(
                _In_ HANDLE ThreadHandle
            );


        NTSTATUS
            NTAPI
            ZwAllocateVirtualMemory(
                _In_ HANDLE ProcessHandle,
                _Inout_ _At_(*BaseAddress, _Readable_bytes_(*RegionSize) _Writable_bytes_(*RegionSize) _Post_readable_byte_size_(*RegionSize)) PVOID *BaseAddress,
                _In_ ULONG_PTR ZeroBits,
                _Inout_ PSIZE_T RegionSize,
                _In_ ULONG AllocationType,
                _In_ ULONG Protect
            );


        NTSTATUS
            NTAPI
            ZwAssignProcessToJobObject(
                _In_ HANDLE JobHandle,
                _In_ HANDLE ProcessHandle
            );


        NTSTATUS
            NTAPI
            ZwAssociateWaitCompletionPacket(
                _In_ HANDLE WaitCompletionPacketHandle,
                _In_ HANDLE IoCompletionHandle,
                _In_ HANDLE TargetObjectHandle,
                _In_opt_ PVOID KeyContext,
                _In_opt_ PVOID ApcContext,
                _In_ NTSTATUS IoStatus,
                _In_ ULONG_PTR IoStatusInformation,
                _Out_opt_ PBOOLEAN AlreadySignaled
            );


        NTSTATUS
            NTAPI
            ZwCancelIoFile(
                _In_ HANDLE FileHandle,
                _Out_ PIO_STATUS_BLOCK IoStatusBlock
            );


        NTSTATUS
            NTAPI
            ZwCancelIoFileEx(
                _In_ HANDLE FileHandle,
                _In_opt_ PIO_STATUS_BLOCK IoRequestToCancel,
                _Out_ PIO_STATUS_BLOCK IoStatusBlock
            );


        NTSTATUS
            NTAPI
            ZwCancelSynchronousIoFile(
                _In_ HANDLE ThreadHandle,
                _In_opt_ PIO_STATUS_BLOCK IoRequestToCancel,
                _Out_ PIO_STATUS_BLOCK IoStatusBlock
            );


        NTSTATUS
            NTAPI
            ZwCancelWaitCompletionPacket(
                _In_ HANDLE WaitCompletionPacketHandle,
                _In_ BOOLEAN RemoveSignaledPacket
            );


        NTSTATUS
            NTAPI
            ZwClearEvent(
                _In_ HANDLE EventHandle
            );


        NTSTATUS
            NTAPI
            ZwCompareTokens(
                _In_ HANDLE FirstTokenHandle,
                _In_ HANDLE SecondTokenHandle,
                _Out_ PBOOLEAN Equal
            );


        NTSTATUS
            NTAPI
            ZwCreateEvent(
                _Out_ PHANDLE EventHandle,
                _In_ ACCESS_MASK DesiredAccess,
                _In_opt_ POBJECT_ATTRIBUTES ObjectAttributes,
                _In_ EVENT_TYPE EventType,
                _In_ BOOLEAN InitialState
            );


        NTSTATUS
            NTAPI
            ZwCreateIoCompletion(
                _Out_ PHANDLE IoCompletionHandle,
                _In_ ACCESS_MASK DesiredAccess,
                _In_opt_ POBJECT_ATTRIBUTES ObjectAttributes,
                _In_opt_ ULONG Count
            );


        NTSTATUS
            NTAPI
            ZwCreateJobObject(
                _Out_ PHANDLE JobHandle,
                _In_ ACCESS_MASK DesiredAccess,
                _In_opt_ POBJECT_ATTRIBUTES ObjectAttributes
            );


        NTSTATUS
            NTAPI
            ZwCreateKeyedEvent(
                _Out_ PHANDLE KeyedEventHandle,
                _In_ ACCESS_MASK DesiredAccess,
                _In_opt_ POBJECT_ATTRIBUTES ObjectAttributes,
                _In_ ULONG Flags
            );


        NTSTATUS
            NTAPI
            ZwCreatePartition(
                _Out_ PHANDLE PartitionHandle,
                _In_ ACCESS_MASK DesiredAccess,
                _In_opt_ POBJECT_ATTRIBUTES ObjectAttributes,
                _In_ ULONG PreferredNode
            );


        NTSTATUS
            NTAPI
            ZwCreateProcessEx(
                _Out_ PHANDLE ProcessHandle,
                _In_ ACCESS_MASK DesiredAccess,
                _In_opt_ POBJECT_ATTRIBUTES ObjectAttributes,
                _In_ HANDLE ParentProcess,
                _In_ ULONG Flags,
                _In_opt_ HANDLE SectionHandle,
                _In_opt_ HANDLE DebugPort,
                _In_opt_ HANDLE ExceptionPort,
                _In_ ULONG JobMemberLevel
            );


        NTSTATUS
            NTAPI
            ZwCreateProfileEx(
                _Out_ PHANDLE ProfileHandle,
                _In_opt_ HANDLE Process,
                _In_ PVOID ProfileBase,
                _In_ SIZE_T ProfileSize,
                _In_ ULONG BucketSize,
                _In_reads_bytes_(BufferSize) PULONG Buffer,
                _In_ ULONG BufferSize,
                _In_ KPROFILE_SOURCE ProfileSource,
                _In_ USHORT GroupCount,
                _In_reads_(GroupCount) PGROUP_AFFINITY GroupAffinity
            );

        
        NTSTATUS
            NTAPI
            ZwCreateSymbolicLinkObject(
                _Out_ PHANDLE LinkHandle,
                _In_ ACCESS_MASK DesiredAccess,
                _In_ POBJECT_ATTRIBUTES ObjectAttributes,
                _In_ PUNICODE_STRING LinkTarget
            );


        NTSTATUS
            NTAPI
            ZwCreateTransaction(
                _Out_ PHANDLE TransactionHandle,
                _In_ ACCESS_MASK DesiredAccess,
                _In_opt_ POBJECT_ATTRIBUTES ObjectAttributes,
                _In_opt_ LPGUID Uow,
                _In_opt_ HANDLE TmHandle,
                _In_opt_ ULONG CreateOptions,
                _In_opt_ ULONG IsolationLevel,
                _In_opt_ ULONG IsolationFlags,
                _In_opt_ PLARGE_INTEGER Timeout,
                _In_opt_ PUNICODE_STRING Description
            );


        NTSTATUS
            NTAPI
            ZwCreateWaitCompletionPacket(
                _Out_ PHANDLE WaitCompletionPacketHandle,
                _In_ ACCESS_MASK DesiredAccess,
                _In_opt_ POBJECT_ATTRIBUTES ObjectAttributes
            );


        NTSTATUS
            NTAPI
            ZwDeleteFile(
                _In_ POBJECT_ATTRIBUTES ObjectAttributes
            );


        NTSTATUS
            NTAPI
            ZwDuplicateObject(
                _In_ HANDLE SourceProcessHandle,
                _In_ HANDLE SourceHandle,
                _In_opt_ HANDLE TargetProcessHandle,
                _Out_opt_ PHANDLE TargetHandle,
                _In_ ACCESS_MASK DesiredAccess,
                _In_ ULONG HandleAttributes,
                _In_ ULONG Options
            );


        NTSTATUS
            NTAPI
            ZwDuplicateToken(
                _In_ HANDLE ExistingTokenHandle,
                _In_ ACCESS_MASK DesiredAccess,
                _In_ POBJECT_ATTRIBUTES ObjectAttributes,
                _In_ BOOLEAN EffectiveOnly,
                _In_ TOKEN_TYPE TokenType,
                _Out_ PHANDLE NewTokenHandle
            );


        NTSTATUS
            NTAPI
            ZwEnumerateBootEntries(
                _Out_writes_bytes_opt_(*BufferLength) PVOID Buffer,
                _Inout_ PULONG BufferLength
            );


        NTSTATUS
            NTAPI
            ZwEnumerateDriverEntries(
                _Out_writes_bytes_opt_(*BufferLength) PVOID Buffer,
                _Inout_ PULONG BufferLength
            );


        NTSTATUS
            NTAPI
            ZwFlushBuffersFile(
                _In_ HANDLE FileHandle,
                _Out_ PIO_STATUS_BLOCK IoStatusBlock
            );


        NTSTATUS
            NTAPI
            ZwFlushBuffersFileEx(
                _In_ HANDLE FileHandle,
                _In_ ULONG Flags,
                _In_reads_bytes_(ParametersSize) PVOID Parameters,
                _In_ ULONG ParametersSize,
                _Out_ PIO_STATUS_BLOCK IoStatusBlock
            );


        NTSTATUS
            NTAPI
            ZwFlushInstructionCache(
                _In_ HANDLE ProcessHandle,
                _In_opt_ PVOID BaseAddress,
                _In_ SIZE_T Length
            );

        
        NTSTATUS
            NTAPI
            ZwFreeVirtualMemory(
                _In_ HANDLE ProcessHandle,
                _Inout_ PVOID *BaseAddress,
                _Inout_ PSIZE_T RegionSize,
                _In_ ULONG FreeType
            );


        NTSTATUS
            NTAPI
            ZwFsControlFile(
                _In_ HANDLE FileHandle,
                _In_opt_ HANDLE Event,
                _In_opt_ PIO_APC_ROUTINE ApcRoutine,
                _In_opt_ PVOID ApcContext,
                _Out_ PIO_STATUS_BLOCK IoStatusBlock,
                _In_ ULONG FsControlCode,
                _In_reads_bytes_opt_(InputBufferLength) PVOID InputBuffer,
                _In_ ULONG InputBufferLength,
                _Out_writes_bytes_opt_(OutputBufferLength) PVOID OutputBuffer,
                _In_ ULONG OutputBufferLength
            );


        NTSTATUS
            NTAPI
            ZwGetCachedSigningLevel(
                _In_ HANDLE File,
                _Out_ PULONG Flags,
                _Out_ PSE_SIGNING_LEVEL SigningLevel,
                _Out_writes_bytes_to_opt_(*ThumbprintSize, *ThumbprintSize) PUCHAR Thumbprint,
                _Inout_opt_ PULONG ThumbprintSize,
                _Out_opt_ PULONG ThumbprintAlgorithm
            );


        NTSTATUS
            NTAPI
            ZwGetNextProcess(
                _In_ HANDLE ProcessHandle,
                _In_ ACCESS_MASK DesiredAccess,
                _In_ ULONG HandleAttributes,
                _In_ ULONG Flags,
                _Out_ PHANDLE NewProcessHandle
            );


        NTSTATUS
            NTAPI
            ZwGetNextThread(
                _In_ HANDLE ProcessHandle,
                _In_ HANDLE ThreadHandle,
                _In_ ACCESS_MASK DesiredAccess,
                _In_ ULONG HandleAttributes,
                _In_ ULONG Flags,
                _Out_ PHANDLE NewThreadHandle
            );


        NTSTATUS
            NTAPI
            ZwImpersonateAnonymousToken(
                _In_ HANDLE ThreadHandle
            );


        NTSTATUS
            NTAPI
            ZwIsProcessInJob(
                _In_ HANDLE ProcessHandle,
                _In_opt_ HANDLE JobHandle
            );


        NTSTATUS
            NTAPI
            ZwLoadKey(
                _In_ POBJECT_ATTRIBUTES TargetKey,
                _In_ POBJECT_ATTRIBUTES SourceFile
            );


        NTSTATUS
            NTAPI
            ZwLoadKeyEx(
                _In_ POBJECT_ATTRIBUTES TargetKey,
                _In_ POBJECT_ATTRIBUTES SourceFile,
                _In_ ULONG Flags,
                _In_opt_ HANDLE TrustClassKey,
                _In_opt_ HANDLE Event,
                _In_opt_ ACCESS_MASK DesiredAccess,
                _Out_opt_ PHANDLE RootHandle,
                _Out_opt_ PIO_STATUS_BLOCK IoStatus
            );


        NTSTATUS
            NTAPI
            ZwLockFile(
                _In_ HANDLE FileHandle,
                _In_opt_ HANDLE Event,
                _In_opt_ PIO_APC_ROUTINE ApcRoutine,
                _In_opt_ PVOID ApcContext,
                _Out_ PIO_STATUS_BLOCK IoStatusBlock,
                _In_ PLARGE_INTEGER ByteOffset,
                _In_ PLARGE_INTEGER Length,
                _In_ ULONG Key,
                _In_ BOOLEAN FailImmediately,
                _In_ BOOLEAN ExclusiveLock
            );


        NTSTATUS
            NTAPI
            ZwLockProductActivationKeys(
                _Inout_opt_ ULONG *pPrivateVer,
                _Out_opt_ ULONG *pSafeMode
            );


        NTSTATUS
            NTAPI
            ZwLockVirtualMemory(
                _In_ HANDLE ProcessHandle,
                _Inout_ PVOID *BaseAddress,
                _Inout_ PSIZE_T RegionSize,
                _In_ ULONG MapType
            );

        NTSTATUS
            NTAPI
            ZwManagePartition(
                _In_ MEMORY_PARTITION_INFORMATION_CLASS PartitionInformationClass,
                _In_ PVOID PartitionInformation,
                _In_ ULONG PartitionInformationLength
            );


        NTSTATUS
            NTAPI
            ZwNotifyChangeDirectoryFile(
                _In_ HANDLE FileHandle,
                _In_opt_ HANDLE Event,
                _In_opt_ PIO_APC_ROUTINE ApcRoutine,
                _In_opt_ PVOID ApcContext,
                _Out_ PIO_STATUS_BLOCK IoStatusBlock,
                _Out_writes_bytes_(Length) PVOID Buffer, // FILE_NOTIFY_INFORMATION
                _In_ ULONG Length,
                _In_ ULONG CompletionFilter,
                _In_ BOOLEAN WatchTree
            );


        NTSTATUS
            NTAPI
            ZwNotifyChangeDirectoryFileEx(
                _In_     HANDLE                             FileHandle,
                _In_opt_ HANDLE                             Event,
                _In_opt_ PIO_APC_ROUTINE                    ApcRoutine,
                _In_opt_ PVOID                              ApcContext,
                _Out_    PIO_STATUS_BLOCK                   IoStatusBlock,
                _Out_writes_bytes_(Length) PVOID            Buffer,
                _In_     ULONG                              Length,
                _In_     ULONG                              CompletionFilter,
                _In_     BOOLEAN                            WatchTree,
                _In_opt_ DIRECTORY_NOTIFY_INFORMATION_CLASS DirectoryNotifyInformationClass
            );


        NTSTATUS
            NTAPI
            ZwNotifyChangeKey(
                _In_ HANDLE KeyHandle,
                _In_opt_ HANDLE Event,
                _In_opt_ PIO_APC_ROUTINE ApcRoutine,
                _In_opt_ PVOID ApcContext,
                _Out_ PIO_STATUS_BLOCK IoStatusBlock,
                _In_ ULONG CompletionFilter,
                _In_ BOOLEAN WatchTree,
                _Out_writes_bytes_opt_(BufferSize) PVOID Buffer,
                _In_ ULONG BufferSize,
                _In_ BOOLEAN Asynchronous
            );


        NTSTATUS
            NTAPI
            ZwNotifyChangeSession(
                _In_ HANDLE SessionHandle,
                _In_ ULONG ChangeSequenceNumber,
                _In_ PLARGE_INTEGER ChangeTimeStamp,
                _In_ IO_SESSION_EVENT Event,
                _In_ IO_SESSION_STATE NewState,
                _In_ IO_SESSION_STATE PreviousState,
                _In_reads_bytes_opt_(PayloadSize) PVOID Payload,
                _In_ ULONG PayloadSize
            );


        NTSTATUS
            NTAPI
            ZwOpenDirectoryObject(
                _Out_ PHANDLE DirectoryHandle,
                _In_ ACCESS_MASK DesiredAccess,
                _In_ POBJECT_ATTRIBUTES ObjectAttributes
            );


        NTSTATUS
            NTAPI
            ZwOpenIoCompletion(
                _Out_ PHANDLE IoCompletionHandle,
                _In_ ACCESS_MASK DesiredAccess,
                _In_ POBJECT_ATTRIBUTES ObjectAttributes
            );


        NTSTATUS
            NTAPI
            ZwOpenJobObject(
                _Out_ PHANDLE JobHandle,
                _In_ ACCESS_MASK DesiredAccess,
                _In_ POBJECT_ATTRIBUTES ObjectAttributes
            );


        NTSTATUS
            NTAPI
            ZwOpenPartition(
                _Out_ PHANDLE PartitionHandle,
                _In_ ACCESS_MASK DesiredAccess,
                _In_ POBJECT_ATTRIBUTES ObjectAttributes
            );


        NTSTATUS
            NTAPI
            ZwOpenProcessToken(
                _In_ HANDLE ProcessHandle,
                _In_ ACCESS_MASK DesiredAccess,
                _Out_ PHANDLE TokenHandle
            );


        NTSTATUS
            NTAPI
            ZwOpenProcessTokenEx(
                _In_ HANDLE ProcessHandle,
                _In_ ACCESS_MASK DesiredAccess,
                _In_ ULONG HandleAttributes,
                _Out_ PHANDLE TokenHandle
            );


        NTSTATUS
            NTAPI
            ZwOpenSession(
                _Out_ PHANDLE SessionHandle,
                _In_ ACCESS_MASK DesiredAccess,
                _In_ POBJECT_ATTRIBUTES ObjectAttributes
            );


        NTSTATUS
            NTAPI
            ZwOpenThread(
                _Out_ PHANDLE ThreadHandle,
                _In_ ACCESS_MASK DesiredAccess,
                _In_ POBJECT_ATTRIBUTES ObjectAttributes,
                _In_opt_ PCLIENT_ID ClientId
            );


        NTSTATUS
            NTAPI
            ZwOpenThreadToken(
                _In_ HANDLE ThreadHandle,
                _In_ ACCESS_MASK DesiredAccess,
                _In_ BOOLEAN OpenAsSelf,
                _Out_ PHANDLE TokenHandle
            );


        NTSTATUS
            NTAPI
            ZwOpenThreadTokenEx(
                _In_ HANDLE ThreadHandle,
                _In_ ACCESS_MASK DesiredAccess,
                _In_ BOOLEAN OpenAsSelf,
                _In_ ULONG HandleAttributes,
                _Out_ PHANDLE TokenHandle
            );


        NTSTATUS
            NTAPI
            ZwOpenTransaction(
                _Out_ PHANDLE TransactionHandle,
                _In_ ACCESS_MASK DesiredAccess,
                _In_ POBJECT_ATTRIBUTES ObjectAttributes,
                _In_ LPGUID Uow,
                _In_opt_ HANDLE TmHandle
            );


        NTSTATUS
            NTAPI
            ZwPrePrepareComplete(
                _In_ HANDLE EnlistmentHandle,
                _In_opt_ PLARGE_INTEGER TmVirtualClock
            );


        NTSTATUS
            NTAPI
            ZwPrepareComplete(
                _In_ HANDLE EnlistmentHandle,
                _In_opt_ PLARGE_INTEGER TmVirtualClock
            );


        NTSTATUS
            NTAPI
            ZwPropagationComplete(
                _In_ HANDLE ResourceManagerHandle,
                _In_ ULONG RequestCookie,
                _In_ ULONG BufferLength,
                _In_ PVOID Buffer
            );


        NTSTATUS
            NTAPI
            ZwPropagationFailed(
                _In_ HANDLE ResourceManagerHandle,
                _In_ ULONG RequestCookie,
                _In_ NTSTATUS PropStatus
            );


        NTSTATUS
            NTAPI
            ZwProtectVirtualMemory(
                _In_ HANDLE ProcessHandle,
                _Inout_ PVOID *BaseAddress,
                _Inout_ PSIZE_T RegionSize,
                _In_ ULONG NewProtect,
                _Out_ PULONG OldProtect
            );


        NTSTATUS
            NTAPI
            ZwPulseEvent(
                _In_ HANDLE EventHandle,
                _Out_opt_ PLONG PreviousState
            );


        NTSTATUS
            NTAPI
            ZwQueryDefaultLocale(
                _In_ BOOLEAN UserProfile,
                _Out_ PLCID DefaultLocaleId
            );


        NTSTATUS
            NTAPI
            ZwQueryDefaultUILanguage(
                _Out_ LANGID *DefaultUILanguageId
            );


        NTSTATUS
            NTAPI
            ZwQueryDirectoryFile(
                _In_ HANDLE FileHandle,
                _In_opt_ HANDLE Event,
                _In_opt_ PIO_APC_ROUTINE ApcRoutine,
                _In_opt_ PVOID ApcContext,
                _Out_ PIO_STATUS_BLOCK IoStatusBlock,
                _Out_writes_bytes_(Length) PVOID FileInformation,
                _In_ ULONG Length,
                _In_ FILE_INFORMATION_CLASS FileInformationClass,
                _In_ BOOLEAN ReturnSingleEntry,
                _In_opt_ PUNICODE_STRING FileName,
                _In_ BOOLEAN RestartScan
            );


        NTSTATUS
            NTAPI
            ZwQueryDirectoryFileEx(
                _In_     HANDLE                 FileHandle,
                _In_opt_ HANDLE                 Event,
                _In_opt_ PIO_APC_ROUTINE        ApcRoutine,
                _In_opt_ PVOID                  ApcContext,
                _Out_    PIO_STATUS_BLOCK       IoStatusBlock,
                _Out_    PVOID                  FileInformation,
                _In_     ULONG                  Length,
                _In_     FILE_INFORMATION_CLASS FileInformationClass,
                _In_     ULONG                  QueryFlags,
                _In_opt_ PUNICODE_STRING        FileName
            );

        NTSTATUS
            NTAPI
            ZwQueryDirectoryObject(
                _In_ HANDLE DirectoryHandle,
                _Out_writes_bytes_opt_(Length) PVOID Buffer,
                _In_ ULONG Length,
                _In_ BOOLEAN ReturnSingleEntry,
                _In_ BOOLEAN RestartScan,
                _Inout_ PULONG Context,
                _Out_opt_ PULONG ReturnLength
            );


        NTSTATUS
            NTAPI
            ZwQueryEaFile(
                _In_ HANDLE FileHandle,
                _Out_ PIO_STATUS_BLOCK IoStatusBlock,
                _Out_writes_bytes_(Length) PVOID Buffer,
                _In_ ULONG Length,
                _In_ BOOLEAN ReturnSingleEntry,
                _In_reads_bytes_opt_(EaListLength) PVOID EaList,
                _In_ ULONG EaListLength,
                _In_opt_ PULONG EaIndex,
                _In_ BOOLEAN RestartScan
            );

        
        NTSTATUS
            NTAPI
            ZwQueryInformationJobObject(
                _In_opt_ HANDLE JobHandle,
                _In_ JOBOBJECTINFOCLASS JobObjectInformationClass,
                _Out_writes_bytes_(JobObjectInformationLength) PVOID JobObjectInformation,
                _In_ ULONG JobObjectInformationLength,
                _Out_opt_ PULONG ReturnLength
            );


        NTSTATUS
            NTAPI
            ZwQueryInformationProcess(
                _In_ HANDLE ProcessHandle,
                _In_ PROCESSINFOCLASS ProcessInformationClass,
                _Out_writes_bytes_(ProcessInformationLength) PVOID ProcessInformation,
                _In_ ULONG ProcessInformationLength,
                _Out_opt_ PULONG ReturnLength
            );


        NTSTATUS
            NTAPI
            ZwQueryInformationThread(
                _In_ HANDLE ThreadHandle,
                _In_ THREADINFOCLASS ThreadInformationClass,
                _Out_writes_bytes_(ThreadInformationLength) PVOID ThreadInformation,
                _In_ ULONG ThreadInformationLength,
                _Out_opt_ PULONG ReturnLength
            );


        NTSTATUS
            NTAPI
            ZwQueryInformationToken(
                _In_ HANDLE TokenHandle,
                _In_ TOKEN_INFORMATION_CLASS TokenInformationClass,
                _Out_writes_bytes_(TokenInformationLength) PVOID TokenInformation,
                _In_ ULONG TokenInformationLength,
                _Out_ PULONG ReturnLength
            );


        NTSTATUS
            NTAPI
            ZwQueryInformationTransaction(
                _In_ HANDLE TransactionHandle,
                _In_ TRANSACTION_INFORMATION_CLASS TransactionInformationClass,
                _Out_writes_bytes_(TransactionInformationLength) PVOID TransactionInformation,
                _In_ ULONG TransactionInformationLength,
                _Out_opt_ PULONG ReturnLength
            );

        NTSTATUS
            NTAPI
            ZwQueryInstallUILanguage(
                _Out_ LANGID *InstallUILanguageId
            );


        NTSTATUS
            NTAPI
            ZwQueryIntervalProfile(
                _In_ KPROFILE_SOURCE ProfileSource,
                _Out_ PULONG Interval
            );


        NTSTATUS
            NTAPI
            ZwQueryLicenseValue(
                _In_ PUNICODE_STRING ValueName,
                _Out_opt_ PULONG Type,
                _Out_writes_bytes_to_opt_(DataSize, *ResultDataSize) PVOID Data,
                _In_ ULONG DataSize,
                _Out_ PULONG ResultDataSize
            );


        NTSTATUS
            NTAPI
            ZwQueryObject(
                _In_ HANDLE Handle,
                _In_ OBJECT_INFORMATION_CLASS ObjectInformationClass,
                _Out_writes_bytes_opt_(ObjectInformationLength) PVOID ObjectInformation,
                _In_ ULONG ObjectInformationLength,
                _Out_opt_ PULONG ReturnLength
            );


        NTSTATUS
            NTAPI
            ZwQueryQuotaInformationFile(
                _In_ HANDLE FileHandle,
                _Out_ PIO_STATUS_BLOCK IoStatusBlock,
                _Out_writes_bytes_(Length) PVOID Buffer,
                _In_ ULONG Length,
                _In_ BOOLEAN ReturnSingleEntry,
                _In_reads_bytes_opt_(SidListLength) PVOID SidList,
                _In_ ULONG SidListLength,
                _In_opt_ PSID StartSid,
                _In_ BOOLEAN RestartScan
            );


        NTSTATUS
            NTAPI
            ZwQuerySection(
                _In_ HANDLE SectionHandle,
                _In_ SECTION_INFORMATION_CLASS SectionInformationClass,
                _Out_writes_bytes_(SectionInformationLength) PVOID SectionInformation,
                _In_ SIZE_T SectionInformationLength,
                _Out_opt_ PSIZE_T ReturnLength
            );


        NTSTATUS
            NTAPI
            ZwQuerySecurityAttributesToken(
                _In_ HANDLE TokenHandle,
                _In_reads_opt_(NumberOfAttributes) PUNICODE_STRING Attributes,
                _In_ ULONG NumberOfAttributes,
                _Out_writes_bytes_(Length) PVOID Buffer, // PTOKEN_SECURITY_ATTRIBUTES_INFORMATION
                _In_ ULONG Length,
                _Out_ PULONG ReturnLength
            );


        NTSTATUS
            NTAPI
            ZwQuerySecurityObject(
                _In_ HANDLE Handle,
                _In_ SECURITY_INFORMATION SecurityInformation,
                _Out_writes_bytes_opt_(Length) PSECURITY_DESCRIPTOR SecurityDescriptor,
                _In_ ULONG Length,
                _Out_ PULONG LengthNeeded
            );



        NTSTATUS
            NTAPI
            ZwQuerySystemEnvironmentValueEx(
                _In_ PUNICODE_STRING VariableName,
                _In_ LPGUID VendorGuid,
                _Out_writes_bytes_opt_(*ValueLength) PVOID Value,
                _Inout_ PULONG ValueLength,
                _Out_opt_ PULONG Attributes
            );


        NTSTATUS
            NTAPI
            ZwQuerySystemInformation(
                _In_ SYSTEM_INFORMATION_CLASS SystemInformationClass,
                _Out_writes_bytes_opt_(SystemInformationLength) PVOID SystemInformation,
                _In_ ULONG SystemInformationLength,
                _Out_opt_ PULONG ReturnLength
            );


        NTSTATUS
            NTAPI
            ZwQuerySystemInformationEx(
                _In_ SYSTEM_INFORMATION_CLASS SystemInformationClass,
                _In_reads_bytes_(InputBufferLength) PVOID InputBuffer,
                _In_ ULONG InputBufferLength,
                _Out_writes_bytes_opt_(SystemInformationLength) PVOID SystemInformation,
                _In_ ULONG SystemInformationLength,
                _Out_opt_ PULONG ReturnLength
            );


        NTSTATUS
            NTAPI
            ZwQueryTimerResolution(
                _Out_ PULONG MaximumTime,
                _Out_ PULONG MinimumTime,
                _Out_ PULONG CurrentTime
            );


        NTSTATUS
            NTAPI
            ZwQueryVirtualMemory(
                _In_ HANDLE ProcessHandle,
                _In_ PVOID BaseAddress,
                _In_ MEMORY_INFORMATION_CLASS MemoryInformationClass,
                _Out_writes_bytes_(MemoryInformationLength) PVOID MemoryInformation,
                _In_ SIZE_T MemoryInformationLength,
                _Out_opt_ PSIZE_T ReturnLength
            );


        NTSTATUS
            NTAPI
            ZwRemoveIoCompletion(
                _In_ HANDLE IoCompletionHandle,
                _Out_ PVOID *KeyContext,
                _Out_ PVOID *ApcContext,
                _Out_ PIO_STATUS_BLOCK IoStatusBlock,
                _In_opt_ PLARGE_INTEGER Timeout
            );


        NTSTATUS
            NTAPI
            ZwRemoveIoCompletionEx(
                _In_ HANDLE IoCompletionHandle,
                _Out_writes_to_(Count, *NumEntriesRemoved) PFILE_IO_COMPLETION_INFORMATION IoCompletionInformation,
                _In_ ULONG Count,
                _Out_ PULONG NumEntriesRemoved,
                _In_opt_ PLARGE_INTEGER Timeout,
                _In_ BOOLEAN Alertable
            );


        NTSTATUS
            NTAPI
            ZwReplaceKey(
                _In_ POBJECT_ATTRIBUTES NewFile,
                _In_ HANDLE TargetHandle,
                _In_ POBJECT_ATTRIBUTES OldFile
            );


        NTSTATUS
            NTAPI
            ZwRequestPort(
                _In_ HANDLE PortHandle,
                _In_reads_bytes_(RequestMessage->u1.s1.TotalLength) PPORT_MESSAGE RequestMessage
            );


        NTSTATUS
            NTAPI
            ZwRequestWaitReplyPort(
                _In_ HANDLE PortHandle,
                _In_reads_bytes_(RequestMessage->u1.s1.TotalLength) PPORT_MESSAGE RequestMessage,
                _Out_ PPORT_MESSAGE ReplyMessage
            );


        NTSTATUS
            NTAPI
            ZwResetEvent(
                _In_ HANDLE EventHandle,
                _Out_opt_ PLONG PreviousState
            );

        NTSTATUS
            NTAPI
            ZwSecureConnectPort(
                _Out_ PHANDLE PortHandle,
                _In_ PUNICODE_STRING PortName,
                _In_ PSECURITY_QUALITY_OF_SERVICE SecurityQos,
                _Inout_opt_ PPORT_VIEW ClientView,
                _In_opt_ PSID RequiredServerSid,
                _Inout_opt_ PREMOTE_PORT_VIEW ServerView,
                _Out_opt_ PULONG MaxMessageLength,
                _Inout_updates_bytes_to_opt_(*ConnectionInformationLength, *ConnectionInformationLength) PVOID ConnectionInformation,
                _Inout_opt_ PULONG ConnectionInformationLength
            );


        NTSTATUS
            NTAPI
            ZwSetCachedSigningLevel(
                _In_ ULONG Flags,
                _In_ SE_SIGNING_LEVEL InputSigningLevel,
                _In_reads_(SourceFileCount) PHANDLE SourceFiles,
                _In_ ULONG SourceFileCount,
                _In_opt_ HANDLE TargetFile
            );


        NTSTATUS
            NTAPI
            ZwSetDefaultUILanguage(
                _In_ LANGID DefaultUILanguageId
            );


        NTSTATUS
            NTAPI
            ZwSetDriverEntryOrder(
                _In_reads_(Count) PULONG Ids,
                _In_ ULONG Count
            );


        NTSTATUS
            NTAPI
            ZwSetEaFile(
                _In_ HANDLE FileHandle,
                _Out_ PIO_STATUS_BLOCK IoStatusBlock,
                _In_reads_bytes_(Length) PVOID Buffer,
                _In_ ULONG Length
            );


        NTSTATUS
            NTAPI
            ZwSetEvent(
                _In_ HANDLE EventHandle,
                _Out_opt_ PLONG PreviousState
            );
        

        NTSTATUS
            NTAPI
            ZwSetInformationJobObject(
                _In_ HANDLE JobHandle,
                _In_ JOBOBJECTINFOCLASS JobObjectInformationClass,
                _In_reads_bytes_(JobObjectInformationLength) PVOID JobObjectInformation,
                _In_ ULONG JobObjectInformationLength
            );


        NTSTATUS
            NTAPI
            ZwSetInformationObject(
                _In_ HANDLE Handle,
                _In_ OBJECT_INFORMATION_CLASS ObjectInformationClass,
                _In_reads_bytes_(ObjectInformationLength) PVOID ObjectInformation,
                _In_ ULONG ObjectInformationLength
            );


        NTSTATUS
            NTAPI
            ZwSetInformationProcess(
                _In_ HANDLE ProcessHandle,
                _In_ PROCESSINFOCLASS ProcessInformationClass,
                _In_reads_bytes_(ProcessInformationLength) PVOID ProcessInformation,
                _In_ ULONG ProcessInformationLength
            );


        NTSTATUS
            NTAPI
            ZwSetInformationToken(
                _In_ HANDLE TokenHandle,
                _In_ TOKEN_INFORMATION_CLASS TokenInformationClass,
                _In_reads_bytes_(TokenInformationLength) PVOID TokenInformation,
                _In_ ULONG TokenInformationLength
            );


        NTSTATUS
            NTAPI
            ZwSetInformationVirtualMemory(
                _In_ HANDLE ProcessHandle,
                _In_ VIRTUAL_MEMORY_INFORMATION_CLASS VmInformationClass,
                _In_ ULONG_PTR NumberOfEntries,
                _In_reads_(NumberOfEntries) PMEMORY_RANGE_ENTRY VirtualAddresses,
                _In_reads_bytes_(VmInformationLength) PVOID VmInformation,
                _In_ ULONG VmInformationLength
            );


        NTSTATUS
            NTAPI
            ZwSetIntervalProfile(
                _In_ ULONG Interval,
                _In_ KPROFILE_SOURCE Source
            );


        NTSTATUS
            NTAPI
            ZwSetIoCompletion(
                _In_ HANDLE IoCompletionHandle,
                _In_opt_ PVOID KeyContext,
                _In_opt_ PVOID ApcContext,
                _In_ NTSTATUS IoStatus,
                _In_ ULONG_PTR IoStatusInformation
            );


        NTSTATUS
            NTAPI
            ZwSetIoCompletionEx(
                _In_ HANDLE IoCompletionHandle,
                _In_ HANDLE IoCompletionPacketHandle,
                _In_opt_ PVOID KeyContext,
                _In_opt_ PVOID ApcContext,
                _In_ NTSTATUS IoStatus,
                _In_ ULONG_PTR IoStatusInformation
            );


        NTSTATUS
            NTAPI
            ZwSetQuotaInformationFile(
                _In_ HANDLE FileHandle,
                _Out_ PIO_STATUS_BLOCK IoStatusBlock,
                _In_reads_bytes_(Length) PVOID Buffer,
                _In_ ULONG Length
            );


        NTSTATUS
            NTAPI
            ZwSetSecurityObject(
                _In_ HANDLE Handle,
                _In_ SECURITY_INFORMATION SecurityInformation,
                _In_ PSECURITY_DESCRIPTOR SecurityDescriptor
            );


        NTSTATUS
            NTAPI
            ZwSetSystemEnvironmentValueEx(
                _In_ PUNICODE_STRING VariableName,
                _In_ LPGUID VendorGuid,
                _In_reads_bytes_opt_(ValueLength) PVOID Value,
                _In_ ULONG ValueLength,
                _In_ ULONG Attributes
            );


        NTSTATUS
            NTAPI
            ZwSetSystemInformation(
                _In_ SYSTEM_INFORMATION_CLASS SystemInformationClass,
                _In_reads_bytes_opt_(SystemInformationLength) PVOID SystemInformation,
                _In_ ULONG SystemInformationLength
            );

        
        NTSTATUS
            NTAPI
            ZwSetSystemTime(
                _In_opt_ PLARGE_INTEGER SystemTime,
                _Out_opt_ PLARGE_INTEGER PreviousTime
            );


        NTSTATUS
            NTAPI
            ZwSetTimerResolution(
                _In_ ULONG DesiredTime,
                _In_ BOOLEAN SetResolution,
                _Out_ PULONG ActualTime
            );


        NTSTATUS
            NTAPI
            ZwSetVolumeInformationFile(
                _In_ HANDLE FileHandle,
                _Out_ PIO_STATUS_BLOCK IoStatusBlock,
                _In_reads_bytes_(Length) PVOID FsInformation,
                _In_ ULONG Length,
                _In_ FS_INFORMATION_CLASS FsInformationClass
            );


        NTSTATUS
            NTAPI
            ZwStartProfile(
                _In_ HANDLE ProfileHandle
            );


        NTSTATUS
            NTAPI
            ZwStopProfile(
                _In_ HANDLE ProfileHandle
            );

        
        NTSTATUS
            NTAPI
            ZwTerminateJobObject(
                _In_ HANDLE JobHandle,
                _In_ NTSTATUS ExitStatus
            );


        NTSTATUS
            NTAPI
            ZwTraceControl(
                _In_ ULONG FunctionCode,
                _In_reads_bytes_opt_(InBufferLen) PVOID InBuffer,
                _In_ ULONG InBufferLen,
                _Out_writes_bytes_opt_(OutBufferLen) PVOID OutBuffer,
                _In_ ULONG OutBufferLen,
                _Out_ PULONG ReturnLength
            );


        NTSTATUS
            NTAPI
            ZwTraceEvent(
                _In_ HANDLE TraceHandle,
                _In_ ULONG Flags,
                _In_ ULONG FieldSize,
                _In_ PVOID Fields
            );


        NTSTATUS
            NTAPI
            ZwTranslateFilePath(
                _In_ PFILE_PATH InputFilePath,
                _In_ ULONG OutputType,
                _Out_writes_bytes_opt_(*OutputFilePathLength) PFILE_PATH OutputFilePath,
                _Inout_opt_ PULONG OutputFilePathLength
            );


        NTSTATUS
            NTAPI
            ZwUnloadKey(
                _In_ POBJECT_ATTRIBUTES TargetKey
            );


        NTSTATUS
            NTAPI
            ZwUnloadKey2(
                _In_ POBJECT_ATTRIBUTES TargetKey,
                _In_ ULONG Flags
            );


        NTSTATUS
            NTAPI
            ZwUnloadKeyEx(
                _In_ POBJECT_ATTRIBUTES TargetKey,
                _In_opt_ HANDLE Event
            );


        NTSTATUS
            NTAPI
            ZwUnlockFile(
                _In_ HANDLE FileHandle,
                _Out_ PIO_STATUS_BLOCK IoStatusBlock,
                _In_ PLARGE_INTEGER ByteOffset,
                _In_ PLARGE_INTEGER Length,
                _In_ ULONG Key
            );


        NTSTATUS
            NTAPI
            ZwUnlockVirtualMemory(
                _In_ HANDLE ProcessHandle,
                _Inout_ PVOID *BaseAddress,
                _Inout_ PSIZE_T RegionSize,
                _In_ ULONG MapType
            );


        NTSTATUS
            NTAPI
            ZwWaitForMultipleObjects(
                _In_ ULONG Count,
                _In_reads_(Count) HANDLE Handles[],
                _In_ WAIT_TYPE WaitType,
                _In_ BOOLEAN Alertable,
                _In_opt_ PLARGE_INTEGER Timeout
            );


        NTSTATUS
            NTAPI
            ZwWaitForSingleObject(
                _In_ HANDLE Handle,
                _In_ BOOLEAN Alertable,
                _In_opt_ PLARGE_INTEGER Timeout
            );


        NTSTATUS
            NTAPI
            ZwYieldExecution(
                VOID
            );
    }
}

namespace wdk
{
    extern"C"
    {
        inline auto ZwInitSystem() -> NTSTATUS
        {
            return STATUS_SUCCESS;
        }
    }
}
