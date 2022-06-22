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

template <typename T, typename std::enable_if<std::is_unsigned<T>::value, std::nullptr_t>::type = nullptr> 
void add_imm(const XReg &dst, const XReg &src, T imm, const XReg &tmp) { 
  assert(src.getIdx() != tmp.getIdx());

  uint64_t bit_ptn = static_cast<uint64_t>(imm);

  //si12
  if ((bit_ptn >> 11) == 0) {
    addi_d(dst, src,(int32_t)bit_ptn);
  }
  //si16<<16
  else if ( (bit_ptn & 0xffff) == 0 && 
            (bit_ptn & 0x80000000) == 0 &&
	    (bit_ptn >> 32) == 0 ) {
    addu16i_d(dst, src, (int32_t)(bit_ptn >> 16));
  }
  else {
    mov_imm(tmp, bit_ptn);
    add_d(dst, src, tmp);
  }

  return;
}

template <typename T, typename std::enable_if<std::is_signed<T>::value, std::nullptr_t>::type = nullptr> 
void add_imm(const XReg &dst, const XReg &src, T imm, const XReg &tmp) { 
  assert(src.getIdx() != tmp.getIdx());

  /* Sign bit must be extended. */
  int64_t bit_ptn = static_cast<int64_t>(imm);

  int64_t min = -1*(1<<11);
  int64_t max = 0x7ff;
  //si12
  if ( chkVal(bit_ptn, min, max) ) {
    addi_d(dst, src, (int32_t)bit_ptn);
    return;
  }

  //si16<<16
  uint32_t signBit = bit_ptn & 0x80000000;
  uint32_t upper32 = bit_ptn >> 32;

  if ( (bit_ptn & 0xffff) == 0 && 
       (  (signBit == 0 && upper32 == 0) 
	||(signBit != 0 && upper32 == 0xffffffff)  
       ) ){
    addu16i_d(dst, src, (int32_t)(bit_ptn >> 16));
    return;
  }

  mov_imm(tmp, bit_ptn);
  add_d(dst, src, tmp);

  return;
}

template <typename T, typename std::enable_if<std::is_signed<T>::value, std::nullptr_t>::type = nullptr> 
void sub_imm(const XReg &dst, const XReg &src, T imm, const XReg &tmp) { 
  /* This add_imm function allows dst == src,
 *      but tmp must be different from src */
  assert(src.getIdx() != tmp.getIdx());

  /* Sign bit must be extended. */
  int64_t bit_ptn = static_cast<int64_t>(imm);
  int64_t negImm = -1*bit_ptn;

  add_imm(dst, src, negImm, tmp);

  return;
}

template <typename T, typename std::enable_if<std::is_unsigned<T>::value, std::nullptr_t>::type = nullptr> 
void sub_imm(const XReg &dst, const XReg &src, T imm, const XReg &tmp) { 
  /* This add_imm function allows dst == src,
 *      but tmp must be different from src */
  assert(src.getIdx() != tmp.getIdx());

  uint64_t bit_ptn = static_cast<uint64_t>(imm);
  int64_t negImm = -1*bit_ptn;

  add_imm(dst, src, negImm, tmp);

  return;
}

void mov_imm_general(const XReg &dst, uint64_t imm) {
  //64bit = 12bit_4 + 20bit_3 + 20bit_2 + 12bit_1
  uint32_t imm_12bit_1 = imm & 0xfff;
  uint32_t imm_20bit_2 = (imm>>12) & 0xfffff;
  uint32_t signBit12 = 0x800;
  uint32_t signBit20 = 0x80000;
 
  if( 0 != (imm_20bit_2 & signBit20) ) {
    imm_20bit_2 |= 0xfff00000;  //sign extend
  }

  lu12i_w(dst, imm_20bit_2);
  ori(dst, dst, imm_12bit_1);

  // if high 32bit not 0
  if (imm & 0xffffffff80000000) {
    uint32_t imm_20bit_3 = (imm>>32) & 0xfffff;
    if( 0 != (imm_20bit_3 & signBit20) ) {
      imm_20bit_3 |= 0xfff00000;  //sign extend
    }
    lu32i_d(dst, imm_20bit_3);

    uint32_t imm_12bit_4 = (imm>>52) & 0xfff;
    if( 0 != (imm_12bit_4 & signBit12) ) {
      imm_12bit_4 |= 0xfffff000;  //sign extend
    }
    lu52i_d(dst, dst, imm_12bit_4);
  }

  return;
}

template <typename T, typename std::enable_if<std::is_unsigned<T>::value, std::nullptr_t>::type = nullptr> 
void mov_imm(const XReg &dst, T imm) {
  uint64_t bit_ptn = static_cast<uint64_t>(imm);

  //si12
  if ((bit_ptn >> 11) == 0) {
    addi_d(dst, zero,(int32_t)bit_ptn);
  }
  //si16<<16
  else if ( (bit_ptn & 0xffff) == 0 && 
            (bit_ptn & 0x80000000) == 0 &&
            (bit_ptn >> 32) == 0 ) {
    addu16i_d(dst, zero, (int32_t)(bit_ptn >> 16));
  }
  else {
    mov_imm_general(dst, bit_ptn);
  }

  return;
}

template <typename T, typename std::enable_if<std::is_signed<T>::value, std::nullptr_t>::type = nullptr> 
void mov_imm(const XReg &dst, T imm) {
  int64_t bit_ptn = static_cast<int64_t>(imm);

  //si12
  int64_t s12min = -1*(1<<11);
  int64_t s12max = 0x7ff;
  if ( chkVal(bit_ptn, s12min, s12max) ) {
    addi_d(dst, zero, (int32_t)bit_ptn);
    return;
  }

  //si16<<16
  uint32_t signBit = bit_ptn & 0x80000000;
  uint32_t upper32 = bit_ptn >> 32;

  if ( (bit_ptn & 0xffff) == 0 && 
       (  (signBit == 0 && upper32 == 0) 
	||(signBit != 0 && upper32 == 0xffffffff)  
       ) ){
    addu16i_d(dst, zero, (int32_t)(bit_ptn >> 16));
    return;
  }

  mov_imm_general(dst, (uint64_t)bit_ptn);
  return;
}

