#ifndef __UNIT_CLASS__
#define __UNIT_CLASS__

#include "fe7.h"

Unit* (*getUnit)(int id) = (Unit*(*)(int))(0x8019430 | 1);
Unit* (*getUnitCharacter)(int index) = (Unit* (*)(int))(0x801829C | 1);
int (*portrait)(Unit* u) = (int(*)(Unit*))(0x80192B8 | 1);
#endif
