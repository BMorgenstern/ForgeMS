/**
 * These macros are for following the specification for the utility here:
http://dl.dropbox.com/u/336940/Software/Hextator%27s%20Doc/Development/Applications/Patching/Assembly%20Patcher/folDIR.html
 * so we can write hacks for already assembled applications and go straight from high level
 * source to a binary patch
**/

#ifndef __ADAPT__
#define __ADAPT__ 1

// Strings
#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)
#define UNIQUE_STRING __FILE__ TOSTRING(__LINE__)

// Faster inline assembly syntax
#define _asm __asm__ __volatile__

// For making debugging comments
#if defined(__MIPS_H__)
#define COMMENT(com) _asm("#" com)
#elif defined(__ARM_H__)
#define COMMENT(com) _asm("@" com)
#endif

// Custom directives to be fixed by a post processing script
// Sets origin/location explicitly
#define ORIGIN(addr) COMMENT(".org\t" TOSTRING(addr))
// Sets origin/location to be after the symbol given
// i.e. origin = symbolOrigin + symbolSize
// XXX: Generates an immediate value prefix
#define CONTINUE(sym) COMMENT(".cont\t%0" :: "i" (sym))

// For labels, which are similarly trivial
#define LABEL(name) _asm(#name ":")
// NOP instruction
#define NOP _asm("nop")
// 4 byte align
#define ALIGN(amt) _asm(".align\t" #amt)

// Language specific directives
#if defined(__MIPS_H__)
#define NOREORDER _asm(".set\tnoreorder")
#define REORDER _asm(".set\treorder")
#elif defined(__ARM_H__)
// Mark ARM code
#define ARM _asm(".arm")
// Mark Thumb code
#define THUMB _asm(".thumb")
#endif

// For hooking existing code
#define NORETURN _asm(".funcend")
#if defined(__MIPS_H__)
#define HOOK(addr) \
	ORIGIN(addr); \
	NOREORDER
#define HOOKEND \
	REORDER; \
	NORETURN
