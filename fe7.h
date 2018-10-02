#ifndef __FE7_H__
#define __FE7_H__

#include "arm.h"
#include "adapt.h"
#include "Item.h"

#define HARDWARE         0x08000000
//#define TextBuffer        0x202A5B4
//#define IconLocation    0x6006250
#define RE(f,g) reinterpret_cast<f>(g)
#define SETVAR(REG, VAR) PUSH(REG);POPVAR(VAR)


class Unit;
class Combatant;
typedef Combatant* CP;

template <class T>
__attribute__((noinline))
T getPercent(T num, T per){
    return (num*per)/100;
}

namespace Tiles{
    enum{
        nil, plain, road, village, village2, house, armory, shop, arena, //0-8
        cockroom, fort, gate, forest, thicket, sand, drifts, river, //9-16 9-0x10
        mountain, peak, bridge, bridge2, sea, lake, floor, floor2, //17-24 0x11-0x18
        fence, wall, wall2, rubble, pillar, door, throne, chest, //25-32 0x19-0x20
        chest2, roof, gate2, church, ruins, cliff, ballista, longb, //33-40 0x21-0x28
        killerb, flat, wreck, nil2, stairs, nil3, glacier, arena2, //41-48 0x29-0x30
        valley, fence2, snag, bridge3, sky, deeps, ruins2, inn, //49-56 0x31-0x38
        barrel, bone, dark, water, gunnel, plank, brace, mast //57-64 0x39-0x40
    };
} 
        
class MoveCost{
private:
    u8 costs[0x40];
public:
    int get(int index){
        return this->costs[index];
    }
};

class HPRegen : public MoveCost{};
class RestoreStatus : public HPRegen{
public:
    bool Restore(int index){
        return (bool)this->get(index);
    }
};

#define INC(x) _asm(".incbin\t"#x)
#define SPACE(arg) _asm(".space\t%0" :: "i" (arg))

namespace WeaponTypes{
    enum weaps{Sword, Lance, Axe, Bow, Staff, Anima, Light, Dark};
}

namespace Weather{
    enum {None, LightSnow, Snow, BlueBG, Rain, Flames, Sandstorm, Clouds};
}

#ifdef __INCLUDE_WEATHER_
u8* weather = (u8*)0x202BC0D;
#endif

namespace alliance{
    enum Team{Ally, NPC, Enemy};
    /*
    int getAllegiance(Team arg){
        return arg * 0x40;
    }
    */
}

namespace levels{
    enum {None = 0, E = 1, D = 31, C = 71, B = 121, A = 181, S = 251};
}

namespace levelindex{
    enum {None, E, D, C, B, A, S};
}

namespace CC {
    enum abilities{MountedAid = 0x1, Move = 0x2, Steal = 0x4, Lockpick = 0x8, Dance = 0x10,
    Play = 0x20, Critical = 0x40, Ballistas = 0x80, Promoted = 0x100, Supply = 0x200, 
    MountedIcon = 0x400, DragonLock = 0x800, Pegasus = 0x1000, Lord = 0x2000, 
    Female = 0x4000, Boss = 0x8000, UnusedLock = 0x10000, WoDao = 0x20000, 
    Dragonstone = 0x40000, PreventsControlling = 0x100000, Triangle = 0x200000, 
    Different = 0x400000, Glitches = 0x800000, NoEXP = 0x1000000, Lethality = 0x2000000, 
    MagicSealing = 0x4000000, DropItem = 0x8000000, Rapier = 0x10000000, 
    WolfBeil = 0x20000000, ManiKatti = 0x40000000, Forblaze = 0x80000000};
    namespace Character{
        //todo
    }
    namespace Class{
        //todo
    }
}

namespace BattleStats{
	enum bits{critical, 
		miss, 
		lastattack, 
		counter, 
		brave,
		unk,
		poison,
		devil,
		};
}

