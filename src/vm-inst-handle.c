#include <math.h>

#include "./common.h"
#include "./vm.h"
#include "./vm-inst.h"
#include "./vm-inst-handle.h"

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

  if (!vm->flags.running) {
    return;
  }
} 

HandleDecl(_inst_DUPL_handle) {
  Word val;

  val = _stack_peek(vm);

  if (!vm->flags.running)
    return;

  _stack_push(vm, val);

  if (!vm->flags.running)
    return;
} 

HandleDecl(_inst_PUSHA_handle) { 
  _stack_push(vm, vm->ra);

  if (!vm->flags.running)
    return;
}

HandleDecl(_inst_PUSHB_handle) { 
  _stack_push(vm, vm->rb);

  if (!vm->flags.running)
    return;
}

HandleDecl(_inst_PUSHC_handle) { 
  _stack_push(vm, vm->rc);

  if (!vm->flags.running)
    return;
}

HandleDecl(_inst_PUSHD_handle) { 
  _stack_push(vm, vm->rd);

  if (!vm->flags.running)
    return;
}

HandleDecl(_inst_PUSHP_handle) { 
  _stack_push(vm, vm->pc);

  if (!vm->flags.running)
    return;
}

HandleDecl(_inst_PUSHS_handle) { 
  _stack_push(vm, vm->sp);

  if (!vm->flags.running)
    return;
}

HandleDecl(_inst_PUSHF_handle) { 
  _stack_push(vm, vm->ff);

  if (!vm->flags.running)
    return;
}

/* Stack Popping */

HandleDecl(_inst_POP_handle) {
  _stack_pop(vm);

  if (!vm->flags.running)
    return;
} 

HandleDecl(_inst_POPA_handle) {
  Word val;

  val = _stack_pop(vm);
  
  if (!vm->flags.running)
    return;

  vm->ra = val;
}

HandleDecl(_inst_POPB_handle) {
  Word val;

  val = _stack_pop(vm);
  
  if (!vm->flags.running)
    return;

  vm->rb = val;
}

HandleDecl(_inst_POPC_handle) {
  Word val;

  val = _stack_pop(vm);
  
  if (!vm->flags.running)
    return;

  vm->rc = val;
}

