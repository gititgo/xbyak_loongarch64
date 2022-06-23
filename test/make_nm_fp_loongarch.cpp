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
const uint64_t WSP =  1ULL << flagBit++; /** Test vector is {sp} */
const uint64_t WZERO =  1ULL << flagBit++; /** Test vector is {zero} */

const uint64_t XREG =  1ULL << flagBit++;
const uint64_t XREG_DIFF = 1ULL << flagBit++;

const uint64_t IMM3BIT =  1ULL << flagBit++; /** Test vector is {0, 1, 2, 4, 7} */
const uint64_t IMM3BIT_FCC =  1ULL << flagBit++; /** Test vector is {0, 1, 2, 4, 7} */
const uint64_t IMM4BIT =  1ULL << flagBit++; /** Test vector is {0, 1, ..., 8, 15 } */
const uint64_t IMM5BIT =  1ULL << flagBit++; /** Test vector is {0, 1, ..., 16, 31 } */
const uint64_t IMM5BIT_S =  1ULL << flagBit++;
const uint64_t IMM6BIT =  1ULL << flagBit++; /** Test vector is {0, 1, ..., 32, 63 } */
const uint64_t IMM7BIT =  1ULL << flagBit++;
const uint64_t IMM8BIT =  1ULL << flagBit++;
const uint64_t IMM10BIT_S =  1ULL << flagBit++;
const uint64_t IMM12BIT = 1ULL << flagBit++; /** Test vector is {0, 1, ..., 2048, 4095 } */
const uint64_t IMM12BIT_SIGNED = 1ULL << flagBit++; /** Test vector is {-2048, -1024, ..., 0, 1, ..., 2047 } */
const uint64_t IMM13BIT = 1ULL << flagBit++; /** Test vector is {0, 1, ..., 4096, 8191 } */
const uint64_t IMM16BIT = 1ULL << flagBit++; /** Test vector is {0, 1, ..., 4096, 1<<13, 1<<14, 1<<15, 1<<16-1 } */
const uint64_t IMM20BIT = 1ULL << flagBit++; /** Test vector is {0, 1, ..., 4096, 1<<13, 1<<14, ..., 1<<20-1 } */

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

  std::vector<std::string> tv_WREG = {"$t1", "$t3", "$t5", "$v0", "$a1", "$a3", "$a5", "$s1", "$s3", "$s5", "$t7", "$t8", "$ra"};
  std::vector<std::string> tv_WSP = {"$sp"};
  std::vector<std::string> tv_WZERO = {"$zero"};
  std::vector<std::string> tv_XREG = {"$f0", "$f1", "$f2", "$f4", "$f5", "$f7", "$f8", "$f10", "$f11", "$f16", "$f17", "$f31"};
  std::vector<std::string> tv_XREG_DIFF = {"$f3", "$f6", "$f9", "$f12", "$f13", "$f14", "$f15", "$f18", "$f19", "$f20", "$f21", "$f22"};
  std::vector<std::string> tv_IMM3BIT = {"3", "0", "1", "2", "4", "7"};
  std::vector<std::string> jtv_IMM3BIT_FCC = {"3", "0", "1", "2", "4", "7"};
  std::vector<std::string> tv_IMM3BIT_FCC = {"$fcc3", "$fcc0", "$fcc1", "$fcc2", "$fcc4", "$fcc7"};
  std::vector<std::string> tv_IMM4BIT = {"7", "0", "1", "2", "4", "8", "15"};
  std::vector<std::string> tv_IMM5BIT = {"0x1e", "0", "1",  "2",
                                         "4",    "8", "16", "31"};
  std::vector<std::string> tv_IMM5BIT_S = {"0", "1",  "2", "4", "8", "15", 
                                           "-1", "-8", "-12", "-14", "-15", "-16"};
  std::vector<std::string> tv_IMM6BIT = {"0x39", "0",  "1",  "2", "4",
                                         "8",    "16", "32", "63"};
  std::vector<std::string> tv_IMM7BIT = {"0x3f", "0",  "1",  "2", "4",
                                         "8",    "16", "32", "64", "127"};
  std::vector<std::string> tv_IMM8BIT = {"0x7f", "0",  "1",  "2", "4",
                                         "8",    "16", "32", "64", "128", "255"};
  std::vector<std::string> tv_IMM10BIT_S = {
      "0", "1", "2","4", "8", "16", "32", "64", "128", "256", "511",
      "-512", "-511", "-510", "-508", "-496", "-480", "-448", "-384", "-256", "-1"};
  std::vector<std::string> tv_IMM12BIT = {
      "0x2aa", "0",   "1",   "2",   "4",    "8",    "16",  "32",
      "64",    "128", "256", "512", "1024", "2048", "4095"};
  std::vector<std::string> tv_IMM12BIT_SIGNED = {
      "-2048", "-1024", "-89", "-800", "0",   "1",   "2",   "4",    "8",    "16",  "32",
      "64",    "128", "256", "512", "1024", "2047", "-1"};
  std::vector<std::string> tv_IMM13BIT = {
      "0x1999", "0",   "1",   "2",   "4",    "8",    "16",   "32",
      "64",     "128", "256", "512", "1024", "2048", "4096", "8191"};
  std::vector<std::string> tv_IMM16BIT = {
      "0xe38e", "0",    "1",     "2",     "4",        "8",    "16",
      "32",     "64",   "128",   "256",   "512",      "1024", "2048",
      "4096",   "8191", "1<<14", "1<<15", "(1<<16)-1"};
  std::vector<std::string> tv_IMM20BIT = {
      "0",    "1",     "2",     "4",        "8",    "16",
      "32",     "64",   "128",   "256",   "512",    "1024", "2048",
      "4096",   "8191", "1<<14", "1<<15", "1<<19", "(1<<20)-1"};
  std::vector<std::string> tv_BITMASK32, jtv_BITMASK32;
  std::vector<std::string> tv_BITMASK64, jtv_BITMASK64;

  std::vector<std::vector<std::string> *> tv_VectorsAs = {&tv_WREG,
                                                          &tv_WSP,
                                                          &tv_WZERO,
                                                          &tv_XREG,
                                                          &tv_XREG_DIFF,
                                                          &tv_IMM3BIT,
                                                          &tv_IMM3BIT_FCC,
                                                          &tv_IMM4BIT,
                                                          &tv_IMM5BIT,
                                                          &tv_IMM5BIT_S,
                                                          &tv_IMM6BIT,
                                                          &tv_IMM7BIT,
                                                          &tv_IMM8BIT,
                                                          &tv_IMM10BIT_S,
                                                          &tv_IMM12BIT,
                                                          &tv_IMM12BIT_SIGNED,
                                                          &tv_IMM13BIT,
                                                          &tv_IMM16BIT,
                                                          &tv_IMM20BIT,
                                                          &tv_BITMASK32,
                                                          &tv_BITMASK64};

  std::vector<std::vector<std::string> *> tv_VectorsJit = {&tv_WREG,
                                                           &tv_WSP,
                                                           &tv_WZERO,
                                                           &tv_XREG,
                                                           &tv_XREG_DIFF,
                                                           &tv_IMM3BIT,
                                                           &jtv_IMM3BIT_FCC,
                                                           &tv_IMM4BIT,
                                                           &tv_IMM5BIT,
                                                           &tv_IMM5BIT_S,
                                                           &tv_IMM6BIT,
                                                           &tv_IMM7BIT,
                                                           &tv_IMM8BIT,
                                                           &tv_IMM10BIT_S,
                                                           &tv_IMM12BIT,
                                                           &tv_IMM12BIT_SIGNED,
                                                           &tv_IMM13BIT,
                                                           &tv_IMM16BIT,
                                                           &tv_IMM20BIT,
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
        /** Debug	std::cout << tv_BITMASK32.at(tv_BITMASK32.size()-1) <<
         * std::endl; */
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

  PUT1( DataProcReg_4Reg_0,
        NM("fmadd.s", "fmadd.d", "fmsub.s", "fmsub.d", "fnmadd.s", "fnmadd.d",
           "fnmsub.s", "fnmsub.d"),
        OPS(XREG, XREG, XREG_DIFF, XREG_DIFF) );

  PUT1( DataProcReg_3Reg_0,
        NM("fadd.s", "fadd.d", "fsub.s", "fsub.d", "fscaleb.s", "fscaleb.d",
           "fmul.s", "fmul.d", "fdiv.s", "fdiv.d", "fcopysign.s", "fcopysign.d", 
           "fmax.s", "fmax.d", "fmin.s", "fmin.d",
           "fmaxa.s", "fmaxa.d", "fmina.s", "fmina.d"),
        OPS(XREG, XREG, XREG_DIFF) );

  PUT1( DataProcReg_3Reg_1,
        NM("fsel"),
        OPS(XREG, XREG, XREG_DIFF, IMM3BIT_FCC) );

  PUT1( DataProcReg_3Reg_2,
        NM("fldx.s", "fldx.d", "fstx.s", "fstx.d", "fldgt.s", "fldgt.d",
	   "fldle.s", "fldle.d", "fstgt.s", "fstgt.d", "fstle.s", "fstle.d"),
        OPS(XREG, WREG, WREG) );

  PUT1( DataProcReg_2Reg_0,
        NM( "fsqrt.s", "fsqrt.d", "fabs.s", "fabs.d", "flogb.s", "flogb.d", "fclass.s", "fclass.d",
            "fneg.s", "fneg.d", "frecip.s", "frecip.d", "frsqrt.s", "frsqrt.d", "fmov.s", "fmov.d",
	        "fcvt.s.d", "fcvt.d.s", "ftintrm.w.s", "ftintrm.w.d", "ftintrm.l.s", "ftintrm.l.d",
	        "ftintrp.w.s", "ftintrp.w.d", "ftintrp.l.s", "ftintrp.l.d", "ftintrz.w.s", "ftintrz.w.d",
	        "ftintrz.l.s", "ftintrz.l.d", "ftintrne.w.s", "ftintrne.w.d", "ftintrne.l.s", "ftintrne.l.d",
	        "ftint.w.s", "ftint.w.d", "ftint.l.s", "ftint.l.d", "ffint.s.w", "ffint.s.l", "ffint.d.w",
	        "ffint.d.l", "frint.s", "frint.d"),
        OPS(XREG, XREG_DIFF));

  PUT1( DataProcReg_2Reg_1,
        NM("movgr2fr.w", "movgr2fr.d", "movgr2frh.w"),
        OPS(XREG, WREG) );

  PUT1( DataProcReg_2Reg_2,
        NM("movfr2gr.s", "movfr2gr.d", "movfrh2gr.s"),
        OPS(WREG, XREG));

  PUT1( DataProcReg_2Reg_3,
        NM("movfr2cf"),
        OPS(IMM3BIT_FCC, XREG) );

  PUT1( DataProcReg_2Reg_4,
        NM("movgr2cf"),
        OPS(IMM3BIT_FCC, WREG) );

  PUT1( DataProcReg_2Reg_5,
        NM("movcf2fr"),
        OPS(XREG, IMM3BIT_FCC) );

  PUT1( DataProcReg_2Reg_6,
        NM("movcf2gr"),
        OPS(WREG, IMM3BIT_FCC) );

  PUT1( DataProcReg_2Reg_7,
        NM("fcmp.caf.s", "fcmp.caf.d", "fcmp.cun.s", "fcmp.cun.d", "fcmp.ceq.s", "fcmp.ceq.d",
           "fcmp.cueq.s", "fcmp.cueq.d", "fcmp.clt.s", "fcmp.clt.d", "fcmp.cult.s", "fcmp.cult.d",
           "fcmp.cle.s", "fcmp.cle.d", "fcmp.cule.s", "fcmp.cule.d", "fcmp.cne.s", "fcmp.cne.d",
           "fcmp.cor.s", "fcmp.cor.d", "fcmp.cune.s", "fcmp.cune.d", "fcmp.saf.s", "fcmp.saf.d",
           "fcmp.sun.s", "fcmp.sun.d", "fcmp.seq.s", "fcmp.seq.d", "fcmp.sueq.s", "fcmp.sueq.d",
           "fcmp.slt.s", "fcmp.slt.d", "fcmp.sult.s", "fcmp.sult.d", "fcmp.sle.s", "fcmp.sle.d",
           "fcmp.sule.s", "fcmp.sule.d", "fcmp.sne.s", "fcmp.sne.d", "fcmp.sor.s", "fcmp.sor.d",
           "fcmp.sune.s", "fcmp.sune.s"),
        OPS(IMM3BIT_FCC, XREG, XREG_DIFF) );

  PUT1( DataProcReg_2Reg_8,
        NM("fld.s", "fst.s", "fld.d", "fst.d"),
        OPS(XREG, WREG, IMM12BIT_SIGNED) );

  void putDataProcReg() {
    putDataProcReg_4Reg_0();
    putDataProcReg_3Reg_0();
    putDataProcReg_3Reg_1();
    putDataProcReg_3Reg_2();
    putDataProcReg_2Reg_0();
    putDataProcReg_2Reg_1();
    putDataProcReg_2Reg_2();
    putDataProcReg_2Reg_3();
    putDataProcReg_2Reg_4();
    putDataProcReg_2Reg_5();
    putDataProcReg_2Reg_6();
    putDataProcReg_2Reg_7();
    putDataProcReg_2Reg_8();
  }

  void put() {
    putDataProcReg();
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
