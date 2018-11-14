#pragma once
#include "ObStruct.inl"
#include "SeStruct.inl"


namespace wdk
{

    using LPC_PVOID     = PVOID;
    using LPC_HANDLE    = HANDLE;
    using LPC_SIZE_T    = SIZE_T;
    using LPC_CLIENT_ID = CLIENT_ID;

    enum LPCAccessMask : ACCESS_MASK
    {
        PortConnect     = 0x1,
        PortAllAccess   = (StandardRightsRequired | Synchronize | PortConnect)
    };

    enum PortObjectAttributesMask : ACCESS_MASK
    {
        PortValidObjectArrtibutes = ObjectCaseInsensitive
    };

    enum LPCMessageType : UINT32
    {
        LPCNewMessage,
        LPCRequest,
        LPCReply,
        LPCDataGram,
        LPCLostReply,
        LPCPortClosed,
        LPCClientDied,
        LPCException,
        LPCDebugEvent,
        LPCErrorEvent,
        LPCConnectionRequest,
        LPCConnectionRefused,
        LPCMaximum,

        LPCNoImpersonate    = 0x4000,
        LPCKernelModeMessage= 0x8000,
    };

    typedef struct PORT_MESSAGE
    {
        union
        {
            struct
            {
                SHORT DataLength;
                SHORT TotalLength;
            } s1;
            ULONG Length;
        } u1;
        union
        {
            struct
            {
                SHORT Type;
                SHORT DataInfoOffset;
            } s2;
            ULONG ZeroInit;
        } u2;
        union
        {
            LPC_CLIENT_ID ClientId;
            double DoNotUseThisField;
        };
        ULONG MessageId;
        union
        {
            LPC_SIZE_T ClientViewSize;
            ULONG CallbackId;
        };
    } *PPORT_MESSAGE;

    typedef struct PORT_DATA_ENTRY
    {
        PVOID Base;
        ULONG Size;
    }*PPORT_DATA_ENTRY;

    typedef struct PORT_DATA_INFORMATION
    {
        ULONG CountDataEntries;
        PORT_DATA_ENTRY DataEntries[1];
    }*PPORT_DATA_INFORMATION;

    enum : UINT32
    {
        PortMaximumMessageLength = 64 * sizeof(SIZE_T),
        LPCMaxConnectionInfoSize = 16 * sizeof(SIZE_T),

        PortTotalMaximumMessageLength = 
            ((PortMaximumMessageLength + sizeof(PORT_MESSAGE) + LPCMaxConnectionInfoSize + 0xF) & ~0xF)
    };

    typedef struct _LPC_CLIENT_DIED_MSG
    {
        PORT_MESSAGE PortMsg;
        LARGE_INTEGER CreateTime;
    } LPC_CLIENT_DIED_MSG, *PLPC_CLIENT_DIED_MSG;

    typedef struct _PORT_VIEW
    {
        ULONG   Length;
        HANDLE  SectionHandle;
        ULONG   SectionOffset;
        SIZE_T  ViewSize;
        PVOID   ViewBase;
        PVOID   ViewRemoteBase;
    } PORT_VIEW, *PPORT_VIEW;

    typedef struct _REMOTE_PORT_VIEW
    {
        ULONG   Length;
        SIZE_T  ViewSize;
        PVOID   ViewBase;
    } REMOTE_PORT_VIEW, *PREMOTE_PORT_VIEW;

    // WOW64 definitions

    // Except in a small number of special cases, WOW64 programs using the LPC APIs must use the 64-bit versions of the
    // PORT_MESSAGE, PORT_VIEW and REMOTE_PORT_VIEW data structures. Note that we take a different approach than the
    // official NT headers, which produce 64-bit versions in a 32-bit environment when USE_LPC6432 is defined.

    typedef struct _PORT_MESSAGE64
    {
        union
        {
            struct
            {
                CSHORT DataLength;
                CSHORT TotalLength;
            } s1;
            ULONG Length;
        } u1;
        union
        {
            struct
            {
                CSHORT Type;
                CSHORT DataInfoOffset;
            } s2;
            ULONG ZeroInit;
        } u2;
        union
        {
            CLIENT_ID64 ClientId;
            double DoNotUseThisField;
        };
        ULONG MessageId;
        union
        {
            ULONGLONG ClientViewSize; // only valid for LPC_CONNECTION_REQUEST messages
            ULONG CallbackId; // only valid for LPC_REQUEST messages
        };
    } PORT_MESSAGE64, *PPORT_MESSAGE64;

