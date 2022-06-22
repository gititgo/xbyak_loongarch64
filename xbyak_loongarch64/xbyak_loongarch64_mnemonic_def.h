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
/*LSX begin*/
void vadd_b(const VReg &vd, const VReg &vj, const VReg &vk);
void vadd_h(const VReg &vd, const VReg &vj, const VReg &vk);
void vadd_w(const VReg &vd, const VReg &vj, const VReg &vk);
void vadd_d(const VReg &vd, const VReg &vj, const VReg &vk);

void vmax_b(const VReg &vd, const VReg &vj, const VReg &vk);
void vmax_h(const VReg &vd, const VReg &vj, const VReg &vk);
void vmax_w(const VReg &vd, const VReg &vj, const VReg &vk);
void vmax_d(const VReg &vd, const VReg &vj, const VReg &vk);

void vmax_bu(const VReg &vd, const VReg &vj, const VReg &vk);
void vmax_hu(const VReg &vd, const VReg &vj, const VReg &vk);
void vmax_wu(const VReg &vd, const VReg &vj, const VReg &vk);
void vmax_du(const VReg &vd, const VReg &vj, const VReg &vk);

void vmin_b(const VReg &vd, const VReg &vj, const VReg &vk);
void vmin_h(const VReg &vd, const VReg &vj, const VReg &vk);
void vmin_w(const VReg &vd, const VReg &vj, const VReg &vk);
void vmin_d(const VReg &vd, const VReg &vj, const VReg &vk);

void vmin_bu(const VReg &vd, const VReg &vj, const VReg &vk);
void vmin_hu(const VReg &vd, const VReg &vj, const VReg &vk);
void vmin_wu(const VReg &vd, const VReg &vj, const VReg &vk);
void vmin_du(const VReg &vd, const VReg &vj, const VReg &vk);

void vmul_b(const VReg &vd, const VReg &vj, const VReg &vk);
void vmul_h(const VReg &vd, const VReg &vj, const VReg &vk);
void vmul_w(const VReg &vd, const VReg &vj, const VReg &vk);
void vmul_d(const VReg &vd, const VReg &vj, const VReg &vk);

void vdiv_b(const VReg &vd, const VReg &vj, const VReg &vk);
void vdiv_h(const VReg &vd, const VReg &vj, const VReg &vk);
void vdiv_w(const VReg &vd, const VReg &vj, const VReg &vk);
void vdiv_d(const VReg &vd, const VReg &vj, const VReg &vk);

void vfmax_s(const VReg &vd, const VReg &vj, const VReg &vk);
void vfmax_d(const VReg &vd, const VReg &vj, const VReg &vk);
void vfmin_s(const VReg &vd, const VReg &vj, const VReg &vk);
void vfmin_d(const VReg &vd, const VReg &vj, const VReg &vk);

void vfadd_s(const VReg &vd, const VReg &vj, const VReg &vk);
void vfadd_d(const VReg &vd, const VReg &vj, const VReg &vk);
void vfmul_s(const VReg &vd, const VReg &vj, const VReg &vk);
void vfmul_d(const VReg &vd, const VReg &vj, const VReg &vk);

void vldrepl_b(const VReg &vd, const XReg &rj, int32_t si12);
void vldrepl_h(const VReg &vd, const XReg &rj, int32_t si11);
void vldrepl_w(const VReg &vd, const XReg &rj, int32_t si10);
void vldrepl_d(const VReg &vd, const XReg &rj, int32_t si9);

void vstelm_b(const VReg &vd, const XReg &rj, int32_t si8, uint32_t idx);
void vstelm_h(const VReg &vd, const XReg &rj, int32_t si8, uint32_t idx);
void vstelm_w(const VReg &vd, const XReg &rj, int32_t si8, uint32_t idx);
void vstelm_d(const VReg &vd, const XReg &rj, int32_t si8, uint32_t idx);

void vreplve_b(const VReg &vd, const VReg &vj, const XReg &rk);
void vreplve_h(const VReg &vd, const VReg &vj, const XReg &rk);
void vreplve_w(const VReg &vd, const VReg &vj, const XReg &rk);
void vreplve_d(const VReg &vd, const VReg &vj, const XReg &rk);

void vpickev_b(const VReg &vd, const VReg &vj, const VReg &vk);
void vpickev_h(const VReg &vd, const VReg &vj, const VReg &vk);
void vpickev_w(const VReg &vd, const VReg &vj, const VReg &vk);
void vpickev_d(const VReg &vd, const VReg &vj, const VReg &vk);

void vand_v(const VReg &vd, const VReg &vj, const VReg &vk);
void vor_v(const VReg &vd, const VReg &vj, const VReg &vk);
void vxor_v(const VReg &vd, const VReg &vj, const VReg &vk);
void vnor_v(const VReg &vd, const VReg &vj, const VReg &vk);
void vandn_v(const VReg &vd, const VReg &vj, const VReg &vk);
void vorn_v(const VReg &vd, const VReg &vj, const VReg &vk);
void vffint_s_w(const VReg &vd, const VReg &vj);
void vftint_w_s(const VReg &vd, const VReg &vj);

void vreplgr2vr_b(const VReg &vd, const XReg &rj);
void vreplgr2vr_h(const VReg &vd, const XReg &rj);
void vreplgr2vr_w(const VReg &vd, const XReg &rj);
void vreplgr2vr_d(const VReg &vd, const XReg &rj);

void vextrins_d(const VReg &vd, const VReg &vj, uint32_t imm8);
void vextrins_w(const VReg &vd, const VReg &vj, uint32_t imm8);
void vextrins_h(const VReg &vd, const VReg &vj, uint32_t imm8);
void vextrins_b(const VReg &vd, const VReg &vj, uint32_t imm8);

void vseq_b(const VReg &vd, const VReg &vj, const VReg &vk);
void vseq_h(const VReg &vd, const VReg &vj, const VReg &vk);
void vseq_w(const VReg &vd, const VReg &vj, const VReg &vk);
void vseq_d(const VReg &vd, const VReg &vj, const VReg &vk);

void vfsub_s(const VReg &vd, const VReg &vj, const VReg &vk);
void vfsub_d(const VReg &vd, const VReg &vj, const VReg &vk);
void vfdiv_s(const VReg &vd, const VReg &vj, const VReg &vk);
void vfdiv_d(const VReg &vd, const VReg &vj, const VReg &vk);

void vilvl_b(const VReg &vd, const VReg &vj, const VReg &vk);
void vilvl_h(const VReg &vd, const VReg &vj, const VReg &vk);
void vilvl_w(const VReg &vd, const VReg &vj, const VReg &vk);
void vilvl_d(const VReg &vd, const VReg &vj, const VReg &vk);
void vilvh_b(const VReg &vd, const VReg &vj, const VReg &vk);
void vilvh_h(const VReg &vd, const VReg &vj, const VReg &vk);
void vilvh_w(const VReg &vd, const VReg &vj, const VReg &vk);
void vilvh_d(const VReg &vd, const VReg &vj, const VReg &vk);

void vshuf4i_b(const VReg &vd, const VReg &vj, uint32_t ui8);
void vshuf4i_h(const VReg &vd, const VReg &vj, uint32_t ui8);
void vshuf4i_w(const VReg &vd, const VReg &vj, uint32_t ui8);
void vshuf4i_d(const VReg &vd, const VReg &vj, uint32_t ui8);

void vslli_b(const VReg &vd, const VReg &vj, uint32_t ui3);
void vslli_h(const VReg &vd, const VReg &vj, uint32_t ui4);
void vslli_w(const VReg &vd, const VReg &vj, uint32_t ui5);
void vslli_d(const VReg &vd, const VReg &vj, uint32_t ui6);
void vsrli_b(const VReg &vd, const VReg &vj, uint32_t ui3);
void vsrli_h(const VReg &vd, const VReg &vj, uint32_t ui4);
void vsrli_w(const VReg &vd, const VReg &vj, uint32_t ui5);
void vsrli_d(const VReg &vd, const VReg &vj, uint32_t ui6);
void vsrai_b(const VReg &vd, const VReg &vj, uint32_t ui3);
void vsrai_h(const VReg &vd, const VReg &vj, uint32_t ui4);
void vsrai_w(const VReg &vd, const VReg &vj, uint32_t ui5);
void vsrai_d(const VReg &vd, const VReg &vj, uint32_t ui6);

void vbsll_v(const VReg &vd, const VReg &vj, uint32_t ui5);
void vbsrl_v(const VReg &vd, const VReg &vj, uint32_t ui5);

void vbitsel_v(const VReg &vd, const VReg &vj, const VReg &vk, const VReg &va);

void vfmadd_s(const VReg &vd, const VReg &vj, const VReg &vk, const VReg &va);
void vfmadd_d(const VReg &vd, const VReg &vj, const VReg &vk, const VReg &va);

#define VFCMP_MN_FUNC_DECLEAR(name) \
   void vfcmp_##name##_s(const VReg &vd, const VReg &vj, const VReg &vk); \
   void vfcmp_##name##_d(const VReg &vd, const VReg &vj, const VReg &vk);

VFCMP_MN_FUNC_DECLEAR(caf)
VFCMP_MN_FUNC_DECLEAR(cun)
VFCMP_MN_FUNC_DECLEAR(ceq)
VFCMP_MN_FUNC_DECLEAR(cueq)
VFCMP_MN_FUNC_DECLEAR(clt)
VFCMP_MN_FUNC_DECLEAR(cult)
VFCMP_MN_FUNC_DECLEAR(cle)
VFCMP_MN_FUNC_DECLEAR(cule)
VFCMP_MN_FUNC_DECLEAR(cne)
VFCMP_MN_FUNC_DECLEAR(cor)
VFCMP_MN_FUNC_DECLEAR(cune)
VFCMP_MN_FUNC_DECLEAR(saf)
VFCMP_MN_FUNC_DECLEAR(sun)
VFCMP_MN_FUNC_DECLEAR(seq)
VFCMP_MN_FUNC_DECLEAR(sueq)
VFCMP_MN_FUNC_DECLEAR(slt)
VFCMP_MN_FUNC_DECLEAR(sult)
VFCMP_MN_FUNC_DECLEAR(sle)
VFCMP_MN_FUNC_DECLEAR(sule)
VFCMP_MN_FUNC_DECLEAR(sne)
VFCMP_MN_FUNC_DECLEAR(sor)
VFCMP_MN_FUNC_DECLEAR(sune)
/*LSX end*/

/*LASX begin*/
void xvfmadd_s(const XVReg &xd, const XVReg &xj, const XVReg &xk, const XVReg &xa);
void xvfmadd_d(const XVReg &xd, const XVReg &xj, const XVReg &xk, const XVReg &xa);

void xvfmsub_s(const XVReg &xd, const XVReg &xj, const XVReg &xk, const XVReg &xa);
void xvfmsub_d(const XVReg &xd, const XVReg &xj, const XVReg &xk, const XVReg &xa);

void xvfnmadd_s(const XVReg &xd, const XVReg &xj, const XVReg &xk, const XVReg &xa);
void xvfnmadd_d(const XVReg &xd, const XVReg &xj, const XVReg &xk, const XVReg &xa);

void xvfnmsub_s(const XVReg &xd, const XVReg &xj, const XVReg &xk, const XVReg &xa);
void xvfnmsub_d(const XVReg &xd, const XVReg &xj, const XVReg &xk, const XVReg &xa);

#define XVFCMP_MN_FUNC_DECLEAR(name) \
   void xvfcmp_##name##_s(const XVReg &xd, const XVReg &xj, const XVReg &xk); \
   void xvfcmp_##name##_d(const XVReg &xd, const XVReg &xj, const XVReg &xk);

XVFCMP_MN_FUNC_DECLEAR(caf)
XVFCMP_MN_FUNC_DECLEAR(cun)
XVFCMP_MN_FUNC_DECLEAR(ceq)
XVFCMP_MN_FUNC_DECLEAR(cueq)
XVFCMP_MN_FUNC_DECLEAR(clt)
XVFCMP_MN_FUNC_DECLEAR(cult)
XVFCMP_MN_FUNC_DECLEAR(cle)
XVFCMP_MN_FUNC_DECLEAR(cule)
XVFCMP_MN_FUNC_DECLEAR(cne)
XVFCMP_MN_FUNC_DECLEAR(cor)
XVFCMP_MN_FUNC_DECLEAR(cune)
XVFCMP_MN_FUNC_DECLEAR(saf)
XVFCMP_MN_FUNC_DECLEAR(sun)
XVFCMP_MN_FUNC_DECLEAR(seq)
XVFCMP_MN_FUNC_DECLEAR(sueq)
XVFCMP_MN_FUNC_DECLEAR(slt)
XVFCMP_MN_FUNC_DECLEAR(sult)
XVFCMP_MN_FUNC_DECLEAR(sle)
XVFCMP_MN_FUNC_DECLEAR(sule)
XVFCMP_MN_FUNC_DECLEAR(sne)
XVFCMP_MN_FUNC_DECLEAR(sor)
XVFCMP_MN_FUNC_DECLEAR(sune)

