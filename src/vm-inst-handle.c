#include <math.h>
#include <stdio.h>

#include "./common.h"
#include "./vm.h"
#include "./vm-inst.h"
#include "./vm-inst-handle.h"

/* Util */

#define LOW_HALF \
  ((DWord) ~((Word) 0x0))
#define HIGH_HALF \
  ~LOW_HALF

/* Inst Handles */

/* Halt */

HandleDecl(_inst_HALT_handle) {
  vm->flags.haltinst = TRUE;
  vm->flags.running = FALSE;
}

/* Stack Pushing */

HandleDecl(_inst_PUSH_handle) {
  Word val;

  val = _prog_fetch(vm);

  if (!vm->flags.running) {
    return;
  }

  _stack_push(vm, val);
} 

HandleDecl(_inst_DUPL_handle) {
  Word val;

  val = _stack_peek(vm);

  if (!vm->flags.running)
    return;

  _stack_push(vm, val);
} 

HandleDecl(_inst_PUSHA_handle) { 
  _stack_push(vm, vm->ra);
}

HandleDecl(_inst_PUSHX_handle) { 
  _stack_push(vm, vm->rx);
}

HandleDecl(_inst_PUSHY_handle) { 
  _stack_push(vm, vm->ry);
}

HandleDecl(_inst_PUSHZ_handle) { 
  _stack_push(vm, vm->rz);
}

HandleDecl(_inst_PUSHP_handle) { 
  _stack_push(vm, vm->pc);
}

HandleDecl(_inst_PUSHS_handle) { 
  _stack_push(vm, vm->sp);
}

HandleDecl(_inst_PUSHB_handle) { 
  _stack_push(vm, vm->bp);
}

HandleDecl(_inst_PUSHL_handle) {
  Word n, val;

  n = _prog_fetch(vm);

  if (!vm->flags.running)
    return;

  /* Check ? */

  val = _stack_read(vm, vm->bp + n);

  if (!vm->flags.running)
    return;

  _stack_push(vm, val);
}

/* Stack Popping */

HandleDecl(_inst_POP_handle) {
  _stack_pop(vm);
} 

HandleDecl(_inst_POPA_handle) {
  Word val;

  val = _stack_pop(vm);
  
  if (!vm->flags.running)
    return;

  vm->ra = val;
}

HandleDecl(_inst_POPX_handle) {
  Word val;

  val = _stack_pop(vm);
  
  if (!vm->flags.running)
    return;

  vm->rx = val;
}

HandleDecl(_inst_POPY_handle) {
  Word val;

  val = _stack_pop(vm);
  
  if (!vm->flags.running)
    return;

  vm->ry = val;
}

HandleDecl(_inst_POPZ_handle) { 
  Word val;

  val = _stack_pop(vm);

  if (!vm->flags.running)
    return;
  
  vm->rz = val;
}

HandleDecl(_inst_POPP_handle) { 
  Word val;

  val = _stack_pop(vm);

  if (!vm->flags.running)
    return;

  vm->pc = val;
}

HandleDecl(_inst_POPS_handle) { 
  Word val;

  val = _stack_pop(vm);

  if (!vm->flags.running)
    return;

  vm->sp = val;
}

HandleDecl(_inst_POPB_handle) { 
  Word val;

  val = _stack_pop(vm);

  if (!vm->flags.running)
    return;

  vm->bp = val;
}

HandleDecl(_inst_POPL_handle) { 
  Word n, val;

  n = _prog_fetch(vm);

  if (!vm->flags.running)
    return;

  val = _stack_pop(vm);

  if (!vm->flags.running)
    return;

  _stack_write(vm, vm->bp + n, val);
}

/* Branching */

HandleDecl(_inst_JUMP_handle) {
  Word addr;
  
  addr = _prog_fetch(vm);

  if (!vm->flags.running)
    return;

  vm->pc = addr;
}

