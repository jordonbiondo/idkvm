#include "vm.h"
#include "greatest.h"
#include <stdbool.h>

GREATEST_MAIN_DEFS();

bool IDK_INST_BIT_V(idk_instruction i, short n) {
  idk_instruction t = 1;
  t <<= sizeof(short) - n - 1;
  return (i & t);
}

TEST set_instruction () {
  idk_instruction i = 0;
  idk_i_set_type(&i, idk_t_add);

  FAIL();
}

SUITE(instructions) {
  RUN_TEST(set_instruction);
}

int main (int argc, char** argv) {
    GREATEST_MAIN_BEGIN();
    RUN_SUITE(instructions);
    GREATEST_MAIN_END();
}
