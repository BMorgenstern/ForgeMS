#ifndef __BUTTON_FE8__
#define __BUTTON_FE8__

class Button{
	private: 
		u16 held; 
		u16 pressed; 
		u16 pressed2; 
		u16 lastheld; 
		u16 lastpress; 
		static Button* GlobalButtonData(){
			return (Button*)0x2024CC4;
			/*
			this pointer points to the game's global native Button object,
			it is kept private to maintain the integrity of its members.
			*/
		}
	public:
		enum button{A,B,Select,Start,Right,Left,Up,Down,R,L};
		static bool Pressed(button b){
			return GlobalButtonData()->pressed2 & (1 << b);
		}
		/*
		The GBA's buttons are represented as bits, 1 means it's pressed. Bitshifting and 
		an enumeration are used to easily check the status of a particular button.
		*/
};

#endif