namespace item{
    enum abilities{Weapon = 0x1, Magic = 0x2, Staff = 0x4, Indestructible = 0x8, Unsellable = 0x10, 
    Brave = 0x20, MagicSword = 0x40, Uncounterable = 0x80, Reverse = 0x100, unk_0 = 0x200, 
    DragonLocker = 0x400, Unused = 0x800, SwordfighterLock = 0x1000, unk_1 = 0x2000, NegateEffectiveness = 0x4000, 
    NegateCriticals = 0x8000, NegateDefense = 0x20000, LockedEliwood = 0x40000, LockedHector = 0x80000, 
    LockedLyn = 0x100000, LockedAthos = 0x200000};
    enum{};//ID's
}

namespace status{
    enum{current = 1 << 0, grey = 1 << 1, dead = 1 << 2, notfielded = 1 << 3, rescuing = 1 << 4, 
    rescued = 1 << 5, moved = 1 << 6, norbutton = 1 << 7, eliwoodlordmapsprite = 0x800, portraitplusone = 0x800000};
}

namespace battlebits{
    enum{inbattle = 1, prebattle = 2, statscreen = 4, map = 0x80};
}


class chapterData{
	int gold;
	char slot;
	char vision;
	char chapID;
	char phase;
	short turn;
	char unk[2];
	char bitmap;
};


class Abilities{
protected:    
    u32 bitfield;
public:
    u32 get(){
        return this->bitfield;
    }
    void set(u32 arg){
        this->bitfield = arg;
    }
    bool getAbility(int ability, int bit){
        ability = (u8)ability;
        if(bit < 1 || bit > 4)
            return false;
        else
            return (this->bitfield) & (ability << 8*(bit-1));
    }
    bool getAbility(u32 ability){
        return this->bitfield & ability ;
    }
};

namespace bits{
    enum{crit = 1, miss = 2, lastattack = 4, AI = 8, Brave = 0x10, Poison = 0x40, Devil = 0x80, 
    Leech = 0x100, HalfHP = 0x200, Silencer = 0x0800, Start = 0x10000, Attacking = 0x80000};
}

class Bitmap : public Abilities{
public:    
    s8 getDamage(){
        s8* array = (s8*)&this->bitfield;
        return array[3];
    }
};

class Stats{
private:
    s8 stat[7];
public:
    s8 get(int index){
        return this->stat[index];
    }
    void set(int index, int arg){
        this->stat[index] = arg;
        return;
    }
};

class Boosts : public Stats{
	private:
		s8 mov;
		s8 con;
	public:
		int gethpboost(){
			return this->get(0);
		}
		int getstrboost(){
			return this->get(1);
		}
		int getsklboost(){
			return this->get(2);
		}
		int getspdboost(){
			return this->get(3);
		}
		int getlukboost(){
			return this->get(4);
		}
		int getdefboost(){
			return this->get(5);
		}
		int getresboost(){
			return this->get(6);
		}
		int getmovboost(){
			return this->mov;
		}
		int getconboost(){
			return this->con;
		}
};

class Object{
public:    
    u16    name;
    //+0
    u16    desc;
    //+2
    u16    usedesc;
    //+4
    u8    num;
    //+6
    u8     type;
    //+7
    Abilities abilities;
    //+8
    Boosts*    pointer;
    //+$C
    u8* effectiveness;
    //+$10
    u8    uses;
    //+14
    u8    mgt;
    //+15
    u8    hit;
    //+16
    u8    wgt;
    //+17
    u8    crit;
    //+18
    u8    range;
    //+19
    u16    cost;
    //+1A
    u8    rank;
    //+1C
    u8    icon;
    //+1D
    u8    use;
    //+1E
    u8    effect;
    //+1F
    u8    weapexp;
    //+20
    u8 bitmap;
    // +21    
    u8 statusindex;
    //+22
    u8    unk_0001;
    bool hasItemAbility(int ab, int index = 0){
        return (index == 0) ? this->abilities.getAbility(ab) : this->abilities.getAbility(ab, index);
    }
};

