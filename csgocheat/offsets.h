#ifndef OFFSETS_
#define OFFSETS_

#include <Windows.h>

#define ENTITY_LIST 0x4CCDBFC

#define LOCAL_PLAYER 0xCBD6B4

namespace PLAYER {
	DWORD dwForceAttack = 0x30FF2A0;
	DWORD dwForceAttack2 = 0x30FF2AC;
	DWORD dwForceBackward = 0x30FF2E8;
	DWORD dwForceForward = 0x30FF2F4;
	DWORD dwForceJump = 0x5170DB0;
	DWORD dwForceLeft = 0x30FF30C;
	DWORD dwForceRight = 0x30FF300;
	DWORD m_iCrosshairId = 0xB394;
	DWORD m_bIsScoped = 0x390A;
}

namespace ENTITY {
	DWORD m_iCrosshairId = 0xB394;
	DWORD m_iHealth = 0x100;
	DWORD m_iTeamNum = 0xF4;
	DWORD m_hActiveWeapon = 0x2EF8;
}
#endif