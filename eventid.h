#ifndef __EVENT_ID__
#define __EVENT_ID__

#include "arm.h"

/**
Event ID's are the game's native flags, they are set and checked 
to determine if an action has been performed or something has occured,
eg. a boss was defeating or a character interaction happened.
I used the game's native functions to maintain integrity of those values.
*/
class EventID{
	private:
		u8 id;
	public:
		int get(){return this->id;}
		bool Check(){
			bool (*func)(EventID i) = (bool(*)(EventID))(0x8083DA8 | 1);
			return func(*this);
		}
		void Set(){
			void (*func)(EventID i) = (void(*)(EventID))(0x8083D94 | 1);
			return func(*this);
		}
};

#endif