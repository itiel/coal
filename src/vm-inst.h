#ifndef _VM_INST_H_
#define _VM_INST_H_

/* Instruction Set */

enum CoalVM_InstSet {

  /*
    Arith, logic, incr & decr, bitshift 
    and typecast inst affect arith & 
    logic flags.

    Unless stated otherwise, arith, 
    logic, bitshift and typecast inst 
    operators are popped from the stack 
    and the result is pushed back on.

    Data types:
      B: Byte
      C: Char
      U: Unsi
      I: Inte
      F: Flot
      D: Doub
      W: Word
      T: TwoW

    Source and destination:
      I, (nothing): Immediate - From next word
      R: Addr Reg - From/into addr in RD 
      A: Accum Reg - From/into RA 
      D: Addr Reg - From/into RD 
      P: Prog Count - From/into PC
      V: LVAR - From/into local vars
      S: Stack - From/onto stack
      T: Data - From/into data 
  */
 
  /* Halt */

  INST_HALT, /* Completely stop */

  /* Stack Pushing */

  INST_PUSH, /* Push onto stack (Immediate) */
  INST_DUPL, /* Push duplicate of last item  */
  
  INST_PUSHA, /* Push RA */
  INST_PUSHB, /* Push RB */
  INST_PUSHC, /* Push RC */
  INST_PUSHD, /* Push RD */
  INST_PUSHP, /* Push PC */
  INST_PUSHS, /* Push SP */
  INST_PUSHF, /* Push FF */

  /* Stack Popping */

  INST_POP,  /* Pop from stack into void */

  INST_POPA, /* Pop into RA */
  INST_POPB, /* Pop into RB */
  INST_POPC, /* Pop into RC */
  INST_POPD, /* Pop into RD */
  INST_POPP, /* Pop into PC */
  INST_POPS, /* Pop into SP */
  INST_POPF, /* Pop into FF */

  /* Register Loading */

  INST_LOADA, /* Load into RA (Immediate) */
  INST_LOADB, /* Load into RB (Immediate) */
  INST_LOADC, /* Load into RC (Immediate) */
  INST_LOADD, /* Load into RD (Immediate) */

  /* Register Moving */

  INST_MOVAB, /* Copy RA into RB*/
  INST_MOVAC, /* Copy RA into RC*/
  INST_MOVAD, /* Copy RA into RD*/

  INST_MOVBA, /* Copy RB into RA*/
  INST_MOVBC, /* Copy RB into RC*/
  INST_MOVBD, /* Copy RB into RD*/
  
  INST_MOVCA, /* Copy RC into RA*/
  INST_MOVCB, /* Copy RC into RB*/
  INST_MOVCD, /* Copy RC into RD*/
  
  INST_MOVDA, /* Copy RD into RA*/
  INST_MOVDB, /* Copy RD into RB*/
  INST_MOVDC, /* Copy RD into RC*/

  /* Branching */

  INST_JUMP,  /* Load into PC (immediate) */

  INST_JUMPZ,   /* JUMP if ZF */
  INST_JUMPNZ,  /* JUMP if !ZF */
  
  INST_JUMPC,   /* JUMP if CF */
  INST_JUMPNC,  /* JUMP if !CF */
  
  INST_JUMPS,   /* JUMP if SF */
  INST_JUMPNS,  /* JUMP if !SF */
  
  INST_JUMPO,   /* JUMP if OF */
  INST_JUMPNO,  /* JUMP if !OF */
  
  // INST_JUMPP,   /* JUMP if PF */
  // INST_JUMPNP,  /* JUMP if !PF */
  
  /*
    Combined conditions

     Cnd | Z | C | S
    -----+---+---+---
      =  | 1 | 0 | 0
      <  | 0 | 1 | 1
      >  | 0 | 0 | 0
  */

  // INST_JUMPE,   /* JUMP if ZF & !CF & !SF */
  // INST_JUMPNE,  /* JUMP if !(ZF & !CF & !SF) */

  // INST_JUMPL,   /* JUMP if !ZF & CF & SF */
  // INST_JUMPNL,  /* JUMP if !(ZF & !CF & !SF) */
  
