#include <fstream>
#include <stack>
#include <stdio.h>
#include <stdlib.h>
#include <xbyak_loongarch64/xbyak_loongarch64.h>

class Brainfuck : public Xbyak_loongarch64::CodeGenerator {
public:
  int getContinuousChar(std::istream &is, char c) {
    int count = 1;
    char p;
    while (is >> p) {
      if (p != c)
        break;
      count++;
    }
    is.unget();
    return count;
  }
  Brainfuck(std::istream &is) : CodeGenerator(100000) {
    // void (*)(void* putchar, void* getchar, int *stack)
    using namespace Xbyak_loongarch64;
    //const auto &pPutchar = a0;
    //const auto &pGetchar = a1;
    const auto &stack = a2;
    const int saveSize = 48;
    int i=1;
    //stp(fp, t8, pre_ptr(sp, -saveSize));
    addi_d(sp, sp, -saveSize);
    st_d(t8,sp,saveSize-8*(i++));
    st_d(fp,sp,saveSize-8*(i++));
    //stp(pPutchar, pGetchar, ptr(sp, 16));
    st_d(a0,sp,saveSize-8*(i++));
    st_d(a1,sp,saveSize-8*(i++));
    //str(stack, ptr(sp, 16 + 16));    --把ptr指针放入stack
    st_d(stack,sp,16+16);
    //mov(a0,t0);
    add_d(a0, t0, zero);
    add_d(a1, t1, zero);
    add_d(a2, t2, zero);

    std::stack<Label> labelF, labelB;
    char c;
    while (is >> c) {
      switch (c) {
      case '+':
      case '-': {
        int count = getContinuousChar(is, c);
        addi_d(t7,zero,count);
        //ldr(t0, ptr(stack));
        ld_d(t0,stack,0);
        // QQQ : not support large count
        if (c == '+') {
          addi_d(t0, t0, count);
        } else {
          sub_d(t0, t0, t7);
        }
        //str(t0, ptr(stack));
        st_d(t0,stack,0);
      } break;
      case '>':
      case '<': {
        int count = getContinuousChar(is, c) * 8;
        addi_d(t7,zero,count);
        if (c == '>') {
          addi_d(stack, stack, count);
        } else {
          sub_d(stack, stack, t7);
        }
      } break;
      case '.':
        //ldr(t0, ptr(stack));
        ld_d(t0,stack,0);
        //blr(pPutchar);
        addi_d(a0,a0,1);
        break;
      case ',':
        //blr(pGetchar);
        addi_d(a1,a1,1);
        //str(t0, ptr(stack));
        st_d(t0,stack,0);
        break;
      case '[': {
        Label B = L();
        labelB.push(B);
        //ldr(t0, ptr(stack));
        ld_d(t0,stack,0);
        //cmp(t0, 0);
        Label F;
        //beq(F);
        beq(t0,zero,F);
        labelF.push(F);
      } break;
      case ']': {
        Label B = labelB.top();
        labelB.pop();
        b(B);
        Label F = labelF.top();
        labelF.pop();
        L(F);
      } break;
      default:
        break;
      }
    }

    //ldr(stack, ptr(sp, 16 + 16));
    ld_d(stack, sp, 16+16);
    //ldp(pPutchar, pGetchar, ptr(sp, 16));
    ld_d(a0, sp, saveSize-8);
    ld_d(a1, sp, saveSize-8*2);
    addi_d(sp, sp, saveSize);
    //ldp(fp, t8, post_ptr(sp, saveSize));
    ld_d(t8, sp, saveSize-8);
    ld_d(fp, sp, saveSize-8*2);
    addi_d(sp, sp, saveSize);
    jirl(zero,ra,0);
  }
};

int main(int argc, char *argv[]) try {
  if (argc != 2) {
    fprintf(stderr, "bf filename.bf\n");
    return 1;
  }
  std::ifstream ifs(argv[1]);
  Brainfuck bf(ifs);
  bf.ready();
  static int64_t stack[128 * 1024];
  auto f = bf.getCode<void (*)(const void *, const void *, int64_t *)>();
#if 0
  FILE *fp = fopen("bf.dump", "wb");
  fwrite((const void*)f, bf.getSize(), 1, fp);
  fclose(fp);
#endif
  f((const void *)putchar, (const void *)getchar, stack);
} catch (std::exception &e) {
  printf("ERR:%s\n", e.what());
  return 1;
}
