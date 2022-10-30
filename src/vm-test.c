#include "./common.h"
#include "./vm.h"
#include "./vm-inst.h"
#include "./vm-capi.h"

int main (int argc, char ** argv) {
  CoalVM vm[1];
  u32 addr, p_frame, p_len;
  u32 fib_addr, l2_addr, l3_addr, main_addr;
  Bool res;

  #define _prog(_c, _w) \
    { \
      _ram_write_word(vm, _c, (_w)); \
      _c += sizeof(Word); \
    }

  #define _bprog(_c, _b) \
    { \
      _ram_write_byte(vm, _c, (_b)); \
      (_c += 1); \
    }

  addr = 0x0;

  /* No Global */

  p_frame = addr;

  /* Fib*/

  fib_addr = (addr - p_frame) >> 2;

  _prog(addr, INST_PUSH); _prog(addr, 0x2);
  _prog(addr, INST_PUSHL); _prog(addr, 0x1);
  _prog(addr, INST_UCOMP); 

  l2_addr = ((addr - p_frame) >> 2) + 8;

  _prog(addr, INST_JUMPNB); _prog(addr, l2_addr); /* L2 */

  /* If param less than 0x2 */
  _prog(addr, INST_PUSHL); _prog(addr, 0x1);
  _prog(addr, INST_POPL); _prog(addr, 0x0);

  l3_addr = ((addr - p_frame) >> 2) + 53;

  _prog(addr, INST_JUMP); _prog(addr, l3_addr); /* L3 */

  /* L2 */

  /* Retval */
  _prog(addr, INST_PUSHS);
  _prog(addr, INST_PUSH); _prog(addr, 0x1);
  _prog(addr, INST_USUM);
  _prog(addr, INST_POPS);  

  /* Params */
  _prog(addr, INST_PUSH); _prog(addr, 0x1);
  _prog(addr, INST_PUSHL); _prog(addr, 0x1);
  _prog(addr, INST_USUB);

  /* Storing Base Ptr */
  _prog(addr, INST_PUSHB); 

  /* Updating Base Ptr */
  _prog(addr, INST_PUSH); _prog(addr, 0x4);
  _prog(addr, INST_PUSHS); 
  _prog(addr, INST_USUB);
  _prog(addr, INST_POPB); 

  /* Program Ptr */
  _prog(addr, INST_PUSH); _prog(addr, 0x3);
  _prog(addr, INST_PUSHP);
  _prog(addr, INST_USUM);

  /* Branching */
  _prog(addr, INST_JUMP); _prog(addr, fib_addr);

  /* Restoring Base Ptr */
  _prog(addr, INST_POPB); 

  /* Discarding Params */
  _prog(addr, INST_POP); 

  /* Don't do anything to retval yet */

  /* Retval */
  _prog(addr, INST_PUSHS);
  _prog(addr, INST_PUSH); _prog(addr, 0x1);
  _prog(addr, INST_USUM);
  _prog(addr, INST_POPS);

  /* Params */
  _prog(addr, INST_PUSH); _prog(addr, 0x2);
  _prog(addr, INST_PUSHL); _prog(addr, 0x1);
  _prog(addr, INST_USUB); 

  /* Storing Base Ptr */
  _prog(addr, INST_PUSHB); 

  /* Updating Base Ptr */
  _prog(addr, INST_PUSH); _prog(addr, 0x4);
  _prog(addr, INST_PUSHS);
  _prog(addr, INST_USUB);
  _prog(addr, INST_POPB);  
        
  /* Program Ptr */
  _prog(addr, INST_PUSH); _prog(addr, 0x3);
  _prog(addr, INST_PUSHP);
  _prog(addr, INST_USUM); 

  /* Branching */
  _prog(addr, INST_JUMP); _prog(addr, fib_addr);

  /* Restoring Base Ptr */
  _prog(addr, INST_POPB);

  /* Discarding Params */
  _prog(addr, INST_POP);  

  /* Preparing retval */
  _prog(addr, INST_USUM);
  _prog(addr, INST_POPL); _prog(addr, 0x0); 

  /* L3 */

  /* Handing over control */
  _prog(addr, INST_POPP); 

  /* Main */

  main_addr = (addr - p_frame) >> 2;

  /* Retval */
  _prog(addr, INST_PUSHS);
  _prog(addr, INST_PUSH); _prog(addr, 0x1);
  _prog(addr, INST_USUM);
  _prog(addr, INST_POPS);  

  /* Params */
  _prog(addr, INST_PUSH); _prog(addr, 0xF);

  /* Storing Base Ptr */
  _prog(addr, INST_PUSHB); 

  /* Updating Base Ptr */
  _prog(addr, INST_PUSH); _prog(addr, 0x4);
  _prog(addr, INST_PUSHS); 
  _prog(addr, INST_USUB);
  _prog(addr, INST_POPB); 

  /* Program Ptr */
  _prog(addr, INST_PUSH); _prog(addr, 0x3);
  _prog(addr, INST_PUSHP);
  _prog(addr, INST_USUM);

  /* Branching */
  _prog(addr, INST_JUMP); _prog(addr, fib_addr);

  /* Restoring Base Ptr */
  _prog(addr, INST_POPB); 

  /* Discarding Params */
  _prog(addr, INST_POP);

  /* Do something with retval */
  _prog(addr, INST_POPA);

  /* End program */

  _prog(addr, INST_HALT); 

  /* Program Length */

  p_len = (addr - p_frame) >> 2;

  /* Init */

  res = CoalVM_init(vm, p_frame, p_len, main_addr);

  if (!res)
    return 1;

  /* Run VM */

  CoalVM_run(vm);

  // CoalVM_stats(vm);
  // getchar();
 
  return vm->ra;
}
