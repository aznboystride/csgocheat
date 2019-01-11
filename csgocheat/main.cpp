#include "offsets.h"
#include "proctools.h"

using namespace std;

DWORD pid;

DWORD clientdll;

DWORD playerAddress;

DWORD teamNumber;

BOOL numlock = FALSE;

BOOL caplock = TRUE;

DWORD GetPlayerAddress() {
	return Read(clientdll + LOCAL_PLAYER, pid);
}

DWORD GetTeamNumber() {
	DWORD base = Read(clientdll + ENTITY_LIST, pid);
	if (base == -1) {
		cerr << "Fail\n";
	}
	DWORD num = Read(base + ENTITY::m_iTeamNum, pid);
	if (base == -1) {
		cerr << "Fail\n";
	}
	return num;
}

DWORD GetHealth() {
	DWORD base = Read(clientdll + ENTITY_LIST, pid);
	if (base == -1) {
		cerr << "Fail\n";
	}
	DWORD num = Read(base + ENTITY::m_iHealth, pid);
	if (base == -1) {
		cerr << "Fail\n";
	}
	return num;
}

DWORD WINAPI _TriggerBunnyHop(LPVOID params) {
	BOOL bSuccess;
	while (TRUE) {
		Sleep(40);
		if (GetAsyncKeyState(VK_NUMLOCK) & 0x8001) {
			cout << "\a" << endl;
			numlock = !numlock;
			if (numlock)
				cout << "BUNNY HOP ENABLED\n";
			else
				cout << "BUNNY HOP DISABLED\n";
		}
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

HANDLE TriggerBunnyHop() {
	HANDLE h = CreateThread(NULL, 0, _TriggerBunnyHop, NULL, 0, NULL);
	if (h == NULL) {
		cerr << "Fail To Trigger Auto Bunny Hop\n";
	}
	return h;
}

BOOL IsCrossHairFriendly(DWORD crosshair) {
	DWORD base = Read(clientdll + ENTITY_LIST + ((crosshair - 1) * 0x10), pid);
	return GetTeamNumber() == Read(base + ENTITY::m_iTeamNum, pid);
}

DWORD _GetTeamNumber(DWORD crosshair) {
	DWORD base = Read(clientdll + ENTITY_LIST + ((crosshair - 1) * 0x10), pid);
	return Read(base + ENTITY::m_iTeamNum, pid);
}

DWORD WINAPI _TriggerAutoShoot(LPVOID dwFlags) {
	BOOL bSuccess;
	BOOL scopeIn;
	DWORD crosshair;
	DWORD flags;
	SHORT state;
	if(dwFlags)
		flags = *(DWORD*)dwFlags;
	while (TRUE) {
		Sleep(40);
		if (GetAsyncKeyState(VK_CAPITAL) & 0x8001) {
			cout << "\a" << endl;
			caplock = !caplock;
			if (caplock)
				cout << "TRIGGER AUTO SHOOT ENABLED\n";
			else
				cout << "TRIGGER AUTO SHOOT DISABLED\n";
		}
		if (caplock) {
			scopeIn = Read<BOOL>(GetPlayerAddress() + PLAYER::m_bIsScoped, pid);
			crosshair = Read(GetPlayerAddress() + PLAYER::m_iCrosshairId, pid);
			if (crosshair > 0 /*&& scopeIn*/ && !IsCrossHairFriendly(crosshair)) {
				bSuccess = Write(clientdll + PLAYER::dwForceAttack, 5, pid);
				cout << "die " << _GetTeamNumber(crosshair) << endl;
				cout << "My Team Number: " << GetTeamNumber() << endl;
				if (bSuccess == FALSE)
					cerr << "write fail\n";
				Sleep(30);
				bSuccess = Write(clientdll + PLAYER::dwForceAttack, 4, pid);
				if (bSuccess == FALSE)
					cerr << "write fail\n";
				Sleep(30);
			}
		}
	}
	return 0;
}

HANDLE TriggerAutoShoot(DWORD dwFlags) {
	HANDLE h = CreateThread(NULL, 0, _TriggerAutoShoot, (LPVOID)dwFlags, 0, NULL);
	if (h == NULL) {
		cerr << "Fail To Trigger Auto Shoot\n";
	}
	return h;
}

int main() {
	
	pid = GetProcessID("csgo.exe");
	clientdll = GetProcessModule("client_panorama.dll", pid);
	teamNumber = GetTeamNumber();
	playerAddress = GetPlayerAddress();
	HANDLE hopHandle = TriggerBunnyHop();
	HANDLE shHandle = TriggerAutoShoot(NULL);
	cin.get();
	return 0;
}