#include <stdio.h>
#include <xbyak_loongarch64/xbyak_loongarch64_util.h>

/*
FX700
cpu type=000000000000001e
mmi msa msa2 lsx lasx
*/
int main() {
  using namespace Xbyak_loongarch64::util;
  Cpu cpu;
  printf("cpu type=%016lx\n", (long)cpu.getType());
  if (cpu.has(Cpu::tLSX)) {
    printf("lsx ");
  }
  if (cpu.has(Cpu::tLASX)) {
    printf("lasx ");
  }
  printf("\n");
}
