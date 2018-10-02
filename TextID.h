#ifndef __TEXT_ID__
#define __TEXT_ID__

#define RTextThread 0x8A01628
#define RButtonThread 0x8A00A98
#define ShopTextThread 0x8591358


class TextID{
    private:
        unsigned short id;
    public: 
        int get(){ return id; }
		TextID(int arg){this->id = arg;}
};

class Name{
    private:
        TextID name;
        TextID desc;
    public: 
        TextID getName(){ return name; }
        TextID getDesc(){ return desc; }
};

char* (*getText)(TextID t) = (char*(*)(TextID))(0x800A2A0);


#endif