HandleDecl(_inst_JUMPZ_handle) {
  Word addr;

  addr = _prog_fetch(vm);

  if (!vm->flags.running)
    return;

  if (vm->flags.zero)
    vm->pc = addr;
}

HandleDecl(_inst_JUMPNZ_handle) {
  Word addr;

  addr = _prog_fetch(vm);

  if (!vm->flags.running)
    return;

  if (!vm->flags.zero)
    vm->pc = addr;
}

#define _equals(flags) \
  (flags.zero && !flags.carry && !flags.sign)
#define _below(flags) \
  (!flags.zero && flags.carry && flags.sign)
#define _above(flags) \
  (!flags.zero && !flags.carry && !flags.sign)

HandleDecl(_inst_JUMPE_handle) {
  Word addr;

  addr = _prog_fetch(vm);

  if (!vm->flags.running)
    return;

  if (_equals(vm->flags))
    vm->pc = addr; 
}

HandleDecl(_inst_JUMPNE_handle) {
  Word addr;

  addr = _prog_fetch(vm);

  if (!vm->flags.running)
    return;

  if (!_equals(vm->flags))
    vm->pc = addr;
}

HandleDecl(_inst_JUMPB_handle) {
  Word addr;

  addr = _prog_fetch(vm);

  if (!vm->flags.running)
    return;

  if (_below(vm->flags))
    vm->pc = addr;
}

HandleDecl(_inst_JUMPNB_handle) {
  Word addr;

  addr = _prog_fetch(vm);

  if (!vm->flags.running)
    return;

  if (!_below(vm->flags))
    vm->pc = addr;
}

HandleDecl(_inst_JUMPA_handle) {
  Word addr;

  addr = _prog_fetch(vm);

  if (!vm->flags.running)
    return;

  if (_above(vm->flags))
    vm->pc = addr;
}

HandleDecl(_inst_JUMPNA_handle) {
  Word addr;

  addr = _prog_fetch(vm);

  if (!vm->flags.running)
    return;

  if (!_above(vm->flags))
    vm->pc = addr;
}

HandleDecl(_inst_JUMPEB_handle) {
  Word addr;

  addr = _prog_fetch(vm);  

  if (!vm->flags.running)
    return;

  if (_equals(vm->flags) || _below(vm->flags))
    vm->pc = addr;
}

HandleDecl(_inst_JUMPNEB_handle) {
  Word addr;

  addr = _prog_fetch(vm);  

  if (!vm->flags.running)
    return;

  if (!(_equals(vm->flags) || _below(vm->flags)))
    vm->pc = addr;
}

HandleDecl(_inst_JUMPEA_handle) {
  Word addr;

  addr = _prog_fetch(vm);  

  if (!vm->flags.running)
    return;

  if (_equals(vm->flags) || _above(vm->flags))
    vm->pc = addr;
}

HandleDecl(_inst_JUMPNEA_handle) {
  Word addr;

  addr = _prog_fetch(vm);  

  if (!vm->flags.running)
    return;

  if (!(_equals(vm->flags) || _above(vm->flags)))
    vm->pc = addr;
}

/* Register Incr & Decr */

#define _integer_operation(r_type, o_type, flags, optr, opnd_1, opnd_2) \
  ({ \
    r_type r_opnd_1, r_opnd_2, r_res; \
    o_type o_opnd_1, o_opnd_2, o_res; \
    r_opnd_1 = opnd_1; \
    r_opnd_2 = opnd_2; \
    o_opnd_1 = r_opnd_1; \
    o_opnd_2 = r_opnd_2; \
    o_res = o_opnd_1 optr o_opnd_2; \
    r_res = o_res & LOW_HALF; \
    flags.zero = !(r_res); \
    flags.carry = !!(o_res & HIGH_HALF); \
    flags.sign = !!signbit(*((f32 *) &r_res)); \
    flags.overflow = \
      signbit(*((f32 *) &r_res)) != \
      signbit(*((f32 *) &r_opnd_1)); \
    r_res; \
  })

