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

/****** LASX begin ******/

#define FP_S   0b01
#define FP_D   0b10

enum int_type {
  TYPE_B = 0,
  TYPE_H = 1,
  TYPE_W = 2,
  TYPE_D = 3,
  TYPE_Q = 4
};

enum cond {
  CAF = 0x0,
  CUN = 0x8,
  CEQ = 0x4,
  CUEQ = 0xC,
  CLT = 0x2,
  CULT = 0xA,
  CLE = 0x6,
  CULE = 0xE,
  CNE = 0x10,
  COR = 0x14,
  CUNE = 0x18,
  SAF = 0x1,
  SUN = 0x9,
  SEQ = 0x5,
  SUEQ = 0xD,
  SLT = 0x3,
  SULT = 0xB,
  SLE = 0x7,
  SULE = 0xF,
  SNE = 0x11,
  SOR = 0x15,
  SUNE = 0x19
};

void CodeGenerator::xvfmadd_s(const XVReg &xd, const XVReg &xj, const XVReg &xk, const XVReg &xa) { LasxFormat4R(0b0000101000, FP_S, xa, xk, xj, xd); }
void CodeGenerator::xvfmadd_d(const XVReg &xd, const XVReg &xj, const XVReg &xk, const XVReg &xa) { LasxFormat4R(0b0000101000, FP_D, xa, xk, xj, xd); }

void CodeGenerator::xvfmsub_s(const XVReg &xd, const XVReg &xj, const XVReg &xk, const XVReg &xa) { LasxFormat4R(0b0000101001, FP_S, xa, xk, xj, xd); }
void CodeGenerator::xvfmsub_d(const XVReg &xd, const XVReg &xj, const XVReg &xk, const XVReg &xa) { LasxFormat4R(0b0000101001, FP_D, xa, xk, xj, xd); }

void CodeGenerator::xvfnmadd_s(const XVReg &xd, const XVReg &xj, const XVReg &xk, const XVReg &xa) { LasxFormat4R(0b0000101010, FP_S, xa, xk, xj, xd); }
void CodeGenerator::xvfnmadd_d(const XVReg &xd, const XVReg &xj, const XVReg &xk, const XVReg &xa) { LasxFormat4R(0b0000101010, FP_D, xa, xk, xj, xd); }

void CodeGenerator::xvfnmsub_s(const XVReg &xd, const XVReg &xj, const XVReg &xk, const XVReg &xa) { LasxFormat4R(0b0000101011, FP_S, xa, xk, xj, xd); }
void CodeGenerator::xvfnmsub_d(const XVReg &xd, const XVReg &xj, const XVReg &xk, const XVReg &xa) { LasxFormat4R(0b0000101011, FP_D, xa, xk, xj, xd); }

#define XVFCMP_MN_FUNC(name, cond_code) \
  void CodeGenerator::xvfcmp_##name##_s(const XVReg &xd, const XVReg &xj, const XVReg &xk) \
  { LasxFormatCond(0b0000110010, FP_S, cond_code, xk, xj, xd); } \
  void CodeGenerator::xvfcmp_##name##_d(const XVReg &xd, const XVReg &xj, const XVReg &xk) \
  { LasxFormatCond(0b0000110010, FP_D, cond_code, xk, xj, xd); }

XVFCMP_MN_FUNC(caf, CAF)
XVFCMP_MN_FUNC(cun, CUN)
XVFCMP_MN_FUNC(ceq, CEQ)
XVFCMP_MN_FUNC(cueq, CUEQ)
XVFCMP_MN_FUNC(clt, CLT)
XVFCMP_MN_FUNC(cult, CULT)
XVFCMP_MN_FUNC(cle, CLE)
XVFCMP_MN_FUNC(cule, CULE)
XVFCMP_MN_FUNC(cne, CNE)
XVFCMP_MN_FUNC(cor, COR)
XVFCMP_MN_FUNC(cune, CUNE)
XVFCMP_MN_FUNC(saf, SAF)
XVFCMP_MN_FUNC(sun, SUN)
XVFCMP_MN_FUNC(seq, SEQ)
XVFCMP_MN_FUNC(sueq, SUEQ)
XVFCMP_MN_FUNC(slt, SLT)
XVFCMP_MN_FUNC(sult, SULT)
XVFCMP_MN_FUNC(sle, SLE)
XVFCMP_MN_FUNC(sule, SULE)
XVFCMP_MN_FUNC(sne, SNE)
XVFCMP_MN_FUNC(sor, SOR)
XVFCMP_MN_FUNC(sune, SUNE)

void CodeGenerator::xvbitsel_v(const XVReg &xd, const XVReg &xj, const XVReg &xk, const XVReg &xa) { LasxFormat4R(0b0000110100, 0b10, xa, xk, xj, xd); }

void CodeGenerator::xvshuf_b(const XVReg &xd, const XVReg &xj, const XVReg &xk, const XVReg &xa) { LasxFormat4R(0b0000110101, 0b10, xa, xk, xj, xd); }

void CodeGenerator::vld(const VReg &vd, const XReg &rj, int32_t si12) { LasxFormatI12(0b0010110000, si12, rj, vd); }
void CodeGenerator::vst(const VReg &vd, const XReg &rj, int32_t si12) { LasxFormatI12(0b0010110001, si12, rj, vd); }
void CodeGenerator::xvld(const XVReg &xd, const XReg &rj, int32_t si12) { LasxFormatI12(0b0010110010, si12, rj, xd); }
void CodeGenerator::xvst(const XVReg &xd, const XReg &rj, int32_t si12) { LasxFormatI12(0b0010110011, si12, rj, xd); }

void CodeGenerator::xvldrepl_b(const XVReg &xd, const XReg &rj, int32_t si12) { LasxFormatAddr(0b00110010, TYPE_B, si12, rj, xd); }
void CodeGenerator::xvldrepl_h(const XVReg &xd, const XReg &rj, int32_t si11) { LasxFormatAddr(0b00110010, TYPE_H, si11, rj, xd); }
void CodeGenerator::xvldrepl_w(const XVReg &xd, const XReg &rj, int32_t si10) { LasxFormatAddr(0b00110010, TYPE_W, si10, rj, xd); }
void CodeGenerator::xvldrepl_d(const XVReg &xd, const XReg &rj, int32_t si9)  { LasxFormatAddr(0b00110010, TYPE_D, si9,  rj, xd); }

void CodeGenerator::xvstelm_b(const XVReg &xd, const XReg &rj, int32_t si8, uint32_t idx) { LasxFormatI8ELM(0b00110011, TYPE_B, idx, si8, rj, xd); }
void CodeGenerator::xvstelm_h(const XVReg &xd, const XReg &rj, int32_t si8, uint32_t idx) { LasxFormatI8ELM(0b00110011, TYPE_H, idx, si8, rj, xd); }
void CodeGenerator::xvstelm_w(const XVReg &xd, const XReg &rj, int32_t si8, uint32_t idx) { LasxFormatI8ELM(0b00110011, TYPE_W, idx, si8, rj, xd); }
void CodeGenerator::xvstelm_d(const XVReg &xd, const XReg &rj, int32_t si8, uint32_t idx) { LasxFormatI8ELM(0b00110011, TYPE_D, idx, si8, rj, xd); }

void CodeGenerator::vldx(const VReg &vd, const XReg &rj, const XReg &rk) { LasxFormat3RX(0b00111000010000, rk, rj, vd); }
void CodeGenerator::vstx(const VReg &vd, const XReg &rj, const XReg &rk) { LasxFormat3RX(0b00111000010001, rk, rj, vd); }
void CodeGenerator::xvldx(const XVReg &xd, const XReg &rj, const XReg &rk) { LasxFormat3RX(0b00111000010010, rk, rj, xd); }
void CodeGenerator::xvstx(const XVReg &xd, const XReg &rj, const XReg &rk) { LasxFormat3RX(0b00111000010011, rk, rj, xd); }

void CodeGenerator::xvseq_b(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101000000000, TYPE_B, xk, xj, xd); }
void CodeGenerator::xvseq_h(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101000000000, TYPE_H, xk, xj, xd); }
void CodeGenerator::xvseq_w(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101000000000, TYPE_W, xk, xj, xd); }
void CodeGenerator::xvseq_d(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101000000000, TYPE_D, xk, xj, xd); }

void CodeGenerator::xvsle_b(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101000000001, TYPE_B, xk, xj, xd); }
void CodeGenerator::xvsle_h(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101000000001, TYPE_H, xk, xj, xd); }
void CodeGenerator::xvsle_w(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101000000001, TYPE_W, xk, xj, xd); }
void CodeGenerator::xvsle_d(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101000000001, TYPE_D, xk, xj, xd); }

void CodeGenerator::xvsle_bu(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101000000010, TYPE_B, xk, xj, xd); }
void CodeGenerator::xvsle_hu(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101000000010, TYPE_H, xk, xj, xd); }
void CodeGenerator::xvsle_wu(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101000000010, TYPE_W, xk, xj, xd); }
void CodeGenerator::xvsle_du(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101000000010, TYPE_D, xk, xj, xd); }

void CodeGenerator::xvslt_b(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101000000011, TYPE_B, xk, xj, xd); }
void CodeGenerator::xvslt_h(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101000000011, TYPE_H, xk, xj, xd); }
void CodeGenerator::xvslt_w(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101000000011, TYPE_W, xk, xj, xd); }
void CodeGenerator::xvslt_d(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101000000011, TYPE_D, xk, xj, xd); }

void CodeGenerator::xvslt_bu(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101000000100, TYPE_B, xk, xj, xd); }
void CodeGenerator::xvslt_hu(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101000000100, TYPE_H, xk, xj, xd); }
void CodeGenerator::xvslt_wu(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101000000100, TYPE_W, xk, xj, xd); }
void CodeGenerator::xvslt_du(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101000000100, TYPE_D, xk, xj, xd); }

void CodeGenerator::xvadd_b(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101000000101, TYPE_B, xk, xj, xd); }
void CodeGenerator::xvadd_h(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101000000101, TYPE_H, xk, xj, xd); }
void CodeGenerator::xvadd_w(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101000000101, TYPE_W, xk, xj, xd); }
void CodeGenerator::xvadd_d(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101000000101, TYPE_D, xk, xj, xd); }

void CodeGenerator::xvsub_b(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101000000110, TYPE_B, xk, xj, xd); }
void CodeGenerator::xvsub_h(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101000000110, TYPE_H, xk, xj, xd); }
void CodeGenerator::xvsub_w(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101000000110, TYPE_W, xk, xj, xd); }
void CodeGenerator::xvsub_d(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101000000110, TYPE_D, xk, xj, xd); }

void CodeGenerator::xvaddwev_h_b(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101000001111, TYPE_B, xk, xj, xd); }
void CodeGenerator::xvaddwev_w_h(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101000001111, TYPE_H, xk, xj, xd); }
void CodeGenerator::xvaddwev_d_w(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101000001111, TYPE_W, xk, xj, xd); }
void CodeGenerator::xvaddwev_q_d(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101000001111, TYPE_D, xk, xj, xd); }

void CodeGenerator::xvsubwev_h_b(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101000010000, TYPE_B, xk, xj, xd); }
void CodeGenerator::xvsubwev_w_h(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101000010000, TYPE_H, xk, xj, xd); }
void CodeGenerator::xvsubwev_d_w(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101000010000, TYPE_W, xk, xj, xd); }
void CodeGenerator::xvsubwev_q_d(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101000010000, TYPE_D, xk, xj, xd); }

void CodeGenerator::xvaddwod_h_b(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101000010001, TYPE_B, xk, xj, xd); }
void CodeGenerator::xvaddwod_w_h(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101000010001, TYPE_H, xk, xj, xd); }
void CodeGenerator::xvaddwod_d_w(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101000010001, TYPE_W, xk, xj, xd); }
void CodeGenerator::xvaddwod_q_d(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101000010001, TYPE_D, xk, xj, xd); }

void CodeGenerator::xvsubwod_h_b(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101000010010, TYPE_B, xk, xj, xd); }
void CodeGenerator::xvsubwod_w_h(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101000010010, TYPE_H, xk, xj, xd); }
void CodeGenerator::xvsubwod_d_w(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101000010010, TYPE_W, xk, xj, xd); }
void CodeGenerator::xvsubwod_q_d(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101000010010, TYPE_D, xk, xj, xd); }

void CodeGenerator::xvaddwev_h_bu(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101000010111, TYPE_B, xk, xj, xd); }
void CodeGenerator::xvaddwev_w_hu(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101000010111, TYPE_H, xk, xj, xd); }
void CodeGenerator::xvaddwev_d_wu(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101000010111, TYPE_W, xk, xj, xd); }
void CodeGenerator::xvaddwev_q_du(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101000010111, TYPE_D, xk, xj, xd); }

void CodeGenerator::xvsubwev_h_bu(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101000011000, TYPE_B, xk, xj, xd); }
void CodeGenerator::xvsubwev_w_hu(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101000011000, TYPE_H, xk, xj, xd); }
void CodeGenerator::xvsubwev_d_wu(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101000011000, TYPE_W, xk, xj, xd); }
void CodeGenerator::xvsubwev_q_du(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101000011000, TYPE_D, xk, xj, xd); }

void CodeGenerator::xvaddwod_h_bu(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101000011001, TYPE_B, xk, xj, xd); }
void CodeGenerator::xvaddwod_w_hu(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101000011001, TYPE_H, xk, xj, xd); }
void CodeGenerator::xvaddwod_d_wu(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101000011001, TYPE_W, xk, xj, xd); }
void CodeGenerator::xvaddwod_q_du(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101000011001, TYPE_D, xk, xj, xd); }

void CodeGenerator::xvsubwod_h_bu(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101000011010, TYPE_B, xk, xj, xd); }
void CodeGenerator::xvsubwod_w_hu(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101000011010, TYPE_H, xk, xj, xd); }
void CodeGenerator::xvsubwod_d_wu(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101000011010, TYPE_W, xk, xj, xd); }
void CodeGenerator::xvsubwod_q_du(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101000011010, TYPE_D, xk, xj, xd); }

void CodeGenerator::xvaddwev_h_bu_b(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101000011111, TYPE_B, xk, xj, xd); }
void CodeGenerator::xvaddwev_w_hu_h(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101000011111, TYPE_H, xk, xj, xd); }
void CodeGenerator::xvaddwev_d_wu_w(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101000011111, TYPE_W, xk, xj, xd); }
void CodeGenerator::xvaddwev_q_du_d(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101000011111, TYPE_D, xk, xj, xd); }

void CodeGenerator::xvaddwod_h_bu_b(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101000100000, TYPE_B, xk, xj, xd); }
void CodeGenerator::xvaddwod_w_hu_h(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101000100000, TYPE_H, xk, xj, xd); }
void CodeGenerator::xvaddwod_d_wu_w(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101000100000, TYPE_W, xk, xj, xd); }
void CodeGenerator::xvaddwod_q_du_d(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101000100000, TYPE_D, xk, xj, xd); }

void CodeGenerator::xvsadd_b(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101000100011, TYPE_B, xk, xj, xd); }
void CodeGenerator::xvsadd_h(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101000100011, TYPE_H, xk, xj, xd); }
void CodeGenerator::xvsadd_w(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101000100011, TYPE_W, xk, xj, xd); }
void CodeGenerator::xvsadd_d(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101000100011, TYPE_D, xk, xj, xd); }

void CodeGenerator::xvssub_b(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101000100100, TYPE_B, xk, xj, xd); }
void CodeGenerator::xvssub_h(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101000100100, TYPE_H, xk, xj, xd); }
void CodeGenerator::xvssub_w(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101000100100, TYPE_W, xk, xj, xd); }
void CodeGenerator::xvssub_d(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101000100100, TYPE_D, xk, xj, xd); }

void CodeGenerator::xvsadd_bu(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101000100101, TYPE_B, xk, xj, xd); }
void CodeGenerator::xvsadd_hu(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101000100101, TYPE_H, xk, xj, xd); }
void CodeGenerator::xvsadd_wu(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101000100101, TYPE_W, xk, xj, xd); }
void CodeGenerator::xvsadd_du(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101000100101, TYPE_D, xk, xj, xd); }

void CodeGenerator::xvssub_bu(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101000100110, TYPE_B, xk, xj, xd); }
void CodeGenerator::xvssub_hu(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101000100110, TYPE_H, xk, xj, xd); }
void CodeGenerator::xvssub_wu(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101000100110, TYPE_W, xk, xj, xd); }
void CodeGenerator::xvssub_du(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101000100110, TYPE_D, xk, xj, xd); }

void CodeGenerator::xvhaddw_h_b(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101000101010, TYPE_B, xk, xj, xd); }
void CodeGenerator::xvhaddw_w_h(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101000101010, TYPE_H, xk, xj, xd); }
void CodeGenerator::xvhaddw_d_w(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101000101010, TYPE_W, xk, xj, xd); }
void CodeGenerator::xvhaddw_q_d(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101000101010, TYPE_D, xk, xj, xd); }

void CodeGenerator::xvhsubw_h_b(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101000101011, TYPE_B, xk, xj, xd); }
void CodeGenerator::xvhsubw_w_h(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101000101011, TYPE_H, xk, xj, xd); }
void CodeGenerator::xvhsubw_d_w(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101000101011, TYPE_W, xk, xj, xd); }
void CodeGenerator::xvhsubw_q_d(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101000101011, TYPE_D, xk, xj, xd); }

void CodeGenerator::xvhaddw_hu_bu(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101000101100, TYPE_B, xk, xj, xd); }
void CodeGenerator::xvhaddw_wu_hu(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101000101100, TYPE_H, xk, xj, xd); }
void CodeGenerator::xvhaddw_du_wu(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101000101100, TYPE_W, xk, xj, xd); }
void CodeGenerator::xvhaddw_qu_du(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101000101100, TYPE_D, xk, xj, xd); }

void CodeGenerator::xvhsubw_hu_bu(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101000101101, TYPE_B, xk, xj, xd); }
void CodeGenerator::xvhsubw_wu_hu(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101000101101, TYPE_H, xk, xj, xd); }
void CodeGenerator::xvhsubw_du_wu(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101000101101, TYPE_W, xk, xj, xd); }
void CodeGenerator::xvhsubw_qu_du(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101000101101, TYPE_D, xk, xj, xd); }

void CodeGenerator::xvadda_b(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101000101110, TYPE_B, xk, xj, xd); }
void CodeGenerator::xvadda_h(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101000101110, TYPE_H, xk, xj, xd); }
void CodeGenerator::xvadda_w(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101000101110, TYPE_W, xk, xj, xd); }
void CodeGenerator::xvadda_d(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101000101110, TYPE_D, xk, xj, xd); }

void CodeGenerator::xvabsd_b(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101000110000, TYPE_B, xk, xj, xd); }
void CodeGenerator::xvabsd_h(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101000110000, TYPE_H, xk, xj, xd); }
void CodeGenerator::xvabsd_w(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101000110000, TYPE_W, xk, xj, xd); }
void CodeGenerator::xvabsd_d(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101000110000, TYPE_D, xk, xj, xd); }

void CodeGenerator::xvabsd_bu(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101000110001, TYPE_B, xk, xj, xd); }
void CodeGenerator::xvabsd_hu(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101000110001, TYPE_H, xk, xj, xd); }
void CodeGenerator::xvabsd_wu(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101000110001, TYPE_W, xk, xj, xd); }
void CodeGenerator::xvabsd_du(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101000110001, TYPE_D, xk, xj, xd); }

void CodeGenerator::xvavg_b(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101000110010, TYPE_B, xk, xj, xd); }
void CodeGenerator::xvavg_h(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101000110010, TYPE_H, xk, xj, xd); }
void CodeGenerator::xvavg_w(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101000110010, TYPE_W, xk, xj, xd); }
void CodeGenerator::xvavg_d(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101000110010, TYPE_D, xk, xj, xd); }

void CodeGenerator::xvavg_bu(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101000110011, TYPE_B, xk, xj, xd); }
void CodeGenerator::xvavg_hu(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101000110011, TYPE_H, xk, xj, xd); }
void CodeGenerator::xvavg_wu(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101000110011, TYPE_W, xk, xj, xd); }
void CodeGenerator::xvavg_du(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101000110011, TYPE_D, xk, xj, xd); }

void CodeGenerator::xvavgr_b(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101000110100, TYPE_B, xk, xj, xd); }
void CodeGenerator::xvavgr_h(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101000110100, TYPE_H, xk, xj, xd); }
void CodeGenerator::xvavgr_w(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101000110100, TYPE_W, xk, xj, xd); }
void CodeGenerator::xvavgr_d(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101000110100, TYPE_D, xk, xj, xd); }

void CodeGenerator::xvavgr_bu(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101000110101, TYPE_B, xk, xj, xd); }
void CodeGenerator::xvavgr_hu(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101000110101, TYPE_H, xk, xj, xd); }
void CodeGenerator::xvavgr_wu(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101000110101, TYPE_W, xk, xj, xd); }
void CodeGenerator::xvavgr_du(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101000110101, TYPE_D, xk, xj, xd); }

void CodeGenerator::xvmax_b(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101000111000, TYPE_B, xk, xj, xd); }
void CodeGenerator::xvmax_h(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101000111000, TYPE_H, xk, xj, xd); }
void CodeGenerator::xvmax_w(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101000111000, TYPE_W, xk, xj, xd); }
void CodeGenerator::xvmax_d(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101000111000, TYPE_D, xk, xj, xd); }

void CodeGenerator::xvmin_b(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101000111001, TYPE_B, xk, xj, xd); }
void CodeGenerator::xvmin_h(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101000111001, TYPE_H, xk, xj, xd); }
void CodeGenerator::xvmin_w(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101000111001, TYPE_W, xk, xj, xd); }
void CodeGenerator::xvmin_d(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101000111001, TYPE_D, xk, xj, xd); }

void CodeGenerator::xvmax_bu(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101000111010, TYPE_B, xk, xj, xd); }
void CodeGenerator::xvmax_hu(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101000111010, TYPE_H, xk, xj, xd); }
void CodeGenerator::xvmax_wu(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101000111010, TYPE_W, xk, xj, xd); }
void CodeGenerator::xvmax_du(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101000111010, TYPE_D, xk, xj, xd); }

void CodeGenerator::xvmin_bu(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101000111011, TYPE_B, xk, xj, xd); }
void CodeGenerator::xvmin_hu(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101000111011, TYPE_H, xk, xj, xd); }
void CodeGenerator::xvmin_wu(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101000111011, TYPE_W, xk, xj, xd); }
void CodeGenerator::xvmin_du(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101000111011, TYPE_D, xk, xj, xd); }

void CodeGenerator::xvmul_b(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101001000010, TYPE_B, xk, xj, xd); }
void CodeGenerator::xvmul_h(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101001000010, TYPE_H, xk, xj, xd); }
void CodeGenerator::xvmul_w(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101001000010, TYPE_W, xk, xj, xd); }
void CodeGenerator::xvmul_d(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101001000010, TYPE_D, xk, xj, xd); }

