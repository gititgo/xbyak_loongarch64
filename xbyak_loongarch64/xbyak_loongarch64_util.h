#pragma once
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
#ifndef XBYAK_LOONGARCH_UTIL_H_
#define XBYAK_LOONGARCH_UTIL_H_

#include <stdint.h>
#ifdef __linux__
#include <sys/prctl.h>
#endif

#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/resource.h>
#include "xbyak_loongarch64_err.h"

namespace Xbyak_loongarch64 {
namespace util {

enum simdLen_t {
  SIMD_NONE = 0,
  LSX_MASK = 1<<6,
  LASX_MASK = 1<<7
};

/**
   CPU detection class
*/
class Cpu {
  uint64_t type_;
  simdLen_t simdLen_;

public:
  typedef uint64_t Type;

  static const Type tNONE = 0;
  static const Type tLSX = 1 << 0;
  static const Type tLASX = 1 << 1;

  int g__fd[2];
  int g_support_cpucfg;

  static void handler(int signum) {
    close(signum);
    exit(1);
  }


  int cpucfg_test(void) {
    pid_t pid;
    int status = 0;

    g_support_cpucfg = 0;
    status = pipe(g__fd);
    if (status != 0) {
        printf("xbyak util pipe failed!\n");
    }
    pid = fork();
    if (pid == 0) { /* Subprocess */
        struct sigaction act;
        close(g__fd[0]);
        /* Set signal action for SIGILL. */
        act.sa_handler = Cpu::handler;
        sigaction(SIGILL, &act, NULL);

        /* Execute cpucfg in subprocess. */
        __asm__ volatile(
            "cpucfg $t0, $zero    \n\t"
            :::
        );
        g_support_cpucfg = 1;
        if (-1 == write(g__fd[1], &g_support_cpucfg, sizeof(g_support_cpucfg))) {
            printf("xbyak util write error!\n");
        }
        close(g__fd[1]);
        exit(0);
    } else if (pid > 0) { /* Parent process*/
        close(g__fd[1]);
        if ((waitpid(pid, &status, 0) <= 0) ||
            (read(g__fd[0], &g_support_cpucfg, sizeof(g_support_cpucfg)) <= 0))
            g_support_cpucfg = 0;
        close(g__fd[0]);
    } else {
        g_support_cpucfg = 0;
    }

    return g_support_cpucfg;
  }

  uint64_t get_cpu_flags_from_cpucfg() {
      uint64_t flags = 0;
      int flag = 0;
      __asm__ volatile(
          "addi.d $a6, $zero, 0x02        \n\t"
          "cpucfg $a7, $a6        \n\t"
          "st.w   $a7, %0, 0x00   \n\t"
          :
          : "r"(&flag)
          : "memory"
      );
      if (flag & LSX_MASK)
          flags |= tLSX;
      if (flag & LASX_MASK)
          flags |= tLASX;
      //printf("flags by cpucfg is %ld\n", flags);
      return flags;
  }

  uint64_t get_cpu_flags_from_cpuinfo(void) {
      uint64_t flags = 0;
      char buf[1024];

#ifdef __linux__
      FILE* fp = fopen("/proc/cpuinfo", "r");
      if (!fp)
          return flags;

      memset(buf, 0, sizeof(buf));
      if (0 == fread(buf, sizeof(char), sizeof(buf) - 1, fp)) {
          printf("xbyak util fread error!\n");
      }
      fclose(fp);
      if (strstr(buf, "3A5000")) {
          flags |= tLASX | tLSX;
      }
      //printf("flags by /proc/cpuinfo is %ld\n", flags);
#endif
      return flags;
  }

  Cpu() : type_(tNONE), simdLen_(LASX_MASK) {
    int ret = cpucfg_test();
    if (ret == 1)
        type_ = get_cpu_flags_from_cpucfg();
    else
        type_ = get_cpu_flags_from_cpuinfo();
  }

  Type getType() const { return type_; }
  bool has(Type type) const { return (type & type_) != 0; }
  uint64_t getSimdLen() const { return simdLen_; }
  bool isLasxSupported() const { return type_ & tLASX; }
  bool isLsxSupported() const { return type_ & tLSX; }
  //bool isAtomicSupported() const { return type_ & tATOMIC; }
  bool isAtomicSupported() const { return isLasxSupported(); }
};
} // namespace util
} // namespace Xbyak_loongarch64
#endif
