# Windows Driver Kit Extesion Header

## Environment

* C++17  
* Windows 7 or higher  
* Arch: X86, AMD64

##  Config

1. `#include <wdk\wdk.h>`
2. Call `wdk::WdkInitSystem()` in `DriverEntry`

```C++
extern"C" 
auto DriverEntry(PDRIVER_OBJECT aDriverObject, PUNICODE_STRING) -> NTSTATUS
{
    auto vStatus = STATUS_SUCCESS;

    for (;;)
    {
        // Just a chestnut(example)

        vStatus = wdk::WdkInitSystem();
        if (!NT_SUCCESS(vStatus))
        {
            break;
        }

        aDriverObject->DriverUnload = DriverUnload;
        break;
    }
    if (!NT_SUCCESS(vStatus))
    {
        DriverUnload(aDriverObject);
    }
    
    return vStatus;
}
```

## Feature

Undocument struct, function and Tips.

E.g
* ETHREAD
* EPROCESS
* Other ...

## Thanks and references

Thanks for the support of these projects

> [MSDN](https://docs.microsoft.com/en-us/)  
> [ReactOS](https://github.com/reactos/reactos)  
> [ProcessHacker](https://github.com/processhacker/processhacker)  
> [wbenny/pdbex](https://github.com/wbenny/pdbex)  
> [wbenny/ntdiff](https://ntdiff.github.io/)  
> [tandasat/HyperPlatform](https://github.com/tandasat/HyperPlatform)