void CodeGenerator::xvmuh_b(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101001000011, TYPE_B, xk, xj, xd); }
void CodeGenerator::xvmuh_h(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101001000011, TYPE_H, xk, xj, xd); }
void CodeGenerator::xvmuh_w(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101001000011, TYPE_W, xk, xj, xd); }
void CodeGenerator::xvmuh_d(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101001000011, TYPE_D, xk, xj, xd); }

void CodeGenerator::xvmuh_bu(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101001000100, TYPE_B, xk, xj, xd); }
void CodeGenerator::xvmuh_hu(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101001000100, TYPE_H, xk, xj, xd); }
void CodeGenerator::xvmuh_wu(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101001000100, TYPE_W, xk, xj, xd); }
void CodeGenerator::xvmuh_du(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101001000100, TYPE_D, xk, xj, xd); }

void CodeGenerator::xvmulwev_h_b(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101001001000, TYPE_B, xk, xj, xd); }
void CodeGenerator::xvmulwev_w_h(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101001001000, TYPE_H, xk, xj, xd); }
void CodeGenerator::xvmulwev_d_w(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101001001000, TYPE_W, xk, xj, xd); }
void CodeGenerator::xvmulwev_q_d(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101001001000, TYPE_D, xk, xj, xd); }

void CodeGenerator::xvmulwod_h_b(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101001001001, TYPE_B, xk, xj, xd); }
void CodeGenerator::xvmulwod_w_h(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101001001001, TYPE_H, xk, xj, xd); }
void CodeGenerator::xvmulwod_d_w(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101001001001, TYPE_W, xk, xj, xd); }
void CodeGenerator::xvmulwod_q_d(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101001001001, TYPE_D, xk, xj, xd); }

void CodeGenerator::xvmulwev_h_bu(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101001001100, TYPE_B, xk, xj, xd); }
void CodeGenerator::xvmulwev_w_hu(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101001001100, TYPE_H, xk, xj, xd); }
void CodeGenerator::xvmulwev_d_wu(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101001001100, TYPE_W, xk, xj, xd); }
void CodeGenerator::xvmulwev_q_du(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101001001100, TYPE_D, xk, xj, xd); }

void CodeGenerator::xvmulwod_h_bu(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101001001101, TYPE_B, xk, xj, xd); }
void CodeGenerator::xvmulwod_w_hu(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101001001101, TYPE_H, xk, xj, xd); }
void CodeGenerator::xvmulwod_d_wu(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101001001101, TYPE_W, xk, xj, xd); }
void CodeGenerator::xvmulwod_q_du(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101001001101, TYPE_D, xk, xj, xd); }

void CodeGenerator::xvmulwev_h_bu_b(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101001010000, TYPE_B, xk, xj, xd); }
void CodeGenerator::xvmulwev_w_hu_h(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101001010000, TYPE_H, xk, xj, xd); }
void CodeGenerator::xvmulwev_d_wu_w(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101001010000, TYPE_W, xk, xj, xd); }
void CodeGenerator::xvmulwev_q_du_d(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101001010000, TYPE_D, xk, xj, xd); }

void CodeGenerator::xvmulwod_h_bu_b(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101001010001, TYPE_B, xk, xj, xd); }
void CodeGenerator::xvmulwod_w_hu_h(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101001010001, TYPE_H, xk, xj, xd); }
void CodeGenerator::xvmulwod_d_wu_w(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101001010001, TYPE_W, xk, xj, xd); }
void CodeGenerator::xvmulwod_q_du_d(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101001010001, TYPE_D, xk, xj, xd); }

void CodeGenerator::xvmadd_b(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101001010100, TYPE_B, xk, xj, xd); }
void CodeGenerator::xvmadd_h(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101001010100, TYPE_H, xk, xj, xd); }
void CodeGenerator::xvmadd_w(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101001010100, TYPE_W, xk, xj, xd); }
void CodeGenerator::xvmadd_d(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101001010100, TYPE_D, xk, xj, xd); }

void CodeGenerator::xvmsub_b(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101001010101, TYPE_B, xk, xj, xd); }
void CodeGenerator::xvmsub_h(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101001010101, TYPE_H, xk, xj, xd); }
void CodeGenerator::xvmsub_w(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101001010101, TYPE_W, xk, xj, xd); }
void CodeGenerator::xvmsub_d(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101001010101, TYPE_D, xk, xj, xd); }

void CodeGenerator::xvmaddwev_h_b(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101001010110, TYPE_B, xk, xj, xd); }
void CodeGenerator::xvmaddwev_w_h(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101001010110, TYPE_H, xk, xj, xd); }
void CodeGenerator::xvmaddwev_d_w(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101001010110, TYPE_W, xk, xj, xd); }
void CodeGenerator::xvmaddwev_q_d(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101001010110, TYPE_D, xk, xj, xd); }

void CodeGenerator::xvmaddwod_h_b(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101001010111, TYPE_B, xk, xj, xd); }
void CodeGenerator::xvmaddwod_w_h(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101001010111, TYPE_H, xk, xj, xd); }
void CodeGenerator::xvmaddwod_d_w(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101001010111, TYPE_W, xk, xj, xd); }
void CodeGenerator::xvmaddwod_q_d(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101001010111, TYPE_D, xk, xj, xd); }

void CodeGenerator::xvmaddwev_h_bu(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101001011010, TYPE_B, xk, xj, xd); }
void CodeGenerator::xvmaddwev_w_hu(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101001011010, TYPE_H, xk, xj, xd); }
void CodeGenerator::xvmaddwev_d_wu(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101001011010, TYPE_W, xk, xj, xd); }
void CodeGenerator::xvmaddwev_q_du(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101001011010, TYPE_D, xk, xj, xd); }

void CodeGenerator::xvmaddwod_h_bu(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101001011011, TYPE_B, xk, xj, xd); }
void CodeGenerator::xvmaddwod_w_hu(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101001011011, TYPE_H, xk, xj, xd); }
void CodeGenerator::xvmaddwod_d_wu(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101001011011, TYPE_W, xk, xj, xd); }
void CodeGenerator::xvmaddwod_q_du(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101001011011, TYPE_D, xk, xj, xd); }

void CodeGenerator::xvmaddwev_h_bu_b(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101001011110, TYPE_B, xk, xj, xd); }
void CodeGenerator::xvmaddwev_w_hu_h(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101001011110, TYPE_H, xk, xj, xd); }
void CodeGenerator::xvmaddwev_d_wu_w(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101001011110, TYPE_W, xk, xj, xd); }
void CodeGenerator::xvmaddwev_q_du_d(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101001011110, TYPE_D, xk, xj, xd); }

void CodeGenerator::xvmaddwod_h_bu_b(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101001011111, TYPE_B, xk, xj, xd); }
void CodeGenerator::xvmaddwod_w_hu_h(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101001011111, TYPE_H, xk, xj, xd); }
void CodeGenerator::xvmaddwod_d_wu_w(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101001011111, TYPE_W, xk, xj, xd); }
void CodeGenerator::xvmaddwod_q_du_d(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101001011111, TYPE_D, xk, xj, xd); }

void CodeGenerator::xvdiv_b(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101001110000, TYPE_B, xk, xj, xd); }
void CodeGenerator::xvdiv_h(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101001110000, TYPE_H, xk, xj, xd); }
void CodeGenerator::xvdiv_w(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101001110000, TYPE_W, xk, xj, xd); }
void CodeGenerator::xvdiv_d(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101001110000, TYPE_D, xk, xj, xd); }

void CodeGenerator::xvmod_b(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101001110001, TYPE_B, xk, xj, xd); }
void CodeGenerator::xvmod_h(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101001110001, TYPE_H, xk, xj, xd); }
void CodeGenerator::xvmod_w(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101001110001, TYPE_W, xk, xj, xd); }
void CodeGenerator::xvmod_d(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101001110001, TYPE_D, xk, xj, xd); }

void CodeGenerator::xvdiv_bu(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101001110010, TYPE_B, xk, xj, xd); }
void CodeGenerator::xvdiv_hu(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101001110010, TYPE_H, xk, xj, xd); }
void CodeGenerator::xvdiv_wu(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101001110010, TYPE_W, xk, xj, xd); }
void CodeGenerator::xvdiv_du(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101001110010, TYPE_D, xk, xj, xd); }

void CodeGenerator::xvmod_bu(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101001110011, TYPE_B, xk, xj, xd); }
void CodeGenerator::xvmod_hu(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101001110011, TYPE_H, xk, xj, xd); }
void CodeGenerator::xvmod_wu(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101001110011, TYPE_W, xk, xj, xd); }
void CodeGenerator::xvmod_du(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101001110011, TYPE_D, xk, xj, xd); }

void CodeGenerator::xvsll_b(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101001110100, TYPE_B, xk, xj, xd); }
void CodeGenerator::xvsll_h(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101001110100, TYPE_H, xk, xj, xd); }
void CodeGenerator::xvsll_w(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101001110100, TYPE_W, xk, xj, xd); }
void CodeGenerator::xvsll_d(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101001110100, TYPE_D, xk, xj, xd); }

void CodeGenerator::xvsrl_b(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101001110101, TYPE_B, xk, xj, xd); }
void CodeGenerator::xvsrl_h(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101001110101, TYPE_H, xk, xj, xd); }
void CodeGenerator::xvsrl_w(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101001110101, TYPE_W, xk, xj, xd); }
void CodeGenerator::xvsrl_d(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101001110101, TYPE_D, xk, xj, xd); }

void CodeGenerator::xvsra_b(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101001110110, TYPE_B, xk, xj, xd); }
void CodeGenerator::xvsra_h(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101001110110, TYPE_H, xk, xj, xd); }
void CodeGenerator::xvsra_w(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101001110110, TYPE_W, xk, xj, xd); }
void CodeGenerator::xvsra_d(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101001110110, TYPE_D, xk, xj, xd); }

void CodeGenerator::xvrotr_b(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101001110111, TYPE_B, xk, xj, xd); }
void CodeGenerator::xvrotr_h(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101001110111, TYPE_H, xk, xj, xd); }
void CodeGenerator::xvrotr_w(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101001110111, TYPE_W, xk, xj, xd); }
void CodeGenerator::xvrotr_d(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101001110111, TYPE_D, xk, xj, xd); }

void CodeGenerator::xvsrlr_b(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101001111000, TYPE_B, xk, xj, xd); }
void CodeGenerator::xvsrlr_h(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101001111000, TYPE_H, xk, xj, xd); }
void CodeGenerator::xvsrlr_w(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101001111000, TYPE_W, xk, xj, xd); }
void CodeGenerator::xvsrlr_d(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101001111000, TYPE_D, xk, xj, xd); }

void CodeGenerator::xvsrar_b(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101001111001, TYPE_B, xk, xj, xd); }
void CodeGenerator::xvsrar_h(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101001111001, TYPE_H, xk, xj, xd); }
void CodeGenerator::xvsrar_w(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101001111001, TYPE_W, xk, xj, xd); }
void CodeGenerator::xvsrar_d(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101001111001, TYPE_D, xk, xj, xd); }

void CodeGenerator::xvsrln_b_h(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101001111010, TYPE_H, xk, xj, xd); }
void CodeGenerator::xvsrln_h_w(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101001111010, TYPE_W, xk, xj, xd); }
void CodeGenerator::xvsrln_w_d(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101001111010, TYPE_D, xk, xj, xd); }

void CodeGenerator::xvsran_b_h(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101001111011, TYPE_H, xk, xj, xd); }
void CodeGenerator::xvsran_h_w(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101001111011, TYPE_W, xk, xj, xd); }
void CodeGenerator::xvsran_w_d(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101001111011, TYPE_D, xk, xj, xd); }

void CodeGenerator::xvsrlrn_b_h(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101001111100, TYPE_H, xk, xj, xd); }
void CodeGenerator::xvsrlrn_h_w(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101001111100, TYPE_W, xk, xj, xd); }
void CodeGenerator::xvsrlrn_w_d(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101001111100, TYPE_D, xk, xj, xd); }

void CodeGenerator::xvsrarn_b_h(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101001111101, TYPE_H, xk, xj, xd); }
void CodeGenerator::xvsrarn_h_w(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101001111101, TYPE_W, xk, xj, xd); }
void CodeGenerator::xvsrarn_w_d(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101001111101, TYPE_D, xk, xj, xd); }

void CodeGenerator::xvssrln_b_h(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101001111110, TYPE_H, xk, xj, xd); }
void CodeGenerator::xvssrln_h_w(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101001111110, TYPE_W, xk, xj, xd); }
void CodeGenerator::xvssrln_w_d(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101001111110, TYPE_D, xk, xj, xd); }

void CodeGenerator::xvssran_b_h(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101001111111, TYPE_H, xk, xj, xd); }
void CodeGenerator::xvssran_h_w(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101001111111, TYPE_W, xk, xj, xd); }
void CodeGenerator::xvssran_w_d(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101001111111, TYPE_D, xk, xj, xd); }

void CodeGenerator::xvssrlrn_b_h(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101010000000, TYPE_H, xk, xj, xd); }
void CodeGenerator::xvssrlrn_h_w(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101010000000, TYPE_W, xk, xj, xd); }
void CodeGenerator::xvssrlrn_w_d(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101010000000, TYPE_D, xk, xj, xd); }

void CodeGenerator::xvssrarn_b_h(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101010000001, TYPE_H, xk, xj, xd); }
void CodeGenerator::xvssrarn_h_w(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101010000001, TYPE_W, xk, xj, xd); }
void CodeGenerator::xvssrarn_w_d(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101010000001, TYPE_D, xk, xj, xd); }

void CodeGenerator::xvssrln_bu_h(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101010000010, TYPE_H, xk, xj, xd); }
void CodeGenerator::xvssrln_hu_w(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101010000010, TYPE_W, xk, xj, xd); }
void CodeGenerator::xvssrln_wu_d(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101010000010, TYPE_D, xk, xj, xd); }

void CodeGenerator::xvssran_bu_h(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101010000011, TYPE_H, xk, xj, xd); }
void CodeGenerator::xvssran_hu_w(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101010000011, TYPE_W, xk, xj, xd); }
void CodeGenerator::xvssran_wu_d(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101010000011, TYPE_D, xk, xj, xd); }

void CodeGenerator::xvssrlrn_bu_h(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101010000100, TYPE_H, xk, xj, xd); }
void CodeGenerator::xvssrlrn_hu_w(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101010000100, TYPE_W, xk, xj, xd); }
void CodeGenerator::xvssrlrn_wu_d(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101010000100, TYPE_D, xk, xj, xd); }

void CodeGenerator::xvssrarn_bu_h(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101010000101, TYPE_H, xk, xj, xd); }
void CodeGenerator::xvssrarn_hu_w(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101010000101, TYPE_W, xk, xj, xd); }
void CodeGenerator::xvssrarn_wu_d(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101010000101, TYPE_D, xk, xj, xd); }

void CodeGenerator::xvbitclr_b(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101010000110, TYPE_B, xk, xj, xd); }
void CodeGenerator::xvbitclr_h(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101010000110, TYPE_H, xk, xj, xd); }
void CodeGenerator::xvbitclr_w(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101010000110, TYPE_W, xk, xj, xd); }
void CodeGenerator::xvbitclr_d(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101010000110, TYPE_D, xk, xj, xd); }

void CodeGenerator::xvbitset_b(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101010000111, TYPE_B, xk, xj, xd); }
void CodeGenerator::xvbitset_h(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101010000111, TYPE_H, xk, xj, xd); }
void CodeGenerator::xvbitset_w(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101010000111, TYPE_W, xk, xj, xd); }
void CodeGenerator::xvbitset_d(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101010000111, TYPE_D, xk, xj, xd); }

void CodeGenerator::xvbitrev_b(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101010001000, TYPE_B, xk, xj, xd); }
void CodeGenerator::xvbitrev_h(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101010001000, TYPE_H, xk, xj, xd); }
void CodeGenerator::xvbitrev_w(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101010001000, TYPE_W, xk, xj, xd); }
void CodeGenerator::xvbitrev_d(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101010001000, TYPE_D, xk, xj, xd); }

void CodeGenerator::xvpackev_b(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101010001011, TYPE_B, xk, xj, xd); }
void CodeGenerator::xvpackev_h(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101010001011, TYPE_H, xk, xj, xd); }
void CodeGenerator::xvpackev_w(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101010001011, TYPE_W, xk, xj, xd); }
void CodeGenerator::xvpackev_d(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101010001011, TYPE_D, xk, xj, xd); }

void CodeGenerator::xvpackod_b(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101010001100, TYPE_B, xk, xj, xd); }
void CodeGenerator::xvpackod_h(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101010001100, TYPE_H, xk, xj, xd); }
void CodeGenerator::xvpackod_w(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101010001100, TYPE_W, xk, xj, xd); }
void CodeGenerator::xvpackod_d(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101010001100, TYPE_D, xk, xj, xd); }

void CodeGenerator::xvilvl_b(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101010001101, TYPE_B, xk, xj, xd); }
void CodeGenerator::xvilvl_h(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101010001101, TYPE_H, xk, xj, xd); }
void CodeGenerator::xvilvl_w(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101010001101, TYPE_W, xk, xj, xd); }
void CodeGenerator::xvilvl_d(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101010001101, TYPE_D, xk, xj, xd); }

void CodeGenerator::xvilvh_b(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101010001110, TYPE_B, xk, xj, xd); }
void CodeGenerator::xvilvh_h(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101010001110, TYPE_H, xk, xj, xd); }
void CodeGenerator::xvilvh_w(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101010001110, TYPE_W, xk, xj, xd); }
void CodeGenerator::xvilvh_d(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101010001110, TYPE_D, xk, xj, xd); }

void CodeGenerator::xvpickev_b(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101010001111, TYPE_B, xk, xj, xd); }
void CodeGenerator::xvpickev_h(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101010001111, TYPE_H, xk, xj, xd); }
void CodeGenerator::xvpickev_w(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101010001111, TYPE_W, xk, xj, xd); }
void CodeGenerator::xvpickev_d(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101010001111, TYPE_D, xk, xj, xd); }

void CodeGenerator::xvpickod_b(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101010010000, TYPE_B, xk, xj, xd); }
void CodeGenerator::xvpickod_h(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101010010000, TYPE_H, xk, xj, xd); }
void CodeGenerator::xvpickod_w(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101010010000, TYPE_W, xk, xj, xd); }
void CodeGenerator::xvpickod_d(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101010010000, TYPE_D, xk, xj, xd); }

void CodeGenerator::xvreplve_b(const XVReg &xd, const XVReg &xj, const XReg &rk) { LasxFormat3R(0b011101010010001, TYPE_B, rk, xj, xd); }
void CodeGenerator::xvreplve_h(const XVReg &xd, const XVReg &xj, const XReg &rk) { LasxFormat3R(0b011101010010001, TYPE_H, rk, xj, xd); }
void CodeGenerator::xvreplve_w(const XVReg &xd, const XVReg &xj, const XReg &rk) { LasxFormat3R(0b011101010010001, TYPE_W, rk, xj, xd); }
void CodeGenerator::xvreplve_d(const XVReg &xd, const XVReg &xj, const XReg &rk) { LasxFormat3R(0b011101010010001, TYPE_D, rk, xj, xd); }

void CodeGenerator::xvand_v(const XVReg &xd, const XVReg &xj, const XVReg &xk)  { LasxFormat3RVec(0b01110101001001100, xk, xj, xd); }
void CodeGenerator::xvor_v(const XVReg &xd, const XVReg &xj, const XVReg &xk)   { LasxFormat3RVec(0b01110101001001101, xk, xj, xd); }
void CodeGenerator::xvxor_v(const XVReg &xd, const XVReg &xj, const XVReg &xk)  { LasxFormat3RVec(0b01110101001001110, xk, xj, xd); }
void CodeGenerator::xvnor_v(const XVReg &xd, const XVReg &xj, const XVReg &xk)  { LasxFormat3RVec(0b01110101001001111, xk, xj, xd); }
void CodeGenerator::xvandn_v(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3RVec(0b01110101001010000, xk, xj, xd); }
void CodeGenerator::xvorn_v(const XVReg &xd, const XVReg &xj, const XVReg &xk)  { LasxFormat3RVec(0b01110101001010001, xk, xj, xd); }

void CodeGenerator::xvfrstp_b(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101010010101, 0b10, xk, xj, xd); }
void CodeGenerator::xvfrstp_h(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101010010101, 0b11, xk, xj, xd); }

void CodeGenerator::xvadd_q(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3RVec(0b01110101001011010, xk, xj, xd); }

void CodeGenerator::xvsub_q(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3RVec(0b01110101001011011, xk, xj, xd); }

void CodeGenerator::xvsigncov_b(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101010010111, TYPE_B, xk, xj, xd); }
void CodeGenerator::xvsigncov_h(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101010010111, TYPE_H, xk, xj, xd); }
void CodeGenerator::xvsigncov_w(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101010010111, TYPE_W, xk, xj, xd); }
void CodeGenerator::xvsigncov_d(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101010010111, TYPE_D, xk, xj, xd); }

void CodeGenerator::xvfadd_s(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101010011000, FP_S, xk, xj, xd); }
void CodeGenerator::xvfadd_d(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101010011000, FP_D, xk, xj, xd); }

void CodeGenerator::xvfsub_s(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101010011001, FP_S, xk, xj, xd); }
void CodeGenerator::xvfsub_d(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101010011001, FP_D, xk, xj, xd); }

void CodeGenerator::xvfmul_s(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101010011100, FP_S, xk, xj, xd); }
void CodeGenerator::xvfmul_d(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101010011100, FP_D, xk, xj, xd); }

void CodeGenerator::xvfdiv_s(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101010011101, FP_S, xk, xj, xd); }
void CodeGenerator::xvfdiv_d(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101010011101, FP_D, xk, xj, xd); }

void CodeGenerator::xvfmax_s(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101010011110, FP_S, xk, xj, xd); }
void CodeGenerator::xvfmax_d(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101010011110, FP_D, xk, xj, xd); }

void CodeGenerator::xvfmin_s(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101010011111, FP_S, xk, xj, xd); }
void CodeGenerator::xvfmin_d(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101010011111, FP_D, xk, xj, xd); }

void CodeGenerator::xvfmaxa_s(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101010100000, FP_S, xk, xj, xd); }
void CodeGenerator::xvfmaxa_d(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101010100000, FP_D, xk, xj, xd); }

void CodeGenerator::xvfmina_s(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101010100001, FP_S, xk, xj, xd); }
void CodeGenerator::xvfmina_d(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101010100001, FP_D, xk, xj, xd); }

void CodeGenerator::xvfscaleb_s(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101010100010, FP_S, xk, xj, xd); }
void CodeGenerator::xvfscaleb_d(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101010100010, FP_D, xk, xj, xd); }

