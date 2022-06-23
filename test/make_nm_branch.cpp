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

uint64_t flagBit = 0;
const uint64_t WREG = flagBit++;  /** Test vector is {w0, w1, ..., w30 } */
const uint64_t XREG = flagBit++;  /** Test vector is {x0, x1, ..., x30 } */
const uint64_t XREG2 = flagBit++; /** Test vector is {x0, x1, ..., x30 } */
const uint64_t WSP = flagBit++;   /** Test vector is {wsp} */
const uint64_t XSP = flagBit++;   /** Test vector is {sp} */
const uint64_t XNSP = flagBit++;
const uint64_t XNSP2 = flagBit++;
const uint64_t XNSP3 = flagBit++;

const uint64_t WNZR = flagBit++; /** Test vector is {w0, w1, ..., w30, wzr } */
const uint64_t XNZR = flagBit++; /** Test vector is {x0, x1, ..., x30, xzr } */

const uint64_t IMM1BIT = flagBit++; /** Test vector is {0, 1 } */
const uint64_t IMM2BIT = flagBit++; /** Test vector is {0, 1, ..., 3 } */
const uint64_t IMM3BIT = flagBit++; /** Test vector is {0, 1, ..., 7 } */
const uint64_t IMM3BIT_FCC = flagBit++; /** Test vector is {0, 1, 2, 4, 7} */
const uint64_t IMM4BIT = flagBit++; /** Test vector is {0, 1, ..., 8, 15 } */
const uint64_t IMM5BIT = flagBit++; /** Test vector is {0, 1, ..., 31 } */
const uint64_t IMM6BIT = flagBit++; /** Test vector is {0, 1, ..., 63 } */
const uint64_t IMM7BIT = flagBit++; /** Test vector is {0, 1, ..., 127 } */
const uint64_t IMM16BIT =
    flagBit++; /** Test vector is {0, 1, ..., 2048, 4095 } */
const uint64_t UIMM16BIT = flagBit++; /** Test vector is {0, 1, ..., 4096, 1<<13,
                                        1<<14, 1<<15, 1<<16-1 } */
const uint64_t IMM9BIT_PM =
    flagBit++; /** Test vector is {-256, -255, ..., 255 } */
const uint64_t IMM7BIT_MUL4 =
    flagBit++; /** Test vector is { 0, 4, 8, ..., 127*4 } */
const uint64_t IMM7BIT_MUL8 =
    flagBit++; /** Test vector is { 0, 8, 16, ..., 127*8 } */
const uint64_t IMM7BIT_MUL16 =
    flagBit++; /** Test vector is { -256, -252, ..., 252 } */
const uint64_t IMM7BIT_PM_MUL4 = flagBit++;
const uint64_t IMM7BIT_PM_MUL8 = flagBit++;
const uint64_t IMM7BIT_PM_MUL16 =
    flagBit++; /** Test vector is { 0, 16, 32, ..., 127*16 } */
const uint64_t IMM10BIT_PM_MUL8 = flagBit++;
const uint64_t IMM12BIT_MUL2 =
    flagBit++; /** Test vector is {0, 4, 8, ..., 8190 } */
const uint64_t IMM12BIT_MUL4 =
    flagBit++; /** Test vector is {0, 4, 8, ..., 16380 } */
const uint64_t IMM12BIT_MUL8 =
    flagBit++; /** Test vector is {0, 8, 16, ..., 32760 } */
const uint64_t IMM12BIT_MUL16 =
    flagBit++; /** Test vector is {0, 16, 32, ..., 65320 } */
const uint64_t IMM14BIT_MUL4 = flagBit++;
const uint64_t IMM16BIT_MUL4 = flagBit++;
const uint64_t IMM20BIT_MUL4 = flagBit++;
const uint64_t IMM21BIT_MUL4 =
    flagBit++; /** Test vector is {-2^19*4, ...., (2^19-1)*4 } */
const uint64_t IMM26BIT_MUL4 = flagBit++;

const uint64_t NOPARA = 100000;

