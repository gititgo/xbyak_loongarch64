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
    //const auto &pPutchar = x19;
    //const auto &pGetchar = x20;
    //const auto &stack = x21;
    const auto &pPutchar = s0;
    const auto &pGetchar = s1;
    const auto &stack = s2;
    const int saveSize = 48;
    //stp(x29, x30, pre_ptr(sp, -saveSize));
    addi_d(sp, sp, -saveSize);
    st_d(fp, sp, saveSize);
    st_d(ra, sp, saveSize - 8);
    //stp(pPutchar, pGetchar, ptr(sp, 16));
    st_d(pPutchar, sp, 16);
    st_d(pGetchar, sp, 16 - 8);
    //str(stack, ptr(sp, 16 + 16));
    st_d(stack, sp, 16 + 16);
    //mov(pPutchar, x0);
    add_d(pPutchar, a0, zero);
    //mov(pGetchar, x1);
    add_d(pGetchar, a1, zero);
    //mov(stack, x2);
    add_d(stack, a2, zero);

    std::stack<Label> labelF, labelB;
    char c;
    while (is >> c) {
      switch (c) {
      case '+':
      case '-': {
        int count = getContinuousChar(is, c);
        //ldr(x0, ptr(stack));
	ld_d(a0, stack, 0);
        // QQQ : not support large count
        if (c == '+') {
          //add(x0, x0, count);
	  addi_d(a0, a0, count);
        } else {
          //sub(x0, x0, count);
	  addi_d(a0, a0, -count);
        }
        //str(x0, ptr(stack));
	st_d(a0, stack, 0);
      } break;
      case '>':
      case '<': {
        int count = getContinuousChar(is, c) * 8;
        if (c == '>') {
          //add(stack, stack, count);
	  addi_d(stack, stack, count);
        } else {
          //sub(stack, stack, count);
	  addi_d(stack, stack, -count);
        }
      } break;
      case '.':
        //ldr(x0, ptr(stack));
	ld_d(a0, stack, 0);
        //blr(pPutchar);
	jirl(ra, pPutchar, 0);
        break;
      case ',':
        //blr(pGetchar);
	jirl(ra, pGetchar, 0);
        //str(x0, ptr(stack));
	st_d(a0, stack, 0);
        break;
      case '[': {
        Label B = L();
        labelB.push(B);
        //ldr(x0, ptr(stack));
	ld_d(a0, stack, 0);
        //cmp(x0, 0);
        Label F;
        //beq(F);
	beqz(a0, F);
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
    ld_d(stack, sp, 16 + 16);
    //ldp(pPutchar, pGetchar, ptr(sp, 16));
    ld_d(pGetchar, sp, 8);
    ld_d(pPutchar, sp, 16);
    //ldp(x29, x30, post_ptr(sp, saveSize));
    ld_d(ra, sp, saveSize - 8);
    ld_d(fp, sp, saveSize);
    addi_d(sp, sp, saveSize);
    //ret();
    jirl(zero, ra, 0);
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
