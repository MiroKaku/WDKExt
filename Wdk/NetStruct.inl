#pragma once


namespace wdk
{


    enum class NetworkAdapterCharacteristics : UINT32
    {
        NCF_VIRTUAL                     = 0x00000001,
        NCF_SOFTWARE_ENUMERATED         = 0x00000002,
        NCF_PHYSICAL                    = 0x00000004,
        NCF_HIDDEN                      = 0x00000008,
        NCF_NO_SERVICE                  = 0x00000010,
        NCF_NOT_USER_REMOVABLE          = 0x00000020,
        NCF_MULTIPORT_INSTANCED_ADAPTER = 0x00000040,
        NCF_HAS_UI                      = 0x00000080,
        NCF_SINGLE_INSTANCE             = 0x00000100,
        NCF_FILTER                      = 0x00000400,
        NCF_DONTEXPOSELOWER             = 0x00001000,
        NCF_HIDE_BINDING                = 0x00002000,
        NCF_NDIS_PROTOCOL               = 0x00004000,
        NCF_FIXED_BINDING               = 0x00020000,
        NCF_LW_FILTER                   = 0x00040000
    };


    enum class AddressFamily : UINT16
    {
        Unspecified     = 0,    // Unspecified address family
        Unix            = 1,    // Unix local to host address
        InterNetwork    = 2,    // Address for IP version 4
        ImpLink         = 3,    // ARPANET IMP address
        Pup             = 4,    // Address for PUP protocols
        Chaos           = 5,    // Address for MIT CHAOS protocols
        Ipx             = 6,    // IPX or SPX address
        XeroxNS         = 6,    // Address for Xerox NS protocols
        Iso             = 7,    // Address for ISO protocols
        Osi             = 7,    // Address for OSI protocols
        Ecma            = 8,    // European Computer Manufacturers Association (ECMA) address
        DataKit         = 9,    // Address for Datakit protocols
        Ccitt           = 10,   // Addresses for CCITT protocols, such as X.25.
        Sna             = 11,   // IBM SNA address
        DecNet          = 12,   // DECnet address
        DataLink        = 13,   // Direct data-link interface address
        Lat             = 14,   // LAT address
        HyperChannel    = 15,   // NSC Hyperchannel address
        Appletalk       = 16,   // AppleTalk address
        NetBios         = 17,   // NetBios address
        VoiceView       = 18,   // VoiceView address
        FireFox         = 19,   // FireFox address
        Banyan          = 21,   // Banyan address
        Atm             = 22,   // Native ATM services address
        InterNetworkV6  = 23,   // Address for IP version 6
        Cluster         = 24,   // Address for Microsoft cluster products
        Ieee12844       = 25,   // IEEE 1284.4 workgroup address
        InfraredData    = 26,   // IrDA address
        NetworkDesigners= 28,   // Address for Network Designers OSI gateway-enabled protocols
        Bluetooth       = 32,   // Bluetooth address

        Max             = 35
    };

}
