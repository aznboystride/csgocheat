#ifndef OFFSETS_
#define OFFSETS_

#include <Windows.h>

#define ENTITY_LIST 0x4CCDBFC

#define LOCAL_PLAYER 0xCBD6B4

namespace PLAYER {
	DWORD dwForceAttack = LOCAL_PLAYER + 0x30FF2A0;
	DWORD dwForceAttack2 = LOCAL_PLAYER + 0x30FF2AC;
	DWORD dwForceBackward = LOCAL_PLAYER + 0x30FF2E8;
	DWORD dwForceForward = LOCAL_PLAYER + 0x30FF2F4;
	DWORD dwForceJump = LOCAL_PLAYER + 0x5170DB0;
	DWORD dwForceLeft = LOCAL_PLAYER + 0x30FF30C;
	DWORD dwForceRight = LOCAL_PLAYER + 0x30FF300;
	DWORD m_iCrosshairId = LOCAL_PLAYER + 0xB394;
	DWORD m_bIsScoped = LOCAL_PLAYER + 0x390A;
}

namespace ENTITY {
	DWORD m_iCrosshairId = ENTITY_LIST + 0xB394;
	DWORD m_iHealth = ENTITY_LIST + 0x100;
	DWORD m_iTeamNum = ENTITY_LIST + 0xF4;
	DWORD m_hActiveWeapon = ENTITY_LIST + 0x2EF8;
}
#endif