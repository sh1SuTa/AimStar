#include "imports.h"
#include "functions.h"

//https://github.com/beans42/kernel-read-write-using-ioctl
auto real_main(PDRIVER_OBJECT driver_obj, PUNICODE_STRING registery_path) -> NTSTATUS
{
	UNREFERENCED_PARAMETER(registery_path);

	UNICODE_STRING dev_name, sym_link;
	PDEVICE_OBJECT dev_obj;

	RtlInitUnicodeString(&dev_name, L"\\Device\\AimStarDriver"); //�������豸������
	//����һ���豸�������������Դ�������豸����ָ�� dev_obj
	//FILE_DEVICE_UNKNOWN ��ʾһ��δ֪���͵��豸��FILE_DEVICE_SECURE_OPEN ��־��ʾ�豸ֻ֧�ְ�ȫ��
	auto status = IoCreateDevice(driver_obj, 0, &dev_name, FILE_DEVICE_UNKNOWN, FILE_DEVICE_SECURE_OPEN, FALSE, &dev_obj);
	// �����豸����ʧ���򷵻�
	if (status != STATUS_SUCCESS) return status;
	//sym_link ��һ���������ӣ���ָ���豸���ƣ�ʹ���û��ռ�������ͨ�� \\DosDevices\\AimStarDriver �������豸
	RtlInitUnicodeString(&sym_link, L"\\??\\AimStarDriver");
	status = IoCreateSymbolicLink(&sym_link, &dev_name);
	if (status != STATUS_SUCCESS) return status;
	//DO_BUFFERED_IO ��ʾ�豸֧�ֻ��������/���������
	SetFlag(dev_obj->Flags, DO_BUFFERED_IO); 

	//IRP_MJ_CREATE��IRP_MJ_CLOSE �� IRP_MJ_DEVICE_CONTROL ���������������ֻ����������͡�
	//default_dispatch �����������͹رղ�����
	//ioctl_dispatch ���������豸���Ʋ�����IOCTL����
	driver_obj->MajorFunction[IRP_MJ_CREATE] = default_dispatch; //link our io create function
	driver_obj->MajorFunction[IRP_MJ_CLOSE] = default_dispatch; //link our io close function
	driver_obj->MajorFunction[IRP_MJ_DEVICE_CONTROL] = ioctl_dispatch; //link our control code handler
	//����ж��ʱ���õĺ�����ĿǰΪ�գ���ζ��û��ʵ��ж�ع��ܡ�
	driver_obj->DriverUnload = NULL; //add later
	//DO_DEVICE_INITIALIZING ��һ���豸��ʼ���ı�־��ͨ������ ClearFlag �������ʾ�豸��ʼ�����
	ClearFlag(dev_obj->Flags, DO_DEVICE_INITIALIZING); 
	dbg("[AimStar] DRIVER LOADED SUCCEFULLY");
	return status;
}

//�����������ڵ㣬����ϵͳ��������ʱ���øú������˺�������� IoCreateDriver ��������������
//C++11β���������﷨������ֵ����Ϊ NTSTATUS
auto driver_entry() -> const NTSTATUS
{
	UNICODE_STRING  drv_name;
	RtlInitUnicodeString(&drv_name, L"\\Driver\\AimStarDriver");
	return IoCreateDriver(&drv_name, real_main); //so it's kdmapper-able
}