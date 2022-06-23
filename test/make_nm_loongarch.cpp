/*******************************************************************************
 * Copyright 2021-2022 LOONGSON LIMITED
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
// clang-format off
#include <stdio.h>
#define XBYAK_NO_OP_NAMES
#include "xbyak_loongarch64.h"
#include <cassert>
#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <vector>

#define NUM_OF_ARRAY(x) (sizeof(x) / sizeof(x[0]))

using namespace Xbyak_loongarch64;

const int bitEnd = 64;

uint64_t flagBit = 0;
const uint64_t WREG = 1ULL << flagBit++; /** 除sp/zero外的通用寄存器 */
const uint64_t WREG_AM = 1ULL << flagBit++; /** 除sp/zero外的与WREG不同的通用寄存器，为了AM系列指令测试 */
const uint64_t WSP =  1ULL << flagBit++; /** Test vector is {sp} */
const uint64_t WZERO =  1ULL << flagBit++; /** Test vector is {zero} */
const uint64_t WREG_WSP = WREG | WSP;
const uint64_t WREG_WSP_WZERO = WREG | WSP | WZERO;
const uint64_t REG_CP0 =  1ULL << flagBit++;
const uint64_t REG_FP =  1ULL << flagBit++;

const uint64_t IMM2BIT =  1ULL << flagBit++; /** Test vector is {0, 1, 2, 3} */
const uint64_t IMM3BIT =  1ULL << flagBit++; /** Test vector is {0, 1, 2, 4, 7} */
const uint64_t IMM3BIT_FCC =  1ULL << flagBit++; /** Test vector is {0, 1, 2, 4, 7} */
const uint64_t IMM4BIT =  1ULL << flagBit++; /** Test vector is {0, 1, ..., 8, 15 } */
const uint64_t IMM5BIT =  1ULL << flagBit++; /** Test vector is {0, 1, ..., 16, 31 } */
const uint64_t IMM5BIT_MSBD =  1ULL << flagBit++; /** Test vector is {16, ... ,31 } */
const uint64_t IMM5BIT_LSBD =  1ULL << flagBit++; /** Test vector is {1, ..., 15 } */
const uint64_t IMM6BIT =  1ULL << flagBit++; /** Test vector is {0, 1, ..., 32, 63 } */
const uint64_t IMM6BIT_MSBD =  1ULL << flagBit++; /** Test vector is {32, ... ,63 } */
const uint64_t IMM6BIT_LSBD =  1ULL << flagBit++; /** Test vector is {1, ..., 31 } */
const uint64_t IMM8BIT =  1ULL << flagBit++; /** Test vector is {0, 1, ..., 32, 63, 128, 255 } */
const uint64_t IMM12BIT = 1ULL << flagBit++; /** Test vector is {0, 1, ..., 2048, 4095 } */
const uint64_t IMM12BIT_SIGNED = 1ULL << flagBit++; /** Test vector is {-2048, -1024, ..., 0, 1, ..., 2047 } */
const uint64_t IMM13BIT = 1ULL << flagBit++; /** Test vector is {0, 1, ..., 4096, 8191 } */
const uint64_t IMM14BIT = 1ULL << flagBit++; /** Test vector is {0, 1, ..., 4096, 8191, 16383 } */
const uint64_t IMM14BIT_SIGNED = 1ULL << flagBit++; /** Test vector is {-8192, ..., 0, 1, ..., 4096, 8191 } */
const uint64_t IMM15BIT = 1ULL << flagBit++; /** Test vector is {0, 1, ..., 4096, 1<<12, 1<<13, 1<<14, 1<<15-1 } */
const uint64_t IMM16BIT = 1ULL << flagBit++; /** Test vector is {0, 1, ..., 4096, 1<<13, 1<<14, 1<<15, 1<<16-1 } */
const uint64_t IMM16BIT_SIGNED = 1ULL << flagBit++; /** Test vector is {-1<<15, 1, ..., 4096, 1<<12, 1<<13, 1<<14, 1<<15-1 } */
const uint64_t IMM20BIT = 1ULL << flagBit++; /** Test vector is {0, 1, ..., 4096, 1<<13, 1<<14, ..., 1<<20-1 } */
const uint64_t IMM20BIT_SIGNED = 1ULL << flagBit++; /** Test vector is {-1<<19, 0, 1, ..., 4096, 1<<13, 1<<14, ..., 1<<19-1 } */

