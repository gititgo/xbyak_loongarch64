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
const uint64_t XREG = 1ULL << flagBit++;

const uint64_t VREG =  1ULL << flagBit++;
const uint64_t XVREG =  1ULL << flagBit++;
const uint64_t MSACREG =  1ULL << flagBit++;

const uint64_t IMM1BIT =  1ULL << flagBit++;
const uint64_t IMM2BIT =  1ULL << flagBit++;
const uint64_t IMM3BIT =  1ULL << flagBit++; /** Test vector is {0, 1, 2, 4, 7} */
const uint64_t IMM3BIT_FCC =  1ULL << flagBit++; /** Test vector is {0, 1, 2, 4, 7} */
const uint64_t IMM3BIT_S =  1ULL << flagBit++;
const uint64_t IMM4BIT =  1ULL << flagBit++; /** Test vector is {0, 1, ..., 8, 15 } */
const uint64_t IMM4BIT_S =  1ULL << flagBit++;
const uint64_t IMM5BIT =  1ULL << flagBit++; /** Test vector is {0, 1, ..., 16, 31 } */
const uint64_t IMM5BIT_S =  1ULL << flagBit++;
const uint64_t IMM6BIT =  1ULL << flagBit++; /** Test vector is {0, 1, ..., 32, 63 } */
const uint64_t IMM6BIT_S =  1ULL << flagBit++;
const uint64_t IMM7BIT =  1ULL << flagBit++;
const uint64_t IMM8BIT =  1ULL << flagBit++;
const uint64_t IMM8BIT_S =  1ULL << flagBit++;
const uint64_t IMM8BIT_S_MUL2 =  1ULL << flagBit++;
const uint64_t IMM8BIT_S_MUL4 =  1ULL << flagBit++;
const uint64_t IMM8BIT_S_MUL8 =  1ULL << flagBit++;
const uint64_t IMM10BIT_S =  1ULL << flagBit++;
const uint64_t IMM12BIT = 1ULL << flagBit++; /** Test vector is {0, 1, ..., 2048, 4095 } */
const uint64_t IMM12BIT_S = 1ULL << flagBit++; /** Test vector is {0, 1, ..., 2048, 4095 } */
const uint64_t IMM12BIT_S_MUL2 = 1ULL << flagBit++;
const uint64_t IMM12BIT_S_MUL4 = 1ULL << flagBit++;
const uint64_t IMM12BIT_S_MUL8 = 1ULL << flagBit++;
const uint64_t IMM13BIT = 1ULL << flagBit++; /** Test vector is {0, 1, ..., 4096, 8191 } */
const uint64_t IMM13BIT_S = 1ULL << flagBit++;
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

  std::vector<std::string> tv_XREG = {"$zero", "$ra", "$tp", "$a0", "$a4", "$t4", "$s7"};
  std::vector<std::string> tv_VREG = {"$vr11", "$vr0", "$vr4", "$vr8", "$vr16", "$vr31"};
  std::vector<std::string> tv_XVREG = {"$xr0", "$xr1", "$xr2", "$xr4", "$xr8", "$xr16", "$xr31"};
  std::vector<std::string> tv_MSACREG = {"$0", "$1", "$4", "$8", "$16", "$31"};
  std::vector<std::string>  tv_IMM1BIT = {"0", "1"};
  std::vector<std::string>  tv_IMM2BIT = {"0", "1", "2", "3"};
  std::vector<std::string>  tv_IMM3BIT = {"3", "0", "1", "2", "4", "7"};
  std::vector<std::string> jtv_IMM3BIT_FCC = {"3", "0", "1", "2", "4", "7"};
  std::vector<std::string>  tv_IMM3BIT_FCC = {"$fcc3", "$fcc0", "$fcc1", "$fcc2", "$fcc4", "$fcc7"};
  std::vector<std::string>  tv_IMM3BIT_S = {"0", "1", "2", "3", "-4", "-3", "-2", "-1"};
  std::vector<std::string> tv_IMM4BIT = {"7", "0", "1", "2", "4", "8", "15"};
  std::vector<std::string> tv_IMM4BIT_S = {"0", "1", "2", "4", "7", "-8", "-7", "-6", "-4", "-1"};
  std::vector<std::string> tv_IMM5BIT = {"0x1e", "0", "1",  "2",
                                         "4",    "8", "16", "31"};
  std::vector<std::string> tv_IMM5BIT_S = {"0", "1",  "2", "4", "8", "15", 
                                           "-1", "-8", "-12", "-14", "-15", "-16"};
  std::vector<std::string> tv_IMM6BIT = {"0x39", "0",  "1",  "2", "4",
                                         "8",    "16", "32", "63"};
  std::vector<std::string> tv_IMM6BIT_S = {"0",  "1",  "2", "4", "8", "16", "31", 
                                           "-32", "-31", "-30", "-28", "-24", "-16", "-1"};
  std::vector<std::string> tv_IMM7BIT = {"0x3f", "0",  "1",  "2", "4",
                                         "8",    "16", "32", "64", "127"};
  std::vector<std::string> tv_IMM8BIT = {"0x7f", "0",  "1",  "2", "4",
                                         "8",    "16", "32", "64", "128", "255"};
  std::vector<std::string> tv_IMM8BIT_S =      {"-1*(1<<7)", "1<<6", "(1<<7)-1"} ;
  std::vector<std::string> tv_IMM8BIT_S_MUL2 = {"-1*(1<<8)", "1<<6", "(1<<8)-1-1"};
  std::vector<std::string> tv_IMM8BIT_S_MUL4 = {"-1*(1<<9)", "1<<6", "(1<<5)-4", "1<<8", "(1<<8)+4", "(1<<9)-1-3"};
  std::vector<std::string> tv_IMM8BIT_S_MUL8 = {"-1*(1<<10)", "1<<6", "1<<5", "(1<<8)-8", "(1<<10)-1-7"};
  std::vector<std::string> tv_IMM10BIT_S = {
      "0", "1", "2","4", "8", "16", "32", "64", "128", "256", "511",
      "-512", "-511", "-510", "-508", "-496", "-480", "-448", "-384", "-256", "-1"};
  std::vector<std::string> tv_IMM12BIT = {
      "0x2aa", "0",   "1",   "2",   "4",    "8",    "16",  "32",
      "64",    "128", "256", "512", "1024", "2048", "4095"};
  std::vector<std::string> tv_IMM12BIT_S =     {"-1*(1<<11)", "1<<10", "(1<<11)-1"};
  std::vector<std::string> tv_IMM12BIT_S_MUL2 = {"-1*(1<<11)", "1<<10", "(1<<11)-1-1"};
  std::vector<std::string> tv_IMM12BIT_S_MUL4 = {"-1*(1<<11)", "1<<10", "(1<<11)-1-3"};
  std::vector<std::string> tv_IMM12BIT_S_MUL8 = {"-1*(1<<11)", "1<<10", "(1<<11)-1-7"};
  std::vector<std::string> tv_IMM13BIT = {
      "0x1999", "0",   "1",   "2",   "4",    "8",    "16",   "32",
      "64",     "128", "256", "512", "1024", "2048", "4096", "8191"};
  std::vector<std::string> tv_IMM13BIT_S =      {"-1*(1<<12)", "1<<11", "(1<<12)-1"} ;
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

  std::vector<std::vector<std::string> *> tv_VectorsAs = {&tv_XREG,
                                                          &tv_VREG,
                                                          &tv_XVREG,
                                                          &tv_MSACREG,
                                                          &tv_IMM1BIT,
                                                          &tv_IMM2BIT,
                                                          &tv_IMM3BIT,
                                                          &tv_IMM3BIT_FCC,
                                                          &tv_IMM3BIT_S,
                                                          &tv_IMM4BIT,
                                                          &tv_IMM4BIT_S,
                                                          &tv_IMM5BIT,
                                                          &tv_IMM5BIT_S,
                                                          &tv_IMM6BIT,
                                                          &tv_IMM6BIT_S,
                                                          &tv_IMM7BIT,
                                                          &tv_IMM8BIT,
                                                          &tv_IMM8BIT_S,
                                                          &tv_IMM8BIT_S_MUL2,
                                                          &tv_IMM8BIT_S_MUL4,
                                                          &tv_IMM8BIT_S_MUL8,
                                                          &tv_IMM10BIT_S,
                                                          &tv_IMM12BIT,
                                                          &tv_IMM12BIT_S,
                                                          &tv_IMM12BIT_S_MUL2,
                                                          &tv_IMM12BIT_S_MUL4,
                                                          &tv_IMM12BIT_S_MUL8,
                                                          &tv_IMM13BIT,
                                                          &tv_IMM13BIT_S,
                                                          &tv_IMM16BIT,
                                                          &tv_IMM20BIT,
                                                          &tv_BITMASK32,
                                                          &tv_BITMASK64};

  std::vector<std::vector<std::string> *> tv_VectorsJit = {&tv_XREG,
                                                           &tv_VREG,
                                                           &tv_XVREG,
                                                           &tv_MSACREG,
                                                           &tv_IMM1BIT,
                                                           &tv_IMM2BIT,
                                                           &tv_IMM3BIT,
                                                           &jtv_IMM3BIT_FCC,
                                                           &tv_IMM3BIT_S,
                                                           &tv_IMM4BIT,
                                                           &tv_IMM4BIT_S,
                                                           &tv_IMM5BIT,
                                                           &tv_IMM5BIT_S,
                                                           &tv_IMM6BIT,
                                                           &tv_IMM6BIT_S,
                                                           &tv_IMM7BIT,
                                                           &tv_IMM8BIT,
                                                           &tv_IMM8BIT_S,
                                                           &tv_IMM8BIT_S_MUL2,
                                                           &tv_IMM8BIT_S_MUL4,
                                                           &tv_IMM8BIT_S_MUL8,
                                                           &tv_IMM10BIT_S,
                                                           &tv_IMM12BIT,
                                                           &tv_IMM12BIT_S,
                                                           &tv_IMM12BIT_S_MUL2,
                                                           &tv_IMM12BIT_S_MUL4,
                                                           &tv_IMM12BIT_S_MUL8,
                                                           &tv_IMM13BIT,
                                                           &tv_IMM13BIT_S,
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
        /** Debug std::cout << tv_BITMASK64.at(tv_BITMASK64.size()-1) <<
         * std::endl; */
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

/*****************************************************************/
  PUT1( DataProc_4R,
        NM("xvfmadd.s",
"xvfmadd.d",
"xvfmsub.s",
"xvfmsub.d",
"xvfnmadd.s",
"xvfnmadd.d",
"xvfnmsub.s",
"xvfnmsub.d",
"xvbitsel.v",
"xvshuf.b"
          ),
        OPS(XVREG, XVREG, XVREG, XVREG) );

  PUT1( DataProc_4VR,
        NM("vbitsel.v","vfmadd.s","vfmadd.d"),
        OPS(VREG, VREG, VREG, VREG) );

/*****************************************************************/
  PUT1( DataProc_VR_2GR,
        NM("vldx", "vstx"),
        OPS(VREG, XREG, XREG) );
  PUT1( DataProc_XR_2GR,
        NM("xvldx", "xvstx"),
        OPS(XVREG, XREG, XREG) );

  PUT1( DataProc_VR_GR, NM(  "vreplgr2vr.b", "vreplgr2vr.h", "vreplgr2vr.w", "vreplgr2vr.d"), OPS(VREG, XREG) );
  PUT1( DataProc_2VR_GR, NM(  "vreplve.b", "vreplve.h", "vreplve.w", "vreplve.d"), OPS(VREG, VREG, XREG) );
  PUT1( DataProc_2VR_UINT5, NM( "vbsll.v", "vbsrl.v" ), OPS(VREG, VREG, IMM5BIT) );
  PUT1( DataProc_2VR_UINT8, NM( "vextrins.d", "vextrins.w", "vextrins.h", "vextrins.b", "vshuf4i.b", "vshuf4i.h", "vshuf4i.w", "vshuf4i.d" ), OPS(VREG, VREG, IMM8BIT) );
  PUT1( DataProc_2XR_GR,
        NM("xvreplve.b", "xvreplve.h", "xvreplve.w", "xvreplve.d"),
        OPS(XVREG, XVREG, XREG) );

  PUT1( DataProc_3XR,
        NM(
"xvseq.b",
"xvseq.h",
"xvseq.w",
"xvseq.d",
"xvsle.b",
"xvsle.h",
"xvsle.w",
"xvsle.d",
"xvsle.bu",
"xvsle.hu",
"xvsle.wu",
"xvsle.du",
"xvslt.b",
"xvslt.h",
"xvslt.w",
"xvslt.d",
"xvslt.bu",
"xvslt.hu",
"xvslt.wu",
"xvslt.du",
"xvadd.b",
"xvadd.h",
"xvadd.w",
"xvadd.d",
"xvsub.b",
"xvsub.h",
"xvsub.w",
"xvsub.d",
"xvaddwev.h.b",
"xvaddwev.w.h",
"xvaddwev.d.w",
"xvaddwev.q.d",
"xvsubwev.h.b",
"xvsubwev.w.h",
"xvsubwev.d.w",
"xvsubwev.q.d",
"xvaddwod.h.b",
"xvaddwod.w.h",
"xvaddwod.d.w",
"xvaddwod.q.d",
"xvsubwod.h.b",
"xvsubwod.w.h",
"xvsubwod.d.w",
"xvsubwod.q.d",
"xvaddwev.h.bu",
"xvaddwev.w.hu",
"xvaddwev.d.wu",
"xvaddwev.q.du",
"xvsubwev.h.bu",
"xvsubwev.w.hu",
"xvsubwev.d.wu",
"xvsubwev.q.du",
"xvaddwod.h.bu",
"xvaddwod.w.hu",
"xvaddwod.d.wu",
"xvaddwod.q.du",
"xvsubwod.h.bu",
"xvsubwod.w.hu",
"xvsubwod.d.wu",
"xvsubwod.q.du",
"xvaddwev.h.bu.b",
"xvaddwev.w.hu.h",
"xvaddwev.d.wu.w",
"xvaddwev.q.du.d",
"xvaddwod.h.bu.b",
"xvaddwod.w.hu.h",
"xvaddwod.d.wu.w",
"xvaddwod.q.du.d",
"xvsadd.b",
"xvsadd.h",
"xvsadd.w",
"xvsadd.d",
"xvssub.b",
"xvssub.h",
"xvssub.w",
"xvssub.d",
"xvsadd.bu",
"xvsadd.hu",
"xvsadd.wu",
"xvsadd.du",
"xvssub.bu",
"xvssub.hu",
"xvssub.wu",
"xvssub.du",
"xvhaddw.h.b",
"xvhaddw.w.h",
"xvhaddw.d.w",
"xvhaddw.q.d",
"xvhsubw.h.b",
"xvhsubw.w.h",
"xvhsubw.d.w",
"xvhsubw.q.d",
"xvhaddw.hu.bu",
"xvhaddw.wu.hu",
"xvhaddw.du.wu",
"xvhaddw.qu.du",
"xvhsubw.hu.bu",
"xvhsubw.wu.hu",
"xvhsubw.du.wu",
"xvhsubw.qu.du",
"xvadda.b",
"xvadda.h",
"xvadda.w",
"xvadda.d",
"xvabsd.b",
"xvabsd.h",
"xvabsd.w",
"xvabsd.d",
"xvabsd.bu",
"xvabsd.hu",
"xvabsd.wu",
"xvabsd.du",
"xvavg.b",
"xvavg.h",
"xvavg.w",
"xvavg.d",
"xvavg.bu",
"xvavg.hu",
"xvavg.wu",
"xvavg.du",
"xvavgr.b",
"xvavgr.h",
"xvavgr.w",
"xvavgr.d",
"xvavgr.bu",
"xvavgr.hu",
"xvavgr.wu",
"xvavgr.du",
"xvmax.b",
"xvmax.h",
"xvmax.w",
"xvmax.d",
"xvmin.b",
"xvmin.h",
"xvmin.w",
"xvmin.d",
"xvmax.bu",
"xvmax.hu",
"xvmax.wu",
"xvmax.du",
"xvmin.bu",
"xvmin.hu",
"xvmin.wu",
"xvmin.du",
"xvmul.b",
"xvmul.h",
"xvmul.w",
"xvmul.d",
"xvmuh.b",
"xvmuh.h",
"xvmuh.w",
"xvmuh.d",
"xvmuh.bu",
"xvmuh.hu",
"xvmuh.wu",
"xvmuh.du",
"xvmulwev.h.b",
"xvmulwev.w.h",
"xvmulwev.d.w",
"xvmulwev.q.d",
"xvmulwod.h.b",
"xvmulwod.w.h",
"xvmulwod.d.w",
"xvmulwod.q.d",
"xvmulwev.h.bu",
"xvmulwev.w.hu",
"xvmulwev.d.wu",
"xvmulwev.q.du",
"xvmulwod.h.bu",
"xvmulwod.w.hu",
"xvmulwod.d.wu",
"xvmulwod.q.du",
"xvmulwev.h.bu.b",
"xvmulwev.w.hu.h",
"xvmulwev.d.wu.w",
"xvmulwev.q.du.d",
"xvmulwod.h.bu.b",
"xvmulwod.w.hu.h",
"xvmulwod.d.wu.w",
"xvmulwod.q.du.d",
"xvmadd.b",
"xvmadd.h",
"xvmadd.w",
"xvmadd.d",
"xvmsub.b",
"xvmsub.h",
"xvmsub.w",
"xvmsub.d",
"xvmaddwev.h.b",
"xvmaddwev.w.h",
"xvmaddwev.d.w",
"xvmaddwev.q.d",
"xvmaddwod.h.b",
"xvmaddwod.w.h",
"xvmaddwod.d.w",
"xvmaddwod.q.d",
"xvmaddwev.h.bu",
"xvmaddwev.w.hu",
"xvmaddwev.d.wu",
"xvmaddwev.q.du",
"xvmaddwod.h.bu",
"xvmaddwod.w.hu",
"xvmaddwod.d.wu",
"xvmaddwod.q.du",
"xvmaddwev.h.bu.b",
"xvmaddwev.w.hu.h",
"xvmaddwev.d.wu.w",
"xvmaddwev.q.du.d",
"xvmaddwod.h.bu.b",
"xvmaddwod.w.hu.h",
"xvmaddwod.d.wu.w",
"xvmaddwod.q.du.d",
"xvdiv.b",
"xvdiv.h",
"xvdiv.w",
"xvdiv.d",
"xvmod.b",
"xvmod.h",
"xvmod.w",
"xvmod.d",
"xvdiv.bu",
"xvdiv.hu",
"xvdiv.wu",
"xvdiv.du",
"xvmod.bu",
"xvmod.hu",
"xvmod.wu",
"xvmod.du",
"xvsll.b",
"xvsll.h",
"xvsll.w",
"xvsll.d",
"xvsrl.b",
"xvsrl.h",
"xvsrl.w",
"xvsrl.d",
"xvsra.b",
"xvsra.h",
"xvsra.w",
"xvsra.d",
"xvrotr.b",
"xvrotr.h",
"xvrotr.w",
"xvrotr.d",
"xvsrlr.b",
"xvsrlr.h",
"xvsrlr.w",
"xvsrlr.d",
"xvsrar.b",
"xvsrar.h",
"xvsrar.w",
"xvsrar.d",
"xvsrln.b.h",
"xvsrln.h.w",
"xvsrln.w.d",
"xvsran.b.h",
"xvsran.h.w",
"xvsran.w.d",
"xvsrlrn.b.h",
"xvsrlrn.h.w",
"xvsrlrn.w.d",
"xvsrarn.b.h",
"xvsrarn.h.w",
"xvsrarn.w.d",
"xvssrln.b.h",
"xvssrln.h.w",
"xvssrln.w.d",
"xvssran.b.h",
"xvssran.h.w",
"xvssran.w.d",
"xvssrlrn.b.h",
"xvssrlrn.h.w",
"xvssrlrn.w.d",
"xvssrarn.b.h",
"xvssrarn.h.w",
"xvssrarn.w.d",
"xvssrln.bu.h",
"xvssrln.hu.w",
"xvssrln.wu.d",
"xvssran.bu.h",
"xvssran.hu.w",
"xvssran.wu.d",
"xvssrlrn.bu.h",
"xvssrlrn.hu.w",
"xvssrlrn.wu.d",
"xvssrarn.bu.h",
"xvssrarn.hu.w",
"xvssrarn.wu.d",
"xvbitclr.b",
"xvbitclr.h",
"xvbitclr.w",
"xvbitclr.d",
"xvbitset.b",
"xvbitset.h",
"xvbitset.w",
"xvbitset.d",
"xvbitrev.b",
"xvbitrev.h",
"xvbitrev.w",
"xvbitrev.d",
"xvpackev.b",
"xvpackev.h",
"xvpackev.w",
"xvpackev.d",
"xvpackod.b",
"xvpackod.h",
"xvpackod.w",
"xvpackod.d",
"xvilvl.b",
"xvilvl.h",
"xvilvl.w",
"xvilvl.d",
"xvilvh.b",
"xvilvh.h",
"xvilvh.w",
"xvilvh.d",
"xvpickev.b",
"xvpickev.h",
"xvpickev.w",
"xvpickev.d",
"xvpickod.b",
"xvpickod.h",
"xvpickod.w",
"xvpickod.d",
"xvfrstp.b",
"xvfrstp.h",
"xvsigncov.b",
"xvsigncov.h",
"xvsigncov.w",
"xvsigncov.d",
"xvfadd.s",
"xvfadd.d",
"xvfsub.s",
"xvfsub.d",
"xvfmul.s",
"xvfmul.d",
"xvfdiv.s",
"xvfdiv.d",
"xvfmax.s",
"xvfmax.d",
"xvfmin.s",
"xvfmin.d",
"xvfmaxa.s",
"xvfmaxa.d",
"xvfmina.s",
"xvfmina.d",
"xvfscaleb.s",
"xvfscaleb.d",
"xvfcvt.h.s",
"xvfcvt.s.d",
"xvffint.s.l",
"xvftint.w.d",
"xvftintrm.w.d",
"xvftintrp.w.d",
"xvftintrz.w.d",
"xvftintrne.w.d",
"xvshuf.h",
"xvshuf.w",
"xvshuf.d",
"xvperm.w",
"xvand.v",
"xvor.v",
"xvxor.v",
"xvnor.v",
"xvandn.v",
"xvorn.v",
"xvadd.q",
"xvsub.q",
//CMP.cond
"xvfcmp.caf.s",
"xvfcmp.cun.s",
"xvfcmp.ceq.s",
"xvfcmp.cueq.s",
"xvfcmp.clt.s",
"xvfcmp.cult.s",
"xvfcmp.cle.s",
"xvfcmp.cule.s",
"xvfcmp.cne.s",
"xvfcmp.cor.s",
"xvfcmp.cune.s",
"xvfcmp.saf.s",
"xvfcmp.sun.s",
"xvfcmp.seq.s",
"xvfcmp.sueq.s",
"xvfcmp.slt.s",
"xvfcmp.sult.s",
"xvfcmp.sle.s",
"xvfcmp.sule.s",
"xvfcmp.sne.s",
"xvfcmp.sor.s",
"xvfcmp.sune.s",
"xvfcmp.caf.d",
"xvfcmp.cun.d",
"xvfcmp.ceq.d",
"xvfcmp.cueq.d",
"xvfcmp.clt.d",
"xvfcmp.cult.d",
"xvfcmp.cle.d",
"xvfcmp.cule.d",
"xvfcmp.cne.d",
"xvfcmp.cor.d",
"xvfcmp.cune.d",
"xvfcmp.saf.d",
"xvfcmp.sun.d",
"xvfcmp.seq.d",
"xvfcmp.sueq.d",
"xvfcmp.slt.d",
"xvfcmp.sult.d",
"xvfcmp.sle.d",
"xvfcmp.sule.d",
"xvfcmp.sne.d",
"xvfcmp.sor.d",
"xvfcmp.sune.d"
	),
        OPS(XVREG, XVREG, XVREG) );

  void putDataProc_3R() {
    putDataProc_VR_2GR();
    putDataProc_XR_2GR();
    putDataProc_VR_GR();
    putDataProc_2VR_GR();
    putDataProc_2VR_UINT5();
    putDataProc_2VR_UINT8();
    putDataProc_2XR_GR();
    putDataProc_3XR();
    putDataProc_3VR();
  }

/*****************************************************************/
  PUT1( DataProc_VR_GR_SI12,
        NM("vld", "vst", "vldrepl.b"),
        OPS(VREG, XREG, IMM12BIT_S) );
  PUT1( DataProc_VR_GR_SI12_MUL2, NM("vldrepl.h"), OPS(VREG, XREG, IMM12BIT_S_MUL2) );
  PUT1( DataProc_VR_GR_SI12_MUL4, NM("vldrepl.w"), OPS(VREG, XREG, IMM12BIT_S_MUL4) );
  PUT1( DataProc_VR_GR_SI12_MUL8, NM("vldrepl.d"), OPS(VREG, XREG, IMM12BIT_S_MUL8) );

  PUT1( DataProc_XR_GR_SI12,
        NM("xvld", "xvst","xvldrepl.b"),
        OPS(XVREG, XREG, IMM12BIT_S) );
  PUT1( DataProc_XR_GR_SI12_MUL2, NM("xvldrepl.h"), OPS(XVREG, XREG, IMM12BIT_S_MUL2) );
  PUT1( DataProc_XR_GR_SI12_MUL4, NM("xvldrepl.w"), OPS(XVREG, XREG, IMM12BIT_S_MUL4) );
  PUT1( DataProc_XR_GR_SI12_MUL8, NM("xvldrepl.d"), OPS(XVREG, XREG, IMM12BIT_S_MUL8) );

  PUT1( DataProc_2XR_SI5,
        NM(
"xvseqi.b",
"xvseqi.h",
"xvseqi.w",
"xvseqi.d",
"xvslei.b",
"xvslei.h",
"xvslei.w",
"xvslei.d",
"xvslti.b",
"xvslti.h",
"xvslti.w",
"xvslti.d",
"xvmaxi.b",
"xvmaxi.h",
"xvmaxi.w",
"xvmaxi.d",
"xvmini.b",
"xvmini.h",
"xvmini.w",
"xvmini.d"
          ),
        OPS(XVREG, XVREG, IMM5BIT_S) );

  PUT1( DataProc_2XR_UI5,
        NM(
"xvslei.bu",
"xvslei.hu",
"xvslei.wu",
"xvslei.du",
"xvslti.bu",
"xvslti.hu",
"xvslti.wu",
"xvslti.du",
"xvaddi.bu",
"xvaddi.hu",
"xvaddi.wu",
"xvaddi.du",
"xvsubi.bu",
"xvsubi.hu",
"xvsubi.wu",
"xvsubi.du",
"xvbsll.v",
"xvbsrl.v",
"xvmaxi.bu",
"xvmaxi.hu",
"xvmaxi.wu",
"xvmaxi.du",
"xvmini.bu",
"xvmini.hu",
"xvmini.wu",
"xvmini.du",
"xvfrstpi.b",
"xvfrstpi.h",
"xvhseli.d"
          ),
        OPS(XVREG, XVREG, IMM5BIT) );

  PUT1( DataProc_BIT_2VR_UI3,
        NM(
"vslli.b",
"vsrli.b",
"vsrai.b"),
        OPS(VREG, VREG, IMM3BIT) );

  PUT1( DataProc_BIT_2VR_UI4,
        NM(
"vslli.h",
"vsrli.h",
"vsrai.h"),
        OPS(VREG, VREG, IMM4BIT) );

  PUT1( DataProc_BIT_2VR_UI5,
        NM(
"vslli.w",
"vsrli.w",
"vsrai.w"),
        OPS(VREG, VREG, IMM5BIT) );

  PUT1( DataProc_BIT_2VR_UI6,
        NM(
"vslli.d",
"vsrli.d",
"vsrai.d"),
        OPS(VREG, VREG, IMM6BIT) );

  PUT1( DataProc_BIT_2XR_UI3,
        NM(
"xvrotri.b",
"xvsrlri.b",
"xvsrari.b",
"xvsllwil.h.b",
"xvsllwil.hu.bu",
"xvbitclri.b",
"xvbitseti.b",
"xvbitrevi.b",
"xvsat.b",
"xvsat.bu",
"xvslli.b",
"xvsrli.b",
"xvsrai.b"
          ),
        OPS(XVREG, XVREG, IMM3BIT) );

  PUT1( DataProc_BIT_2XR_UI4,
        NM(
"xvrotri.h",
"xvsrlri.h",
"xvsrari.h",
"xvsllwil.w.h",
"xvsllwil.wu.hu",
"xvbitclri.h",
"xvbitseti.h",
"xvbitrevi.h",
"xvsat.h",
"xvsat.hu",
"xvslli.h",
"xvsrli.h",
"xvsrai.h",
"xvsrlni.b.h",
"xvsrlrni.b.h",
"xvssrlni.b.h",
"xvssrlni.bu.h",
"xvssrlrni.b.h",
"xvssrlrni.bu.h",
"xvsrani.b.h",
"xvsrarni.b.h",
"xvssrani.b.h",
"xvssrani.bu.h",
"xvssrarni.b.h",
"xvssrarni.bu.h"
          ),
        OPS(XVREG, XVREG, IMM4BIT) );

  PUT1( DataProc_BIT_2XR_UI5,
        NM(
"xvrotri.w",
"xvsrlri.w",
"xvsrari.w",
"xvsllwil.d.w",
"xvsllwil.du.wu",
"xvbitclri.w",
"xvbitseti.w",
"xvbitrevi.w",
"xvsat.w",
"xvsat.wu",
"xvslli.w",
"xvsrli.w",
"xvsrai.w",
"xvsrlni.h.w",
"xvsrlrni.h.w",
"xvssrlni.h.w",
"xvssrlni.hu.w",
"xvssrlrni.h.w",
"xvssrlrni.hu.w",
"xvsrani.h.w",
"xvsrarni.h.w",
"xvssrani.h.w",
"xvssrani.hu.w",
"xvssrarni.h.w",
"xvssrarni.hu.w"
          ),
        OPS(XVREG, XVREG, IMM5BIT) );

  PUT1( DataProc_BIT_2XR_UI6,
        NM(
"xvrotri.d",
"xvsrlri.d",
"xvsrari.d",
"xvbitclri.d",
"xvbitseti.d",
"xvbitrevi.d",
"xvsat.d",
"xvsat.du",
"xvslli.d",
"xvsrli.d",
"xvsrai.d",
"xvsrlni.w.d",
"xvsrlrni.w.d",
"xvssrlni.w.d",
"xvssrlni.wu.d",
"xvssrlrni.w.d",
"xvssrlrni.wu.d",
"xvsrani.w.d",
"xvsrarni.w.d",
"xvssrani.w.d",
"xvssrani.wu.d",
"xvssrarni.w.d",
"xvssrarni.wu.d"
          ),
        OPS(XVREG, XVREG, IMM6BIT) );

  PUT1( DataProc_BIT_2XR_UI7,
        NM(
"xvsrlni.d.q",
"xvsrlrni.d.q",
"xvssrlni.d.q",
"xvssrlni.du.q",
"xvssrlrni.d.q",
"xvssrlrni.du.q",
"xvsrani.d.q",
"xvsrarni.d.q",
"xvssrani.d.q",
"xvssrani.du.q",
"xvssrarni.d.q",
"xvssrarni.du.q"
          ),
        OPS(XVREG, XVREG, IMM7BIT) );

/*****************************************************************/

  PUT1( DataProc_VR_GR_UI4, NM("vinsgr2vr.b"), OPS(VREG, XREG, IMM4BIT) );
  PUT1( DataProc_VR_GR_UI3, NM("vinsgr2vr.h"), OPS(VREG, XREG, IMM3BIT) );
  PUT1( DataProc_VR_GR_UI2, NM("vinsgr2vr.w"), OPS(VREG, XREG, IMM2BIT) );
  PUT1( DataProc_VR_GR_UI1, NM("vinsgr2vr.d"), OPS(VREG, XREG, IMM1BIT) );

  PUT1( DataProc_XR_GR_UI3, NM("xvinsgr2vr.w"), OPS(XVREG, XREG, IMM3BIT) );
  PUT1( DataProc_XR_GR_UI2, NM("xvinsgr2vr.d"), OPS(XVREG, XREG, IMM2BIT) );

  PUT1( DataProc_GR_VR_UI4, NM("vpickve2gr.b", "vpickve2gr.bu"), OPS(XREG, VREG, IMM4BIT) );
  PUT1( DataProc_GR_VR_UI3, NM("vpickve2gr.h", "vpickve2gr.hu"), OPS(XREG, VREG, IMM3BIT) );
  PUT1( DataProc_GR_VR_UI2, NM("vpickve2gr.w", "vpickve2gr.wu"), OPS(XREG, VREG, IMM2BIT) );
  PUT1( DataProc_GR_VR_UI1, NM("vpickve2gr.d", "vpickve2gr.du"), OPS(XREG, VREG, IMM1BIT) );

  PUT1( DataProc_GR_XR_UI3, NM("xvpickve2gr.w", "xvpickve2gr.wu"), OPS(XREG, XVREG, IMM3BIT) );
  PUT1( DataProc_GR_XR_UI2, NM("xvpickve2gr.d", "xvpickve2gr.du"), OPS(XREG, XVREG, IMM2BIT) );

  PUT1( DataProc_2XR_UI3, NM("xvinsve0.w", "xvpickve.w", "xvrepl128vei.h"), OPS(XVREG, XVREG, IMM3BIT) );
  PUT1( DataProc_2XR_UI2, NM("xvinsve0.d", "xvpickve.d", "xvrepl128vei.w"), OPS(XVREG, XVREG, IMM2BIT) );

  PUT1( DataProc_VR_VR_UI4, NM("vreplvei.b"), OPS(VREG, VREG, IMM4BIT) );
  PUT1( DataProc_VR_VR_UI3, NM("vreplvei.h"), OPS(VREG, VREG, IMM3BIT) );
  PUT1( DataProc_VR_VR_UI2, NM("vreplvei.w"), OPS(VREG, VREG, IMM2BIT) );
  PUT1( DataProc_VR_VR_UI1, NM("vreplvei.d"), OPS(VREG, VREG, IMM1BIT) );

  PUT1( DataProc_2XR_UI4, NM("xvrepl128vei.b"), OPS(XVREG, XVREG, IMM4BIT) );
  PUT1( DataProc_2XR_UI1, NM("xvrepl128vei.d"), OPS(XVREG, XVREG, IMM1BIT) );

  PUT1( DataProc_3VR, NM(
"vfmax.s", 
"vfmax.d", 
"vfmin.s", 
"vfmin.d", 
"vfadd.s", 
"vfadd.d", 
"vfmul.s", 
"vfmul.d",
"vadd.b", 
"vadd.h", 
"vadd.w", 
"vadd.d", 
"vmax.b", 
"vmax.h", 
"vmax.w", 
"vmax.d", 
"vmin.b", 
"vmin.h", 
"vmin.w", 
"vmin.d", 
"vmul.b", 
"vmul.h", 
"vmul.w", 
"vmul.d",
"vand.v",
"vor.v",
"vxor.v",
"vnor.v",
"vandn.v",
"vorn.v",
"vpickev.b",
"vpickev.h",
"vpickev.w",
"vpickev.d",
"vmax.bu",
"vmax.hu",
"vmax.wu",
"vmax.du",
"vmin.bu",
"vmin.hu",
"vmin.wu",
"vmin.du",
"vseq.b",
"vseq.h",
"vseq.w",
"vseq.d",
"vfsub.s",
"vfsub.d",
"vfdiv.s",
"vfdiv.d",
"vilvl.b",
"vilvl.h",
"vilvl.w",
"vilvl.d",
"vilvh.b",
"vilvh.h",
"vilvh.w",
"vilvh.d",
//CMP.cond
"vfcmp.caf.s",
"vfcmp.cun.s",
"vfcmp.ceq.s",
"vfcmp.cueq.s",
"vfcmp.clt.s",
"vfcmp.cult.s",
"vfcmp.cle.s",
"vfcmp.cule.s",
"vfcmp.cne.s",
"vfcmp.cor.s",
"vfcmp.cune.s",
"vfcmp.saf.s",
"vfcmp.sun.s",
"vfcmp.seq.s",
"vfcmp.sueq.s",
"vfcmp.slt.s",
"vfcmp.sult.s",
"vfcmp.sle.s",
"vfcmp.sule.s",
"vfcmp.sne.s",
"vfcmp.sor.s",
"vfcmp.sune.s",
"vfcmp.caf.d",
"vfcmp.cun.d",
"vfcmp.ceq.d",
"vfcmp.cueq.d",
"vfcmp.clt.d",
"vfcmp.cult.d",
"vfcmp.cle.d",
"vfcmp.cule.d",
"vfcmp.cne.d",
"vfcmp.cor.d",
"vfcmp.cune.d",
"vfcmp.saf.d",
"vfcmp.sun.d",
"vfcmp.seq.d",
"vfcmp.sueq.d",
"vfcmp.slt.d",
"vfcmp.sult.d",
"vfcmp.sle.d",
"vfcmp.sule.d",
"vfcmp.sne.d",
"vfcmp.sor.d",
"vfcmp.sune.d"
    ), OPS(VREG, VREG, VREG) );

/*****************************************************************/
  PUT1( DataProc_2XR_UI8, 
        NM(
"xvextrins.d",
"xvextrins.w",
"xvextrins.h",
"xvextrins.b",
"xvshuf4i.b",
"xvshuf4i.h",
"xvshuf4i.w",
"xvshuf4i.d",
"xvbitseli.b",
"xvandi.b",
"xvori.b",
"xvxori.b",
"xvnori.b",
"xvpermi.w",
"xvpermi.d",
"xvpermi.q"
		), 
	OPS(XVREG, XVREG, IMM8BIT) );

/*****************************************************************/

  void putDataProc_2R_1I() {
    putDataProc_VR_GR_SI12();
    putDataProc_VR_GR_SI12_MUL2();
    putDataProc_VR_GR_SI12_MUL4();
    putDataProc_VR_GR_SI12_MUL8();

    putDataProc_XR_GR_SI12();
    putDataProc_XR_GR_SI12_MUL2();
    putDataProc_XR_GR_SI12_MUL4();
    putDataProc_XR_GR_SI12_MUL8();

    putDataProc_2XR_SI5();
    putDataProc_2XR_UI5();

    putDataProc_BIT_2VR_UI3();
    putDataProc_BIT_2VR_UI4();
    putDataProc_BIT_2VR_UI5();
    putDataProc_BIT_2VR_UI6();

    putDataProc_BIT_2XR_UI3();
    putDataProc_BIT_2XR_UI4();
    putDataProc_BIT_2XR_UI5();
    putDataProc_BIT_2XR_UI6();
    putDataProc_BIT_2XR_UI7();

    putDataProc_VR_GR_UI4();
    putDataProc_VR_GR_UI3();
    putDataProc_VR_GR_UI2();
    putDataProc_VR_GR_UI1();
    putDataProc_GR_VR_UI4();
    putDataProc_GR_VR_UI3();
    putDataProc_GR_VR_UI2();
    putDataProc_GR_VR_UI1();
    putDataProc_VR_VR_UI4();
    putDataProc_VR_VR_UI3();
    putDataProc_VR_VR_UI2();
    putDataProc_VR_VR_UI1();

    putDataProc_XR_GR_UI3();
    putDataProc_XR_GR_UI2();

    putDataProc_GR_XR_UI3();
    putDataProc_GR_XR_UI2();

    putDataProc_2XR_UI3();
    putDataProc_2XR_UI2();

    putDataProc_2XR_UI4();
    putDataProc_2XR_UI1();

    putDataProc_2XR_UI8();

  }

/*****************************************************************/
  PUT1( DataProc_VR_GR_SI8_UI1, NM("vstelm.d"), OPS(VREG, XREG, IMM8BIT_S_MUL8, IMM1BIT) );
  PUT1( DataProc_VR_GR_SI8_UI2, NM("vstelm.w"), OPS(VREG, XREG, IMM8BIT_S_MUL4, IMM2BIT) );
  PUT1( DataProc_VR_GR_SI8_UI3, NM("vstelm.h"), OPS(VREG, XREG, IMM8BIT_S_MUL2, IMM3BIT) );
  PUT1( DataProc_VR_GR_SI8_UI4, NM("vstelm.b"), OPS(VREG, XREG, IMM8BIT_S, IMM4BIT) );

  PUT1( DataProc_XR_GR_SI8_UI2, NM("xvstelm.d"), OPS(XVREG, XREG, IMM8BIT_S_MUL8, IMM2BIT) );
  PUT1( DataProc_XR_GR_SI8_UI3, NM("xvstelm.w"), OPS(XVREG, XREG, IMM8BIT_S_MUL4, IMM3BIT) );
  PUT1( DataProc_XR_GR_SI8_UI4, NM("xvstelm.h"), OPS(XVREG, XREG, IMM8BIT_S_MUL2, IMM4BIT) );
  PUT1( DataProc_XR_GR_SI8_UI5, NM("xvstelm.b"), OPS(XVREG, XREG, IMM8BIT_S, IMM5BIT) );

  void putDataProc_2R_2I() {
    putDataProc_VR_GR_SI8_UI1();
    putDataProc_VR_GR_SI8_UI2();
    putDataProc_VR_GR_SI8_UI3();
    putDataProc_VR_GR_SI8_UI4();

    putDataProc_XR_GR_SI8_UI2();
    putDataProc_XR_GR_SI8_UI3();
    putDataProc_XR_GR_SI8_UI4();
    putDataProc_XR_GR_SI8_UI5();
  }

/*****************************************************************/
  PUT1( DataProc_XR_GR, 
        NM(
"xvreplgr2vr.b",
"xvreplgr2vr.h",
"xvreplgr2vr.w",
"xvreplgr2vr.d"
	  ), 
	OPS(XVREG, XREG) );
  PUT1( DataProc_2VR, NM("vffint.s.w", "vftint.w.s"), OPS(VREG, VREG) );

  PUT1( DataProc_2XR, 
        NM(
"xvclo.b",
"xvclo.h",
"xvclo.w",
"xvclo.d",
"xvclz.b",
"xvclz.h",
"xvclz.w",
"xvclz.d",
"xvpcnt.b",
"xvpcnt.h",
"xvpcnt.w",
"xvpcnt.d",
"xvneg.b",
"xvneg.h",
"xvneg.w",
"xvneg.d",
"xvmskltz.b",
"xvmskltz.h",
"xvmskltz.w",
"xvmskltz.d",
"xvmskgez.b",
"xvmsknz.b",
"xvflogb.s",
"xvflogb.d",
"xvfclass.s",
"xvfclass.d",
"xvfsqrt.s",
"xvfsqrt.d",
"xvfrecip.s",
"xvfrecip.d",
"xvfrsqrt.s",
"xvfrsqrt.d",
"xvfrint.s",
"xvfrint.d",
"xvfrintrm.s",
"xvfrintrm.d",
"xvfrintrp.s",
"xvfrintrp.d",
"xvfrintrz.s",
"xvfrintrz.d",
"xvfrintrne.s",
"xvfrintrne.d",
"xvfcvtl.s.h",
"xvfcvth.s.h",
"xvfcvtl.d.s",
"xvfcvth.d.s",
"xvffint.s.w",
"xvffint.s.wu",
"xvffint.d.l",
"xvffint.d.lu",
"xvffintl.d.w",
"xvffinth.d.w",
"xvftint.w.s",
"xvftint.l.d",
"xvftintrm.w.s",
"xvftintrm.l.d",
"xvftintrp.w.s",
"xvftintrp.l.d",
"xvftintrz.w.s",
"xvftintrz.l.d",
"xvftintrne.w.s",
"xvftintrne.l.d",
"xvftint.wu.s",
"xvftint.lu.d",
"xvftintrz.wu.s",
"xvftintrz.lu.d",
"xvftintl.l.s",
"xvftinth.l.s",
"xvftintrml.l.s",
"xvftintrmh.l.s",
"xvftintrpl.l.s",
"xvftintrph.l.s",
"xvftintrzl.l.s",
"xvftintrzh.l.s",
"xvftintrnel.l.s",
"xvftintrneh.l.s",
"xvexth.h.b",
"xvexth.w.h",
"xvexth.d.w",
"xvexth.q.d",
"xvexth.hu.bu",
"xvexth.wu.hu",
"xvexth.du.wu",
"xvexth.qu.du",
"xvreplve0.b",
"xvreplve0.h",
"xvreplve0.w",
"xvreplve0.d",
"xvreplve0.q",
"xvextl.q.d",
"xvextl.qu.du",
"vext2xv.h.b",
"vext2xv.w.b",
"vext2xv.d.b",
"vext2xv.w.h",
"vext2xv.d.h",
"vext2xv.d.w",
"vext2xv.hu.bu",
"vext2xv.wu.bu",
"vext2xv.du.bu",
"vext2xv.wu.hu",
"vext2xv.du.hu",
"vext2xv.du.wu"
	  ), 
	OPS(XVREG, XVREG) );
  
  void putDataProc_2R() {
    putDataProc_XR_GR();
    putDataProc_2VR();
    putDataProc_2XR();
  }

/*****************************************************************/
  PUT1( DataProc_XR_CFR, 
        NM(
"xvseteqz.v",
"xvsetnez.v",
"xvsetanyeqz.b",
"xvsetanyeqz.h",
"xvsetanyeqz.w",
"xvsetanyeqz.d",
"xvsetallnez.b",
"xvsetallnez.h",
"xvsetallnez.w",
"xvsetallnez.d"
	  ), 
	OPS(IMM3BIT_FCC, XVREG) );
 
  PUT1( DataProc_XR_SI13, NM("xvldi"), OPS(XVREG, IMM13BIT_S) );

  void putDataProc_1R_1I() {
    putDataProc_XR_CFR();
    putDataProc_XR_SI13();
  }

/*****************************************************************/

  PUT1( DataProc_1R_2I, NM("xvmepatmsk.v"), OPS(XVREG, IMM5BIT, IMM5BIT) );

/*****************************************************************/
  void put() {
    putDataProc_4R();
    putDataProc_4VR();
    putDataProc_2R_1I();
    putDataProc_2R_2I();
    putDataProc_3R();
    putDataProc_2R();
    putDataProc_1R_1I();
    putDataProc_1R_2I();
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