void CodeGenerator::xvfcvt_h_s(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101010100011, 0b00, xk, xj, xd); }
void CodeGenerator::xvfcvt_s_d(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101010100011, 0b01, xk, xj, xd); }

void CodeGenerator::xvffint_s_l(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101010100100, 0b00, xk, xj, xd); }
void CodeGenerator::xvftint_w_d(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101010100100, 0b11, xk, xj, xd); }

void CodeGenerator::xvftintrm_w_d(const XVReg &xd, const XVReg &xj, const XVReg &xk)  { LasxFormat3R(0b011101010100101, 0b00, xk, xj, xd); }
void CodeGenerator::xvftintrp_w_d(const XVReg &xd, const XVReg &xj, const XVReg &xk)  { LasxFormat3R(0b011101010100101, 0b01, xk, xj, xd); }
void CodeGenerator::xvftintrz_w_d(const XVReg &xd, const XVReg &xj, const XVReg &xk)  { LasxFormat3R(0b011101010100101, 0b10, xk, xj, xd); }
void CodeGenerator::xvftintrne_w_d(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101010100101, 0b11, xk, xj, xd); }

void CodeGenerator::xvshuf_h(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101010111101, TYPE_H, xk, xj, xd); }
void CodeGenerator::xvshuf_w(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101010111101, TYPE_W, xk, xj, xd); }
void CodeGenerator::xvshuf_d(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101010111101, TYPE_D, xk, xj, xd); }

void CodeGenerator::xvperm_w(const XVReg &xd, const XVReg &xj, const XVReg &xk) { LasxFormat3R(0b011101010111110, TYPE_W, xk, xj, xd); }

void CodeGenerator::xvseqi_b(const XVReg &xd, const XVReg &xj, int32_t si5) { LasxFormatI5(0b011101101000000, TYPE_B, si5, xj, xd); }
void CodeGenerator::xvseqi_h(const XVReg &xd, const XVReg &xj, int32_t si5) { LasxFormatI5(0b011101101000000, TYPE_H, si5, xj, xd); }
void CodeGenerator::xvseqi_w(const XVReg &xd, const XVReg &xj, int32_t si5) { LasxFormatI5(0b011101101000000, TYPE_W, si5, xj, xd); }
void CodeGenerator::xvseqi_d(const XVReg &xd, const XVReg &xj, int32_t si5) { LasxFormatI5(0b011101101000000, TYPE_D, si5, xj, xd); }

void CodeGenerator::xvslei_b(const XVReg &xd, const XVReg &xj, int32_t si5) { LasxFormatI5(0b011101101000001, TYPE_B, si5, xj, xd); }
void CodeGenerator::xvslei_h(const XVReg &xd, const XVReg &xj, int32_t si5) { LasxFormatI5(0b011101101000001, TYPE_H, si5, xj, xd); }
void CodeGenerator::xvslei_w(const XVReg &xd, const XVReg &xj, int32_t si5) { LasxFormatI5(0b011101101000001, TYPE_W, si5, xj, xd); }
void CodeGenerator::xvslei_d(const XVReg &xd, const XVReg &xj, int32_t si5) { LasxFormatI5(0b011101101000001, TYPE_D, si5, xj, xd); }

void CodeGenerator::xvslei_bu(const XVReg &xd, const XVReg &xj, uint32_t ui5) { LasxFormatI5(0b011101101000010, TYPE_B, ui5, xj, xd); }
void CodeGenerator::xvslei_hu(const XVReg &xd, const XVReg &xj, uint32_t ui5) { LasxFormatI5(0b011101101000010, TYPE_H, ui5, xj, xd); }
void CodeGenerator::xvslei_wu(const XVReg &xd, const XVReg &xj, uint32_t ui5) { LasxFormatI5(0b011101101000010, TYPE_W, ui5, xj, xd); }
void CodeGenerator::xvslei_du(const XVReg &xd, const XVReg &xj, uint32_t ui5) { LasxFormatI5(0b011101101000010, TYPE_D, ui5, xj, xd); }

void CodeGenerator::xvslti_b(const XVReg &xd, const XVReg &xj, int32_t si5) { LasxFormatI5(0b011101101000011, TYPE_B, si5, xj, xd); }
void CodeGenerator::xvslti_h(const XVReg &xd, const XVReg &xj, int32_t si5) { LasxFormatI5(0b011101101000011, TYPE_H, si5, xj, xd); }
void CodeGenerator::xvslti_w(const XVReg &xd, const XVReg &xj, int32_t si5) { LasxFormatI5(0b011101101000011, TYPE_W, si5, xj, xd); }
void CodeGenerator::xvslti_d(const XVReg &xd, const XVReg &xj, int32_t si5) { LasxFormatI5(0b011101101000011, TYPE_D, si5, xj, xd); }

void CodeGenerator::xvslti_bu(const XVReg &xd, const XVReg &xj, uint32_t ui5) { LasxFormatI5(0b011101101000100, TYPE_B, ui5, xj, xd); }
void CodeGenerator::xvslti_hu(const XVReg &xd, const XVReg &xj, uint32_t ui5) { LasxFormatI5(0b011101101000100, TYPE_H, ui5, xj, xd); }
void CodeGenerator::xvslti_wu(const XVReg &xd, const XVReg &xj, uint32_t ui5) { LasxFormatI5(0b011101101000100, TYPE_W, ui5, xj, xd); }
void CodeGenerator::xvslti_du(const XVReg &xd, const XVReg &xj, uint32_t ui5) { LasxFormatI5(0b011101101000100, TYPE_D, ui5, xj, xd); }

void CodeGenerator::xvaddi_bu(const XVReg &xd, const XVReg &xj, uint32_t ui5) { LasxFormatI5(0b011101101000101, TYPE_B, ui5, xj, xd); }
void CodeGenerator::xvaddi_hu(const XVReg &xd, const XVReg &xj, uint32_t ui5) { LasxFormatI5(0b011101101000101, TYPE_H, ui5, xj, xd); }
void CodeGenerator::xvaddi_wu(const XVReg &xd, const XVReg &xj, uint32_t ui5) { LasxFormatI5(0b011101101000101, TYPE_W, ui5, xj, xd); }
void CodeGenerator::xvaddi_du(const XVReg &xd, const XVReg &xj, uint32_t ui5) { LasxFormatI5(0b011101101000101, TYPE_D, ui5, xj, xd); }

void CodeGenerator::xvsubi_bu(const XVReg &xd, const XVReg &xj, uint32_t ui5) { LasxFormatI5(0b011101101000110, TYPE_B, ui5, xj, xd); }
void CodeGenerator::xvsubi_hu(const XVReg &xd, const XVReg &xj, uint32_t ui5) { LasxFormatI5(0b011101101000110, TYPE_H, ui5, xj, xd); }
void CodeGenerator::xvsubi_wu(const XVReg &xd, const XVReg &xj, uint32_t ui5) { LasxFormatI5(0b011101101000110, TYPE_W, ui5, xj, xd); }
void CodeGenerator::xvsubi_du(const XVReg &xd, const XVReg &xj, uint32_t ui5) { LasxFormatI5(0b011101101000110, TYPE_D, ui5, xj, xd); }

void CodeGenerator::xvbsll_v(const XVReg &xd, const XVReg &xj, uint32_t ui5) { LasxFormatI5(0b011101101000111, 0b00, ui5, xj, xd); }
void CodeGenerator::xvbsrl_v(const XVReg &xd, const XVReg &xj, uint32_t ui5) { LasxFormatI5(0b011101101000111, 0b01, ui5, xj, xd); }

void CodeGenerator::xvmaxi_b(const XVReg &xd, const XVReg &xj, int32_t si5) { LasxFormatI5(0b011101101001000, TYPE_B, si5, xj, xd); }
void CodeGenerator::xvmaxi_h(const XVReg &xd, const XVReg &xj, int32_t si5) { LasxFormatI5(0b011101101001000, TYPE_H, si5, xj, xd); }
void CodeGenerator::xvmaxi_w(const XVReg &xd, const XVReg &xj, int32_t si5) { LasxFormatI5(0b011101101001000, TYPE_W, si5, xj, xd); }
void CodeGenerator::xvmaxi_d(const XVReg &xd, const XVReg &xj, int32_t si5) { LasxFormatI5(0b011101101001000, TYPE_D, si5, xj, xd); }

void CodeGenerator::xvmini_b(const XVReg &xd, const XVReg &xj, int32_t si5) { LasxFormatI5(0b011101101001001, TYPE_B, si5, xj, xd); }
void CodeGenerator::xvmini_h(const XVReg &xd, const XVReg &xj, int32_t si5) { LasxFormatI5(0b011101101001001, TYPE_H, si5, xj, xd); }
void CodeGenerator::xvmini_w(const XVReg &xd, const XVReg &xj, int32_t si5) { LasxFormatI5(0b011101101001001, TYPE_W, si5, xj, xd); }
void CodeGenerator::xvmini_d(const XVReg &xd, const XVReg &xj, int32_t si5) { LasxFormatI5(0b011101101001001, TYPE_D, si5, xj, xd); }

void CodeGenerator::xvmaxi_bu(const XVReg &xd, const XVReg &xj, uint32_t ui5) { LasxFormatI5(0b011101101001010, TYPE_B, ui5, xj, xd); }
void CodeGenerator::xvmaxi_hu(const XVReg &xd, const XVReg &xj, uint32_t ui5) { LasxFormatI5(0b011101101001010, TYPE_H, ui5, xj, xd); }
void CodeGenerator::xvmaxi_wu(const XVReg &xd, const XVReg &xj, uint32_t ui5) { LasxFormatI5(0b011101101001010, TYPE_W, ui5, xj, xd); }
void CodeGenerator::xvmaxi_du(const XVReg &xd, const XVReg &xj, uint32_t ui5) { LasxFormatI5(0b011101101001010, TYPE_D, ui5, xj, xd); }

void CodeGenerator::xvmini_bu(const XVReg &xd, const XVReg &xj, uint32_t ui5) { LasxFormatI5(0b011101101001011, TYPE_B, ui5, xj, xd); }
void CodeGenerator::xvmini_hu(const XVReg &xd, const XVReg &xj, uint32_t ui5) { LasxFormatI5(0b011101101001011, TYPE_H, ui5, xj, xd); }
void CodeGenerator::xvmini_wu(const XVReg &xd, const XVReg &xj, uint32_t ui5) { LasxFormatI5(0b011101101001011, TYPE_W, ui5, xj, xd); }
void CodeGenerator::xvmini_du(const XVReg &xd, const XVReg &xj, uint32_t ui5) { LasxFormatI5(0b011101101001011, TYPE_D, ui5, xj, xd); }

void CodeGenerator::xvfrstpi_b(const XVReg &xd, const XVReg &xj, uint32_t ui5) { LasxFormatI5(0b011101101001101, TYPE_B, ui5, xj, xd); }
void CodeGenerator::xvfrstpi_h(const XVReg &xd, const XVReg &xj, uint32_t ui5) { LasxFormatI5(0b011101101001101, TYPE_H, ui5, xj, xd); }

void CodeGenerator::xvmepatmsk_v(const XVReg &xd, int32_t mode, uint32_t ui5) { LasxFormatI5Mode(0b01110110100110111, ui5, mode, xd); }

void CodeGenerator::xvclo_b(const XVReg &xd, const XVReg &xj) { LasxFormat2R(0b01110110100111000000, TYPE_B, xj, xd); }
void CodeGenerator::xvclo_h(const XVReg &xd, const XVReg &xj) { LasxFormat2R(0b01110110100111000000, TYPE_H, xj, xd); }
void CodeGenerator::xvclo_w(const XVReg &xd, const XVReg &xj) { LasxFormat2R(0b01110110100111000000, TYPE_W, xj, xd); }
void CodeGenerator::xvclo_d(const XVReg &xd, const XVReg &xj) { LasxFormat2R(0b01110110100111000000, TYPE_D, xj, xd); }

void CodeGenerator::xvclz_b(const XVReg &xd, const XVReg &xj) { LasxFormat2R(0b01110110100111000001, TYPE_B, xj, xd); }
void CodeGenerator::xvclz_h(const XVReg &xd, const XVReg &xj) { LasxFormat2R(0b01110110100111000001, TYPE_H, xj, xd); }
void CodeGenerator::xvclz_w(const XVReg &xd, const XVReg &xj) { LasxFormat2R(0b01110110100111000001, TYPE_W, xj, xd); }
void CodeGenerator::xvclz_d(const XVReg &xd, const XVReg &xj) { LasxFormat2R(0b01110110100111000001, TYPE_D, xj, xd); }

void CodeGenerator::xvpcnt_b(const XVReg &xd, const XVReg &xj) { LasxFormat2R(0b01110110100111000010, TYPE_B, xj, xd); }
void CodeGenerator::xvpcnt_h(const XVReg &xd, const XVReg &xj) { LasxFormat2R(0b01110110100111000010, TYPE_H, xj, xd); }
void CodeGenerator::xvpcnt_w(const XVReg &xd, const XVReg &xj) { LasxFormat2R(0b01110110100111000010, TYPE_W, xj, xd); }
void CodeGenerator::xvpcnt_d(const XVReg &xd, const XVReg &xj) { LasxFormat2R(0b01110110100111000010, TYPE_D, xj, xd); }

void CodeGenerator::xvneg_b(const XVReg &xd, const XVReg &xj) { LasxFormat2R(0b01110110100111000011, TYPE_B, xj, xd); }
void CodeGenerator::xvneg_h(const XVReg &xd, const XVReg &xj) { LasxFormat2R(0b01110110100111000011, TYPE_H, xj, xd); }
void CodeGenerator::xvneg_w(const XVReg &xd, const XVReg &xj) { LasxFormat2R(0b01110110100111000011, TYPE_W, xj, xd); }
void CodeGenerator::xvneg_d(const XVReg &xd, const XVReg &xj) { LasxFormat2R(0b01110110100111000011, TYPE_D, xj, xd); }

void CodeGenerator::xvmskltz_b(const XVReg &xd, const XVReg &xj) { LasxFormat2R(0b01110110100111000100, TYPE_B, xj, xd); }
void CodeGenerator::xvmskltz_h(const XVReg &xd, const XVReg &xj) { LasxFormat2R(0b01110110100111000100, TYPE_H, xj, xd); }
void CodeGenerator::xvmskltz_w(const XVReg &xd, const XVReg &xj) { LasxFormat2R(0b01110110100111000100, TYPE_W, xj, xd); }
void CodeGenerator::xvmskltz_d(const XVReg &xd, const XVReg &xj) { LasxFormat2R(0b01110110100111000100, TYPE_D, xj, xd); }

void CodeGenerator::xvmskgez_b(const XVReg &xd, const XVReg &xj) { LasxFormat2R(0b01110110100111000101, TYPE_B, xj, xd); }

void CodeGenerator::xvmsknz_b(const XVReg &xd, const XVReg &xj)  { LasxFormat2R(0b01110110100111000110, TYPE_B, xj, xd); }

void CodeGenerator::xvseteqz_v(uint32_t cd, const XVReg &xj) { LasxFormatCFR(0b01110110100111001001, 0b10, xj, cd); }
void CodeGenerator::xvsetnez_v(uint32_t cd, const XVReg &xj) { LasxFormatCFR(0b01110110100111001001, 0b11, xj, cd); }

void CodeGenerator::xvsetanyeqz_b(uint32_t cd, const XVReg &xj) { LasxFormatCFR(0b01110110100111001010, TYPE_B, xj, cd); }
void CodeGenerator::xvsetanyeqz_h(uint32_t cd, const XVReg &xj) { LasxFormatCFR(0b01110110100111001010, TYPE_H, xj, cd); }
void CodeGenerator::xvsetanyeqz_w(uint32_t cd, const XVReg &xj) { LasxFormatCFR(0b01110110100111001010, TYPE_W, xj, cd); }
void CodeGenerator::xvsetanyeqz_d(uint32_t cd, const XVReg &xj) { LasxFormatCFR(0b01110110100111001010, TYPE_D, xj, cd); }

void CodeGenerator::xvsetallnez_b(uint32_t cd, const XVReg &xj) { LasxFormatCFR(0b01110110100111001011, TYPE_B, xj, cd); }
void CodeGenerator::xvsetallnez_h(uint32_t cd, const XVReg &xj) { LasxFormatCFR(0b01110110100111001011, TYPE_H, xj, cd); }
void CodeGenerator::xvsetallnez_w(uint32_t cd, const XVReg &xj) { LasxFormatCFR(0b01110110100111001011, TYPE_W, xj, cd); }
void CodeGenerator::xvsetallnez_d(uint32_t cd, const XVReg &xj) { LasxFormatCFR(0b01110110100111001011, TYPE_D, xj, cd); }

void CodeGenerator::xvflogb_s(const XVReg &xd, const XVReg &xj) { LasxFormat2R(0b01110110100111001100, FP_S, xj, xd); }
void CodeGenerator::xvflogb_d(const XVReg &xd, const XVReg &xj) { LasxFormat2R(0b01110110100111001100, FP_D, xj, xd); }

void CodeGenerator::xvfclass_s(const XVReg &xd, const XVReg &xj) { LasxFormat2R(0b01110110100111001101, FP_S, xj, xd); }
void CodeGenerator::xvfclass_d(const XVReg &xd, const XVReg &xj) { LasxFormat2R(0b01110110100111001101, FP_D, xj, xd); }

void CodeGenerator::xvfsqrt_s(const XVReg &xd, const XVReg &xj) { LasxFormat2R(0b01110110100111001110, FP_S, xj, xd); }
void CodeGenerator::xvfsqrt_d(const XVReg &xd, const XVReg &xj) { LasxFormat2R(0b01110110100111001110, FP_D, xj, xd); }

void CodeGenerator::xvfrecip_s(const XVReg &xd, const XVReg &xj) { LasxFormat2R(0b01110110100111001111, FP_S, xj, xd); }
void CodeGenerator::xvfrecip_d(const XVReg &xd, const XVReg &xj) { LasxFormat2R(0b01110110100111001111, FP_D, xj, xd); }

void CodeGenerator::xvfrsqrt_s(const XVReg &xd, const XVReg &xj) { LasxFormat2R(0b01110110100111010000, FP_S, xj, xd); }
void CodeGenerator::xvfrsqrt_d(const XVReg &xd, const XVReg &xj) { LasxFormat2R(0b01110110100111010000, FP_D, xj, xd); }

void CodeGenerator::xvfrint_s(const XVReg &xd, const XVReg &xj) { LasxFormat2R(0b01110110100111010011, FP_S, xj, xd); }
void CodeGenerator::xvfrint_d(const XVReg &xd, const XVReg &xj) { LasxFormat2R(0b01110110100111010011, FP_D, xj, xd); }

void CodeGenerator::xvfrintrm_s(const XVReg &xd, const XVReg &xj) { LasxFormat2R(0b01110110100111010100, FP_S, xj, xd); }
void CodeGenerator::xvfrintrm_d(const XVReg &xd, const XVReg &xj) { LasxFormat2R(0b01110110100111010100, FP_D, xj, xd); }

void CodeGenerator::xvfrintrp_s(const XVReg &xd, const XVReg &xj) { LasxFormat2R(0b01110110100111010101, FP_S, xj, xd); }
void CodeGenerator::xvfrintrp_d(const XVReg &xd, const XVReg &xj) { LasxFormat2R(0b01110110100111010101, FP_D, xj, xd); }

void CodeGenerator::xvfrintrz_s(const XVReg &xd, const XVReg &xj) { LasxFormat2R(0b01110110100111010110, FP_S, xj, xd); }
void CodeGenerator::xvfrintrz_d(const XVReg &xd, const XVReg &xj) { LasxFormat2R(0b01110110100111010110, FP_D, xj, xd); }

void CodeGenerator::xvfrintrne_s(const XVReg &xd, const XVReg &xj) { LasxFormat2R(0b01110110100111010111, FP_S, xj, xd); }
void CodeGenerator::xvfrintrne_d(const XVReg &xd, const XVReg &xj) { LasxFormat2R(0b01110110100111010111, FP_D, xj, xd); }

void CodeGenerator::xvfcvtl_s_h(const XVReg &xd, const XVReg &xj) { LasxFormat2R(0b01110110100111011110, 0b10, xj, xd); }
void CodeGenerator::xvfcvth_s_h(const XVReg &xd, const XVReg &xj) { LasxFormat2R(0b01110110100111011110, 0b11, xj, xd); }

void CodeGenerator::xvfcvtl_d_s(const XVReg &xd, const XVReg &xj) { LasxFormat2R(0b01110110100111011111, 0b00, xj, xd); }
void CodeGenerator::xvfcvth_d_s(const XVReg &xd, const XVReg &xj) { LasxFormat2R(0b01110110100111011111, 0b01, xj, xd); }

void CodeGenerator::xvffint_s_w(const XVReg &xd, const XVReg &xj)  { LasxFormat2R(0b01110110100111100000, 0b00, xj, xd); }
void CodeGenerator::xvffint_s_wu(const XVReg &xd, const XVReg &xj) { LasxFormat2R(0b01110110100111100000, 0b01, xj, xd); }
void CodeGenerator::xvffint_d_l(const XVReg &xd, const XVReg &xj)  { LasxFormat2R(0b01110110100111100000, 0b10, xj, xd); }
void CodeGenerator::xvffint_d_lu(const XVReg &xd, const XVReg &xj) { LasxFormat2R(0b01110110100111100000, 0b11, xj, xd); }

void CodeGenerator::xvffintl_d_w(const XVReg &xd, const XVReg &xj) { LasxFormat2R(0b01110110100111100001, 0b00, xj, xd); }
void CodeGenerator::xvffinth_d_w(const XVReg &xd, const XVReg &xj) { LasxFormat2R(0b01110110100111100001, 0b01, xj, xd); }

void CodeGenerator::xvftint_w_s(const XVReg &xd, const XVReg &xj) { LasxFormat2R(0b01110110100111100011, 0b00, xj, xd); }
void CodeGenerator::xvftint_l_d(const XVReg &xd, const XVReg &xj) { LasxFormat2R(0b01110110100111100011, 0b01, xj, xd); }

void CodeGenerator::xvftintrm_w_s(const XVReg &xd, const XVReg &xj) { LasxFormat2R(0b01110110100111100011, 0b10, xj, xd); }
void CodeGenerator::xvftintrm_l_d(const XVReg &xd, const XVReg &xj) { LasxFormat2R(0b01110110100111100011, 0b11, xj, xd); }

void CodeGenerator::xvftintrp_w_s(const XVReg &xd, const XVReg &xj) { LasxFormat2R(0b01110110100111100100, 0b00, xj, xd); }
void CodeGenerator::xvftintrp_l_d(const XVReg &xd, const XVReg &xj) { LasxFormat2R(0b01110110100111100100, 0b01, xj, xd); }

