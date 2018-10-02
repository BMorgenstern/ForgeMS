#ifndef __ARM_H__
#define __ARM_H__

#ifndef NULL
#define NULL 0
#endif

typedef unsigned       char  u8;
typedef unsigned       short u16;
typedef unsigned       int   u32;
typedef unsigned long  long  u64;
typedef signed         char  s8;
typedef signed         short s16;
typedef signed         int   s32;
typedef signed   long  long  s64;
typedef float                f32;
typedef double               f64;

#ifdef __LANGUAGE_C__
typedef u8                   bool;
#define false                0
#define true                 1
#endif

#define MODE_BIT_ARM   0
#define MODE_BIT_THUMB 1

#endif
