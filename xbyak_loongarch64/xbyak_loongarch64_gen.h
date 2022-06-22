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
#include "xbyak_loongarch64_adr.h"
#include "xbyak_loongarch64_code_array.h"
#include "xbyak_loongarch64_err.h"
#include "xbyak_loongarch64_label.h"
#include "xbyak_loongarch64_reg.h"

enum CondFlagReg { 
  fcc0 = 0,
  fcc1 = 1,
  fcc2 = 2,
  fcc3 = 3,
  fcc4 = 4,
  fcc5 = 5,
  fcc6 = 6,
  fcc7 = 7
};

class CodeGenerator : public CodeArray {

  LabelManager labelMgr_;

  // ################### check function #################
  // check val (list)
  template <typename T> bool chkVal(T val, const std::initializer_list<T> &list) {
    return std::any_of(list.begin(), list.end(), [=](T x) { return x == val; });
  }

  // check val (range)
  template <typename T> bool chkVal(T val, T min, T max) { return (min <= val && val <= max); }

  // check val (condtional func)
  template <typename T> bool chkVal(T val, const std::function<bool(T)> &func) { return func(val); }

  // verify (include range)
  void verifyIncRange(uint64_t val, uint64_t min, uint64_t max, int err_type, bool to_i = false) {
    if (to_i && !chkVal((int64_t)val, (int64_t)min, (int64_t)max)) {
      throw Error(err_type);
    } else if (!to_i && !chkVal(val, min, max)) {
      throw Error(err_type);
    }
  }

  // verify (not include range)
  void verifyNotIncRange(uint64_t val, uint64_t min, uint64_t max, int err_type, bool to_i = false) {
    if (to_i && chkVal((uint64_t)val, (uint64_t)min, (uint64_t)max)) {
      throw Error(err_type);
    } else if (!to_i && chkVal(val, min, max)) {
      throw Error(err_type);
    }
  }

  // verify (include list)
  void verifyIncList(uint64_t val, const std::initializer_list<uint64_t> &list, int err_type) {
    if (!chkVal(val, list)) {
      throw Error(err_type);
    }
  }

  // verify (not include list)
  void verifyNotIncList(uint64_t val, const std::initializer_list<uint64_t> &list, int err_type) {
    if (chkVal(val, list)) {
      throw Error(err_type);
    }
  }

  // verify (conditional function)
  void verifyCond(uint64_t val, const std::function<bool(uint64_t)> &func, int err_type) {
    if (!chkVal(val, func)) {
      throw Error(err_type);
    }
  }

  // verify (conditional function)
  void verifyNotCond(uint64_t val, const std::function<bool(uint64_t)> &func, int err_type) {
    if (chkVal(val, func)) {
      throw Error(err_type);
    }
  }

  // ############### encoding helper function #############
  // generate encoded imm
  uint32_t genNImmrImms(uint64_t imm, uint32_t size);

  // generate relative address for label offset
  uint64_t genLabelOffset(const Label &label, const JmpLabel &jmpL) {
    size_t offset = 0;
    int64_t labelOffset = 0;
    if (labelMgr_.getOffset(&offset, label)) {
      labelOffset = (offset - size_) * CSIZE;
    } else {
      labelMgr_.addUndefinedLabel(label, jmpL);
    }
    return labelOffset;
  }

  // ################## encoding function ##################
  /*LoongArch SIMD begin*/
  template <typename T> 
  void LasxFormat4R(uint32_t op, uint32_t df, const T &ra, const T &rk, const T &rj, const T &rd );
  template <typename T> 
  void LasxFormatCond(uint32_t op, uint32_t df, uint32_t cond, const T &rk, const T &rj, const T &rd );
  template <typename T, typename R> 
  void LasxFormatI12(uint32_t op, int32_t imm, const R &rj, const T &rd );
  template <typename T, typename R>
  void LasxFormatAddr(uint32_t op, uint32_t df, int32_t off, const R &rj, const T &rd );
  template <typename T, typename R>
  void LasxFormatI8ELM(uint32_t op, uint32_t df, uint32_t idx, int32_t imm8, const R &rj, const T &rd );
  template <typename T, typename R>
  void LasxFormat3R(uint32_t op, uint32_t df, const R &rk, const T &rj, const T &rd );
  template <typename T, typename S, typename std::enable_if<std::is_signed<S>::value, std::nullptr_t>::type = nullptr>
  void LasxFormatI5(uint32_t op, uint32_t df, S imm5, const T &rj, const T &rd );
  template <typename T, typename S, typename std::enable_if<std::is_unsigned<S>::value, std::nullptr_t>::type = nullptr>
  void LasxFormatI5(uint32_t op, uint32_t df, S imm5, const T &rj, const T &rd );
  template <typename T, typename R>
  void LasxFormat2R(uint32_t op, uint32_t df, const R &rj, const T &rd );
  template <typename T>
  void LasxFormatBIT(uint32_t op, uint32_t df, uint32_t m, const T &rj, const T &rd);
  template <typename T, typename R> 
  void LasxFormat3RX(uint32_t op, const R &rk, const R &rj, const T &rd );
  template <typename T> 
  void LasxFormat3RVec(uint32_t op, const T &rk, const T &rj, const T &rd );
  template <typename T> 
  void LasxFormatI5Mode(uint32_t op, uint32_t imm5, uint32_t mode, const T &rd );
  template <typename T> 
  void LasxFormatCFR(uint32_t op, uint32_t df, const T &rj, uint32_t cd);
  template <typename T, typename R> 
  void LasxFormatELM(uint32_t op, uint32_t df, uint32_t idx, const T &rj, const R &rd );
  template <typename T, typename R> 
  void LasxFormatELM_1(uint32_t op, uint32_t df, uint32_t idx, const T &rj, const R &rd );
  template <typename T> 
  void LasxFormat2RSubOp(uint32_t op, uint32_t subOp, const T &rj, const T &rd );
  template <typename T> 
  void LasxFormatI8(uint32_t op, uint32_t imm8, const T &rj, const T &rd );
  template <typename T> 
  void LasxFormatI13(uint32_t op, int32_t imm13, const T &rd );
  /*LoongArch SIMD end*/