void CodeGenerator::xvftintrz_w_s(const XVReg &xd, const XVReg &xj) { LasxFormat2R(0b01110110100111100100, 0b10, xj, xd); }
void CodeGenerator::xvftintrz_l_d(const XVReg &xd, const XVReg &xj) { LasxFormat2R(0b01110110100111100100, 0b11, xj, xd); }

void CodeGenerator::xvftintrne_w_s(const XVReg &xd, const XVReg &xj) { LasxFormat2R(0b01110110100111100101, 0b00, xj, xd); }
void CodeGenerator::xvftintrne_l_d(const XVReg &xd, const XVReg &xj) { LasxFormat2R(0b01110110100111100101, 0b01, xj, xd); }

void CodeGenerator::xvftint_wu_s(const XVReg &xd, const XVReg &xj) { LasxFormat2R(0b01110110100111100101, 0b10, xj, xd); }
void CodeGenerator::xvftint_lu_d(const XVReg &xd, const XVReg &xj) { LasxFormat2R(0b01110110100111100101, 0b11, xj, xd); }

void CodeGenerator::xvftintrz_wu_s(const XVReg &xd, const XVReg &xj) { LasxFormat2R(0b01110110100111100111, 0b00, xj, xd); }
void CodeGenerator::xvftintrz_lu_d(const XVReg &xd, const XVReg &xj) { LasxFormat2R(0b01110110100111100111, 0b01, xj, xd); }

void CodeGenerator::xvftintl_l_s(const XVReg &xd, const XVReg &xj) { LasxFormat2R(0b01110110100111101000, 0b00, xj, xd); }
void CodeGenerator::xvftinth_l_s(const XVReg &xd, const XVReg &xj) { LasxFormat2R(0b01110110100111101000, 0b01, xj, xd); }

void CodeGenerator::xvftintrml_l_s(const XVReg &xd, const XVReg &xj) { LasxFormat2R(0b01110110100111101000, 0b10, xj, xd); }
void CodeGenerator::xvftintrmh_l_s(const XVReg &xd, const XVReg &xj) { LasxFormat2R(0b01110110100111101000, 0b11, xj, xd); }

void CodeGenerator::xvftintrpl_l_s(const XVReg &xd, const XVReg &xj) { LasxFormat2R(0b01110110100111101001, 0b00, xj, xd); }
void CodeGenerator::xvftintrph_l_s(const XVReg &xd, const XVReg &xj) { LasxFormat2R(0b01110110100111101001, 0b01, xj, xd); }

void CodeGenerator::xvftintrzl_l_s(const XVReg &xd, const XVReg &xj) { LasxFormat2R(0b01110110100111101001, 0b10, xj, xd); }
void CodeGenerator::xvftintrzh_l_s(const XVReg &xd, const XVReg &xj) { LasxFormat2R(0b01110110100111101001, 0b11, xj, xd); }

void CodeGenerator::xvftintrnel_l_s(const XVReg &xd, const XVReg &xj) { LasxFormat2R(0b01110110100111101010, 0b00, xj, xd); }
void CodeGenerator::xvftintrneh_l_s(const XVReg &xd, const XVReg &xj) { LasxFormat2R(0b01110110100111101010, 0b01, xj, xd); }

void CodeGenerator::xvexth_h_b(const XVReg &xd, const XVReg &xj) { LasxFormat2R(0b01110110100111101110, TYPE_B, xj, xd); }
void CodeGenerator::xvexth_w_h(const XVReg &xd, const XVReg &xj) { LasxFormat2R(0b01110110100111101110, TYPE_H, xj, xd); }
void CodeGenerator::xvexth_d_w(const XVReg &xd, const XVReg &xj) { LasxFormat2R(0b01110110100111101110, TYPE_W, xj, xd); }
void CodeGenerator::xvexth_q_d(const XVReg &xd, const XVReg &xj) { LasxFormat2R(0b01110110100111101110, TYPE_D, xj, xd); }

void CodeGenerator::xvexth_hu_bu(const XVReg &xd, const XVReg &xj) { LasxFormat2R(0b01110110100111101111, TYPE_B, xj, xd); }
void CodeGenerator::xvexth_wu_hu(const XVReg &xd, const XVReg &xj) { LasxFormat2R(0b01110110100111101111, TYPE_H, xj, xd); }
void CodeGenerator::xvexth_du_wu(const XVReg &xd, const XVReg &xj) { LasxFormat2R(0b01110110100111101111, TYPE_W, xj, xd); }
void CodeGenerator::xvexth_qu_du(const XVReg &xd, const XVReg &xj) { LasxFormat2R(0b01110110100111101111, TYPE_D, xj, xd); }

void CodeGenerator::vext2xv_h_b(const XVReg &xd, const XVReg &xj) { Loongarch2Reg(0b0111011010011111000100, xj.getIdx(), xd.getIdx()); }
void CodeGenerator::vext2xv_w_b(const XVReg &xd, const XVReg &xj) { Loongarch2Reg(0b0111011010011111000101, xj.getIdx(), xd.getIdx()); }
void CodeGenerator::vext2xv_d_b(const XVReg &xd, const XVReg &xj) { Loongarch2Reg(0b0111011010011111000110, xj.getIdx(), xd.getIdx()); }
void CodeGenerator::vext2xv_w_h(const XVReg &xd, const XVReg &xj) { Loongarch2Reg(0b0111011010011111000111, xj.getIdx(), xd.getIdx()); }
void CodeGenerator::vext2xv_d_h(const XVReg &xd, const XVReg &xj) { Loongarch2Reg(0b0111011010011111001000, xj.getIdx(), xd.getIdx()); }
void CodeGenerator::vext2xv_d_w(const XVReg &xd, const XVReg &xj) { Loongarch2Reg(0b0111011010011111001001, xj.getIdx(), xd.getIdx()); }
void CodeGenerator::vext2xv_hu_bu(const XVReg &xd, const XVReg &xj) { Loongarch2Reg(0b0111011010011111001010, xj.getIdx(), xd.getIdx()); }
void CodeGenerator::vext2xv_wu_bu(const XVReg &xd, const XVReg &xj) { Loongarch2Reg(0b0111011010011111001011, xj.getIdx(), xd.getIdx()); }
void CodeGenerator::vext2xv_du_bu(const XVReg &xd, const XVReg &xj) { Loongarch2Reg(0b0111011010011111001100, xj.getIdx(), xd.getIdx()); }
void CodeGenerator::vext2xv_wu_hu(const XVReg &xd, const XVReg &xj) { Loongarch2Reg(0b0111011010011111001101, xj.getIdx(), xd.getIdx()); }
void CodeGenerator::vext2xv_du_hu(const XVReg &xd, const XVReg &xj) { Loongarch2Reg(0b0111011010011111001110, xj.getIdx(), xd.getIdx()); }
void CodeGenerator::vext2xv_du_wu(const XVReg &xd, const XVReg &xj) { Loongarch2Reg(0b0111011010011111001111, xj.getIdx(), xd.getIdx()); }

void CodeGenerator::xvreplgr2vr_b(const XVReg &xd, const XReg &rj) { LasxFormat2R(0b01110110100111110000, TYPE_B, rj, xd); }
void CodeGenerator::xvreplgr2vr_h(const XVReg &xd, const XReg &rj) { LasxFormat2R(0b01110110100111110000, TYPE_H, rj, xd); }
void CodeGenerator::xvreplgr2vr_w(const XVReg &xd, const XReg &rj) { LasxFormat2R(0b01110110100111110000, TYPE_W, rj, xd); }
void CodeGenerator::xvreplgr2vr_d(const XVReg &xd, const XReg &rj) { LasxFormat2R(0b01110110100111110000, TYPE_D, rj, xd); }

void CodeGenerator::xvhseli_d(const XVReg &xd, const XVReg &xj, uint32_t ui5) { LasxFormatI5(0b011101101001111, 0b11, ui5, xj, xd); }

void CodeGenerator::xvrotri_b(const XVReg &xd, const XVReg &xj, uint32_t imm) { LasxFormatBIT(0b01110110101000, TYPE_B, imm, xj, xd); }
void CodeGenerator::xvrotri_h(const XVReg &xd, const XVReg &xj, uint32_t imm) { LasxFormatBIT(0b01110110101000, TYPE_H, imm, xj, xd); }
void CodeGenerator::xvrotri_w(const XVReg &xd, const XVReg &xj, uint32_t imm) { LasxFormatBIT(0b01110110101000, TYPE_W, imm, xj, xd); }
void CodeGenerator::xvrotri_d(const XVReg &xd, const XVReg &xj, uint32_t imm) { LasxFormatBIT(0b01110110101000, TYPE_D, imm, xj, xd); }

void CodeGenerator::xvsrlri_b(const XVReg &xd, const XVReg &xj, uint32_t imm) { LasxFormatBIT(0b01110110101001, TYPE_B, imm, xj, xd); }
void CodeGenerator::xvsrlri_h(const XVReg &xd, const XVReg &xj, uint32_t imm) { LasxFormatBIT(0b01110110101001, TYPE_H, imm, xj, xd); }
void CodeGenerator::xvsrlri_w(const XVReg &xd, const XVReg &xj, uint32_t imm) { LasxFormatBIT(0b01110110101001, TYPE_W, imm, xj, xd); }
void CodeGenerator::xvsrlri_d(const XVReg &xd, const XVReg &xj, uint32_t imm) { LasxFormatBIT(0b01110110101001, TYPE_D, imm, xj, xd); }

void CodeGenerator::xvsrari_b(const XVReg &xd, const XVReg &xj, uint32_t imm) { LasxFormatBIT(0b01110110101010, TYPE_B, imm, xj, xd); }
void CodeGenerator::xvsrari_h(const XVReg &xd, const XVReg &xj, uint32_t imm) { LasxFormatBIT(0b01110110101010, TYPE_H, imm, xj, xd); }
void CodeGenerator::xvsrari_w(const XVReg &xd, const XVReg &xj, uint32_t imm) { LasxFormatBIT(0b01110110101010, TYPE_W, imm, xj, xd); }
void CodeGenerator::xvsrari_d(const XVReg &xd, const XVReg &xj, uint32_t imm) { LasxFormatBIT(0b01110110101010, TYPE_D, imm, xj, xd); }

void CodeGenerator::vinsgr2vr_b(const VReg &vd, const XReg &rj, uint32_t ui4) { LasxFormatELM(0b01110010111010, TYPE_B, ui4, rj, vd); }
void CodeGenerator::vinsgr2vr_h(const VReg &vd, const XReg &rj, uint32_t ui3) { LasxFormatELM(0b01110010111010, TYPE_H, ui3, rj, vd); }
void CodeGenerator::vinsgr2vr_w(const VReg &vd, const XReg &rj, uint32_t ui2) { LasxFormatELM(0b01110010111010, TYPE_W, ui2, rj, vd); }
void CodeGenerator::vinsgr2vr_d(const VReg &vd, const XReg &rj, uint32_t ui1) { LasxFormatELM(0b01110010111010, TYPE_D, ui1, rj, vd); }

void CodeGenerator::xvinsgr2vr_w(const XVReg &xd, const XReg &rj, uint32_t imm) { LasxFormatELM_1(0b01110110111010, TYPE_W, imm, rj, xd); }
void CodeGenerator::xvinsgr2vr_d(const XVReg &xd, const XReg &rj, uint32_t imm) { LasxFormatELM_1(0b01110110111010, TYPE_D, imm, rj, xd); }

void CodeGenerator::vpickve2gr_b(const XReg &rd, const VReg &vj, uint32_t ui4) { LasxFormatELM(0b01110010111011, TYPE_B, ui4, vj, rd); }
void CodeGenerator::vpickve2gr_h(const XReg &rd, const VReg &vj, uint32_t ui3) { LasxFormatELM(0b01110010111011, TYPE_H, ui3, vj, rd); }
void CodeGenerator::vpickve2gr_w(const XReg &rd, const VReg &vj, uint32_t ui2) { LasxFormatELM(0b01110010111011, TYPE_W, ui2, vj, rd); }
void CodeGenerator::vpickve2gr_d(const XReg &rd, const VReg &vj, uint32_t ui1) { LasxFormatELM(0b01110010111011, TYPE_D, ui1, vj, rd); }
void CodeGenerator::vpickve2gr_bu(const XReg &rd, const VReg &vj, uint32_t ui4) { LasxFormatELM(0b01110010111100, TYPE_B, ui4, vj, rd); }
void CodeGenerator::vpickve2gr_hu(const XReg &rd, const VReg &vj, uint32_t ui3) { LasxFormatELM(0b01110010111100, TYPE_H, ui3, vj, rd); }
void CodeGenerator::vpickve2gr_wu(const XReg &rd, const VReg &vj, uint32_t ui2) { LasxFormatELM(0b01110010111100, TYPE_W, ui2, vj, rd); }
void CodeGenerator::vpickve2gr_du(const XReg &rd, const VReg &vj, uint32_t ui1) { LasxFormatELM(0b01110010111100, TYPE_D, ui1, vj, rd); }

void CodeGenerator::xvpickve2gr_w(const XReg &rd, const XVReg &xj, uint32_t imm) { LasxFormatELM_1(0b01110110111011, TYPE_W, imm, xj, rd); }
void CodeGenerator::xvpickve2gr_d(const XReg &rd, const XVReg &xj, uint32_t imm) { LasxFormatELM_1(0b01110110111011, TYPE_D, imm, xj, rd); }

void CodeGenerator::xvpickve2gr_wu(const XReg &rd, const XVReg &xj, uint32_t imm) { LasxFormatELM_1(0b01110110111100, TYPE_W, imm, xj, rd); }
void CodeGenerator::xvpickve2gr_du(const XReg &rd, const XVReg &xj, uint32_t imm) { LasxFormatELM_1(0b01110110111100, TYPE_D, imm, xj, rd); }

void CodeGenerator::vreplvei_b(const VReg &vd, const VReg &vj, uint32_t ui4) { LasxFormatELM(0b01110010111101, TYPE_B, ui4, vj, vd); }
void CodeGenerator::vreplvei_h(const VReg &vd, const VReg &vj, uint32_t ui3) { LasxFormatELM(0b01110010111101, TYPE_H, ui3, vj, vd); }
void CodeGenerator::vreplvei_w(const VReg &vd, const VReg &vj, uint32_t ui2) { LasxFormatELM(0b01110010111101, TYPE_W, ui2, vj, vd); }
void CodeGenerator::vreplvei_d(const VReg &vd, const VReg &vj, uint32_t ui1) { LasxFormatELM(0b01110010111101, TYPE_D, ui1, vj, vd); }

void CodeGenerator::xvrepl128vei_b(const XVReg &xd, const XVReg &xj, uint32_t imm) { LasxFormatELM(0b01110110111101, TYPE_B, imm, xj, xd); }
void CodeGenerator::xvrepl128vei_h(const XVReg &xd, const XVReg &xj, uint32_t imm) { LasxFormatELM(0b01110110111101, TYPE_H, imm, xj, xd); }
void CodeGenerator::xvrepl128vei_w(const XVReg &xd, const XVReg &xj, uint32_t imm) { LasxFormatELM(0b01110110111101, TYPE_W, imm, xj, xd); }
void CodeGenerator::xvrepl128vei_d(const XVReg &xd, const XVReg &xj, uint32_t imm) { LasxFormatELM(0b01110110111101, TYPE_D, imm, xj, xd); }

void CodeGenerator::xvinsve0_w(const XVReg &xd, const XVReg &xj, uint32_t imm) { LasxFormatELM_1(0b01110110111111, TYPE_W, imm, xj, xd); }
void CodeGenerator::xvinsve0_d(const XVReg &xd, const XVReg &xj, uint32_t imm) { LasxFormatELM_1(0b01110110111111, TYPE_D, imm, xj, xd); }

void CodeGenerator::xvpickve_w(const XVReg &xd, const XVReg &xj, uint32_t imm) { LasxFormatELM_1(0b01110111000000, TYPE_W, imm, xj, xd); }
void CodeGenerator::xvpickve_d(const XVReg &xd, const XVReg &xj, uint32_t imm) { LasxFormatELM_1(0b01110111000000, TYPE_D, imm, xj, xd); }

void CodeGenerator::xvreplve0_b(const XVReg &xd, const XVReg &xj) { LasxFormat2RSubOp(0b01110111000001, 0b11000000, xj, xd); }
void CodeGenerator::xvreplve0_h(const XVReg &xd, const XVReg &xj) { LasxFormat2RSubOp(0b01110111000001, 0b11100000, xj, xd); }
void CodeGenerator::xvreplve0_w(const XVReg &xd, const XVReg &xj) { LasxFormat2RSubOp(0b01110111000001, 0b11110000, xj, xd); }
void CodeGenerator::xvreplve0_d(const XVReg &xd, const XVReg &xj) { LasxFormat2RSubOp(0b01110111000001, 0b11111000, xj, xd); }
void CodeGenerator::xvreplve0_q(const XVReg &xd, const XVReg &xj) { LasxFormat2RSubOp(0b01110111000001, 0b11111100, xj, xd); }

void CodeGenerator::xvsllwil_h_b(const XVReg &xd, const XVReg &xj, uint32_t imm) { LasxFormatBIT(0b01110111000010, TYPE_B, imm, xj, xd); }
void CodeGenerator::xvsllwil_w_h(const XVReg &xd, const XVReg &xj, uint32_t imm) { LasxFormatBIT(0b01110111000010, TYPE_H, imm, xj, xd); }
void CodeGenerator::xvsllwil_d_w(const XVReg &xd, const XVReg &xj, uint32_t imm) { LasxFormatBIT(0b01110111000010, TYPE_W, imm, xj, xd); }

void CodeGenerator::xvextl_q_d(const XVReg &xd, const XVReg &xj) { LasxFormat2RSubOp(0b01110111000010, 0b01000000, xj, xd); }

void CodeGenerator::xvsllwil_hu_bu(const XVReg &xd, const XVReg &xj, uint32_t imm) { LasxFormatBIT(0b01110111000011, TYPE_B, imm, xj, xd); }
void CodeGenerator::xvsllwil_wu_hu(const XVReg &xd, const XVReg &xj, uint32_t imm) { LasxFormatBIT(0b01110111000011, TYPE_H, imm, xj, xd); }
void CodeGenerator::xvsllwil_du_wu(const XVReg &xd, const XVReg &xj, uint32_t imm) { LasxFormatBIT(0b01110111000011, TYPE_W, imm, xj, xd); }

void CodeGenerator::xvextl_qu_du(const XVReg &xd, const XVReg &xj) { LasxFormat2RSubOp(0b01110111000011, 0b01000000, xj, xd); }

void CodeGenerator::xvbitclri_b(const XVReg &xd, const XVReg &xj, uint32_t imm) { LasxFormatBIT(0b01110111000100, TYPE_B, imm, xj, xd); }
void CodeGenerator::xvbitclri_h(const XVReg &xd, const XVReg &xj, uint32_t imm) { LasxFormatBIT(0b01110111000100, TYPE_H, imm, xj, xd); }
void CodeGenerator::xvbitclri_w(const XVReg &xd, const XVReg &xj, uint32_t imm) { LasxFormatBIT(0b01110111000100, TYPE_W, imm, xj, xd); }
void CodeGenerator::xvbitclri_d(const XVReg &xd, const XVReg &xj, uint32_t imm) { LasxFormatBIT(0b01110111000100, TYPE_D, imm, xj, xd); }

void CodeGenerator::xvbitseti_b(const XVReg &xd, const XVReg &xj, uint32_t imm) { LasxFormatBIT(0b01110111000101, TYPE_B, imm, xj, xd); }
void CodeGenerator::xvbitseti_h(const XVReg &xd, const XVReg &xj, uint32_t imm) { LasxFormatBIT(0b01110111000101, TYPE_H, imm, xj, xd); }
void CodeGenerator::xvbitseti_w(const XVReg &xd, const XVReg &xj, uint32_t imm) { LasxFormatBIT(0b01110111000101, TYPE_W, imm, xj, xd); }
void CodeGenerator::xvbitseti_d(const XVReg &xd, const XVReg &xj, uint32_t imm) { LasxFormatBIT(0b01110111000101, TYPE_D, imm, xj, xd); }

void CodeGenerator::xvbitrevi_b(const XVReg &xd, const XVReg &xj, uint32_t imm) { LasxFormatBIT(0b01110111000110, TYPE_B, imm, xj, xd); }
void CodeGenerator::xvbitrevi_h(const XVReg &xd, const XVReg &xj, uint32_t imm) { LasxFormatBIT(0b01110111000110, TYPE_H, imm, xj, xd); }
void CodeGenerator::xvbitrevi_w(const XVReg &xd, const XVReg &xj, uint32_t imm) { LasxFormatBIT(0b01110111000110, TYPE_W, imm, xj, xd); }
void CodeGenerator::xvbitrevi_d(const XVReg &xd, const XVReg &xj, uint32_t imm) { LasxFormatBIT(0b01110111000110, TYPE_D, imm, xj, xd); }

void CodeGenerator::xvsat_b(const XVReg &xd, const XVReg &xj, uint32_t imm) { LasxFormatBIT(0b01110111001001, TYPE_B, imm, xj, xd); }
void CodeGenerator::xvsat_h(const XVReg &xd, const XVReg &xj, uint32_t imm) { LasxFormatBIT(0b01110111001001, TYPE_H, imm, xj, xd); }
void CodeGenerator::xvsat_w(const XVReg &xd, const XVReg &xj, uint32_t imm) { LasxFormatBIT(0b01110111001001, TYPE_W, imm, xj, xd); }
void CodeGenerator::xvsat_d(const XVReg &xd, const XVReg &xj, uint32_t imm) { LasxFormatBIT(0b01110111001001, TYPE_D, imm, xj, xd); }

void CodeGenerator::xvsat_bu(const XVReg &xd, const XVReg &xj, uint32_t imm) { LasxFormatBIT(0b01110111001010, TYPE_B, imm, xj, xd); }
void CodeGenerator::xvsat_hu(const XVReg &xd, const XVReg &xj, uint32_t imm) { LasxFormatBIT(0b01110111001010, TYPE_H, imm, xj, xd); }
void CodeGenerator::xvsat_wu(const XVReg &xd, const XVReg &xj, uint32_t imm) { LasxFormatBIT(0b01110111001010, TYPE_W, imm, xj, xd); }
void CodeGenerator::xvsat_du(const XVReg &xd, const XVReg &xj, uint32_t imm) { LasxFormatBIT(0b01110111001010, TYPE_D, imm, xj, xd); }

void CodeGenerator::xvslli_b(const XVReg &xd, const XVReg &xj, uint32_t imm) { LasxFormatBIT(0b01110111001011, TYPE_B, imm, xj, xd); }
void CodeGenerator::xvslli_h(const XVReg &xd, const XVReg &xj, uint32_t imm) { LasxFormatBIT(0b01110111001011, TYPE_H, imm, xj, xd); }
void CodeGenerator::xvslli_w(const XVReg &xd, const XVReg &xj, uint32_t imm) { LasxFormatBIT(0b01110111001011, TYPE_W, imm, xj, xd); }
void CodeGenerator::xvslli_d(const XVReg &xd, const XVReg &xj, uint32_t imm) { LasxFormatBIT(0b01110111001011, TYPE_D, imm, xj, xd); }

