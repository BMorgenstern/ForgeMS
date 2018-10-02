#ifndef __THREAD__
#define __THREAD__

/**
This thread class exists in the game already, this is simply my best imitation of it
*/

#include "arm.h"
#include "adapt.h"

#define INITADDRESS 0x8002C7D
#define KILLADDRESS 0x80030E9
#define SEARCH 0x8002E9D
#define SCAN 0x8002F25

class Thread{
public:
    enum Action
    {
        Kill, SetText, ExecuteOnce, Execute, 
        SetDestructor, SubThread, SubThreadWithArgs, SubThread2,
        ThreadSearch, KillAll, AdvanceAll, Skip, 
        SkipUntil, SetPosition, Buffer, Set26, 
        Nothing, KillIfDupExists 
    };
    typedef void(*Threadfunc)(Thread*);
    class ThreadData{
    public:
        Action action;
        Threadfunc tfunc;
        Thread* ThreadInit(Action action=Execute){
            Thread*(*func)(ThreadData* d, Action a) = (Thread*(*)(ThreadData*, Action))(INITADDRESS);
            return func(this, action);
        }
        Thread* Search(){
        	Thread*(*func)(ThreadData* d) = (Thread*(*)(ThreadData*))(SEARCH);
        	return func(this);
        }
    };
    ThreadData* origin;
    ThreadData* current;
    Threadfunc destructor;
    Threadfunc currfunc;
    char* threaddesc; // probably a debug relic
    Thread* parent;
    Thread* child;
    Thread* parent2;
    Thread* child2;
    short buffer; //number of frames to sleep for
    short unk;
	u8 bitmap;//28
	u8 scratch;//29
	u16 scratchshorts[3];
    int data[15];


    //Methods
    void SetFunc(Threadfunc f){
        this->currfunc = f;
    }
    void NextFunc(){
        this->SetFunc(0);
    }
    void KillThread(){
        Threadfunc func = (Threadfunc)KILLADDRESS;
        func(this);
    }
	void ScanThread(int a){
        void(*func)(Thread* t, int a) = (void(*)(Thread*, int))(SCAN);
        func(this, a);
    }
};

typedef Thread::ThreadData ThreadData;
typedef Thread::Threadfunc Threadfunc;

#endif

