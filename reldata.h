#include "arm.h"
#include "Coord.h"

struct Reldata{
		u16 rng[6];
		u8 actor;
		u8 receiver;
		Coord pos;
		u8 spacesmoved;
		u8 action;
		u8 itemindex;
		Coord newpos;
		u8 type; //poorly defined, usually 0 or 1
};

Reldata* rel = (Reldata*)(0x203A958);