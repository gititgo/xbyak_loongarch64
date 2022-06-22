/*******************************************************************************
 * Copyright 2019-2022 LOONGSON LIMITED
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *******************************************************************************/
#include <xbyak_loongarch64/xbyak_loongarch64.h>
using namespace Xbyak_loongarch64;
class Generator : public CodeGenerator {
public:
  Generator() {
    Label label_process, label_result;

    L(label_process);
    ld_bu(t0, a0, 0);
    addi_d(a0, a0, 1);
    ld_bu(t1, a1, 0);
    addi_d(a1, a1, 1);

    beq(t0, zero, label_result);
    beq(t1, zero, label_result);
    beq(t0, t1, label_process);

    L(label_result);
    sub_d(v0, t0, t1);
    jirl(zero, ra, 0);
  }
};
int main() {
  Generator gen;
  gen.ready();
  auto f = gen.getCode<int (*)(char*, char*)>();
  char str0[] = "this is a string ";
  char str1[] = "this is a string yyy";
  char str2[] = "asdfghj";
  char str3[] = "asdfghj";
  gen.dump();
  //printf("a0 addr is %p %p\n", str0, str1);
  printf("%s == %s ? %d\n", str0, str1, f(str0, str1));
  printf("%s == %s ? %d\n", str2, str3, f(str2, str3));
}
