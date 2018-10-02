#ifndef __FORGE_N_SHOP_THREADS__
#define __FORGE_N_SHOP_THREADS__

#include "thread.h"
#include "forgeitems.h"
#include "button.h"


#define FRAME_BUFFER 5 

#define NOITEMS 0xB09 //dummy text
#define NOINGREDS 0xB0A // dummy
#define FORGEWELCOME 0xB0B

void MainData(); //The forge thread's metadata

ForgeItem* forgeitems = (ForgeItem*)0x9040C00;

void (*ShopText)(int text, Thread* shopThread) = (void (*)(int,Thread*))(0x80B4169);
/*This native function renders text to the Shop UI*/

u8* option = (u8*)0x0202BD30;
u16* TopList = (u16*)0x203EF9E;
u16* FillList(u16*);
u16* list = (u16*)0x2000000;

enum Shop{Armory,Vendor,Secret,Forge};

void (*ShopThreadInit)(Unit* unit, u16* listp, Shop shop, Thread* parentThread) = (void(*)(Unit*, u16*, Shop, Thread*))(0x80B4240 | 1);

class ShopThread : public Thread{
	public:
		Unit* unit(){
			Unit** upp = (Unit**)this; 
			return upp[11];
		}
		int cursor(){
			u8* ptr = (u8*)this;
			return ptr[0x5C];
		}
		int cursor(int arg){
			u8* ptr = (u8*)this;
			ptr[0x5C] = arg;
		}
		int itemsforsale(){
			u8* ptr = (u8*)this;
			return ptr[0x5A];
		}
		int itemsforsale(int arg){
			u8* ptr = (u8*)this;
			ptr[0x5A] = arg;
		}
		int itemstosell(){
			u8* ptr = (u8*)this;
			return ptr[0x5B];
		}
		int itemstosell(int arg){
			u8* ptr = (u8*)this;
			ptr[0x5B] = arg;
		}
		Shop shop(){
			return (Shop)(((u8*)this)[0x61]); 
		}
		Shop shop(Shop arg){
			u8* ptr = (u8*)this;
			Shop* sptr = (Shop*)(&ptr[0x61]);
			*sptr = arg;
		}
		bool RButton(){
			bool* ptr = (bool*)this;
			return ptr[0x62];
		}
		
		//Thread funcs
		
		void NewGreeting(int greeting);
		void BuyOption();
		void AnythingElse();
		void Welcome();
		int ShopPortraitGet();
		int CheckAndCount(bool);
		bool MoneyOrIngreds(int);
		int itemcheck();
		int supplycheck();
		
		/**
		This extremely unconventional calling method is used to circumvent an inability to use 
		non-static methods' addresses. In order to maintain an object oriented design, static 
		methods return the addresses of class methods. This approach is used for the 
		ForgeThread class as well as the ShopThread class.
		**/
		
		static void(*BuyOptionAddr())(){return (void(*)())&ShopThread::BuyOption;}
		static void(*AnythingElseAddr())(){return (void(*)())&ShopThread::AnythingElse;}
		static void(*WelcomeAddr())(){return (void(*)())&ShopThread::Welcome;}
		static void(*ShopPortraitGetAddr())(){return (void(*)())&ShopThread::ShopPortraitGet;}
		static int(*itemcheckAddr())(){return (int(*)())&ShopThread::itemcheck;}
		static int(*supplycheckAddr())(){return (int(*)())&ShopThread::supplycheck;}
		static bool(*MoneyOrIngredsAddr())(int){return (bool(*)(int))&ShopThread::MoneyOrIngreds;}
};