#ifndef PUSH_ALL
void PUSH_ALL(void) {
	_asm("ADDIU	$sp,	$sp,	0xFF1C	#-0x00E4");
	_asm("SW	$1,	0x0000	($sp)	#");
	_asm("SW	$2,	0x0004	($sp)	#");
	_asm("SW	$3,	0x0008	($sp)	#");
	_asm("SW	$4,	0x000C	($sp)	#");
	_asm("SW	$5,	0x0010	($sp)	#");
	_asm("SW	$6,	0x0014	($sp)	#");
	_asm("SW	$7,	0x0018	($sp)	#");
	_asm("SW	$8,	0x001C	($sp)	#");
	_asm("SW	$9,	0x0020	($sp)	#");
	_asm("SW	$10,	0x0024	($sp)	#");
	_asm("SW	$11,	0x0028	($sp)	#");
	_asm("SW	$12,	0x002C	($sp)	#");
	_asm("SW	$13,	0x0030	($sp)	#");
	_asm("SW	$14,	0x0034	($sp)	#");
	_asm("SW	$15,	0x0038	($sp)	#");
	_asm("SW	$16,	0x003C	($sp)	#");
	_asm("SW	$17,	0x0040	($sp)	#");
	_asm("SW	$18,	0x0044	($sp)	#");
	_asm("SW	$19,	0x0048	($sp)	#");
	_asm("SW	$20,	0x004C	($sp)	#");
	_asm("SW	$21,	0x0050	($sp)	#");
	_asm("SW	$22,	0x0054	($sp)	#");
	_asm("SW	$23,	0x0058	($sp)	#");
	_asm("SW	$24,	0x005C	($sp)	#");
	_asm("SW	$25,	0x0060	($sp)	#");
	_asm("SWC1	$f0,	0x0064	($sp)	#");
	_asm("SWC1	$f1,	0x0068	($sp)	#");
	_asm("SWC1	$f2,	0x006C	($sp)	#");
	_asm("SWC1	$f3,	0x0070	($sp)	#");
	_asm("SWC1	$f4,	0x0074	($sp)	#");
	_asm("SWC1	$f5,	0x0078	($sp)	#");
	_asm("SWC1	$f6,	0x007C	($sp)	#");
	_asm("#SWC1	$f7,	0x0080	($sp)	#");
	_asm("SWC1	$f8,	0x0084	($sp)	#");
	_asm("SWC1	$f9,	0x0088	($sp)	#");
	_asm("SWC1	$f10,	0x008C	($sp)	#");
	_asm("SWC1	$f11,	0x0090	($sp)	#");
	_asm("SWC1	$f12,	0x0094	($sp)	#");
	_asm("SWC1	$f13,	0x0098	($sp)	#");
	_asm("SWC1	$f14,	0x009C	($sp)	#");
	_asm("SWC1	$f15,	0x00A0	($sp)	#");
	_asm("SWC1	$f16,	0x00A4	($sp)	#");
	_asm("SWC1	$f17,	0x00A8	($sp)	#");
	_asm("SWC1	$f18,	0x00AC	($sp)	#");
	_asm("SWC1	$f19,	0x00B0	($sp)	#");
	_asm("SWC1	$f20,	0x00B4	($sp)	#");
	_asm("#SWC1	$f21,	0x00B8	($sp)	#");
	_asm("#SWC1	$f22,	0x00BC	($sp)	#");
	_asm("#SWC1	$f23,	0x00C0	($sp)	#");
	_asm("#SWC1	$f24,	0x00C4	($sp)	#");
	_asm("#SWC1	$f25,	0x00C8	($sp)	#");
	_asm("SWC1	$f26,	0x00CC	($sp)	#");
	_asm("SWC1	$f27,	0x00D0	($sp)	#");
	_asm("SWC1	$f28,	0x00D4	($sp)	#");
	_asm("SWC1	$f29,	0x00D8	($sp)	#");
	_asm("SWC1	$f30,	0x00DC	($sp)	#");
	_asm("#SWC1	$f31,	0x00E0	($sp)	#");
}
#endif
#ifndef POP_ALL
void POP_ALL(void) {
	_asm("LW	$1,	0x0000	($sp)	#");
	_asm("LW	$2,	0x0004	($sp)	#");
	_asm("LW	$3,	0x0008	($sp)	#");
	_asm("LW	$4,	0x000C	($sp)	#");
	_asm("LW	$5,	0x0010	($sp)	#");
	_asm("LW	$6,	0x0014	($sp)	#");
	_asm("LW	$7,	0x0018	($sp)	#");
	_asm("LW	$8,	0x001C	($sp)	#");
	_asm("LW	$9,	0x0020	($sp)	#");
	_asm("LW	$10,	0x0024	($sp)	#");
	_asm("LW	$11,	0x0028	($sp)	#");
	_asm("LW	$12,	0x002C	($sp)	#");
	_asm("LW	$13,	0x0030	($sp)	#");
	_asm("LW	$14,	0x0034	($sp)	#");
	_asm("LW	$15,	0x0038	($sp)	#");
	_asm("LW	$16,	0x003C	($sp)	#");
	_asm("LW	$17,	0x0040	($sp)	#");
	_asm("LW	$18,	0x0044	($sp)	#");
	_asm("LW	$19,	0x0048	($sp)	#");
	_asm("LW	$20,	0x004C	($sp)	#");
	_asm("LW	$21,	0x0050	($sp)	#");
	_asm("LW	$22,	0x0054	($sp)	#");
	_asm("LW	$23,	0x0058	($sp)	#");
	_asm("LW	$24,	0x005C	($sp)	#");
	_asm("LW	$25,	0x0060	($sp)	#");
	_asm("LWC1	$f0,	0x0064	($sp)	#");
	_asm("LWC1	$f1,	0x0068	($sp)	#");
	_asm("LWC1	$f2,	0x006C	($sp)	#");
	_asm("LWC1	$f3,	0x0070	($sp)	#");
	_asm("LWC1	$f4,	0x0074	($sp)	#");
	_asm("LWC1	$f5,	0x0078	($sp)	#");
	_asm("LWC1	$f6,	0x007C	($sp)	#");
	_asm("#LWC1	$f7,	0x0080	($sp)	#");
	_asm("LWC1	$f8,	0x0084	($sp)	#");
	_asm("LWC1	$f9,	0x0088	($sp)	#");
	_asm("LWC1	$f10,	0x008C	($sp)	#");
	_asm("LWC1	$f11,	0x0090	($sp)	#");
	_asm("LWC1	$f12,	0x0094	($sp)	#");
	_asm("LWC1	$f13,	0x0098	($sp)	#");
	_asm("LWC1	$f14,	0x009C	($sp)	#");
	_asm("LWC1	$f15,	0x00A0	($sp)	#");
	_asm("LWC1	$f16,	0x00A4	($sp)	#");
	_asm("LWC1	$f17,	0x00A8	($sp)	#");
	_asm("LWC1	$f18,	0x00AC	($sp)	#");
	_asm("LWC1	$f19,	0x00B0	($sp)	#");
	_asm("LWC1	$f20,	0x00B4	($sp)	#");
	_asm("#LWC1	$f21,	0x00B8	($sp)	#");
	_asm("#LWC1	$f22,	0x00BC	($sp)	#");
	_asm("#LWC1	$f23,	0x00C0	($sp)	#");
	_asm("#LWC1	$f24,	0x00C4	($sp)	#");
	_asm("#LWC1	$f25,	0x00C8	($sp)	#");
	_asm("LWC1	$f26,	0x00CC	($sp)	#");
	_asm("LWC1	$f27,	0x00D0	($sp)	#");
	_asm("LWC1	$f28,	0x00D4	($sp)	#");
	_asm("LWC1	$f29,	0x00D8	($sp)	#");
	_asm("LWC1	$f30,	0x00DC	($sp)	#");
	_asm("#LWC1	$f31,	0x00E0	($sp)	#");
	_asm("ADDIU	$sp,	$sp,	0x00E4	#");
}
#endif
#define SWITCH_TO_USER_MODE \
	NOREORDER; \
	_asm("JAL				PUSH_ALL"); \
	NOP; \
	REORDER
