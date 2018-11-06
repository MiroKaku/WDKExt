#pragma once


namespace wdk
{

    // private
    typedef struct _FILE_IO_COMPLETION_INFORMATION
    {
        PVOID KeyContext;
        PVOID ApcContext;
        IO_STATUS_BLOCK IoStatusBlock;
    } FILE_IO_COMPLETION_INFORMATION, *PFILE_IO_COMPLETION_INFORMATION;

}

#include "Io\build_7600.inl"
#include "Io\build_7601.inl"
#include "Io\build_9200.inl"
#include "Io\build_9600.inl"
#include "Io\build_10240.inl"
#include "Io\build_10586.inl"
#include "Io\build_14393.inl"
#include "Io\build_15063.inl"
#include "Io\build_16299.inl"
#include "Io\build_17134.inl"
#include "Io\build_17763.inl"