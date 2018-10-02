#include "arm.h"
#include "adapt.h"
#include "TextID.h"
#include "ListItem.h"
#include "reldata.h"
#include "Unit.h"
#include "thread.h"
#include "shopthreads.h"
#include "eventid.h"

void ForgeShop(Thread* pthread){
	/*This function allows for easy user Forge initilaization 
	by calling the it, similar to the other ingame shops*/
	
	ORIGIN(0x9130000);
	u16 items[20];
	u16* ip = FillList(list);
	ShopThreadInit(getUnit(rel->actor), ip, Forge, pthread); 
	return;
}

u16* FillList(u16* listp){
	int i,j = 0;
	int potseller = getUnit(rel->receiver)->getCharID(); 
	ForgeItem* fg = forgeitems;
	/* Forge items will be added to the list so long as the specifed flag, and 
	seller character ID match, or are set to 0 meaning there is no requirement*/
	while((fg+j)->item){
		EventID e = (fg+j)->event;
		int s = (fg+j)->seller;
		if((e.get() == 0 || e.Check()) && (s == 0 || s == potseller)){
			listp[i] = (fg+j)->item;
			list[i] = j;
			i++;
		}
		j++;
	}
	listp[i] = 0;//end of list is explicitly set
	return listp;
}

#include "forgehooks.h" 
//Hooks are included last to maintain proper addressing