//	_asm("ADDIU	$sp,	$sp,	0xFFFC	#-0x0004"); \
//	_asm("SW	$31,	0x0000	($sp)	#"); \
Above lines removed from macro above
#define RETURN_FROM_USER_MODE \
	NOREORDER; \
	_asm("JAL				POP_ALL"); \
	NOP; \
	REORDER
//	_asm("LW	$31,	0x0000	($sp)	#"); \
//	_asm("ADDIU	$sp,	$sp,	0x0004	#"); \
Above lines removed from macro above
#elif defined(__ARM_H__)
#define HOOK(addr) \
	ORIGIN(addr)
#define HOOKEND \
	NORETURN
#define SET_RETURN(addr) \
	_asm("push {r0}"); \
	_asm("mov r0, %0" :: "i" (((addr) >> 24) & 0xFF)); \
	_asm("lsl r0, r0, #8"); \
	_asm("add r0, %0" :: "i" (((addr) >> 16) & 0xFF)); \
	_asm("lsl r0, r0, #8"); \
	_asm("add r0, %0" :: "i" (((addr) >> 8) & 0xFF)); \
	_asm("lsl r0, r0, #8"); \
	_asm("add r0, %0" :: "i" ((addr) & 0xFF)); \
	_asm("str r0, [sp, #8]"); \
	_asm("pop {r0}")
#define SWITCH_TO_USER_MODE \
	_asm("push {r0-r7}"); \
	_asm("mov r0, r8"); \
	_asm("mov r1, r9"); \
	_asm("mov r2, r10"); \
	_asm("mov r3, r11"); \
	_asm("mov r4, r12"); \
	_asm("push {r0-r5}")
	//_asm("mrs r5, cpsr"); \
Above lines removed from macro above
// TODO: More of these
#define READ_R6(sym) \
	_asm("ldr\t%0, [sp, #48]" : "=r" (sym))
