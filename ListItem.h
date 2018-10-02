#include "Item.h"
#include "Unit.h"

enum Source{supply=1, unit};
void (*SetItemArray)(Unit* curr, u8 type, Source sources) = (void (*)(Unit*, u8, Source))(0x80981E4 | 1);
void (*RemoveItem)(Unit* unit, int index) = (void (*)(Unit*, int))(0x8019484 | 1);
void (*UpdateSupply)() = (void(*)())(0x80982B8 | 1);
int(*CountSupply)() = (int(*)())(0x8031570 | 1);

class UnitListItem{
	public:
		u8 character; // 0 = Supply
		u8 itemindex;
		Item item;
		Item* getItemAddr(){return &this->item;}
		bool FindItem(int ID){return this->getItemAddr()->getID() == ID;}
		void RemoveUnit(){
			Unit* u = getUnitCharacter(this->character);
			RemoveItem(u, this->itemindex);
		}
		
};

UnitListItem* GlobalList = (UnitListItem*)(0x20122D4);
u16* indices = (u16*)(0x2012F54);
u16* numoftype = (u16*)(0x2012F56);

void Clear(int index){
	UnitListItem* i = GlobalList+index;
	if(i->character)
		i->RemoveUnit();
	else
		*(int*)(i) = 0;
}

void ClearAll(int* indices, int count = 3){
	for(int k = 0; k < count-1; k++){
		UnitListItem* i = GlobalList+indices[k];
		UnitListItem* j = GlobalList+indices[k+1];
		if(i->character == j->character){
			if(i->itemindex < j->itemindex){
				int temp = indices[k];
				indices[k] = indices[k+1];
				indices[k+1] = temp;
				k = -1;
			}
		}
	}
	for(int n = 0; n < count; n++){
		Clear(indices[n]);
	}
	UpdateSupply();
}