class ForgeThread : public Thread{
	public:
		ShopThread* shopThread(){
			return (ShopThread*)this->data[0];
		}
		ShopThread* shopThread(ShopThread* t){
			*((ShopThread**)(&this->data[0])) = t;
		}
		int TopOfTheList(){
			return this->scratchshorts[0];
		}
		void TopOfTheList(int arg){
			this->scratchshorts[0] = arg;
		}
		int LastState(){
			return this->scratchshorts[1];
		}
		void LastState(int arg){
			this->scratchshorts[1] = arg;
		}
		int oldoption(){
			return this->scratchshorts[2];
		}
		void oldoption(int arg){
			this->scratchshorts[2] = arg;
		}
		int buffer(){
			return this->data[1];
		}
		int buffer(int var){
			this->data[1] = var;
		}
		void addFrames(int var){
			this->data[1]+= var;
		}
		int tempcursor(){
			u16* ptr = (u16*)&(this->data[2]);
			return ptr[1];
		}
		int tempcursor(int var){
			u16* ptr = (u16*)&(this->data[2]);
			ptr[1] = var;
		}
		int cursor(){
			u16* ptr = (u16*)&(this->data[2]);
			return ptr[1];
		}
		int cursor(int var){
			u16* ptr = (u16*)&(this->data[2]);
			ptr[1] = var;
		}
		bool sameItem(){
			return (this->cursor() == this->shopThread()->cursor());
		}
		bool sameTemp(){
			return (this->tempcursor() == this->shopThread()->cursor());
		}
		void setItem(){
			this->cursor(this->shopThread()->cursor());
		}
		void setTemp(){
			this->tempcursor(this->shopThread()->cursor());
		}
		int ingcount(){
			return this->data[3];
		}
		int ingcount(int var){
			this->data[3] = var;
		}
		int items(){
			return this->data[4];
		}
		int items(int var){
			this->data[4] = var;
		}
		int ingredi(int index){
			int* pt = &this->data[5];
			return pt[index];
		}
		int ingredi(int index, int var){
			int* pt = &this->data[5];
			pt[index] = var;
		}
		int* ingredi(){
			return &this->data[5];
		}
		UnitListItem* ingreds(int index){

			UnitListItem* pt = (UnitListItem*)(&this->data[8]);
			return &pt[index];
		}
		void ingreds(int index, UnitListItem var){
			UnitListItem* pt = (UnitListItem*)(&this->data[8]);
			pt[index] = var;
		}
		void ingreds(int index, int var){
			int* pt = (&this->data[8]);
			pt[index] = var;
		}
		void Success(int arg){
			this->scratch = arg;
		}
		int Success(){
			return this->scratch;
		}
		void FindItems(ForgeItem* f){
			int counter = 0;
			/*The for loop counts of number of ingredients an item needs.*/
			for(counter; counter < 3; counter++){
				if(!f->ingredients[counter])
					break;
				else{
					this->ingredi(counter, -1);
					this->ingreds(counter, 0);
				}
			}
			this->ingcount(counter);
			SetItemArray(0,-1,Source(supply|unit));//set the list
			for(int listiterator = 0; listiterator < *indices; listiterator++){
				//parsing the list of all items
				for(int ingredientiterator = 0; ingredientiterator < counter; ingredientiterator++){
					int ingredient = f->ingredients[ingredientiterator];
					if(ingredient == 0)
						break; //sentinel controlled list
					//parse the 3 ingredients
					if((GlobalList+listiterator)->FindItem(ingredient)){
						/*
						Items are added if they have yet to be found, or an instance with fewer uses is found
						*/
						int ingindex = this->ingredi(ingredientiterator);
						if(ingindex == -1 || (GlobalList+ingindex)->getItemAddr()->getUses() > (GlobalList+listiterator)->getItemAddr()->getUses()){
							this->ingredi(ingredientiterator, listiterator);
							this->ingreds(ingredientiterator, *(GlobalList+listiterator));
						}
					}
				}
				
			}
		}
		
		//Thread Funcs
		
		void Constructor();
		void Display();
		/*The same approach of employing static methods to get non-static addresses is used*/
		static void(*ConstructorAddr())(){return (void(*)())&ForgeThread::Constructor;}
		static void(*DisplayAddr())(){return (void(*)())&ForgeThread::Display;} 
};

void ForgeThread::Constructor(){
	this->cursor(-1);
	this->buffer(0);
	this->ingcount(0);
	this->Success(0);
	this->TopOfTheList(*TopList);
	this->LastState(0);
	this->oldoption(*option);
}


void ForgeThread::Display(){
	bool screenmoved = false;
	if (*TopList != this->TopOfTheList()){
		this->TopOfTheList(*TopList);
		screenmoved = true;
		/*logically, if the top item changed, the screen moved*/
	}
	Thread* t = ((ThreadData*)RButtonThread)->Search();
	Thread* t2 = ((ThreadData*)ShopTextThread)->Search();
	bool RButton = (t != 0); //if the RButton info is active
	bool RChanged = false;
	if(this->LastState() != RButton){
		this->LastState(RButton);
		RChanged = true;
	}
			
	if(Button::Pressed(Button::A) && !RButton){
		*option = this->oldoption();
		this->NextFunc();
		return;
		/*
		Pressing A while the RButton isn't up means an item
		has been selected for purchase, so we advance the thread.
		*/
	}
	else if(Button::Pressed(Button::B) && !RButton){
		*option = this->oldoption();
		this->KillThread();
		return;
		/*
		Pressing B while the RButton isn't up means the user 
		has exited the menu, so we kill the thread.
		*/
	}
	else if(!this->sameItem() && !this->Success()){
		if(!RButton){
			this->setTemp();
			this->Success(1);
			this->buffer(FRAME_BUFFER);
		}
		return;
	}	
	if(this->buffer() > 0){
		if(t2 || screenmoved || RChanged)
			this->buffer(FRAME_BUFFER);
		else if(this->sameTemp())
			this->addFrames(-1);
		else
			this->Success(0);
		return;
	}
	if(this->Success() && !this->buffer()){
		this->setItem();
		this->buffer(0);
		ForgeItem* f = forgeitems + list[this->cursor()] ;
		this->Success(0);
		*option = 0x60; //set text speed to MAX		
		ShopText((int)(f->text.get()), this);
		/*
		Item dependent text is rendered after the cursor moves
		and the thread has slept accordingly.
		*/
	}

}