struct Weaponlevels{
    u8 weapons[8]; //access with enum defs
};

class Class{
    //u8 unk_0000[84];
public:    
    u16 name;
    u16 desc;
    u8    id;
    u8    z[35];
    Abilities abilities;
    Weaponlevels bases;
    void* animationptr;
    MoveCost* moveptr[3];
    u8    y[16];
    MoveCost* getMove(int w = -1){
        if(w == Weather::Rain)
            return this->moveptr[1];
        else if(w == Weather::LightSnow || w == Weather::Snow)
            return this->moveptr[2];
        else
            return this->moveptr[0];
    }
};


class Character{
	public:
		u16 name;
		u16 desc;
		u8 id;
		u8 classsupport;
		u16 portrait;
		u8 chibi;
		u8 affinity;
		u8 unk;
		u8 lvl;
		Stats bases;
		u8 con;
		Weaponlevels wlvls;
		Stats growths;
		u8 unk_bytes[5];
		Abilities abilities;
		void* supports;
		u8 unk_bytes2[3];
};

class Unit{
protected:    
    //80 bytes long
    Character* character_pointer;
    //+0
    Class*    class_pointer;
    //+4
    s8    level;
    //+8
    s8    exp;
    //+9
    u8    unused;//full 8 bits
    //+0xA
    u8     unitnumber;
    //+0xB
    Abilities status;
    //+0xC
    s8 xposition;
    // X position +0x10
    s8 yposition;
    // Y position +0x11
    s8 maxHP;
    // max HP +0x12
    s8 currHP;
    // current HP +0x13
    s8 power;
    //str/mag +0x14
    s8 skill;
    //Skill +0x15
    s8 speed;
    //Speed +0x16
    s8 defence;
    //Defence +0x17
    s8 resistance;
    //Resistance +0x18
    s8 luck;
    //Luck +0x19
    s8 con;
    // con +0x1A
    u8 Traveller;
    // traveller +0x1B
    u8 move;
    // +0x1C; only the lower 7 bits are used
    s8 movebonus;
    // movement +0x1D
    Item items[5];
    //+0x1E
    Weaponlevels weap;
    //+2f
    u8    statuseffect;
    //+0x30
    u8    resfog;//only goes up to 0x77 (???)
    //+0x31
    u8    supports[7];
    //+0x32
    u8    mag;// only 7 bit
    //+0x39
    u16 garbage;//won't save anything; useless
    //+0x3A
    u32    BWL;
    //+0x3C
    u8    AI3;
    //+0x40
    u8    AI4;
    //+0x41
    u8    AI1;
    //+0x42
    u8    unused3;
    //+0x43
    u8    AI2;
    //+0x44
    u8    unused4;
    //+0x45
    u8    unused5; //only saves up to 1; can be used as a bool
    //+0x46
    u8    garbage2; //won't save anything; useless
    //+0x47
public:   
    s8* getStatArray(){
        return &this->power;
    }
    s8 getPower(){
        return this->power;
    }
    s8 getSkl(){
        return this->skill;
    }
    s8 getSpd(){
        return this->speed;
    }
    s8 getLuck(){
        return this->luck;
    }
    s8 getDef(){
        return this->defence;
    }
    s8 getRes(){
        return this->resistance;
    }
    s8 getHP(){
        return this->currHP;
    }
    s8 getMax(){
        return this->maxHP;
    }
    void setHP(s8 x){
        this->currHP = x;
    }
    void setMax(s8 x){
        this->maxHP = x;
    }
    u8 getEXP(){
        return this->exp;
    }
    void setEXP(u8 arg){
        this->exp = arg;
    }
    Class* getClass(){
        return this->class_pointer;
    }
	Character* getCharacter(){
		return this->character_pointer;
	}
	void setClass(Class* c){
        this->class_pointer = c;
    }
	void setCharacter(Character* c){
		this->character_pointer = c;
	}
    u8 getClassID(){
        return this->class_pointer->id;
    }
    u8 getCharID(){
        return this->character_pointer->id;
    }
    Abilities getUnitAbilities(){
        Abilities x;
        x.set((this->character_pointer->abilities.get()) | (this->class_pointer->abilities.get()));
        return x;
    }
    u8    getPosition(){
        return this->xposition + this->yposition;
    }
    u8    getX(){
        return this->xposition;
    }
    u8    getY(){
        return this->yposition;
    }
    u8    getNumber(){
        return this->unitnumber;
    }
    Weaponlevels* getWeapLvl(){
        return &this->weap;
    }
	void setWeapLvl(Weaponlevels w){
		this->weap = w;
	}
    Item* getItems(){
        return &this->items[0];
    }
    Item* getItemAddr(int item){
        return this->getItems() + item;
    }
    Item getItem(int item){
        return this->items[item];
    }
	void setItem(int index, Item i){
		this->items[index] = i;
	}
    u8 getSt(){
        return this->statuseffect;
    }
    s8 getStEff(){
        int full = this->statuseffect;
        full &= 15;
        return full;
    }
    s8 getTurns(){
        int full = this->statuseffect;
        full << 24;
        full >> 28;
        return full;
    }
    s8 getLevel(){
        return this->level;
    }
    u8 getTraveller(){
        return this->Traveller;
    }
    Abilities getStatus(){
        return this->status;
    }
    bool getStatus(int bit){
        return this->getStatus().getAbility(bit);
    }
    bool getStatus(int ability, int bit){
        return this->getStatus().getAbility(ability, bit);
    }
    bool hasAbility(u32 ab, int index = 0){
        return (index == 0) ? this->getUnitAbilities().getAbility(ab) : this->getUnitAbilities().getAbility(ab, index);
    }
    u8 getAI4(){
        return this->AI4;
    }
    int posSub(int arg1, int arg2){
        if(arg1 - arg2 < 0)
            return arg2 - arg1;
        else
            return arg1 - arg2;
    }
    bool inRange(Unit* p, int range){
        int rg = this->posSub(this->getX(), p->getX()) + this->posSub(this->getY(), p->getY());
        return (rg <= range);
    }
};