#define _unsigned_integer_operation(flags, optr, opnd_1, opnd_2) \
  _integer_operation(u32, u64, flags, optr, opnd_1, opnd_2)

#define _signed_integer_operation(flags, optr, opnd_1, opnd_2) \
  _integer_operation(i32, i64, flags, optr, opnd_1, opnd_2)

HandleDecl(_inst_INCRA_handle) {
  vm->ra = _unsigned_integer_operation(vm->flags, +, vm->ra, 1U);
}

HandleDecl(_inst_INCRX_handle) {
  vm->rx = _unsigned_integer_operation(vm->flags, +, vm->rx, 1U);
}

HandleDecl(_inst_INCRY_handle) {
  vm->ry = _unsigned_integer_operation(vm->flags, +, vm->ry, 1U);
}

HandleDecl(_inst_INCRZ_handle) { 
  vm->rz = _unsigned_integer_operation(vm->flags, +, vm->rz, 1U);
}

HandleDecl(_inst_DECRA_handle) {
  vm->ra = _unsigned_integer_operation(vm->flags, -, vm->ra, 1U);
}

HandleDecl(_inst_DECRX_handle) {
  vm->rx = _unsigned_integer_operation(vm->flags, -, vm->rx, 1U);
}

HandleDecl(_inst_DECRY_handle) {
  vm->ry = _unsigned_integer_operation(vm->flags, -, vm->ry, 1U);
}

HandleDecl(_inst_DECRZ_handle) { 
  vm->rz = _unsigned_integer_operation(vm->flags, -, vm->rz, 1U);
}

/* Arithmetics */

HandleDecl(_inst_USUM_handle) {
  Word opnd_1, opnd_2, res;

  opnd_1 = _stack_pop(vm);

  if (!vm->flags.running) 
    return;

  opnd_2 = _stack_pop(vm);

  if (!vm->flags.running) 
    return;

  res = opnd_1 + opnd_2;

  _stack_push(vm, res);
} 

HandleDecl(_inst_USUB_handle) {
  Word opnd_1, opnd_2, res;

  opnd_1 = _stack_pop(vm);

  if (!vm->flags.running) 
    return;

  opnd_2 = _stack_pop(vm);

  if (!vm->flags.running) 
    return;

  res = opnd_1 - opnd_2;

  _stack_push(vm, res);
} 

/* Logic */

HandleDecl(_inst_UCOMP_handle) {
  u32 opnd_1, opnd_2;

  /* Setting */

  opnd_1 = _stack_pop(vm);

  if (!vm->flags.running)
    return;

  opnd_2 = _stack_pop(vm);

  if (!vm->flags.running)
    return;

  _unsigned_integer_operation(vm->flags, -, opnd_1, opnd_2);
}

HandleDecl(_inst_ICOMP_handle) {
  /* TODO: Implement */
}

HandleDecl(_inst_FCOMP_handle) {
  /* TODO: Implement */
}

HandleDecl(_inst_AND_handle) {
  Word u_src1, u_src2, u_res;

  /* Setting */

  u_src1 = _stack_pop(vm);

  if (!vm->flags.running)
    return;

  u_src2 = _stack_pop(vm);

  if (!vm->flags.running)
    return;

  /* Operation */

  u_res = u_src1 & u_src2;

  /* Flags */

  vm->flags.zero = !u_res;
  vm->flags.carry = FALSE;
  vm->flags.sign = !!signbit(*((f32 *) &u_res));
  vm->flags.overflow = 
    signbit(*((f32 *) &u_res)) != signbit(*((f32 *) &u_src1));
  vm->flags.nan = !!isnan(*((f32 *) &u_res));
  vm->flags.infinity = !!isinf(*((f32 *) &u_res));

  /* Storing result */

  _stack_push(vm, u_res);
}