    typedef struct _LPC_CLIENT_DIED_MSG64
    {
        PORT_MESSAGE64 PortMsg;
        LARGE_INTEGER CreateTime;
    } LPC_CLIENT_DIED_MSG64, *PLPC_CLIENT_DIED_MSG64;

    typedef struct _PORT_VIEW64
    {
        ULONG Length;
        ULONGLONG SectionHandle;
        ULONG SectionOffset;
        ULONGLONG ViewSize;
        ULONGLONG ViewBase;
        ULONGLONG ViewRemoteBase;
    } PORT_VIEW64, *PPORT_VIEW64;

    typedef struct _REMOTE_PORT_VIEW64
    {
        ULONG Length;
        ULONGLONG ViewSize;
        ULONGLONG ViewBase;
    } REMOTE_PORT_VIEW64, *PREMOTE_PORT_VIEW64;

    typedef struct _LPCP_NONPAGED_PORT_QUEUE
    {
        KSEMAPHORE Semaphore;       // Counting semaphore that is incremented
                                    // whenever a message is put in receive queue
        struct _LPCP_PORT_OBJECT *BackPointer;
    } LPCP_NONPAGED_PORT_QUEUE, *PLPCP_NONPAGED_PORT_QUEUE;

    typedef struct _LPCP_PORT_QUEUE
    {
        PLPCP_NONPAGED_PORT_QUEUE NonPagedPortQueue;
        PKSEMAPHORE Semaphore;      // Counting semaphore that is incremented
                                    // whenever a message is put in receive queue
        LIST_ENTRY ReceiveHead;     // list of messages to receive
    } LPCP_PORT_QUEUE, *PLPCP_PORT_QUEUE;

    typedef struct _LPCP_PORT_OBJECT
    {
        struct _LPCP_PORT_OBJECT *ConnectionPort;
        struct _LPCP_PORT_OBJECT *ConnectedPort;
        struct _LPCP_PORT_QUEUE MsgQueue;
        CLIENT_ID Creator;
        PVOID ClientSectionBase;
        PVOID ServerSectionBase;
        PVOID PortContext;
        PETHREAD ClientThread;                  // only SERVER_COMMUNICATION_PORT
        SECURITY_QUALITY_OF_SERVICE SecurityQos;
        SECURITY_CLIENT_CONTEXT StaticSecurity;
        LIST_ENTRY LpcReplyChainHead;           // Only in _COMMUNICATION ports
        LIST_ENTRY LpcDataInfoChainHead;        // Only in _COMMUNICATION ports
        union
        {
            PEPROCESS ServerProcess;                // Only in SERVER_CONNECTION ports
            PEPROCESS MappingProcess;               // Only in _COMMUNICATION    ports
        };
        USHORT MaxMessageLength;
        USHORT MaxConnectionInfoLength;
        ULONG Flags;
        KEVENT WaitEvent;                          // Object is truncated for non-waitable ports
    } LPCP_PORT_OBJECT, *PLPCP_PORT_OBJECT;

    typedef struct _LPCP_MESSAGE
    {
        union
        {
            LIST_ENTRY Entry;
            struct
            {
                SINGLE_LIST_ENTRY FreeEntry;
                ULONG Reserved0;
            };
        };

        PVOID SenderPort;
        PETHREAD RepliedToThread;               // Filled in when reply is sent so recipient
                                                // of reply can dereference it.
        PVOID PortContext;                      // Captured from senders communication port.
        PORT_MESSAGE Request;
    } LPCP_MESSAGE, *PLPCP_MESSAGE;
}

#include "LPC\build_7600.inl"
#include "LPC\build_7601.inl"
#include "LPC\build_9200.inl"
#include "LPC\build_9600.inl"
#include "LPC\build_10240.inl"
#include "LPC\build_10586.inl"
#include "LPC\build_14393.inl"
#include "LPC\build_15063.inl"
#include "LPC\build_16299.inl"
#include "LPC\build_17134.inl"
#include "LPC\build_17763.inl"