struct BattleData{
    u16    bitmap;    
    // |1 means in battle, |2 means out of battle; +0
    u8    range;    
    // literally the range of battle; +2
    u8    unk_00;    
    // dunno won't break; +3
    s16    damage;    
    // damage to be dealt +4
    s16 atk;
    // +6
    s16 defense;
    // +8
    s16 hit;
    // +$A
    s16 crit;
    // +$C
    s16 leth;
    // +$E
	Unit* TrianglePartners[2];
};

class AttackData{
    private:
        unsigned short bitmap;
        unsigned char bit2;
        unsigned char damage;
    public:
        AttackData(int x, int y, int z){
            this->bitmap = x;
            this->bit2 = y;
            this->damage = z;
        }
        void setvals(int x, int y, int z){
            this->bitmap = x;
            this->bit2 = y;
            this->damage = z;
        }
        int getDamage(){
            return this->damage;
        }
        void MassClear(int indices){
            for(int i = 0; i < indices; i++){
                AttackData* bc = this+i;
                bc->setvals(0,0,0);
            }
        }
        void Initialize(int indices, AttackData** addr){
            *addr = this;
            MassClear(indices);
        }
};

class Combatant : public Unit{    
public:
    Item weapID;
    // +0x48
    Item weapIDBeforeBattle;
    // +0x4A
    Abilities weapAbilities;
    // +0x4C
    u8 Type;
    // +0x50
    u8 index;
    // +51
    u8 canattack;
    // +52
    s8    wtahit;
    //+0x53
    s8    wtadamage;
    //+0x54
    u8    terrain;
    //+0x55
    u8    defboost;
    // +0x56
    u8    avdboost;
    //+0x57
    u8 resboot;
    // 0x58
    u8 derp;
    // 0x59
    u16 attack;
    //+0x5A
    u16 def;
    //+0x5C
    u16 AS;
    //+0x5E
    u16 hit;
    // Hit +0x60
    u16 avoid;
    // Avoid +0x62
    u16 battleHit;
    // Battle Hit +0x64
    u16 crit;
    // Crit +0x66
    u16 critAvoid;
    // Crit_avoid +0x68
    u16 battleCrit;
    // Battle Crit 0x6A
    u16 lethality;
    //u8 unk_0003;
    u8 expgain;
    // Experience to gain +0x6E
    s8 statustoinflict;
    // +6F
    u8 level2;
    // 70
	u8 exp2;
	// 71
	u8 currentHP2;
	// 72
    u8 HPChange;
    // +0x73
    u8 StrChange;
    // +0x74
    u8 SkillChange;
    // +0x75
    u8 SpeedChange;
    // +0x76
    u8 DefChange;
    // +0x77
    u8 ResChange;
    // +0x78
    u8 LuckChange;    
    // +0x79
    u8 ConChange;
    // +0x7A
    u8 wexp;
    // +0x7B
    u8 todo;
    // +0x7C
    u8 weapBroken;
    // +0x7D
    u16 unk_0005;
};

