#pragma once


namespace wdk
{

#pragma region Process
    // private
    typedef struct _PROCESS_DISK_COUNTERS
    {
        ULONGLONG BytesRead;
        ULONGLONG BytesWritten;
        ULONGLONG ReadOperationCount;
        ULONGLONG WriteOperationCount;
        ULONGLONG FlushOperationCount;
    } PROCESS_DISK_COUNTERS, *PPROCESS_DISK_COUNTERS;
    
    // private
    typedef union _ENERGY_STATE_DURATION
    {
        union
        {
            ULONGLONG Value;
            ULONG LastChangeTime;
        };

        ULONG Duration : 31;
        ULONG IsInState : 1;
    } ENERGY_STATE_DURATION, *PENERGY_STATE_DURATION;

    // private
    typedef struct _PROCESS_ENERGY_VALUES
    {
        ULONGLONG Cycles[2][4];
        ULONGLONG DiskEnergy;
        ULONGLONG NetworkTailEnergy;
        ULONGLONG MBBTailEnergy;
        ULONGLONG NetworkTxRxBytes;
        ULONGLONG MBBTxRxBytes;
        union
        {
            ENERGY_STATE_DURATION Durations[3];
            struct
            {
                ENERGY_STATE_DURATION ForegroundDuration;
                ENERGY_STATE_DURATION DesktopVisibleDuration;
                ENERGY_STATE_DURATION PSMForegroundDuration;
            };
        };
        ULONG CompositionRendered;
        ULONG CompositionDirtyGenerated;
        ULONG CompositionDirtyPropagated;
        ULONG Reserved1;
        ULONGLONG AttributedCycles[4][2];
        ULONGLONG WorkOnBehalfCycles[4][2];
    } PROCESS_ENERGY_VALUES, *PPROCESS_ENERGY_VALUES;
#pragma endregion


#pragma region File
    // private
    typedef struct _FILE_PATH
    {
        ULONG Version;
        ULONG Length;
        ULONG Type;
        UCHAR FilePath[1];
    } FILE_PATH, *PFILE_PATH;


    // private
    typedef struct _FILE_IO_COMPLETION_INFORMATION
    {
        PVOID KeyContext;
        PVOID ApcContext;
        IO_STATUS_BLOCK IoStatusBlock;
    } FILE_IO_COMPLETION_INFORMATION, *PFILE_IO_COMPLETION_INFORMATION;
#pragma endregion


}

#include "Fs\build_7600.inl"
#include "Fs\build_7601.inl"
#include "Fs\build_9200.inl"
#include "Fs\build_9600.inl"
#include "Fs\build_10240.inl"
#include "Fs\build_10586.inl"
#include "Fs\build_14393.inl"
#include "Fs\build_15063.inl"
#include "Fs\build_16299.inl"
#include "Fs\build_17134.inl"
#include "Fs\build_17763.inl"