#ifndef __FORGE_ITEMS__
#define __FORGE_ITEMS__

#include "eventid.h"

struct ForgeItem{
	u8 item; // 0
	u8 ingredients[3]; // 1
	TextID text; // 4
	EventID event; // 6
	u8 seller; // 7
};

#endif