void CodeGenerator::xvsrli_b(const XVReg &xd, const XVReg &xj, uint32_t imm) { LasxFormatBIT(0b01110111001100, TYPE_B, imm, xj, xd); }
void CodeGenerator::xvsrli_h(const XVReg &xd, const XVReg &xj, uint32_t imm) { LasxFormatBIT(0b01110111001100, TYPE_H, imm, xj, xd); }
void CodeGenerator::xvsrli_w(const XVReg &xd, const XVReg &xj, uint32_t imm) { LasxFormatBIT(0b01110111001100, TYPE_W, imm, xj, xd); }
void CodeGenerator::xvsrli_d(const XVReg &xd, const XVReg &xj, uint32_t imm) { LasxFormatBIT(0b01110111001100, TYPE_D, imm, xj, xd); }

void CodeGenerator::xvsrai_b(const XVReg &xd, const XVReg &xj, uint32_t imm) { LasxFormatBIT(0b01110111001101, TYPE_B, imm, xj, xd); }
void CodeGenerator::xvsrai_h(const XVReg &xd, const XVReg &xj, uint32_t imm) { LasxFormatBIT(0b01110111001101, TYPE_H, imm, xj, xd); }
void CodeGenerator::xvsrai_w(const XVReg &xd, const XVReg &xj, uint32_t imm) { LasxFormatBIT(0b01110111001101, TYPE_W, imm, xj, xd); }
void CodeGenerator::xvsrai_d(const XVReg &xd, const XVReg &xj, uint32_t imm) { LasxFormatBIT(0b01110111001101, TYPE_D, imm, xj, xd); }

void CodeGenerator::xvsrlni_b_h(const XVReg &xd, const XVReg &xj, uint32_t imm) { LasxFormatBIT(0b01110111010000, TYPE_H, imm, xj, xd); }
void CodeGenerator::xvsrlni_h_w(const XVReg &xd, const XVReg &xj, uint32_t imm) { LasxFormatBIT(0b01110111010000, TYPE_W, imm, xj, xd); }
void CodeGenerator::xvsrlni_w_d(const XVReg &xd, const XVReg &xj, uint32_t imm) { LasxFormatBIT(0b01110111010000, TYPE_D, imm, xj, xd); }
void CodeGenerator::xvsrlni_d_q(const XVReg &xd, const XVReg &xj, uint32_t imm) { LasxFormatBIT(0b01110111010000, TYPE_Q, imm, xj, xd); }

void CodeGenerator::xvsrlrni_b_h(const XVReg &xd, const XVReg &xj, uint32_t imm) { LasxFormatBIT(0b01110111010001, TYPE_H, imm, xj, xd); }
void CodeGenerator::xvsrlrni_h_w(const XVReg &xd, const XVReg &xj, uint32_t imm) { LasxFormatBIT(0b01110111010001, TYPE_W, imm, xj, xd); }
void CodeGenerator::xvsrlrni_w_d(const XVReg &xd, const XVReg &xj, uint32_t imm) { LasxFormatBIT(0b01110111010001, TYPE_D, imm, xj, xd); }
void CodeGenerator::xvsrlrni_d_q(const XVReg &xd, const XVReg &xj, uint32_t imm) { LasxFormatBIT(0b01110111010001, TYPE_Q, imm, xj, xd); }

void CodeGenerator::xvssrlni_b_h(const XVReg &xd, const XVReg &xj, uint32_t imm) { LasxFormatBIT(0b01110111010010, TYPE_H, imm, xj, xd); }
void CodeGenerator::xvssrlni_h_w(const XVReg &xd, const XVReg &xj, uint32_t imm) { LasxFormatBIT(0b01110111010010, TYPE_W, imm, xj, xd); }
void CodeGenerator::xvssrlni_w_d(const XVReg &xd, const XVReg &xj, uint32_t imm) { LasxFormatBIT(0b01110111010010, TYPE_D, imm, xj, xd); }
void CodeGenerator::xvssrlni_d_q(const XVReg &xd, const XVReg &xj, uint32_t imm) { LasxFormatBIT(0b01110111010010, TYPE_Q, imm, xj, xd); }

void CodeGenerator::xvssrlni_bu_h(const XVReg &xd, const XVReg &xj, uint32_t imm) { LasxFormatBIT(0b01110111010011, TYPE_H, imm, xj, xd); }
void CodeGenerator::xvssrlni_hu_w(const XVReg &xd, const XVReg &xj, uint32_t imm) { LasxFormatBIT(0b01110111010011, TYPE_W, imm, xj, xd); }
void CodeGenerator::xvssrlni_wu_d(const XVReg &xd, const XVReg &xj, uint32_t imm) { LasxFormatBIT(0b01110111010011, TYPE_D, imm, xj, xd); }
void CodeGenerator::xvssrlni_du_q(const XVReg &xd, const XVReg &xj, uint32_t imm) { LasxFormatBIT(0b01110111010011, TYPE_Q, imm, xj, xd); }

void CodeGenerator::xvssrlrni_b_h(const XVReg &xd, const XVReg &xj, uint32_t imm) { LasxFormatBIT(0b01110111010100, TYPE_H, imm, xj, xd); }
void CodeGenerator::xvssrlrni_h_w(const XVReg &xd, const XVReg &xj, uint32_t imm) { LasxFormatBIT(0b01110111010100, TYPE_W, imm, xj, xd); }
void CodeGenerator::xvssrlrni_w_d(const XVReg &xd, const XVReg &xj, uint32_t imm) { LasxFormatBIT(0b01110111010100, TYPE_D, imm, xj, xd); }
void CodeGenerator::xvssrlrni_d_q(const XVReg &xd, const XVReg &xj, uint32_t imm) { LasxFormatBIT(0b01110111010100, TYPE_Q, imm, xj, xd); }

void CodeGenerator::xvssrlrni_bu_h(const XVReg &xd, const XVReg &xj, uint32_t imm) { LasxFormatBIT(0b01110111010101, TYPE_H, imm, xj, xd); }
void CodeGenerator::xvssrlrni_hu_w(const XVReg &xd, const XVReg &xj, uint32_t imm) { LasxFormatBIT(0b01110111010101, TYPE_W, imm, xj, xd); }
void CodeGenerator::xvssrlrni_wu_d(const XVReg &xd, const XVReg &xj, uint32_t imm) { LasxFormatBIT(0b01110111010101, TYPE_D, imm, xj, xd); }
void CodeGenerator::xvssrlrni_du_q(const XVReg &xd, const XVReg &xj, uint32_t imm) { LasxFormatBIT(0b01110111010101, TYPE_Q, imm, xj, xd); }

void CodeGenerator::xvsrani_b_h(const XVReg &xd, const XVReg &xj, uint32_t imm) { LasxFormatBIT(0b01110111010110, TYPE_H, imm, xj, xd); }
void CodeGenerator::xvsrani_h_w(const XVReg &xd, const XVReg &xj, uint32_t imm) { LasxFormatBIT(0b01110111010110, TYPE_W, imm, xj, xd); }
void CodeGenerator::xvsrani_w_d(const XVReg &xd, const XVReg &xj, uint32_t imm) { LasxFormatBIT(0b01110111010110, TYPE_D, imm, xj, xd); }
void CodeGenerator::xvsrani_d_q(const XVReg &xd, const XVReg &xj, uint32_t imm) { LasxFormatBIT(0b01110111010110, TYPE_Q, imm, xj, xd); }

void CodeGenerator::xvsrarni_b_h(const XVReg &xd, const XVReg &xj, uint32_t imm) { LasxFormatBIT(0b01110111010111, TYPE_H, imm, xj, xd); }
void CodeGenerator::xvsrarni_h_w(const XVReg &xd, const XVReg &xj, uint32_t imm) { LasxFormatBIT(0b01110111010111, TYPE_W, imm, xj, xd); }
void CodeGenerator::xvsrarni_w_d(const XVReg &xd, const XVReg &xj, uint32_t imm) { LasxFormatBIT(0b01110111010111, TYPE_D, imm, xj, xd); }
void CodeGenerator::xvsrarni_d_q(const XVReg &xd, const XVReg &xj, uint32_t imm) { LasxFormatBIT(0b01110111010111, TYPE_Q, imm, xj, xd); }

void CodeGenerator::xvssrani_b_h(const XVReg &xd, const XVReg &xj, uint32_t imm) { LasxFormatBIT(0b01110111011000, TYPE_H, imm, xj, xd); }
void CodeGenerator::xvssrani_h_w(const XVReg &xd, const XVReg &xj, uint32_t imm) { LasxFormatBIT(0b01110111011000, TYPE_W, imm, xj, xd); }
void CodeGenerator::xvssrani_w_d(const XVReg &xd, const XVReg &xj, uint32_t imm) { LasxFormatBIT(0b01110111011000, TYPE_D, imm, xj, xd); }
void CodeGenerator::xvssrani_d_q(const XVReg &xd, const XVReg &xj, uint32_t imm) { LasxFormatBIT(0b01110111011000, TYPE_Q, imm, xj, xd); }

void CodeGenerator::xvssrani_bu_h(const XVReg &xd, const XVReg &xj, uint32_t imm) { LasxFormatBIT(0b01110111011001, TYPE_H, imm, xj, xd); }
void CodeGenerator::xvssrani_hu_w(const XVReg &xd, const XVReg &xj, uint32_t imm) { LasxFormatBIT(0b01110111011001, TYPE_W, imm, xj, xd); }
void CodeGenerator::xvssrani_wu_d(const XVReg &xd, const XVReg &xj, uint32_t imm) { LasxFormatBIT(0b01110111011001, TYPE_D, imm, xj, xd); }
void CodeGenerator::xvssrani_du_q(const XVReg &xd, const XVReg &xj, uint32_t imm) { LasxFormatBIT(0b01110111011001, TYPE_Q, imm, xj, xd); }

void CodeGenerator::xvssrarni_b_h(const XVReg &xd, const XVReg &xj, uint32_t imm) { LasxFormatBIT(0b01110111011010, TYPE_H, imm, xj, xd); }
void CodeGenerator::xvssrarni_h_w(const XVReg &xd, const XVReg &xj, uint32_t imm) { LasxFormatBIT(0b01110111011010, TYPE_W, imm, xj, xd); }
void CodeGenerator::xvssrarni_w_d(const XVReg &xd, const XVReg &xj, uint32_t imm) { LasxFormatBIT(0b01110111011010, TYPE_D, imm, xj, xd); }
void CodeGenerator::xvssrarni_d_q(const XVReg &xd, const XVReg &xj, uint32_t imm) { LasxFormatBIT(0b01110111011010, TYPE_Q, imm, xj, xd); }

void CodeGenerator::xvssrarni_bu_h(const XVReg &xd, const XVReg &xj, uint32_t imm) { LasxFormatBIT(0b01110111011011, TYPE_H, imm, xj, xd); }
void CodeGenerator::xvssrarni_hu_w(const XVReg &xd, const XVReg &xj, uint32_t imm) { LasxFormatBIT(0b01110111011011, TYPE_W, imm, xj, xd); }
void CodeGenerator::xvssrarni_wu_d(const XVReg &xd, const XVReg &xj, uint32_t imm) { LasxFormatBIT(0b01110111011011, TYPE_D, imm, xj, xd); }
void CodeGenerator::xvssrarni_du_q(const XVReg &xd, const XVReg &xj, uint32_t imm) { LasxFormatBIT(0b01110111011011, TYPE_Q, imm, xj, xd); }

void CodeGenerator::xvextrins_d(const XVReg &xd, const XVReg &xj, uint32_t imm8) { LasxFormatI8(0b01110111100000, imm8, xj, xd); }
void CodeGenerator::xvextrins_w(const XVReg &xd, const XVReg &xj, uint32_t imm8) { LasxFormatI8(0b01110111100001, imm8, xj, xd); }
void CodeGenerator::xvextrins_h(const XVReg &xd, const XVReg &xj, uint32_t imm8) { LasxFormatI8(0b01110111100010, imm8, xj, xd); }
void CodeGenerator::xvextrins_b(const XVReg &xd, const XVReg &xj, uint32_t imm8) { LasxFormatI8(0b01110111100011, imm8, xj, xd); }

void CodeGenerator::xvshuf4i_b(const XVReg &xd, const XVReg &xj, uint32_t imm8) { LasxFormatI8(0b01110111100100, imm8, xj, xd); }
void CodeGenerator::xvshuf4i_h(const XVReg &xd, const XVReg &xj, uint32_t imm8) { LasxFormatI8(0b01110111100101, imm8, xj, xd); }
void CodeGenerator::xvshuf4i_w(const XVReg &xd, const XVReg &xj, uint32_t imm8) { LasxFormatI8(0b01110111100110, imm8, xj, xd); }
void CodeGenerator::xvshuf4i_d(const XVReg &xd, const XVReg &xj, uint32_t imm8) { LasxFormatI8(0b01110111100111, imm8, xj, xd); }

void CodeGenerator::xvbitseli_b(const XVReg &xd, const XVReg &xj, uint32_t imm8) { LasxFormatI8(0b01110111110001, imm8, xj, xd); }
void CodeGenerator::xvandi_b(const XVReg &xd, const XVReg &xj, uint32_t imm8)    { LasxFormatI8(0b01110111110100, imm8, xj, xd); }
void CodeGenerator::xvori_b(const XVReg &xd, const XVReg &xj, uint32_t imm8)     { LasxFormatI8(0b01110111110101, imm8, xj, xd); }
void CodeGenerator::xvxori_b(const XVReg &xd, const XVReg &xj, uint32_t imm8)    { LasxFormatI8(0b01110111110110, imm8, xj, xd); }
void CodeGenerator::xvnori_b(const XVReg &xd, const XVReg &xj, uint32_t imm8)    { LasxFormatI8(0b01110111110111, imm8, xj, xd); }

void CodeGenerator::xvldi(const XVReg &xd, int32_t imm13) { LasxFormatI13(0b01110111111000, imm13, xd); }

void CodeGenerator::xvpermi_w(const XVReg &xd, const XVReg &xj, uint32_t imm8) { LasxFormatI8(0b01110111111001, imm8, xj, xd); }
void CodeGenerator::xvpermi_d(const XVReg &xd, const XVReg &xj, uint32_t imm8) { LasxFormatI8(0b01110111111010, imm8, xj, xd); }
void CodeGenerator::xvpermi_q(const XVReg &xd, const XVReg &xj, uint32_t imm8) { LasxFormatI8(0b01110111111011, imm8, xj, xd); }
/****** LASX end ******/

