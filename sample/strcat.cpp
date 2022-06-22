#include <xbyak_loongarch64/xbyak_loongarch64.h>
using namespace Xbyak_loongarch64;
class Generator : public CodeGenerator {
public:
  Generator() {
    Label label_process1, label_process2, label_result;
    addi_d(v0, a0, 0);
    ld_bu(t0,a0,0);
    beq(t0, zero, label_process2);
    L(label_process1);
    addi_d(a0,a0,1);
    ld_bu(t0,a0,0);
    beq(t0, zero, label_process2);
    bnez(t0, label_process1);

    L(label_process2);
    ld_bu(t0, a1, 0);
    st_b(t0, a0, 0);
    addi_d(a0,a0,1);
    addi_d(a1,a1,1);
    beq(t0, zero, label_result);
    bnez(t0, label_process2);

    L(label_result);
    jirl(zero, ra, 0);

  }
};
int main() {
    Generator gen;
    gen.ready();
    auto f = gen.getCode<int (*)(char*,char*)>();
    char str0[] = "loongarch is ";
    char str1[] = "the best";
    gen.dump();
    f(str0,str1);
    printf("all:(%s)\n", str0);
}
