#pragma once
/*******************************************************************************
 * Copyright 2019-2021 LOONGSON LIMITED
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

#include "xbyak_loongarch64_err.h"
#include "xbyak_loongarch64_reg.h"

enum AdrKind {
  BASE_ONLY = 1,     // base register only
  BASE_IMM = 1 << 1, // base plus offset (immediate)
};

class Adr {
  AdrKind kind_;

protected:

public:
  explicit Adr(AdrKind kind) : kind_(kind) {}
  AdrKind getKind() { return kind_; }
};

// base only
class AdrNoOfs : public Adr {
  XReg xn_;

public:
  explicit AdrNoOfs(const XReg &xn) : Adr(BASE_ONLY), xn_(xn) {}
  const XReg &getXn() const { return xn_; }
};

// base plus offset (signed immediate)
class AdrImm : public Adr {
  XReg xn_;
  int32_t imm_;

public:
  explicit AdrImm(const XReg &xn, int32_t imm) : Adr(BASE_IMM), xn_(xn), imm_(imm) {}
  AdrImm(const AdrNoOfs &a) : Adr(BASE_IMM), xn_(a.getXn()), imm_(0) {}
  const XReg &getXn() const { return xn_; }
  int32_t getImm() const { return imm_; }
};

// base size_t offset (unsigned immediate) for binary_injector
class Address : public Adr {
  XReg xn_;
  size_t offset_;
  bool broadcast_;

public:
  explicit Address(const XReg &xn, size_t offset, bool broadcast = false) : Adr(BASE_IMM), xn_(xn), offset_(offset), broadcast_(broadcast) {}
  const XReg &getXReg() const { return xn_; }
  uint32_t getOffset() const { return offset_; }
  uint32_t getIdx() const { return xn_.getIdx(); }
  bool operator==(const Address& rhs) const
  {
    return getIdx() == rhs.getIdx() && getOffset() == rhs.getOffset() && getBroadcast() == rhs.getBroadcast();
  }
  bool operator!=(const Address& rhs) const { return !operator==(rhs); }
  bool getBroadcast() const { return broadcast_; }
};

AdrNoOfs ptr(const XReg &xn);
AdrImm ptr(const XReg &xn, int32_t imm);

inline AdrNoOfs ptr(const XReg &xn) { return AdrNoOfs(xn); }

inline AdrImm ptr(const XReg &xn, int32_t imm) { return AdrImm(xn, imm); }

inline Address ptr_a(const XReg &xn, size_t offset) { return Address(xn, offset); }

inline Address ptr_b(const XReg &xn, size_t offset) { return Address(xn, offset, true); }