void xvbitsel_v(const XVReg &xd, const XVReg &xj, const XVReg &xk, const XVReg &xa);

void xvshuf_b(const XVReg &xd, const XVReg &xj, const XVReg &xk, const XVReg &xa);

void vld(const VReg &vd, const XReg &rj, int32_t si12);
void vst(const VReg &vd, const XReg &rj, int32_t si12);
void xvld(const XVReg &xd, const XReg &rj, int32_t si12);
void xvst(const XVReg &xd, const XReg &rj, int32_t si12);

void xvldrepl_b(const XVReg &xd, const XReg &rj, int32_t si12);
void xvldrepl_h(const XVReg &xd, const XReg &rj, int32_t si11);
void xvldrepl_w(const XVReg &xd, const XReg &rj, int32_t si10);
void xvldrepl_d(const XVReg &xd, const XReg &rj, int32_t si9);

void xvstelm_b(const XVReg &xd, const XReg &rj, int32_t si8, uint32_t idx);
void xvstelm_h(const XVReg &xd, const XReg &rj, int32_t si8, uint32_t idx);
void xvstelm_w(const XVReg &xd, const XReg &rj, int32_t si8, uint32_t idx);
void xvstelm_d(const XVReg &xd, const XReg &rj, int32_t si8, uint32_t idx);

void vldx(const VReg &vd, const XReg &rj, const XReg &rk);
void vstx(const VReg &vd, const XReg &rj, const XReg &rk);
void xvldx(const XVReg &xd, const XReg &rj, const XReg &rk);
void xvstx(const XVReg &xd, const XReg &rj, const XReg &rk);

