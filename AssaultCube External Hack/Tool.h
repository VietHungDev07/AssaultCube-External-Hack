#pragma once
#include"includes.h"
extern HANDLE ProcessHandle;
DWORD FindProcessID(const wchar_t* NameProcess);
HANDLE AttackGame(DWORD PID);