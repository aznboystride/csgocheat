#include "offsets.h"
#include "proctools.h"

using namespace std;

DWORD pid;

DWORD clientdll;

void TriggerBunnyHop() {
	Write(PLAYER::dwForceJump, 1, pid);
}

int main() {
	pid = GetProcessID("csgo.exe");
	clientdll = GetProcessModule("client_panorama.dll", pid);


	cin.get();
	return 0;
}