HandleDecl(_inst_TEST_handle) {
  Word u_src1, u_src2, u_res;

  /* Setting */

  u_src1 = _stack_pop(vm);

  if (!vm->flags.running)
    return;

  u_src2 = _stack_pop(vm);

  if (!vm->flags.running)
    return;

  /* Operation */

  u_res = u_src1 & u_src2;

  /* Flags */

  vm->flags.zero = !u_res;
  vm->flags.carry = FALSE;
  vm->flags.sign = !!signbit(*((f32 *) &u_res));
  vm->flags.overflow = 
    signbit(*((f32 *) &u_res)) != signbit(*((f32 *) &u_src1));
  vm->flags.nan = !!isnan(*((f32 *) &u_res));
  vm->flags.infinity = !!isinf(*((f32 *) &u_res));

  /* No result */
}

HandleDecl(_inst_XOR_handle) {
  Word u_src1, u_src2, u_res;

  /* Setting */

  u_src1 = _stack_pop(vm);

  if (!vm->flags.running)
    return;

  u_src2 = _stack_pop(vm);

  if (!vm->flags.running)
    return;

  /* Operation */

  u_res = u_src1 ^ u_src2;

  /* Flags */

  vm->flags.zero = !u_res;
  vm->flags.carry = FALSE;
  vm->flags.sign = !!signbit(*((f32 *) &u_res));
  vm->flags.overflow = 
    signbit(*((f32 *) &u_res)) != signbit(*((f32 *) &u_src1));
  vm->flags.nan = !!isnan(*((f32 *) &u_res));
  vm->flags.infinity = !!isinf(*((f32 *) &u_res));

  /* Storing result */

  _stack_push(vm, u_res);

}

HandleDecl(_inst_OR_handle) {
  Word u_src1, u_src2, u_res;

  /* Setting */

  u_src1 = _stack_pop(vm);

  if (!vm->flags.running)
    return;

  u_src2 = _stack_pop(vm);

  if (!vm->flags.running)
    return;

  /* Operation */

  u_res = u_src1 | u_src2;

  /* Flags */

  vm->flags.zero = !u_res;
  vm->flags.carry = FALSE;
  vm->flags.sign = !!signbit(*((f32 *) &u_res));
  vm->flags.overflow = 
    signbit(*((f32 *) &u_res)) != signbit(*((f32 *) &u_src1));
  vm->flags.nan = !!isnan(*((f32 *) &u_res));
  vm->flags.infinity = !!isinf(*((f32 *) &u_res));

  /* Storing result */

  _stack_push(vm, u_res);
}

HandleDecl(_inst_NOT_handle) {
  Word u_src, u_res;

  /* Setting */

  u_src = _stack_pop(vm);

  if (!vm->flags.running)
    return;

  /* Operation */

  u_res = ~u_src;

  /* Flags */

  vm->flags.zero = !u_res;
  vm->flags.carry = FALSE;
  vm->flags.sign = !!signbit(*((f32 *) &u_res));
  vm->flags.overflow = 
    signbit(*((f32 *) &u_res)) != signbit(*((f32 *) &u_src));
  vm->flags.nan = !!isnan(*((f32 *) &u_res));
  vm->flags.infinity = !!isinf(*((f32 *) &u_res));

  /* Storing result */

  _stack_push(vm, u_res);
}

/* Bit Shifting */

HandleDecl(_inst_SHL_handle) {
  Word u_src, u_res;
  DWord l_src, l_res;

  /* Setting */

  u_src = _stack_pop(vm);

  if (!vm->flags.running) 
    return;

  l_src = u_src;

  /* Operation */

  l_res = l_src << 1;
  u_res = (Word) (l_res & LOW_HALF);
  
  /* Flags */

  vm->flags.zero = !u_res;
  vm->flags.carry = !!(l_res & HIGH_HALF);
  vm->flags.sign = !!signbit(*((f32 *) &u_res));
  vm->flags.overflow = 
    signbit(*((f32 *) &u_res)) != signbit(*((f32 *) &u_src));
  vm->flags.nan = !!isnan(*((f32 *) &u_res));
  vm->flags.infinity = !!isinf(*((f32 *) &u_res));

  /* Storing result */

  _stack_push(vm, u_res);
}

