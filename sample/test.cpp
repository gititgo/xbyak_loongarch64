#include <xbyak_loongarch64/xbyak_loongarch64.h>
using namespace Xbyak_loongarch64;
class Generator : public CodeGenerator {
public:
  Generator() {
    Label label_result1,label_result2;
    ld_bu(t0, a0, 0);
    //addi_d(a0, a0, 1);
    beq(t0, zero, label_result2);
    //addi_d(v0,t0,0);

    L(label_result1);   //exist
    addi_d(v0,zero,1);
    jirl(zero, ra, 0);
    L(label_result2);   //not exist
    addi_d(v0, zero, -1);
    jirl(zero, ra, 0);
  }
};
int main() {
  Generator gen;
  gen.ready();
  auto f = gen.getCode<int (*)(char*)>();
  char str0[] = "";
  gen.dump();
  //printf("a0 addr is %p %p\n", str0, str1);
  printf("index:%d\n", f(str0));
}
