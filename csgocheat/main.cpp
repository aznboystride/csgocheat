#include "offsets.h"
#include "proctools.h"

using namespace std;

DWORD pid;

DWORD clientdll;

DWORD playerAddress;

DWORD teamNumber;

BOOL numlock = FALSE;

void TriggerBunnyHop() {
	BOOL bSuccess;
	while (TRUE) {
		if (GetAsyncKeyState(VK_NUMLOCK) & 0x8001)
			numlock = !numlock;
		if (numlock) {
			bSuccess = Write(clientdll + PLAYER::dwForceJump, 1, pid);
			Sleep(100);
			bSuccess = Write(clientdll + PLAYER::dwForceJump, 0, pid);
			if (bSuccess == FALSE) {
				cerr << "FAILURE\n" << GetLastError() << endl;;
			}
			Sleep(100);
		}
	}
}

BOOL IsCrossHairFriendly(DWORD crosshair) {
	DWORD base = Read(clientdll + ENTITY_LIST + (crosshair * 0x10), pid);
	return teamNumber == Read(base + ENTITY::m_iTeamNum, pid);
}

void TriggerAutoShoot(DWORD dwFlags) {
	BOOL bSuccess;
	BOOL scopeIn;
	DWORD crosshair;
	while (TRUE) {
		scopeIn = Read<BOOL>(playerAddress + PLAYER::m_bIsScoped, pid);
		crosshair = Read(playerAddress + PLAYER::m_iCrosshairId, pid);
		if (crosshair > 0 && scopeIn && !IsCrossHairFriendly(crosshair)) {
			bSuccess = Write(playerAddress + PLAYER::dwForceAttack, 5, pid);
			Sleep(30);
			bSuccess = Write(playerAddress + PLAYER::dwForceAttack, 4, pid);
			Sleep(30);
		}
	}
}

DWORD GetTeamNumber() {
	DWORD base = Read(clientdll + ENTITY_LIST, pid);
	return Read(base + ENTITY::m_iTeamNum, pid);
}

DWORD GetPlayerAddress() {
	return Read(clientdll + LOCAL_PLAYER, pid);
}

int main() {
	pid = GetProcessID("csgo.exe");
	clientdll = GetProcessModule("client_panorama.dll", pid);
	teamNumber = GetTeamNumber();
	playerAddress = GetPlayerAddress();

	while (TRUE)
	{		
		TriggerBunnyHop();
	}
	cin.get();
	return 0;
}