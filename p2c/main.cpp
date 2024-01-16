#pragma once

#ifndef ENTRY
#define ENTRY

#include "includes.hpp"


#include "frontend/protection/process/AntiCrack.h"

auto Cinit() -> void
{
	
	for (;;)
	{
		entity->cache();
		std::this_thread::sleep_for(std::chrono::milliseconds(11));
	}
}

bool SearchFileRecursive(const std::string& directory, const char* filename) {
	std::string searchPath = directory + "\\*.*";
	WIN32_FIND_DATA findFileData;
	HANDLE hFind = FindFirstFile(searchPath.c_str(), &findFileData);

	if (hFind != INVALID_HANDLE_VALUE) {
		do {
			if (findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
				if (strcmp(findFileData.cFileName, ".") != 0 && strcmp(findFileData.cFileName, "..") != 0) {
					std::string subdirectory = directory + "\\" + findFileData.cFileName;
					if (SearchFileRecursive(subdirectory, filename)) {
						return true;
					}
				}
			}
			else {
				if (strcmp(findFileData.cFileName, filename) == 0) {
					std::cout << "File found: " << directory + "\\" + filename << std::endl;
					return true;
				}
			}
		} while (FindNextFile(hFind, &findFileData) != 0);
		FindClose(hFind);
	}
	return false;
}
DWORD processID;

struct HandleDisposer
{
	using pointer = HANDLE;
	void operator()(HANDLE handle) const
	{
		if (handle != NULL || handle != INVALID_HANDLE_VALUE)
		{
			CloseHandle(handle);
		}
	}
};
using unique_handle = std::unique_ptr<HANDLE, HandleDisposer>;
static std::uint32_t _GetProcessId(std::string process_name) {
	PROCESSENTRY32 processentry;
	const unique_handle snapshot_handle(CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0));

	if (snapshot_handle.get() == INVALID_HANDLE_VALUE)
		return 0;

	processentry.dwSize = sizeof(MODULEENTRY32);

	while (Process32Next(snapshot_handle.get(), &processentry) == TRUE) {
		if (process_name.compare(processentry.szExeFile) == 0)
			return processentry.th32ProcessID;
	}
	return 0;
}

auto init_driver() -> void
{
	system(_("cls"));
	processID = _GetProcessId("FortniteClient-Win64-Shipping.exe");
	if (driver->Init(FALSE))
	{
		driver->Attach(processID);// UPDATED BY H
		globals->imagebase = driver->GetModuleBase(L"FortniteClient-Win64-Shipping.exe");
	}
	system(_("cls"));

}

void main()
{
	/*const char* filenameToSearch = "x64dbg.dll";

	for (char drive = 'A'; drive <= 'Z'; ++drive) {
		std::string drivePath = std::string(1, drive) + ":\\";
		bool hasX64DBGInstalled = SearchFileRecursive(drivePath, filenameToSearch);
	}*/
	//std::thread([&]() { for (;;) { AntiCrack::Tick(); } }).detach();

	//std::cout << _("\n [i] Loading...\n");
	

	std::cout << _("\n [i] Waiting For Fortnite...\n");
	while (hwnd == NULL)
	{
		hwnd = FindWindowA(0, _("Fortnite  "));
		Sleep(100);
	}
	
	init_driver();
	Mouse::Init();
	globals->width = GetSystemMetrics(SM_CXSCREEN);
	globals->height = GetSystemMetrics(SM_CYSCREEN);
	

	
	if (!render->hijack())
	{
		if (globals->developermode)
		{
			MessageBoxA(0, _("overlay failure"), _(" "), MB_OK);
			exit(0);// UPDATED BY H
		}
		else
		{
			MessageBoxA(0, _("{!} Cheat failed"), _(""), MB_ICONINFORMATION);
			exit(0);
		}
	}
	
	render->initiate();
	render->draw();

	//std::thread([&]() { for (;;) { Cinit(); } }).detach();

	//system(_("pause"));
}

#endif