void ShopThread::NewGreeting(int greeting){
	if(this->itemsforsale() == 0){
		ShopText(NOITEMS, this);
		this->ScanThread(Thread::Action(7));
		/*
		If the store has nothing to sell, we provide a message to the user, 
		and return to the previous shop state.  
		*/
	}
	else if(this->shop() != Forge)
		ShopText(greeting, this); 
	//if shop is not a Forge, proceed as normal 
	else{
		//start the Forge thread if it is a Forge
		ThreadData* Browser = (ThreadData*)&MainData;
		ForgeThread* browserthread = (ForgeThread*)Browser->Search();
		if(browserthread)
			browserthread->KillThread();
		//if the thread is alive, kill it before starting a new one
		browserthread = (ForgeThread*)Browser->ThreadInit();
		browserthread->shopThread(this);
		browserthread->items(this->itemstosell());
	}
}


bool ShopThread::MoneyOrIngreds(int cost){
	int funds = *(int*)0x202BCF8;
	if(cost > funds){
		ShopText(0x8B2, this);
		return 0;
		/*Can't process the transaction if the user can't afford the item*/
	}
	else if(this->shop() == Forge){
		ThreadData* Browser = (ThreadData*)&MainData;
		ForgeThread* browserthread = (ForgeThread*)Browser->Search();
		if(browserthread){
		//ingredientcheck
			ForgeItem* f = forgeitems + list[browserthread->shopThread()->cursor()] ;
			browserthread->FindItems(f);
			for(int i = 0; i < browserthread->ingcount(); i++)
				if(browserthread->ingredi(i) == -1){
					ShopText(NOINGREDS, this);
					browserthread->KillThread();
					return 0;
				}
			/*Provide an error message to the user if they don't have the ingredients 
			needed, then cancel the transaction and kill the thread*/
		}
	}
	return 1;	//We can process the transaction	
}

int ShopThread::CheckAndCount(bool supply){
	int max = (supply) ? 100 : 5;
	/*Storage can hold 100 items, character can hold 5*/
	int items = (supply) ? CountSupply() : this->itemstosell(); 
	ThreadData* Browser = (ThreadData*)&MainData;
	ForgeThread* browserthread = (ForgeThread*)Browser->Search();
		// if the forge thread isn't active, simply return the number of items like normal
		if(browserthread){
			/*
			If the Forge thread is active, remove the ingredients to make space before checking
			*/
			int cnt = browserthread->ingcount();
			int* indices = browserthread->ingredi();
			for(int cntr = 0; cntr < cnt; cntr++){
				UnitListItem* uli = GlobalList + indices[cntr];
				int compto = (supply) ? 0 : this->unit()->getCharID();
				if(uli->character == compto)
					items--;
			}
			if(items < max)
				ClearAll(indices, cnt);
			//we remove the items if the transaction succeeds ie enough room to hold it.
		}
	return items;
}

void ShopThread::BuyOption(){
	NewGreeting(0x8A3);
}

void ShopThread::AnythingElse(){
	NewGreeting(0x8A6);
}

void ShopThread::Welcome(){
	if(!this->unit())
		this->ScanThread(Thread::SetPosition);
	else if(this->shop() != Forge)
		ShopText(0x89A, this);
	else
		ShopText(FORGEWELCOME, this);//provide unique Forge welcome text
}

int ShopThread::ShopPortraitGet(){
	switch(this->shop()){
		case 0:
			return 0x65;
		case 1:
			return 0x66;
		case 2:
			return 0x68;
		default:
			return portrait(getUnit(rel->receiver));
	}
}
		

int ShopThread::itemcheck(){
	return CheckAndCount(false);
}

int ShopThread::supplycheck(){
	return CheckAndCount(true);
}

#endif