#define READ_R5(sym) \
	_asm("ldr\t%0, [sp, #44]" : "=r" (sym))
#define READ_R4(sym) \
	_asm("ldr\t%0, [sp, #40]" : "=r" (sym))
#define READ_R3(sym) \
	_asm("ldr\t%0, [sp, #36]" : "=r" (sym))	
#define READ_R2(sym) \
	_asm("ldr\t%0, [sp, #32]" : "=r" (sym))
#define READ_R1(sym) \
	_asm("ldr\t%0, [sp, #28]" : "=r" (sym))
#define READ_R0(sym) \
	_asm("ldr\t%0, [sp, #24]" : "=r" (sym))	
#define UPDATE_R0(sym) \
	_asm("str\t%0, [sp, #24]" :: "r" (sym))
#define UPDATE_R1(sym) \
	_asm("str\t%0, [sp, #28]" :: "r" (sym))	
#define UPDATE_R2(sym) \
	_asm("str\t%0, [sp, #32]" :: "r" (sym))
#define UPDATE_R3(sym) \
	_asm("str\t%0, [sp, #36]" :: "r" (sym))
#define UPDATE_R4(sym) \
	_asm("str\t%0, [sp, #40]" :: "r" (sym))	
#define UPDATE_R5(sym) \
	_asm("str\t%0, [sp, #44]" :: "r" (sym))	
#define RETURN_FROM_USER_MODE \
	_asm("pop {r0-r5}"); \
	_asm("mov r8, r0"); \
	_asm("mov r9, r1"); \
	_asm("mov r10, r2"); \
	_asm("mov r11, r3"); \
	_asm("mov r12, r4"); \
	_asm("pop {r0-r7}")
//	_asm("msr cpsr, r5"); \
Above lines removed from macro above
#endif

// It might be cool to control which registers are used for passing arguments
// and receiving output
#define NAME_REG(reg, name) _asm(#name " .req " #reg)
#define REGISTER(type, var, reg) register type var __asm__(#reg)
#define READ_REG(arg, reg) _asm("mov\t%0, " #reg : "=r" (arg))
#define MOV(reg1, reg2) _asm("mov\t" #reg1 ", " #reg2)
#define MOVI(reg, exp) _asm("mov\t" #reg ", %0" :: "i" (exp))
#define MOVR(reg, exp) _asm("mov\t" #reg ", %0" :: "r" (exp))

// Load relative macros
#if defined(__MIPS_H__)
#define LOAD_LIT(reg, lit) _asm("li\t" #reg ", " TOSTRING(lit))
#elif defined(__ARM_H__)
#define LOAD_LIT(reg, lit) _asm("ldr\t" #reg ", =" TOSTRING(lit))
#define LOAD_SYM(reg, sym) _asm("ldr\t" #reg ", " TOSTRING(sym))
#define LOAD_VAR_SYM(var, sym) _asm("ldr\t%0, " TOSTRING(sym) : "=r" (var))
#endif

