#pragma once
#include "RtlStruct.inl"


namespace wdk
{
    extern"C"
    {

        PIMAGE_NT_HEADERS NTAPI 
            RtlImageNtHeader(
                _In_ PVOID Base
            );

        PVOID NTAPI
            RtlImageDirectoryEntryToData(
                _In_ PVOID Base,
                _In_ BOOLEAN MappedAsImage,
                _In_ USHORT DirectoryEntry,
                _Out_ PULONG Size
            );

        ULONG NTAPI
            RtlGetNtGlobalFlags(
                VOID
            );

        BOOLEAN NTAPI
            RtlIsSandboxedToken(
                _In_opt_ PSECURITY_SUBJECT_CONTEXT Context,
                _In_ KPROCESSOR_MODE PreviousMode
            );

        NTSTATUS NTAPI
            RtlConvertSidToUnicodeString(
                _Inout_ PUNICODE_STRING UnicodeString,
                _In_ PSID Sid,
                _In_ BOOLEAN AllocateDestinationString
            );

        ULONG NTAPI
            RtlNtStatusToDosError(
                _In_ NTSTATUS Status
            );

        ULONG NTAPI
            RtlNtStatusToDosErrorNoTeb(
                _In_ NTSTATUS Status
            );

    }
}

namespace wdk
{
    extern"C"
    {
        
        inline constexpr auto Is64BitSystem() -> bool { return (sizeof(SIZE_T) == sizeof(UINT64)); };
        inline constexpr auto Is32BitSystem() -> bool { return !Is64BitSystem(); }

        __declspec(selectany) SystemVersion NtSystemVersion = SystemVersion::Unknown;
        inline auto GetSystemVersion()
            ->SystemVersion
        {
            if (SystemVersion::Unknown != NtSystemVersion)
            {
                return NtSystemVersion;
            }

            NTSTATUS vStatus = STATUS_SUCCESS;
            RTL_OSVERSIONINFOW  vVersion{};

            vStatus = RtlGetVersion(&vVersion);
            if (STATUS_SUCCESS != vStatus)
            {
                return SystemVersion::Unknown;
            }

            switch (vVersion.dwBuildNumber)
            {
            default:
                break;
            case 2600:
                NtSystemVersion = SystemVersion::WindowsXP;
                break;
            case 3790:
                NtSystemVersion = SystemVersion::WindowsXP64;
                break;
            case 6000:
                NtSystemVersion = SystemVersion::WindowsVista;
                break;
            case 6001:
                NtSystemVersion = SystemVersion::WindowsVista_SP1;
                break;
            case 6002:
                NtSystemVersion = SystemVersion::WindowsVista_SP2;
                break;
            case 7600:
                NtSystemVersion = SystemVersion::Windows7;
                break;
            case 7601:
                NtSystemVersion = SystemVersion::Windows7_SP1;
                break;
            case 9200:
                NtSystemVersion = SystemVersion::Windows8;
                break;
            case 9600:
                NtSystemVersion = SystemVersion::Windows8_1;
                break;
            case 10240:
                NtSystemVersion = SystemVersion::Windows10;
                break;
            case 10586:
                NtSystemVersion = SystemVersion::Windows10_1511;
                break;
            case 14393:
                NtSystemVersion = SystemVersion::Windows10_1607;
                break;
            case 15063:
                NtSystemVersion = SystemVersion::Windows10_1703;
                break;
            case 16299:
                NtSystemVersion = SystemVersion::Windows10_1709;
                break;
            case 17134:
                NtSystemVersion = SystemVersion::Windows10_1803;
                break;
            case 17763:
                NtSystemVersion = SystemVersion::Windows10_1809;
                break;
            }

            return NtSystemVersion;
        }

        inline bool IsWindowsXPOrGreater()
        {
            if (GetSystemVersion() >= SystemVersion::WindowsXP)
            {
                return true;
            }
            return false;
        }

        inline bool IsWindowsXPSP1OrGreater()
        {
            if (GetSystemVersion() >= SystemVersion::WindowsXP)
            {
                return true;
            }
            return false;
        }

        inline bool IsWindowsXPSP2OrGreater()
        {
            if (GetSystemVersion() >= SystemVersion::WindowsXP)
            {
                return true;
            }
            return false;
        }

        inline bool IsWindowsXPSP3OrGreater()
        {
            if (GetSystemVersion() >= SystemVersion::WindowsXP)
            {
                return true;
            }
            return false;
        }

        inline bool IsWindowsVistaOrGreater()
        {
            if (GetSystemVersion() >= SystemVersion::WindowsVista)
            {
                return true;
            }
            return false;
        }

        inline bool IsWindowsVistaSP1OrGreater()
        {
            if (GetSystemVersion() >= SystemVersion::WindowsVista_SP1)
            {
                return true;
            }
            return false;
        }

        inline bool IsWindowsVistaSP2OrGreater()
        {
            if (GetSystemVersion() >= SystemVersion::WindowsVista_SP2)
            {
                return true;
            }
            return false;
        }

        inline bool IsWindows7OrGreater()
        {
            if (GetSystemVersion() >= SystemVersion::Windows7)
            {
                return true;
            }
            return false;
        }

        inline bool IsWindows7SP1OrGreater()
        {
            if (GetSystemVersion() >= SystemVersion::Windows7_SP1)
            {
                return true;
            }
            return false;
        }

        inline bool IsWindows8OrGreater()
        {
            if (GetSystemVersion() >= SystemVersion::Windows8)
            {
                return true;
            }
            return false;
        }

        inline bool IsWindows8Point1OrGreater()
        {
            if (GetSystemVersion() >= SystemVersion::Windows8_1)
            {
                return true;
            }
            return false;
        }

        inline bool IsWindows10OrGreater()
        {
            if (GetSystemVersion() >= SystemVersion::Windows10)
            {
                return true;
            }
            return false;
        }

        inline bool IsWindowsThreshold1OrGreater()
        {
            if (GetSystemVersion() >= SystemVersion::Windows10_1507)
            {
                return true;
            }
            return false;
        }

        inline bool IsWindowsThreshold2OrGreater()
        {
            if (GetSystemVersion() >= SystemVersion::Windows10_1511)
            {
                return true;
            }
            return false;
        }

        inline bool IsWindowsRedstone1OrGreater()
        {
            if (GetSystemVersion() >= SystemVersion::Windows10_1607)
            {
                return true;
            }
            return false;
        }

        inline bool IsWindowsRedstone2OrGreater()
        {
            if (GetSystemVersion() >= SystemVersion::Windows10_1703)
            {
                return true;
            }
            return false;
        }

        inline bool IsWindowsRedstone3OrGreater()
        {
            if (GetSystemVersion() >= SystemVersion::Windows10_1709)
            {
                return true;
            }
            return false;
        }

        inline bool IsWindowsRedstone4OrGreater()
        {
            if (GetSystemVersion() >= SystemVersion::Windows10_1803)
            {
                return true;
            }
            return false;
        }

        inline bool IsWindowsRedstone5OrGreater()
        {
            if (GetSystemVersion() >= SystemVersion::Windows10_1809)
            {
                return true;
            }
            return false;
        }

        inline auto RtlInitSystem() -> NTSTATUS
        {
            if (GetSystemVersion() == SystemVersion::Unknown)
            {
                return STATUS_NOT_SUPPORTED;
            }

            return STATUS_SUCCESS;
        }

    }
}
