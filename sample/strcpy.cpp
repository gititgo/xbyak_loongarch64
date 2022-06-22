#include <xbyak_loongarch64/xbyak_loongarch64.h>
using namespace Xbyak_loongarch64;
class Generator : public CodeGenerator {
public:
  Generator() {
    Label label_process, label_result;
    addi_d(a2,a1,0);
    ld_bu(t0, a0, 0);
    beqz(t0, label_result);
    L(label_process);
    st_b(t0, a1, 0);
    addi_d(a0,a0,1);
    addi_d(a1,a1,1);
    ld_bu(t0, a0, 0);

    bnez(t0, label_process);
    beqz(t0, label_result);

    L(label_result);
    addi_d(v0, a2, 0);
    jirl(zero, ra, 0);
  }
};
int main() {
  Generator gen;
  gen.ready();
  auto f = gen.getCode<int (*)(char*,char*)>();
  char str0[] = "loongarch";
  char str1[1024]={0};
  gen.dump();
  f(str0,str1);
  printf("src:(%s)\ndst:(%s)\n", str0,str1);
}


