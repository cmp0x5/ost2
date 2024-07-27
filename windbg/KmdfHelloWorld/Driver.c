#include <ntddk.h>
#include <wdf.h>
DRIVER_INITIALIZE DriverEntry;
EVT_WDF_DRIVER_DEVICE_ADD KmdfHelloWorldEvtDeviceAdd;

NTSTATUS
DriverEntry(
	_In_ PDRIVER_OBJECT DriverObject,
	_In_ PUNICODE_STRING RegistryPath
)
{
	NTSTATUS status = STATUS_SUCCESS;

	// alloc driver configuration object
	WDF_DRIVER_CONFIG config;

	KdPrintEx((DPFLTR_IHVDRIVER_ID, DPFLTR_INFO_LEVEL, "KmdfHelloWorld: DriverEntry\n"));

	// initialize driver config object to register entry point
	// for EvtDeviceAdd callback, KmdfHelloWorldEvtDeviceAdd
	WDF_DRIVER_CONFIG_INIT(&config,
		KmdfHelloWorldEvtDeviceAdd
	);

	// create driver object
	status = WdfDriverCreate(DriverObject,
		RegistryPath,
		WDF_NO_OBJECT_ATTRIBUTES,
		&config,
		WDF_NO_HANDLE
	);
	return status;
}
NTSTATUS
KmdfHelloWorldEvtDeviceAdd(
	_In_ WDFDRIVER Driver,
	_Inout_ PWDFDEVICE_INIT DeviceInit
)
{
	// mark driver object as unreferenced since
	// its unused
	UNREFERENCED_PARAMETER(Driver);

	NTSTATUS status;

	// alloc device object
	WDFDEVICE hDevice;

	// print hello world
	KdPrintEx((DPFLTR_IHVDRIVER_ID, DPFLTR_INFO_LEVEL, "KmdfHelloWorld: KmdfHelloWorldEvtDeviceAdd\n"));

	// create device object
	status = WdfDeviceCreate(&DeviceInit,
		WDF_NO_OBJECT_ATTRIBUTES,
		&hDevice
	);
	return status;
}