//
// Copyright (C) C0000374
//
// Çàãðóç÷èê îâåðëåÿ
//
#include <WINDOWS.H>

typedef void(__stdcall* POVERLAYMAIN) (PVOID, PVOID, PVOID, PVOID, PVOID);

void __stdcall WinMainCRTStartup(void) {

	HANDLE			hOverlay;
	DWORD			FileSize;
	PVOID			pOverlay;
	DWORD			NumberOfBytesRead;
	HMODULE			Kernel32;
	PVOID			pLoadLibrary;
	PVOID			pGetProcAddress;
	PVOID			pVirtualAlloc;
	PVOID			pVirtualFree;
	POVERLAYMAIN	pOverlayMain;

	hOverlay = CreateFileW(
		L"OVERLAY.BIN",
		GENERIC_READ,
		FILE_SHARE_READ,
		NULL,
		OPEN_EXISTING,
		0,
		NULL
	);
	if (hOverlay == INVALID_HANDLE_VALUE) ExitProcess(1);

	FileSize = GetFileSize(hOverlay, NULL);

	pOverlay = VirtualAlloc(
		NULL,
		FileSize,
		MEM_RESERVE | MEM_COMMIT,
		PAGE_EXECUTE_READWRITE
	);
	if (!pOverlay) {

		CloseHandle(hOverlay);
		ExitProcess(1);
	}

	ReadFile(
		hOverlay,
		pOverlay,
		FileSize,
		&NumberOfBytesRead,
		NULL
	);

	CloseHandle(hOverlay);

	Kernel32 = GetModuleHandleW(L"KERNEL32.DLL");
	pLoadLibrary = (PVOID)GetProcAddress(Kernel32, "LoadLibraryA");
	pGetProcAddress = (PVOID)GetProcAddress(Kernel32, "GetProcAddress");
	pVirtualAlloc = (PVOID)GetProcAddress(Kernel32, "VirtualAlloc");
	pVirtualFree = (PVOID)GetProcAddress(Kernel32, "VirtualFree");
	pOverlayMain = (POVERLAYMAIN)pOverlay;

	pOverlayMain(
		pLoadLibrary,
		pGetProcAddress,
		pVirtualAlloc,
		pVirtualFree,
		pOverlay
	);

	VirtualFree(
		pOverlay,
		0,
		MEM_RELEASE
	);

	ExitProcess(0);

}
