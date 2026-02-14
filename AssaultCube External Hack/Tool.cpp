#include"Tool.h"
HANDLE ProcessHandle = NULL;
DWORD FindProcessID(const wchar_t* NameProcess) 
{
	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hSnap == INVALID_HANDLE_VALUE || hSnap == NULL)
	{
		return 0;
	}
	PROCESSENTRY32W ProcEntry;
	ProcEntry.dwSize = sizeof(PROCESSENTRY32W);
	if (Process32FirstW(hSnap, &ProcEntry))
	{
		if (_wcsicmp(ProcEntry.szExeFile, NameProcess) == 0)
		{
			CloseHandle(hSnap);
			return ProcEntry.th32ProcessID;
		}

		while (Process32NextW(hSnap, &ProcEntry))
		{
			if (_wcsicmp(ProcEntry.szExeFile, NameProcess) == 0)
			{
				CloseHandle(hSnap);
				return ProcEntry.th32ProcessID;
			}
		}
	}
	return 0;
}

HANDLE AttackGame(DWORD PID)
{
	ProcessHandle = OpenProcess(PROCESS_VM_READ, NULL, PID);
	if (ProcessHandle == INVALID_HANDLE_VALUE || ProcessHandle == NULL)
	{
		return INVALID_HANDLE_VALUE;
	}
	return ProcessHandle;
}