  /*LoongArch base begin*/
  void Loongarch2Reg(uint32_t opCode, uint32_t rj, uint32_t rd);
  void Loongarch2Reg1Offset(uint32_t opCode, uint32_t rj, uint32_t rd, int32_t offset, int32_t type);
  void Loongarch2Reg2Param(uint32_t opCode, uint32_t msb, uint32_t lsb, uint32_t rj, uint32_t rd, int32_t type);
  void Loongarch3Reg(uint32_t opCode, uint32_t rk, uint32_t rj, uint32_t rd);
  void Loongarch3Reg1Sa(uint32_t opCode, uint32_t sa, uint32_t rk, uint32_t rj, uint32_t rd, uint32_t type);
  void Loongarch1Code(uint32_t opCode, uint32_t code);
  void Loongarch2RegZeroExtend(uint32_t opCode, uint32_t fr, uint32_t cr, int32_t type);
  void LoongarchOnlyOpcode(uint32_t opCode);
  void Loongarch4Reg(uint32_t opCode, uint32_t fa, uint32_t fk, uint32_t fj, uint32_t fd);
  void Loongarch1Reg1Imm(uint32_t opCode, int32_t si, uint32_t rd);
  uint32_t LoongarchLabelEnc(uint32_t op, const int32_t rj, const int32_t rd, int64_t labelOffset, int32_t type);
  void LoongarchLabel(uint32_t op, const int32_t rj, const int32_t rd, const Label& label, int32_t type);
  void LasxFormatI8VSTELM(uint32_t op, uint32_t df, uint32_t idx, int32_t imm8, const XReg &rj, const VReg &vd);
  /*LoongArch base end*/

  template <class T> void putL_inner(T &label) {
    if (isAutoGrow() && size_ >= maxSize_)
      growMemory();
    LoongarchLabel(0b010100, 0, 0, label, 4); // insert nemonic (B <label>)
  }

public:
  const XReg zero, ra, tp, sp, a0, v0, a1, v1, a2, a3, a4, a5, a6, a7, t0;
  const XReg t1, t2, t3, t4, t5, t6, t7, t8, x_, fp, s0, s1, s2, s3, s4, s5;
  const XReg s6, s7, s8_;

  //CPU Control Regs/CP0 Regs
  const XReg c0, c1, c2, c3, c4, c5, c6, c7, c8, c9, c10, c11, c12;
  const XReg c13, c14, c15, c16, c17, c18, c19, c20, c21, c22, c23, c24, c25;
  const XReg c26, c27, c28, c29, c30, c31;

  const XReg f0, f1, f2, f3, f4, f5, f6, f7, f8, f9, f10, f11, f12;
  const XReg f13, f14, f15, f16, f17, f18, f19, f20, f21, f22, f23, f24, f25;
  const XReg f26, f27, f28, f29, f30, f31;

  const VReg vr0, vr1, vr2, vr3, vr4, vr5, vr6, vr7, vr8, vr9, vr10, vr11, vr12;
  const VReg vr13, vr14, vr15, vr16, vr17, vr18, vr19, vr20, vr21, vr22, vr23;
  const VReg vr24, vr25, vr26, vr27, vr28, vr29, vr30, vr31;

  const XVReg xr0, xr1, xr2, xr3, xr4, xr5, xr6, xr7, xr8, xr9, xr10, xr11, xr12;
  const XVReg xr13, xr14, xr15, xr16, xr17, xr18, xr19, xr20, xr21, xr22, xr23;
  const XVReg xr24, xr25, xr26, xr27, xr28, xr29, xr30, xr31;