HandleDecl(_inst_SHR_handle) {
  Word u_src, u_res;
  DWord l_src, l_res;

  /* Setting */

  u_src = _stack_pop(vm);

  if (!vm->flags.running) 
    return;

  l_src = ((DWord) u_src) << (sizeof(Word) * 8);

  /* Operation */

  l_res = l_src >> 1;
  u_res = (Word) (l_res >> (sizeof(Word) * 8));
  
  /* Flags */

  vm->flags.zero = !u_res;
  vm->flags.carry = !!(l_res & LOW_HALF);
  vm->flags.sign = !!signbit(*((f32 *) &u_res));
  vm->flags.overflow = 
    signbit(*((f32 *) &u_res)) != signbit(*((f32 *) &u_src));
  vm->flags.nan = !!isnan(*((f32 *) &u_res));
  vm->flags.infinity = !!isinf(*((f32 *) &u_res));

  /* Storing result */

  _stack_push(vm, u_res);
}

HandleDecl(_inst_RTL_handle) {
  Word u_src, u_res;
  DWord l_src, l_res;

  /* Setting */

  u_src = _stack_pop(vm);

  if (!vm->flags.running) 
    return;

  l_src = u_src;

  /* Operation */

  l_res = (l_src << 1) | (l_src >> ((sizeof(Word) * 8) - 1));
  u_res = (Word) (l_res & LOW_HALF);
  
  /* Flags */

  vm->flags.zero = !u_res;
  vm->flags.carry = !!(l_res & HIGH_HALF);
  vm->flags.sign = !!signbit(*((f32 *) &u_res));
  vm->flags.overflow = 
    signbit(*((f32 *) &u_res)) != signbit(*((f32 *) &u_src));
  vm->flags.nan = !!isnan(*((f32 *) &u_res));
  vm->flags.infinity = !!isinf(*((f32 *) &u_res));

  /* Storing result */

  _stack_push(vm, u_res);
}

HandleDecl(_inst_RTR_handle) {
  Word u_src, u_res;
  DWord l_src, l_res;

  /* Setting */

  u_src = _stack_pop(vm);

  if (!vm->flags.running) 
    return;

  l_src = ((DWord) u_src) << (sizeof(Word) * 8);

  /* Operation */

  l_res = (l_src >> 1) | (l_src << ((sizeof(Word) * 8) - 1));
  u_res = (Word) (l_res >> (sizeof(Word) * 8));
  
  /* Flags */

  vm->flags.zero = !u_res;
  vm->flags.carry = !!(l_res & LOW_HALF);
  vm->flags.sign = !!signbit(*((f32 *) &u_res));
  vm->flags.overflow = 
    signbit(*((f32 *) &u_res)) != signbit(*((f32 *) &u_src));
  vm->flags.nan = !!isnan(*((f32 *) &u_res));
  vm->flags.infinity = !!isinf(*((f32 *) &u_res));

  /* Storing result */

  _stack_push(vm, u_res);
}

/* CAPI Interrupt */

HandleDecl(_inst_CAPI_handle) {
  vm->flags.intrenable = TRUE;
  vm->flags.intrcapi = TRUE;
}

/* No Operation */

HandleDecl(_inst_NOOP_handle) {
  return;
}

/* Inst Handle Table */

