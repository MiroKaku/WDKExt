#pragma once


/* native type */

using INT8      = signed    __int8;
using INT16     = signed    __int16;
using INT32     = signed    __int32;
using INT64     = signed    __int64;

using UINT8     = unsigned  __int8;
using UINT16    = unsigned  __int16;
using UINT32    = unsigned  __int32;
using UINT64    = unsigned  __int64;

using CHAR      = char;
using SHORT     = short;
using LONG      = long;
using LONGLONG  = INT64;
using LONG64    = INT64;

using UCHAR     = unsigned  char;
using USHORT    = unsigned  short;
using ULONG     = unsigned  long;
using ULONGLONG = UINT64;
using ULONG64   = UINT64;

using BYTE      = UCHAR;
using WORD      = USHORT;
using DWORD     = ULONG;
using QWORD     = UINT64;

using PVOID32   = void * __ptr32;
using PVOID64   = void * __ptr64;
using HANDLE32  = PVOID32;
using HANDLE64  = PVOID64;

#ifdef _WIN64
using INT_PTR   = INT64;
using LONG_PTR  = INT64;
using SSIZE_T   = INT64;

using UINT_PTR  = UINT64;
using ULONG_PTR = UINT64;
using SIZE_T    = UINT64;
#else
using INT_PTR   = INT32;
using LONG_PTR  = LONG;
using SSIZE_T   = LONG_PTR;

using UINT_PTR  = UINT32;
using ULONG_PTR = ULONG;
using SIZE_T    = ULONG_PTR;
#endif


#ifndef SameDefine$
#define SameDefine$(ns, type)   \
    using ns::_##type;          \
    using ns::type;             \
    using ns::P##type
#endif


namespace wdk
{
    
    enum StandardAccessMask : ACCESS_MASK
    {
        Delete                  = 0x00010000,
        ReadControl             = 0x00020000,
        WriteDac                = 0x00040000,
        WriteOwner              = 0x00080000,
        Synchronize             = 0x00100000,

        StandardRightsRequired  = 0x000F0000,
        StandardRightsRead      = ReadControl,
        StandardRightsWrite     = ReadControl,
        StandardRightsExecute   = ReadControl,

        StandardRightsAll       = 0x001F0000,
        SpecificRightsAll       = 0x0000FFFF,

        AccessSystemSecurity    = 0x01000000,
        MaximumAllowed          = 0x02000000,
    };


    enum GenericAccessMask : ACCESS_MASK
    {
        GenericRead     = 0x80000000,
        GenericWrite    = 0x40000000,
        GenericExecute  = 0x20000000,
        GenericAll      = 0x10000000,
    };


    template<typename T = HANDLE>
    struct CLIENT_ID_T
    {
        T UniqueProcess;
        T UniqueThread;
    };
    using CLIENT_ID32 = CLIENT_ID_T<HANDLE32>;
    using CLIENT_ID64 = CLIENT_ID_T<HANDLE64>;


    template<typename T = PVOID>
    struct LIST_ENTRY_T
    {
        T Flink;
        T Blink;
    };


    template<typename T = PVOID>
    struct T_STRING
    {
        USHORT  Length;
        USHORT  MaximumLength;

        T       Buffer;
    };

}


namespace wdk
{

    template<typename T = PVOID>
    FORCEINLINE auto InitializeListHead(
        _Out_ LIST_ENTRY_T<T> * ListHead)
        -> VOID

    {
        ListHead->Flink = ListHead->Blink = ListHead;
    }


    template<typename T = PVOID>
    FORCEINLINE auto IsListEmpty(
        _In_ const LIST_ENTRY_T<T> * ListHead)
        -> BOOLEAN
    {
        return (BOOLEAN)(ListHead->Flink == ListHead);
    }


    template<typename T = PVOID>
    FORCEINLINE auto RemoveEntryList(
        _In_ LIST_ENTRY_T<T>* Entry)
        -> BOOLEAN
    {
        using LIST_TYPE  = LIST_ENTRY_T<T>;
        using PLIST_TYPE = LIST_TYPE*;

        auto Blink = PLIST_TYPE();
        auto Flink = PLIST_TYPE();

        Blink = (PLIST_TYPE)Entry->Blink;
        Flink = (PLIST_TYPE)Entry->Flink;

        if constexpr (sizeof(T) == sizeof(PVOID32))
        {
            Blink->Flink = (PVOID32)(UINT32)(SIZE_T)Flink;
            Flink->Blink = (PVOID32)(UINT32)(SIZE_T)Blink;
        }
        else
        {
            Blink->Flink = Flink;
            Flink->Blink = Blink;
        }

        return (BOOLEAN)(Flink == Blink);
    }