typedef Combatant* CP;

class WTA{
    private:
        u8 type;
        u8 type2;
        u8 hit;
        u8 dmg;
    public:
        int getType(bool second = false){
            int type = (second) ? this->type2 : this->type;
            if(type > 0x10)
                return -1;
            return type;
        }
        bool getEndList(bool second = false){
            return this->getType(second) < 0;
        }
        int getHitBoost(){
            return this->hit;
        }
        int getDmgBoost(){
            return this->dmg;
        }
        int penalise(int y){
            return -(y);
        }
        bool MatchType(CP arg, bool second = false){
            return (arg->Type == this->getType(second));
        }
        bool Always(CP arg){
            return (arg->Type == this->getType() && this->getType() == -1);
        }
        bool Success(CP arg1, CP arg2){
            return MatchType(arg1) && MatchType(arg2, true);
        }
        WTA* getWTA(CP arg1, CP arg2){
            for(WTA* wta = this; !(wta->getEndList()); wta++){
                if(wta->Success(arg1, arg2))
                    return wta;
                
            }
            for(WTA* wta = this; !(wta->getEndList()); wta++){
                if(wta->Always(arg1))
                    return wta;
            }
            return NULL;
        }

};

class FullBattleData{
protected:
    BattleData battle;
    Combatant contenders[2];
    AttackData bitmap[7];
    AttackData* currMap;
public:
    BattleData getBattle(){
        return this->battle;
    }
    Combatant getAT(){
        return this->contenders[0];
    }
    CP getATptr(){
        return &this->contenders[0];
    }
    Combatant getDF(){
        return this->contenders[1];
    }
    CP getDFptr(){
        return &this->contenders[1];
    }
    AttackData getBitmap(int index){
        return this->bitmap[index];
    }
    AttackData* getBitmapP(int index){
        return &this->bitmap[index];
    }
    AttackData getCurrMap(){
        return *currMap;
    }
    AttackData* getCurrMapP(){
        return currMap;
    }
    bool isAttacker(CP Com){
        return Com == this->getATptr();
    }
    bool isDefender(CP Com){
        return !this->isAttacker(Com);
    }
    
    CP getEnemy(CP Com){
        CP a = this->getATptr();
        CP d = this->getDFptr();
        if(Com == a){
            return d;
        }
        else if(Com == d){
            return a;
        }
        else{
            return NULL;
        }
    }
};

/*
CP const thisCombatant = RE(CP, thisUnit);




#define Address_canEquip 0x080161A4
typedef bool (*Prototype_canEquip)(Combatant* unit, u8 itemID);
Prototype_canEquip canEquip = (Prototype_canEquip)(Address_canEquip | MODE_BIT_THUMB);
*/
#ifdef EQUIPPED_FUNC
#define Address_equippedItem 0x08016764
typedef Item (*Prototype_equippedItem)(Unit* unit);
Prototype_equippedItem equippedItem = (Prototype_equippedItem)(Address_equippedItem | MODE_BIT_THUMB);
#endif

