#pragma once


namespace wdk
{

    enum class SystemVersion : UINT32
    {
        Unknown,

        WindowsXP,                  // 5.1.2600
        WindowsXP64,                // 5.2.3790

        WindowsVista,               // 6.0.6000
        WindowsVista_SP1,           // 6.0.6001
        WindowsVista_SP2,           // 6.0.6002

        Windows7,                   // 6.1.7600
        Windows7_SP1,               // 6.1.7601

        Windows8,                   // 6.2.9200

        Windows8_1,                 // 6.3.9600

        Windows10,
        Windows10_1507 = Windows10, // 10.0.10240
        Windows10_1511,             // 10.0.10586
        Windows10_1607,             // 10.0.14393
        Windows10_1703,             // 10.0.15063
        Windows10_1709,             // 10.0.16299
        Windows10_1803,             // 10.0.17134
        Windows10_1809,             // 10.0.17763
        WindowsMax,
    };
    

    typedef struct _RTL_PROCESS_MODULE_INFORMATION
    {
        HANDLE Section;
        PVOID MappedBase;
        PVOID ImageBase;
        ULONG ImageSize;
        ULONG Flags;
        USHORT LoadOrderIndex;
        USHORT InitOrderIndex;
        USHORT LoadCount;
        USHORT OffsetToFileName;
        UCHAR FullPathName[256];
    } RTL_PROCESS_MODULE_INFORMATION, *PRTL_PROCESS_MODULE_INFORMATION;

    typedef struct _RTL_PROCESS_MODULES
    {
        ULONG NumberOfModules;
        RTL_PROCESS_MODULE_INFORMATION Modules[1];
    } RTL_PROCESS_MODULES, *PRTL_PROCESS_MODULES;

    // private
    typedef struct _RTL_PROCESS_MODULE_INFORMATION_EX
    {
        USHORT NextOffset;
        RTL_PROCESS_MODULE_INFORMATION BaseInfo;
        ULONG ImageChecksum;
        ULONG TimeDateStamp;
        PVOID DefaultBase;
    } RTL_PROCESS_MODULE_INFORMATION_EX, *PRTL_PROCESS_MODULE_INFORMATION_EX;

}

#include "Rtl\build_7600.inl"
#include "Rtl\build_7601.inl"
#include "Rtl\build_9200.inl"
#include "Rtl\build_9600.inl"
#include "Rtl\build_10240.inl"
#include "Rtl\build_10586.inl"
#include "Rtl\build_14393.inl"
#include "Rtl\build_15063.inl"
#include "Rtl\build_16299.inl"
#include "Rtl\build_17134.inl"
#include "Rtl\build_17763.inl"
