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
	BOOL m_bIsScoped = LOCAL_PLAYER + 0x390A;
}

namespace ENTITY {
	unsigned int m_iCrosshairId = 0xB394;
	unsigned int m_iHealth = 0x100;
	unsigned int m_iTeamNum = 0xF4;
	unsigned int m_hActiveWeapon = 0x2EF8;

}

#endif