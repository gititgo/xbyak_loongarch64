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
#define TEST_NUM 1011

#include "../xbyak_loongarch64/xbyak_loongarch64.h"
#include <cstring>

using namespace Xbyak_loongarch64;

class GeneratorAdd : public CodeGenerator {

  template <typename T> void genAddFuncCore(const T imm) {
    add_imm(v0, a0, imm, t0); // t0 are temporary registers.
    jirl(zero, ra, 0);
  }

public:
  template <typename T> GeneratorAdd(T i) { genAddFuncCore(i); }
};

class GeneratorSub : public CodeGenerator {

  template <typename T> void genSubFuncCore(const T imm) {
    sub_imm(v0, a0, imm, t0); // t0 are temporary registers.
    jirl(zero, ra, 0);
  }

public:
  template <typename T> GeneratorSub(T i) { genSubFuncCore(i); }
};

template <typename T> void test_add(std::vector<T> &v) {

  for (const auto &e : v) {
    GeneratorAdd s(e);
    s.ready();
    uint64_t (*f)(T a) = (uint64_t(*)(T a))s.getCode();
    //s.dump();
    uint64_t retVal = f(TEST_NUM);

    if (typeid(e) == typeid(int32_t) || typeid(e) == typeid(int64_t)) {
      int64_t tmp = TEST_NUM + static_cast<int64_t>(e);
      //    std::cout << std::hex << "e  :" << e << std::endl;
      //    std::cout << std::hex << "tmp:" << tmp << std::endl;
      //    std::cout << std::hex << "ret:" << retVal << std::endl;
      if (std::memcmp(&retVal, &tmp, sizeof(uint64_t)) == 0) {
        //printf("test add signed ok!\n");
      } else {
        printf("test add signed fail!\n");
        std::cout << "add:" << TEST_NUM << " + " << e << " = "
                << static_cast<int64_t>(retVal) << std::endl;
      }
    } else {
      uint64_t tmp = TEST_NUM + static_cast<uint64_t>(e);
      //    std::cout << std::hex << "e  :" << e << std::endl;
      //    std::cout << std::hex << "tmp:" << tmp << std::endl;
      //    std::cout << std::hex << "ret:" << retVal << std::endl;
      if (std::memcmp(&retVal, &tmp, sizeof(uint64_t)) == 0) {
        //printf("test add unsigned ok!\n");
      } else {
        printf("test add unsigned fail!\n");
        std::cout << "add:" << TEST_NUM << " + " << e << " = "
                << static_cast<int64_t>(retVal) << std::endl;
      }
    }
  }
}

template <typename T> void test_sub(std::vector<T> &v) {

  for (const auto &e : v) {
    GeneratorSub s(e);
    s.ready();
    uint64_t (*f)(T a) = (uint64_t(*)(T a))s.getCode();
    //s.dump();
    uint64_t retVal = f(TEST_NUM);

    if (typeid(e) == typeid(int32_t) || typeid(e) == typeid(int64_t)) {
      int64_t tmp = TEST_NUM - static_cast<int64_t>(e);
      //    std::cout << std::hex << "e  :" << e << std::endl;
      //    std::cout << std::hex << "tmp:" << tmp << std::endl;
      //    std::cout << std::hex << "ret:" << retVal << std::endl;
      
      if (std::memcmp(&retVal, &tmp, sizeof(uint64_t)) == 0) {
        //printf("test sub signed ok!\n");
      } else {
        printf("test sub signed fail!\n");
        std::cout << "sub:" << TEST_NUM << " - " << e << " = "
                << static_cast<int64_t>(retVal) << std::endl;
      }
    } else {
      uint64_t tmp = TEST_NUM - static_cast<uint64_t>(e);
      //    std::cout << std::hex << "e  :" << e << std::endl;
      //    std::cout << std::hex << "tmp:" << tmp << std::endl;
      //    std::cout << std::hex << "ret:" << retVal << std::endl;
      if (std::memcmp(&retVal, &tmp, sizeof(uint64_t)) == 0) {
        //printf("test sub unsigned ok!\n");
      } else {
        printf("test sub unsigned fail!\n");
        std::cout << "sub:" << TEST_NUM << " - " << e << " = "
                << static_cast<int64_t>(retVal) << std::endl;
      }
    }
  }
}

int main() {

  std::vector<int32_t> v_int32 = {std::numeric_limits<int32_t>::min(),
                                  std::numeric_limits<int32_t>::min() + 1,
                                  -2048,
                                  -2047,
                                  -2046,
                                  -1,
                                  0,
                                  1,
                                  2046,
                                  2047,
                                  2048,
                                  std::numeric_limits<int32_t>::max() - 1,
                                  std::numeric_limits<int32_t>::max()};

  std::vector<uint32_t> v_uint32 = {0,
                                    1,
                                    2046,
                                    2047,
                                    2048,
                                    2049,
                                    std::numeric_limits<uint32_t>::max() - 1,
                                    std::numeric_limits<uint32_t>::max()};

  std::vector<int64_t> v_int64 = {std::numeric_limits<int64_t>::min(),
                                  std::numeric_limits<int64_t>::min() + 1,
                                  -2048,
                                  -2047,
                                  -2046,
                                  -1,
                                  0,
                                  1,
                                  2046,
                                  2047,
                                  2048,
                                  std::numeric_limits<int64_t>::max() - 1,
                                  std::numeric_limits<int64_t>::max()};

  std::vector<uint64_t> v_uint64_t = {0,
                                      1,
                                      2046,
                                      2047,
                                      2048,
                                      2049,
                                      std::numeric_limits<uint64_t>::max() - 1,
                                      std::numeric_limits<uint64_t>::max()};

  test_add(v_int32);
  test_add(v_uint32);
  test_add(v_int64);
  test_add(v_uint64_t);

  test_sub(v_int32);
  test_sub(v_uint32);
  test_sub(v_int64);
  test_sub(v_uint64_t);

  return 0;
}
