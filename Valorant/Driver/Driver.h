#pragma once
#include <Windows.h>
#include <cstdio>
#include <cstdint>

#define INVALID_POINTER(x) ((DWORD64)x == 0 || (DWORD64)x == 0xffffffffffffffff)

typedef struct _Command
{
	int Source;
	int Target;
	DWORD64 SourceAddress;
	DWORD64 TargetAddress;
	DWORD64 Size;
} Command;

#define IOCTL_COMMAND CTL_CODE(FILE_DEVICE_UNKNOWN, 0xFEED, METHOD_BUFFERED, FILE_ANY_ACCESS)

typedef struct _ModInfo
{
	int Target;
	wchar_t Name[256];
	DWORD64 BaseAddress;
	ULONG Size;
} ModInfo;

#define IOCTL_MODINFO CTL_CODE(FILE_DEVICE_UNKNOWN, 0xFEED2, METHOD_BUFFERED, FILE_ANY_ACCESS)

HANDLE DriverHandle;
int CurrentProcessPid;
int TargetProcessPid;

#define MAX_VIRTUAL_USERMODE 0x7FFFFFFFFFFF
#define MIN_VIRTUAL_USERMODE 0x10000


bool InitDriver(int targetPid)
{
	DriverHandle = CreateFileA("\\\\.\\PhysicalDrive0", GENERIC_ALL, FILE_SHARE_READ | FILE_SHARE_WRITE, nullptr, OPEN_EXISTING, NULL, nullptr);
	if (DriverHandle == INVALID_HANDLE_VALUE)
		return false;

	CurrentProcessPid = GetCurrentProcessId();
	TargetProcessPid = targetPid;

	return true;
}

void SendCommand(Command* cmd)
{
	DWORD returned = 0;
	bool status = DeviceIoControl(DriverHandle, IOCTL_COMMAND, cmd, sizeof(Command), cmd, sizeof(Command), &returned, nullptr);

	if (!status)
	{
		printf("Err: %x\n", GetLastError());
	}
}

void CopyVirtual(bool read, uint64_t destination, uint64_t source, SIZE_T size)
{
	if (destination > MAX_VIRTUAL_USERMODE)
		return;
	if (destination < MIN_VIRTUAL_USERMODE)
		return;
	if (source > MAX_VIRTUAL_USERMODE)
		return;
	if (source < MIN_VIRTUAL_USERMODE)
		return;

	Command cmd;
	cmd.Source = read ? TargetProcessPid : CurrentProcessPid;
	cmd.Target = read ? CurrentProcessPid : TargetProcessPid;
	cmd.SourceAddress = source;
	cmd.TargetAddress = destination;
	cmd.Size = size;

	SendCommand(&cmd);
}

DWORD64 GetModuleInfo(PCWCHAR moduleName, ULONG* size)
{
	ModInfo info = { 0 };
	info.Target = TargetProcessPid;
	memcpy(info.Name, moduleName, wcslen(moduleName) * sizeof(wchar_t));

	DWORD returned = 0;
	bool status = DeviceIoControl(DriverHandle, IOCTL_MODINFO, &info, sizeof(ModInfo), &info, sizeof(ModInfo), &returned, nullptr);

	if (!status)
		return 0;

	if (size)
		*size = info.Size;

	return info.BaseAddress;
}

void Close()
{
	CloseHandle(DriverHandle);
}

template<typename T>
T Read(uint64_t address)
{
	T val = T();
	CopyVirtual(true, reinterpret_cast<uint64_t>(&val), address, sizeof(T));
	return val;
}

template<typename T>
void read_array(uint64_t address, T * array, size_t len) {
	CopyVirtual(true, (uint64_t)array, address, sizeof(T) * len);
}

template<typename T>
void Write(uint64_t address, T val)
{
	CopyVirtual(false, address, reinterpret_cast<uint64_t>(&val), sizeof(T));
}
