#define ArmoryMusic 0x36
#define VendorMusic 0x35
#define SecretMusic 0x35
#define ForgeMusic 0xC

/**
Several segments of the ingame needed to be directly modified to ensure the new Forge code 
would be properly accomodated. The changes are all extremely hardware specific, hence all 
of the changes are made here for organization and to keep the other code segments clean. 
*/

void MainData(){
	/**This sets the Forge thread's system of behaviour.
	First it calls its constructer to set default values,
	it then continually runs its Display method, which renders
	text to the screen, and finally sets the thread to sleep until 
	it is explicitly killed.
	*/
	LITERAL(Thread::ExecuteOnce);
	HACK_ADDR_LIT(ForgeThread::ConstructorAddr(), 1);
	LITERAL(Thread::Execute);
	HACK_ADDR_LIT(ForgeThread::DisplayAddr(), 1);
	LITERAL(Thread::Nothing);
	HOOKEND;
}
void BuyOptionHook(){
	ORIGIN(0x8A3927C);
	HACK_ADDR_LIT(ShopThread::BuyOptionAddr(), 1);
	HOOKEND;
}

void AnythingElseHook(){
	ORIGIN(0x8A392BC);
	HACK_ADDR_LIT(ShopThread::AnythingElseAddr(), 1);
	HOOKEND;
}

void WelcomeHook(){
	ORIGIN(0x8A39254);
	HACK_ADDR_LIT(ShopThread::WelcomeAddr(), 1);
	HOOKEND;
}

void BL2ITEMCHECK(){
	ORIGIN(0x80B4650);
	LONG(0xFEAAF7FF);
	HOOKEND;
}

void BL2SUPPLYCHECK(){
	ORIGIN(0x80B4734);
	LONG(0xFE3CF7FF);
	HOOKEND;
}

void BackTracking(){
	ORIGIN(0x80B43A8);
	asm("ldr\tr1, [pc]");
	asm("bx r1");
	HACK_ADDR_LIT(ShopThread::itemcheckAddr(), 1);
	asm("ldr\tr1, [pc]");
	asm("bx r1");
	HACK_ADDR_LIT(ShopThread::supplycheckAddr(), 1);
	HOOKEND;
}

void PortraitHook(){
	ORIGIN(0x80B4154);
	asm("ldr\tr1, [pc]");
	asm("bx r1");
	HACK_ADDR_LIT(ShopThread::ShopPortraitGetAddr(), 1);
	HOOKEND;
}
void FixForgeText(){
	ORIGIN(0x80B4174);
	asm("ldrb\tr0,[r0]");
	asm("cmp\tr0,#3");
	asm("bne\tend");
	asm("mov\tr0,#0");
	LABEL(end);
	HOOKEND;
}

void MusicFix(){
	ORIGIN(0x80B4BFC);
	asm("ldrb\tr0,[r0]");
	asm("mov\tr1,pc");
	asm("b music");
	BYTE(ArmoryMusic);
	BYTE(VendorMusic);
	BYTE(SecretMusic);
	BYTE(ForgeMusic);
	SHORT(0);
	LONG(0);
	LABEL(music);
	asm("ldrb\tr0,[r0,r1]");
	asm("mov\tr1,#0");
	HOOKEND;
}

void MoneyTakeFix(){
	ORIGIN(0x80B45C8);
	asm("mov\tr0,r5");
	asm("mov\tr1,r4");
	asm("ldr\tr2,[pc,#0x14]");
	BYTE(0x1D);
	BYTE(0xF0);
	BYTE(0x7B);
	BYTE(0xF9);
	asm("cmp\tr0,#0");
	BYTE(0x8);
	BYTE(0xD1);
	asm("nop");
	HOOKEND;
}

void MoneyTakeFixHackAddr(){
	ORIGIN(0x80B45E4);
	HACK_ADDR_LIT(ShopThread::MoneyOrIngredsAddr(),1);
	HOOKEND;
}

void Lazy(){
	ORIGIN(0x9040C00);
	BYTE(0x4A);
	BYTE(0x45);
	SHORT(0);
	SHORT(0x412);
	BYTE(0);
	BYTE(1);
	BYTE(0x4);
	BYTE(0x1);
	BYTE(0x3);
	BYTE(0);
	SHORT(0x420);
	SHORT(0);
	LONG(0);
	HOOKEND;
}