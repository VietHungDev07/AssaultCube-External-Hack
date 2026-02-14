#pragma once
#include"includes.h"

typedef struct {
	float x;
	float y;
	float z;

} Vector3D;
typedef struct {
	float x;
	float y;
} Vector2D;

class ManagerObject {
public:
	DWORD Object;
	DWORD GetManagerObject();
	DWORD GetLocalPlayer();
	DWORD GetEntityList();
	int GetCountPlayer();
	int GetMaxPlayerInMatch();
	DWORD GetPlayer(int index);
};
class PlayerStruct {
public:
	DWORD PlayerAddress;
	int Health;
	int Ammo;
	Vector3D Position;
	Vector3D RootPosition;

	int GetHealth();
	int GetAmmo();
	Vector3D GetPosition();
	Vector3D GetRootPosition();

};
class Camera 
{
public:
	static float ViewMatrix[16];
	static void InitMatrix();
	static bool WorldToScreen(const Vector3D& world, Vector2D& screen, int width, int height);
};