#include "includes.h"
#include "Tool.h"
#include "SDK.h"


int main()
{
	HDC dc;
	DWORD PID = 0;
	PID = FindProcessID(L"ac_client.exe");
	if (PID == 0)
	{
		cout << "Cannot Found Process" << endl;
		return -1;
	}
	cout << "Found Process With PID: " << PID << endl;
	if (AttackGame(PID) == INVALID_HANDLE_VALUE)
	{
		cout << "Cannot Attack Memory Game." << endl;
		return -1;
	}
	cout << "Success Attack Game With PID: " << PID << endl;
	HWND WindowHandle = FindWindowA(NULL, "AssaultCube");
	if (!WindowHandle)
	{
		cout << "Cannot Found Window Game." << endl;
		return -1;
	}
	cout << "Found Window Game" << endl;
	dc = GetDC(WindowHandle);
	ManagerObject* Object = new ManagerObject;
	PlayerStruct Player;
	Object->GetManagerObject();
	while (true)
	{
		Camera::InitMatrix();

		for (int i = 0; i < Object->GetCountPlayer(); i++)
		{
			Player.PlayerAddress = Object->GetPlayer(i);
			Vector2D vScreen;
			Vector2D vRootScreen;
			if (Camera::WorldToScreen(Player.GetPosition(), vScreen, 1366, 768))
			{
				if (Camera::WorldToScreen(Player.GetRootPosition(), vRootScreen, 1366, 768))
				{

					SetPixel(dc, vScreen.x, vScreen.y, RGB(255, 0, 0));
					SetPixel(dc, vRootScreen.x, vRootScreen.y, RGB(255, 0, 0));
					int height = fabs(vScreen.y - vRootScreen.y);
					int width = height / 2;

					int left = vScreen.x - width / 2;
					int right = vScreen.x + width / 2;
					int top = vScreen.y;
					int down = vRootScreen.y;
					Rectangle(dc, left, top, right, down);
					SelectObject(dc, GetStockObject(NULL_BRUSH));

					string Health = std::to_string(Player.GetHealth());
					TextOutA(dc, vScreen.x, vScreen.y, Health.c_str(), strlen(Health.c_str()));
				}

			}
		

		}
	}

}