HandleDecl(_inst_POPD_handle) { 
  Word val;

  val = _stack_pop(vm);

  if (!vm->flags.running)
    return;
  
  vm->rd = val;
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

HandleDecl(_inst_POPF_handle) { 
  Word val;

  val = _stack_pop(vm);

  if (!vm->flags.running)
    return;

  vm->pf = val;
}

/* Register Loading */

HandleDecl(_inst_LOADA_handle) {
  Word val;

  val = _prog_fetch(vm);

  if (!vm->flags.running)
    return;

  vm->ra = val;
}

HandleDecl(_inst_LOADB_handle) {
  Word val;

  val = _prog_fetch(vm);

  if (!vm->flags.running)
    return;

  vm->rb = val;
}

HandleDecl(_inst_LOADC_handle) {
  Word val;

  val = _prog_fetch(vm);

  if (!vm->flags.running)
    return;

  vm->rc = val;
}

HandleDecl(_inst_LOADD_handle) {
  Word val;

  val = _prog_fetch(vm);

  if (!vm->flags.running)
    return;

  vm->rd = val;
}

/* Register Moving */

HandleDecl(_inst_MOVAB_handle){
  vm->rb = vm->ra;
}

HandleDecl(_inst_MOVAC_handle){
  vm->rc = vm->ra;
}

HandleDecl(_inst_MOVAD_handle){
  vm->rd = vm->ra;
}

HandleDecl(_inst_MOVBA_handle){
  vm->ra = vm->rb;
}

HandleDecl(_inst_MOVBC_handle){
  vm->rc = vm->rb;
}

HandleDecl(_inst_MOVBD_handle){
  vm->rd = vm->rb;
}

HandleDecl(_inst_MOVCA_handle){
  vm->ra = vm->rc;
}

HandleDecl(_inst_MOVCB_handle){
  vm->rb = vm->rc;
}

HandleDecl(_inst_MOVCD_handle){
  vm->rd = vm->rc;
}

HandleDecl(_inst_MOVDA_handle){
  vm->ra = vm->rd;
}

HandleDecl(_inst_MOVDB_handle){
  vm->rb = vm->rd;
}

HandleDecl(_inst_MOVDC_handle){
  vm->rc = vm->rd;
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

HandleDecl(_inst_JUMPC_handle) {
  Word addr;

  addr = _prog_fetch(vm);

  if (!vm->flags.running)
    return;

  if (vm->flags.carry)
    vm->pc = addr;
}

HandleDecl(_inst_JUMPNC_handle) {
  Word addr;

  addr = _prog_fetch(vm);

  if (!vm->flags.running)
    return;

  if (!vm->flags.carry)
    vm->pc = addr;
}

HandleDecl(_inst_JUMPS_handle) {
  Word addr;

  addr = _prog_fetch(vm);

  if (!vm->flags.running)
    return;

  if (vm->flags.sign)
    vm->pc = addr;
}

HandleDecl(_inst_JUMPNS_handle) {
  Word addr;

  addr = _prog_fetch(vm);

  if (!vm->flags.running)
    return;

  if (!vm->flags.sign)
    vm->pc = addr;
}

HandleDecl(_inst_JUMPO_handle) {
  Word addr;

  addr = _prog_fetch(vm);

  if (!vm->flags.running)
    return;

  if (vm->flags.overflow)
    vm->pc = addr;
}

HandleDecl(_inst_JUMPNO_handle) {
  Word addr;

  addr = _prog_fetch(vm);

  if (!vm->flags.running)
    return;

  if (!vm->flags.overflow)
    vm->pc = addr;
}

/* Register Incr & Decr */

HandleDecl(_inst_INCRA_handle) {
  Word u_src, u_res;
  TwoW l_src, l_res;

  /* Setting */

  u_src = vm->ra;
  l_src = u_src;

  /* Operation */

  l_res = l_src + 1U;
  u_res = (Word) (l_res & TwoW_RHALF);

  /* Flags */

  vm->flags.zero = !u_res;
  vm->flags.carry = !!(l_res & TwoW_LHALF);
  vm->flags.sign = !!signbit(*((Flot *) &u_res));
  vm->flags.overflow = 
    signbit (*((Flot *) &u_res)) != signbit(*((Flot *) &u_src));
  vm->flags.nan = !!isnan(*((Flot *) &u_res));
  vm->flags.infinity = !!isinf(*((Flot *) &u_res));

  /* Storing result */

  vm->ra = u_res;
}

HandleDecl(_inst_INCRB_handle) {
  Word u_src, u_res;
  TwoW l_src, l_res;

  /* Setting */

  u_src = vm->rb;
  l_src = u_src;

  /* Operation */

  l_res = l_src + 1U;
  u_res = (Word) (l_res & TwoW_RHALF);

  /* Flags */

  vm->flags.zero = !u_res;
  vm->flags.carry = !!(l_res & TwoW_LHALF);
  vm->flags.sign = !!signbit(*((Flot *) &u_res));
  vm->flags.overflow = 
    signbit (*((Flot *) &u_res)) != signbit(*((Flot *) &u_src));
  vm->flags.nan = !!isnan(*((Flot *) &u_res));
  vm->flags.infinity = !!isinf(*((Flot *) &u_res));

  /* Storing result */

  vm->rb = u_res;
}

HandleDecl(_inst_INCRC_handle) {
  Word u_src, u_res;
  TwoW l_src, l_res;

  /* Setting */

  u_src = vm->rc;
  l_src = u_src;

  /* Operation */

  l_res = l_src + 1U;
  u_res = (Word) (l_res & TwoW_RHALF);

  /* Flags */

  vm->flags.zero = !u_res;
  vm->flags.carry = !!(l_res & TwoW_LHALF);
  vm->flags.sign = !!signbit(*((Flot *) &u_res));
  vm->flags.overflow = 
    signbit (*((Flot *) &u_res)) != signbit(*((Flot *) &u_src));
  vm->flags.nan = !!isnan(*((Flot *) &u_res));
  vm->flags.infinity = !!isinf(*((Flot *) &u_res));

  /* Storing result */

  vm->rc = u_res;
}

HandleDecl(_inst_INCRD_handle) { 
  Word u_src, u_res;
  TwoW l_src, l_res;

  /* Setting */

  u_src = vm->rd;
  l_src = u_src;

  /* Operation */

  l_res = l_src + 1U;
  u_res = (Word) (l_res & TwoW_RHALF);

  /* Flags */

  vm->flags.zero = !u_res;
  vm->flags.carry = !!(l_res & TwoW_LHALF);
  vm->flags.sign = !!signbit(*((Flot *) &u_res));
  vm->flags.overflow = 
    signbit (*((Flot *) &u_res)) != signbit(*((Flot *) &u_src));
  vm->flags.nan = !!isnan(*((Flot *) &u_res));
  vm->flags.infinity = !!isinf(*((Flot *) &u_res));

  /* Storing result */

  vm->rd = u_res;
}

HandleDecl(_inst_DECRA_handle) {
  Word u_src, u_res;
  TwoW l_src, l_res;

  /* Setting */

  u_src = vm->ra;
  l_src = u_src;

  /* Operation */

  l_res = l_src - 1U;
  u_res = (Word) (l_res & TwoW_RHALF);

  /* Flags */

  vm->flags.zero = !u_res;
  vm->flags.carry = !!(l_res & TwoW_LHALF);
  vm->flags.sign = !!signbit(*((Flot *) &u_res));
  vm->flags.overflow = 
    signbit (*((Flot *) &u_res)) != signbit(*((Flot *) &u_src));
  vm->flags.nan = !!isnan(*((Flot *) &u_res));
  vm->flags.infinity = !!isinf(*((Flot *) &u_res));

  /* Storing result */

  vm->ra = u_res;
}

HandleDecl(_inst_DECRB_handle) {
  Word u_src, u_res;
  TwoW l_src, l_res;

  /* Setting */

  u_src = vm->rb;
  l_src = u_src;

  /* Operation */

  l_res = l_src - 1U;
  u_res = (Word) (l_res & TwoW_RHALF);

  /* Flags */

  vm->flags.zero = !u_res;
  vm->flags.carry = !!(l_res & TwoW_LHALF);
  vm->flags.sign = !!signbit(*((Flot *) &u_res));
  vm->flags.overflow = 
    signbit (*((Flot *) &u_res)) != signbit(*((Flot *) &u_src));
  vm->flags.nan = !!isnan(*((Flot *) &u_res));
  vm->flags.infinity = !!isinf(*((Flot *) &u_res));

  /* Storing result */

  vm->rb = u_res;
}

HandleDecl(_inst_DECRC_handle) {
  Word u_src, u_res;
  TwoW l_src, l_res;

  /* Setting */

  u_src = vm->rc;
  l_src = u_src;

  /* Operation */

  l_res = l_src - 1U;
  u_res = (Word) (l_res & TwoW_RHALF);

  /* Flags */

  vm->flags.zero = !u_res;
  vm->flags.carry = !!(l_res & TwoW_LHALF);
  vm->flags.sign = !!signbit(*((Flot *) &u_res));
  vm->flags.overflow = 
    signbit (*((Flot *) &u_res)) != signbit(*((Flot *) &u_src));
  vm->flags.nan = !!isnan(*((Flot *) &u_res));
  vm->flags.infinity = !!isinf(*((Flot *) &u_res));

  /* Storing result */

  vm->rc = u_res;
}

HandleDecl(_inst_DECRD_handle) {
  Word u_src, u_res;
  TwoW l_src, l_res;

  /* Setting */

  u_src = vm->rd;
  l_src = u_src;

  /* Operation */

  l_res = l_src - 1U;
  u_res = (Word) (l_res & TwoW_RHALF);

  /* Flags */

  vm->flags.zero = !u_res;
  vm->flags.carry = !!(l_res & TwoW_LHALF);
  vm->flags.sign = !!signbit(*((Flot *) &u_res));
  vm->flags.overflow = 
    signbit (*((Flot *) &u_res)) != signbit(*((Flot *) &u_src));
  vm->flags.nan = !!isnan(*((Flot *) &u_res));
  vm->flags.infinity = !!isinf(*((Flot *) &u_res));

  /* Storing result */

  vm->rd = u_res;
}

/* Logic */

HandleDecl(_inst_COMP_handle) {
  Word u_src1, u_src2, u_res;
  TwoW l_src1, l_src2, l_res;

  /* Setting */

  u_src1 = _stack_pop(vm);

  if (!vm->flags.running)
    return;

  u_src2 = _stack_pop(vm);

  if (!vm->flags.running)
    return;

  l_src1 = u_src1;
  l_src2 = u_src2;

  /* Operation */

  l_res = l_src1 - l_src2;
  u_res = (Word) (l_res & TwoW_RHALF);

  /* Flags */

  vm->flags.zero = !u_res;
  vm->flags.carry = !!(l_res & TwoW_LHALF);
  vm->flags.sign = !!signbit(*((Flot *) &u_res));
  vm->flags.overflow = 
    signbit(*((Flot *) &u_res)) != signbit(*((Flot *) &u_src1));
  vm->flags.nan = !!isnan(*((Flot *) &u_res));
  vm->flags.infinity = !!isinf(*((Flot *) &u_res));

  /* No result */
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
  vm->flags.sign = !!signbit(*((Flot *) &u_res));
  vm->flags.overflow = 
    signbit(*((Flot *) &u_res)) != signbit(*((Flot *) &u_src1));
  vm->flags.nan = !!isnan(*((Flot *) &u_res));
  vm->flags.infinity = !!isinf(*((Flot *) &u_res));

  /* Storing result */

  _stack_push(vm, u_res);

  if (!vm->flags.running)
    return;
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
  vm->flags.sign = !!signbit(*((Flot *) &u_res));
  vm->flags.overflow = 
    signbit(*((Flot *) &u_res)) != signbit(*((Flot *) &u_src1));
  vm->flags.nan = !!isnan(*((Flot *) &u_res));
  vm->flags.infinity = !!isinf(*((Flot *) &u_res));

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
  vm->flags.sign = !!signbit(*((Flot *) &u_res));
  vm->flags.overflow = 
    signbit(*((Flot *) &u_res)) != signbit(*((Flot *) &u_src1));
  vm->flags.nan = !!isnan(*((Flot *) &u_res));
  vm->flags.infinity = !!isinf(*((Flot *) &u_res));

  /* Storing result */

  _stack_push(vm, u_res);

  if (!vm->flags.running)
    return;
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
  vm->flags.sign = !!signbit(*((Flot *) &u_res));
  vm->flags.overflow = 
    signbit(*((Flot *) &u_res)) != signbit(*((Flot *) &u_src1));
  vm->flags.nan = !!isnan(*((Flot *) &u_res));
  vm->flags.infinity = !!isinf(*((Flot *) &u_res));

  /* Storing result */

  _stack_push(vm, u_res);

  if (!vm->flags.running)
    return;
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
  vm->flags.sign = !!signbit(*((Flot *) &u_res));
  vm->flags.overflow = 
    signbit(*((Flot *) &u_res)) != signbit(*((Flot *) &u_src));
  vm->flags.nan = !!isnan(*((Flot *) &u_res));
  vm->flags.infinity = !!isinf(*((Flot *) &u_res));

  /* Storing result */

  _stack_push(vm, u_res);

  if (!vm->flags.running)
    return;
}

/* Bit Shifting */

HandleDecl(_inst_SHL_handle) {
  Word u_src, u_res;
  TwoW l_src, l_res;

  /* Setting */

  u_src = _stack_pop(vm);

  if (!vm->flags.running) 
    return;

  l_src = u_src;

  /* Operation */

  l_res = l_src << 1;
  u_res = (Word) (l_res & TwoW_RHALF);
  
  /* Flags */

  vm->flags.zero = !u_res;
  vm->flags.carry = !!(l_res & TwoW_LHALF);
  vm->flags.sign = !!signbit(*((Flot *) &u_res));
  vm->flags.overflow = 
    signbit(*((Flot *) &u_res)) != signbit(*((Flot *) &u_src));
  vm->flags.nan = !!isnan(*((Flot *) &u_res));
  vm->flags.infinity = !!isinf(*((Flot *) &u_res));

  /* Storing result */

  _stack_push(vm, u_res);

  if (!vm->flags.running)
    return;
}

HandleDecl(_inst_SHR_handle) {
  Word u_src, u_res;
  TwoW l_src, l_res;

  /* Setting */

  u_src = _stack_pop(vm);

  if (!vm->flags.running) 
    return;

  l_src = ((TwoW) u_src) << (Word_SIZE * 8);

  /* Operation */

  l_res = l_src >> 1;
  u_res = (Word) (l_res >> (Word_SIZE * 8));
  
  /* Flags */

  vm->flags.zero = !u_res;
  vm->flags.carry = !!(l_res & TwoW_RHALF);
  vm->flags.sign = !!signbit(*((Flot *) &u_res));
  vm->flags.overflow = 
    signbit(*((Flot *) &u_res)) != signbit(*((Flot *) &u_src));
  vm->flags.nan = !!isnan(*((Flot *) &u_res));
  vm->flags.infinity = !!isinf(*((Flot *) &u_res));

  /* Storing result */

  _stack_push(vm, u_res);

  if (!vm->flags.running)
    return;
}

HandleDecl(_inst_RTL_handle) {
  Word u_src, u_res;
  TwoW l_src, l_res;

  /* Setting */

  u_src = _stack_pop(vm);

  if (!vm->flags.running) 
    return;

  l_src = u_src;

  /* Operation */

  l_res = (l_src << 1) | (l_src >> ((Word_SIZE * 8) - 1));
  u_res = (Word) (l_res & TwoW_RHALF);
  
  /* Flags */

  vm->flags.zero = !u_res;
  vm->flags.carry = !!(l_res & TwoW_LHALF);
  vm->flags.sign = !!signbit(*((Flot *) &u_res));
  vm->flags.overflow = 
    signbit(*((Flot *) &u_res)) != signbit(*((Flot *) &u_src));
  vm->flags.nan = !!isnan(*((Flot *) &u_res));
  vm->flags.infinity = !!isinf(*((Flot *) &u_res));

  /* Storing result */

  _stack_push(vm, u_res);

  if (!vm->flags.running)
    return;
}

HandleDecl(_inst_RTR_handle) {
  Word u_src, u_res;
  TwoW l_src, l_res;

  /* Setting */

  u_src = _stack_pop(vm);

  if (!vm->flags.running) 
    return;

  l_src = ((TwoW) u_src) << (Word_SIZE * 8);

  /* Operation */

  l_res = (l_src >> 1) | (l_src << ((Word_SIZE * 8) - 1));
  u_res = (Word) (l_res >> (Word_SIZE * 8));
  
  /* Flags */

  vm->flags.zero = !u_res;
  vm->flags.carry = !!(l_res & TwoW_RHALF);
  vm->flags.sign = !!signbit(*((Flot *) &u_res));
  vm->flags.overflow = 
    signbit(*((Flot *) &u_res)) != signbit(*((Flot *) &u_src));
  vm->flags.nan = !!isnan(*((Flot *) &u_res));
  vm->flags.infinity = !!isinf(*((Flot *) &u_res));

  /* Storing result */

  _stack_push(vm, u_res);

  if (!vm->flags.running)
    return;
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
  _inst_PUSHB_handle,
  _inst_PUSHC_handle,
  _inst_PUSHD_handle,
  _inst_PUSHP_handle,
  _inst_PUSHS_handle,
  _inst_PUSHF_handle,

  /* Stack Popping */

  _inst_POP_handle,
  _inst_POPA_handle,
  _inst_POPB_handle,
  _inst_POPC_handle,
  _inst_POPD_handle,
  _inst_POPP_handle,
  _inst_POPS_handle,
  _inst_POPF_handle,

  /* Register Loading */

  _inst_LOADA_handle,
  _inst_LOADB_handle,
  _inst_LOADC_handle,
  _inst_LOADD_handle,

  /* Register Moving */

  _inst_MOVAB_handle,
  _inst_MOVAC_handle,
  _inst_MOVAD_handle,
  _inst_MOVBA_handle,
  _inst_MOVBC_handle,
  _inst_MOVBD_handle,
  _inst_MOVCA_handle,
  _inst_MOVCB_handle,
  _inst_MOVCD_handle,
  _inst_MOVDA_handle,
  _inst_MOVDB_handle,
  _inst_MOVDC_handle,

  /* Branching */

  _inst_JUMP_handle, 
  _inst_JUMPZ_handle, 
  _inst_JUMPNZ_handle,  
  _inst_JUMPC_handle, 
  _inst_JUMPNC_handle,  
  _inst_JUMPS_handle, 
  _inst_JUMPNS_handle,  
  _inst_JUMPO_handle, 
  _inst_JUMPNO_handle, 
  
  /* Register Incr & Decr */

  _inst_INCRA_handle,
  _inst_INCRB_handle,
  _inst_INCRC_handle,
  _inst_INCRD_handle,
  _inst_DECRA_handle,
  _inst_DECRB_handle,
  _inst_DECRC_handle,
  _inst_DECRD_handle,

  /* Logic */

  _inst_COMP_handle, 
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

/* Arithmetics */

// Bool _arith_handle(CoalVM * vm) {
//   Any first, second, result;

//   first.u = vm->ra;
//   second.u = vm->rb;

//   switch (vm->inst) {
//     case INST_BMUL:   
//       result.u = ((u32) first.b) * ((u32) second.b);
//       break;
//     case INST_BDIV:  
//       result.u = ((u32) first.b) / ((u32) second.b); 
//       break;
//     case INST_BSUM:  
//       result.u = ((u32) first.b) + ((u32) second.b); 
//       break;
//     case INST_BSUB: 
//       result.u = ((u32) first.b) - ((u32) second.b); 
//       break;
    
//     case INST_CMUL:  
//       result.i = ((i32) first.c) * ((i32) second.c);
//       break;
//     case INST_CDIV:  
//       result.i = ((i32) first.c) / ((i32) second.c); 
//       break;
//     case INST_CSUM:  
//       result.i = ((i32) first.c) + ((i32) second.c); 
//       break;
//     case INST_CSUB:  
//       result.i = ((i32) first.c) - ((i32) second.c); 
//       break;
    
//     case INST_UMUL:  
//       result.l = ((u64) first.u) * ((u64) second.u);
//       break;
//     case INST_UDIV:  
//       result.l = ((u64) first.u) / ((u64) second.u); 
//       break;
//     case INST_USUM:  
//       result.l = ((u64) first.u) + ((u64) second.u); 
//       break;
//     case INST_USUB:  
//       result.l = ((u64) first.u) - ((u64) second.u); 
//       break;
    
//     case INST_IMUL:  
//       result.s = ((i64) first.i) * ((i64) second.i);
//       break;
//     case INST_IDIV:  
//       result.s = ((i64) first.i) / ((i64) second.i); 
//       break;
//     case INST_ISUM:  
//       result.s = ((i64) first.i) + ((i64) second.i); 
//       break;
//     case INST_ISUB:  
//       result.s = ((i64) first.i) - ((i64) second.i); 
//       break;
    
//     case INST_FMUL: 
//       result.f = first.f * second.f; 
//       break;
//     case INST_FDIV:  
//       result.f = first.f / second.f; 
//       break;
//     case INST_FSUM:  
//       result.f = first.f + second.f; 
//       break;
//     case INST_FSUB:  
//       result.f = first.f - second.f; 
//       break;
    
//     default:
//       return FALSE;
//   }

//   /* Carry & Zero Check */

//   switch (vm->inst) {
//     case INST_BMUL: case INST_BDIV:
//     case INST_BSUM: case INST_BSUB:
//       if (result.u & ~((u32) 0xFFU))
//         _flags_include(vm, FLAG_CARRY);
//       else
//         _flags_exclude(vm, FLAG_CARRY);

//       result.b = result.u;

//       if (result.b == 0) _flags_include(vm, FLAG_ZERO);
//       else _flags_exclude(vm, FLAG_ZERO);

//       break;

//     case INST_CMUL: case INST_CDIV:  
//     case INST_CSUM: case INST_CSUB:  
//       if (result.u & ~((u32) 0x800000FFU))
//         _flags_include(vm, FLAG_CARRY);
//       else 
//         _flags_exclude(vm, FLAG_CARRY);

//       result.c = result.i;

//       if (result.c == 0) _flags_include(vm, FLAG_ZERO);
//       else _flags_exclude(vm, FLAG_ZERO);

//       break;
    
//     case INST_UMUL: case INST_UDIV:  
//     case INST_USUM: case INST_USUB:
//       if (result.l & ~((u64) 0xFFFFFFFFU)) 
//         _flags_include(vm, FLAG_CARRY);
//       else 
//         _flags_exclude(vm, FLAG_CARRY);

//       result.u = result.l;

//       if (result.u == 0) _flags_include(vm, FLAG_ZERO);
//       else _flags_exclude(vm, FLAG_ZERO);

//       break;
    
//     case INST_IMUL: case INST_IDIV:  
//     case INST_ISUM: case INST_ISUB:  
//       if (result.l & ~((u64) 0x80000000FFFFFFFFU)) 
//         _flags_include(vm, FLAG_CARRY);
//       else 
//         _flags_exclude(vm, FLAG_CARRY);

//       result.i = result.s;

//       if (result.i == 0) _flags_include(vm, FLAG_ZERO);
//       else _flags_exclude(vm, FLAG_ZERO);

//       break;
    
//     case INST_FMUL: case INST_FDIV:  
//     case INST_FSUM: case INST_FSUB:  
//       _flags_exclude(vm, FLAG_CARRY);

//       if (result.f == 0.0) _flags_include(vm, FLAG_ZERO);
//       else _flags_exclude(vm, FLAG_ZERO);

//       break;
//   }

//   /* Sign, Overflow, NAN & INF Check */

//   switch (vm->inst) {
//     case INST_BMUL: case INST_BDIV:
//     case INST_BSUM: case INST_BSUB:
//     case INST_CMUL: case INST_CDIV:  
//     case INST_CSUM: case INST_CSUB: 

//       if (result.b & 0x8U) _flags_include(vm, FLAG_SIGN);
//       else _flags_exclude(vm, FLAG_SIGN);

//       if ((result.b & 0x8U) != (first.b & 0x8U))
//         _flags_include(vm, FLAG_OVERFLOW);
//       else 
//         _flags_exclude(vm, FLAG_OVERFLOW);

//       _flags_exclude(vm, FLAG_NAN);
//       _flags_exclude(vm, FLAG_INFINITY);

//       break;
    
//     case INST_UMUL: case INST_UDIV:  
//     case INST_USUM: case INST_USUB:
//     case INST_IMUL: case INST_IDIV:  
//     case INST_ISUM: case INST_ISUB:  
//     case INST_FMUL: case INST_FDIV:  
//     case INST_FSUM: case INST_FSUB:
      
//       if (signbit(result.f)) _flags_include(vm, FLAG_SIGN);
//       else _flags_exclude(vm, FLAG_SIGN);

//       if (signbit(result.f) != signbit(first.f))
//         _flags_include(vm, FLAG_OVERFLOW);
//       else 
//         _flags_exclude(vm, FLAG_OVERFLOW);

//       if (isnan(result.f)) _flags_include(vm, FLAG_NAN);
//       else _flags_exclude(vm, FLAG_NAN);

//       if (isinf(result.f)) _flags_include(vm, FLAG_INFINITY);
//       else _flags_exclude(vm, FLAG_INFINITY);

//       break;
//   }

//   vm->ra = result.u;

//   return TRUE;
// }

