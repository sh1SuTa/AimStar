#include "imports.h"
#include "functions.h"

//https://github.com/beans42/kernel-read-write-using-ioctl
auto real_main(PDRIVER_OBJECT driver_obj, PUNICODE_STRING registery_path) -> NTSTATUS
{
	UNREFERENCED_PARAMETER(registery_path);

	UNICODE_STRING dev_name, sym_link;
	PDEVICE_OBJECT dev_obj;

	RtlInitUnicodeString(&dev_name, L"\\Device\\AimStarDriver"); //定义了设备的名称
	//创建一个设备对象，它会分配资源并返回设备对象指针 dev_obj
	//FILE_DEVICE_UNKNOWN 表示一个未知类型的设备，FILE_DEVICE_SECURE_OPEN 标志表示设备只支持安全打开
	auto status = IoCreateDevice(driver_obj, 0, &dev_name, FILE_DEVICE_UNKNOWN, FILE_DEVICE_SECURE_OPEN, FALSE, &dev_obj);
	// 创建设备对象失败则返回
	if (status != STATUS_SUCCESS) return status;
	//sym_link 是一个符号链接，它指向设备名称，使得用户空间程序可以通过 \\DosDevices\\AimStarDriver 来访问设备
	RtlInitUnicodeString(&sym_link, L"\\??\\AimStarDriver");
	status = IoCreateSymbolicLink(&sym_link, &dev_name);
	if (status != STATUS_SUCCESS) return status;
	//DO_BUFFERED_IO 表示设备支持缓冲的输入/输出操作。
	SetFlag(dev_obj->Flags, DO_BUFFERED_IO); 

	//IRP_MJ_CREATE、IRP_MJ_CLOSE 和 IRP_MJ_DEVICE_CONTROL 是驱动操作的三种基本操作类型。
	//default_dispatch 函数处理创建和关闭操作。
	//ioctl_dispatch 函数处理设备控制操作（IOCTL）。
	driver_obj->MajorFunction[IRP_MJ_CREATE] = default_dispatch; //link our io create function
	driver_obj->MajorFunction[IRP_MJ_CLOSE] = default_dispatch; //link our io close function
	driver_obj->MajorFunction[IRP_MJ_DEVICE_CONTROL] = ioctl_dispatch; //link our control code handler
	//驱动卸载时调用的函数，目前为空，意味着没有实现卸载功能。
	driver_obj->DriverUnload = NULL; //add later
	//DO_DEVICE_INITIALIZING 是一个设备初始化的标志，通过调用 ClearFlag 清除，表示设备初始化完成
	ClearFlag(dev_obj->Flags, DO_DEVICE_INITIALIZING); 
	dbg("[AimStar] DRIVER LOADED SUCCEFULLY");
	return status;
}

//驱动程序的入口点，操作系统加载驱动时调用该函数。此函数会调用 IoCreateDriver 创建并加载驱动
//C++11尾返回类型语法，返回值类型为 NTSTATUS
auto driver_entry() -> const NTSTATUS
{
	UNICODE_STRING  drv_name;
	RtlInitUnicodeString(&drv_name, L"\\Driver\\AimStarDriver");
	return IoCreateDriver(&drv_name, real_main); //so it's kdmapper-able
}