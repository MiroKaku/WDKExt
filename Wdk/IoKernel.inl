#pragma once
#include "IoStruct.inl"


namespace wdk
{
    extern"C"
    {
        extern POBJECT_TYPE *IoAdapterObjectType;
        extern POBJECT_TYPE *IoDriverObjectType;

        NTSTATUS NTAPI
            IoQueryFileDosDeviceName(
                _In_  PFILE_OBJECT FileObject,
                _Out_ POBJECT_NAME_INFORMATION *ObjectNameInformation
            );

        NTSTATUS NTAPI
            IoCreateDriver(
                _In_opt_ PUNICODE_STRING DriverName,
                _In_ PDRIVER_INITIALIZE InitializationFunction
            );

        VOID NTAPI
            IoDeleteDriver(
                _In_ PDRIVER_OBJECT DriverObject
            );

        PDEVICE_OBJECT NTAPI
            IoGetBaseFileSystemDeviceObject(
                _In_ PFILE_OBJECT FileObject
            );

        PDEVICE_OBJECT NTAPI
            IoGetDeviceAttachmentBaseRef(
                _In_ PDEVICE_OBJECT DeviceObject
            );
    }
}

namespace wdk
{
    extern"C"
    {
        inline auto IoInitSystem() -> NTSTATUS
        {
            return STATUS_SUCCESS;
        }
    }
}
