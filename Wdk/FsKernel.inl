#pragma once
#include "FsStruct.inl"


namespace wdk
{
    extern"C"
    {

#ifndef _NTIFS_
#define FSRTL_FSP_TOP_LEVEL_IRP                 ((LONG_PTR)0x01)
#define FSRTL_CACHE_TOP_LEVEL_IRP               ((LONG_PTR)0x02)
#define FSRTL_MOD_WRITE_TOP_LEVEL_IRP           ((LONG_PTR)0x03)
#define FSRTL_FAST_IO_TOP_LEVEL_IRP             ((LONG_PTR)0x04)
#define FSRTL_NETWORK1_TOP_LEVEL_IRP            ((LONG_PTR)0x05)
#define FSRTL_NETWORK2_TOP_LEVEL_IRP            ((LONG_PTR)0x06)
#define FSRTL_ASYNC_CACHED_READ_TOP_LEVEL_IRP   ((LONG_PTR)0x07)
#define FSRTL_MAX_TOP_LEVEL_IRP_FLAG            ((LONG_PTR)0xFFFF)
#endif

        inline void NTAPI
            FsRtlSetTopLevelIrpForModWriter()
        {
            auto TempIrp = (PIRP)FSRTL_MOD_WRITE_TOP_LEVEL_IRP;
            IoSetTopLevelIrp(TempIrp);
        }

        BOOLEAN NTAPI
            FsRtlCopyRead(
                _In_ PFILE_OBJECT FileObject,
                _In_ PLARGE_INTEGER FileOffset,
                _In_ ULONG Length,
                _In_ BOOLEAN Wait,
                _In_ ULONG LockKey,
                __out_bcount(Length) PVOID Buffer,
                _Out_ PIO_STATUS_BLOCK IoStatus,
                _In_ PDEVICE_OBJECT DeviceObject
            );

        BOOLEAN NTAPI
            FsRtlCopyWrite(
                _In_ PFILE_OBJECT FileObject,
                _In_ PLARGE_INTEGER FileOffset,
                _In_ ULONG Length,
                _In_ BOOLEAN Wait,
                _In_ ULONG LockKey,
                __in_bcount(Length) PVOID Buffer,
                _Out_ PIO_STATUS_BLOCK IoStatus,
                _In_ PDEVICE_OBJECT DeviceObject
            );

        BOOLEAN NTAPI
            FsRtlMdlRead(
                _In_ PFILE_OBJECT FileObject,
                _In_ PLARGE_INTEGER FileOffset,
                _In_ ULONG Length,
                _In_ ULONG LockKey,
                _Out_ PMDL *MdlChain,
                _Out_ PIO_STATUS_BLOCK IoStatus
            );

        BOOLEAN NTAPI
            FsRtlMdlReadComplete(
                _In_ PFILE_OBJECT FileObject,
                _In_ PMDL MdlChain
            );

        BOOLEAN NTAPI
            FsRtlPrepareMdlWrite(
                _In_ PFILE_OBJECT FileObject,
                _In_ PLARGE_INTEGER FileOffset,
                _In_ ULONG Length,
                _In_ ULONG LockKey,
                _Out_ PMDL *MdlChain,
                _Out_ PIO_STATUS_BLOCK IoStatus
            );

        BOOLEAN NTAPI
            FsRtlMdlWriteComplete(
                _In_ PFILE_OBJECT FileObject,
                _In_ PLARGE_INTEGER FileOffset,
                _In_ PMDL MdlChain
            );

        BOOLEAN NTAPI
            FsRtlMdlReadDev(
                _In_ PFILE_OBJECT FileObject,
                _In_ PLARGE_INTEGER FileOffset,
                _In_ ULONG Length,
                _In_ ULONG LockKey,
                _Out_ PMDL *MdlChain,
                _Out_ PIO_STATUS_BLOCK IoStatus,
                _In_ PDEVICE_OBJECT DeviceObject
            );

        BOOLEAN NTAPI
            FsRtlMdlReadCompleteDev(
                _In_ PFILE_OBJECT FileObject,
                _In_ PMDL MdlChain,
                _In_ PDEVICE_OBJECT DeviceObject
            );

        BOOLEAN NTAPI
            FsRtlPrepareMdlWriteDev(
                _In_ PFILE_OBJECT FileObject,
                _In_ PLARGE_INTEGER FileOffset,
                _In_ ULONG Length,
                _In_ ULONG LockKey,
                _Out_ PMDL *MdlChain,
                _Out_ PIO_STATUS_BLOCK IoStatus,
                _In_ PDEVICE_OBJECT DeviceObject
            );

        BOOLEAN NTAPI
            FsRtlMdlWriteCompleteDev(
                _In_ PFILE_OBJECT FileObject,
                _In_ PLARGE_INTEGER FileOffset,
                _In_ PMDL MdlChain,
                _In_ PDEVICE_OBJECT DeviceObject
            );

        VOID NTAPI
            FsRtlAcquireFileExclusive(
                _In_ PFILE_OBJECT FileObject
            );

        VOID NTAPI
            FsRtlReleaseFile(
                _In_ PFILE_OBJECT FileObject
            );

        NTSTATUS NTAPI
            FsRtlGetFileSize(
                _In_ PFILE_OBJECT FileObject,
                _Inout_ PLARGE_INTEGER FileSize
            );

        BOOLEAN NTAPI
            FsRtlIsNameInExpression(
                _In_ PUNICODE_STRING Expression,
                _In_ PUNICODE_STRING Name,
                _In_ BOOLEAN IgnoreCase,
                _In_opt_ PWCH UpcaseTable
            );
    }
}

namespace wdk
{
    extern"C"
    {
        inline auto FsInitSystem() -> NTSTATUS
        {
            return STATUS_SUCCESS;
        }
    }
}