/****** Loongarch base begin *****/
void CodeGenerator::add_w(const XReg& rd, const XReg& rj, const XReg& rk) { Loongarch3Reg(0b100000, rk.getIdx(), rj.getIdx(), rd.getIdx()); }
void CodeGenerator::add_d(const XReg& rd, const XReg& rj, const XReg& rk) { Loongarch3Reg(0b100001, rk.getIdx(), rj.getIdx(), rd.getIdx()); }
void CodeGenerator::andi(const XReg& rd, const XReg& rj, int32_t ui12) { Loongarch2Reg1Offset(0b1101, rj.getIdx(), rd.getIdx(), ui12, 5); }
void CodeGenerator::clo_w(const XReg& rd, const XReg& rj) { Loongarch2Reg(0b100, rj.getIdx(), rd.getIdx()); }
void CodeGenerator::clz_w(const XReg& rd, const XReg& rj) { Loongarch2Reg(0b101, rj.getIdx(), rd.getIdx()); }
void CodeGenerator::cto_w(const XReg& rd, const XReg& rj) { Loongarch2Reg(0b110, rj.getIdx(), rd.getIdx()); }
void CodeGenerator::ctz_w(const XReg& rd, const XReg& rj) { Loongarch2Reg(0b111, rj.getIdx(), rd.getIdx()); }
void CodeGenerator::clo_d(const XReg& rd, const XReg& rj) { Loongarch2Reg(0b1000, rj.getIdx(), rd.getIdx()); }
void CodeGenerator::clz_d(const XReg& rd, const XReg& rj) { Loongarch2Reg(0b1001, rj.getIdx(), rd.getIdx()); }
void CodeGenerator::cto_d(const XReg& rd, const XReg& rj) { Loongarch2Reg(0b1010, rj.getIdx(), rd.getIdx()); }
void CodeGenerator::ctz_d(const XReg& rd, const XReg& rj) { Loongarch2Reg(0b1011, rj.getIdx(), rd.getIdx()); }
void CodeGenerator::revb_2h(const XReg& rd, const XReg& rj) { Loongarch2Reg(0b1100, rj.getIdx(), rd.getIdx()); }
void CodeGenerator::revb_4h(const XReg& rd, const XReg& rj) { Loongarch2Reg(0b1101, rj.getIdx(), rd.getIdx()); }
void CodeGenerator::revb_2w(const XReg& rd, const XReg& rj) { Loongarch2Reg(0b1110, rj.getIdx(), rd.getIdx()); }
void CodeGenerator::revb_d(const XReg& rd, const XReg& rj) { Loongarch2Reg(0b1111, rj.getIdx(), rd.getIdx()); }
void CodeGenerator::revh_2w(const XReg& rd, const XReg& rj) { Loongarch2Reg(0b10000, rj.getIdx(), rd.getIdx()); }
void CodeGenerator::revh_d(const XReg& rd, const XReg& rj) { Loongarch2Reg(0b10001, rj.getIdx(), rd.getIdx()); }
void CodeGenerator::bitrev_4b(const XReg& rd, const XReg& rj) { Loongarch2Reg(0b10010, rj.getIdx(), rd.getIdx()); }
void CodeGenerator::bitrev_8b(const XReg& rd, const XReg& rj) { Loongarch2Reg(0b10011, rj.getIdx(), rd.getIdx()); }
void CodeGenerator::bitrev_w(const XReg& rd, const XReg& rj) { Loongarch2Reg(0b10100, rj.getIdx(), rd.getIdx()); }
void CodeGenerator::bitrev_d(const XReg& rd, const XReg& rj) { Loongarch2Reg(0b10101, rj.getIdx(), rd.getIdx()); }
void CodeGenerator::ext_w_h(const XReg& rd, const XReg& rj) { Loongarch2Reg(0b10110, rj.getIdx(), rd.getIdx()); }
void CodeGenerator::ext_w_b(const XReg& rd, const XReg& rj) { Loongarch2Reg(0b10111, rj.getIdx(), rd.getIdx()); }
void CodeGenerator::rdtimel_w(const XReg& rd, const XReg& rj) { Loongarch2Reg(0b11000, rj.getIdx(), rd.getIdx()); }
void CodeGenerator::rdtimeh_w(const XReg& rd, const XReg& rj) { Loongarch2Reg(0b11001, rj.getIdx(), rd.getIdx()); }
void CodeGenerator::rdtime_d(const XReg& rd, const XReg& rj) { Loongarch2Reg(0b11010, rj.getIdx(), rd.getIdx()); }
void CodeGenerator::cpucfg(const XReg& rd, const XReg& rj) { Loongarch2Reg(0b11011, rj.getIdx(), rd.getIdx()); }
void CodeGenerator::asrtle_d(const XReg& rj, const XReg& rk) { Loongarch3Reg(0b10, rk.getIdx(), rj.getIdx(), 0); }
void CodeGenerator::asrtgt_d(const XReg& rj, const XReg& rk) { Loongarch3Reg(0b11, rk.getIdx(), rj.getIdx(), 0); }
void CodeGenerator::alsl_w(const XReg& rd, const XReg& rj, const XReg& rk, uint32_t sa2) { Loongarch3Reg1Sa(0b10, sa2 - 1, rk.getIdx(), rj.getIdx(), rd.getIdx(), 2); }
void CodeGenerator::alsl_wu(const XReg& rd, const XReg& rj, const XReg& rk, uint32_t sa2) { Loongarch3Reg1Sa(0b11, sa2 - 1, rk.getIdx(), rj.getIdx(), rd.getIdx(), 2); }
void CodeGenerator::bytepick_w(const XReg& rd, const XReg& rj, const XReg& rk, uint32_t sa2) { Loongarch3Reg1Sa(0b100, sa2, rk.getIdx(), rj.getIdx(), rd.getIdx(), 2); }
void CodeGenerator::bytepick_d(const XReg& rd, const XReg& rj, const XReg& rk, uint32_t sa3) { Loongarch3Reg1Sa(0b11, sa3, rk.getIdx(), rj.getIdx(), rd.getIdx(), 1); }
void CodeGenerator::sub_w(const XReg& rd, const XReg& rj, const XReg& rk) { Loongarch3Reg(0b100010, rk.getIdx(), rj.getIdx(), rd.getIdx()); }
void CodeGenerator::sub_d(const XReg& rd, const XReg& rj, const XReg& rk) { Loongarch3Reg(0b100011, rk.getIdx(), rj.getIdx(), rd.getIdx()); }
void CodeGenerator::slt(const XReg& rd, const XReg& rj, const XReg& rk) { Loongarch3Reg(0b100100, rk.getIdx(), rj.getIdx(), rd.getIdx()); }
void CodeGenerator::sltu(const XReg& rd, const XReg& rj, const XReg& rk) { Loongarch3Reg(0b100101, rk.getIdx(), rj.getIdx(), rd.getIdx()); }
void CodeGenerator::maskeqz(const XReg& rd, const XReg& rj, const XReg& rk) { Loongarch3Reg(0b100110, rk.getIdx(), rj.getIdx(), rd.getIdx()); }
void CodeGenerator::masknez(const XReg& rd, const XReg& rj, const XReg& rk) { Loongarch3Reg(0b100111, rk.getIdx(), rj.getIdx(), rd.getIdx()); }
void CodeGenerator::nor(const XReg& rd, const XReg& rj, const XReg& rk) { Loongarch3Reg(0b101000, rk.getIdx(), rj.getIdx(), rd.getIdx()); }
void CodeGenerator::and_(const XReg& rd, const XReg& rj, const XReg& rk) { Loongarch3Reg(0b101001, rk.getIdx(), rj.getIdx(), rd.getIdx()); }
void CodeGenerator::or_(const XReg& rd, const XReg& rj, const XReg& rk) { Loongarch3Reg(0b101010, rk.getIdx(), rj.getIdx(), rd.getIdx()); }
void CodeGenerator::xor_(const XReg& rd, const XReg& rj, const XReg& rk) { Loongarch3Reg(0b101011, rk.getIdx(), rj.getIdx(), rd.getIdx()); }
void CodeGenerator::orn(const XReg& rd, const XReg& rj, const XReg& rk) { Loongarch3Reg(0b101100, rk.getIdx(), rj.getIdx(), rd.getIdx()); }
void CodeGenerator::andn(const XReg& rd, const XReg& rj, const XReg& rk) { Loongarch3Reg(0b101101, rk.getIdx(), rj.getIdx(), rd.getIdx()); }
void CodeGenerator::sll_w(const XReg& rd, const XReg& rj, const XReg& rk) { Loongarch3Reg(0b101110, rk.getIdx(), rj.getIdx(), rd.getIdx()); }
void CodeGenerator::srl_w(const XReg& rd, const XReg& rj, const XReg& rk) { Loongarch3Reg(0b101111, rk.getIdx(), rj.getIdx(), rd.getIdx()); }
void CodeGenerator::sra_w(const XReg& rd, const XReg& rj, const XReg& rk) { Loongarch3Reg(0b110000, rk.getIdx(), rj.getIdx(), rd.getIdx()); }
void CodeGenerator::sll_d(const XReg& rd, const XReg& rj, const XReg& rk) { Loongarch3Reg(0b110001, rk.getIdx(), rj.getIdx(), rd.getIdx()); }
void CodeGenerator::srl_d(const XReg& rd, const XReg& rj, const XReg& rk) { Loongarch3Reg(0b110010, rk.getIdx(), rj.getIdx(), rd.getIdx()); }
void CodeGenerator::sra_d(const XReg& rd, const XReg& rj, const XReg& rk) { Loongarch3Reg(0b110011, rk.getIdx(), rj.getIdx(), rd.getIdx()); }
void CodeGenerator::rotr_w(const XReg& rd, const XReg& rj, const XReg& rk) { Loongarch3Reg(0b110110, rk.getIdx(), rj.getIdx(), rd.getIdx()); }
void CodeGenerator::rotr_d(const XReg& rd, const XReg& rj, const XReg& rk) { Loongarch3Reg(0b110111, rk.getIdx(), rj.getIdx(), rd.getIdx()); }
void CodeGenerator::mul_w(const XReg& rd, const XReg& rj, const XReg& rk) { Loongarch3Reg(0b111000, rk.getIdx(), rj.getIdx(), rd.getIdx()); }
void CodeGenerator::mulh_w(const XReg& rd, const XReg& rj, const XReg& rk) { Loongarch3Reg(0b111001, rk.getIdx(), rj.getIdx(), rd.getIdx()); }
void CodeGenerator::mulh_wu(const XReg& rd, const XReg& rj, const XReg& rk) { Loongarch3Reg(0b111010, rk.getIdx(), rj.getIdx(), rd.getIdx()); }
void CodeGenerator::mul_d(const XReg& rd, const XReg& rj, const XReg& rk) { Loongarch3Reg(0b111011, rk.getIdx(), rj.getIdx(), rd.getIdx()); }
void CodeGenerator::mulh_d(const XReg& rd, const XReg& rj, const XReg& rk) { Loongarch3Reg(0b111100, rk.getIdx(), rj.getIdx(), rd.getIdx()); }
void CodeGenerator::mulh_du(const XReg& rd, const XReg& rj, const XReg& rk) { Loongarch3Reg(0b111101, rk.getIdx(), rj.getIdx(), rd.getIdx()); }
void CodeGenerator::mulw_d_w(const XReg& rd, const XReg& rj, const XReg& rk) { Loongarch3Reg(0b111110, rk.getIdx(), rj.getIdx(), rd.getIdx()); }
void CodeGenerator::mulw_d_wu(const XReg& rd, const XReg& rj, const XReg& rk) { Loongarch3Reg(0b111111, rk.getIdx(), rj.getIdx(), rd.getIdx()); }
void CodeGenerator::div_w(const XReg& rd, const XReg& rj, const XReg& rk) { Loongarch3Reg(0b1000000, rk.getIdx(), rj.getIdx(), rd.getIdx()); }
void CodeGenerator::mod_w(const XReg& rd, const XReg& rj, const XReg& rk) { Loongarch3Reg(0b1000001, rk.getIdx(), rj.getIdx(), rd.getIdx()); }
void CodeGenerator::div_wu(const XReg& rd, const XReg& rj, const XReg& rk) { Loongarch3Reg(0b1000010, rk.getIdx(), rj.getIdx(), rd.getIdx()); }
void CodeGenerator::mod_wu(const XReg& rd, const XReg& rj, const XReg& rk) { Loongarch3Reg(0b1000011, rk.getIdx(), rj.getIdx(), rd.getIdx()); }
void CodeGenerator::div_d(const XReg& rd, const XReg& rj, const XReg& rk) { Loongarch3Reg(0b1000100, rk.getIdx(), rj.getIdx(), rd.getIdx()); }
void CodeGenerator::mod_d(const XReg& rd, const XReg& rj, const XReg& rk) { Loongarch3Reg(0b1000101, rk.getIdx(), rj.getIdx(), rd.getIdx()); }
void CodeGenerator::div_du(const XReg& rd, const XReg& rj, const XReg& rk) { Loongarch3Reg(0b1000110, rk.getIdx(), rj.getIdx(), rd.getIdx()); }
void CodeGenerator::mod_du(const XReg& rd, const XReg& rj, const XReg& rk) { Loongarch3Reg(0b1000111, rk.getIdx(), rj.getIdx(), rd.getIdx()); }
void CodeGenerator::crc_w_b_w(const XReg& rd, const XReg& rj, const XReg& rk) { Loongarch3Reg(0b1001000, rk.getIdx(), rj.getIdx(), rd.getIdx()); }
void CodeGenerator::crc_w_h_w(const XReg& rd, const XReg& rj, const XReg& rk) { Loongarch3Reg(0b1001001, rk.getIdx(), rj.getIdx(), rd.getIdx()); }
void CodeGenerator::crc_w_w_w(const XReg& rd, const XReg& rj, const XReg& rk) { Loongarch3Reg(0b1001010, rk.getIdx(), rj.getIdx(), rd.getIdx()); }
void CodeGenerator::crc_w_d_w(const XReg& rd, const XReg& rj, const XReg& rk) { Loongarch3Reg(0b1001011, rk.getIdx(), rj.getIdx(), rd.getIdx()); }
void CodeGenerator::crcc_w_b_w(const XReg& rd, const XReg& rj, const XReg& rk) { Loongarch3Reg(0b1001100, rk.getIdx(), rj.getIdx(), rd.getIdx()); }
void CodeGenerator::crcc_w_h_w(const XReg& rd, const XReg& rj, const XReg& rk) { Loongarch3Reg(0b1001101, rk.getIdx(), rj.getIdx(), rd.getIdx()); }
void CodeGenerator::crcc_w_w_w(const XReg& rd, const XReg& rj, const XReg& rk) { Loongarch3Reg(0b1001110, rk.getIdx(), rj.getIdx(), rd.getIdx()); }
void CodeGenerator::crcc_w_d_w(const XReg& rd, const XReg& rj, const XReg& rk) { Loongarch3Reg(0b1001111, rk.getIdx(), rj.getIdx(), rd.getIdx()); }
void CodeGenerator::break_(int32_t code15) { Loongarch1Code(0b1010100, code15); }
void CodeGenerator::dbcl(int32_t code15) { Loongarch1Code(0b1010101, code15); }
void CodeGenerator::syscall(int32_t code15) { Loongarch1Code(0b1010110, code15); }
void CodeGenerator::alsl_d(const XReg& rd, const XReg& rj, const XReg& rk, uint32_t sa2) { Loongarch3Reg1Sa(0b10110, sa2 - 1, rk.getIdx(), rj.getIdx(), rd.getIdx(), 2); }
void CodeGenerator::slli_w(const XReg& rd, const XReg& rj, uint32_t ui5) { Loongarch2Reg1Offset(0b10000001, rj.getIdx(), rd.getIdx(), ui5, 4); }
void CodeGenerator::slli_d(const XReg& rd, const XReg& rj, uint32_t ui6) { Loongarch2Reg1Offset(0b1000001, rj.getIdx(), rd.getIdx(), ui6, 3); }
void CodeGenerator::srli_w(const XReg& rd, const XReg& rj, uint32_t ui5) { Loongarch2Reg1Offset(0b10001001, rj.getIdx(), rd.getIdx(), ui5, 4); }
void CodeGenerator::srli_d(const XReg& rd, const XReg& rj, uint32_t ui6) { Loongarch2Reg1Offset(0b1000101, rj.getIdx(), rd.getIdx(), ui6, 3); }
void CodeGenerator::srai_w(const XReg& rd, const XReg& rj, uint32_t ui5) { Loongarch2Reg1Offset(0b10010001, rj.getIdx(), rd.getIdx(), ui5, 4); }
void CodeGenerator::srai_d(const XReg& rd, const XReg& rj, uint32_t ui6) { Loongarch2Reg1Offset(0b1001001, rj.getIdx(), rd.getIdx(), ui6, 3); }
void CodeGenerator::rotri_w(const XReg& rd, const XReg& rj, uint32_t ui5) { Loongarch2Reg1Offset(0b10011001, rj.getIdx(), rd.getIdx(), ui5, 4); }
void CodeGenerator::rotri_d(const XReg& rd, const XReg& rj, uint32_t ui6) { Loongarch2Reg1Offset(0b1001101, rj.getIdx(), rd.getIdx(), ui6, 3); }
void CodeGenerator::bstrins_w(const XReg& rd, const XReg& rj, uint32_t msbw, uint32_t lsbw) { Loongarch2Reg2Param(0b11, msbw, lsbw, rj.getIdx(), rd.getIdx(), 1); }
void CodeGenerator::bstrpick_w(const XReg& rd, const XReg& rj, uint32_t msbw, uint32_t lsbw) { Loongarch2Reg2Param(0b11, msbw, lsbw, rj.getIdx(), rd.getIdx(), 2); }
void CodeGenerator::bstrins_d(const XReg& rd, const XReg& rj, uint32_t msbd, uint32_t lsbd) { Loongarch2Reg2Param(0b10, msbd, lsbd, rj.getIdx(), rd.getIdx(), 3); }
void CodeGenerator::bstrpick_d(const XReg& rd, const XReg& rj, uint32_t msbd, uint32_t lsbd) { Loongarch2Reg2Param(0b11, msbd, lsbd, rj.getIdx(), rd.getIdx(), 3); }
void CodeGenerator::fadd_s(const XReg& fd, const XReg& fj, const XReg& fk) { Loongarch3Reg(0b1000000001, fk.getIdx(), fj.getIdx(), fd.getIdx()); }
void CodeGenerator::fadd_d(const XReg& fd, const XReg& fj, const XReg& fk) { Loongarch3Reg(0b1000000010, fk.getIdx(), fj.getIdx(), fd.getIdx()); }
void CodeGenerator::fsub_s(const XReg& fd, const XReg& fj, const XReg& fk) { Loongarch3Reg(0b1000000101, fk.getIdx(), fj.getIdx(), fd.getIdx()); }
void CodeGenerator::fsub_d(const XReg& fd, const XReg& fj, const XReg& fk) { Loongarch3Reg(0b1000000110, fk.getIdx(), fj.getIdx(), fd.getIdx()); }
void CodeGenerator::fmul_s(const XReg& fd, const XReg& fj, const XReg& fk) { Loongarch3Reg(0b1000001001, fk.getIdx(), fj.getIdx(), fd.getIdx()); }
void CodeGenerator::fmul_d(const XReg& fd, const XReg& fj, const XReg& fk) { Loongarch3Reg(0b1000001010, fk.getIdx(), fj.getIdx(), fd.getIdx()); }
void CodeGenerator::fdiv_s(const XReg& fd, const XReg& fj, const XReg& fk) { Loongarch3Reg(0b1000001101, fk.getIdx(), fj.getIdx(), fd.getIdx()); }
void CodeGenerator::fdiv_d(const XReg& fd, const XReg& fj, const XReg& fk) { Loongarch3Reg(0b1000001110, fk.getIdx(), fj.getIdx(), fd.getIdx()); }
void CodeGenerator::fmax_s(const XReg& fd, const XReg& fj, const XReg& fk) { Loongarch3Reg(0b1000010001, fk.getIdx(), fj.getIdx(), fd.getIdx()); }
void CodeGenerator::fmax_d(const XReg& fd, const XReg& fj, const XReg& fk) { Loongarch3Reg(0b1000010010, fk.getIdx(), fj.getIdx(), fd.getIdx()); }
void CodeGenerator::fmin_s(const XReg& fd, const XReg& fj, const XReg& fk) { Loongarch3Reg(0b1000010101, fk.getIdx(), fj.getIdx(), fd.getIdx()); }
void CodeGenerator::fmin_d(const XReg& fd, const XReg& fj, const XReg& fk) { Loongarch3Reg(0b1000010110, fk.getIdx(), fj.getIdx(), fd.getIdx()); }
void CodeGenerator::fmaxa_s(const XReg& fd, const XReg& fj, const XReg& fk) { Loongarch3Reg(0b1000011001, fk.getIdx(), fj.getIdx(), fd.getIdx()); }
void CodeGenerator::fmaxa_d(const XReg& fd, const XReg& fj, const XReg& fk) { Loongarch3Reg(0b1000011010, fk.getIdx(), fj.getIdx(), fd.getIdx()); }
void CodeGenerator::fmina_s(const XReg& fd, const XReg& fj, const XReg& fk) { Loongarch3Reg(0b1000011101, fk.getIdx(), fj.getIdx(), fd.getIdx()); }
void CodeGenerator::fmina_d(const XReg& fd, const XReg& fj, const XReg& fk) { Loongarch3Reg(0b1000011110, fk.getIdx(), fj.getIdx(), fd.getIdx()); }
void CodeGenerator::fscaleb_s(const XReg& fd, const XReg& fj, const XReg& fk) { Loongarch3Reg(0b1000100001, fk.getIdx(), fj.getIdx(), fd.getIdx()); }
void CodeGenerator::fscaleb_d(const XReg& fd, const XReg& fj, const XReg& fk) { Loongarch3Reg(0b1000100010, fk.getIdx(), fj.getIdx(), fd.getIdx()); }
void CodeGenerator::fcopysign_s(const XReg& fd, const XReg& fj, const XReg& fk) { Loongarch3Reg(0b1000100101, fk.getIdx(), fj.getIdx(), fd.getIdx()); }
void CodeGenerator::fcopysign_d(const XReg& fd, const XReg& fj, const XReg& fk) { Loongarch3Reg(0b1000100110, fk.getIdx(), fj.getIdx(), fd.getIdx()); }
void CodeGenerator::fabs_s(const XReg& fd, const XReg& fj) { Loongarch2Reg(0b100010100000001, fj.getIdx(), fd.getIdx()); }
void CodeGenerator::fabs_d(const XReg& fd, const XReg& fj) { Loongarch2Reg(0b100010100000010, fj.getIdx(), fd.getIdx()); }
void CodeGenerator::fneg_s(const XReg& fd, const XReg& fj) { Loongarch2Reg(0b100010100000101, fj.getIdx(), fd.getIdx()); }
void CodeGenerator::fneg_d(const XReg& fd, const XReg& fj) { Loongarch2Reg(0b100010100000110, fj.getIdx(), fd.getIdx()); }
void CodeGenerator::flogb_s(const XReg& fd, const XReg& fj) { Loongarch2Reg(0b100010100001001, fj.getIdx(), fd.getIdx()); }
void CodeGenerator::flogb_d(const XReg& fd, const XReg& fj) { Loongarch2Reg(0b100010100001010, fj.getIdx(), fd.getIdx()); }
void CodeGenerator::fclass_s(const XReg& fd, const XReg& fj) { Loongarch2Reg(0b100010100001101, fj.getIdx(), fd.getIdx()); }
void CodeGenerator::fclass_d(const XReg& fd, const XReg& fj) { Loongarch2Reg(0b100010100001110, fj.getIdx(), fd.getIdx()); }
void CodeGenerator::fsqrt_s(const XReg& fd, const XReg& fj) { Loongarch2Reg(0b100010100010001, fj.getIdx(), fd.getIdx()); }
void CodeGenerator::fsqrt_d(const XReg& fd, const XReg& fj) { Loongarch2Reg(0b100010100010010, fj.getIdx(), fd.getIdx()); }
void CodeGenerator::frecip_s(const XReg& fd, const XReg& fj) { Loongarch2Reg(0b100010100010101, fj.getIdx(), fd.getIdx()); }
void CodeGenerator::frecip_d(const XReg& fd, const XReg& fj) { Loongarch2Reg(0b100010100010110, fj.getIdx(), fd.getIdx()); }
void CodeGenerator::frsqrt_s(const XReg& fd, const XReg& fj) { Loongarch2Reg(0b100010100011001, fj.getIdx(), fd.getIdx()); }
void CodeGenerator::frsqrt_d(const XReg& fd, const XReg& fj) { Loongarch2Reg(0b100010100011010, fj.getIdx(), fd.getIdx()); }
void CodeGenerator::fmov_s(const XReg& fd, const XReg& fj) { Loongarch2Reg(0b100010100100101, fj.getIdx(), fd.getIdx()); }
void CodeGenerator::fmov_d(const XReg& fd, const XReg& fj) { Loongarch2Reg(0b100010100100110, fj.getIdx(), fd.getIdx()); }
void CodeGenerator::movgr2fr_w(const XReg& fd, const XReg& rj) { Loongarch2Reg(0b0000000100010100101001, rj.getIdx(), fd.getIdx()); }
void CodeGenerator::movgr2fr_d(const XReg& fd, const XReg& rj) { Loongarch2Reg(0b0000000100010100101010, rj.getIdx(), fd.getIdx()); }
void CodeGenerator::movgr2frh_w(const XReg& fd, const XReg& rj) { Loongarch2Reg(0b0000000100010100101011, rj.getIdx(), fd.getIdx()); }
void CodeGenerator::movfr2gr_s(const XReg& rd, const XReg& fj) { Loongarch2Reg(0b100010100101101, fj.getIdx(), rd.getIdx()); }
void CodeGenerator::movfr2gr_d(const XReg& rd, const XReg& fj) { Loongarch2Reg(0b100010100101110, fj.getIdx(), rd.getIdx()); }
void CodeGenerator::movfrh2gr_s(const XReg& rd, const XReg& fj) { Loongarch2Reg(0b100010100101111, fj.getIdx(), rd.getIdx()); }
void CodeGenerator::movgr2fcsr(const XReg& fcsr, const XReg& rj) { Loongarch2Reg(0b100010100110000, rj.getIdx(), fcsr.getIdx()); }
void CodeGenerator::movfcsr2gr(const XReg& rd, const XReg& fcsr) { Loongarch2Reg(0b100010100110010, fcsr.getIdx(), rd.getIdx()); }
void CodeGenerator::movfr2cf(const uint32_t cd, const XReg& fj) { Loongarch2RegZeroExtend(0b100010100110100, fj.getIdx(), cd, 1); }
void CodeGenerator::movcf2fr(const XReg& fd, const uint32_t cj) { Loongarch2RegZeroExtend(0b100010100110101, cj, fd.getIdx(), 2); }
void CodeGenerator::movgr2cf(const uint32_t cd, const XReg& rj) { Loongarch2RegZeroExtend(0b100010100110110, rj.getIdx(), cd, 1); }
void CodeGenerator::movcf2gr(const XReg& rd, const uint32_t cj) { Loongarch2RegZeroExtend(0b100010100110111, cj, rd.getIdx(), 2); }
void CodeGenerator::fcvt_s_d(const XReg& fd, const XReg& fj) { Loongarch2Reg(0b100011001000110, fj.getIdx(), fd.getIdx()); }
void CodeGenerator::fcvt_d_s(const XReg& fd, const XReg& fj) { Loongarch2Reg(0b100011001001001, fj.getIdx(), fd.getIdx()); }
void CodeGenerator::ftintrm_w_s(const XReg& fd, const XReg& fj) { Loongarch2Reg(0b100011010000001, fj.getIdx(), fd.getIdx()); }
void CodeGenerator::ftintrm_w_d(const XReg& fd, const XReg& fj) { Loongarch2Reg(0b100011010000010, fj.getIdx(), fd.getIdx()); }
void CodeGenerator::ftintrm_l_s(const XReg& fd, const XReg& fj) { Loongarch2Reg(0b100011010001001, fj.getIdx(), fd.getIdx()); }
void CodeGenerator::ftintrm_l_d(const XReg& fd, const XReg& fj) { Loongarch2Reg(0b100011010001010, fj.getIdx(), fd.getIdx()); }
void CodeGenerator::ftintrp_w_s(const XReg& fd, const XReg& fj) { Loongarch2Reg(0b100011010010001, fj.getIdx(), fd.getIdx()); }
void CodeGenerator::ftintrp_w_d(const XReg& fd, const XReg& fj) { Loongarch2Reg(0b100011010010010, fj.getIdx(), fd.getIdx()); }
void CodeGenerator::ftintrp_l_s(const XReg& fd, const XReg& fj) { Loongarch2Reg(0b100011010011001, fj.getIdx(), fd.getIdx()); }
void CodeGenerator::ftintrp_l_d(const XReg& fd, const XReg& fj) { Loongarch2Reg(0b100011010011010, fj.getIdx(), fd.getIdx()); }
void CodeGenerator::ftintrz_w_s(const XReg& fd, const XReg& fj) { Loongarch2Reg(0b100011010100001, fj.getIdx(), fd.getIdx()); }
void CodeGenerator::ftintrz_w_d(const XReg& fd, const XReg& fj) { Loongarch2Reg(0b100011010100010, fj.getIdx(), fd.getIdx()); }
void CodeGenerator::ftintrz_l_s(const XReg& fd, const XReg& fj) { Loongarch2Reg(0b100011010101001, fj.getIdx(), fd.getIdx()); }
void CodeGenerator::ftintrz_l_d(const XReg& fd, const XReg& fj) { Loongarch2Reg(0b100011010101010, fj.getIdx(), fd.getIdx()); }
void CodeGenerator::ftintrne_w_s(const XReg& fd, const XReg& fj) { Loongarch2Reg(0b100011010110001, fj.getIdx(), fd.getIdx()); }
void CodeGenerator::ftintrne_w_d(const XReg& fd, const XReg& fj) { Loongarch2Reg(0b100011010110010, fj.getIdx(), fd.getIdx()); }
void CodeGenerator::ftintrne_l_s(const XReg& fd, const XReg& fj) { Loongarch2Reg(0b100011010111001, fj.getIdx(), fd.getIdx()); }
void CodeGenerator::ftintrne_l_d(const XReg& fd, const XReg& fj) { Loongarch2Reg(0b100011010111010, fj.getIdx(), fd.getIdx()); }
void CodeGenerator::ftint_w_s(const XReg& fd, const XReg& fj) { Loongarch2Reg(0b100011011000001, fj.getIdx(), fd.getIdx()); }
void CodeGenerator::ftint_w_d(const XReg& fd, const XReg& fj) { Loongarch2Reg(0b100011011000010, fj.getIdx(), fd.getIdx()); }
void CodeGenerator::ftint_l_s(const XReg& fd, const XReg& fj) { Loongarch2Reg(0b100011011001001, fj.getIdx(), fd.getIdx()); }
void CodeGenerator::ftint_l_d(const XReg& fd, const XReg& fj) { Loongarch2Reg(0b100011011001010, fj.getIdx(), fd.getIdx()); }
void CodeGenerator::ffint_s_w(const XReg& fd, const XReg& fj) { Loongarch2Reg(0b100011101000100, fj.getIdx(), fd.getIdx()); }
void CodeGenerator::ffint_s_l(const XReg& fd, const XReg& fj) { Loongarch2Reg(0b100011101000110, fj.getIdx(), fd.getIdx()); }
void CodeGenerator::ffint_d_w(const XReg& fd, const XReg& fj) { Loongarch2Reg(0b100011101001000, fj.getIdx(), fd.getIdx()); }
void CodeGenerator::ffint_d_l(const XReg& fd, const XReg& fj) { Loongarch2Reg(0b100011101001010, fj.getIdx(), fd.getIdx()); }
void CodeGenerator::frint_s(const XReg& fd, const XReg& fj) { Loongarch2Reg(0b100011110010001, fj.getIdx(), fd.getIdx()); }
void CodeGenerator::frint_d(const XReg& fd, const XReg& fj) { Loongarch2Reg(0b100011110010010, fj.getIdx(), fd.getIdx()); }
void CodeGenerator::slti(const XReg& rd, const XReg& rj, int32_t si12) { Loongarch2Reg1Offset(0b1000, rj.getIdx(), rd.getIdx(), si12, 2); }
void CodeGenerator::sltui(const XReg& rd, const XReg& rj, int32_t si12) { Loongarch2Reg1Offset(0b1001, rj.getIdx(), rd.getIdx(), si12, 2); }
void CodeGenerator::addi_w(const XReg& rd, const XReg& rj, int32_t si12) { Loongarch2Reg1Offset(0b1010, rj.getIdx(), rd.getIdx(), si12, 2); }
void CodeGenerator::addi_d(const XReg& rd, const XReg& rj, int32_t si12) { Loongarch2Reg1Offset(0b1011, rj.getIdx(), rd.getIdx(), si12, 2); }
void CodeGenerator::lu52i_d(const XReg& rd, const XReg& rj, int32_t si12) { Loongarch2Reg1Offset(0b1100, rj.getIdx(), rd.getIdx(), si12, 2); }
void CodeGenerator::ori(const XReg& rd, const XReg& rj, int32_t ui12) { Loongarch2Reg1Offset(0b1110, rj.getIdx(), rd.getIdx(), ui12, 5); }
void CodeGenerator::xori(const XReg& rd, const XReg& rj, int32_t ui12) { Loongarch2Reg1Offset(0b1111, rj.getIdx(), rd.getIdx(), ui12, 5); }
void CodeGenerator::csrrd(const XReg& rd, int32_t csr14) { Loongarch2Reg1Offset(0b100, 0, rd.getIdx(), csr14, 8); }
void CodeGenerator::csrwr(const XReg& rd, int32_t csr14) { Loongarch2Reg1Offset(0b100, 1, rd.getIdx(), csr14, 8); }
void CodeGenerator::csrxchg(const XReg& rd, const XReg& rj, int32_t csr14) { Loongarch2Reg1Offset(0b100, rj.getIdx(), rd.getIdx(), csr14, 8); }
void CodeGenerator::cacop(const int32_t code5, const XReg& rj, int32_t si12) { Loongarch2Reg1Offset(0b11000, rj.getIdx(), code5, si12, 2); }
void CodeGenerator::lddir(const XReg& rd, const XReg& rj, int32_t level8) { Loongarch2Reg1Offset(0b110010000, rj.getIdx(), rd.getIdx(), level8, 7); }
void CodeGenerator::ldpte(const XReg& rj, int32_t seq8) { Loongarch2Reg1Offset(0b110010001, rj.getIdx(), 0, seq8, 7); }
void CodeGenerator::iocsrrd_b(const XReg& rd, const XReg& rj) { Loongarch2Reg(0b11001001000000000, rj.getIdx(), rd.getIdx()); }
void CodeGenerator::iocsrrd_h(const XReg& rd, const XReg& rj) { Loongarch2Reg(0b11001001000000001, rj.getIdx(), rd.getIdx()); }
void CodeGenerator::iocsrrd_w(const XReg& rd, const XReg& rj) { Loongarch2Reg(0b11001001000000010, rj.getIdx(), rd.getIdx()); }
void CodeGenerator::iocsrrd_d(const XReg& rd, const XReg& rj) { Loongarch2Reg(0b11001001000000011, rj.getIdx(), rd.getIdx()); }
void CodeGenerator::iocsrwr_b(const XReg& rd, const XReg& rj) { Loongarch2Reg(0b11001001000000100, rj.getIdx(), rd.getIdx()); }
void CodeGenerator::iocsrwr_h(const XReg& rd, const XReg& rj) { Loongarch2Reg(0b11001001000000101, rj.getIdx(), rd.getIdx()); }
void CodeGenerator::iocsrwr_w(const XReg& rd, const XReg& rj) { Loongarch2Reg(0b11001001000000110, rj.getIdx(), rd.getIdx()); }
void CodeGenerator::iocsrwr_d(const XReg& rd, const XReg& rj) { Loongarch2Reg(0b11001001000000111, rj.getIdx(), rd.getIdx()); }
void CodeGenerator::tlbclr() { LoongarchOnlyOpcode(0b00000110010010000010000000000000); }
void CodeGenerator::tlbflush() { LoongarchOnlyOpcode(0b00000110010010000010010000000000); }
void CodeGenerator::tlbsrch() { LoongarchOnlyOpcode(0b00000110010010000010100000000000); }
void CodeGenerator::tlbrd() { LoongarchOnlyOpcode(0b00000110010010000010110000000000); }
void CodeGenerator::tlbwr() { LoongarchOnlyOpcode(0b00000110010010000011000000000000); }
void CodeGenerator::tlbfill() { LoongarchOnlyOpcode(0b00000110010010000011010000000000); }
void CodeGenerator::ertn() { LoongarchOnlyOpcode(0b00000110010010000011100000000000); }
void CodeGenerator::idle(int32_t level15) { Loongarch1Code(0b00000110010010001, level15); }
void CodeGenerator::invtlb(const int32_t op, const XReg& rj, const XReg& rk) { Loongarch3Reg(0b00000110010010011, rk.getIdx(), rj.getIdx(), op); }
void CodeGenerator::fmadd_s(const XReg& fd, const XReg& fj, const XReg& fk, const XReg& fa) { Loongarch4Reg(0b10000001, fa.getIdx(), fk.getIdx(), fj.getIdx(), fd.getIdx()); }
void CodeGenerator::fmadd_d(const XReg& fd, const XReg& fj, const XReg& fk, const XReg& fa) { Loongarch4Reg(0b10000010, fa.getIdx(), fk.getIdx(), fj.getIdx(), fd.getIdx()); }
void CodeGenerator::fmsub_s(const XReg& fd, const XReg& fj, const XReg& fk, const XReg& fa) { Loongarch4Reg(0b10000101, fa.getIdx(), fk.getIdx(), fj.getIdx(), fd.getIdx()); }
void CodeGenerator::fmsub_d(const XReg& fd, const XReg& fj, const XReg& fk, const XReg& fa) { Loongarch4Reg(0b10000110, fa.getIdx(), fk.getIdx(), fj.getIdx(), fd.getIdx()); }
void CodeGenerator::fnmadd_s(const XReg& fd, const XReg& fj, const XReg& fk, const XReg& fa) { Loongarch4Reg(0b10001001, fa.getIdx(), fk.getIdx(), fj.getIdx(), fd.getIdx()); }
void CodeGenerator::fnmadd_d(const XReg& fd, const XReg& fj, const XReg& fk, const XReg& fa) { Loongarch4Reg(0b10001010, fa.getIdx(), fk.getIdx(), fj.getIdx(), fd.getIdx()); }
void CodeGenerator::fnmsub_s(const XReg& fd, const XReg& fj, const XReg& fk, const XReg& fa) { Loongarch4Reg(0b10001101, fa.getIdx(), fk.getIdx(), fj.getIdx(), fd.getIdx()); }
void CodeGenerator::fnmsub_d(const XReg& fd, const XReg& fj, const XReg& fk, const XReg& fa) { Loongarch4Reg(0b10001110, fa.getIdx(), fk.getIdx(), fj.getIdx(), fd.getIdx()); }
void CodeGenerator::fcmp_caf_s(const uint32_t cd, const XReg& fj, const XReg& fk) { Loongarch4Reg(0b11000001, 0b00000, fk.getIdx(), fj.getIdx(), cd); }
void CodeGenerator::fcmp_caf_d(const uint32_t cd, const XReg& fj, const XReg& fk) { Loongarch4Reg(0b11000010, 0b00000, fk.getIdx(), fj.getIdx(), cd); }
void CodeGenerator::fcmp_cun_s(const uint32_t cd, const XReg& fj, const XReg& fk) { Loongarch4Reg(0b11000001, 0b01000, fk.getIdx(), fj.getIdx(), cd); }
void CodeGenerator::fcmp_cun_d(const uint32_t cd, const XReg& fj, const XReg& fk) { Loongarch4Reg(0b11000010, 0b01000, fk.getIdx(), fj.getIdx(), cd); }
void CodeGenerator::fcmp_ceq_s(const uint32_t cd, const XReg& fj, const XReg& fk) { Loongarch4Reg(0b11000001, 0b00100, fk.getIdx(), fj.getIdx(), cd); }
void CodeGenerator::fcmp_ceq_d(const uint32_t cd, const XReg& fj, const XReg& fk) { Loongarch4Reg(0b11000010, 0b00100, fk.getIdx(), fj.getIdx(), cd); }
void CodeGenerator::fcmp_cueq_s(const uint32_t cd, const XReg& fj, const XReg& fk) { Loongarch4Reg(0b11000001, 0b01100, fk.getIdx(), fj.getIdx(), cd); }
void CodeGenerator::fcmp_cueq_d(const uint32_t cd, const XReg& fj, const XReg& fk) { Loongarch4Reg(0b11000010, 0b01100, fk.getIdx(), fj.getIdx(), cd); }
void CodeGenerator::fcmp_clt_s(const uint32_t cd, const XReg& fj, const XReg& fk) { Loongarch4Reg(0b11000001, 0b00010, fk.getIdx(), fj.getIdx(), cd); }
void CodeGenerator::fcmp_clt_d(const uint32_t cd, const XReg& fj, const XReg& fk) { Loongarch4Reg(0b11000010, 0b00010, fk.getIdx(), fj.getIdx(), cd); }
void CodeGenerator::fcmp_cult_s(const uint32_t cd, const XReg& fj, const XReg& fk) { Loongarch4Reg(0b11000001, 0b01010, fk.getIdx(), fj.getIdx(), cd); }
void CodeGenerator::fcmp_cult_d(const uint32_t cd, const XReg& fj, const XReg& fk) { Loongarch4Reg(0b11000010, 0b01010, fk.getIdx(), fj.getIdx(), cd); }
void CodeGenerator::fcmp_cle_s(const uint32_t cd, const XReg& fj, const XReg& fk) { Loongarch4Reg(0b11000001, 0b00110, fk.getIdx(), fj.getIdx(), cd); }
void CodeGenerator::fcmp_cle_d(const uint32_t cd, const XReg& fj, const XReg& fk) { Loongarch4Reg(0b11000010, 0b00110, fk.getIdx(), fj.getIdx(), cd); }
void CodeGenerator::fcmp_cule_s(const uint32_t cd, const XReg& fj, const XReg& fk) { Loongarch4Reg(0b11000001, 0b01110, fk.getIdx(), fj.getIdx(), cd); }
void CodeGenerator::fcmp_cule_d(const uint32_t cd, const XReg& fj, const XReg& fk) { Loongarch4Reg(0b11000010, 0b01110, fk.getIdx(), fj.getIdx(), cd); }
void CodeGenerator::fcmp_cne_s(const uint32_t cd, const XReg& fj, const XReg& fk) { Loongarch4Reg(0b11000001, 0b10000, fk.getIdx(), fj.getIdx(), cd); }
void CodeGenerator::fcmp_cne_d(const uint32_t cd, const XReg& fj, const XReg& fk) { Loongarch4Reg(0b11000010, 0b10000, fk.getIdx(), fj.getIdx(), cd); }
void CodeGenerator::fcmp_cor_s(const uint32_t cd, const XReg& fj, const XReg& fk) { Loongarch4Reg(0b11000001, 0b10100, fk.getIdx(), fj.getIdx(), cd); }
void CodeGenerator::fcmp_cor_d(const uint32_t cd, const XReg& fj, const XReg& fk) { Loongarch4Reg(0b11000010, 0b10100, fk.getIdx(), fj.getIdx(), cd); }
void CodeGenerator::fcmp_cune_s(const uint32_t cd, const XReg& fj, const XReg& fk) { Loongarch4Reg(0b11000001, 0b11000, fk.getIdx(), fj.getIdx(), cd); }
void CodeGenerator::fcmp_cune_d(const uint32_t cd, const XReg& fj, const XReg& fk) { Loongarch4Reg(0b11000010, 0b11000, fk.getIdx(), fj.getIdx(), cd); }
void CodeGenerator::fcmp_saf_s(const uint32_t cd, const XReg& fj, const XReg& fk) { Loongarch4Reg(0b11000001, 0b00001, fk.getIdx(), fj.getIdx(), cd); }
void CodeGenerator::fcmp_saf_d(const uint32_t cd, const XReg& fj, const XReg& fk) { Loongarch4Reg(0b11000010, 0b00001, fk.getIdx(), fj.getIdx(), cd); }
void CodeGenerator::fcmp_sun_s(const uint32_t cd, const XReg& fj, const XReg& fk) { Loongarch4Reg(0b11000001, 0b01001, fk.getIdx(), fj.getIdx(), cd); }
void CodeGenerator::fcmp_sun_d(const uint32_t cd, const XReg& fj, const XReg& fk) { Loongarch4Reg(0b11000010, 0b01001, fk.getIdx(), fj.getIdx(), cd); }
void CodeGenerator::fcmp_seq_s(const uint32_t cd, const XReg& fj, const XReg& fk) { Loongarch4Reg(0b11000001, 0b00101, fk.getIdx(), fj.getIdx(), cd); }
void CodeGenerator::fcmp_seq_d(const uint32_t cd, const XReg& fj, const XReg& fk) { Loongarch4Reg(0b11000010, 0b00101, fk.getIdx(), fj.getIdx(), cd); }
void CodeGenerator::fcmp_sueq_s(const uint32_t cd, const XReg& fj, const XReg& fk) { Loongarch4Reg(0b11000001, 0b01101, fk.getIdx(), fj.getIdx(), cd); }
void CodeGenerator::fcmp_sueq_d(const uint32_t cd, const XReg& fj, const XReg& fk) { Loongarch4Reg(0b11000010, 0b01101, fk.getIdx(), fj.getIdx(), cd); }
void CodeGenerator::fcmp_slt_s(const uint32_t cd, const XReg& fj, const XReg& fk) { Loongarch4Reg(0b11000001, 0b00011, fk.getIdx(), fj.getIdx(), cd); }
void CodeGenerator::fcmp_slt_d(const uint32_t cd, const XReg& fj, const XReg& fk) { Loongarch4Reg(0b11000010, 0b00011, fk.getIdx(), fj.getIdx(), cd); }
void CodeGenerator::fcmp_sult_s(const uint32_t cd, const XReg& fj, const XReg& fk) { Loongarch4Reg(0b11000001, 0b01011, fk.getIdx(), fj.getIdx(), cd); }
void CodeGenerator::fcmp_sult_d(const uint32_t cd, const XReg& fj, const XReg& fk) { Loongarch4Reg(0b11000010, 0b01011, fk.getIdx(), fj.getIdx(), cd); }
void CodeGenerator::fcmp_sle_s(const uint32_t cd, const XReg& fj, const XReg& fk) { Loongarch4Reg(0b11000001, 0b00111, fk.getIdx(), fj.getIdx(), cd); }
void CodeGenerator::fcmp_sle_d(const uint32_t cd, const XReg& fj, const XReg& fk) { Loongarch4Reg(0b11000010, 0b00111, fk.getIdx(), fj.getIdx(), cd); }
void CodeGenerator::fcmp_sule_s(const uint32_t cd, const XReg& fj, const XReg& fk) { Loongarch4Reg(0b11000001, 0b01111, fk.getIdx(), fj.getIdx(), cd); }
void CodeGenerator::fcmp_sule_d(const uint32_t cd, const XReg& fj, const XReg& fk) { Loongarch4Reg(0b11000010, 0b01111, fk.getIdx(), fj.getIdx(), cd); }
void CodeGenerator::fcmp_sne_s(const uint32_t cd, const XReg& fj, const XReg& fk) { Loongarch4Reg(0b11000001, 0b10001, fk.getIdx(), fj.getIdx(), cd); }
void CodeGenerator::fcmp_sne_d(const uint32_t cd, const XReg& fj, const XReg& fk) { Loongarch4Reg(0b11000010, 0b10001, fk.getIdx(), fj.getIdx(), cd); }
void CodeGenerator::fcmp_sor_s(const uint32_t cd, const XReg& fj, const XReg& fk) { Loongarch4Reg(0b11000001, 0b10101, fk.getIdx(), fj.getIdx(), cd); }
void CodeGenerator::fcmp_sor_d(const uint32_t cd, const XReg& fj, const XReg& fk) { Loongarch4Reg(0b11000010, 0b10101, fk.getIdx(), fj.getIdx(), cd); }
void CodeGenerator::fcmp_sune_s(const uint32_t cd, const XReg& fj, const XReg& fk) { Loongarch4Reg(0b11000001, 0b11001, fk.getIdx(), fj.getIdx(), cd); }
void CodeGenerator::fcmp_sune_d(const uint32_t cd, const XReg& fj, const XReg& fk) { Loongarch4Reg(0b11000010, 0b11001, fk.getIdx(), fj.getIdx(), cd); }
void CodeGenerator::fsel(const XReg& fd, const XReg& fj, const XReg& fk, const uint32_t ca) { Loongarch4Reg(0b000011010000, ca, fk.getIdx(), fj.getIdx(), fd.getIdx()); }
void CodeGenerator::addu16i_d(const XReg& rd, const XReg& rj, int32_t si16) { Loongarch2Reg1Offset(0b000100, rj.getIdx(), rd.getIdx(), si16, 1); }
void CodeGenerator::lu12i_w(const XReg& rd, int32_t si20) { Loongarch1Reg1Imm(0b0001010, si20, rd.getIdx()); }
void CodeGenerator::lu32i_d(const XReg& rd, int32_t si20) { Loongarch1Reg1Imm(0b0001011, si20, rd.getIdx()); }
void CodeGenerator::pcaddi(const XReg& rd, int32_t si20) { Loongarch1Reg1Imm(0b0001100, si20, rd.getIdx()); }
void CodeGenerator::pcalau12i(const XReg& rd, int32_t si20) { Loongarch1Reg1Imm(0b0001101, si20, rd.getIdx()); }
void CodeGenerator::pcaddu12i(const XReg& rd, int32_t si20) { Loongarch1Reg1Imm(0b0001110, si20, rd.getIdx()); }
void CodeGenerator::pcaddu18i(const XReg& rd, int32_t si20) { Loongarch1Reg1Imm(0b0001111, si20, rd.getIdx()); }
void CodeGenerator::pcaddi(const XReg& rd, const Label& label) { LoongarchLabel(0b0001100, 0, rd.getIdx(), label, 5); }
void CodeGenerator::ll_w(const XReg& rd, const XReg& rj, int32_t si14) { Loongarch2Reg1Offset(0b00100000, rj.getIdx(), rd.getIdx(), si14, 6); }
void CodeGenerator::sc_w(const XReg& rd, const XReg& rj, int32_t si14) { Loongarch2Reg1Offset(0b00100001, rj.getIdx(), rd.getIdx(), si14, 6); }
void CodeGenerator::ll_d(const XReg& rd, const XReg& rj, int32_t si14) { Loongarch2Reg1Offset(0b00100010, rj.getIdx(), rd.getIdx(), si14, 6); }
void CodeGenerator::sc_d(const XReg& rd, const XReg& rj, int32_t si14) { Loongarch2Reg1Offset(0b00100011, rj.getIdx(), rd.getIdx(), si14, 6); }
void CodeGenerator::ldptr_w(const XReg& rd, const XReg& rj, int32_t si14) { Loongarch2Reg1Offset(0b00100100, rj.getIdx(), rd.getIdx(), si14, 6); }
void CodeGenerator::stptr_w(const XReg& rd, const XReg& rj, int32_t si14) { Loongarch2Reg1Offset(0b00100101, rj.getIdx(), rd.getIdx(), si14, 6); }
void CodeGenerator::ldptr_d(const XReg& rd, const XReg& rj, int32_t si14) { Loongarch2Reg1Offset(0b00100110, rj.getIdx(), rd.getIdx(), si14, 6); }
void CodeGenerator::stptr_d(const XReg& rd, const XReg& rj, int32_t si14) { Loongarch2Reg1Offset(0b00100111, rj.getIdx(), rd.getIdx(), si14, 6); }
void CodeGenerator::ld_b(const XReg& rd, const XReg& rj, int32_t si12) { Loongarch2Reg1Offset(0b0010100000, rj.getIdx(), rd.getIdx(), si12, 2); }
void CodeGenerator::ld_h(const XReg& rd, const XReg& rj, int32_t si12) { Loongarch2Reg1Offset(0b0010100001, rj.getIdx(), rd.getIdx(), si12, 2); }
void CodeGenerator::ld_w(const XReg& rd, const XReg& rj, int32_t si12) { Loongarch2Reg1Offset(0b0010100010, rj.getIdx(), rd.getIdx(), si12, 2); }
void CodeGenerator::ld_d(const XReg& rd, const XReg& rj, int32_t si12) { Loongarch2Reg1Offset(0b0010100011, rj.getIdx(), rd.getIdx(), si12, 2); }
void CodeGenerator::st_b(const XReg& rd, const XReg& rj, int32_t si12) { Loongarch2Reg1Offset(0b0010100100, rj.getIdx(), rd.getIdx(), si12, 2); }
void CodeGenerator::st_h(const XReg& rd, const XReg& rj, int32_t si12) { Loongarch2Reg1Offset(0b0010100101, rj.getIdx(), rd.getIdx(), si12, 2); }
void CodeGenerator::st_w(const XReg& rd, const XReg& rj, int32_t si12) { Loongarch2Reg1Offset(0b0010100110, rj.getIdx(), rd.getIdx(), si12, 2); }
void CodeGenerator::st_d(const XReg& rd, const XReg& rj, int32_t si12) { Loongarch2Reg1Offset(0b0010100111, rj.getIdx(), rd.getIdx(), si12, 2); }
void CodeGenerator::ld_bu(const XReg& rd, const XReg& rj, int32_t si12) { Loongarch2Reg1Offset(0b0010101000, rj.getIdx(), rd.getIdx(), si12, 2); }
void CodeGenerator::ld_hu(const XReg& rd, const XReg& rj, int32_t si12) { Loongarch2Reg1Offset(0b0010101001, rj.getIdx(), rd.getIdx(), si12, 2); }
void CodeGenerator::ld_wu(const XReg& rd, const XReg& rj, int32_t si12) { Loongarch2Reg1Offset(0b0010101010, rj.getIdx(), rd.getIdx(), si12, 2); }
void CodeGenerator::preld(const int32_t hint, const XReg& rj, int32_t si12) { Loongarch2Reg1Offset(0b0010101011, rj.getIdx(), hint, si12, 2); }
void CodeGenerator::fld_s(const XReg& fd, const XReg& rj, int32_t si12) { Loongarch2Reg1Offset(0b0010101100, rj.getIdx(), fd.getIdx(), si12, 2); }
void CodeGenerator::fst_s(const XReg& fd, const XReg& rj, int32_t si12) { Loongarch2Reg1Offset(0b0010101101, rj.getIdx(), fd.getIdx(), si12, 2); }
void CodeGenerator::fld_d(const XReg& fd, const XReg& rj, int32_t si12) { Loongarch2Reg1Offset(0b0010101110, rj.getIdx(), fd.getIdx(), si12, 2); }
void CodeGenerator::fst_d(const XReg& fd, const XReg& rj, int32_t si12) { Loongarch2Reg1Offset(0b0010101111, rj.getIdx(), fd.getIdx(), si12, 2); }
void CodeGenerator::ldx_b(const XReg& rd, const XReg& rj, const XReg& rk) { Loongarch3Reg(0b00111000000000000, rk.getIdx(), rj.getIdx(), rd.getIdx()); }
void CodeGenerator::ldx_h(const XReg& rd, const XReg& rj, const XReg& rk) { Loongarch3Reg(0b00111000000001000, rk.getIdx(), rj.getIdx(), rd.getIdx()); }
void CodeGenerator::ldx_w(const XReg& rd, const XReg& rj, const XReg& rk) { Loongarch3Reg(0b00111000000010000, rk.getIdx(), rj.getIdx(), rd.getIdx()); }
void CodeGenerator::ldx_d(const XReg& rd, const XReg& rj, const XReg& rk) { Loongarch3Reg(0b00111000000011000, rk.getIdx(), rj.getIdx(), rd.getIdx()); }
void CodeGenerator::stx_b(const XReg& rd, const XReg& rj, const XReg& rk) { Loongarch3Reg(0b00111000000100000, rk.getIdx(), rj.getIdx(), rd.getIdx()); }
void CodeGenerator::stx_h(const XReg& rd, const XReg& rj, const XReg& rk) { Loongarch3Reg(0b00111000000101000, rk.getIdx(), rj.getIdx(), rd.getIdx()); }
void CodeGenerator::stx_w(const XReg& rd, const XReg& rj, const XReg& rk) { Loongarch3Reg(0b00111000000110000, rk.getIdx(), rj.getIdx(), rd.getIdx()); }
void CodeGenerator::stx_d(const XReg& rd, const XReg& rj, const XReg& rk) { Loongarch3Reg(0b00111000000111000, rk.getIdx(), rj.getIdx(), rd.getIdx()); }
void CodeGenerator::ldx_bu(const XReg& rd, const XReg& rj, const XReg& rk) { Loongarch3Reg(0b00111000001000000, rk.getIdx(), rj.getIdx(), rd.getIdx()); }
void CodeGenerator::ldx_hu(const XReg& rd, const XReg& rj, const XReg& rk) { Loongarch3Reg(0b00111000001001000, rk.getIdx(), rj.getIdx(), rd.getIdx()); }
void CodeGenerator::ldx_wu(const XReg& rd, const XReg& rj, const XReg& rk) { Loongarch3Reg(0b00111000001010000, rk.getIdx(), rj.getIdx(), rd.getIdx()); }
void CodeGenerator::preldx(const int32_t hint, const XReg& rj, const XReg& rk) { Loongarch3Reg(0b00111000001011000, rk.getIdx(), rj.getIdx(), hint); }
void CodeGenerator::fldx_s(const XReg& fd, const XReg& rj, const XReg& rk) { Loongarch3Reg(0b00111000001100000, rk.getIdx(), rj.getIdx(), fd.getIdx()); }
void CodeGenerator::fldx_d(const XReg& fd, const XReg& rj, const XReg& rk) { Loongarch3Reg(0b00111000001101000, rk.getIdx(), rj.getIdx(), fd.getIdx()); }
void CodeGenerator::fstx_s(const XReg& fd, const XReg& rj, const XReg& rk) { Loongarch3Reg(0b00111000001110000, rk.getIdx(), rj.getIdx(), fd.getIdx()); }
void CodeGenerator::fstx_d(const XReg& fd, const XReg& rj, const XReg& rk) { Loongarch3Reg(0b00111000001111000, rk.getIdx(), rj.getIdx(), fd.getIdx()); }
void CodeGenerator::amswap_w(const XReg& rd, const XReg& rk, const XReg& rj) { Loongarch3Reg(0b00111000011000000, rk.getIdx(), rj.getIdx(), rd.getIdx()); }
void CodeGenerator::amswap_d(const XReg& rd, const XReg& rk, const XReg& rj) { Loongarch3Reg(0b00111000011000001, rk.getIdx(), rj.getIdx(), rd.getIdx()); }
void CodeGenerator::amadd_w(const XReg& rd, const XReg& rk, const XReg& rj) { Loongarch3Reg(0b00111000011000010, rk.getIdx(), rj.getIdx(), rd.getIdx()); }
void CodeGenerator::amadd_d(const XReg& rd, const XReg& rk, const XReg& rj) { Loongarch3Reg(0b00111000011000011, rk.getIdx(), rj.getIdx(), rd.getIdx()); }
void CodeGenerator::amand_w(const XReg& rd, const XReg& rk, const XReg& rj) { Loongarch3Reg(0b00111000011000100, rk.getIdx(), rj.getIdx(), rd.getIdx()); }
void CodeGenerator::amand_d(const XReg& rd, const XReg& rk, const XReg& rj) { Loongarch3Reg(0b00111000011000101, rk.getIdx(), rj.getIdx(), rd.getIdx()); }
void CodeGenerator::amor_w(const XReg& rd, const XReg& rk, const XReg& rj) { Loongarch3Reg(0b00111000011000110, rk.getIdx(), rj.getIdx(), rd.getIdx()); }
void CodeGenerator::amor_d(const XReg& rd, const XReg& rk, const XReg& rj) { Loongarch3Reg(0b00111000011000111, rk.getIdx(), rj.getIdx(), rd.getIdx()); }
void CodeGenerator::amxor_w(const XReg& rd, const XReg& rk, const XReg& rj) { Loongarch3Reg(0b00111000011001000, rk.getIdx(), rj.getIdx(), rd.getIdx()); }
void CodeGenerator::amxor_d(const XReg& rd, const XReg& rk, const XReg& rj) { Loongarch3Reg(0b00111000011001001, rk.getIdx(), rj.getIdx(), rd.getIdx()); }
void CodeGenerator::ammax_w(const XReg& rd, const XReg& rk, const XReg& rj) { Loongarch3Reg(0b00111000011001010, rk.getIdx(), rj.getIdx(), rd.getIdx()); }
void CodeGenerator::ammax_d(const XReg& rd, const XReg& rk, const XReg& rj) { Loongarch3Reg(0b00111000011001011, rk.getIdx(), rj.getIdx(), rd.getIdx()); }
void CodeGenerator::ammin_w(const XReg& rd, const XReg& rk, const XReg& rj) { Loongarch3Reg(0b00111000011001100, rk.getIdx(), rj.getIdx(), rd.getIdx()); }
void CodeGenerator::ammin_d(const XReg& rd, const XReg& rk, const XReg& rj) { Loongarch3Reg(0b00111000011001101, rk.getIdx(), rj.getIdx(), rd.getIdx()); }
void CodeGenerator::ammax_wu(const XReg& rd, const XReg& rk, const XReg& rj) { Loongarch3Reg(0b00111000011001110, rk.getIdx(), rj.getIdx(), rd.getIdx()); }
void CodeGenerator::ammax_du(const XReg& rd, const XReg& rk, const XReg& rj) { Loongarch3Reg(0b00111000011001111, rk.getIdx(), rj.getIdx(), rd.getIdx()); }
void CodeGenerator::ammin_wu(const XReg& rd, const XReg& rk, const XReg& rj) { Loongarch3Reg(0b00111000011010000, rk.getIdx(), rj.getIdx(), rd.getIdx()); }
void CodeGenerator::ammin_du(const XReg& rd, const XReg& rk, const XReg& rj) { Loongarch3Reg(0b00111000011010001, rk.getIdx(), rj.getIdx(), rd.getIdx()); }
void CodeGenerator::amswap_db_w(const XReg& rd, const XReg& rk, const XReg& rj) { Loongarch3Reg(0b00111000011010010, rk.getIdx(), rj.getIdx(), rd.getIdx()); }
void CodeGenerator::amswap_db_d(const XReg& rd, const XReg& rk, const XReg& rj) { Loongarch3Reg(0b00111000011010011, rk.getIdx(), rj.getIdx(), rd.getIdx()); }
void CodeGenerator::amadd_db_w(const XReg& rd, const XReg& rk, const XReg& rj) { Loongarch3Reg(0b00111000011010100, rk.getIdx(), rj.getIdx(), rd.getIdx()); }
void CodeGenerator::amadd_db_d(const XReg& rd, const XReg& rk, const XReg& rj) { Loongarch3Reg(0b00111000011010101, rk.getIdx(), rj.getIdx(), rd.getIdx()); }
void CodeGenerator::amand_db_w(const XReg& rd, const XReg& rk, const XReg& rj) { Loongarch3Reg(0b00111000011010110, rk.getIdx(), rj.getIdx(), rd.getIdx()); }
void CodeGenerator::amand_db_d(const XReg& rd, const XReg& rk, const XReg& rj) { Loongarch3Reg(0b00111000011010111, rk.getIdx(), rj.getIdx(), rd.getIdx()); }
void CodeGenerator::amor_db_w(const XReg& rd, const XReg& rk, const XReg& rj) { Loongarch3Reg(0b00111000011011000, rk.getIdx(), rj.getIdx(), rd.getIdx()); }
void CodeGenerator::amor_db_d(const XReg& rd, const XReg& rk, const XReg& rj) { Loongarch3Reg(0b00111000011011001, rk.getIdx(), rj.getIdx(), rd.getIdx()); }
void CodeGenerator::amxor_db_w(const XReg& rd, const XReg& rk, const XReg& rj) { Loongarch3Reg(0b00111000011011010, rk.getIdx(), rj.getIdx(), rd.getIdx()); }
void CodeGenerator::amxor_db_d(const XReg& rd, const XReg& rk, const XReg& rj) { Loongarch3Reg(0b00111000011011011, rk.getIdx(), rj.getIdx(), rd.getIdx()); }
void CodeGenerator::ammax_db_w(const XReg& rd, const XReg& rk, const XReg& rj) { Loongarch3Reg(0b00111000011011100, rk.getIdx(), rj.getIdx(), rd.getIdx()); }
void CodeGenerator::ammax_db_d(const XReg& rd, const XReg& rk, const XReg& rj) { Loongarch3Reg(0b00111000011011101, rk.getIdx(), rj.getIdx(), rd.getIdx()); }
void CodeGenerator::ammin_db_w(const XReg& rd, const XReg& rk, const XReg& rj) { Loongarch3Reg(0b00111000011011110, rk.getIdx(), rj.getIdx(), rd.getIdx()); }
void CodeGenerator::ammin_db_d(const XReg& rd, const XReg& rk, const XReg& rj) { Loongarch3Reg(0b00111000011011111, rk.getIdx(), rj.getIdx(), rd.getIdx()); }
void CodeGenerator::ammax_db_wu(const XReg& rd, const XReg& rk, const XReg& rj) { Loongarch3Reg(0b00111000011100000, rk.getIdx(), rj.getIdx(), rd.getIdx()); }
void CodeGenerator::ammax_db_du(const XReg& rd, const XReg& rk, const XReg& rj) { Loongarch3Reg(0b00111000011100001, rk.getIdx(), rj.getIdx(), rd.getIdx()); }
void CodeGenerator::ammin_db_wu(const XReg& rd, const XReg& rk, const XReg& rj) { Loongarch3Reg(0b00111000011100010, rk.getIdx(), rj.getIdx(), rd.getIdx()); }
void CodeGenerator::ammin_db_du(const XReg& rd, const XReg& rk, const XReg& rj) { Loongarch3Reg(0b00111000011100011, rk.getIdx(), rj.getIdx(), rd.getIdx()); }
void CodeGenerator::dbar(const int32_t hint) { Loongarch1Code(0b00111000011100100, hint); }
void CodeGenerator::ibar(const int32_t hint) { Loongarch1Code(0b00111000011100101, hint); }
void CodeGenerator::fldgt_s(const XReg& fd, const XReg& rj, const XReg& rk) { Loongarch3Reg(0b00111000011101000, rk.getIdx(), rj.getIdx(), fd.getIdx()); }
void CodeGenerator::fldgt_d(const XReg& fd, const XReg& rj, const XReg& rk) { Loongarch3Reg(0b00111000011101001, rk.getIdx(), rj.getIdx(), fd.getIdx()); }
void CodeGenerator::fldle_s(const XReg& fd, const XReg& rj, const XReg& rk) { Loongarch3Reg(0b00111000011101010, rk.getIdx(), rj.getIdx(), fd.getIdx()); }
void CodeGenerator::fldle_d(const XReg& fd, const XReg& rj, const XReg& rk) { Loongarch3Reg(0b00111000011101011, rk.getIdx(), rj.getIdx(), fd.getIdx()); }
void CodeGenerator::fstgt_s(const XReg& fd, const XReg& rj, const XReg& rk) { Loongarch3Reg(0b00111000011101100, rk.getIdx(), rj.getIdx(), fd.getIdx()); }
void CodeGenerator::fstgt_d(const XReg& fd, const XReg& rj, const XReg& rk) { Loongarch3Reg(0b00111000011101101, rk.getIdx(), rj.getIdx(), fd.getIdx()); }
void CodeGenerator::fstle_s(const XReg& fd, const XReg& rj, const XReg& rk) { Loongarch3Reg(0b00111000011101110, rk.getIdx(), rj.getIdx(), fd.getIdx()); }
void CodeGenerator::fstle_d(const XReg& fd, const XReg& rj, const XReg& rk) { Loongarch3Reg(0b00111000011101111, rk.getIdx(), rj.getIdx(), fd.getIdx()); }
void CodeGenerator::ldgt_b(const XReg& rd, const XReg& rj, const XReg& rk) { Loongarch3Reg(0b00111000011110000, rk.getIdx(), rj.getIdx(), rd.getIdx()); }
void CodeGenerator::ldgt_h(const XReg& rd, const XReg& rj, const XReg& rk) { Loongarch3Reg(0b00111000011110001, rk.getIdx(), rj.getIdx(), rd.getIdx()); }
void CodeGenerator::ldgt_w(const XReg& rd, const XReg& rj, const XReg& rk) { Loongarch3Reg(0b00111000011110010, rk.getIdx(), rj.getIdx(), rd.getIdx()); }
void CodeGenerator::ldgt_d(const XReg& rd, const XReg& rj, const XReg& rk) { Loongarch3Reg(0b00111000011110011, rk.getIdx(), rj.getIdx(), rd.getIdx()); }
void CodeGenerator::ldle_b(const XReg& rd, const XReg& rj, const XReg& rk) { Loongarch3Reg(0b00111000011110100, rk.getIdx(), rj.getIdx(), rd.getIdx()); }
void CodeGenerator::ldle_h(const XReg& rd, const XReg& rj, const XReg& rk) { Loongarch3Reg(0b00111000011110101, rk.getIdx(), rj.getIdx(), rd.getIdx()); }
void CodeGenerator::ldle_w(const XReg& rd, const XReg& rj, const XReg& rk) { Loongarch3Reg(0b00111000011110110, rk.getIdx(), rj.getIdx(), rd.getIdx()); }
void CodeGenerator::ldle_d(const XReg& rd, const XReg& rj, const XReg& rk) { Loongarch3Reg(0b00111000011110111, rk.getIdx(), rj.getIdx(), rd.getIdx()); }
void CodeGenerator::stgt_b(const XReg& rd, const XReg& rj, const XReg& rk) { Loongarch3Reg(0b00111000011111000, rk.getIdx(), rj.getIdx(), rd.getIdx()); }
void CodeGenerator::stgt_h(const XReg& rd, const XReg& rj, const XReg& rk) { Loongarch3Reg(0b00111000011111001, rk.getIdx(), rj.getIdx(), rd.getIdx()); }
void CodeGenerator::stgt_w(const XReg& rd, const XReg& rj, const XReg& rk) { Loongarch3Reg(0b00111000011111010, rk.getIdx(), rj.getIdx(), rd.getIdx()); }
void CodeGenerator::stgt_d(const XReg& rd, const XReg& rj, const XReg& rk) { Loongarch3Reg(0b00111000011111011, rk.getIdx(), rj.getIdx(), rd.getIdx()); }
void CodeGenerator::stle_b(const XReg& rd, const XReg& rj, const XReg& rk) { Loongarch3Reg(0b00111000011111100, rk.getIdx(), rj.getIdx(), rd.getIdx()); }
void CodeGenerator::stle_h(const XReg& rd, const XReg& rj, const XReg& rk) { Loongarch3Reg(0b00111000011111101, rk.getIdx(), rj.getIdx(), rd.getIdx()); }
void CodeGenerator::stle_w(const XReg& rd, const XReg& rj, const XReg& rk) { Loongarch3Reg(0b00111000011111110, rk.getIdx(), rj.getIdx(), rd.getIdx()); }
void CodeGenerator::stle_d(const XReg& rd, const XReg& rj, const XReg& rk) { Loongarch3Reg(0b00111000011111111, rk.getIdx(), rj.getIdx(), rd.getIdx()); }
void CodeGenerator::nop() { andi(zero, zero, 0); }
void CodeGenerator::jirl(const XReg& rd, const XReg& rj, int64_t offset) { dd(LoongarchLabelEnc(0b010011, rj.getIdx(), rd.getIdx(), offset, 1)); }
void CodeGenerator::bltu(const XReg& rj, const XReg& rd, int64_t offset) { dd(LoongarchLabelEnc(0b011010, rj.getIdx(), rd.getIdx(), offset, 1)); }
void CodeGenerator::bgeu(const XReg& rj, const XReg& rd, int64_t offset) { dd(LoongarchLabelEnc(0b011011, rj.getIdx(), rd.getIdx(), offset, 1)); }
void CodeGenerator::beqz(const XReg& rj, int64_t offset21) { dd(LoongarchLabelEnc(0b010000, rj.getIdx(), 0, offset21, 2)); }
void CodeGenerator::bnez(const XReg& rj, int64_t offset21) { dd(LoongarchLabelEnc(0b010001, rj.getIdx(), 0, offset21, 2)); }
void CodeGenerator::bceqz(const uint32_t cj, int64_t offset21) { dd(LoongarchLabelEnc(0b010010, cj, 0, offset21, 2)); }
void CodeGenerator::bcnez(const uint32_t cj, int64_t offset21) { dd(LoongarchLabelEnc(0b010010, cj, 0, offset21, 3)); }
void CodeGenerator::beq(const XReg& rj, const XReg& rd, int64_t offset) { dd(LoongarchLabelEnc(0b010110, rj.getIdx(), rd.getIdx(), offset, 1)); }
void CodeGenerator::bne(const XReg& rj, const XReg& rd, int64_t offset) { dd(LoongarchLabelEnc(0b010111, rj.getIdx(), rd.getIdx(), offset, 1)); }
void CodeGenerator::blt(const XReg& rj, const XReg& rd, int64_t offset) { dd(LoongarchLabelEnc(0b011000, rj.getIdx(), rd.getIdx(), offset, 1)); }
void CodeGenerator::bge(const XReg& rj, const XReg& rd, int64_t offset) { dd(LoongarchLabelEnc(0b011001, rj.getIdx(), rd.getIdx(), offset, 1)); }
void CodeGenerator::b(int64_t offset26) { dd(LoongarchLabelEnc(0b010100, 0, 0, offset26, 4)); }
void CodeGenerator::bl(int64_t offset26) { dd(LoongarchLabelEnc(0b010101, 0, 0, offset26, 4)); }
void CodeGenerator::jirl(const XReg& rd, const XReg& rj, const Label& label) { LoongarchLabel(0b010011, rj.getIdx(), rd.getIdx(), label, 1); }
void CodeGenerator::bltu(const XReg& rj, const XReg& rd, const Label& label) { LoongarchLabel(0b011010, rj.getIdx(), rd.getIdx(), label, 1); }
void CodeGenerator::bgeu(const XReg& rj, const XReg& rd, const Label& label) { LoongarchLabel(0b011011, rj.getIdx(), rd.getIdx(), label, 1); }
void CodeGenerator::beqz(const XReg& rj, const Label& label) { LoongarchLabel(0b010000, rj.getIdx(), 0, label, 2); }
void CodeGenerator::bnez(const XReg& rj, const Label& label) { LoongarchLabel(0b010001, rj.getIdx(), 0, label, 2); }
void CodeGenerator::bceqz(const uint32_t cj, const Label& label) { LoongarchLabel(0b010010, cj, 0, label, 2); }
void CodeGenerator::bcnez(const uint32_t cj, const Label& label) { LoongarchLabel(0b010010, cj, 0, label, 3); }
void CodeGenerator::beq(const XReg& rj, const XReg& rd, const Label& label) { LoongarchLabel(0b010110, rj.getIdx(), rd.getIdx(), label, 1); }
void CodeGenerator::bne(const XReg& rj, const XReg& rd, const Label& label) { LoongarchLabel(0b010111, rj.getIdx(), rd.getIdx(), label, 1); }
void CodeGenerator::blt(const XReg& rj, const XReg& rd, const Label& label) { LoongarchLabel(0b011000, rj.getIdx(), rd.getIdx(), label, 1); }
void CodeGenerator::bge(const XReg& rj, const XReg& rd, const Label& label) { LoongarchLabel(0b011001, rj.getIdx(), rd.getIdx(), label, 1); }
void CodeGenerator::b(const Label& label) { LoongarchLabel(0b010100, 0, 0, label, 4); }
void CodeGenerator::bl(const Label& label) { LoongarchLabel(0b010101, 0, 0, label, 4); }
/****** Loongarch base end *****/
