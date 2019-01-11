#ifndef PROCTOOLS_
#define PROCTOOLS_

#include <Windows.h>
#include <TlHelp32.h>
#include <iostream>
#include <string>

using namespace std;

DWORD GetProcessID(string appname) {
	PROCESSENTRY32 procSentry;
	HANDLE handle;
	procSentry.dwSize = sizeof(PROCESSENTRY32);
	handle = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	while (Process32Next(handle, &procSentry))
	{
		if (strcmp(appname.c_str(), procSentry.szExeFile) == 0) {
			CloseHandle(handle);
			return procSentry.th32ProcessID;
		}
	}
	CloseHandle(handle);
	return -1;
}

DWORD GetProcessModule(string modName, DWORD pid) {
	MODULEENTRY32 modEntry;
	HANDLE handle;
	modEntry.dwSize = sizeof(MODULEENTRY32);
	handle = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, pid);
	while (Module32Next(handle, &modEntry))
	{
		if (strcmp(modName.c_str(), modEntry.szModule) == 0) {
			CloseHandle(handle);
			return (DWORD)modEntry.modBaseAddr;
		}
	}
	CloseHandle(handle);
	return -1;
}

template<class T=DWORD>
BOOL Write(DWORD address, T value, DWORD pid) {
	T toWrite = value;
	HANDLE handle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
	BOOL bSuccess = WriteProcessMemory(handle, (LPVOID)address, (LPVOID)&toWrite, sizeof(toWrite), NULL);
	CloseHandle(handle);
	return bSuccess;
}

template<class T=DWORD>
T Read(DWORD address, DWORD pid) {
	T toRead;
	HANDLE handle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
	BOOL bSuccess = ReadProcessMemory(handle, (LPVOID)address, &toRead, sizeof(toRead), NULL);
	CloseHandle(handle);
	if(bSuccess)
		return toRead;
	toRead = -1;
	return toRead;
}

#endif
