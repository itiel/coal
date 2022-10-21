#ifndef _VM_H_
#define _VM_H_

#include "./common.h"

/* Flags Register */

typedef union CoalVMFlags {
  Word all;

  struct {

    /* Is Running? */

    Word running : 1;
    
    /* Arith & Logic */

    Word zero     : 1; /* ZF */
    Word carry    : 1; /* CF */
    Word sign     : 1; /* SF */
    Word overflow : 1; /* OF */
    Word pair     : 1; /* PF */
    Word nan      : 1; /* NF */
    Word infinity : 1; /* IF */

    /* Interrupts */

    Word intrenable : 1;
    Word intrcapi   : 1; /* C/Coal VM API */
    Word intrsoft   : 1;
    Word intrhard   : 1;

    /* Exit Reasons */

    Word badinst         : 1;
    Word haltinst        : 1;
    Word accessviolation : 1;
    Word stackoverflow   : 1;
    Word stackunderflow  : 1;
    
    /* Ununsed */

    Word unused : 15;
  };
} CoalVMFlags;

#define _flags_set(reg, flag, val) \
  (reg.flag = (val))

#define _flags_include(reg, flag) \
  _flags_set(reg, flag, 1U)

#define _flags_exclude(reg, flag) \
  _flags_set(reg, flag, 0U)

#define _flags_toggle(reg, flag) \
  _flags_set(reg, flag, !reg.flag)

/* Virtual Machine */

/* 
  Distribution of RAM and VM Pointers
  
  +---------------+ <- Global Var Frame (Absolute)
  |               |    (always zero)
  |   2. Global   |
  |      Var      | <- GLV addr (Relative)
  |               |
  +---------------+ <- Program Frame (Absolute) 
  |               | 
  |  1. Program   | <- Program Counter (Relative)
  |               |
  +---------------+ <- Stack Frame (Absolute)
  |               |
  |   3. Stack    | <- Stack pointer (Relative)
  |               |
  +---------------+ <- Heap Frame (Absolute)
  |               |
  |   4. Heap     | <- Heap addr (Relative)
  |               |
  +---------------+

*/

#define RAM_SIZE 0x80000U

typedef struct CoalVM {
  
  /* Registers */

  Word ra; /* Accumulator */
  Word rb; /* Gral. Purpose */
  Word rc; /* Gral. Purpose */
  Word rd; /* Address */

  /* Absolute ptrs */
  
  Word pf; /* Program Frame */
  Word sf; /* Stack Frame */
  Word hf; /* Heap Frame */

  /* Relative ptrs */

  Word pc; /* Program counter */
  Word sp; /* Stack pointer */
  Word ff; /* Function Frame */
  
  /* Current Inst */

  Word inst;

  /* Flags (see `Flags Register`)*/

  CoalVMFlags flags; 
  
  /* RAM */

  Byte ram[RAM_SIZE];

} CoalVM;

/* Handle Type */

#define HandleDecl(name) void name (CoalVM * vm)
typedef void (* Handle) (CoalVM * vm);

/* RAM Read & Write */

void _ram_write_byte (CoalVM * vm, Word addr, Byte val);
Byte _ram_read_byte (CoalVM * vm, Word addr);
void _ram_write_word (CoalVM * vm, Word addr, Word val);
Word _ram_read_word (CoalVM * vm, Word addr);

/* Program Fetch */

Word _prog_fetch (CoalVM * vm);

/* Stack */

Word _stack_read (CoalVM * vm, Word addr);
void _stack_write (CoalVM * vm, Word addr, Word val);
Word _stack_pop (CoalVM * vm);
void _stack_push (CoalVM * vm, Word val);
Word _stack_peek (CoalVM * vm);

/* Init */

bool CoalVM_init (CoalVM * vm, Word p_frame, Word p_len, Word p_start);

/* Run */

void CoalVM_run (CoalVM * vm) ;

/* Statistics */

void CoalVM_stats (CoalVM * vm);

#endif /* #ifndef _VM_H_ */
