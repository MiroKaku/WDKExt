#pragma once
#include <wmilib.h>

namespace wdk
{
    enum WMI_CLOCK_TYPE
    {
        WmiClockTypeDefault,
        WmiClockTypeSystemTime,
        WmiClockTypePerfCounter,
        WmiClockTypeProcess,
        WmiClockTypeThread,
        WmiClockTypeCPUCycle,
    };
}

#include "Wmi\build_7600.inl"
#include "Wmi\build_7601.inl"
#include "Wmi\build_9200.inl"
#include "Wmi\build_9600.inl"
#include "Wmi\build_10240.inl"
#include "Wmi\build_10586.inl"
#include "Wmi\build_14393.inl"
#include "Wmi\build_15063.inl"
#include "Wmi\build_16299.inl"
#include "Wmi\build_17134.inl"
#include "Wmi\build_17763.inl"
