#include <stdio.h>

#include "./common.h"
#include "./vm.h"
#include "./vm-inst.h"
#include "./vm-capi.h"

int main (int argc, char ** argv) {
  CoalVM vm[1];
  u32 addr, msg_addr, msg_len, p_start, p_len;
  bool res;

  /*
    # ASM

    /import
      "capi.ash"  as capi 
      "std.ash"   as std 
 
    /const
      $msgcnt     "😻\n"

    /data
      @msg
        STR       $msgcnt # String (Null terminated)

    /prog
      @main
        PUSH      STRLN @msg  # Length
        PUSH      @msg        # Base addr
        PUSH      std.$FDOUT  # File desc (stdout)
        PUSH      capi.$WRITE # CAPI Number
        CAPI                  # CAPI Call  
        HALT
  */

  #define _prog(_c, _w) \
    { \
      _ram_write_word(vm, _c, (_w)); \
      _c += Word_SIZE; \
    }

  #define _bprog(_c, _b) \
    { \
      _ram_write_byte(vm, _c, (_b)); \
      _c += 1; \
    }

  #define PROG_FRAME 0x100

  addr = 0x0;

  msg_addr = addr;

  _prog(addr, 0xF09F98BB); // 😻
  _bprog(addr, '\n');
  _bprog(addr, '\0');

  msg_len = addr - 1;

  addr = PROG_FRAME;
  p_len = 0;
 
  _prog(addr, INST_LOADA); _prog(addr, CAPI_WRITE);
  p_len += 2;
  _prog(addr, INST_LOADB); _prog(addr, 0x1);
  p_len += 2;
  _prog(addr, INST_LOADC); _prog(addr, msg_addr);
  p_len += 2;
  _prog(addr, INST_LOADD); _prog(addr, msg_len);
  p_len += 2;
  _prog(addr, INST_CAPI);
  p_len += 1;
  _prog(addr, INST_HALT);
  p_len += 1;

  /* Init */

  p_start = 0;

  res = CoalVM_init(vm, PROG_FRAME, p_len, p_start);

  if (!res)
    return 1;

  /* Run VM */

  CoalVM_run(vm);

  // CoalVM_stats(vm);
  // getchar();
 
  return 0;
}