Handle _inst_handle_table[_INST_LEN] = {
  
  /* Halt */

  _inst_HALT_handle,

  /* Stack Pushing */

  _inst_PUSH_handle,
  _inst_DUPL_handle,
  _inst_PUSHA_handle,
  _inst_PUSHX_handle,
  _inst_PUSHY_handle,
  _inst_PUSHX_handle,
  _inst_PUSHP_handle,
  _inst_PUSHS_handle,
  _inst_PUSHB_handle,
  _inst_PUSHL_handle,

  /* Stack Popping */

  _inst_POP_handle,
  _inst_POPA_handle,
  _inst_POPX_handle,
  _inst_POPY_handle,
  _inst_POPZ_handle,
  _inst_POPP_handle,
  _inst_POPS_handle,
  _inst_POPB_handle,
  _inst_POPL_handle,

  /* Branching */

  _inst_JUMP_handle, 
  _inst_JUMPZ_handle, 
  _inst_JUMPNZ_handle, 
  _inst_JUMPE_handle,
  _inst_JUMPNE_handle,
  _inst_JUMPB_handle,
  _inst_JUMPNB_handle,
  _inst_JUMPA_handle,
  _inst_JUMPNA_handle,
  _inst_JUMPEB_handle,
  _inst_JUMPNEB_handle,
  _inst_JUMPEA_handle,
  _inst_JUMPNEA_handle,
  
  /* Register Incr & Decr */

  _inst_INCRA_handle,
  _inst_INCRX_handle,
  _inst_INCRY_handle,
  _inst_INCRZ_handle,
  _inst_DECRA_handle,
  _inst_DECRX_handle,
  _inst_DECRY_handle,
  _inst_DECRZ_handle,

  /* Arithmetics */

  _inst_USUM_handle,
  _inst_USUB_handle,

  /* Logic */

  _inst_UCOMP_handle, 
  _inst_ICOMP_handle, 
  _inst_FCOMP_handle, 
  _inst_AND_handle, 
  _inst_TEST_handle, 
  _inst_XOR_handle, 
  _inst_OR_handle, 
  _inst_NOT_handle, 

  /* Bit Shifting */

  _inst_SHL_handle, 
  _inst_SHR_handle, 
  _inst_RTL_handle, 
  _inst_RTR_handle, 

  /* Interrupts */

  _inst_CAPI_handle, 

  /* No Operation */

  _inst_NOOP_handle

};

/* Type Casting */

// Bool _typecast_handle(CoalVM * vm) {
//   Any a;

//   a.u = vm->ra;

//   switch (vm->inst) { 
//     case INST_C2B:
//       a.b = a.c;
//       a.u &= 0xFFU;
//       break; 
//     case INST_U2B:
//       a.b = a.u;
//       a.u &= 0xFFU;
//       break; 
//     case INST_I2B:
//       a.b = a.i;
//       a.u &= 0xFFU;
//       break; 
//     case INST_F2B:
//       a.b = a.f;
//       a.u &= 0xFFU;
//       break;
//     case INST_B2C:
//       a.c = a.b;
//       a.u &= 0xFFU;
//       break; 
//     case INST_U2C:
//       a.c = a.u;
//       a.u &= 0xFFU;
//       break; 
//     case INST_I2C:
//       a.c = a.i;
//       a.u &= 0xFFU;
//       break; 
//     case INST_F2C:
//       a.c = a.f;
//       a.u &= 0xFFU;
//       break; 
//     case INST_B2U:
//       a.u = a.b;
//       break; 
//     case INST_C2U:
//       a.u = a.c;
//       break; 
//     case INST_I2U:
//       a.u = a.i;
//       break; 
//     case INST_F2U:
//       a.u = a.f;
//       break; 
//     case INST_B2I:
//       a.i = a.b;
//       break; 
//     case INST_C2I:
//       a.i = a.c;
//       break; 
//     case INST_U2I:
//       a.i = a.u;
//       break; 
//     case INST_F2I:
//       a.i = a.f;
//       break; 
//     case INST_B2F:
//       a.f = a.b;
//       break; 
//     case INST_C2F:
//       a.f = a.c;
//       break; 
//     case INST_U2F:
//       a.f = a.u;
//       break; 
//     case INST_I2F:
//       a.f = a.i;
//       break; 
//     default:
//       return FALSE;
//   }

//   vm->ra = a.u;

//   return TRUE;
// }
