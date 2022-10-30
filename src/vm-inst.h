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
      B: u8 | Byte
      C: i8
      U: u32
      I: i32
      F: f32
      D: f64
      W: Word
      T: DWord

    Source/destination:
      (none):   Immediate - From next word
      A:        Accumulator - From/into RA 
      X, Y, Z:  Gral Purpose - From/into RX|RY|RZ 
      P:        Prog Count - From/into PC 
      S:        Stack - From/onto stack | 
                Stack Pointer - From/into SP
      B:        Base Pointer - From/into BP 
      L:        Local Var - From/into LVar N
      I:        Stack Item - From/into Item N

    Conditional branching is based on flags

    +------------+-----------+
    |            |   Flags   |
    | Condition  +---+---+---+
    |            | Z | C | S |
    |------------+---+---+---+
    | = (Equals) | 1 | 0 | 0 |
    | < (Below)  | 0 | 1 | 1 |
    | > (Above)  | 0 | 0 | 0 |
    +------------+---+---+---+
  */
 
  /* Halt */

  INST_HALT, /* Completely stop */

  /* Stack Pushing */

  INST_PUSH, /* Push onto stack (Immediate) */
  INST_DUPL, /* Push duplicate of last item  */
  
  INST_PUSHA, /* Push RA */
  INST_PUSHX, /* Push RX */
  INST_PUSHY, /* Push RY */
  INST_PUSHZ, /* Push RZ */
  INST_PUSHP, /* Push PC */
  INST_PUSHS, /* Push SP */
  INST_PUSHB, /* Push BP */
  INST_PUSHL, /* Push LVar N (or SItem BP + N) */
  // INST_PUSHI, /* Push Stack Item N */

  /* Stack Popping */

  INST_POP,  /* Pop from stack into void */

  INST_POPA, /* Pop into RA */
  INST_POPX, /* Pop into RX */
  INST_POPY, /* Pop into RY */
  INST_POPZ, /* Pop into RZ */
  INST_POPP, /* Pop into PC */
  INST_POPS, /* Pop into SP */
  INST_POPB, /* Pop into BP */
  INST_POPL, /* Pop into LVar N (or SItem BP + N) */
  // INST_POPI, /* Pop into Stack Item N */

  /* Branching */

  INST_JUMP,  /* Load into PC (immediate) */

  INST_JUMPZ,  /* JUMP if Zero */
  INST_JUMPNZ, /* JUMP if !Zero */

  INST_JUMPE,  /* JUMP if Equals */
  INST_JUMPNE, /* JUMP if !Equals */

  INST_JUMPB,  /* JUMP if Below */
  INST_JUMPNB, /* JUMP if !Below */
  
  INST_JUMPA,  /* JUMP if Above */
  INST_JUMPNA, /* JUMP if !Above */

  INST_JUMPEB,  /* JUMP if Equals or Below */
  INST_JUMPNEB, /* JUMP if !(Equals or Below) */

  INST_JUMPEA,  /* JUMP if Equals or Above */
  INST_JUMPNEA, /* JUMP if !(Equals or Above) */
  
  /* Type Casting */

  // INST_C2B, /* Cast i8 to u8 */ 
  // INST_C2U, /* Cast i8 to u32 */ 
  // INST_C2I, /* Cast i8 to i32 */ 
  // INST_C2F, /* Cast i8 to f32 */ 

  // INST_B2C, /* Cast u8 to i8 */ 
  // INST_B2U, /* Cast u8 to u32 */ 
  // INST_B2I, /* Cast u8 to i32 */ 
  // INST_B2F, /* Cast u8 to f32 */ 

  // INST_U2C, /* Cast u32 to i8 */ 
  // INST_U2B, /* Cast u32 to u8 */ 
  // INST_U2I, /* Cast u32 to i32 */ 
  // INST_U2F, /* Cast u32 to f32 */ 

  // INST_I2C, /* Cast i32 to i8 */ 
  // INST_I2B, /* Cast i32 to u8 */ 
  // INST_I2U, /* Cast i32 to u32 */ 
  // INST_I2F, /* Cast i32 to f32 */ 

  // INST_F2C, /* Cast f32 to i8 */ 
  // INST_F2B, /* Cast f32 to u8 */
  // INST_F2U, /* Cast f32 to u32 */ 
  // INST_F2I, /* Cast f32 to i32 */ 

  /* Register Incr & Decr */

  INST_INCRA, /* Increment RA by 1 */
  INST_INCRX, /* Increment RX by 1 */
  INST_INCRY, /* Increment RY by 1 */
  INST_INCRZ, /* Increment RZ by 1 */

  INST_DECRA, /* Decrement RA by 1 */
  INST_DECRX, /* Decrement RX by 1 */
  INST_DECRY, /* Decrement RY by 1 */
  INST_DECRZ, /* Decrement RZ by 1 */

  /* Arithmetics */

  // INST_BMUL, /* Multiply (u8) */  
  // INST_BDIV, /* Divide (u8) */ 
  // INST_BSUM, /* Add (u8) */ 
  // INST_BSUB, /* Subtract (u8) */ 
 
  // INST_CMUL, /* Multiply (i8) */ 
  // INST_CDIV, /* Divide (i8) */ 
  // INST_CSUM, /* Add (i8) */ 
  // INST_CSUB, /* Subtract (i8) */ 
 
  // INST_UMUL, /* Multiply (u32) */ 
  // INST_UDIV, /* Divide (u32) */ 
  INST_USUM, /* Add (u32) */ 
  INST_USUB, /* Subtract (u32) */ 
 
  // INST_IMUL, /* Multiply (i32) */ 
  // INST_IDIV, /* Divide (i32) */ 
  // INST_ISUM, /* Add (i32) */ 
  // INST_ISUB, /* Subtract (i32) */ 

  // INST_FMUL, /* Multiply (f32) */ 
  // INST_FDIV, /* Divide (f32) */ 
  // INST_FSUM, /* Add (f32) */ 
  // INST_FSUB, /* Subtract (f32) */ 

  /* Logic */

  INST_UCOMP, /* USUB (with no result) */
  INST_ICOMP, /* ISUB (with no result) */
  INST_FCOMP, /* f32 comparison */
  
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
