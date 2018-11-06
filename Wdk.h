#pragma once
#pragma warning(push)
#pragma warning(disable: 4201)


/* wdm */
#if !defined(_WDMDDK_) && !defined(__FLTKERNEL__)
#error "Must include <wdm.h> or <FltKernel.h>"
#endif

#if defined(_WDM_INCLUDED_)
#error "Must first include <ntddk.h>"
#endif

/* sys */

#include <intrin.h>
#include <stdlib.h>
#include <ntimage.h>

/* ext */

#include "Wdk\Native.inl"
#include "Wdk\CmKernel.inl"
#include "Wdk\DbgKernel.inl"
#include "Wdk\ExKernel.inl"
#include "Wdk\FsKernel.inl"
#include "Wdk\IoKernel.inl"
#include "Wdk\KeKernel.inl"
#include "Wdk\LPCKernel.inl"
#include "Wdk\MmKernel.inl"
#include "Wdk\ObKernel.inl"
#include "Wdk\PsKernel.inl"
#include "Wdk\TsKernel.inl"
#include "Wdk\RtlKernel.inl"
#include "Wdk\SeKernel.inl"
#include "Wdk\WmiKernel.inl"
#include "Wdk\NetKernel.inl"
#include "Wdk\ZwKernel.inl"


namespace wdk
{

    inline auto WdkInitSystem() -> NTSTATUS
    {
#define SuccessCheck$(x) if (!NT_SUCCESS(vStatus = (x))) break

        auto vStatus = STATUS_SUCCESS;

        for (;;)
        {
            SuccessCheck$(RtlInitSystem());
            SuccessCheck$(CmInitSystem());
            SuccessCheck$(DbgInitSystem());
            SuccessCheck$(ExInitSystem());
            SuccessCheck$(FsInitSystem());
            SuccessCheck$(IoInitSystem());
            SuccessCheck$(KeInitSystem());
            SuccessCheck$(LPCInitSystem());
            SuccessCheck$(MmInitSystem());
            SuccessCheck$(ObInitSystem());
            SuccessCheck$(PsInitSystem());
            SuccessCheck$(TsInitSystem());
            SuccessCheck$(SeInitSystem());
            SuccessCheck$(WmiInitSystem());
            SuccessCheck$(ZwInitSystem());

            break;
        }

        return vStatus;

#undef SuccessCheck$ 
    }

}

#pragma warning(pop)
