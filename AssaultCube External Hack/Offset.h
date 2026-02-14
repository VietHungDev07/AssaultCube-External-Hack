#pragma once
#include "includes.h"

namespace Offset {
	DWORD ViewMatrix = 0x57DFD0;
	DWORD ManagerObject = 0x58AC00;
	DWORD LocalPlayer = 0x0;
	DWORD EntityList = 0x4;
	DWORD MaxPlayer = 0x8;
	DWORD TotalPlayerInMatch = 0xC;
	DWORD Health = 0xEC;
	vector<DWORD> Ammo = { 0x364,0x14,0x0 };
	DWORD Position = 0x4;
	DWORD RootPosition = 0x28;

}