  CodeGenerator(size_t maxSize = DEFAULT_MAX_CODE_SIZE, void *userPtr = DontSetProtectRWE, Allocator *allocator = 0)
      : CodeArray(maxSize, userPtr, allocator)
#if 1
        ,
        zero(0), ra(1), tp(2), sp(3), a0(4), v0(4), a1(5), v1(5), a2(6), a3(7), a4(8), a5(9), a6(10), a7(11), t0(12), t1(13), t2(14), t3(15), t4(16), t5(17), t6(18), t7(19), t8(20), x_(21), fp(22), s0(23), s1(24), s2(25), s3(26), s4(27), s5(28), s6(29), s7(30), s8_(31)

        ,
        c0(0), c1(1), c2(2), c3(3), c4(4), c5(5), c6(6), c7(7), c8(8), c9(9), c10(10), c11(11), c12(12), c13(13), c14(14), c15(15), c16(16), c17(17), c18(18), c19(19), c20(20), c21(21), c22(22), c23(23), c24(24), c25(25), c26(26), c27(27), c28(28), c29(29), c30(30), c31(31)

        ,
        f0(0), f1(1), f2(2), f3(3), f4(4), f5(5), f6(6), f7(7), f8(8), f9(9), f10(10), f11(11), f12(12), f13(13), f14(14), f15(15), f16(16), f17(17), f18(18), f19(19), f20(20), f21(21), f22(22), f23(23), f24(24), f25(25), f26(26), f27(27), f28(28), f29(29), f30(30), f31(31)

        ,
        vr0(0), vr1(1), vr2(2), vr3(3), vr4(4), vr5(5), vr6(6), vr7(7), vr8(8), vr9(9), vr10(10), vr11(11), vr12(12), vr13(13), vr14(14), vr15(15), vr16(16), vr17(17), vr18(18), vr19(19), vr20(20), vr21(21), vr22(22), vr23(23), vr24(24), vr25(25), vr26(26), vr27(27), vr28(28), vr29(29), vr30(30), vr31(31) 

        ,
        xr0(0), xr1(1), xr2(2), xr3(3), xr4(4), xr5(5), xr6(6), xr7(7), xr8(8), xr9(9), xr10(10), xr11(11), xr12(12), xr13(13), xr14(14), xr15(15), xr16(16), xr17(17), xr18(18), xr19(19), xr20(20), xr21(21), xr22(22), xr23(23), xr24(24), xr25(25), xr26(26), xr27(27), xr28(28), xr29(29), xr30(30), xr31(31) 

#endif
  {
    labelMgr_.set(this);
  }

  unsigned int getVersion() const { return VERSION; }

  void L(Label &label) { labelMgr_.defineClabel(label); }
  Label L() {
    Label label;
    L(label);
    return label;
  }
  void inLocalLabel() { /*assert(NULL);*/
  }
  void outLocalLabel() { /*assert(NULL);*/
  }
  /*
          assign src to dst
          require
          dst : does not used by L()
          src : used by L()
  */
  void assignL(Label &dst, const Label &src) { labelMgr_.assign(dst, src); }
  /*
          put address of label to buffer
          @note the put size is 4(32-bit), 8(64-bit)
  */
  void putL(const Label &label) { putL_inner(label); }

  void reset() {
    resetSize();
    labelMgr_.reset();
    labelMgr_.set(this);
  }
  bool hasUndefinedLabel() const { return labelMgr_.hasUndefClabel(); }
  void clearCache(void *begin, void *end) {
    __builtin___clear_cache((char *)begin, (char *)end);
  }
  /*
          MUST call ready() to complete generating code if you use AutoGrow
     mode.
          It is not necessary for the other mode if hasUndefinedLabel() is true.
  */
  void ready(ProtectMode mode = PROTECT_RE) {
    if (hasUndefinedLabel())
      throw Error(ERR_LABEL_IS_NOT_FOUND);
    if (isAutoGrow()) {
      calcJmpAddress();
    }
    if (useProtect())
      setProtectMode(mode);
    clearCache(const_cast<uint8_t *>(getCode()), const_cast<uint8_t *>(getCurr()));
  }
  // set read/exec
  void readyRE() { return ready(PROTECT_RE); }
#ifdef XBYAK_TEST
  void dump(bool doClear = true) {
    CodeArray::dump();
    if (doClear)
      size_ = 0;
  }
#endif

  XReg getTmpXReg() { return t0; }

#include "xbyak_loongarch64_meta_mnemonic.h"
#include "xbyak_loongarch64_mnemonic_def.h"

  void align(size_t x) {
    if (x == 4)
      return; // loongson instructions are always 4 bytes.
    if (x < 4 || (x % 4))
      throw Error(ERR_BAD_ALIGN);

    if (isAutoGrow() && x > inner::getPageSize())
      fprintf(stderr, "warning:autoGrow mode does not support %d align\n", (int)x);

    size_t remain = size_t(getCurr());
    if (remain % 4)
      throw Error(ERR_BAD_ALIGN);
    remain = x - (remain % x);

    while (remain) {
      nop();
      remain -= 4;
    }
  }
};