// Absolute jumps
#if defined(__MIPS_H__)
#define REG_BRANCH(reg) _asm("jr\t" #reg)
#elif defined(__ARM_H__)
#define REG_BRANCH(reg) _asm("bx\t" #reg)
#define REG_BRANCH_ARM(reg, cond) _asm("bx" #cond "\t" #reg)
#define REG_RETURN_ARM(reg, addr, cond) \
	_asm("ldr" #cond "\t" #reg ", =" TOSTRING(addr)); \
	REG_BRANCH(reg, cond)
#endif
#define REG_RETURN(reg, addr) LOAD_LIT(reg, addr); REG_BRANCH(reg)

// Relative jumps
#if defined(__MIPS_H__)
#define LITERALBRANCH(exp) _asm("beqz\t$0, " #exp)
#elif defined(__ARM_H__)
#define LITERALBRANCH(exp) _asm("b\t" #exp)
#endif

// For embedding literal
#define BYTE(lit) _asm(".byte\t" TOSTRING(lit))
#define SHORT(lit) _asm(".short\t" TOSTRING(lit))
#define LONG(lit) _asm(".long\t" TOSTRING(lit))

// For enabling and disabling "recording", which is a way of selecting what of the compiler
// output to actually keep.
// Abusing this is how we embed instructions which force the compiler to do our
// bidding without actually having those instructions remain at assembly time
// (where the instructions are no longer purposeful)
#define DO_RECORD COMMENT("FILE_BEGIN")
#define NO_RECORD COMMENT("FILE_END")

// Some code should just be inlined, and code that is meant to be a function should never
// be inlined
// These macros simplify the process of dictating this information
#define FUNC volatile __attribute__((noinline))
#define CODE volatile inline __attribute__((always_inline))

// Macros for marking registers as safe or unsafe to use.
// Because of how this works, registers are marked as unsafe in reverse;
// they are listed at the end of the relevant function and all code up to the
// previous time associated registers were marked as safe will be unable to use
// the "unsafe" registers. This means that functions which mark any registers as
// unsafe must mark all registers as safe at their beginning using "YES_REGS" to
// avoid starving previous functions and potentially causing the compiler to fail.
#if defined(__MIPS_H__)
// TODO: This
#define YES_REG(reg)
#define NO_REG(reg)
#define YES_REGS
#define NO_REGS
#elif defined(__ARM_H__)
#define YES_REG(reg) NO_RECORD; volatile register int _y##reg __asm__(#reg); _y##reg = *(int*)_y##reg; DO_RECORD
#define NO_REG(reg) NO_RECORD; volatile register int _n##reg __asm__(#reg); _asm("str\t" #reg ", [r0]" :: "r" (_n##reg)); DO_RECORD
#define YES_REGS YES_REG(r0); YES_REG(r1); YES_REG(r2); YES_REG(r3); YES_REG(r4); YES_REG(r5); YES_REG(r6); YES_REG(r7); YES_REG(r8); YES_REG(r9); YES_REG(r10); YES_REG(r11); YES_REG(r12); YES_REG(r13); YES_REG(r14)
#define NO_REGS NO_REG(r0); NO_REG(r1); NO_REG(r2); NO_REG(r3); NO_REG(r4); NO_REG(r5); NO_REG(r6); NO_REG(r7); NO_REG(r8); NO_REG(r9); NO_REG(r10); NO_REG(r11); NO_REG(r12); NO_REG(r13); NO_REG(r14)
#endif

// These simplify function declarations
#define FUNCTION(type, name, args...) FUNC type name ( args ) { YES_REGS;
// FUNC_START should only be used if the YES_REGS; in FUNCTION() is inappropriate
#define FUNC_START { DO_RECORD;
#define FUNC_END NO_RECORD; }
#define INLINE(type, name, args...) CODE type name ( args ) { YES_REGS;
#define INLINE_END }

// Including has to be done after compiling, but we can have include statements cleanly
// embedded in the high level source using these
// This includes a whole file, which is actually a pretty bad idea
//#define IMPORT(file, ext, mode) FUNC void ___import_other_files_##file##___() { DO_RECORD; _asm(".include\t\"" #file ext ".formatted.asm\""); _asm("." mode); NO_RECORD; }
// This includes only a function from a file
#define IMPORT(func, file, ext, mode) FUNC void ___import_other_files_##file##_##func##___() { DO_RECORD; _asm(".set\t" #func "Switch, 1"); _asm(".include\t\"" #file ext ".formatted.asm\""); _asm("." mode); NO_RECORD; }
// This includes only a function from a file, but does so directly within another function
#define EMBED(func, file, ext, mode) _asm(".set\t" #func "Switch, 1"); _asm(".include\t\"" #file ext ".formatted.asm\""); _asm("." mode)

// For remotely complex functions, returning while in a function that is not
// "normal" (as marked by having "_nrmlfunc" in the function's name) will fail
// to exclude the invalid stack instructions associated with those that were
// excluded from the beginning of the function; this macro can be used to get
// around this though of course it is limited to returning only single return
// values in the r0 register (which is typically all that is necessary anyway)
#if defined(__MIPS_H__)
#define RETURN_VAR(arg) _asm("mov\t$2, %0" :: "r" (arg))
#elif defined(__ARM_H__)
#define RETURN_VAR(arg) _asm("mov\tr0, %0" :: "r" (arg))
#endif
// This lets us choose the return register
#define RETURN_VAR_REG(arg, reg) _asm("mov\t" #reg ", %0" :: "r" (arg))

// Returning
#if defined(__MIPS_H__)
#define RETURN _asm("jr\t$31")
#elif defined(__ARM_H__)
#define RETURN _asm("bx\tlr")
#endif

// Stack control
#if defined(__MIPS_H__)
#define PUSH(reg) \
	_asm("addiu\t$sp, $sp, 0xfffc"); \
	_asm("sw\t" #reg ", 0x0000 ($sp)")
#define POP(reg) \
	_asm("lw\t" #reg ", 0x0000 ($sp)"); \
	_asm("addiu\t$sp, $sp, 0x0004")
#define POPVAR(var) \
	_asm("lw\t%0, 0x0000 ($sp)" : "=r" (var)); \
	_asm("addiu\t$sp, $sp, 0x0004")
#elif defined(__ARM_H__)
#define ARM_PUSH(args...) _asm("stmfd\tsp!, {" #args "}")
#define ARM_POP(args...) _asm("ldmfd\tsp!, {" #args "}")
// These two work for both ARM and Thumb and should be used instead
#define PUSH(args...) _asm("push\t{" #args "}")
#define POP(args...) _asm("pop\t{" #args "}")
// Here is some code for doing the same with variables in unknown registers
#define PUSHVAR(var) _asm("push\t{%0}" :: "r" (var))
#define POPVAR(var) _asm("pop\t{%0}" : "=r" (var))
#endif

// We must record the main function if we want its contents
#define MAIN_START int main() { DO_RECORD;
// We must stop recording after the main function ends to avoid assembling the
// extra garbage that comes afterward (important labels and data will still be kept)
#define MAIN_END NO_RECORD; }

// ARM cores have a Thumb mode; we will need to compile Thumb code separately with
// some strange hacks to facilitate putting the compiled Thumb code correctly mixed
// into the compiled ARM code and these macros will help with that
#ifdef __ARM_H__
#define THUMB_START FUNC void ___thumb_header___() FUNC_START _asm(".grab"); FUNC_END
#define THUMB_FUNC(type, name, args...) FUNC type name ( args ) { YES_REGS; \
	_asm(".funcHeader"); \
	_asm(".ifndef\t" #name "Switch"); \
	_asm(".set\t" #name "Switch, 0"); \
	_asm(".endif"); \
	_asm(".if\t" #name "Switch != 0"); \
	_asm(".set\t" #name "Switch, 0"); \
	_asm(".endFuncHeader"); \
	THUMB;
#define THUMB_FUNC_END _asm(".closeif"); FUNC_END
#endif

// We can reference things defined using the previous macros in our main source file
// with these:
#define UNIQUE_CALL UNIQUE_STRING
#ifdef __ARM_H__
#define INLINE_THUMB(func, reg, file, ext, mode) \
	_asm("ldr\t" #reg ", =" #func "Call" UNIQUE_CALL " + 1"); \
	_asm("adr\tlr, " #func "Call" UNIQUE_CALL "_return"); \
	_asm("bx\t" #reg); \
	_asm(#func "Call" UNIQUE_CALL ":"); \
	EMBED(func, file, ext, mode); \
	ALIGN_4; \
	_asm(#func "Call" UNIQUE_CALL "_return:")
#define THUMB_CALL(func, file, ext, mode, type, args...) \
	IMPORT(func, file, ext, mode) \
	extern FUNC type func ( args )
#define CALL_THUMB(func, reg) \
	_asm("ldr\t" #reg ", =\v%0 + 1" :: "i" (func)); \
	_asm("adr\tlr, " #func "Call" UNIQUE_CALL "_return"); \
	_asm("bx\t" #reg); \
	_asm(#func "Call" UNIQUE_CALL "_return:")
#define CALL_THUMB_LIT(lit, reg) \
	LOAD_LIT(reg, lit + 1); \
	_asm("adr\tlr, literalCall" UNIQUE_CALL "_return"); \
	_asm("bx\t" #reg); \
	_asm("literalCall" UNIQUE_CALL "_return:")
#endif

// Provisions for calling ARM code from Thumb
#ifdef __ARM_H__
#define SWITCH_TO_ARM \
	ALIGN_4; \
	_asm("bx\tpc"); \
	ALIGN_4; \
	ARM
#define CALL_ARM(func, reg) \
	_asm("ldr\t" #reg ", =\v%0" :: "i" (func)); \
	_asm("bx\t" #reg)
#define CALL_ARM_LIT(lit, reg) \
	LOAD_LIT(reg, lit); \
	_asm("bx\t" #reg)
#define THUMB_SET_RETURN(lit) \
	PUSH(r0); \
	LOAD_LIT(r0, lit + 1); \
	_asm("mov\tlr, r0"); \
	POP(r0)
#endif

#ifdef __ARM_H__
// For calling potentially distant thumb functions
#define LONG_CALL_THUMB(lit, reg) \
	PUSH(r0); \
	_asm("adr\tr0, literalCall" UNIQUE_CALL "_return"); \
	_asm("add\tr0, #0x01"); \
	MOV(lr, r0); \
	POP(r0); \
	LOAD_LIT(reg, lit + 1); \
	_asm("bx\t" #reg); \
	ALIGN_4; \
	_asm("literalCall" UNIQUE_CALL "_return:")
// For doing a long return
#define LONG_RETURN_THUMB(lit) \
	THUMB_SET_RETURN(lit); \
	RETURN
#endif

#define LITERAL(val) _asm(".long\t\v%0" :: "i" (val))
#define ADDRESS(val) LITERAL(val)
#define HARDWARE_OFFSET(addr) \
	FUNC void ___hardware_offset___() { DO_RECORD; \
	ADDRESS(addr); \
	NO_RECORD; }
#define HACK_ADDR(name) name##_ORIGIN
#define ORIGIN_SYM(sym) COMMENT(".org\t%0_ORIGIN" :: "i" (sym))
#ifdef __ARM_H__
#define HACK_ADDR_LIT(sym, mode) \
	_asm(".long\t%0_ORIGIN | %1" :: "i" (sym), "i" (mode)) // "i"
#endif
#define HACK_SIZE(name) name##_SIZE
#define HACK_HEADER_OFFSET(name, origin, offset) \
	_asm(".set\t" TOSTRING(HACK_ADDR(name)) ", " #origin); \
	_asm(".set\t" TOSTRING(HACK_SIZE(name)) ", " #name "_END - " #name "_START"); \
	COMMENT("Origin"); \
	_asm(".long\t" TOSTRING(HACK_ADDR(name))); \
	COMMENT("Offset (bytes to ignore)"); \
	LITERAL(offset); \
	COMMENT("Size"); \
	_asm(".long\t" TOSTRING(HACK_SIZE(name) - offset)); \
	_asm(#name "_START:")
#define HACK_HEADER(name, origin) \
	HACK_HEADER_OFFSET(name, origin, 0)
#define HACK_FOOTER(name) \
	_asm(".pool"); \
	_asm(".movedown" #name "_END:")
#define HACK_LABEL_ADDR(name, label) \
	(HACK_ADDR(name) + label - name##_START)
#define HACK_END(name) \
	(HACK_ADDR(name) + HACK_SIZE(name))
#define HACK_END_ALIGN_4(name) \
	((HACK_END(name) + 3) & (~3))

// Relative jumps
#define RELATIONTOLABEL(targetAddress, currentContext, label) \
	(targetAddress - HACK_LABEL_ADDR(currentContext, label))
#define RELATIONTOCURRLOC(targetAddress, currentContext) \
	RELATIONTOLABEL(targetAddress, currentContext, .)
#define BRANCH(targetAddress, currentContext) \
	BRANCH(". + " TOSTRING(RELATIONTOCURRLOC(targetAddress, currentContext)))

#endif
