#pragma once
#include "MmStruct.inl"
#include "RtlKernel.inl"


namespace wdk
{
    extern"C"
    {

        NTSTATUS NTAPI
            MmCreateSection(
                _Deref_out_ PVOID *SectionObject,
                _In_ ACCESS_MASK DesiredAccess,
                _In_opt_ POBJECT_ATTRIBUTES ObjectAttributes,
                _In_ PLARGE_INTEGER InputMaximumSize,
                _In_ ULONG SectionPageProtection,
                _In_ ULONG AllocationAttributes,
                _In_opt_ HANDLE FileHandle,
                _In_opt_ PFILE_OBJECT FileObject
            );

        NTSTATUS NTAPI
            MmMapViewOfSection(
                _In_ PVOID SectionToMap,
                _In_ PEPROCESS Process,
                __deref_inout_bcount(*CapturedViewSize) PVOID *CapturedBase,
                _In_ ULONG_PTR ZeroBits,
                _In_ SIZE_T CommitSize,
                _Inout_ PLARGE_INTEGER SectionOffset,
                _Inout_ PSIZE_T CapturedViewSize,
                _In_ SECTION_INHERIT InheritDisposition,
                _In_ ULONG AllocationType,
                _In_ ULONG Win32Protect
            );

        NTSTATUS NTAPI
            MmUnmapViewOfSection(
                _In_ PEPROCESS Process,
                _In_ PVOID BaseAddress
            );

        BOOLEAN NTAPI
            MmForceSectionClosed(
                _In_ PSECTION_OBJECT_POINTERS SectionObjectPointer,
                _In_ BOOLEAN DelayClose
            );

        BOOLEAN NTAPI
            MmForceSectionClosedEx(
                _In_ PSECTION_OBJECT_POINTERS SectionObjectPointer,
                _In_ ULONG ForceCloseFlags
            );

        NTSTATUS NTAPI MmCopyVirtualMemory(
            _In_ PEPROCESS   aFromProcess,
            _In_ CONST PVOID aFromAddress,
            _In_ PEPROCESS   aToProcess,
            _Out_ PVOID      aToAddress,
            _In_ SIZE_T      aBufferSize,
            _In_ KPROCESSOR_MODE aPreviousMode,
            _Out_ PSIZE_T    aNumberOfBytesCopied
        );

    }
}



