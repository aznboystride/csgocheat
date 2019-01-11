#include "offsets.h"
#include "proctools.h"

using namespace std;

DWORD pid;

DWORD clientdll;

DWORD entity_base;

void TriggerBunnyHop() {
	BOOL bSuccess;
	while (TRUE) {
		bSuccess = Write(PLAYER::dwForceJump, 1, pid);
		if (bSuccess == FALSE) {
			cerr << "Failed To Trigger Bunny Hop\n";
			ExitThread(-1);
		}
		Sleep(30);
		bSuccess = Write(PLAYER::dwForceJump, 0, pid);
		if (bSuccess == FALSE) {
			cerr << "Failed To Trigger Bunny Hop\n";
			ExitThread(-1);
		}
		Sleep(30);
	}
}

void TriggerAutoShoot(DWORD dwFlags) {
	BOOL bSuccess;
	BOOL scopeIn;
	while (TRUE) {
		scopeIn = Read<BOOL>(PLAYER::m_bIsScoped, pid);
		//if (scopeIn == -1) {
		//	cerr << "Failed To Detect Scope\n";
		//	ExitThread(-1);
		//}
		bSuccess = Write(PLAYER::dwForceAttack, 5, pid);
		//if (bSuccess == FALSE) {
		//	cerr << "Failed To Trigger Force Shoot\n";
		//	ExitThread(-1);
		//}
		Sleep(30);
		bSuccess = Write(PLAYER::dwForceAttack, 4, pid);
		//if (bSuccess == FALSE) {
		//	cerr << "Failed To Trigger Force Shoot\n";
		//	ExitThread(-1);
		//}
		Sleep(30);
	}
}

int main() {
	pid = GetProcessID("csgo.exe");
	clientdll = GetProcessModule("client_panorama.dll", pid);


	cin.get();
	return 0;
}