void xvseq_b(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvseq_h(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvseq_w(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvseq_d(const XVReg &xd, const XVReg &xj, const XVReg &xk);

void xvsle_b(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvsle_h(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvsle_w(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvsle_d(const XVReg &xd, const XVReg &xj, const XVReg &xk);

void xvsle_bu(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvsle_hu(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvsle_wu(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvsle_du(const XVReg &xd, const XVReg &xj, const XVReg &xk);

void xvslt_b(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvslt_h(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvslt_w(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvslt_d(const XVReg &xd, const XVReg &xj, const XVReg &xk);

void xvslt_bu(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvslt_hu(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvslt_wu(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvslt_du(const XVReg &xd, const XVReg &xj, const XVReg &xk);

void xvadd_b(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvadd_h(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvadd_w(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvadd_d(const XVReg &xd, const XVReg &xj, const XVReg &xk);


void xvsub_b(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvsub_h(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvsub_w(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvsub_d(const XVReg &xd, const XVReg &xj, const XVReg &xk);

void xvaddwev_h_b(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvaddwev_w_h(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvaddwev_d_w(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvaddwev_q_d(const XVReg &xd, const XVReg &xj, const XVReg &xk);

void xvsubwev_h_b(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvsubwev_w_h(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvsubwev_d_w(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvsubwev_q_d(const XVReg &xd, const XVReg &xj, const XVReg &xk);

void xvaddwod_h_b(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvaddwod_w_h(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvaddwod_d_w(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvaddwod_q_d(const XVReg &xd, const XVReg &xj, const XVReg &xk);

void xvsubwod_h_b(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvsubwod_w_h(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvsubwod_d_w(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvsubwod_q_d(const XVReg &xd, const XVReg &xj, const XVReg &xk);

void xvaddwev_h_bu(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvaddwev_w_hu(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvaddwev_d_wu(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvaddwev_q_du(const XVReg &xd, const XVReg &xj, const XVReg &xk);

void xvsubwev_h_bu(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvsubwev_w_hu(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvsubwev_d_wu(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvsubwev_q_du(const XVReg &xd, const XVReg &xj, const XVReg &xk);

void xvaddwod_h_bu(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvaddwod_w_hu(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvaddwod_d_wu(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvaddwod_q_du(const XVReg &xd, const XVReg &xj, const XVReg &xk);

void xvsubwod_h_bu(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvsubwod_w_hu(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvsubwod_d_wu(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvsubwod_q_du(const XVReg &xd, const XVReg &xj, const XVReg &xk);

void xvaddwev_h_bu_b(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvaddwev_w_hu_h(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvaddwev_d_wu_w(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvaddwev_q_du_d(const XVReg &xd, const XVReg &xj, const XVReg &xk);

void xvaddwod_h_bu_b(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvaddwod_w_hu_h(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvaddwod_d_wu_w(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvaddwod_q_du_d(const XVReg &xd, const XVReg &xj, const XVReg &xk);

void xvsadd_b(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvsadd_h(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvsadd_w(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvsadd_d(const XVReg &xd, const XVReg &xj, const XVReg &xk);

void xvssub_b(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvssub_h(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvssub_w(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvssub_d(const XVReg &xd, const XVReg &xj, const XVReg &xk);

void xvsadd_bu(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvsadd_hu(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvsadd_wu(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvsadd_du(const XVReg &xd, const XVReg &xj, const XVReg &xk);

void xvssub_bu(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvssub_hu(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvssub_wu(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvssub_du(const XVReg &xd, const XVReg &xj, const XVReg &xk);

void xvhaddw_h_b(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvhaddw_w_h(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvhaddw_d_w(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvhaddw_q_d(const XVReg &xd, const XVReg &xj, const XVReg &xk);

void xvhsubw_h_b(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvhsubw_w_h(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvhsubw_d_w(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvhsubw_q_d(const XVReg &xd, const XVReg &xj, const XVReg &xk);

void xvhaddw_hu_bu(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvhaddw_wu_hu(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvhaddw_du_wu(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvhaddw_qu_du(const XVReg &xd, const XVReg &xj, const XVReg &xk);

void xvhsubw_hu_bu(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvhsubw_wu_hu(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvhsubw_du_wu(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvhsubw_qu_du(const XVReg &xd, const XVReg &xj, const XVReg &xk);

void xvadda_b(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvadda_h(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvadda_w(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvadda_d(const XVReg &xd, const XVReg &xj, const XVReg &xk);

void xvabsd_b(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvabsd_h(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvabsd_w(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvabsd_d(const XVReg &xd, const XVReg &xj, const XVReg &xk);

void xvabsd_bu(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvabsd_hu(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvabsd_wu(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvabsd_du(const XVReg &xd, const XVReg &xj, const XVReg &xk);

void xvavg_b(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvavg_h(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvavg_w(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvavg_d(const XVReg &xd, const XVReg &xj, const XVReg &xk);

void xvavg_bu(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvavg_hu(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvavg_wu(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvavg_du(const XVReg &xd, const XVReg &xj, const XVReg &xk);

void xvavgr_b(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvavgr_h(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvavgr_w(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvavgr_d(const XVReg &xd, const XVReg &xj, const XVReg &xk);

void xvavgr_bu(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvavgr_hu(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvavgr_wu(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvavgr_du(const XVReg &xd, const XVReg &xj, const XVReg &xk);

void xvmax_b(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvmax_h(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvmax_w(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvmax_d(const XVReg &xd, const XVReg &xj, const XVReg &xk);

void xvmin_b(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvmin_h(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvmin_w(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvmin_d(const XVReg &xd, const XVReg &xj, const XVReg &xk);

void xvmax_bu(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvmax_hu(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvmax_wu(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvmax_du(const XVReg &xd, const XVReg &xj, const XVReg &xk);

void xvmin_bu(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvmin_hu(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvmin_wu(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvmin_du(const XVReg &xd, const XVReg &xj, const XVReg &xk);

void xvmul_b(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvmul_h(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvmul_w(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvmul_d(const XVReg &xd, const XVReg &xj, const XVReg &xk);

void xvmuh_b(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvmuh_h(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvmuh_w(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvmuh_d(const XVReg &xd, const XVReg &xj, const XVReg &xk);

void xvmuh_bu(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvmuh_hu(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvmuh_wu(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvmuh_du(const XVReg &xd, const XVReg &xj, const XVReg &xk);

void xvmulwev_h_b(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvmulwev_w_h(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvmulwev_d_w(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvmulwev_q_d(const XVReg &xd, const XVReg &xj, const XVReg &xk);

void xvmulwod_h_b(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvmulwod_w_h(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvmulwod_d_w(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvmulwod_q_d(const XVReg &xd, const XVReg &xj, const XVReg &xk);

void xvmulwev_h_bu(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvmulwev_w_hu(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvmulwev_d_wu(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvmulwev_q_du(const XVReg &xd, const XVReg &xj, const XVReg &xk);

void xvmulwod_h_bu(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvmulwod_w_hu(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvmulwod_d_wu(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvmulwod_q_du(const XVReg &xd, const XVReg &xj, const XVReg &xk);

void xvmulwev_h_bu_b(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvmulwev_w_hu_h(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvmulwev_d_wu_w(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvmulwev_q_du_d(const XVReg &xd, const XVReg &xj, const XVReg &xk);

void xvmulwod_h_bu_b(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvmulwod_w_hu_h(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvmulwod_d_wu_w(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvmulwod_q_du_d(const XVReg &xd, const XVReg &xj, const XVReg &xk);

void xvmadd_b(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvmadd_h(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvmadd_w(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvmadd_d(const XVReg &xd, const XVReg &xj, const XVReg &xk);

void xvmsub_b(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvmsub_h(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvmsub_w(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvmsub_d(const XVReg &xd, const XVReg &xj, const XVReg &xk);

void xvmaddwev_h_b(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvmaddwev_w_h(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvmaddwev_d_w(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvmaddwev_q_d(const XVReg &xd, const XVReg &xj, const XVReg &xk);

void xvmaddwod_h_b(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvmaddwod_w_h(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvmaddwod_d_w(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvmaddwod_q_d(const XVReg &xd, const XVReg &xj, const XVReg &xk);

void xvmaddwev_h_bu(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvmaddwev_w_hu(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvmaddwev_d_wu(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvmaddwev_q_du(const XVReg &xd, const XVReg &xj, const XVReg &xk);

void xvmaddwod_h_bu(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvmaddwod_w_hu(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvmaddwod_d_wu(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvmaddwod_q_du(const XVReg &xd, const XVReg &xj, const XVReg &xk);

void xvmaddwev_h_bu_b(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvmaddwev_w_hu_h(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvmaddwev_d_wu_w(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvmaddwev_q_du_d(const XVReg &xd, const XVReg &xj, const XVReg &xk);

void xvmaddwod_h_bu_b(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvmaddwod_w_hu_h(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvmaddwod_d_wu_w(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvmaddwod_q_du_d(const XVReg &xd, const XVReg &xj, const XVReg &xk);

void xvdiv_b(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvdiv_h(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvdiv_w(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvdiv_d(const XVReg &xd, const XVReg &xj, const XVReg &xk);

void xvmod_b(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvmod_h(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvmod_w(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvmod_d(const XVReg &xd, const XVReg &xj, const XVReg &xk);

void xvdiv_bu(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvdiv_hu(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvdiv_wu(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvdiv_du(const XVReg &xd, const XVReg &xj, const XVReg &xk);

void xvmod_bu(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvmod_hu(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvmod_wu(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvmod_du(const XVReg &xd, const XVReg &xj, const XVReg &xk);

void xvsll_b(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvsll_h(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvsll_w(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvsll_d(const XVReg &xd, const XVReg &xj, const XVReg &xk);

void xvsrl_b(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvsrl_h(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvsrl_w(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvsrl_d(const XVReg &xd, const XVReg &xj, const XVReg &xk);

void xvsra_b(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvsra_h(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvsra_w(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvsra_d(const XVReg &xd, const XVReg &xj, const XVReg &xk);

void xvrotr_b(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvrotr_h(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvrotr_w(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvrotr_d(const XVReg &xd, const XVReg &xj, const XVReg &xk);

void xvsrlr_b(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvsrlr_h(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvsrlr_w(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvsrlr_d(const XVReg &xd, const XVReg &xj, const XVReg &xk);

void xvsrar_b(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvsrar_h(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvsrar_w(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvsrar_d(const XVReg &xd, const XVReg &xj, const XVReg &xk);

void xvsrln_b_h(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvsrln_h_w(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvsrln_w_d(const XVReg &xd, const XVReg &xj, const XVReg &xk);

void xvsran_b_h(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvsran_h_w(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvsran_w_d(const XVReg &xd, const XVReg &xj, const XVReg &xk);

void xvsrlrn_b_h(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvsrlrn_h_w(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvsrlrn_w_d(const XVReg &xd, const XVReg &xj, const XVReg &xk);

void xvsrarn_b_h(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvsrarn_h_w(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvsrarn_w_d(const XVReg &xd, const XVReg &xj, const XVReg &xk);

void xvssrln_b_h(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvssrln_h_w(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvssrln_w_d(const XVReg &xd, const XVReg &xj, const XVReg &xk);

void xvssran_b_h(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvssran_h_w(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvssran_w_d(const XVReg &xd, const XVReg &xj, const XVReg &xk);

void xvssrlrn_b_h(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvssrlrn_h_w(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvssrlrn_w_d(const XVReg &xd, const XVReg &xj, const XVReg &xk);

void xvssrarn_b_h(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvssrarn_h_w(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvssrarn_w_d(const XVReg &xd, const XVReg &xj, const XVReg &xk);

void xvssrln_bu_h(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvssrln_hu_w(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvssrln_wu_d(const XVReg &xd, const XVReg &xj, const XVReg &xk);

void xvssran_bu_h(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvssran_hu_w(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvssran_wu_d(const XVReg &xd, const XVReg &xj, const XVReg &xk);

void xvssrlrn_bu_h(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvssrlrn_hu_w(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvssrlrn_wu_d(const XVReg &xd, const XVReg &xj, const XVReg &xk);

void xvssrarn_bu_h(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvssrarn_hu_w(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvssrarn_wu_d(const XVReg &xd, const XVReg &xj, const XVReg &xk);

void xvbitclr_b(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvbitclr_h(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvbitclr_w(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvbitclr_d(const XVReg &xd, const XVReg &xj, const XVReg &xk);

void xvbitset_b(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvbitset_h(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvbitset_w(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvbitset_d(const XVReg &xd, const XVReg &xj, const XVReg &xk);

void xvbitrev_b(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvbitrev_h(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvbitrev_w(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvbitrev_d(const XVReg &xd, const XVReg &xj, const XVReg &xk);

void xvpackev_b(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvpackev_h(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvpackev_w(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvpackev_d(const XVReg &xd, const XVReg &xj, const XVReg &xk);

void xvpackod_b(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvpackod_h(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvpackod_w(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvpackod_d(const XVReg &xd, const XVReg &xj, const XVReg &xk);

void xvilvl_b(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvilvl_h(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvilvl_w(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvilvl_d(const XVReg &xd, const XVReg &xj, const XVReg &xk);

void xvilvh_b(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvilvh_h(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvilvh_w(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvilvh_d(const XVReg &xd, const XVReg &xj, const XVReg &xk);

void xvpickev_b(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvpickev_h(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvpickev_w(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvpickev_d(const XVReg &xd, const XVReg &xj, const XVReg &xk);

void xvpickod_b(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvpickod_h(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvpickod_w(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvpickod_d(const XVReg &xd, const XVReg &xj, const XVReg &xk);

void xvreplve_b(const XVReg &xd, const XVReg &xj, const XReg &rk);
void xvreplve_h(const XVReg &xd, const XVReg &xj, const XReg &rk);
void xvreplve_w(const XVReg &xd, const XVReg &xj, const XReg &rk);
void xvreplve_d(const XVReg &xd, const XVReg &xj, const XReg &rk);

void xvand_v(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvor_v(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvxor_v(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvnor_v(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvandn_v(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvorn_v(const XVReg &xd, const XVReg &xj, const XVReg &xk);

void xvfrstp_b(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvfrstp_h(const XVReg &xd, const XVReg &xj, const XVReg &xk);

void xvadd_q(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvsub_q(const XVReg &xd, const XVReg &xj, const XVReg &xk);

void xvsigncov_b(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvsigncov_h(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvsigncov_w(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvsigncov_d(const XVReg &xd, const XVReg &xj, const XVReg &xk);

void xvfadd_s(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvfadd_d(const XVReg &xd, const XVReg &xj, const XVReg &xk);

void xvfsub_s(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvfsub_d(const XVReg &xd, const XVReg &xj, const XVReg &xk);

void xvfmul_s(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvfmul_d(const XVReg &xd, const XVReg &xj, const XVReg &xk);

void xvfdiv_s(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvfdiv_d(const XVReg &xd, const XVReg &xj, const XVReg &xk);

void xvfmax_s(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvfmax_d(const XVReg &xd, const XVReg &xj, const XVReg &xk);

void xvfmin_s(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvfmin_d(const XVReg &xd, const XVReg &xj, const XVReg &xk);

void xvfmaxa_s(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvfmaxa_d(const XVReg &xd, const XVReg &xj, const XVReg &xk);

void xvfmina_s(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvfmina_d(const XVReg &xd, const XVReg &xj, const XVReg &xk);

void xvfscaleb_s(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvfscaleb_d(const XVReg &xd, const XVReg &xj, const XVReg &xk);

void xvfcvt_h_s(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvfcvt_s_d(const XVReg &xd, const XVReg &xj, const XVReg &xk);

void xvffint_s_l(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvftint_w_d(const XVReg &xd, const XVReg &xj, const XVReg &xk);

void xvftintrm_w_d(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvftintrp_w_d(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvftintrz_w_d(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvftintrne_w_d(const XVReg &xd, const XVReg &xj, const XVReg &xk);

void xvshuf_h(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvshuf_w(const XVReg &xd, const XVReg &xj, const XVReg &xk);
void xvshuf_d(const XVReg &xd, const XVReg &xj, const XVReg &xk);

void xvperm_w(const XVReg &xd, const XVReg &xj, const XVReg &xk);

void xvseqi_b(const XVReg &xd, const XVReg &xj, int32_t si5);
void xvseqi_h(const XVReg &xd, const XVReg &xj, int32_t si5);
void xvseqi_w(const XVReg &xd, const XVReg &xj, int32_t si5);
void xvseqi_d(const XVReg &xd, const XVReg &xj, int32_t si5);

void xvslei_b(const XVReg &xd, const XVReg &xj, int32_t si5);
void xvslei_h(const XVReg &xd, const XVReg &xj, int32_t si5);
void xvslei_w(const XVReg &xd, const XVReg &xj, int32_t si5);
void xvslei_d(const XVReg &xd, const XVReg &xj, int32_t si5);

void xvslei_bu(const XVReg &xd, const XVReg &xj, uint32_t ui5);
void xvslei_hu(const XVReg &xd, const XVReg &xj, uint32_t ui5);
void xvslei_wu(const XVReg &xd, const XVReg &xj, uint32_t ui5);
void xvslei_du(const XVReg &xd, const XVReg &xj, uint32_t ui5);

void xvslti_b(const XVReg &xd, const XVReg &xj, int32_t si5);
void xvslti_h(const XVReg &xd, const XVReg &xj, int32_t si5);
void xvslti_w(const XVReg &xd, const XVReg &xj, int32_t si5);
void xvslti_d(const XVReg &xd, const XVReg &xj, int32_t si5);

void xvslti_bu(const XVReg &xd, const XVReg &xj, uint32_t ui5);
void xvslti_hu(const XVReg &xd, const XVReg &xj, uint32_t ui5);
void xvslti_wu(const XVReg &xd, const XVReg &xj, uint32_t ui5);
void xvslti_du(const XVReg &xd, const XVReg &xj, uint32_t ui5);

void xvaddi_bu(const XVReg &xd, const XVReg &xj, uint32_t ui5);
void xvaddi_hu(const XVReg &xd, const XVReg &xj, uint32_t ui5);
void xvaddi_wu(const XVReg &xd, const XVReg &xj, uint32_t ui5);
void xvaddi_du(const XVReg &xd, const XVReg &xj, uint32_t ui5);

void xvsubi_bu(const XVReg &xd, const XVReg &xj, uint32_t ui5);
void xvsubi_hu(const XVReg &xd, const XVReg &xj, uint32_t ui5);
void xvsubi_wu(const XVReg &xd, const XVReg &xj, uint32_t ui5);
void xvsubi_du(const XVReg &xd, const XVReg &xj, uint32_t ui5);

void xvbsll_v(const XVReg &xd, const XVReg &xj, uint32_t ui5);
void xvbsrl_v(const XVReg &xd, const XVReg &xj, uint32_t ui5);

void xvmaxi_b(const XVReg &xd, const XVReg &xj, int32_t si5);
void xvmaxi_h(const XVReg &xd, const XVReg &xj, int32_t si5);
void xvmaxi_w(const XVReg &xd, const XVReg &xj, int32_t si5);
void xvmaxi_d(const XVReg &xd, const XVReg &xj, int32_t si5);

void xvmini_b(const XVReg &xd, const XVReg &xj, int32_t si5);
void xvmini_h(const XVReg &xd, const XVReg &xj, int32_t si5);
void xvmini_w(const XVReg &xd, const XVReg &xj, int32_t si5);
void xvmini_d(const XVReg &xd, const XVReg &xj, int32_t si5);

void xvmaxi_bu(const XVReg &xd, const XVReg &xj, uint32_t ui5);
void xvmaxi_hu(const XVReg &xd, const XVReg &xj, uint32_t ui5);
void xvmaxi_wu(const XVReg &xd, const XVReg &xj, uint32_t ui5);
void xvmaxi_du(const XVReg &xd, const XVReg &xj, uint32_t ui5);

void xvmini_bu(const XVReg &xd, const XVReg &xj, uint32_t ui5);
void xvmini_hu(const XVReg &xd, const XVReg &xj, uint32_t ui5);
void xvmini_wu(const XVReg &xd, const XVReg &xj, uint32_t ui5);
void xvmini_du(const XVReg &xd, const XVReg &xj, uint32_t ui5);

void xvfrstpi_b(const XVReg &xd, const XVReg &xj, uint32_t ui5);
void xvfrstpi_h(const XVReg &xd, const XVReg &xj, uint32_t ui5);

void xvmepatmsk_v(const XVReg &xd, int32_t mode, uint32_t ui5);

void xvclo_b(const XVReg &xd, const XVReg &xj);
void xvclo_h(const XVReg &xd, const XVReg &xj);
void xvclo_w(const XVReg &xd, const XVReg &xj);
void xvclo_d(const XVReg &xd, const XVReg &xj);

void xvclz_b(const XVReg &xd, const XVReg &xj);
void xvclz_h(const XVReg &xd, const XVReg &xj);
void xvclz_w(const XVReg &xd, const XVReg &xj);
void xvclz_d(const XVReg &xd, const XVReg &xj);

void xvpcnt_b(const XVReg &xd, const XVReg &xj);
void xvpcnt_h(const XVReg &xd, const XVReg &xj);
void xvpcnt_w(const XVReg &xd, const XVReg &xj);
void xvpcnt_d(const XVReg &xd, const XVReg &xj);

void xvneg_b(const XVReg &xd, const XVReg &xj);
void xvneg_h(const XVReg &xd, const XVReg &xj);
void xvneg_w(const XVReg &xd, const XVReg &xj);
void xvneg_d(const XVReg &xd, const XVReg &xj);

void xvmskltz_b(const XVReg &xd, const XVReg &xj);
void xvmskltz_h(const XVReg &xd, const XVReg &xj);
void xvmskltz_w(const XVReg &xd, const XVReg &xj);
void xvmskltz_d(const XVReg &xd, const XVReg &xj);

void xvmskgez_b(const XVReg &xd, const XVReg &xj);

void xvmsknz_b(const XVReg &xd, const XVReg &xj);

void xvseteqz_v(uint32_t cd, const XVReg &xj);
void xvsetnez_v(uint32_t cd, const XVReg &xj);

void xvsetanyeqz_b(uint32_t cd, const XVReg &xj);
void xvsetanyeqz_h(uint32_t cd, const XVReg &xj);
void xvsetanyeqz_w(uint32_t cd, const XVReg &xj);
void xvsetanyeqz_d(uint32_t cd, const XVReg &xj);

void xvsetallnez_b(uint32_t cd, const XVReg &xj);
void xvsetallnez_h(uint32_t cd, const XVReg &xj);
void xvsetallnez_w(uint32_t cd, const XVReg &xj);
void xvsetallnez_d(uint32_t cd, const XVReg &xj);

void xvflogb_s(const XVReg &xd, const XVReg &xj);
void xvflogb_d(const XVReg &xd, const XVReg &xj);

void xvfclass_s(const XVReg &xd, const XVReg &xj);
void xvfclass_d(const XVReg &xd, const XVReg &xj);

void xvfsqrt_s(const XVReg &xd, const XVReg &xj);
void xvfsqrt_d(const XVReg &xd, const XVReg &xj);

void xvfrecip_s(const XVReg &xd, const XVReg &xj);
void xvfrecip_d(const XVReg &xd, const XVReg &xj);

void xvfrsqrt_s(const XVReg &xd, const XVReg &xj);
void xvfrsqrt_d(const XVReg &xd, const XVReg &xj);

void xvfrint_s(const XVReg &xd, const XVReg &xj);
void xvfrint_d(const XVReg &xd, const XVReg &xj);

void xvfrintrm_s(const XVReg &xd, const XVReg &xj);
void xvfrintrm_d(const XVReg &xd, const XVReg &xj);

void xvfrintrp_s(const XVReg &xd, const XVReg &xj);
void xvfrintrp_d(const XVReg &xd, const XVReg &xj);

void xvfrintrz_s(const XVReg &xd, const XVReg &xj);
void xvfrintrz_d(const XVReg &xd, const XVReg &xj);

void xvfrintrne_s(const XVReg &xd, const XVReg &xj);
void xvfrintrne_d(const XVReg &xd, const XVReg &xj);

void xvfcvtl_s_h(const XVReg &xd, const XVReg &xj);
void xvfcvth_s_h(const XVReg &xd, const XVReg &xj);

void xvfcvtl_d_s(const XVReg &xd, const XVReg &xj);
void xvfcvth_d_s(const XVReg &xd, const XVReg &xj);

void xvffint_s_w(const XVReg &xd, const XVReg &xj);
void xvffint_s_wu(const XVReg &xd, const XVReg &xj);

void xvffint_d_l(const XVReg &xd, const XVReg &xj);
void xvffint_d_lu(const XVReg &xd, const XVReg &xj);

void xvffintl_d_w(const XVReg &xd, const XVReg &xj);
void xvffinth_d_w(const XVReg &xd, const XVReg &xj);

void xvftint_w_s(const XVReg &xd, const XVReg &xj);
void xvftint_l_d(const XVReg &xd, const XVReg &xj);

void xvftintrm_w_s(const XVReg &xd, const XVReg &xj);
void xvftintrm_l_d(const XVReg &xd, const XVReg &xj);

void xvftintrp_w_s(const XVReg &xd, const XVReg &xj);
void xvftintrp_l_d(const XVReg &xd, const XVReg &xj);

void xvftintrz_w_s(const XVReg &xd, const XVReg &xj);
void xvftintrz_l_d(const XVReg &xd, const XVReg &xj);

void xvftintrne_w_s(const XVReg &xd, const XVReg &xj);
void xvftintrne_l_d(const XVReg &xd, const XVReg &xj);

void xvftint_wu_s(const XVReg &xd, const XVReg &xj);
void xvftint_lu_d(const XVReg &xd, const XVReg &xj);

void xvftintrz_wu_s(const XVReg &xd, const XVReg &xj);
void xvftintrz_lu_d(const XVReg &xd, const XVReg &xj);

void xvftintl_l_s(const XVReg &xd, const XVReg &xj);
void xvftinth_l_s(const XVReg &xd, const XVReg &xj);

void xvftintrml_l_s(const XVReg &xd, const XVReg &xj);
void xvftintrmh_l_s(const XVReg &xd, const XVReg &xj);

void xvftintrpl_l_s(const XVReg &xd, const XVReg &xj);
void xvftintrph_l_s(const XVReg &xd, const XVReg &xj);

void xvftintrzl_l_s(const XVReg &xd, const XVReg &xj);
void xvftintrzh_l_s(const XVReg &xd, const XVReg &xj);

void xvftintrnel_l_s(const XVReg &xd, const XVReg &xj);
void xvftintrneh_l_s(const XVReg &xd, const XVReg &xj);

void xvexth_h_b(const XVReg &xd, const XVReg &xj);
void xvexth_w_h(const XVReg &xd, const XVReg &xj);
void xvexth_d_w(const XVReg &xd, const XVReg &xj);
void xvexth_q_d(const XVReg &xd, const XVReg &xj);

void xvexth_hu_bu(const XVReg &xd, const XVReg &xj);
void xvexth_wu_hu(const XVReg &xd, const XVReg &xj);
void xvexth_du_wu(const XVReg &xd, const XVReg &xj);
void xvexth_qu_du(const XVReg &xd, const XVReg &xj);

void vext2xv_h_b(const XVReg &xd, const XVReg &xj);
void vext2xv_w_b(const XVReg &xd, const XVReg &xj);
void vext2xv_d_b(const XVReg &xd, const XVReg &xj);
void vext2xv_w_h(const XVReg &xd, const XVReg &xj);
void vext2xv_d_h(const XVReg &xd, const XVReg &xj);
void vext2xv_d_w(const XVReg &xd, const XVReg &xj);
void vext2xv_hu_bu(const XVReg &xd, const XVReg &xj);
void vext2xv_wu_bu(const XVReg &xd, const XVReg &xj);
void vext2xv_du_bu(const XVReg &xd, const XVReg &xj);
void vext2xv_wu_hu(const XVReg &xd, const XVReg &xj);
void vext2xv_du_hu(const XVReg &xd, const XVReg &xj);
void vext2xv_du_wu(const XVReg &xd, const XVReg &xj);

void xvreplgr2vr_b(const XVReg &xd, const XReg &rj);
void xvreplgr2vr_h(const XVReg &xd, const XReg &rj);
void xvreplgr2vr_w(const XVReg &xd, const XReg &rj);
void xvreplgr2vr_d(const XVReg &xd, const XReg &rj);

void xvhseli_d(const XVReg &xd, const XVReg &xj, uint32_t ui5);

void xvrotri_b(const XVReg &xd, const XVReg &xj, uint32_t imm);
void xvrotri_h(const XVReg &xd, const XVReg &xj, uint32_t imm);
void xvrotri_w(const XVReg &xd, const XVReg &xj, uint32_t imm);
void xvrotri_d(const XVReg &xd, const XVReg &xj, uint32_t imm);

void xvsrlri_b(const XVReg &xd, const XVReg &xj, uint32_t imm);
void xvsrlri_h(const XVReg &xd, const XVReg &xj, uint32_t imm);
void xvsrlri_w(const XVReg &xd, const XVReg &xj, uint32_t imm);
void xvsrlri_d(const XVReg &xd, const XVReg &xj, uint32_t imm);

void xvsrari_b(const XVReg &xd, const XVReg &xj, uint32_t imm);
void xvsrari_h(const XVReg &xd, const XVReg &xj, uint32_t imm);
void xvsrari_w(const XVReg &xd, const XVReg &xj, uint32_t imm);
void xvsrari_d(const XVReg &xd, const XVReg &xj, uint32_t imm);

void vinsgr2vr_b(const VReg &vd, const XReg &rj, uint32_t ui4);
void vinsgr2vr_h(const VReg &vd, const XReg &rj, uint32_t ui3);
void vinsgr2vr_w(const VReg &vd, const XReg &rj, uint32_t ui2);
void vinsgr2vr_d(const VReg &vd, const XReg &rj, uint32_t ui1);

void xvinsgr2vr_w(const XVReg &xd, const XReg &rj, uint32_t imm);
void xvinsgr2vr_d(const XVReg &xd, const XReg &rj, uint32_t imm);

void vpickve2gr_b(const XReg &rd, const VReg &vj, uint32_t ui4);
void vpickve2gr_h(const XReg &rd, const VReg &vj, uint32_t ui3);
void vpickve2gr_w(const XReg &rd, const VReg &vj, uint32_t ui2);
void vpickve2gr_d(const XReg &rd, const VReg &vj, uint32_t ui1);
void vpickve2gr_bu(const XReg &rd, const VReg &vj, uint32_t ui4);
void vpickve2gr_hu(const XReg &rd, const VReg &vj, uint32_t ui3);
void vpickve2gr_wu(const XReg &rd, const VReg &vj, uint32_t ui2);
void vpickve2gr_du(const XReg &rd, const VReg &vj, uint32_t ui1);

void xvpickve2gr_w(const XReg &rd, const XVReg &xj, uint32_t imm);
void xvpickve2gr_d(const XReg &rd, const XVReg &xj, uint32_t imm);

void xvpickve2gr_wu(const XReg &rd, const XVReg &xj, uint32_t imm);
void xvpickve2gr_du(const XReg &rd, const XVReg &xj, uint32_t imm);

void vreplvei_b(const VReg &vd, const VReg &vj, uint32_t ui4);
void vreplvei_h(const VReg &vd, const VReg &vj, uint32_t ui3);
void vreplvei_w(const VReg &vd, const VReg &vj, uint32_t ui2);
void vreplvei_d(const VReg &vd, const VReg &vj, uint32_t ui1);

void xvrepl128vei_b(const XVReg &xd, const XVReg &xj, uint32_t imm);
void xvrepl128vei_h(const XVReg &xd, const XVReg &xj, uint32_t imm);
void xvrepl128vei_w(const XVReg &xd, const XVReg &xj, uint32_t imm);
void xvrepl128vei_d(const XVReg &xd, const XVReg &xj, uint32_t imm);

void xvinsve0_w(const XVReg &xd, const XVReg &xj, uint32_t imm);
void xvinsve0_d(const XVReg &xd, const XVReg &xj, uint32_t imm);

void xvpickve_w(const XVReg &xd, const XVReg &xj, uint32_t imm);
void xvpickve_d(const XVReg &xd, const XVReg &xj, uint32_t imm);

void xvreplve0_b(const XVReg &xd, const XVReg &xj);
void xvreplve0_h(const XVReg &xd, const XVReg &xj);
void xvreplve0_w(const XVReg &xd, const XVReg &xj);
void xvreplve0_d(const XVReg &xd, const XVReg &xj);
void xvreplve0_q(const XVReg &xd, const XVReg &xj);

void xvsllwil_h_b(const XVReg &xd, const XVReg &xj, uint32_t imm);
void xvsllwil_w_h(const XVReg &xd, const XVReg &xj, uint32_t imm);
void xvsllwil_d_w(const XVReg &xd, const XVReg &xj, uint32_t imm);

void xvextl_q_d(const XVReg &xd, const XVReg &xj);

void xvsllwil_hu_bu(const XVReg &xd, const XVReg &xj, uint32_t imm);
void xvsllwil_wu_hu(const XVReg &xd, const XVReg &xj, uint32_t imm);
void xvsllwil_du_wu(const XVReg &xd, const XVReg &xj, uint32_t imm);

void xvextl_qu_du(const XVReg &xd, const XVReg &xj);

void xvbitclri_b(const XVReg &xd, const XVReg &xj, uint32_t imm);
void xvbitclri_h(const XVReg &xd, const XVReg &xj, uint32_t imm);
void xvbitclri_w(const XVReg &xd, const XVReg &xj, uint32_t imm);
void xvbitclri_d(const XVReg &xd, const XVReg &xj, uint32_t imm);

void xvbitseti_b(const XVReg &xd, const XVReg &xj, uint32_t imm);
void xvbitseti_h(const XVReg &xd, const XVReg &xj, uint32_t imm);
void xvbitseti_w(const XVReg &xd, const XVReg &xj, uint32_t imm);
void xvbitseti_d(const XVReg &xd, const XVReg &xj, uint32_t imm);

void xvbitrevi_b(const XVReg &xd, const XVReg &xj, uint32_t imm);
void xvbitrevi_h(const XVReg &xd, const XVReg &xj, uint32_t imm);
void xvbitrevi_w(const XVReg &xd, const XVReg &xj, uint32_t imm);
void xvbitrevi_d(const XVReg &xd, const XVReg &xj, uint32_t imm);

void xvsat_b(const XVReg &xd, const XVReg &xj, uint32_t imm);
void xvsat_h(const XVReg &xd, const XVReg &xj, uint32_t imm);
void xvsat_w(const XVReg &xd, const XVReg &xj, uint32_t imm);
void xvsat_d(const XVReg &xd, const XVReg &xj, uint32_t imm);

void xvsat_bu(const XVReg &xd, const XVReg &xj, uint32_t imm);
void xvsat_hu(const XVReg &xd, const XVReg &xj, uint32_t imm);
void xvsat_wu(const XVReg &xd, const XVReg &xj, uint32_t imm);
void xvsat_du(const XVReg &xd, const XVReg &xj, uint32_t imm);

void xvslli_b(const XVReg &xd, const XVReg &xj, uint32_t imm);
void xvslli_h(const XVReg &xd, const XVReg &xj, uint32_t imm);
void xvslli_w(const XVReg &xd, const XVReg &xj, uint32_t imm);
void xvslli_d(const XVReg &xd, const XVReg &xj, uint32_t imm);

void xvsrli_b(const XVReg &xd, const XVReg &xj, uint32_t imm);
void xvsrli_h(const XVReg &xd, const XVReg &xj, uint32_t imm);
void xvsrli_w(const XVReg &xd, const XVReg &xj, uint32_t imm);
void xvsrli_d(const XVReg &xd, const XVReg &xj, uint32_t imm);

void xvsrai_b(const XVReg &xd, const XVReg &xj, uint32_t imm);
void xvsrai_h(const XVReg &xd, const XVReg &xj, uint32_t imm);
void xvsrai_w(const XVReg &xd, const XVReg &xj, uint32_t imm);
void xvsrai_d(const XVReg &xd, const XVReg &xj, uint32_t imm);

void xvsrlni_b_h(const XVReg &xd, const XVReg &xj, uint32_t imm);
void xvsrlni_h_w(const XVReg &xd, const XVReg &xj, uint32_t imm);
void xvsrlni_w_d(const XVReg &xd, const XVReg &xj, uint32_t imm);
void xvsrlni_d_q(const XVReg &xd, const XVReg &xj, uint32_t imm);

void xvsrlrni_b_h(const XVReg &xd, const XVReg &xj, uint32_t imm);
void xvsrlrni_h_w(const XVReg &xd, const XVReg &xj, uint32_t imm);
void xvsrlrni_w_d(const XVReg &xd, const XVReg &xj, uint32_t imm);
void xvsrlrni_d_q(const XVReg &xd, const XVReg &xj, uint32_t imm);

void xvssrlni_b_h(const XVReg &xd, const XVReg &xj, uint32_t imm);
void xvssrlni_h_w(const XVReg &xd, const XVReg &xj, uint32_t imm);
void xvssrlni_w_d(const XVReg &xd, const XVReg &xj, uint32_t imm);
void xvssrlni_d_q(const XVReg &xd, const XVReg &xj, uint32_t imm);

void xvssrlni_bu_h(const XVReg &xd, const XVReg &xj, uint32_t imm);
void xvssrlni_hu_w(const XVReg &xd, const XVReg &xj, uint32_t imm);
void xvssrlni_wu_d(const XVReg &xd, const XVReg &xj, uint32_t imm);
void xvssrlni_du_q(const XVReg &xd, const XVReg &xj, uint32_t imm);

void xvssrlrni_b_h(const XVReg &xd, const XVReg &xj, uint32_t imm);
void xvssrlrni_h_w(const XVReg &xd, const XVReg &xj, uint32_t imm);
void xvssrlrni_w_d(const XVReg &xd, const XVReg &xj, uint32_t imm);
void xvssrlrni_d_q(const XVReg &xd, const XVReg &xj, uint32_t imm);

void xvssrlrni_bu_h(const XVReg &xd, const XVReg &xj, uint32_t imm);
void xvssrlrni_hu_w(const XVReg &xd, const XVReg &xj, uint32_t imm);
void xvssrlrni_wu_d(const XVReg &xd, const XVReg &xj, uint32_t imm);
void xvssrlrni_du_q(const XVReg &xd, const XVReg &xj, uint32_t imm);

void xvsrani_b_h(const XVReg &xd, const XVReg &xj, uint32_t imm);
void xvsrani_h_w(const XVReg &xd, const XVReg &xj, uint32_t imm);
void xvsrani_w_d(const XVReg &xd, const XVReg &xj, uint32_t imm);
void xvsrani_d_q(const XVReg &xd, const XVReg &xj, uint32_t imm);

void xvsrarni_b_h(const XVReg &xd, const XVReg &xj, uint32_t imm);
void xvsrarni_h_w(const XVReg &xd, const XVReg &xj, uint32_t imm);
void xvsrarni_w_d(const XVReg &xd, const XVReg &xj, uint32_t imm);
void xvsrarni_d_q(const XVReg &xd, const XVReg &xj, uint32_t imm);

void xvssrani_b_h(const XVReg &xd, const XVReg &xj, uint32_t imm);
void xvssrani_h_w(const XVReg &xd, const XVReg &xj, uint32_t imm);
void xvssrani_w_d(const XVReg &xd, const XVReg &xj, uint32_t imm);
void xvssrani_d_q(const XVReg &xd, const XVReg &xj, uint32_t imm);

void xvssrani_bu_h(const XVReg &xd, const XVReg &xj, uint32_t imm);
void xvssrani_hu_w(const XVReg &xd, const XVReg &xj, uint32_t imm);
void xvssrani_wu_d(const XVReg &xd, const XVReg &xj, uint32_t imm);
void xvssrani_du_q(const XVReg &xd, const XVReg &xj, uint32_t imm);

void xvssrarni_b_h(const XVReg &xd, const XVReg &xj, uint32_t imm);
void xvssrarni_h_w(const XVReg &xd, const XVReg &xj, uint32_t imm);
void xvssrarni_w_d(const XVReg &xd, const XVReg &xj, uint32_t imm);
void xvssrarni_d_q(const XVReg &xd, const XVReg &xj, uint32_t imm);

void xvssrarni_bu_h(const XVReg &xd, const XVReg &xj, uint32_t imm);
void xvssrarni_hu_w(const XVReg &xd, const XVReg &xj, uint32_t imm);
void xvssrarni_wu_d(const XVReg &xd, const XVReg &xj, uint32_t imm);
void xvssrarni_du_q(const XVReg &xd, const XVReg &xj, uint32_t imm);

void xvextrins_d(const XVReg &xd, const XVReg &xj, uint32_t imm8);
void xvextrins_w(const XVReg &xd, const XVReg &xj, uint32_t imm8);
void xvextrins_h(const XVReg &xd, const XVReg &xj, uint32_t imm8);
void xvextrins_b(const XVReg &xd, const XVReg &xj, uint32_t imm8);

void xvshuf4i_b(const XVReg &xd, const XVReg &xj, uint32_t imm8);
void xvshuf4i_h(const XVReg &xd, const XVReg &xj, uint32_t imm8);
void xvshuf4i_w(const XVReg &xd, const XVReg &xj, uint32_t imm8);
void xvshuf4i_d(const XVReg &xd, const XVReg &xj, uint32_t imm8);

void xvbitseli_b(const XVReg &xd, const XVReg &xj, uint32_t imm8);
void xvandi_b(const XVReg &xd, const XVReg &xj, uint32_t imm8);
void xvori_b(const XVReg &xd, const XVReg &xj, uint32_t imm8);
void xvxori_b(const XVReg &xd, const XVReg &xj, uint32_t imm8);
void xvnori_b(const XVReg &xd, const XVReg &xj, uint32_t imm8);

void xvldi(const XVReg &xd, int32_t imm13);

void xvpermi_w(const XVReg &xd, const XVReg &xj, uint32_t imm8);
void xvpermi_d(const XVReg &xd, const XVReg &xj, uint32_t imm8);
void xvpermi_q(const XVReg &xd, const XVReg &xj, uint32_t imm8);

/*LASX end*/

/*Base begin*/
                                                                                    // 31~~~~~~~~~~~~~~~15  14～10  9～5  4～0
void add_w(const XReg& rd, const XReg& rj, const XReg& rk);                         // 00000000000100000     rk      rj   rd
void add_d(const XReg& rd, const XReg& rj, const XReg& rk);                         // 00000000000100001     rk      rj   rd
void andi(const XReg& rd, const XReg& rj, int32_t ui12);                            // 0000001101         ui12       rj   rd
void clo_w(const XReg& rd, const XReg& rj);                                         // 0000000000000000000100        rj   rd
void clz_w(const XReg& rd, const XReg& rj);                                         // 0000000000000000000101        rj   rd
void cto_w(const XReg& rd, const XReg& rj);                                         // 0000000000000000000110        rj   rd
void ctz_w(const XReg& rd, const XReg& rj);                                         // 0000000000000000000111        rj   rd
void clo_d(const XReg& rd, const XReg& rj);                                         // 0000000000000000001000        rj   rd
void clz_d(const XReg& rd, const XReg& rj);                                         // 0000000000000000001001        rj   rd
void cto_d(const XReg& rd, const XReg& rj);                                         // 0000000000000000001010        rj   rd
void ctz_d(const XReg& rd, const XReg& rj);                                         // 0000000000000000001011        rj   rd
void revb_2h(const XReg& rd, const XReg& rj);                                       // 0000000000000000001100        rj   rd
void revb_4h(const XReg& rd, const XReg& rj);                                       // 0000000000000000001101        rj   rd
void revb_2w(const XReg& rd, const XReg& rj);                                       // 0000000000000000001110        rj   rd
void revb_d(const XReg& rd, const XReg& rj);                                        // 0000000000000000001111        rj   rd
void revh_2w(const XReg& rd, const XReg& rj);                                       // 0000000000000000010000        rj   rd
void revh_d(const XReg& rd, const XReg& rj);                                        // 0000000000000000010001        rj   rd
void bitrev_4b(const XReg& rd, const XReg& rj);                                     // 0000000000000000010010        rj   rd
void bitrev_8b(const XReg& rd, const XReg& rj);                                     // 0000000000000000010011        rj   rd
void bitrev_w(const XReg& rd, const XReg& rj);                                      // 0000000000000000010100        rj   rd
void bitrev_d(const XReg& rd, const XReg& rj);                                      // 0000000000000000010101        rj   rd
void ext_w_h(const XReg& rd, const XReg& rj);                                       // 0000000000000000010110        rj   rd
void ext_w_b(const XReg& rd, const XReg& rj);                                       // 0000000000000000010111        rj   rd
void rdtimel_w(const XReg& rd, const XReg& rj);                                     // 0000000000000000011000        rj   rd
void rdtimeh_w(const XReg& rd, const XReg& rj);                                     // 0000000000000000011001        rj   rd
void rdtime_d(const XReg& rd, const XReg& rj);                                      // 0000000000000000011010        rj   rd
void cpucfg(const XReg& rd, const XReg& rj);                                        // 0000000000000000011011        rj   rd
void asrtle_d(const XReg& rj, const XReg& rk);                                      // 00000000000000010     rk      rj   00000
void asrtgt_d(const XReg& rj, const XReg& rk);                                      // 00000000000000011     rk      rj   00000
void alsl_w(const XReg& rd, const XReg& rj, const XReg& rk, uint32_t sa2);          // 000000000000010    sa2rk      rj   rd
void alsl_wu(const XReg& rd, const XReg& rj, const XReg& rk, uint32_t sa2);         // 000000000000011    sa2rk      rj   rd
void bytepick_w(const XReg& rd, const XReg& rj, const XReg& rk, uint32_t sa2);      // 000000000000100    sa2rk      rj   rd
void bytepick_d(const XReg& rd, const XReg& rj, const XReg& rk, uint32_t sa3);      // 00000000000011     sa3rk      rj   rd
void sub_w(const XReg& rd, const XReg& rj, const XReg& rk);                         // 00000000000100010     rk      rj   rd
void sub_d(const XReg& rd, const XReg& rj, const XReg& rk);                         // 00000000000100011     rk      rj   rd
void slt(const XReg& rd, const XReg& rj, const XReg& rk);                           // 00000000000100100     rk      rj   rd
void sltu(const XReg& rd, const XReg& rj, const XReg& rk);                          // 00000000000100101     rk      rj   rd
void maskeqz(const XReg& rd, const XReg& rj, const XReg& rk);                       // 00000000000100110     rk      rj   rd
void masknez(const XReg& rd, const XReg& rj, const XReg& rk);                       // 00000000000100111     rk      rj   rd
void nor(const XReg& rd, const XReg& rj, const XReg& rk);                           // 00000000000101000     rk      rj   rd
void and_(const XReg& rd, const XReg& rj, const XReg& rk);                          // 00000000000101001     rk      rj   rd
void or_(const XReg& rd, const XReg& rj, const XReg& rk);                           // 00000000000101010     rk      rj   rd
void xor_(const XReg& rd, const XReg& rj, const XReg& rk);                          // 00000000000101011     rk      rj   rd
void orn(const XReg& rd, const XReg& rj, const XReg& rk);                           // 00000000000101100     rk      rj   rd
void andn(const XReg& rd, const XReg& rj, const XReg& rk);                          // 00000000000101101     rk      rj   rd
void sll_w(const XReg& rd, const XReg& rj, const XReg& rk);                         // 00000000000101110     rk      rj   rd
void srl_w(const XReg& rd, const XReg& rj, const XReg& rk);                         // 00000000000101111     rk      rj   rd
void sra_w(const XReg& rd, const XReg& rj, const XReg& rk);                         // 00000000000110000     rk      rj   rd
void sll_d(const XReg& rd, const XReg& rj, const XReg& rk);                         // 00000000000110001     rk      rj   rd
void srl_d(const XReg& rd, const XReg& rj, const XReg& rk);                         // 00000000000110010     rk      rj   rd
void sra_d(const XReg& rd, const XReg& rj, const XReg& rk);                         // 00000000000110011     rk      rj   rd
void rotr_w(const XReg& rd, const XReg& rj, const XReg& rk);                        // 00000000000110110     rk      rj   rd
void rotr_d(const XReg& rd, const XReg& rj, const XReg& rk);                        // 00000000000110111     rk      rj   rd
void mul_w(const XReg& rd, const XReg& rj, const XReg& rk);                         // 00000000000111000     rk      rj   rd
void mulh_w(const XReg& rd, const XReg& rj, const XReg& rk);                        // 00000000000111001     rk      rj   rd
void mulh_wu(const XReg& rd, const XReg& rj, const XReg& rk);                       // 00000000000111010     rk      rj   rd
void mul_d(const XReg& rd, const XReg& rj, const XReg& rk);                         // 00000000000111011     rk      rj   rd
void mulh_d(const XReg& rd, const XReg& rj, const XReg& rk);                        // 00000000000111100     rk      rj   rd
void mulh_du(const XReg& rd, const XReg& rj, const XReg& rk);                       // 00000000000111101     rk      rj   rd
void mulw_d_w(const XReg& rd, const XReg& rj, const XReg& rk);                      // 00000000000111110     rk      rj   rd
void mulw_d_wu(const XReg& rd, const XReg& rj, const XReg& rk);                     // 00000000000111111     rk      rj   rd
void div_w(const XReg& rd, const XReg& rj, const XReg& rk);                         // 00000000001000000     rk      rj   rd
void mod_w(const XReg& rd, const XReg& rj, const XReg& rk);                         // 00000000001000001     rk      rj   rd
void div_wu(const XReg& rd, const XReg& rj, const XReg& rk);                        // 00000000001000010     rk      rj   rd
void mod_wu(const XReg& rd, const XReg& rj, const XReg& rk);                        // 00000000001000011     rk      rj   rd
void div_d(const XReg& rd, const XReg& rj, const XReg& rk);                         // 00000000001000100     rk      rj   rd
void mod_d(const XReg& rd, const XReg& rj, const XReg& rk);                         // 00000000001000101     rk      rj   rd
void div_du(const XReg& rd, const XReg& rj, const XReg& rk);                        // 00000000001000110     rk      rj   rd
void mod_du(const XReg& rd, const XReg& rj, const XReg& rk);                        // 00000000001000111     rk      rj   rd
void crc_w_b_w(const XReg& rd, const XReg& rj, const XReg& rk);                     // 00000000001001000     rk      rj   rd
void crc_w_h_w(const XReg& rd, const XReg& rj, const XReg& rk);                     // 00000000001001001     rk      rj   rd
void crc_w_w_w(const XReg& rd, const XReg& rj, const XReg& rk);                     // 00000000001001010     rk      rj   rd
void crc_w_d_w(const XReg& rd, const XReg& rj, const XReg& rk);                     // 00000000001001011     rk      rj   rd
void crcc_w_b_w(const XReg& rd, const XReg& rj, const XReg& rk);                    // 00000000001001100     rk      rj   rd
void crcc_w_h_w(const XReg& rd, const XReg& rj, const XReg& rk);                    // 00000000001001101     rk      rj   rd
void crcc_w_w_w(const XReg& rd, const XReg& rj, const XReg& rk);                    // 00000000001001110     rk      rj   rd
void crcc_w_d_w(const XReg& rd, const XReg& rj, const XReg& rk);                    // 00000000001001111     rk      rj   rd
void break_(int32_t code15);                                                        // 00000000001010100       code15
void dbcl(int32_t code15);                                                          // 00000000001010101       code15
void syscall(int32_t code15);                                                       // 00000000001010110       code15
void alsl_d(const XReg& rd, const XReg& rj, const XReg& rk, uint32_t sa2);          // 000000000010110    sa2rk      rj   rd
void slli_w(const XReg& rd, const XReg& rj, uint32_t ui5);                          // 00000000010000001     ui5     rj   rd
void slli_d(const XReg& rd, const XReg& rj, uint32_t ui6);                          // 0000000001000001     ui6     rj   rd
void srli_w(const XReg& rd, const XReg& rj, uint32_t ui5);                          // 00000000010001001     ui5     rj   rd
void srli_d(const XReg& rd, const XReg& rj, uint32_t ui6);                          // 0000000001000101     ui6     rj   rd
void srai_w(const XReg& rd, const XReg& rj, uint32_t ui5);                          // 00000000010010001     ui5     rj   rd
void srai_d(const XReg& rd, const XReg& rj, uint32_t ui6);                          // 0000000001001001     ui6     rj   rd
void rotri_w(const XReg& rd, const XReg& rj, uint32_t ui5);                         // 00000000010011001     ui5     rj   rd
void rotri_d(const XReg& rd, const XReg& rj, uint32_t ui6);                         // 0000000001001101     ui6     rj   rd
void bstrins_w(const XReg& rd, const XReg& rj, uint32_t msbw, uint32_t lsbw);       // 00000000011 msbw 0 lsbw      rj   rd
void bstrpick_w(const XReg& rd, const XReg& rj, uint32_t msbw, uint32_t lsbw);      // 00000000011 msbw 1 lsbw      rj   rd
void bstrins_d(const XReg& rd, const XReg& rj, uint32_t msbd, uint32_t lsbd);       // 0000000010  msbd lsbd        rj   rd
void bstrpick_d(const XReg& rd, const XReg& rj, uint32_t msbd, uint32_t lsbd);      // 0000000011  msbd lsbd        rj   rd
void fadd_s(const XReg& fd, const XReg& fj, const XReg& fk);                        // 00000001000000001      fk    fj   fd
void fadd_d(const XReg& fd, const XReg& fj, const XReg& fk);                        // 00000001000000010      fk    fj   fd
void fsub_s(const XReg& fd, const XReg& fj, const XReg& fk);                        // 00000001000000101      fk    fj   fd
void fsub_d(const XReg& fd, const XReg& fj, const XReg& fk);                        // 00000001000000110      fk    fj   fd
void fmul_s(const XReg& fd, const XReg& fj, const XReg& fk);                        // 00000001000001001      fk    fj   fd
void fmul_d(const XReg& fd, const XReg& fj, const XReg& fk);                        // 00000001000001010      fk    fj   fd
void fdiv_s(const XReg& fd, const XReg& fj, const XReg& fk);                        // 00000001000001101      fk    fj   fd
void fdiv_d(const XReg& fd, const XReg& fj, const XReg& fk);                        // 00000001000001110      fk    fj   fd
void fmax_s(const XReg& fd, const XReg& fj, const XReg& fk);                        // 00000001000010001      fk    fj   fd
void fmax_d(const XReg& fd, const XReg& fj, const XReg& fk);                        // 00000001000010010      fk    fj   fd
void fmin_s(const XReg& fd, const XReg& fj, const XReg& fk);                        // 00000001000010101      fk    fj   fd
void fmin_d(const XReg& fd, const XReg& fj, const XReg& fk);                        // 00000001000010110      fk    fj   fd
void fmaxa_s(const XReg& fd, const XReg& fj, const XReg& fk);                       // 00000001000011001      fk    fj   fd
void fmaxa_d(const XReg& fd, const XReg& fj, const XReg& fk);                       // 00000001000011010      fk    fj   fd
void fmina_s(const XReg& fd, const XReg& fj, const XReg& fk);                       // 00000001000011101      fk    fj   fd
void fmina_d(const XReg& fd, const XReg& fj, const XReg& fk);                       // 00000001000011110      fk    fj   fd
void fscaleb_s(const XReg& fd, const XReg& fj, const XReg& fk);                     // 00000001000100001      fk    fj   fd
void fscaleb_d(const XReg& fd, const XReg& fj, const XReg& fk);                     // 00000001000100010      fk    fj   fd
void fcopysign_s(const XReg& fd, const XReg& fj, const XReg& fk);                   // 00000001000100101      fk    fj   fd
void fcopysign_d(const XReg& fd, const XReg& fj, const XReg& fk);                   // 00000001000100110      fk    fj   fd
void fabs_s(const XReg& fd, const XReg& fj);                                        // 0000000100010100000001       fj   fd
void fabs_d(const XReg& fd, const XReg& fj);                                        // 0000000100010100000010       fj   fd
void fneg_s(const XReg& fd, const XReg& fj);                                        // 0000000100010100000101       fj   fd
void fneg_d(const XReg& fd, const XReg& fj);                                        // 0000000100010100000110       fj   fd
void flogb_s(const XReg& fd, const XReg& fj);                                       // 0000000100010100001001       fj   fd
void flogb_d(const XReg& fd, const XReg& fj);                                       // 0000000100010100001010       fj   fd
void fclass_s(const XReg& fd, const XReg& fj);                                      // 0000000100010100001101       fj   fd
void fclass_d(const XReg& fd, const XReg& fj);                                      // 0000000100010100001110       fj   fd
void fsqrt_s(const XReg& fd, const XReg& fj);                                       // 0000000100010100010001       fj   fd
void fsqrt_d(const XReg& fd, const XReg& fj);                                       // 0000000100010100010010       fj   fd
void frecip_s(const XReg& fd, const XReg& fj);                                      // 0000000100010100010101       fj   fd
void frecip_d(const XReg& fd, const XReg& fj);                                      // 0000000100010100010110       fj   fd
void frsqrt_s(const XReg& fd, const XReg& fj);                                      // 0000000100010100011001       fj   fd
void frsqrt_d(const XReg& fd, const XReg& fj);                                      // 0000000100010100011010       fj   fd
void fmov_s(const XReg& fd, const XReg& fj);                                        // 0000000100010100100101       fj   fd
void fmov_d(const XReg& fd, const XReg& fj);                                        // 0000000100010100100110       fj   fd
void movgr2fr_w(const XReg& fd, const XReg& rj);                                    // 0000000100010100101001       rj   fd
void movgr2fr_d(const XReg& fd, const XReg& rj);                                    // 0000000100010100101010       rj   fd
void movgr2frh_w(const XReg& fd, const XReg& rj);                                   // 0000000100010100101011       rj   fd
void movfr2gr_s(const XReg& rd, const XReg& fj);                                    // 0000000100010100101101       fj   rd
void movfr2gr_d(const XReg& rd, const XReg& fj);                                    // 0000000100010100101110       fj   rd
void movfrh2gr_s(const XReg& rd, const XReg& fj);                                   // 0000000100010100101111       fj   rd
void movgr2fcsr(const XReg& fcsr, const XReg& rj);                                  // 0000000100010100110000       rj   fcsr
void movfcsr2gr(const XReg& rd, const XReg& fcsr);                                  // 0000000100010100110010       fcsr rd
void movfr2cf(const uint32_t cd, const XReg& fj);                                   // 0000000100010100110100       fj  00cd
void movcf2fr(const XReg& fd, const uint32_t cj);                                   // 0000000100010100110101       00cj fd
void movgr2cf(const uint32_t cd, const XReg& rj);                                   // 0000000100010100110110       rj  00cd
void movcf2gr(const XReg& rd, const uint32_t cj);                                   // 0000000100010100110111       00cj rd

void fcvt_s_d(const XReg& fd, const XReg& fj);                                      // 0000000100011001000110       fj   fd
void fcvt_d_s(const XReg& fd, const XReg& fj);                                      // 0000000100011001001001       fj   fd
void ftintrm_w_s(const XReg& fd, const XReg& fj);                                   // 0000000100011010000001       fj   fd
void ftintrm_w_d(const XReg& fd, const XReg& fj);                                   // 0000000100011010000010       fj   fd
void ftintrm_l_s(const XReg& fd, const XReg& fj);                                   // 0000000100011010001001       fj   fd
void ftintrm_l_d(const XReg& fd, const XReg& fj);                                   // 0000000100011010001010       fj   fd
void ftintrp_w_s(const XReg& fd, const XReg& fj);                                   // 0000000100011010010001       fj   fd
void ftintrp_w_d(const XReg& fd, const XReg& fj);                                   // 0000000100011010010010       fj   fd
void ftintrp_l_s(const XReg& fd, const XReg& fj);                                   // 0000000100011010011001       fj   fd
void ftintrp_l_d(const XReg& fd, const XReg& fj);                                   // 0000000100011010011010       fj   fd
void ftintrz_w_s(const XReg& fd, const XReg& fj);                                   // 0000000100011010100001       fj   fd
void ftintrz_w_d(const XReg& fd, const XReg& fj);                                   // 0000000100011010100010       fj   fd
void ftintrz_l_s(const XReg& fd, const XReg& fj);                                   // 0000000100011010101001       fj   fd
void ftintrz_l_d(const XReg& fd, const XReg& fj);                                   // 0000000100011010101010       fj   fd
void ftintrne_w_s(const XReg& fd, const XReg& fj);                                  // 0000000100011010110001       fj   fd
void ftintrne_w_d(const XReg& fd, const XReg& fj);                                  // 0000000100011010110010       fj   fd
void ftintrne_l_s(const XReg& fd, const XReg& fj);                                  // 0000000100011010111001       fj   fd
void ftintrne_l_d(const XReg& fd, const XReg& fj);                                  // 0000000100011010111010       fj   fd
void ftint_w_s(const XReg& fd, const XReg& fj);                                     // 0000000100011011000001       fj   fd
void ftint_w_d(const XReg& fd, const XReg& fj);                                     // 0000000100011011000010       fj   fd
void ftint_l_s(const XReg& fd, const XReg& fj);                                     // 0000000100011011001001       fj   fd
void ftint_l_d(const XReg& fd, const XReg& fj);                                     // 0000000100011011001010       fj   fd
void ffint_s_w(const XReg& fd, const XReg& fj);                                     // 0000000100011101000100       fj   fd
void ffint_s_l(const XReg& fd, const XReg& fj);                                     // 0000000100011101000110       fj   fd
void ffint_d_w(const XReg& fd, const XReg& fj);                                     // 0000000100011101001000       fj   fd
void ffint_d_l(const XReg& fd, const XReg& fj);                                     // 0000000100011101001010       fj   fd
void frint_s(const XReg& fd, const XReg& fj);                                       // 0000000100011110010001       fj   fd
void frint_d(const XReg& fd, const XReg& fj);                                       // 0000000100011110010010       fj   fd

void slti(const XReg& rd, const XReg& rj, int32_t si12);                            // 0000001000  si12             rj   rd
void sltui(const XReg& rd, const XReg& rj, int32_t si12);                           // 0000001001  si12             rj   rd
void addi_w(const XReg& rd, const XReg& rj, int32_t si12);                          // 0000001010  si12             rj   rd
void addi_d(const XReg& rd, const XReg& rj, int32_t si12);                          // 0000001011  si12             rj   rd
void lu52i_d(const XReg& rd, const XReg& rj, int32_t si12);                         // 0000001100  si12             rj   rd
void ori(const XReg& rd, const XReg& rj, int32_t ui12);                             // 0000001110  ui12             rj   rd
void xori(const XReg& rd, const XReg& rj, int32_t ui12);                            // 0000001111  ui12             rj   rd
void csrrd(const XReg& rd, int32_t csr14);                                          // 00000100  csr14            00000  rd
void csrwr(const XReg& rd, int32_t csr14);                                          // 00000100  csr14            00001  rd
void csrxchg(const XReg& rd, const XReg& rj, int32_t csr14);                        // 00000100  csr14          rj!=0,1  rd
void cacop(const int32_t code5, const XReg& rj, int32_t si12);                      // 0000011000  si12             rj  code5
void lddir(const XReg& rd, const XReg& rj, int32_t level8);                         // 00000110010000    level8     rj   rd
void ldpte(const XReg& rj, int32_t seq8);                                           // 00000110010001    seq8       rj  00000

void iocsrrd_b(const XReg& rd, const XReg& rj);                                     // 0000011001001000000000        rj   rd
void iocsrrd_h(const XReg& rd, const XReg& rj);                                     // 0000011001001000000001        rj   rd
void iocsrrd_w(const XReg& rd, const XReg& rj);                                     // 0000011001001000000010        rj   rd
void iocsrrd_d(const XReg& rd, const XReg& rj);                                     // 0000011001001000000011        rj   rd
void iocsrwr_b(const XReg& rd, const XReg& rj);                                     // 0000011001001000000100        rj   rd
void iocsrwr_h(const XReg& rd, const XReg& rj);                                     // 0000011001001000000101        rj   rd
void iocsrwr_w(const XReg& rd, const XReg& rj);                                     // 0000011001001000000110        rj   rd
void iocsrwr_d(const XReg& rd, const XReg& rj);                                     // 0000011001001000000111        rj   rd

void tlbclr();                                                                      // 00000110010010000010000000000000
void tlbflush();                                                                    // 00000110010010000010010000000000
void tlbsrch();                                                                     // 00000110010010000010100000000000
void tlbrd();                                                                       // 00000110010010000010110000000000
void tlbwr();                                                                       // 00000110010010000011000000000000
void tlbfill();                                                                     // 00000110010010000011010000000000
void ertn();                                                                        // 00000110010010000011100000000000

void idle(int32_t level15);                                                         // 00000110010010001      level15
void invtlb(const int32_t op, const XReg& rj, const XReg& rk);                      // 00000110010010011       rk    rj   op

void fmadd_s(const XReg& fd, const XReg& fj, const XReg& fk, const XReg& fa);       // 000010000001       fa   fk    fj   fd
void fmadd_d(const XReg& fd, const XReg& fj, const XReg& fk, const XReg& fa);       // 000010000010       fa   fk    fj   fd
void fmsub_s(const XReg& fd, const XReg& fj, const XReg& fk, const XReg& fa);       // 000010000101       fa   fk    fj   fd
void fmsub_d(const XReg& fd, const XReg& fj, const XReg& fk, const XReg& fa);       // 000010000110       fa   fk    fj   fd
void fnmadd_s(const XReg& fd, const XReg& fj, const XReg& fk, const XReg& fa);      // 000010001001       fa   fk    fj   fd
void fnmadd_d(const XReg& fd, const XReg& fj, const XReg& fk, const XReg& fa);      // 000010001010       fa   fk    fj   fd
void fnmsub_s(const XReg& fd, const XReg& fj, const XReg& fk, const XReg& fa);      // 000010001101       fa   fk    fj   fd
void fnmsub_d(const XReg& fd, const XReg& fj, const XReg& fk, const XReg& fa);      // 000010001110       fa   fk    fj   fd

void fcmp_caf_s(const uint32_t cd, const XReg& fj, const XReg& fk);                 // 000011000001      00000 fk    fj  00cd
void fcmp_caf_d(const uint32_t cd, const XReg& fj, const XReg& fk);                 // 000011000010      00000 fk    fj  00cd
void fcmp_cun_s(const uint32_t cd, const XReg& fj, const XReg& fk);                 // 000011000001      01000 fk    fj  00cd
void fcmp_cun_d(const uint32_t cd, const XReg& fj, const XReg& fk);                 // 000011000010      01000 fk    fj  00cd
void fcmp_ceq_s(const uint32_t cd, const XReg& fj, const XReg& fk);                 // 000011000001      00100 fk    fj  00cd
void fcmp_ceq_d(const uint32_t cd, const XReg& fj, const XReg& fk);                 // 000011000010      00100 fk    fj  00cd
void fcmp_cueq_s(const uint32_t cd, const XReg& fj, const XReg& fk);                // 000011000001      01100 fk    fj  00cd
void fcmp_cueq_d(const uint32_t cd, const XReg& fj, const XReg& fk);                // 000011000010      01100 fk    fj  00cd
void fcmp_clt_s(const uint32_t cd, const XReg& fj, const XReg& fk);                 // 000011000001      00010 fk    fj  00cd
void fcmp_clt_d(const uint32_t cd, const XReg& fj, const XReg& fk);                 // 000011000010      00010 fk    fj  00cd
void fcmp_cult_s(const uint32_t cd, const XReg& fj, const XReg& fk);                // 000011000001      01010 fk    fj  00cd
void fcmp_cult_d(const uint32_t cd, const XReg& fj, const XReg& fk);                // 000011000010      01010 fk    fj  00cd
void fcmp_cle_s(const uint32_t cd, const XReg& fj, const XReg& fk);                 // 000011000001      00110 fk    fj  00cd
void fcmp_cle_d(const uint32_t cd, const XReg& fj, const XReg& fk);                 // 000011000010      00110 fk    fj  00cd
void fcmp_cule_s(const uint32_t cd, const XReg& fj, const XReg& fk);                // 000011000001      01110 fk    fj  00cd
void fcmp_cule_d(const uint32_t cd, const XReg& fj, const XReg& fk);                // 000011000010      01110 fk    fj  00cd
void fcmp_cne_s(const uint32_t cd, const XReg& fj, const XReg& fk);                 // 000011000001      10000 fk    fj  00cd
void fcmp_cne_d(const uint32_t cd, const XReg& fj, const XReg& fk);                 // 000011000010      10000 fk    fj  00cd
void fcmp_cor_s(const uint32_t cd, const XReg& fj, const XReg& fk);                 // 000011000001      10100 fk    fj  00cd
void fcmp_cor_d(const uint32_t cd, const XReg& fj, const XReg& fk);                 // 000011000010      10100 fk    fj  00cd
void fcmp_cune_s(const uint32_t cd, const XReg& fj, const XReg& fk);                // 000011000001      11000 fk    fj  00cd
void fcmp_cune_d(const uint32_t cd, const XReg& fj, const XReg& fk);                // 000011000010      11000 fk    fj  00cd
void fcmp_saf_s(const uint32_t cd, const XReg& fj, const XReg& fk);                 // 000011000001      00001 fk    fj  00cd
void fcmp_saf_d(const uint32_t cd, const XReg& fj, const XReg& fk);                 // 000011000010      00001 fk    fj  00cd
void fcmp_sun_s(const uint32_t cd, const XReg& fj, const XReg& fk);                 // 000011000001      01001 fk    fj  00cd
void fcmp_sun_d(const uint32_t cd, const XReg& fj, const XReg& fk);                 // 000011000010      01001 fk    fj  00cd
void fcmp_seq_s(const uint32_t cd, const XReg& fj, const XReg& fk);                 // 000011000001      00101 fk    fj  00cd
void fcmp_seq_d(const uint32_t cd, const XReg& fj, const XReg& fk);                 // 000011000010      00101 fk    fj  00cd
void fcmp_sueq_s(const uint32_t cd, const XReg& fj, const XReg& fk);                // 000011000001      01101 fk    fj  00cd
void fcmp_sueq_d(const uint32_t cd, const XReg& fj, const XReg& fk);                // 000011000010      01101 fk    fj  00cd
void fcmp_slt_s(const uint32_t cd, const XReg& fj, const XReg& fk);                 // 000011000001      00011 fk    fj  00cd
void fcmp_slt_d(const uint32_t cd, const XReg& fj, const XReg& fk);                 // 000011000010      00011 fk    fj  00cd
void fcmp_sult_s(const uint32_t cd, const XReg& fj, const XReg& fk);                // 000011000001      01011 fk    fj  00cd
void fcmp_sult_d(const uint32_t cd, const XReg& fj, const XReg& fk);                // 000011000010      01011 fk    fj  00cd
void fcmp_sle_s(const uint32_t cd, const XReg& fj, const XReg& fk);                 // 000011000001      00111 fk    fj  00cd
void fcmp_sle_d(const uint32_t cd, const XReg& fj, const XReg& fk);                 // 000011000010      00111 fk    fj  00cd
void fcmp_sule_s(const uint32_t cd, const XReg& fj, const XReg& fk);                // 000011000001      01111 fk    fj  00cd
void fcmp_sule_d(const uint32_t cd, const XReg& fj, const XReg& fk);                // 000011000010      01111 fk    fj  00cd
void fcmp_sne_s(const uint32_t cd, const XReg& fj, const XReg& fk);                 // 000011000001      10001 fk    fj  00cd
void fcmp_sne_d(const uint32_t cd, const XReg& fj, const XReg& fk);                 // 000011000010      10001 fk    fj  00cd
void fcmp_sor_s(const uint32_t cd, const XReg& fj, const XReg& fk);                 // 000011000001      10101 fk    fj  00cd
void fcmp_sor_d(const uint32_t cd, const XReg& fj, const XReg& fk);                 // 000011000010      10101 fk    fj  00cd
void fcmp_sune_s(const uint32_t cd, const XReg& fj, const XReg& fk);                // 000011000001      11001 fk    fj  00cd
void fcmp_sune_d(const uint32_t cd, const XReg& fj, const XReg& fk);                // 000011000010      11001 fk    fj  00cd
void fsel(const XReg& fd, const XReg& fj, const XReg& fk, const uint32_t ca);       // 00001101000000      ca  fk    fj   fd
void addu16i_d(const XReg& rd, const XReg& rj, int32_t si16);                       // 000100      si16              rj   rd

void lu12i_w(const XReg& rd, int32_t si20);                                         // 0001010     si20                   rd
void lu32i_d(const XReg& rd, int32_t si20);                                         // 0001011     si20                   rd
void pcaddi(const XReg& rd, int32_t si20);                                          // 0001100     si20                   rd
void pcalau12i(const XReg& rd, int32_t si20);                                       // 0001101     si20                   rd
void pcaddu12i(const XReg& rd, int32_t si20);                                       // 0001110     si20                   rd
void pcaddu18i(const XReg& rd, int32_t si20);                                       // 0001111     si20                   rd

void pcaddi(const XReg& rd, const Label& label);                                    // 0001100     si20                   rd

void ll_w(const XReg& rd, const XReg& rj, int32_t si14);                            // 00100000    si14              rj   rd
void sc_w(const XReg& rd, const XReg& rj, int32_t si14);                            // 00100001    si14              rj   rd
void ll_d(const XReg& rd, const XReg& rj, int32_t si14);                            // 00100010    si14              rj   rd
void sc_d(const XReg& rd, const XReg& rj, int32_t si14);                            // 00100011    si14              rj   rd
void ldptr_w(const XReg& rd, const XReg& rj, int32_t si14);                         // 00100100    si14              rj   rd
void stptr_w(const XReg& rd, const XReg& rj, int32_t si14);                         // 00100101    si14              rj   rd
void ldptr_d(const XReg& rd, const XReg& rj, int32_t si14);                         // 00100110    si14              rj   rd
void stptr_d(const XReg& rd, const XReg& rj, int32_t si14);                         // 00100111    si14              rj   rd
void ld_b(const XReg& rd, const XReg& rj, int32_t si12);                            // 0010100000    si12            rj   rd
void ld_h(const XReg& rd, const XReg& rj, int32_t si12);                            // 0010100001    si12            rj   rd
void ld_w(const XReg& rd, const XReg& rj, int32_t si12);                            // 0010100010    si12            rj   rd
void ld_d(const XReg& rd, const XReg& rj, int32_t si12);                            // 0010100011    si12            rj   rd
void st_b(const XReg& rd, const XReg& rj, int32_t si12);                            // 0010100100    si12            rj   rd
void st_h(const XReg& rd, const XReg& rj, int32_t si12);                            // 0010100101    si12            rj   rd
void st_w(const XReg& rd, const XReg& rj, int32_t si12);                            // 0010100110    si12            rj   rd
void st_d(const XReg& rd, const XReg& rj, int32_t si12);                            // 0010100111    si12            rj   rd
void ld_bu(const XReg& rd, const XReg& rj, int32_t si12);                           // 0010101000    si12            rj   rd
void ld_hu(const XReg& rd, const XReg& rj, int32_t si12);                           // 0010101001    si12            rj   rd
void ld_wu(const XReg& rd, const XReg& rj, int32_t si12);                           // 0010101010    si12            rj   rd
void preld(const int32_t hint, const XReg& rj, int32_t si12);                       // 0010101011    si12            rj   hint
void fld_s(const XReg& fd, const XReg& rj, int32_t si12);                           // 0010101100    si12            rj   fd
void fst_s(const XReg& fd, const XReg& rj, int32_t si12);                           // 0010101101    si12            rj   fd
void fld_d(const XReg& fd, const XReg& rj, int32_t si12);                           // 0010101110    si12            rj   fd
void fst_d(const XReg& fd, const XReg& rj, int32_t si12);                           // 0010101111    si12            rj   fd

void ldx_b(const XReg& rd, const XReg& rj, const XReg& rk);                         // 00111000000000000     rk      rj   rd
void ldx_h(const XReg& rd, const XReg& rj, const XReg& rk);                         // 00111000000001000     rk      rj   rd
void ldx_w(const XReg& rd, const XReg& rj, const XReg& rk);                         // 00111000000010000     rk      rj   rd
void ldx_d(const XReg& rd, const XReg& rj, const XReg& rk);                         // 00111000000011000     rk      rj   rd
void stx_b(const XReg& rd, const XReg& rj, const XReg& rk);                         // 00111000000100000     rk      rj   rd
void stx_h(const XReg& rd, const XReg& rj, const XReg& rk);                         // 00111000000101000     rk      rj   rd
void stx_w(const XReg& rd, const XReg& rj, const XReg& rk);                         // 00111000000110000     rk      rj   rd
void stx_d(const XReg& rd, const XReg& rj, const XReg& rk);                         // 00111000000111000     rk      rj   rd
void ldx_bu(const XReg& rd, const XReg& rj, const XReg& rk);                        // 00111000001000000     rk      rj   rd
void ldx_hu(const XReg& rd, const XReg& rj, const XReg& rk);                        // 00111000001001000     rk      rj   rd
void ldx_wu(const XReg& rd, const XReg& rj, const XReg& rk);                        // 00111000001010000     rk      rj   rd

void preldx(const int32_t hint, const XReg& rj, const XReg& rk);                    // 00111000001011000     rk      rj   hint
void fldx_s(const XReg& fd, const XReg& rj, const XReg& rk);                        // 00111000001100000     rk      rj   fd
void fldx_d(const XReg& fd, const XReg& rj, const XReg& rk);                        // 00111000001101000     rk      rj   fd
void fstx_s(const XReg& fd, const XReg& rj, const XReg& rk);                        // 00111000001110000     rk      rj   fd
void fstx_d(const XReg& fd, const XReg& rj, const XReg& rk);                        // 00111000001111000     rk      rj   fd

void amswap_w(const XReg& rd, const XReg& rk, const XReg& rj);                      // 00111000011000000     rk      rj   rd
void amswap_d(const XReg& rd, const XReg& rk, const XReg& rj);                      // 00111000011000001     rk      rj   rd
void amadd_w(const XReg& rd, const XReg& rk, const XReg& rj);                       // 00111000011000010     rk      rj   rd
void amadd_d(const XReg& rd, const XReg& rk, const XReg& rj);                       // 00111000011000011     rk      rj   rd
void amand_w(const XReg& rd, const XReg& rk, const XReg& rj);                       // 00111000011000100     rk      rj   rd
void amand_d(const XReg& rd, const XReg& rk, const XReg& rj);                       // 00111000011000101     rk      rj   rd
void amor_w(const XReg& rd, const XReg& rk, const XReg& rj);                        // 00111000011000110     rk      rj   rd
void amor_d(const XReg& rd, const XReg& rk, const XReg& rj);                        // 00111000011000111     rk      rj   rd
void amxor_w(const XReg& rd, const XReg& rk, const XReg& rj);                       // 00111000011001000     rk      rj   rd
void amxor_d(const XReg& rd, const XReg& rk, const XReg& rj);                       // 00111000011001001     rk      rj   rd
void ammax_w(const XReg& rd, const XReg& rk, const XReg& rj);                       // 00111000011001010     rk      rj   rd
void ammax_d(const XReg& rd, const XReg& rk, const XReg& rj);                       // 00111000011001011     rk      rj   rd
void ammin_w(const XReg& rd, const XReg& rk, const XReg& rj);                       // 00111000011001100     rk      rj   rd
void ammin_d(const XReg& rd, const XReg& rk, const XReg& rj);                       // 00111000011001101     rk      rj   rd
void ammax_wu(const XReg& rd, const XReg& rk, const XReg& rj);                      // 00111000011001110     rk      rj   rd
void ammax_du(const XReg& rd, const XReg& rk, const XReg& rj);                      // 00111000011001111     rk      rj   rd
void ammin_wu(const XReg& rd, const XReg& rk, const XReg& rj);                      // 00111000011010000     rk      rj   rd
void ammin_du(const XReg& rd, const XReg& rk, const XReg& rj);                      // 00111000011010001     rk      rj   rd
void amswap_db_w(const XReg& rd, const XReg& rk, const XReg& rj);                   // 00111000011010010     rk      rj   rd
void amswap_db_d(const XReg& rd, const XReg& rk, const XReg& rj);                   // 00111000011010011     rk      rj   rd
void amadd_db_w(const XReg& rd, const XReg& rk, const XReg& rj);                    // 00111000011010100     rk      rj   rd
void amadd_db_d(const XReg& rd, const XReg& rk, const XReg& rj);                    // 00111000011010101     rk      rj   rd
void amand_db_w(const XReg& rd, const XReg& rk, const XReg& rj);                    // 00111000011010110     rk      rj   rd
void amand_db_d(const XReg& rd, const XReg& rk, const XReg& rj);                    // 00111000011010111     rk      rj   rd
void amor_db_w(const XReg& rd, const XReg& rk, const XReg& rj);                     // 00111000011011000     rk      rj   rd
void amor_db_d(const XReg& rd, const XReg& rk, const XReg& rj);                     // 00111000011011001     rk      rj   rd
void amxor_db_w(const XReg& rd, const XReg& rk, const XReg& rj);                    // 00111000011011010     rk      rj   rd
void amxor_db_d(const XReg& rd, const XReg& rk, const XReg& rj);                    // 00111000011011011     rk      rj   rd
void ammax_db_w(const XReg& rd, const XReg& rk, const XReg& rj);                    // 00111000011011100     rk      rj   rd
void ammax_db_d(const XReg& rd, const XReg& rk, const XReg& rj);                    // 00111000011011101     rk      rj   rd
void ammin_db_w(const XReg& rd, const XReg& rk, const XReg& rj);                    // 00111000011011110     rk      rj   rd
void ammin_db_d(const XReg& rd, const XReg& rk, const XReg& rj);                    // 00111000011011111     rk      rj   rd
void ammax_db_wu(const XReg& rd, const XReg& rk, const XReg& rj);                   // 00111000011100000     rk      rj   rd
void ammax_db_du(const XReg& rd, const XReg& rk, const XReg& rj);                   // 00111000011100001     rk      rj   rd
void ammin_db_wu(const XReg& rd, const XReg& rk, const XReg& rj);                   // 00111000011100010     rk      rj   rd
void ammin_db_du(const XReg& rd, const XReg& rk, const XReg& rj);                   // 00111000011100011     rk      rj   rd

void dbar(const int32_t hint);                                                      // 00111000011100100       hint
void ibar(const int32_t hint);                                                      // 00111000011100101       hint

void fldgt_s(const XReg& fd, const XReg& rj, const XReg& rk);                       // 00111000011101000     rk      rj   fd
void fldgt_d(const XReg& fd, const XReg& rj, const XReg& rk);                       // 00111000011101001     rk      rj   fd
void fldle_s(const XReg& fd, const XReg& rj, const XReg& rk);                       // 00111000011101010     rk      rj   fd
void fldle_d(const XReg& fd, const XReg& rj, const XReg& rk);                       // 00111000011101011     rk      rj   fd
void fstgt_s(const XReg& fd, const XReg& rj, const XReg& rk);                       // 00111000011101100     rk      rj   fd
void fstgt_d(const XReg& fd, const XReg& rj, const XReg& rk);                       // 00111000011101101     rk      rj   fd
void fstle_s(const XReg& fd, const XReg& rj, const XReg& rk);                       // 00111000011101110     rk      rj   fd
void fstle_d(const XReg& fd, const XReg& rj, const XReg& rk);                       // 00111000011101111     rk      rj   fd

void ldgt_b(const XReg& rd, const XReg& rj, const XReg& rk);                        // 00111000011110000     rk      rj   rd
void ldgt_h(const XReg& rd, const XReg& rj, const XReg& rk);                        // 00111000011110001     rk      rj   rd
void ldgt_w(const XReg& rd, const XReg& rj, const XReg& rk);                        // 00111000011110010     rk      rj   rd
void ldgt_d(const XReg& rd, const XReg& rj, const XReg& rk);                        // 00111000011110011     rk      rj   rd
void ldle_b(const XReg& rd, const XReg& rj, const XReg& rk);                        // 00111000011110100     rk      rj   rd
void ldle_h(const XReg& rd, const XReg& rj, const XReg& rk);                        // 00111000011110101     rk      rj   rd
void ldle_w(const XReg& rd, const XReg& rj, const XReg& rk);                        // 00111000011110110     rk      rj   rd
void ldle_d(const XReg& rd, const XReg& rj, const XReg& rk);                        // 00111000011110111     rk      rj   rd
void stgt_b(const XReg& rd, const XReg& rj, const XReg& rk);                        // 00111000011111000     rk      rj   rd
void stgt_h(const XReg& rd, const XReg& rj, const XReg& rk);                        // 00111000011111001     rk      rj   rd
void stgt_w(const XReg& rd, const XReg& rj, const XReg& rk);                        // 00111000011111010     rk      rj   rd
void stgt_d(const XReg& rd, const XReg& rj, const XReg& rk);                        // 00111000011111011     rk      rj   rd
void stle_b(const XReg& rd, const XReg& rj, const XReg& rk);                        // 00111000011111100     rk      rj   rd
void stle_h(const XReg& rd, const XReg& rj, const XReg& rk);                        // 00111000011111101     rk      rj   rd
void stle_w(const XReg& rd, const XReg& rj, const XReg& rk);                        // 00111000011111110     rk      rj   rd
void stle_d(const XReg& rd, const XReg& rj, const XReg& rk);                        // 00111000011111111     rk      rj   rd

void nop();

void jirl(const XReg& rd, const XReg& rj, int64_t offset);                          // 010011        offset          rj   rd
void bltu(const XReg& rj, const XReg& rd, int64_t offset);                          // 011010        offset          rj   rd
void bgeu(const XReg& rj, const XReg& rd, int64_t offset);                          // 011011        offset          rj   rd
void beqz(const XReg& rj, int64_t offset21);                                        // 010000        offset21[15:0]  rj  offset21[20:16]
void bnez(const XReg& rj, int64_t offset21);                                        // 010001        offset21[15:0]  rj  offset21[20:16]
void bceqz(const uint32_t cj, int64_t offset21);                                    // 010010        offset21[15:0] 00cj  offset21[20:16]
void bcnez(const uint32_t cj, int64_t offset21);                                    // 010010        offset21[15:0] 01cj  offset21[20:16]
void beq(const XReg& rj, const XReg& rd, int64_t offset);                           // 010110        offset          rj   rd
void bne(const XReg& rj, const XReg& rd, int64_t offset);                           // 010111        offset          rj   rd
void blt(const XReg& rj, const XReg& rd, int64_t offset);                           // 011000        offset          rj   rd
void bge(const XReg& rj, const XReg& rd, int64_t offset);                           // 011001        offset          rj   rd
void b(int64_t offset26);                                                           // 010100        offset26[15:0]    offset26[25:16]
void bl(int64_t offset26);                                                          // 010101        offset26[15:0]    offset26[25:16]

void jirl(const XReg& rd, const XReg& rj, const Label& label);                      // 010011        offset          rj   rd
void bltu(const XReg& rj, const XReg& rd, const Label& label);                      // 011010        offset          rj   rd
void bgeu(const XReg& rj, const XReg& rd, const Label& label);                      // 011011        offset          rj   rd
void beqz(const XReg& rj, const Label& label);                                      // 010000        offset21[15:0]  rj  offset21[20:16]
void bnez(const XReg& rj, const Label& label);                                      // 010001        offset21[15:0]  rj  offset21[20:16]
void bceqz(const uint32_t cj, const Label& label);                                  // 010010        offset21[15:0] 00cj  offset21[20:16]
void bcnez(const uint32_t cj, const Label& label);                                  // 010010        offset21[15:0] 01cj  offset21[20:16]
void beq(const XReg& rj, const XReg& rd, const Label& label);                       // 010110        offset          rj   rd
void bne(const XReg& rj, const XReg& rd, const Label& label);                       // 010111        offset          rj   rd
void blt(const XReg& rj, const XReg& rd, const Label& label);                       // 011000        offset          rj   rd
void bge(const XReg& rj, const XReg& rd, const Label& label);                       // 011001        offset          rj   rd
void b(const Label& label);                                                         // 010100        offset26[15:0]    offset26[25:16]
void bl(const Label& label);                                                        // 010101        offset26[15:0]    offset26[25:16]

/*Base end*/