#ifdef ALLOCATE_HELPERS
void* (*allocate)() = (void*(*)())(0x800459C | 1);
void (*deallocate)(void* x) = (void (*)(void*))(0x80045AC | 1);
#endif

#ifdef TOTAL_LVL 
int (*totallvl)(Unit* r) = (int(*)(Unit*))(0x8029D7C | 1);
#endif

#ifdef RAMPointer
Unit*(*getUnitPointer)(u8 unit) = (Unit*(*)(u8)) (0x8018D0C | 1);
#endif 

#ifdef CharacterRAM
Unit*(*getCharacterPointer)(u8 unit) = (Unit*(*)(u8)) (0x8017D34 | 1);
#endif

#ifdef NEW_WEAP_LVL
u8(*getNewWeapLvl)(CP r) = (u8(*)(CP))(0x8029AFC | 1);
#endif

#ifdef SUPPLY
Item*(*getSupplyPointer)() = (Item*(*)())(0x802E700 | 1);
#endif

#ifdef IF_NEW
bool(*ifNew)(CP r) = (bool(*)(CP))(0x8029BE8 | 1);
#endif
/*
#define Address_useMagicAnimation 0x080184DC
typedef bool (*Prototype_useMagicAnimation)(Combatant* unit);
Prototype_useMagicAnimation useMagicAnimation = (Prototype_useMagicAnimation)(Address_useMagicAnimation | MODE_BIT_THUMB);

#define Address_support 0x08026694
typedef int (*Prototype_support)(int unit, int index);
Prototype_support support = (Prototype_support)(Address_support | MODE_BIT_THUMB);

#define Address_Display 0x0801F100//const r0 = 2025260 // 2024f6c
typedef void (*Prototype_Display)(int constint, int icon, int chararrayptr);
Prototype_Display Display = (Prototype_Display)(Address_Display | MODE_BIT_THUMB);

#define Address_Music 0x08015F84//const r0 = 2025260 // 2024f6c
typedef void (*Prototype_Music)();
Prototype_Music Music = (Prototype_Music)(Address_Music | MODE_BIT_THUMB);

#define Address_unitcount 0x08023874
typedef int (*Prototype_unitcount)(u8 alliance, int constant); // = 0x1000C
Prototype_unitcount unitcount = (Prototype_unitcount)(Address_unitcount | MODE_BIT_THUMB);

#define Address_Chapter 0x8031574
typedef int (*Prototype_Chapter)(u8 chapter); //
Prototype_Chapter Chapter = (Prototype_Chapter)(Address_Chapter | MODE_BIT_THUMB);

#define Address_Text 0x08012C9C
typedef char * (*Prototype_Text)(u16 textID, char * textbuf);
Prototype_Text Text = (Prototype_Text)(Address_Text | MODE_BIT_THUMB);

#define Address_EventID 0x080798F8
typedef bool (*Prototype_EventID)(u8 eventID);
Prototype_EventID EventID = (Prototype_EventID)(Address_EventID | MODE_BIT_THUMB);

//void *window(int x, int y, int w, int h) = (void (*)(int, int, int, int))(0x8049CE5);

int (*getItemEffect)(u16 y) =  (int (*)(u16))(0x8017424 | 1);
/*
__attribute__ ((noinline))
u32 CharacterRAM(int CharacterID){
    for(int i = 1; i < 0xFF; i++){
        u32 charpointer = RAM(i);
        if(*(char*)((*(u32*)charpointer)+4) == CharacterID){
            /*check if the character ID of the current RAM unit pointer == character ID passed
            if so, return it; if not, check the next one
            return charpointer;
        }        
    }
    return 0;
}*/

#endif
