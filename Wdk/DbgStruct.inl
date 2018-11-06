#pragma once


namespace wdk
{
    
    enum DbgkAccessMask : ACCESS_MASK
    {
        DebugReadEvent          = 0x0001,
        DebugProcessAssign      = 0x0002,
        DebugSetInformation     = 0x0004,
        DebugQueryInformation   = 0x0008,

        DEBUG_ALL_ACCESS = StandardRightsRequired | Synchronize | 
        DebugReadEvent | DebugProcessAssign | DebugSetInformation | DebugQueryInformation
    };

    enum : ULONG
    {
        DEBUG_KILL_ON_CLOSE = 0x1
    };

}

#include "Dbg\build_7600.inl"
#include "Dbg\build_7601.inl"
#include "Dbg\build_9200.inl"
#include "Dbg\build_9600.inl"
#include "Dbg\build_10240.inl"
#include "Dbg\build_10586.inl"
#include "Dbg\build_14393.inl"
#include "Dbg\build_15063.inl"
#include "Dbg\build_16299.inl"
#include "Dbg\build_17134.inl"
#include "Dbg\build_17763.inl"