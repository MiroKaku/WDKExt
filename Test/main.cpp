#include <ntddk.h>
#include <wdm.h>
#include <wdk.h>


VOID DriverUnload(PDRIVER_OBJECT /*aDriverObject*/)
{

}

EXTERN_C DRIVER_INITIALIZE DriverEntry;
EXTERN_C NTSTATUS DriverEntry(PDRIVER_OBJECT aDriverObject, PUNICODE_STRING /*aRegistryPath*/)
{
	NTSTATUS vResult = STATUS_UNSUCCESSFUL;

	for (;;)
	{
		vResult = wdk::WdkInitSystem();
		if (!NT_SUCCESS(vResult))
		{
			DbgPrintEx(DPFLTR_IHVDRIVER_ID, DPFLTR_ERROR_LEVEL,
				"!!ERROR!! WdkInitSystem Result=0x%08X\n", vResult);
		}

		aDriverObject->DriverUnload = DriverUnload;
		break;
	}

	return vResult;
}
