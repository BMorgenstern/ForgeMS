#ifndef ITEM__H
#define ITEM__H

//#include "TwoVars.h"

/*
typedef struct Item{
	TwoBytes item;
}Item;


#define get_uses(i) getBTop(&i->item);
#define get_id(i) getBTop(&i->item);
*/

class Item{
	private:
		u16 item;
	public:
		int getUses(){
			return ((u8*)this)[1];
		}
		int getID(){ 
			return ((u8*)this)[0];
		}
};

#endif