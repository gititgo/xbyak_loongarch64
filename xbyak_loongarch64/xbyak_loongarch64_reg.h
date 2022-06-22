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

#include <cassert>

class Operand {
public:
  static const int VL = 4;
  enum Kind { NONE, RREG, VREG_VEC, VREG, XVREG};

  enum Code {
    zero = 0,
    ra = 1,
    tp = 2,
    sp = 3,
    a0 = 4,
    v0 = 4,
    a1 = 5,
    v1 = 5,
    a2 = 6,
    a3 = 7,
    a4 = 8,
    a5 = 9,
    a6 = 10,
    a7 = 11,
    t0 = 12,
    t1 = 13,
    t2 = 14,
    t3 = 15,
    t4 = 16,
    t5 = 17,
    t6 = 18,
    t7 = 19, 
    t8 = 20, 
    x = 21,
    fp = 22, 
    s0 = 23, 
    s1 = 24, 
    s2 = 25,
    s3 = 26,
    s4 = 27,
    s5 = 28,
    s6 = 29,
    s7 = 30,
    s8 = 31, 
    f0 = 0,
    f1, 
    f2, 
    f3, 
    f4, 
    f5, 
    f6, 
    f7, 
    f8, 
    f9, 
    f10, 
    f11, 
    f12,
    f13, 
    f14, 
    f15, 
    f16, 
    f17, 
    f18, 
    f19, 
    f20, 
    f21, 
    f22, 
    f23, 
    f24, 
    f25,
    f26, 
    f27, 
    f28, 
    f29, 
    f30, 
    f31,
    w0 = 0, 
    w1, 
    w2, 
    w3, 
    w4, 
    w5, 
    w6, 
    w7, 
    w8, 
    w9, 
    w10, 
    w11, 
    w12,
    w13, 
    w14, 
    w15, 
    w16, 
    w17, 
    w18, 
    w19, 
    w20, 
    w21, 
    w22, 
    w23,
    w24, 
    w25, 
    w26, 
    w27, 
    w28, 
    w29, 
    w30, 
    w31,
    xr0 = 0,
    xr1,
    xr2,
    xr3,
    xr4,
    xr5,
    xr6,
    xr7,
    xr8,
    xr9,
    xr10,
    xr11,
    xr12,
    xr13,
    xr14,
    xr15,
    xr16,
    xr17,
    xr18,
    xr19,
    xr20,
    xr21,
    xr22,
    xr23,
    xr24,
    xr25,
    xr26,
    xr27,
    xr28,
    xr29,
    xr30,
    xr31,
  };

private:
  Kind kind_;
  uint32_t bit_;

public:
  explicit Operand(Kind kind, uint32_t bit) : kind_(kind), bit_(bit) {}
  uint32_t getBit() const { return bit_; }
  bool isVReg() const { return is(VREG); }
  bool isXVReg() const { return is(XVREG); }

private:
  bool is(Kind kind) const { return (kind_ == kind); }
};

class Reg : public Operand {
  uint32_t index_;

public:
  explicit Reg(uint32_t index, Kind kind, uint32_t bit) : Operand(kind, bit), index_(index) {}
  uint32_t getIdx() const { return index_; }
  bool operator==(const Reg& rhs) const { return getIdx() == rhs.getIdx() && getBit() == rhs.getBit(); }
  bool operator!=(const Reg& rhs) const { return !operator==(rhs); }
};

// General Purpose Register
class RReg : public Reg {
public:
  explicit RReg(uint32_t index, uint32_t bit) : Reg(index, RREG, bit) {}
};

class XReg : public RReg {
public:
  explicit XReg(uint32_t index) : RReg(index, 64) {}
};

class WReg : public RReg {
public:
  explicit WReg(uint32_t index) : RReg(index, 32) {}
};

// base for SIMD vector regisetr
class VRegVec : public Reg {
  uint32_t lane_;

public:
  explicit VRegVec(uint32_t index, uint32_t bits, uint32_t lane) : Reg(index, VREG_VEC, bits), lane_(lane){};
  uint32_t getLane() const { return lane_; }
};

// base for SIMD Vector Register List
class VRegList : public VRegVec {
  uint32_t len_;

public:
  explicit VRegList(const VRegVec &s) : VRegVec(s.getIdx(), s.getBit(), s.getLane()), len_(s.getIdx() - s.getIdx() + 1) {}
  explicit VRegList(const VRegVec &s, const VRegVec &e) : VRegVec(s.getIdx(), s.getBit(), s.getLane()), len_(((e.getIdx() + 32 - s.getIdx()) % 32) + 1) {}
  uint32_t getLen() const { return len_; }
};

// SIMD vector regisetr
class VReg : public Reg {
public:
  explicit VReg(uint32_t index) : Reg(index, VREG, 128) {}
};

class XVReg : public Reg {
public:
  explicit XVReg(uint32_t index) : Reg(index, XVREG, 256) {}
};