#define PUT0(name, nm)                                                         \
  void put##name() const {                                                     \
    std::vector<std::string> nemonic(nm);                                      \
    put(nemonic, #name, 0);                                                    \
  }

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

  std::vector<std::string> tv_WREG = {"$zero", "$t1", "$v0", "$a0", "$a4", "$s0", "$ra", "$a7", "$s3", "$t6"};
  std::vector<std::string> tv_XREG = {"$f1", "$f2", "$f5", "$f7", "$f8", "$f9", "$f20", "$f31"};
  std::vector<std::string> tv_XREG2 = {"$f4", "$f12", "$f14", "$f15", "$f19", "$f22", "$f25", "$f26"};
  std::vector<std::string> tv_WSP = {"$sp"};
  std::vector<std::string> tv_XSP = {"$sp"};
  std::vector<std::string> tv_XNSP = {"x7", "x0",  "x1",  "x2", "x4",
                                      "x8", "x16", "x30", "sp"};
  std::vector<std::string> tv_XNSP2 = {"x3", "x0",  "x1",  "x2", "x4",
                                       "x8", "x16", "x30", "sp"};
  std::vector<std::string> tv_XNSP3 = {"x5", "x15", "x29"};
  std::vector<std::string> tv_WNZR = {"w7", "w0",  "w1",  "w2", "w4",
                                      "w8", "w16", "w30", "wzr"};
  std::vector<std::string> tv_XNZR = {"x3", "x0",  "x1",  "x2", "x4",
                                      "x8", "x16", "x30", "xzr"};
  std::vector<std::string> tv_IMM1BIT = {"1", "0"};
  std::vector<std::string> tv_IMM2BIT = {"1", "0", "1", "2"};
  std::vector<std::string> tv_IMM3BIT = {"3", "0", "1", "2", "4", "7"};
  std::vector<std::string> jtv_IMM3BIT_FCC = {"3", "0", "1", "2", "4", "7"};
  std::vector<std::string> tv_IMM3BIT_FCC = {"$fcc3", "$fcc0", "$fcc1", "$fcc2", "$fcc4", "$fcc7"};
  std::vector<std::string> tv_IMM4BIT = {"7", "0", "1", "2", "4", "8", "15"};
  std::vector<std::string> tv_IMM5BIT = {"7", "0", "1",  "2",
                                         "4", "8", "16", "31"};
  std::vector<std::string> tv_IMM6BIT = {"7", "0",  "1",  "2", "4",
                                         "8", "16", "32", "63"};
  std::vector<std::string> tv_IMM7BIT = {"63", "0",  "1",  "2",  "4",
                                         "8",  "16", "32", "64", "127"};
  std::vector<std::string> tv_IMM16BIT = {
      "0x2aa", "0",   "1",   "2",   "4",    "-8",    "16",  "32",
      "64",    "128", "256", "-512", "1024", "2048", "-4095"};
  std::vector<std::string> tv_UIMM16BIT = {
      "0xe38e", "0",    "1",     "2",     "4",        "8",    "16",
      "32",     "64",   "128",   "256",   "512",      "1024", "2048",
      "4096",   "8191", "1<<14", "1<<15", "(1<<16)-1"};
  std::vector<std::string> tv_IMM9BIT_PM = {
      "127", "-256", "-128", "-64", "-32", "-16", "-8", "-4", "-2",  "-1",
      "0",   "1",    "2",    "4",   "8",   "16",  "32", "64", "128", "255"};
  std::vector<std::string> tv_IMM7BIT_MUL4, tv_IMM7BIT_MUL8, tv_IMM7BIT_MUL16;
  std::vector<std::string> tv_IMM7BIT_PM_MUL4, tv_IMM7BIT_PM_MUL8, tv_IMM7BIT_PM_MUL16;
  std::vector<std::string> tv_IMM10BIT_PM_MUL8;
  std::vector<std::string> tv_IMM12BIT_MUL2, tv_IMM12BIT_MUL4, tv_IMM12BIT_MUL8, tv_IMM12BIT_MUL16;
  std::vector<std::string> tv_IMM14BIT_MUL4;
  std::vector<std::string> tv_IMM16BIT_MUL4;
  std::vector<std::string> tv_IMM20BIT_MUL4;
  std::vector<std::string> tv_IMM21BIT_MUL4;
  std::vector<std::string> tv_IMM26BIT_MUL4;

  std::vector<std::vector<std::string> *> tv_VectorsAs = {&tv_WREG,
                                                          &tv_XREG,
                                                          &tv_XREG2,
                                                          &tv_WSP,
                                                          &tv_XSP,
                                                          &tv_XNSP,
                                                          &tv_XNSP2,
                                                          &tv_XNSP3,
                                                          &tv_WNZR,
                                                          &tv_XNZR,
                                                          &tv_IMM1BIT,
                                                          &tv_IMM2BIT,
                                                          &tv_IMM3BIT,
                                                          &tv_IMM3BIT_FCC,
                                                          &tv_IMM4BIT,
                                                          &tv_IMM5BIT,
                                                          &tv_IMM6BIT,
                                                          &tv_IMM7BIT,
                                                          &tv_IMM16BIT,
                                                          &tv_UIMM16BIT,
                                                          &tv_IMM9BIT_PM,
                                                          &tv_IMM7BIT_MUL4,
                                                          &tv_IMM7BIT_MUL8,
                                                          &tv_IMM7BIT_MUL16,
                                                          &tv_IMM7BIT_PM_MUL4,
                                                          &tv_IMM7BIT_PM_MUL8,
                                                          &tv_IMM7BIT_PM_MUL16,
                                                          &tv_IMM10BIT_PM_MUL8,
                                                          &tv_IMM12BIT_MUL2,
                                                          &tv_IMM12BIT_MUL4,
                                                          &tv_IMM12BIT_MUL8,
                                                          &tv_IMM12BIT_MUL16,
                                                          &tv_IMM14BIT_MUL4,
                                                          &tv_IMM16BIT_MUL4,
                                                          &tv_IMM20BIT_MUL4,
                                                          &tv_IMM21BIT_MUL4,
                                                          &tv_IMM26BIT_MUL4};

  std::vector<std::vector<std::string> *> tv_VectorsJit = {&tv_WREG,
                                                           &tv_XREG,
                                                           &tv_XREG2,
                                                           &tv_WSP,
                                                           &tv_XSP,
                                                           &tv_XNSP,
                                                           &tv_XNSP2,
                                                           &tv_XNSP3,
                                                           &tv_WNZR,
                                                           &tv_XNZR,
                                                           &tv_IMM1BIT,
                                                           &tv_IMM2BIT,
                                                           &tv_IMM3BIT,
                                                           &jtv_IMM3BIT_FCC,
                                                           &tv_IMM4BIT,
                                                           &tv_IMM5BIT,
                                                           &tv_IMM6BIT,
                                                           &tv_IMM7BIT,
                                                           &tv_IMM16BIT,
                                                           &tv_UIMM16BIT,
                                                           &tv_IMM9BIT_PM,
                                                           &tv_IMM7BIT_MUL4,
                                                           &tv_IMM7BIT_MUL8,
                                                           &tv_IMM7BIT_MUL16,
                                                           &tv_IMM7BIT_PM_MUL4,
                                                           &tv_IMM7BIT_PM_MUL8,
                                                           &tv_IMM7BIT_PM_MUL16,
                                                           &tv_IMM10BIT_PM_MUL8,
                                                           &tv_IMM12BIT_MUL2,
                                                           &tv_IMM12BIT_MUL4,
                                                           &tv_IMM12BIT_MUL8,
                                                           &tv_IMM12BIT_MUL16,
                                                           &tv_IMM14BIT_MUL4,
                                                           &tv_IMM16BIT_MUL4,
                                                           &tv_IMM20BIT_MUL4,
                                                           &tv_IMM21BIT_MUL4,
                                                           &tv_IMM26BIT_MUL4};

  std::vector<std::vector<std::string> *> &tv_Vectors = tv_VectorsAs;

  bool isRequireComma(int num_ops, int idx, std::string curr,
                      std::string next) const {
    if (idx == num_ops - 1) { /** Last operand isn't followed by ",". */
      return false;
    }

    if (curr == "" || curr == "[" || curr == "ptr(" || curr == "{" ||
        curr == "(" ) {
      return false;
    }

    if (next == "]" || next == ")" || next == "}" || next == "]!") {
      return false;
    }

    return true;
  }

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

  void put(std::vector<std::string> &n, std::string name,
           int serial = 0) const {
    if( 0 ) {
      std::cout << "#" << name << ":" << serial << std::endl; /** For easy debug */
    }
    for (std::string i : n) {
      const std::string nm = removeUnderScore(i);
      if (isXbyak_) {
        std::cout << nm << "();";
      } else {
        std::cout << nm << std::endl;
      }
    }
  }

  void put(std::vector<std::string> &n, std::vector<uint64_t> &opSet,
           std::string name, int serial = 0) const {
    if( 0 ) {
      std::cout << "#" << name << ":" << serial << std::endl; /** For easy debug */
    }
    for (size_t i = 0; i < n.size(); i++) {
      const std::string nm = replaceDotWithUnderScore(n[i]);
      put(nm.c_str(), opSet);
    }
  }

  //  char* getBaseStr(uint64_t op1)
  const char *getBaseStr(uint64_t op1) const { return get(op1, (uint64_t)0); }

  /** check all op1, op2, op3, op4, op5, op6, op7, op8 */
  void put(const char *nm, std::vector<uint64_t> &ops) const {
    std::vector<std::string> strBase;
    std::string hoge;
    int i, k;
    uint jj;
    int num_ops = ops.size();

    for (i = 0; i < num_ops; i++) {
      strBase.push_back(getBaseStr(ops[i]));
    }

    /** No operand exists. */
    if (num_ops == 0) {
      std::cout << nm << " ";

      if (isXbyak_) {
        std::cout << "();";
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
      for (jj = 0; jj < getNum(ops[i]); jj++) {
        /** print nemonic */
        std::cout << nm;
        if (isXbyak_) {
          std::cout << "(";
        } else {
          std::cout << " ";
        }

        /** Print 0 - (i-1)th operand */
        for (k = 0; k < i; k++) {
          std::string tmp = removeDollar(strBase[k]);
          std::string nextStr = "";
          std::cout << tmp;

          if (k + 1 < num_ops) {
            nextStr = removeDollar(strBase[k + 1]);
          }
          if (isRequireComma(num_ops, k, tmp, nextStr)) {
            std::cout << ", ";
          } else {
            std::cout << " ";
          }
        }

        /** Print i-th operand, which is rotated. */
        {
          std::string tmp = removeDollar(get(ops[i], jj));
          std::string nextStr = "";
          std::cout << removeDollar(get(ops[i], jj));

          if (i + 1 < num_ops) {
            nextStr = removeDollar(strBase[i + 1]);
          }
          if (isRequireComma(num_ops, i, tmp, nextStr)) {
            std::cout << ", ";
          } else {
            std::cout << " ";
          }
        }

        /** Print (i+1) to (num_ops-1)-th operand */
        for (k = i + 1; k < num_ops; k++) {
          std::string tmp = removeDollar(strBase[k]);
          std::string nextStr = "";
          std::cout << tmp;

          if (k + 1 < num_ops) {
            nextStr = removeDollar(strBase[k + 1]);
          }

          if (isRequireComma(num_ops, k, tmp, nextStr)) {
            std::cout << ", ";
          } else {
            std::cout << " ";
          }
        }

        if (isXbyak_) {
          std::cout << "); dump();";
        }

        std::cout << std::endl;
      }
    }
  }

  uint64_t getNum(uint64_t type) const {
    if (type == NOPARA) {
      return 0;
    }

    return tv_Vectors[type]->size();
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

    return tv_Vectors[type]->at(index).c_str();
  }

  void initTv() {
    initTvIMM12BIT();
    initTvIMM7BIT();
    initTvIMM7BIT_PM();
    initTvIMM14BIT();
    initTvIMM10BIT();
    initTvIMM16BIT();
    initTvIMM20BIT();
    initTvIMM21BIT();
    initTvIMM26BIT();
  }

  void initTvIMM12BIT() {
    std::vector<int> tmp = {1023, 0,   1,   2,   4,    8,    16,  32,
                            64,   128, 256, 512, 1024, 2048, 4095};
    tv_IMM12BIT_MUL2.clear();
    tv_IMM12BIT_MUL4.clear();
    tv_IMM12BIT_MUL8.clear();
    tv_IMM12BIT_MUL16.clear();

    for (int i : tmp) {
      tv_IMM12BIT_MUL2.push_back(std::to_string(i * 2));
      tv_IMM12BIT_MUL4.push_back(std::to_string(i * 4));
      tv_IMM12BIT_MUL8.push_back(std::to_string(i * 8));
      tv_IMM12BIT_MUL16.push_back(std::to_string(i * 16));
    }
  }

  void initTvIMM7BIT() {
    std::vector<int> tmp = {127, 0, 1, 2, 4, 8, 16, 32, 64, 128, 255};
    tv_IMM7BIT_MUL4.clear();
    tv_IMM7BIT_MUL8.clear();
    tv_IMM7BIT_MUL16.clear();

    for (int i : tmp) {
      tv_IMM7BIT_MUL4.push_back(std::to_string(i * 4));
      tv_IMM7BIT_MUL8.push_back(std::to_string(i * 8));
      tv_IMM7BIT_MUL16.push_back(std::to_string(i * 16));
    }
  }

  void initTvIMM7BIT_PM() {
    std::vector<int> tmp = {63, -64, -32, -16, -8, -4, -2, -1,
                            0,  1,   2,   4,   8,  16, 32};
    tv_IMM7BIT_PM_MUL4.clear();
    tv_IMM7BIT_PM_MUL8.clear();
    tv_IMM7BIT_PM_MUL16.clear();

    for (int i : tmp) {
      tv_IMM7BIT_PM_MUL4.push_back(std::to_string(i * 4));
      tv_IMM7BIT_PM_MUL8.push_back(std::to_string(i * 8));
      tv_IMM7BIT_PM_MUL16.push_back(std::to_string(i * 16));
    }
  }

  void initTvIMM10BIT() {
    tv_IMM10BIT_PM_MUL8.clear();

    tv_IMM10BIT_PM_MUL8.push_back("8*((1<<6)-1)");

    for (int i = 9; i >= 0; i--) {
      tv_IMM10BIT_PM_MUL8.push_back("-8*(1<<" + std::to_string(i) + ")");
    }

    tv_IMM10BIT_PM_MUL8.push_back("0");

    for (int i = 0; i < 9; i++) {
      tv_IMM10BIT_PM_MUL8.push_back("8*(1<<" + std::to_string(i) + ")");
    }

    tv_IMM10BIT_PM_MUL8.push_back("8*((1<<9)-1)");
  }

  void initTvIMM14BIT() {
    tv_IMM14BIT_MUL4.clear();

    tv_IMM14BIT_MUL4.push_back("4*((1<<10)-1)");

    for (int i = 13; i >= 0; i--) {
      tv_IMM14BIT_MUL4.push_back("-4*(1<<" + std::to_string(i) + ")");
    }

    tv_IMM14BIT_MUL4.push_back("0");

    for (int i = 0; i < 13; i++) {
      tv_IMM14BIT_MUL4.push_back("4*(1<<" + std::to_string(i) + ")");
    }

    tv_IMM14BIT_MUL4.push_back("4*((1<<13)-1)");

    /** Debug
        for(std::string i : tv_IMM14BIT_MUL4) {
        std::cout << "IMM14BIT_MUL4=" << i << std::endl;
        }
    */
  }

  void initTvIMM16BIT() {
    tv_IMM16BIT_MUL4.clear();

    tv_IMM16BIT_MUL4.push_back("4*((1<<13)-1)");

    for (int i = 15; i >= 0; i--) {
      tv_IMM16BIT_MUL4.push_back("-4*(1<<" + std::to_string(i) + ")");
    }

    tv_IMM16BIT_MUL4.push_back("0");

    for (int i = 0; i < 15; i++) {
      tv_IMM16BIT_MUL4.push_back("4*(1<<" + std::to_string(i) + ")");
    }

    tv_IMM16BIT_MUL4.push_back("4*((1<<15)-1)");

    /** Debug
        for(std::string i : tv_IMM16BIT_MUL4) {
        std::cout << "IMM16BIT_MUL4=" << i << std::endl;
        }
    */
  }

  void initTvIMM20BIT() {
    tv_IMM20BIT_MUL4.clear();

    tv_IMM20BIT_MUL4.push_back("4*((1<<14)-1)");

    for (int i = 16; i >= 0; i--) {
      tv_IMM20BIT_MUL4.push_back("-4*(1<<" + std::to_string(i) + ")");
    }

    tv_IMM20BIT_MUL4.push_back("0");

    for (int i = 0; i < 16; i++) {
      tv_IMM20BIT_MUL4.push_back("4*(1<<" + std::to_string(i) + ")");
    }

    tv_IMM20BIT_MUL4.push_back("4*((1<<15)-1)");

    /** Debug
        for(std::string i : tv_IMM20BIT_MUL4) {
        std::cout << "IMM20BIT_MUL4=" << i << std::endl;
        }
    */
  }

  void initTvIMM21BIT() {
    tv_IMM21BIT_MUL4.clear();

    tv_IMM21BIT_MUL4.push_back("4*((1<<16)-1)");

    for (int i = 20; i >= 0; i--) {
      tv_IMM21BIT_MUL4.push_back("-4*(1<<" + std::to_string(i) + ")");
    }

    tv_IMM21BIT_MUL4.push_back("0");

    for (int i = 0; i < 20; i++) {
      tv_IMM21BIT_MUL4.push_back("4*(1<<" + std::to_string(i) + ")");
    }

    tv_IMM21BIT_MUL4.push_back("4*((1<<20)-1)");

    /** Debug
        for(std::string i : tv_IMM21BIT_MUL4) {
        std::cout << "IMM21BIT_MUL4=" << i << std::endl;
        }
    */
  }

  void initTvIMM26BIT() {
    tv_IMM26BIT_MUL4.clear();

    tv_IMM26BIT_MUL4.push_back("4*((1<<16)-1)");

    for (int i = 25; i >= 0; i--) {
      tv_IMM26BIT_MUL4.push_back("-4*(1<<" + std::to_string(i) + ")");
    }

    tv_IMM26BIT_MUL4.push_back("0");

    for (int i = 0; i < 25; i++) {
      tv_IMM26BIT_MUL4.push_back("4*(1<<" + std::to_string(i) + ")");
    }

    tv_IMM26BIT_MUL4.push_back("4*((1<<25)-1)");
  }

public:
  Test(bool isXbyak) : isXbyak_(isXbyak), funcNum_(1) {

    initTv();

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

  std::string removeDollar(std::string s) const {
    if (isXbyak_ && s[0] == '$')
      return s.substr(1);

    return s;
  }

  PUT1(Undinditional_branch0, NM("beqz", "bnez"), OPS(WREG, IMM21BIT_MUL4));
  PUT1(Undinditional_branch1, NM("bceqz", "bcnez"), OPS(IMM3BIT_FCC, IMM21BIT_MUL4));
  PUT1(Undinditional_branch2, NM("b", "bl"), OPS(IMM26BIT_MUL4));
  PUT1(Undinditional_branch3, NM("jirl", "beq", "bne", "blt", "bge", "bltu", "bgeu"), OPS(WREG, WREG, IMM16BIT_MUL4));
  PUT1(Undinditional_branch4, NM("ldptr.w", "ll.w", "sc.w", "ll.d", "sc.d", "stptr.w", "ldptr.d", "stptr.d"), OPS(WREG, WREG, IMM14BIT_MUL4));

  void putUndinditional_branch_core() {
    putUndinditional_branch0();
    putUndinditional_branch1();
    putUndinditional_branch2();
    putUndinditional_branch3();
    putUndinditional_branch4();
  }

  void putUndinditional_branch() { putUndinditional_branch_core(); }

  void put() {
    putUndinditional_branch();

    //    Ops hoge();
    //    hoge.pushNm({"add", "sub"});
  }
};

int main(int argc, char *[]) {
  Test test(argc > 1);
  test.put();
}