    template<typename T = PVOID>
    FORCEINLINE auto RemoveHeadList(
        _Inout_ LIST_ENTRY_T<T>* ListHead)
        -> LIST_ENTRY_T<T>*
    {
        using LIST_TYPE  = LIST_ENTRY_T<T>;
        using PLIST_TYPE = LIST_TYPE * ;

        auto Flink = PLIST_TYPE();
        auto Entry = PLIST_TYPE();

        Entry = (PLIST_TYPE)ListHead->Flink;
        Flink = (PLIST_TYPE)Entry->Flink;

        if constexpr (sizeof(T) == sizeof(PVOID32))
        {
            ListHead->Flink = (PVOID32)(UINT32)(SIZE_T)Flink;
            Flink->Blink    = (PVOID32)(UINT32)(SIZE_T)ListHead;
        }
        else
        {
            ListHead->Flink = Flink;
            Flink->Blink    = ListHead;
        }

        return Entry;
    }


    template<typename T = PVOID>
    FORCEINLINE auto RemoveTailList(
            _Inout_ LIST_ENTRY_T<T>* ListHead)
        -> LIST_ENTRY_T<T>*
    {
        using LIST_TYPE = LIST_ENTRY_T<T>;
        using PLIST_TYPE = LIST_TYPE * ;

        auto Blink = PLIST_TYPE();
        auto Entry = PLIST_TYPE();

        Entry = (PLIST_TYPE)ListHead->Blink;
        Blink = (PLIST_TYPE)Entry->Blink;

        if constexpr (sizeof(T) == sizeof(PVOID32))
        {
            ListHead->Blink = (PVOID32)(UINT32)(SIZE_T)Blink;
            Blink->Flink    = (PVOID32)(UINT32)(SIZE_T)ListHead;
        }
        else
        {
            ListHead->Blink = Blink;
            Blink->Flink    = ListHead;
        }
    }


    template<typename T = PVOID>
    FORCEINLINE auto InsertTailList(
            _Inout_ LIST_ENTRY_T<T>* ListHead,
            _Inout_ __drv_aliasesMem LIST_ENTRY_T<T>* Entry)
        -> VOID
    {
        using LIST_TYPE  = LIST_ENTRY_T<T>;
        using PLIST_TYPE = LIST_TYPE * ;

        auto Blink = PLIST_TYPE();

        Blink = (PLIST_TYPE)ListHead->Blink;

        if constexpr (sizeof(T) == sizeof(PVOID32))
        {
            Entry->Flink    = (PVOID32)(UINT32)(SIZE_T)ListHead;
            Entry->Blink    = (PVOID32)(UINT32)(SIZE_T)Blink;
            Blink->Flink    = (PVOID32)(UINT32)(SIZE_T)Entry;
            ListHead->Blink = (PVOID32)(UINT32)(SIZE_T)Entry;
        }
        else
        {
            Entry->Flink    = ListHead;
            Entry->Blink    = Blink;
            Blink->Flink    = Entry;
            ListHead->Blink = Entry;
        }
    }


    template<typename T = PVOID>
    FORCEINLINE auto InsertHeadList(
            _Inout_ LIST_ENTRY_T<T>* ListHead,
            _Inout_ __drv_aliasesMem LIST_ENTRY_T<T>* Entry)
        -> VOID
    {
        using LIST_TYPE = LIST_ENTRY_T<T>;
        using PLIST_TYPE = LIST_TYPE * ;

        auto Flink = PLIST_TYPE();

        Flink = (PLIST_TYPE)ListHead->Flink;
        
        if constexpr (sizeof(T) == sizeof(PVOID32))
        {
            Entry->Flink    = (PVOID32)(UINT32)(SIZE_T)Flink;
            Entry->Blink    = (PVOID32)(UINT32)(SIZE_T)ListHead;
            Flink->Blink    = (PVOID32)(UINT32)(SIZE_T)Entry;
            ListHead->Flink = (PVOID32)(UINT32)(SIZE_T)Entry;
        }
        else
        {
            Entry->Flink    = Flink;
            Entry->Blink    = ListHead;
            Flink->Blink    = Entry;
            ListHead->Flink = Entry;
        }
    }


    template<typename T = PVOID>
    FORCEINLINE auto AppendTailList(
            _Inout_ LIST_ENTRY_T<T>* ListHead,
            _Inout_ LIST_ENTRY_T<T>* ListToAppend)
        -> VOID
    {
        using LIST_TYPE = LIST_ENTRY_T<T>;
        using PLIST_TYPE = LIST_TYPE * ;

        auto ListEnd = PLIST_TYPE();

        ListEnd = (PLIST_TYPE)ListHead->Blink;

        if constexpr (sizeof(T) == sizeof(PVOID32))
        {
            ListHead->Blink->Flink      = (PVOID32)(UINT32)(SIZE_T)ListToAppend;
            ListHead->Blink             = (PVOID32)(UINT32)(SIZE_T)ListToAppend->Blink;
            ListToAppend->Blink->Flink  = (PVOID32)(UINT32)(SIZE_T)ListHead;
            ListToAppend->Blink         = (PVOID32)(UINT32)(SIZE_T)ListEnd;
        }
        else
        {
            ListHead->Blink->Flink      = ListToAppend;
            ListHead->Blink             = ListToAppend->Blink;
            ListToAppend->Blink->Flink  = ListHead;
            ListToAppend->Blink         = ListEnd;
        }
    }

}