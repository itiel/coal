#include <stdio.h>
#include <unistd.h>
#include <arpa/inet.h>

#include "./vm.h"
#include "./vm-inst.h"
#include "./vm-inst-handle.h"
#include "./vm-capi.h"

/* Util */

#define _print_bits(_w) \
  { \
    for (int _i = (sizeof(_w) * 8) - 1; _i >= 0; _i--) { \
      printf(((_w) & (1 << _i)) ? "1" : "0"); \
      if (!(_i % 8)) printf(" "); \
    } \
  } 

/* RAM Read & Write */

void _ram_write_byte (CoalVM * vm, Word addr, Byte val) {
  if (addr >= sizeof(vm->ram)) {
    vm->flags.accessviolation = TRUE;
    vm->flags.running = FALSE;
    return;
  }

  vm->ram[addr] = val;
}

Byte _ram_read_byte (CoalVM * vm, Word addr) {
  if (addr >= sizeof(vm->ram)) {
    vm->flags.accessviolation = TRUE;
    vm->flags.running = FALSE;
    return 0;
  }

  return vm->ram[addr];
}

void _ram_write_word (CoalVM * vm, Word addr, Word val) {
  if ((addr + sizeof(Word)) > sizeof(vm->ram)) {
    vm->flags.accessviolation = TRUE;
    vm->flags.running = FALSE;
    return;
  }

  *((Word *) &(vm->ram[addr])) = htonl(val);
}

Word _ram_read_word (CoalVM * vm, Word addr) { 
  if ((addr + sizeof(Word)) > sizeof(vm->ram)) {
    vm->flags.accessviolation = TRUE;
    vm->flags.running = FALSE;
    return 0;
  }

  return ntohl(*((Word *) &(vm->ram[addr])));
}

/* Program Fetch */

Word _prog_fetch (CoalVM * vm) {
  Word addr, val;

  addr = vm->pf + (vm->pc * sizeof(Word));

  if ((addr + sizeof(Word)) > vm->sf) {
    vm->flags.accessviolation = TRUE;
    vm->flags.stackoverflow = TRUE;
    vm->flags.running = FALSE;
    return 0;
  }

  val = _ram_read_word(vm, addr);

  if (!vm->flags.running) 
    return 0;

  vm->pc += 1;

  return val;
}

/* Stack */

Word _stack_read (CoalVM * vm, Word s_addr) {
  Word abs_addr, val;

  abs_addr = vm->sf + (s_addr * sizeof(Word)); 

  if ((abs_addr + sizeof(Word)) > vm->hf) {
    vm->flags.accessviolation = TRUE;
    vm->flags.stackoverflow = TRUE;
    vm->flags.running = FALSE;
    return 0;
  }

  val = _ram_read_word(vm, abs_addr);

  if (!vm->flags.running) 
    return 0;

  return val;
}

void _stack_write (CoalVM * vm, Word s_addr, Word val) {
  Word abs_addr;
  abs_addr = vm->sf + (s_addr * sizeof(Word)); 

  if ((abs_addr + sizeof(Word)) > vm->hf) {
    vm->flags.accessviolation = TRUE;
    vm->flags.stackoverflow = TRUE;
    vm->flags.running = FALSE;
    return;
  }

  _ram_write_word(vm, abs_addr, val);
}

Word _stack_pop (CoalVM * vm) {
  Word s_addr, val;

  if (!vm->sp) {
    vm->flags.accessviolation = TRUE;
    vm->flags.stackunderflow = TRUE;
    vm->flags.running = FALSE;
    return 0;
  }

  s_addr = vm->sp - 1; 

  val = _stack_read(vm, s_addr);

  if (!vm->flags.running) 
    return 0;

  vm->sp = s_addr;

  return val;
}

void _stack_push (CoalVM * vm, Word val) {
  _stack_write(vm, vm->sp, val);

  if (!vm->flags.running) 
    return;

  vm->sp += 1;
}

Word _stack_peek (CoalVM * vm) {
  Word addr, val;

  if (!vm->sp) {
    vm->flags.accessviolation = TRUE;
    vm->flags.stackunderflow = TRUE;
    vm->flags.running = FALSE;
    return 0;
  }

  addr = vm->sp - 1; 

  val = _stack_read(vm, addr);

  if (!vm->flags.running) 
    return 0;

  return val;
}

/* Interrupt Handles */

/* C/Coal VM API */

#define CAPIBUFFSIZE 256

