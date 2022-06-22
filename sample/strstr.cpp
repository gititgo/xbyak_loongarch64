#include <xbyak_loongarch64/xbyak_loongarch64.h>
using namespace Xbyak_loongarch64;
class Generator : public CodeGenerator {
public:
  Generator() {
    Label label_process, label_result1,label_result2;
    addi_d(t8, a0, 0);
    addi_d(t2, a0,0);
    addi_d(t3, a1, 0);

    L(label_process);
    ld_bu(t0, a0, 0);
    addi_d(a0, a0, 1);
    ld_bu(t1, a1, 0);
    addi_d(a1, a1, 1);

    beq(t1, zero, label_result1);
    beq(t0, zero, label_result2);
    beq(t0, t1, label_process);
    addi_d(a1,t3,0);
    addi_d(t2,t2,1);
    addi_d(a0,t2,0);
    b(label_process);

    L(label_result1);   //exist
    sub_d(v0,t2,t8);
    addi_d(v0,v0,1);
    jirl(zero, ra, 0);
    L(label_result2);   //not exist
    addi_d(v0, zero, -1);
    jirl(zero, ra, 0);
  }
};
int main() {
  Generator gen;
  gen.ready();
  auto f = gen.getCode<int (*)(char*, char*)>();
  char str0[] = "thisisastringaaa";
  char str1[] = "str";
  gen.dump();
  //printf("a0 addr is %p %p\n", str0, str1);
  printf("index:%d\n", f(str0, str1));
}