namespace wdk
{
    extern"C"
    {
        
        /*
         * CR4 flags
         */
        enum CR4Flags: SIZE_T
        {
            X86_CR4_VME         = 0x00000001,
            X86_CR4_PVI         = 0x00000002,
            X86_CR4_TSD         = 0x00000004,
            X86_CR4_DE          = 0x00000008,
            X86_CR4_PSE         = 0x00000010,
            X86_CR4_PAE         = 0x00000020,
            X86_CR4_MCE         = 0x00000040,
            X86_CR4_PGE         = 0x00000080,
            X86_CR4_PCE         = 0x00000100,
            X86_CR4_OSFXSR      = 0x00000200,
            X86_CR4_OSXMMEXCPT  = 0x00000400,
        };


        inline auto IsEnablePAE() -> bool
        {
            return __readcr4() & X86_CR4_PAE;
        }


        inline auto MiGetPagingLevels() -> UINT32
        {
#ifdef _WIN64
            return 4;
#else
            if (IsEnablePAE())
            {
                return 3;
            }
            return 2;
#endif
        }


#undef PAGE_SIZE
#undef PTE_PER_PAGE
#undef PDE_PER_PAGE
#undef PTI_SHIFT
#undef PDI_SHIFT
#undef PPI_SHIFT


        constexpr SIZE_T PAGE_SIZE = 4096;


#ifdef _WIN64
        constexpr SIZE_T PTE_PER_PAGE = 512;
        constexpr SIZE_T PDE_PER_PAGE = 512;
        constexpr SIZE_T PPE_PER_PAGE = 512;
        constexpr SIZE_T PXE_PER_PAGE = 512;

        constexpr SIZE_T PXE_SIZE = PAGE_SIZE;
        constexpr SIZE_T PPE_SIZE = PXE_SIZE * PXE_PER_PAGE;
        constexpr SIZE_T PDE_SIZE = PPE_SIZE * PPE_PER_PAGE;
        constexpr SIZE_T PTE_SIZE = PDE_SIZE * PDE_PER_PAGE;

        constexpr SIZE_T PTI_MASK  = 0xFFFFFFFFFull;
        constexpr SIZE_T PDI_MASK  = 0x7FFFFFFull;
        constexpr SIZE_T PPI_MASK  = 0x3FFFFull;
        constexpr SIZE_T PXI_MASK  = 0x1FFull;

        constexpr SIZE_T PTI_SHIFT = 12;
        constexpr SIZE_T PDI_SHIFT = 21;
        constexpr SIZE_T PPI_SHIFT = 30;
        constexpr SIZE_T PXI_SHIFT = 39;

        constexpr SIZE_T PTE_BASE_CONST     = 0xFFFFF68000000000UI64;
        constexpr SIZE_T PDE_BASE_CONST     = ((PTE_BASE_CONST & 0x0000FFFFFFFFF000) >> 12) * 8 + PTE_BASE_CONST;   //0xFFFFF6FB40000000UI64;
        constexpr SIZE_T PPE_BASE_CONST     = ((PDE_BASE_CONST & 0x0000FFFFFFFFF000) >> 12) * 8 + PTE_BASE_CONST;   //0xFFFFF6FB7DA00000UI64;
        constexpr SIZE_T PXE_BASE_CONST     = ((PPE_BASE_CONST & 0x0000FFFFFFFFF000) >> 12) * 8 + PTE_BASE_CONST;   //0xFFFFF6FB7DBED000UI64;
        constexpr SIZE_T PXE_SELFMAP_CONST  = ((PXE_BASE_CONST & 0x0000FFFFFFFFF000) >> 12) * 8 + PTE_BASE_CONST;   //0xFFFFF6FB7DBEDF68UI64;

        __declspec(selectany) SIZE_T PTE_BASE   = PTE_BASE_CONST;
        __declspec(selectany) SIZE_T PDE_BASE   = PDE_BASE_CONST;
        __declspec(selectany) SIZE_T PPE_BASE   = PPE_BASE_CONST;
        __declspec(selectany) SIZE_T PXE_BASE   = PXE_BASE_CONST;
        __declspec(selectany) SIZE_T PXE_SELFMAP= PXE_SELFMAP_CONST;

        __declspec(selectany) SIZE_T PXE_TOP    = PXE_BASE_CONST + PXE_SIZE - 1;
        __declspec(selectany) SIZE_T PPE_TOP    = PPE_BASE_CONST + PPE_SIZE - 1;
        __declspec(selectany) SIZE_T PDE_TOP    = PDE_BASE_CONST + PDE_SIZE - 1;
        __declspec(selectany) SIZE_T PTE_TOP    = PTE_BASE_CONST + PTE_SIZE - 1;


        inline auto MiInitPteBase(SIZE_T* aPteBase) 
            -> NTSTATUS
        {
            auto vStatus = STATUS_SUCCESS;

            for (;;)
            {
                if (!IsWindowsRedstone1OrGreater())
                {
                    *aPteBase = PTE_BASE;
                    break;
                }

                constexpr auto cName = UNICODE_STRING(RTL_CONSTANT_STRING(L"MmGetVirtualForPhysical"));
                static UINT8 sSearchPatten[] =
                {
                    // mov     rax,[rax + rdx * 8]
                    // shl     rax, 19h
                    // mov     rdx, PTE_BASE

                    0x48, 0x8B, 0x04, 0xD0,
                    0x48, 0xC1, 0xE0, 0x19,
                    0x48, 0xBA, // 00 00 00 00 80 F6 FF FF
                };

                auto vSearchAddress = (UINT8*)MmGetSystemRoutineAddress(const_cast<PUNICODE_STRING>(&cName));
                if (nullptr == vSearchAddress)
                {
                    vStatus = STATUS_NOT_FOUND;
                    break;
                }

                UINT8* vHitAddress = nullptr;
                for (auto i = 0u; i < 0x60; ++i)
                {
                    if (sizeof(sSearchPatten) == RtlCompareMemory(
                        &vSearchAddress[i], sSearchPatten, sizeof(sSearchPatten)))
                    {
                        vHitAddress = &vSearchAddress[i];
                        break;
                    }
                }
                if (nullptr == vHitAddress)
                {
                    vStatus = STATUS_NOT_FOUND;
                    break;
                }

                *aPteBase = *(SIZE_T*)(vHitAddress + sizeof(sSearchPatten));
                break;
            }

            return vStatus;
        }


        inline auto MiInitPtes(SIZE_T aPteBase)
            -> void
        {
            PTE_BASE    = aPteBase;                                                 //0xFFFFF68000000000UI64;
            PDE_BASE    = ((PTE_BASE & 0x0000FFFFFFFFF000) >> 12) * 8 + PTE_BASE;   //0xFFFFF6FB40000000UI64;
            PPE_BASE    = ((PDE_BASE & 0x0000FFFFFFFFF000) >> 12) * 8 + PTE_BASE;   //0xFFFFF6FB7DA00000UI64;
            PXE_BASE    = ((PPE_BASE & 0x0000FFFFFFFFF000) >> 12) * 8 + PTE_BASE;   //0xFFFFF6FB7DBED000UI64;
            PXE_SELFMAP = ((PXE_BASE & 0x0000FFFFFFFFF000) >> 12) * 8 + PTE_BASE;   //0xFFFFF6FB7DBEDF68UI64;

            PXE_TOP = PXE_BASE + PXE_SIZE - 1;
            PPE_TOP = PPE_BASE + PPE_SIZE - 1;
            PDE_TOP = PDE_BASE + PDE_SIZE - 1;
            PTE_TOP = PTE_BASE + PTE_SIZE - 1;
        }


        inline auto MiPxeToAddress(__in PHARDWARE_PTE aPointerPxe)
            -> void*
        {
            return reinterpret_cast<void*>(
                (reinterpret_cast<LONG64>(aPointerPxe) << 52) >> 16);
        }


        inline auto MiPpeToAddress(__in PHARDWARE_PTE aPointerPpe)
            -> void*
        {
            return reinterpret_cast<void*>(
                (reinterpret_cast<LONG64>(aPointerPpe) << 43) >> 16);
        }


        inline auto MiPdeToAddress(__in PHARDWARE_PTE aPointerPde)
            -> void*
        {
            return reinterpret_cast<void*>(
                (reinterpret_cast<LONG64>(aPointerPde) << 34) >> 16);
        }


        inline auto MiPteToAddress(__in PHARDWARE_PTE aPointerPte)
            -> void*
        {
            return reinterpret_cast<void*>(
                (reinterpret_cast<LONG64>(aPointerPte) << 25) >> 16);
        }


        inline auto MiAddressToPxe(__in void* aAddress)
            -> PHARDWARE_PTE
        {
            const auto Address  = reinterpret_cast<SIZE_T>(aAddress);
            const auto Index    = (Address >> PXI_SHIFT) & PXI_MASK;
            const auto Offset   = Index * sizeof(HARDWARE_PTE);
            return reinterpret_cast<PHARDWARE_PTE>(PXE_BASE + Offset);
        }


        inline auto MiAddressToPpe(__in void* aAddress)
            -> PHARDWARE_PTE
        {
            const auto Address  = reinterpret_cast<SIZE_T>(aAddress);
            const auto Index    = (Address >> PPI_SHIFT) & PPI_MASK;
            const auto Offset   = Index * sizeof(HARDWARE_PTE);
            return reinterpret_cast<PHARDWARE_PTE>(PPE_BASE + Offset);
        }
#else
        /* Non PAE */
        constexpr SIZE_T PTE_PER_PAGE_NON_PAE = 1024;
        constexpr SIZE_T PDE_PER_PAGE_NON_PAE = 1024;
        constexpr SIZE_T PPE_PER_PAGE_NON_PAE = 1;

        constexpr SIZE_T PDE_SIZE_NON_PAE   = PAGE_SIZE * PPE_PER_PAGE_NON_PAE;
        constexpr SIZE_T PTE_SIZE_NON_PAE   = PDE_SIZE_NON_PAE * PDE_PER_PAGE_NON_PAE;

        constexpr SIZE_T PTI_SHIFT_NON_PAE  = 12;
        constexpr SIZE_T PDI_SHIFT_NON_PAE  = 22;

        constexpr SIZE_T PPI_BITS_NON_PAE   = 0;
        constexpr SIZE_T PDI_BITS_NON_PAE   = 10;
        constexpr SIZE_T PTI_BITS_NON_PAE   = 10;
        
        constexpr SIZE_T PPI_MASK_NON_PAE   = ((1 << PPI_BITS_NON_PAE) - 1);
        constexpr SIZE_T PDI_MASK_NON_PAE   = ((1 << (PDI_BITS_NON_PAE + PPI_BITS_NON_PAE)) - 1);
        constexpr SIZE_T PTI_MASK_NON_PAE   = ((1 << (PTI_BITS_NON_PAE + PDI_BITS_NON_PAE + PPI_BITS_NON_PAE)) - 1);
        
        constexpr SIZE_T PTE_BASE_NON_PAE   = 0xC0000000;
        constexpr SIZE_T PDE_BASE_NON_PAE   = 0xC0300000;
        constexpr SIZE_T PDE_TOP_NON_PAE    = PDE_BASE_NON_PAE + PDE_SIZE_NON_PAE - 1;
        constexpr SIZE_T PTE_TOP_NON_PAE    = PTE_BASE_NON_PAE + PTE_SIZE_NON_PAE - 1;
        
        /* PAE */
        constexpr SIZE_T PTE_PER_PAGE_PAE   = 512; // (PAGE_SIZE / sizeof(HARDWARE_PTE));
        constexpr SIZE_T PDE_PER_PAGE_PAE   = 512;
        constexpr SIZE_T PPE_PER_PAGE_PAE   = 4;

        constexpr SIZE_T PDE_SIZE_PAE   = PAGE_SIZE * PPE_PER_PAGE_PAE;
        constexpr SIZE_T PTE_SIZE_PAE   = PDE_SIZE_PAE * PDE_PER_PAGE_PAE;

        constexpr SIZE_T PTI_SHIFT_PAE  = 12;
        constexpr SIZE_T PDI_SHIFT_PAE  = 21;

        constexpr SIZE_T PPI_BITS_PAE   = 2;
        constexpr SIZE_T PDI_BITS_PAE   = 9;
        constexpr SIZE_T PTI_BITS_PAE   = 9;

        constexpr SIZE_T PPI_MASK_PAE   = ((1 << PPI_BITS_PAE) - 1);
        constexpr SIZE_T PDI_MASK_PAE   = ((1 << (PDI_BITS_PAE + PPI_BITS_PAE)) - 1);
        constexpr SIZE_T PTI_MASK_PAE   = ((1 << (PTI_BITS_PAE + PDI_BITS_PAE + PPI_BITS_PAE)) - 1);

        constexpr SIZE_T PTE_BASE_PAE   = 0xC0000000;
        constexpr SIZE_T PDE_BASE_PAE   = 0xC0600000;
        constexpr SIZE_T PDE_TOP_PAE    = PDE_BASE_PAE + PDE_SIZE_PAE - 1;
        constexpr SIZE_T PTE_TOP_PAE    = PTE_BASE_PAE + PTE_SIZE_PAE - 1;

        /* Unused */
        constexpr SIZE_T PXE_BASE   = 0;
        constexpr SIZE_T PPE_BASE   = 0;
        constexpr SIZE_T PSI_SHIFT  = 0;
        constexpr SIZE_T PPI_SHIFT  = 0;
        constexpr SIZE_T PXI_MASK   = 0;

        /* dynamic */
        __declspec(selectany) SIZE_T PTE_PER_PAGE   = 0;
        __declspec(selectany) SIZE_T PDE_PER_PAGE   = 0;
        __declspec(selectany) SIZE_T PPE_PER_PAGE   = 0;

        __declspec(selectany) SIZE_T PTI_SHIFT  = 0;
        __declspec(selectany) SIZE_T PDI_SHIFT  = 0;

        __declspec(selectany) SIZE_T PPI_MASK   = 0;
        __declspec(selectany) SIZE_T PDI_MASK   = 0;
        __declspec(selectany) SIZE_T PTI_MASK   = 0;

        __declspec(selectany) SIZE_T PTE_BASE   = 0;
        __declspec(selectany) SIZE_T PDE_BASE   = 0;
        __declspec(selectany) SIZE_T PDE_TOP    = 0;
        __declspec(selectany) SIZE_T PTE_TOP    = 0;


        inline auto MiInitPteBase(SIZE_T* aPteBase)
            -> NTSTATUS
        {
            if (IsEnablePAE())
            {
                *aPteBase = PTE_BASE_PAE;
            }
            else
            {
                *aPteBase = PTE_BASE;
            }

            return STATUS_SUCCESS;
        }


        inline auto MiInitPtes(SIZE_T aPteBase)
            -> void
        {
            if (aPteBase == PTE_BASE_NON_PAE)
            {
                PTE_PER_PAGE = PTE_PER_PAGE_NON_PAE;
                PDE_PER_PAGE = PDE_PER_PAGE_NON_PAE;
                PPE_PER_PAGE = PPE_PER_PAGE_NON_PAE;
                PTI_SHIFT   = PTI_SHIFT_NON_PAE;
                PDI_SHIFT   = PDI_SHIFT_NON_PAE;
                PPI_MASK    = PPI_MASK_NON_PAE;
                PTI_MASK    = PTI_MASK_NON_PAE;
                PDI_MASK    = PDI_MASK_NON_PAE;
                PDE_BASE    = PDE_BASE_NON_PAE;
                PDE_TOP     = PDE_TOP_NON_PAE;
                PTE_TOP     = PTE_TOP_NON_PAE;
            }
            else
            {
                PTE_PER_PAGE = PTE_PER_PAGE_PAE;
                PDE_PER_PAGE = PDE_PER_PAGE_PAE;
                PPE_PER_PAGE = PPE_PER_PAGE_PAE;
                PTI_SHIFT   = PTI_SHIFT_PAE;
                PDI_SHIFT   = PDI_SHIFT_PAE;
                PPI_MASK    = PPI_MASK_PAE;
                PTI_MASK    = PTI_MASK_PAE;
                PDI_MASK    = PDI_MASK_PAE;
                PDE_BASE    = PDE_BASE_PAE;
                PDE_TOP     = PDE_TOP_PAE;
                PTE_TOP     = PTE_TOP_PAE;
            }
        }


        inline auto MiPpeToAddress(__in PHARDWARE_PTE /*aPointerPpe*/)
            -> void*
        {
            return nullptr;
        }


        inline auto MiPdeToAddress(__in PHARDWARE_PTE aPointerPde)
            -> void*
        {
            return reinterpret_cast<void*>(
                (reinterpret_cast<LONG>(aPointerPde) << 20));
        }


        inline auto MiPteToAddress(__in PHARDWARE_PTE aPointerPte)
            -> void*
        {
            return reinterpret_cast<void*>(
                (reinterpret_cast<LONG>(aPointerPte) << 10));
        }
#endif


        inline auto MiAddressToPde(__in void* aAddress)
            -> PHARDWARE_PTE
        {
            const auto Address = reinterpret_cast<SIZE_T>(aAddress);
            const auto Index = (Address >> PDI_SHIFT) & PDI_MASK;
            const auto Offset = Index * sizeof(HARDWARE_PTE);
            return reinterpret_cast<PHARDWARE_PTE>(PDE_BASE + Offset);
        }


        inline auto MiAddressToPte(__in void* aAddress)
            -> PHARDWARE_PTE
        {
            const auto Address = reinterpret_cast<SIZE_T>(aAddress);
            const auto Index = (Address >> PTI_SHIFT) & PTI_MASK;
            const auto Offset = Index * sizeof(HARDWARE_PTE);
            return reinterpret_cast<PHARDWARE_PTE>(PTE_BASE + Offset);
        }


        inline auto MmInitSystem() -> NTSTATUS
        {
            auto vStatus = STATUS_SUCCESS;

            for (;;)
            {
                SIZE_T vPteBase = PTE_BASE;
                vStatus = MiInitPteBase(&vPteBase);
                if (!NT_SUCCESS(vStatus))
                {
                    break;
                }
                
                MiInitPtes(vPteBase);
                break;
            }

            return vStatus;
        }
    }
}

using wdk::PAGE_SIZE;