HandleDecl(_capi_WRITE_handle) {
  Word fldesc, base, len,
    ramcount, buffcount;
  Byte buff[CAPIBUFFSIZE], b;

  fldesc = vm->rx;
  base = vm->ry;
  len = vm->rz;

  if (!len) 
    return;

  ramcount = 0;
  buffcount = 0;

  while (ramcount < len) {
    b = _ram_read_byte(vm, base + ramcount);
    
    if (!vm->flags.running)
      return;

    buff[buffcount] = b;

    ramcount++;
    buffcount++;

    if (buffcount + 1 >= sizeof(buff)) {
      write(fldesc, buff, buffcount);
      buffcount = 0;
    }
  }

  if (buffcount) {
    write(fldesc, buff, buffcount);
  }
}

Handle _capi_handle_table[_CAPI_LEN] = {
  _capi_WRITE_handle
};

HandleDecl(_intr_CAPI_handle) {
  Word intr;

  intr = vm->ra;

  if (intr >= _CAPI_LEN) {
    vm->flags.badinst = TRUE;
    vm->flags.running = FALSE;
    return;
  }

  _capi_handle_table[intr](vm);
}

/* Fecth & Handle */

HandleDecl(_fetch_handle) {
  vm->inst = _prog_fetch(vm);

  if (!vm->flags.running)
    return;

  if (vm->inst >= _INST_LEN) {
    vm->flags.badinst = TRUE;
    vm->flags.running = FALSE;
    return;
  }

  _inst_handle_table[vm->inst](vm);
} 

/* Init */

Bool CoalVM_init (CoalVM * vm, Word p_frame, Word p_len, Word p_start) {
  Word rem, pf, sf, hf, pc;

  /* Program Frame */
  
  pf = p_frame;

  // if ((rem = pf % sizeof(Word)))
  //   pf += sizeof(Word) - rem;

  // if ((pf + sizeof(Word)) > sizeof(vm->ram)) 
  //   return FALSE;
  
  /* Stack Frame */

  sf = pf + (p_len * sizeof(Word));

  if ((rem = sf % sizeof(Word)))
    sf += sizeof(Word) - rem;

  if ((sf + sizeof(Word)) > sizeof(vm->ram)) 
    return FALSE;

  /* Heap Frame */
  
  hf = sf + ((sizeof(vm->ram) - sf) >> 1);

  if ((rem = hf % sizeof(Word)))
    hf += sizeof(Word) - rem;

  if ((hf + (sizeof(Word) * 8)) > sizeof(vm->ram)) 
    return FALSE;
  
  /* Program counter */

  pc = p_start;

  if (pc > p_len)
    return FALSE;
  
  /* Init */

  vm->pf = pf; 
  vm->sf = sf; 
  vm->hf = hf; 

  vm->pc = pc; 
  vm->sp = 0x0;
  vm->bp = 0x0;
  
  vm->inst = INST_NOOP; 

  vm->flags.all = 0;
  vm->flags.running = TRUE;

  return TRUE;
} 

/* Run */

HandleDecl(CoalVM_run) {
  do {
    // CoalVM_stats(vm);
    // getchar();

    if (!vm->flags.intrenable)
      goto do_exec;

    if (vm->flags.intrcapi) {
      _intr_CAPI_handle(vm);
      
      if (!vm->flags.running)
        return;

      /* Some check first ...? */
      vm->flags.intrcapi = FALSE;
    }

    /* Some check first ...? */
    vm->flags.intrenable = FALSE;

    do_exec:
    
    _fetch_handle(vm);

  } while (vm->flags.running);
}

/* Statistics */

HandleDecl(CoalVM_stats) {
  #define _gut_reg(name, val) \
    { \
      printf(#name "\t-> 0x%08X\t-> ", val); \
      _print_bits(val); \
      printf("\n"); \
    }

  printf("\n-- VM Stats --\n\n");

  _gut_reg(ra, vm->ra);
  _gut_reg(rx, vm->rx);
  _gut_reg(ry, vm->ry);
  _gut_reg(rz, vm->rz);
  _gut_reg(pf, vm->pf);
  _gut_reg(sf, vm->sf);
  _gut_reg(hf, vm->hf);
  _gut_reg(pc, vm->pc);
  _gut_reg(sp, vm->sp);
  _gut_reg(bp, vm->bp);
  _gut_reg(inst, vm->inst);
  _gut_reg(flags, vm->flags.all);

  #define _ind_flag(f) \
    printf( \
      "\t%s -> %s\n", \
      vm->flags.f ? \
        "1" : "0", \
      #f \
    )

  _ind_flag(running);
  _ind_flag(zero);
  _ind_flag(carry);
  _ind_flag(sign);
  _ind_flag(overflow);
  _ind_flag(nan);
  _ind_flag(infinity);
  _ind_flag(intrcapi);
  _ind_flag(badinst);
  _ind_flag(haltinst);
  _ind_flag(accessviolation);
  _ind_flag(stackoverflow);
  _ind_flag(stackunderflow);

  printf("-----\n");
}