  // INST_JUMPG,   /* JUMP if !ZF & !CF & !SF */
  // INST_JUMPNG,  /* JUMP if !(!ZF & !CF & !SF) */
  
  /* Type Casting */

  // INST_C2B, /* Cast Char to Byte */ 
  // INST_C2U, /* Cast Char to Unsi */ 
  // INST_C2I, /* Cast Char to Inte */ 
  // INST_C2F, /* Cast Char to Flot */ 

  // INST_B2C, /* Cast Byte to Char */ 
  // INST_B2U, /* Cast Byte to Unsi */ 
  // INST_B2I, /* Cast Byte to Inte */ 
  // INST_B2F, /* Cast Byte to Flot */ 

  // INST_U2C, /* Cast Unsi to Char */ 
  // INST_U2B, /* Cast Unsi to Byte */ 
  // INST_U2I, /* Cast Unsi to Inte */ 
  // INST_U2F, /* Cast Unsi to Flot */ 

  // INST_I2C, /* Cast Inte to Char */ 
  // INST_I2B, /* Cast Inte to Byte */ 
  // INST_I2U, /* Cast Inte to Unsi */ 
  // INST_I2F, /* Cast Inte to Flot */ 

  // INST_F2C, /* Cast Flot to Char */ 
  // INST_F2B, /* Cast Flot to Byte */
  // INST_F2U, /* Cast Flot to Unsi */ 
  // INST_F2I, /* Cast Flot to Inte */ 

  /* Register Incr & Decr */

  INST_INCRA, /* Increment RA by 1 */
  INST_INCRB, /* Increment RB by 1 */
  INST_INCRC, /* Increment RC by 1 */
  INST_INCRD, /* Increment RD by 1 */

  INST_DECRA, /* Decrement RA by 1 */
  INST_DECRB, /* Decrement RD by 1 */
  INST_DECRC, /* Decrement RA by 1 */
  INST_DECRD, /* Decrement RD by 1 */

  /* Arithmetics */

  // INST_BMUL, /* Multiply (Byte) */  
  // INST_BDIV, /* Divide (Byte) */ 
  // INST_BSUM, /* Add (Byte) */ 
  // INST_BSUB, /* Subtract (Byte) */ 
 
  // INST_CMUL, /* Multiply (Char) */ 
  // INST_CDIV, /* Divide (Char) */ 
  // INST_CSUM, /* Add (Char) */ 
  // INST_CSUB, /* Subtract (Char) */ 
 
  // INST_UMUL, /* Multiply (Unsi) */ 
  // INST_UDIV, /* Divide (Unsi) */ 
  // INST_USUM, /* Add (Unsi) */ 
  // INST_USUB, /* Subtract (Unsi) */ 
 
  // INST_IMUL, /* Multiply (Inte) */ 
  // INST_IDIV, /* Divide (Inte) */ 
  // INST_ISUM, /* Add (Inte) */ 
  // INST_ISUB, /* Subtract (Inte) */ 

  // INST_FMUL, /* Multiply (Flot) */ 
  // INST_FDIV, /* Divide (Flot) */ 
  // INST_FSUM, /* Add (Flot) */ 
  // INST_FSUB, /* Subtract (Flot) */ 

  /* Logic */

  INST_COMP, /* USUB (with no result) */
  INST_AND,  /* Logical AND */
  INST_TEST, /* Logical AND (with no result) */
  INST_XOR,  /* Exclusive OR */
  INST_OR,   /* Logical OR */
  INST_NOT,  /* Logical NOT */

  /* Bit Shifting */

  INST_SHL, /* Shift bits left 1 position */
  INST_SHR, /* Shift bits right 1 position */

  INST_RTL, /* Rotate bits left 1 position */
  INST_RTR, /* Rotate bits right 1 position */

  /* Interrupts */

  INST_CAPI, /* C/Coal VM API Call */

  /* No Operation */

  INST_NOOP, /* Do absolutely nothing */

  /* Other */

  _INST_LEN /* Inst Handle Table Length */

  /*
    TO-DO:
    Implement interrupt instructions.
  */

};

#endif /* #ifndef _VM_INST_H_ */
