#include "SDK.h"
#include "Tool.h"
#include "Offset.h"

DWORD ManagerObject::GetManagerObject()
{
	Object = Offset::ManagerObject;
	return Object;

}
DWORD ManagerObject::GetLocalPlayer()
{
	DWORD LocalPlayerAddress = 0;
	ReadProcessMemory(ProcessHandle, LPCVOID(Object + Offset::LocalPlayer), &LocalPlayerAddress, sizeof(LocalPlayerAddress), 0);
	return LocalPlayerAddress;
}
DWORD ManagerObject::GetEntityList()
{
	DWORD EntityListAddress = 0;
	ReadProcessMemory(ProcessHandle, LPCVOID(Object + Offset::EntityList), &EntityListAddress, sizeof(EntityListAddress), 0);
	return EntityListAddress;
}
int ManagerObject::GetCountPlayer()
{
	int Count = 0;
	ReadProcessMemory(ProcessHandle, LPCVOID(Object + Offset::TotalPlayerInMatch), &Count, sizeof(Count), 0);
	return Count;
}
int ManagerObject::GetMaxPlayerInMatch()
{
	int Count = 0;
	ReadProcessMemory(ProcessHandle, LPCVOID(Object + Offset::MaxPlayer), &Count, sizeof(Count), 0);
	return Count;
}
DWORD ManagerObject::GetPlayer(int index)
{
	DWORD PlayerAddress = 0;
	ReadProcessMemory(ProcessHandle, LPCVOID(GetEntityList() +index*sizeof(DWORD)), &PlayerAddress, sizeof(PlayerAddress), 0);
	return PlayerAddress;
}

int PlayerStruct::GetHealth()
{
	ReadProcessMemory(ProcessHandle, LPCVOID(PlayerAddress + Offset::Health), &Health, sizeof(Health), 0);
	return Health;
}
int PlayerStruct::GetAmmo()
{
	DWORD pAmmo = PlayerAddress;
	for (int i = 0; i < Offset::Ammo.size(); i++)
	{
		ReadProcessMemory(ProcessHandle, LPCVOID(pAmmo + Offset::Ammo[i]), &pAmmo, sizeof(pAmmo), 0);
	}
	Ammo = (int)pAmmo;
	return Ammo;
}
Vector3D PlayerStruct::GetPosition()
{
	ReadProcessMemory(ProcessHandle, LPCVOID(PlayerAddress + Offset::Position), &Position, sizeof(Position), 0);
	return Position;
}
Vector3D PlayerStruct::GetRootPosition()
{
	ReadProcessMemory(ProcessHandle, LPCVOID(PlayerAddress + Offset::RootPosition), &RootPosition, sizeof(RootPosition), 0);
	return RootPosition;
}
float Camera::ViewMatrix[16];
void Camera::InitMatrix()
{
	ReadProcessMemory(ProcessHandle, LPCVOID(Offset::ViewMatrix), &ViewMatrix, sizeof(ViewMatrix), 0);
}

bool Camera::WorldToScreen(const Vector3D& world, Vector2D& screen, int width, int height)
{
	float clipX = world.x * Camera::ViewMatrix[0] + world.y * Camera::ViewMatrix[4] + world.z * Camera::ViewMatrix[8] + Camera::ViewMatrix[12];
	float clipY = world.x * Camera::ViewMatrix[1] + world.y * Camera::ViewMatrix[5] + world.z * Camera::ViewMatrix[9] + Camera::ViewMatrix[13];
	float clipZ = world.x * Camera::ViewMatrix[2] + world.y * Camera::ViewMatrix[6] + world.z * Camera::ViewMatrix[10] +Camera:: ViewMatrix[14];
	float clipW = world.x * Camera::ViewMatrix[3] + world.y * Camera::ViewMatrix[7] + world.z * Camera::ViewMatrix[11] +Camera:: ViewMatrix[15];

	if (clipW < 0.1f) 
		return false;


	float ndcX = clipX / clipW;
	float ndcY = clipY / clipW;

	screen.x = (width / 2.0f * ndcX) + (ndcX + width / 2.0f);
	screen.y = -(height / 2.0f * ndcY) + (ndcY + height / 2.0f);

	return true;
}

