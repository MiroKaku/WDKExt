#pragma once
#include "IoStruct.inl"


namespace wdk
{
    extern"C"
    {
        POBJECT_TYPE *IoAdapterObjectType;
        POBJECT_TYPE *IoDriverObjectType;

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