const uint64_t BITMASK32 = 1ULL << flagBit++; /** Test vector is {0, 1, ..., 2048, 4095 } */
const uint64_t BITMASK64 = 1ULL << flagBit++; /** Test vector is {0, 1, ..., 4096, 8191 } */

const uint64_t NOPARA = 1ULL << (bitEnd - 1);

#define PUT1(name, nm, op_1)                                                   \
  void put##name() const {                                                     \
    std::vector<std::string> nemonic(nm);                                      \
    std::vector<uint64_t> op1(op_1);                                           \
    put(nemonic, op1, #name, 0);                                               \
  }

#define PUT2(name, nm, op_1, op_2)                                             \
  void put##name() const {                                                     \
    std::vector<std::string> nemonic(nm);                                      \
    std::vector<uint64_t> op1(op_1);                                           \
    std::vector<uint64_t> op2(op_2);                                           \
    put(nemonic, op1, #name, 0);                                               \
    put(nemonic, op2, #name, 1);                                               \
  }

#define PUT3(name, nm, op_1, op_2, op_3)                                       \
  void put##name() const {                                                     \
    std::vector<std::string> nemonic(nm);                                      \
    std::vector<uint64_t> op1(op_1);                                           \
    std::vector<uint64_t> op2(op_2);                                           \
    std::vector<uint64_t> op3(op_3);                                           \
    put(nemonic, op1, #name, 0);                                               \
    put(nemonic, op2, #name, 1);                                               \
    put(nemonic, op3, #name, 2);                                               \
  }

#define PUT4(name, nm, op_1, op_2, op_3, op_4)                                 \
  void put##name() const {                                                     \
    std::vector<std::string> nemonic(nm);                                      \
    std::vector<uint64_t> op1(op_1);                                           \
    std::vector<uint64_t> op2(op_2);                                           \
    std::vector<uint64_t> op3(op_3);                                           \
    std::vector<uint64_t> op4(op_4);                                           \
    put(nemonic, op1, #name, 0);                                               \
    put(nemonic, op2, #name, 1);                                               \
    put(nemonic, op3, #name, 2);                                               \
    put(nemonic, op4, #name, 3);                                               \
  }


#define OPS(...)                                                               \
  { __VA_ARGS__ }
#define NM(...)                                                                \
  { __VA_ARGS__ }


class Test {
  Test(const Test &);
  void operator=(const Test &);
  const bool isXbyak_;
  int funcNum_;

  /** String used as test vector */

  //std::vector<std::string> tv_WREG = {"r0", "r1",  "r2", "r4","r8", "r16", "r31"};
  std::vector<std::string> tv_WREG = {"$t0", "$t2", "$t4", "$t8", "$v0", "$a0", "$a4", "$a6", "$s0", "$s2", "$s6", "$s7", "$ra"};
  std::vector<std::string> tv_WREG_AM = {"$t1", "$t3", "$t5", "$a1", "$a3", "$a5", "$s1", "$s3", "$s5", "$t7"};
  std::vector<std::string> tv_WSP = {"$sp"};
  std::vector<std::string> tv_WZERO = {"$zero"};
  std::vector<std::string> tv_REG_CP0 = {"$0", "$1", "$2", "$4", "$8", "$16", "$31"};
  std::vector<std::string> jtv_REG_CP0 = {"c0", "c1", "c2", "c4", "c8", "c16", "c31"};
  std::vector<std::string> tv_REG_FP = {"$0", "$1", "$2", "$4", "$8", "$16", "$31"};
  std::vector<std::string> jtv_REG_FP = {"f0", "f1", "f2", "f4", "f8", "f16", "f31"};
  std::vector<std::string> tv_IMM2BIT = {"3", "1", "2"};
  std::vector<std::string> tv_IMM3BIT = {"3", "0", "1", "2", "4", "7"};
  std::vector<std::string> jtv_IMM3BIT_FCC = {"3", "0", "1", "2", "4", "7"};
  std::vector<std::string> tv_IMM3BIT_FCC = {"$fcc3", "$fcc0", "$fcc1", "$fcc2", "$fcc4", "$fcc7"};
  std::vector<std::string> tv_IMM4BIT = {"7", "0", "1", "2", "4", "8", "15"};
  std::vector<std::string> tv_IMM5BIT = {"0x1e", "0", "1",  "2",
                                         "4",    "8", "16", "31"};
  std::vector<std::string> tv_IMM5BIT_MSBD = {"0x1e", "30", "21",  "22",
                                         "24",    "18", "16", "31"};
  std::vector<std::string> tv_IMM5BIT_LSBD = {"0xe", "0", "1",  "2",
                                         "4",   "8", "15"};
  std::vector<std::string> tv_IMM6BIT = {"0x39", "0",  "1",  "2", "4",
                                         "8",    "16", "32", "63"};
  std::vector<std::string> tv_IMM6BIT_MSBD = {"0x39", "40",  "51",  "62", "34",
                                         "48",    "56", "32", "63"};
  std::vector<std::string> tv_IMM6BIT_LSBD = {"0x19", "0", "1",  "2", "4",
                                         "8",    "16", "31"};
  std::vector<std::string> tv_IMM8BIT = {"0x39", "0",  "1",  "2", "4",
                                         "8",    "16", "32", "63", "64", "128", "255"};
  std::vector<std::string> tv_IMM12BIT = {
      "0x2aa", "0",   "1",   "2",   "4",    "8",    "16",  "32",
      "64",    "128", "256", "512", "1024", "2048", "4095"};
  std::vector<std::string> tv_IMM12BIT_SIGNED = {
      "-2048", "-1024", "-89", "-800", "0",   "1",   "2",   "4",    "8",    "16",  "32",
      "64",    "128", "256", "512", "1024", "2047", "-1"};
  std::vector<std::string> tv_IMM13BIT = {
      "0x1999", "0",   "1",   "2",   "4",    "8",    "16",   "32",
      "64",     "128", "256", "512", "1024", "2048", "4096", "8191"};
  std::vector<std::string> tv_IMM14BIT = {
      "0x1999", "0",   "1",   "2",   "4",    "8",    "16",   "32",
      "64",     "128", "256", "512", "1024", "2048", "4096", "8192",
      "16383", "10000", "8191", "888", "2500", "3200", "3300"};
  std::vector<std::string> tv_IMM14BIT_SIGNED = {
      "0x100", "0",   "4",    "8",    "16",   "32",
      "64",     "128", "256", "512", "1024", "2048", "4096"};
  std::vector<std::string> tv_IMM15BIT = {
      "0x738e", "0",    "1",     "2",     "4",        "8",    "16",
      "32",     "64",   "128",   "256",   "512",      "1024", "2048",
      "4096",   "8191", "1<<12", "1<<13", "1<<14", "(1<<15)-1"};
  std::vector<std::string> tv_IMM16BIT = {
      "0xe38e", "0",    "1",     "2",     "4",        "8",    "16",
      "32",     "64",   "128",   "256",   "512",      "1024", "2048",
      "4096",   "8191", "1<<14", "1<<15", "(1<<16)-1"};
  std::vector<std::string> tv_IMM16BIT_SIGNED = {
      "0x738e", "0",    "1",     "2",     "4",        "8",    "16",
      "32",     "64",   "128",   "256",   "512",      "1024", "2048",
      "4096",   "8191", "1<<13", "1<<14", "(1<<15)-1", "-(1<<15)",
      "-4096", "-8192", "-1", "-2", "-3", "-4", "-88", "-888", "-1039"};
  std::vector<std::string> tv_IMM20BIT = {
      "0",    "1",     "2",     "4",        "8",    "16",
      "32",     "64",   "128",   "256",   "512",    "1024", "2048",
      "4096",   "8191", "1<<14", "1<<15", "1<<19", "(1<<20)-1"};
  std::vector<std::string> tv_IMM20BIT_SIGNED = {
      "0",    "1",     "2",     "4",        "8",    "16",
      "32",     "64",   "128",   "256",   "512",    "1024", "2048",
      "4096",   "8191", "1<<14", "1<<15", "1<<18", "(1<<19)-1", 
      "-(1<<19)", "-1", "-22", "-1999", "-36666"};
  std::vector<std::string> tv_BITMASK32, jtv_BITMASK32;
  std::vector<std::string> tv_BITMASK64, jtv_BITMASK64;

  std::vector<std::vector<std::string> *> tv_VectorsAs = {&tv_WREG,
                                                          &tv_WREG_AM,
                                                          &tv_WSP,
                                                          &tv_WZERO,
                                                          &tv_REG_CP0,
                                                          &tv_REG_FP,
                                                          &tv_IMM2BIT,
                                                          &tv_IMM3BIT,
                                                          &tv_IMM3BIT_FCC,
                                                          &tv_IMM4BIT,
                                                          &tv_IMM5BIT,
                                                          &tv_IMM5BIT_MSBD,
                                                          &tv_IMM5BIT_LSBD,
                                                          &tv_IMM6BIT,
                                                          &tv_IMM6BIT_MSBD,
                                                          &tv_IMM6BIT_LSBD,
                                                          &tv_IMM8BIT,
                                                          &tv_IMM12BIT,
                                                          &tv_IMM12BIT_SIGNED,
                                                          &tv_IMM13BIT,
                                                          &tv_IMM14BIT,
                                                          &tv_IMM14BIT_SIGNED,
                                                          &tv_IMM15BIT,
                                                          &tv_IMM16BIT,
                                                          &tv_IMM16BIT_SIGNED,
                                                          &tv_IMM20BIT,
                                                          &tv_IMM20BIT_SIGNED,
                                                          &tv_BITMASK32,
                                                          &tv_BITMASK64};

  std::vector<std::vector<std::string> *> tv_VectorsJit = {&tv_WREG,
                                                           &tv_WREG_AM,
                                                           &tv_WSP,
                                                           &tv_WZERO,
                                                           &jtv_REG_CP0,
                                                           &jtv_REG_FP,
                                                           &tv_IMM2BIT,
                                                           &tv_IMM3BIT,
                                                           &jtv_IMM3BIT_FCC,
                                                           &tv_IMM4BIT,
                                                           &tv_IMM5BIT,
                                                           &tv_IMM5BIT_MSBD,
                                                           &tv_IMM5BIT_LSBD,
                                                           &tv_IMM6BIT,
                                                           &tv_IMM6BIT_MSBD,
                                                           &tv_IMM6BIT_LSBD,
                                                           &tv_IMM8BIT,
                                                           &tv_IMM12BIT,
                                                           &tv_IMM12BIT_SIGNED,
                                                           &tv_IMM13BIT,
                                                           &tv_IMM14BIT,
                                                           &tv_IMM14BIT_SIGNED,
                                                           &tv_IMM15BIT,
                                                           &tv_IMM16BIT,
                                                           &tv_IMM16BIT_SIGNED,
                                                           &tv_IMM20BIT,
                                                           &tv_IMM20BIT_SIGNED,
                                                           &jtv_BITMASK32,
                                                           &jtv_BITMASK64};

  std::vector<std::vector<std::string> *> &tv_Vectors = tv_VectorsAs;

  /*
    and_, or_, xor_, not_ => and, or, xor, not
  */
  std::string removeUnderScore(std::string s) const {
    if (!isXbyak_ && s[s.size() - 1] == '_')
      s.resize(s.size() - 1);
    return s;
  }

  std::string replaceDotWithUnderScore(std::string s) const {
    if(!isXbyak_) return s;

    for(uint32_t i=0; i<s.size(); i++)
    {
      if (s[i] == '.')
        s[i] = '_';
    }

    return s;
  }

  std::string removeDollar(std::string s) const {
    if (isXbyak_ && s[0] == '$')
      return s.substr(1);

    return s;
  }

  void put(std::vector<std::string> &n, std::vector<uint64_t> &opSet,
           std::string name, int serial = 0) const {
    if( !isXbyak_ ) {
      std::cout << "#" << name << ":" << serial << std::endl; /** For easy debug */
    }

    for (size_t i = 0; i < n.size(); i++) {
      const std::string nmTmp = removeUnderScore(n[i]);
      const std::string nm = replaceDotWithUnderScore(nmTmp);
      put(nm.c_str(), opSet);
    }
  }

  //  char* getBaseStr(uint64_t op1)
  const char *getBaseStr(uint64_t op1) const {
    for (int i = 0; i < bitEnd; i++) {
      if (op1 & (1ULL << i)) {
        return get(1ULL << i, 0);
      }
    }

    std::cerr << std::endl
              << __FILE__ << ":" << __LINE__ << ", Something wrong. op1=" << op1
              << std::endl;
    assert(0);
    return NULL;
  }

  /** check all op1, op2, op3, op4, op5, op6, op7, op8 */
  void put(const char *nm, std::vector<uint64_t> &ops) const {
    std::vector<std::string> strBase;
    std::string hoge;
    std::string opStr;
    int i, j, k;
    uint jj;
    int num_ops = ops.size();

    for (i = 0; i < num_ops; i++) {
      for (j = 0; j < bitEnd; j++) {
        if (ops[i] & (1ULL << j)) {
          strBase.push_back(getBaseStr(ops[i]));
          break;
        }
      }
    }

    /** No operand exists. */
    if (num_ops == 0) {
      std::cout << nm << " ";

      if (isXbyak_) {
        std::cout << "(); dump();";
      }

      std::cout << std::endl;

      return;
    }

    /** Some operands exist.
        Example:nm = add, num_ops = 2, op1 = Xn, op2 = Xn

        The following 64 patterns are printed.
        Expand for op1
        add(X0, X0); dump();
        add(x1, x0); dump();
        ...
        add(x31, x0); dump();
        Expand for op2
        add(x0, x0); dump();
        add(x0, x1); dump();
        ...
        add(x0, x31); dump();
    */
    for (i = 0; i < num_ops; i++) {
      for (j = 0; j < bitEnd; j++) {
        uint64_t bitpos = 1ULL << j;

        if (!(ops[i] & bitpos))
          continue;

        for (jj = 0; jj < getNum(bitpos); jj++) {
          /** print nemonic */
          std::cout << nm;

          if (isXbyak_) {
            std::cout << "(";
          } else {
            std::cout << " ";
          }

          for (k = 0; k < i; k++) {
            if (k != 0) {
              std::cout << ", ";
            }
            opStr = removeDollar(strBase[k]);
            std::cout << opStr;
          }

          if (i != 0) {
            std::cout << ", ";
          }
          opStr = removeDollar(get(bitpos, jj));
          std::cout << opStr;

          for (k = i + 1; k < num_ops; k++) {
            opStr = removeDollar(strBase[k]);
            std::cout << ", " << opStr;
          }

          if (isXbyak_) {
            std::cout << "); dump();";
          }

          std::cout << std::endl;
        }
      }
    }
  }

  uint64_t getNum(uint64_t type) const {
    if (type == NOPARA) {
      return 0;
    }

    for (int i = 0; i < bitEnd; i++) {
      if ((type >> i) & 0x1) {
        return tv_Vectors[i]->size();
      }
    }

    std::cerr << std::endl
              << __FILE__ << ":" << __LINE__
              << ", Something wrong. type=" << type << std::endl;
    assert(0);
    return 0;
  }

  const char *get(uint64_t type, uint64_t index) const {
    if (type == NOPARA) {
      std::cerr << std::endl
                << __FILE__ << ":" << __LINE__
                << ", Something wrong. type=" << type << " index=" << index
                << std::endl;
      assert(0);
      return NULL;
    }

    for (int i = 0; i < bitEnd; i++) {
      if ((type >> i) & 0x1) {
        return tv_Vectors[i]->at(index).c_str();
      }
    }

    std::cerr << std::endl
              << __FILE__ << ":" << __LINE__
              << ", Something wrong. type=" << type << " index=" << index
              << std::endl;
    assert(0);
    return NULL;
  }

public:
  Test(bool isXbyak) : isXbyak_(isXbyak), funcNum_(1) {
    std::stringstream ss;
    std::stringstream jss;
    ss << std::hex << std::showbase;
    jss << std::hex << std::showbase;

    for (uint64_t onesLen = 1; onesLen <= 31;
         onesLen++) { // Inall-one bit is reserved.
      uint64_t bitmask = 0;

      for (uint64_t i = 1; i <= onesLen; i++) {
        bitmask = (bitmask << 1) + 1;
      }

      for (uint64_t shift = 0; shift <= 32 - onesLen; shift++) {
        ss.str("");
        ss << bitmask;
        tv_BITMASK32.push_back(ss.str() + "<<" + std::to_string(shift));
        jtv_BITMASK32.push_back(ss.str() + "<<" + std::to_string(shift));
      }
    }

    for (uint64_t onesLen = 1; onesLen <= 63;
         onesLen++) { // Inall-one bit is reserved.
      uint64_t bitmask = 0;

      for (uint64_t i = 1; i <= onesLen; i++) {
        bitmask = (bitmask << 1) + 1;
      }

      for (uint64_t shift = 0; shift <= 64 - onesLen; shift++) {
        ss.str("");
        jss.str("");
        ss << bitmask;
        jss << "((uint64_t) " << bitmask;
        tv_BITMASK64.push_back(ss.str() + "<<" + std::to_string(shift));
        jtv_BITMASK64.push_back(jss.str() + ") <<" + std::to_string(shift));
      }
    }

    if (!isXbyak_) {
      tv_Vectors = tv_VectorsAs;
      return;
    } else {
      tv_Vectors = tv_VectorsJit;
      printf("%s", "    void gen0()\n"
                   "    {\n");
    }
  }
  /*
    gcc and vc give up to compile this source,
    so I split functions.
  */
  void separateFunc() {
    if (!isXbyak_)
      return;
    printf("    }\n"
           "    void gen%d()\n"
           "    {\n",
           funcNum_++);
  }
  ~Test() {
    if (!isXbyak_)
      return;
    printf("%s", "    }\n"
                 "    void gen()\n"
                 "    {\n");
    for (int i = 0; i < funcNum_; i++) {
      printf("        gen%d();\n", i);
    }
    printf("    }\n");
  }

  PUT1( DataProcReg_2Reg_0, 
        NM("clo.w", "clz.w", "cto.w", "ctz.w", "clo.d", "clz.d", "cto.d", "ctz.d", "revb.2h", "revb.4h",
           "revb.2w", "revb.d", "revh.2w", "revh.d", "bitrev.4b", "bitrev.8b", "bitrev.w", "bitrev.d", 
           "ext.w.h", "ext.w.b", "rdtimel.w", "rdtimeh.w", "rdtime.d", "cpucfg", "asrtle.d", "asrtgt.d",
	   "iocsrrd.b", "iocsrrd.h", "iocsrrd.w", "iocsrrd.d", "iocsrwr.b", "iocsrwr.h", "iocsrwr.w", "iocsrwr.d",
	   "movgr2fcsr", "movfcsr2gr"), 
       OPS(WREG_WSP_WZERO, WREG_WSP_WZERO) );

  PUT1( DataProcReg_2Reg_1,
        NM("slli.w", "srai.w", "srli.w", "rotri.w"),
        OPS(WREG_WSP_WZERO, WREG_WSP_WZERO, IMM5BIT) );

  PUT1( DataProcReg_2Reg_2,
        NM("slli.d", "srai.d", "srli.d", "rotri.d"),
        OPS(WREG_WSP_WZERO, WREG_WSP_WZERO, IMM6BIT) );

  PUT1( DataProcReg_2Reg_3,
        NM("bstrins.w", "bstrpick.w"),
        OPS(WREG_WSP_WZERO, WREG_WSP_WZERO, IMM5BIT_MSBD, IMM5BIT_LSBD) );

  PUT1( DataProcReg_2Reg_4,
        NM("bstrpick.d", "bstrins.d"),
        OPS(WREG_WSP_WZERO, WREG_WSP_WZERO, IMM6BIT_MSBD, IMM6BIT_LSBD) );

  PUT1( DataProcReg_2Reg_5,
        NM("slti", "sltui", "addi.w", "addi.d", "lu52i.d"),
        OPS(WREG_WSP_WZERO, WREG_WSP_WZERO, IMM12BIT_SIGNED) );

  PUT1( DataProcReg_2Reg_6,
        NM("xori", "ori", "andi"),
        OPS(WREG_WSP_WZERO, WREG_WSP_WZERO, IMM12BIT) );

  PUT1( DataProcReg_2Reg_7,
        NM("csrxchg"),
        OPS(WREG, WSP, IMM14BIT) );

  PUT1( DataProcReg_2Reg_8,
        NM("lddir"),
        OPS(WREG_WSP_WZERO, WREG_WSP_WZERO, IMM8BIT) );

  PUT1( DataProcReg_2Reg_9,
        NM("invtlb", "preldx"),
        OPS(IMM5BIT, WREG_WSP_WZERO, WREG_WSP_WZERO) );

  PUT1( DataProcReg_2Reg_10,
        NM("ld.b", "ld.h", "ld.w", "ld.d", "st.b", "st.h", "st.w", "st.d",
	   "ld.bu", "ld.hu", "ld.wu"),
        OPS(WREG_WSP_WZERO, WREG_WSP_WZERO, IMM12BIT_SIGNED) );

  PUT1( DataProcReg_2Reg_11,
        NM("addu16i.d"),
        OPS(WREG_WSP_WZERO, WREG_WSP_WZERO, IMM16BIT_SIGNED) );

  PUT1( DataProcReg_3Reg_0, 
        NM("add.w", "add.d", "sub.w", "sub.d", "slt", "sltu", "maskeqz", "masknez", "nor", "and_",
	   "or_", "xor_", "orn", "andn", "sll.w", "srl.w", "sra.w", "sll.d", "srl.d", "sra.d", "rotr.w",
	   "rotr.d", "mul.w", "mulh.w", "mulh.wu", "mul.d", "mulh.d", "mulh.du", "mulw.d.w", "mulw.d.wu",
	   "crc.w.b.w", "crc.w.h.w", "crc.w.w.w", "crc.w.d.w", "crcc.w.b.w", "crcc.w.h.w", "crcc.w.w.w",
	   "crcc.w.d.w", "ldgt.b", "ldgt.h", "ldgt.w", "ldgt.d", "ldle.b", "ldle.h", "ldle.w", "ldle.d",
	   "stgt.b", "stgt.h", "stgt.w", "stgt.d", "stle.b", "stle.h", "stle.w", "stle.d", "ldx.b",
	   "ldx.h", "ldx.w", "ldx.d", "stx.b", "stx.h", "stx.w", "stx.d", "ldx.bu", "ldx.hu", "ldx.wu"), 
        OPS(WREG_WSP_WZERO, WREG_WSP_WZERO, WREG_WSP_WZERO) );

  PUT1( DataProcReg_3Reg_1, 
        NM("alsl.w", "alsl.wu", "alsl.d", "bytepick.w"),
        OPS(WREG_WSP_WZERO, WREG_WSP_WZERO, WREG_WSP_WZERO, IMM2BIT) ); 

  PUT1( DataProcReg_3Reg_2, 
        NM("bytepick.d"), 
        OPS(WREG_WSP_WZERO, WREG_WSP_WZERO, WREG_WSP_WZERO, IMM3BIT) );

  PUT1( DataProcReg_3Reg_3,
        NM("div.w", "div.wu", "div.d", "div.du", "mod.w", "mod.wu", "mod.d", "mod.du"),
        OPS(WREG_WSP_WZERO, WREG_WSP_WZERO, WREG_WSP_WZERO) );

  PUT1( DataProcReg_3Reg_4,
        NM("ammin_db.d", "ammin_db.w", "amswap.w", "amswap.d", "amadd.w", "amadd.d",
           "amand.w", "amand.d", "amor.w", "amor.d", "amxor.w", "amxor.d", "ammax.w",
	   "ammax.d", "ammin.w", "ammin.d", "ammax.wu", "ammax.du", "ammin.wu", "ammin.du",
	   "amswap_db.w", "amswap_db.d", "amadd_db.w", "amadd_db.d", "amand_db.w", "amand_db.d",
	   "amor_db.w", "amor_db.d", "amxor_db.w", "amxor_db.d", "ammax_db.w", "ammax_db.d",
	   "ammax_db.wu", "ammax_db.du", "ammin_db.wu", "ammin_db.du"),
        OPS(WREG_WSP_WZERO, WREG_AM, WREG_AM) );

  PUT1( DataProcReg_1Reg_0, 
        NM("csrrd", "csrwr"),
        OPS(WREG_WSP_WZERO, IMM14BIT) );

  PUT1( DataProcReg_1Reg_1,
        NM("cacop", "preld"),
        OPS(IMM5BIT, WREG_WSP_WZERO, IMM12BIT_SIGNED) );

  PUT1( DataProcReg_1Reg_2,
        NM("ldpte"),
        OPS(WREG_WSP_WZERO, IMM8BIT) );

  PUT1( DataProcReg_1Reg_3,
        NM("lu12i.w", "lu32i.d", "pcaddi", "pcalau12i", "pcaddu12i", "pcaddu18i"),
        OPS(WREG_WSP_WZERO, IMM20BIT_SIGNED) );

  void putDataProcReg_3Reg() {
    putDataProcReg_3Reg_0();
    putDataProcReg_3Reg_1();
    putDataProcReg_3Reg_2();
    putDataProcReg_3Reg_3();
    putDataProcReg_3Reg_4();
  }

  void putDataProcReg_2Reg() {
    putDataProcReg_2Reg_0();
    putDataProcReg_2Reg_1();
    putDataProcReg_2Reg_2();
    putDataProcReg_2Reg_3();
    putDataProcReg_2Reg_4();
    putDataProcReg_2Reg_5();
    putDataProcReg_2Reg_6();
    putDataProcReg_2Reg_7();
    putDataProcReg_2Reg_8();
    putDataProcReg_2Reg_9();
    putDataProcReg_2Reg_10();
    putDataProcReg_2Reg_11();
  }

  void putDataProcReg_1Reg() {
    putDataProcReg_1Reg_0();
    putDataProcReg_1Reg_1();
    putDataProcReg_1Reg_2();
    putDataProcReg_1Reg_3();
  }

  void putDataProcReg() {
    putDataProcReg_3Reg();
    putDataProcReg_2Reg();
    putDataProcReg_1Reg();
  }

  //Proc no-oprands instructions
  PUT1( DataProcNoOpr_0, 
        NM("tlbclr", "tlbflush", "tlbsrch", "tlbrd", "tlbwr", "tlbfill", "ertn", "nop"),
        OPS() );

  void putDataProcNoOpr() {
    putDataProcNoOpr_0();
  }

  PUT1( DataProcImm15_0, 
        NM("syscall", "dbcl", "break_", "idle", "dbar", "ibar"),
        OPS(IMM15BIT) );

  void putDataProcImm3() {
    //putDataProcImm3_2R();
  }

  void putDataProcImm5() {
    //putDataProcImm5_2R();
  }

  void putDataProcImm16() {
    //putDataProcImm16_2R();
    //putDataProcImm16_1R();
  }

  void putDataProcImm15() {
    putDataProcImm15_0();
  }

  void putDataProcImm() {
    putDataProcImm3();
    putDataProcImm5();
    putDataProcImm16();
    putDataProcImm15();
  }

  void put() {
    putDataProcImm();
    putDataProcReg();
    putDataProcNoOpr();
  }
};

int main(int argc, char *[]) {
  if (flagBit >= bitEnd) {
    std::cerr << "Test vector variation must be less than " << bitEnd
              << std::endl;
    return 1;
  }

  Test test(argc > 1);
  test.put();
}
