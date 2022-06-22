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
/////////////// bit operation ////////////////////
constexpr uint32_t F(uint32_t val, uint32_t pos) { return val << pos; }
inline uint64_t lsb(uint64_t v) { return v & 0x1; }

uint32_t concat(const std::initializer_list<uint32_t> list) {
  uint32_t result = 0;
  for (auto f : list) {
    result |= f;
  }
  return result;
}

inline uint64_t msb(uint64_t v, uint32_t size) {
  uint32_t shift = (size == 0) ? 0 : size - 1;
  return (v >> shift) & 0x1;
}

inline uint64_t ones(uint32_t size) { return (size == 64) ? 0xffffffffffffffff : ((uint64_t)1 << size) - 1; }

inline uint32_t field(uint64_t v, uint32_t mpos, uint32_t lpos) { return static_cast<uint32_t>((v >> lpos) & ones(mpos - lpos + 1)); }

inline uint64_t rrotate(uint64_t v, uint32_t size, uint32_t num) {
  uint32_t shift = (size == 0) ? 0 : (num % size);
  v &= ones(size);
  return (v >> shift) | ((v & ones(shift)) << (size - shift));
}

inline uint64_t lrotate(uint64_t v, uint32_t size, uint32_t num) {
  uint32_t shift = (size == 0) ? 0 : (num % size);
  v &= ones(size);
  return ((v << shift) | ((v >> (size - shift)))) & ones(size);
}

inline uint64_t replicate(uint64_t v, uint32_t esize, uint32_t size) {
  uint64_t result = 0;
  for (uint32_t i = 0; i < 64 / esize; ++i) {
    result |= v << (esize * i);
  }
  return result & ones(size);
}

/******************** LoongArch base begin *******************************/

void CodeGenerator::Loongarch2Reg(uint32_t opCode, uint32_t rj, uint32_t rd)
{
  uint32_t code = concat({F(opCode, 10), F(rj, 5), F(rd, 0)});
  dd(code);
}

void CodeGenerator::Loongarch2Reg1Offset(uint32_t opCode, uint32_t rj, uint32_t rd, int32_t offset, int32_t type)
{
  uint32_t code = 0;
  switch (type)
  {
    case 1:
      verifyIncRange(offset, -1 * (1 << 15), ones(15), ERR_LABEL_IS_TOO_FAR, true);
      code = concat({F(opCode, 26), F(offset&ones(16), 10), F(rj, 5), F(rd, 0)});
      break;
    case 2:
      verifyIncRange(offset, -1 * (1 << 11), ones(11), ERR_ILLEGAL_IMM_RANGE, true);
      code = concat({F(opCode, 22), F(offset&ones(12), 10), F(rj, 5), F(rd, 0)});
      break;
    case 3:
      verifyIncRange(offset, 0, ones(6), ERR_ILLEGAL_IMM_RANGE, true);
      code = concat({F(opCode, 16), F(offset, 10), F(rj, 5), F(rd, 0)});
      break;
    case 4:
      verifyIncRange(offset, 0, ones(5), ERR_ILLEGAL_IMM_RANGE, true);
      code = concat({F(opCode, 15), F(offset, 10), F(rj, 5), F(rd, 0)});
      break;
    case 5:
      verifyIncRange(offset, 0, ones(12), ERR_ILLEGAL_IMM_RANGE, true);
      code = concat({F(opCode, 22), F(offset, 10), F(rj, 5), F(rd, 0)});
      break;
    case 6: {
      verifyIncRange(offset, -1 * (1 << 15), ones(15), ERR_ILLEGAL_IMM_RANGE, true);
      uint32_t imm14 = static_cast<uint32_t>((offset >> 2) & ones(14));
      code = concat({F(opCode, 24), F(imm14, 10), F(rj, 5), F(rd, 0)});
      break;
    }
    case 7:
      verifyIncRange(offset, 0, ones(8), ERR_ILLEGAL_IMM_RANGE, true);
      code = concat({F(opCode, 18), F(offset, 10), F(rj, 5), F(rd, 0)});
      break;
    case 8:
      verifyIncRange(offset, 0, ones(14), ERR_ILLEGAL_IMM_RANGE, true);
      code = concat({F(opCode, 24), F(offset&ones(14), 10), F(rj, 5), F(rd, 0)});
      break;
    default:
      code = concat({F(opCode, 26), F(offset, 10), F(rj, 5), F(rd, 0)});
      break;
  }
  dd(code);
}

void CodeGenerator::Loongarch2Reg2Param(uint32_t opCode, uint32_t msb, uint32_t lsb, uint32_t rj, uint32_t rd, int32_t type)
{
  uint32_t code = 0;
  switch (type)
  {
    case 1:
      code = concat({F(opCode, 21), F(msb, 16), F(0, 15), F(lsb, 10), F(rj, 5), F(rd, 0)});
      break;
    case 2:
      code = concat({F(opCode, 21), F(msb, 16), F(1, 15), F(lsb, 10), F(rj, 5), F(rd, 0)});
      break;
    case 3:
    default:
      code = concat({F(opCode, 22), F(msb, 16), F(lsb, 10), F(rj, 5), F(rd, 0)});
      break;
  }
  dd(code);
}

// loongarch base instruction with 3 reg
void CodeGenerator::Loongarch3Reg(uint32_t opCode, uint32_t rk, uint32_t rj, uint32_t rd)
{
  uint32_t code = concat({F(opCode, 15), F(rk, 10), F(rj, 5), F(rd, 0)});
  dd(code);
}

// loongarch base instruction with 1 sa 3 reg
void CodeGenerator::Loongarch3Reg1Sa(uint32_t opCode, uint32_t sa, uint32_t rk, uint32_t rj, uint32_t rd, uint32_t type)
{
  uint32_t code = 0;
  switch (type)
  {
    case 1:
      code = concat({F(opCode, 18), F(sa, 15), F(rk, 10), F(rj, 5), F(rd, 0)});
      break;
    case 2:
    default:
      code = concat({F(opCode, 17), F(sa, 15), F(rk, 10), F(rj, 5), F(rd, 0)});
      break;
  }
  
  dd(code);
}

void CodeGenerator::Loongarch1Code(uint32_t opCode, uint32_t code)
{
  uint32_t rcode = concat({F(opCode, 15), F(code, 0)});
  dd(rcode);
}

void CodeGenerator::Loongarch2RegZeroExtend(uint32_t opCode, uint32_t fr, uint32_t cr, int32_t type)
{
  uint32_t code = 0;
  switch (type)
  {
    case 1:
      code = concat({F(opCode, 10), F(fr, 5), F(0, 3), F(cr, 0)});
      break;
    case 2:
    default:
      code = concat({F(opCode, 10), F(0, 8), F(fr, 5), F(cr, 0)});
      break;
  }

  dd(code);
}

void CodeGenerator::LoongarchOnlyOpcode(uint32_t opCode)
{
  dd(opCode);
}

void CodeGenerator::Loongarch4Reg(uint32_t opCode, uint32_t fa, uint32_t fk, uint32_t fj, uint32_t fd)
{
  uint32_t code = concat({F(opCode, 20), F(fa, 15), F(fk, 10), F(fj, 5), F(fd, 0)});
  dd(code);
}

void CodeGenerator::Loongarch1Reg1Imm(uint32_t opCode, int32_t si, uint32_t rd)
{
  verifyIncRange(si, -1 * (1 << 19), ones(19), ERR_ILLEGAL_IMM_RANGE, true);
  uint32_t imm20 = static_cast<uint32_t>(si & ones(20));
  uint32_t code = concat({F(opCode, 25), F(imm20, 5), F(rd, 0)});
  dd(code);
}

/* jump instructions
** encoding function
*/
uint32_t CodeGenerator::LoongarchLabelEnc(uint32_t op, const int32_t rj, const int32_t rd, int64_t labelOffset, int32_t type)
{
  uint32_t code = 0;
  switch (type)
  {
    case 1: {
      verifyIncRange(labelOffset, -1 * (1 << 17), ones(17), ERR_LABEL_IS_TOO_FAR, true);
      uint32_t imm16 = static_cast<uint32_t>((labelOffset >> 2) & ones(16));
      code = concat({F(op, 26), F(imm16, 10), F(rj, 5), F(rd, 0)});
      break;
    }
    case 2: {
      verifyIncRange(labelOffset, -1 * (1 << 22), ones(22), ERR_LABEL_IS_TOO_FAR, true);
      uint32_t imm21 = static_cast<uint32_t>((labelOffset >> 2) & ones(21));
      code = concat({F(op, 26), F(imm21&ones(16), 10), F(rj, 5), imm21 >> 16});
      break;
    }
    case 3: {
      verifyIncRange(labelOffset, -1 * (1 << 22), ones(22), ERR_LABEL_IS_TOO_FAR, true);
      uint32_t imm21 = static_cast<uint32_t>((labelOffset >> 2) & ones(21));
      code = concat({F(op, 26), F(imm21&ones(16), 10), F(1, 8), F(rj, 5), imm21 >> 16});
      break;
    }
    case 4: {
      verifyIncRange(labelOffset, -1 * (1 << 27), ones(27), ERR_LABEL_IS_TOO_FAR, true);
      uint32_t imm26 = static_cast<uint32_t>((labelOffset >> 2) & ones(26));
      code = concat({F(op, 26), F(imm26&ones(16), 10), imm26 >> 16});
      break;
    }
    case 5: { //pcaddi
      verifyIncRange(labelOffset, -1 * (1 << 21), ones(21), ERR_LABEL_IS_TOO_FAR, true);
      uint32_t imm20 = static_cast<uint32_t>((labelOffset >> 2) & ones(20));
      code = concat({F(op, 25), F(imm20, 5), F(rd, 0)});
      break;
    }
  }
  return code;
}

/* jump instructions
** b => label
*/
void CodeGenerator::LoongarchLabel(uint32_t op, const int32_t rj, const int32_t rd, const Label& label, int32_t type)
{
  auto encFunc = [&, op, rj, rd, type](int64_t labelOffset) { return LoongarchLabelEnc(op, rj, rd, labelOffset, type); };
  JmpLabel jmpL = JmpLabel(encFunc, size_);
  uint32_t code = LoongarchLabelEnc(op, rj, rd, genLabelOffset(label, jmpL), type);
  dd(code);
}

/******************** LoongArch base end *******************************/

/******************** LoongArch SIMD begin ****************************/

template <typename T> 
void CodeGenerator::LasxFormat4R(uint32_t op, uint32_t df, const T &ra, const T &rk, const T &rj, const T &rd ) {
  uint32_t code = concat({F(op, 22), F(df, 20), F(ra.getIdx(), 15), F(rk.getIdx(), 10), F(rj.getIdx(), 5), F(rd.getIdx(), 0)});
  dd(code);
}

template <typename T> 
void CodeGenerator::LasxFormatCond(uint32_t op, uint32_t df, uint32_t cond, const T &rk, const T &rj, const T &rd ) {
  uint32_t code = concat({F(op, 22), F(df, 20), F(cond, 15), F(rk.getIdx(), 10), F(rj.getIdx(), 5), F(rd.getIdx(), 0)});
  dd(code);
}

template <typename T, typename R> 
void CodeGenerator::LasxFormatI12(uint32_t op, int32_t imm, const R &rj, const T &rd ) {
  verifyIncRange(imm, -1 * (1 << 11), ones(11), ERR_ILLEGAL_IMM_RANGE, true);

  uint32_t imm12 = imm & ones(12);
  uint32_t code = concat({F(op, 22), F(imm12, 10), F(rj.getIdx(), 5), F(rd.getIdx(), 0)});
  dd(code);
}

template <typename T, typename R> 
void CodeGenerator::LasxFormatAddr(uint32_t op, uint32_t df, int32_t off, const R &rj, const T &rd ) {
  uint32_t df_off = 0;
  verifyIncRange(off, -1*(1<<11), ones(11), ERR_ILLEGAL_IMM_RANGE, true);

  switch(df) {
    case 0:  //Byte: 10|off12
    { 
      uint32_t off12 = off & ones(12);
      df_off = (0b10 << 12) | off12;
      break;
    }
    case 1:  //H: 010|off11
    { 
      uint32_t off11 = (off>>1) & ones(11);
      df_off = (0b010 << 11) | off11;
      break;
    }
    case 2:  //W: 0010|off10
    { 
      uint32_t off10 = (off>>2) & ones(10);
      df_off = (0b0010 << 10) | off10;
      break;
    }
    case 3:  //D: 00010|off9
    { 
      uint32_t off9 = (off>>3) & ones(9);
      df_off = (0b00010 << 9) | off9;
      break;
    }
  }

  uint32_t code = concat({F(op, 24), F(df_off, 10), F(rj.getIdx(), 5), F(rd.getIdx(), 0)});
  dd(code);
}

template <typename T, typename R> 
void CodeGenerator::LasxFormatI8ELM(uint32_t op, uint32_t df, uint32_t idx, int32_t imm8, const R &rj, const T &rd ) {
  uint32_t df_n = 0;

  switch(df) {
    case 0:  //Byte: 1|idx5
    { 
      verifyIncRange(idx, 0, ones(5), ERR_ILLEGAL_IMM_RANGE, false);
      verifyIncRange(imm8, -1*(1<<7), ones(7), ERR_ILLEGAL_IMM_RANGE, true);
      uint32_t idx5 = idx & ones(5);
      df_n = (0b1 << 5) | idx5;
      break;
    }
    case 1:  //H: 01|idx4
    { 
      verifyIncRange(idx, 0, ones(4), ERR_ILLEGAL_IMM_RANGE, false);
      verifyIncRange(imm8, -1*(1<<8), ones(8), ERR_ILLEGAL_IMM_RANGE, true);
      uint32_t idx4 = idx & ones(4);
      df_n = (0b1 << 4) | idx4;
      break;
    }
    case 2:  //W: 001|idx3
    { 
      verifyIncRange(idx, 0, ones(3), ERR_ILLEGAL_IMM_RANGE, false);
      verifyIncRange(imm8, -1*(1<<9), ones(9), ERR_ILLEGAL_IMM_RANGE, true);
      uint32_t idx3 = idx & ones(3);
      df_n = (0b1 << 3) | idx3;
      break;
    }
    case 3:  //D: 0001|idx2
    { 
      verifyIncRange(idx, 0, ones(2), ERR_ILLEGAL_IMM_RANGE, false);
      verifyIncRange(imm8, -1*(1<<10), ones(10), ERR_ILLEGAL_IMM_RANGE, true);
      uint32_t idx2 = idx & ones(2);
      df_n = (0b1 << 2) | idx2;
      break;
    }
  }

  uint32_t code = concat({F(op, 24),F(df_n, 18), F((imm8>>df)&ones(8), 10), F(rj.getIdx(), 5), F(rd.getIdx(), 0)});
  dd(code);
}

void CodeGenerator::LasxFormatI8VSTELM(uint32_t op, uint32_t df, uint32_t idx, int32_t imm8, const XReg &rj, const VReg &vd ) {
  uint32_t df_n = 0;

  switch(df) {
    case 0:  //Byte: 10|idx4
    {
      verifyIncRange(idx, 0, ones(4), ERR_ILLEGAL_IMM_RANGE, false);
      verifyIncRange(imm8, -1*(1<<7), ones(7), ERR_ILLEGAL_IMM_RANGE, true);
      uint32_t idx4 = idx & ones(4);
      df_n = (0b10 << 4) | idx4;
      break;
    }
    case 1:  //H: 010|idx3
    {
      verifyIncRange(idx, 0, ones(3), ERR_ILLEGAL_IMM_RANGE, false);
      verifyIncRange(imm8, -1*(1<<8), ones(8), ERR_ILLEGAL_IMM_RANGE, true);
      uint32_t idx3 = idx & ones(3);
      df_n = (0b010 << 3) | idx3;
      break;
    }
    case 2:  //W: 0010|idx2
    {
      verifyIncRange(idx, 0, ones(2), ERR_ILLEGAL_IMM_RANGE, false);
      verifyIncRange(imm8, -1*(1<<9), ones(9), ERR_ILLEGAL_IMM_RANGE, true);
      uint32_t idx2 = idx & ones(2);
      df_n = (0b0010 << 2) | idx2;
      break;
    }
    case 3:  //D: 00010|idx1
    {
      verifyIncRange(idx, 0, ones(1), ERR_ILLEGAL_IMM_RANGE, false);
      verifyIncRange(imm8, -1*(1<<10), ones(10), ERR_ILLEGAL_IMM_RANGE, true);
      uint32_t idx1 = idx & ones(1);
      df_n = (0b00010 << 1) | idx1;
      break;
    }
  }

  uint32_t code = concat({F(op, 24),F(df_n, 18), F((imm8>>df)&ones(8), 10), F(rj.getIdx(), 5), F(vd.getIdx(), 0)});
  dd(code);
}

template <typename T, typename R> 
void CodeGenerator::LasxFormat3RX(uint32_t op, const R &rk, const R &rj, const T &rd ) {
  uint32_t subOp = 0b000;
  uint32_t code = concat({F(op, 18), F(subOp, 15), F(rk.getIdx(), 10), F(rj.getIdx(), 5), F(rd.getIdx(), 0)});
  dd(code);
}

template <typename T, typename R> 
void CodeGenerator::LasxFormat3R(uint32_t op, uint32_t df, const R &rk, const T &rj, const T &rd ) {
  uint32_t code = concat({F(op, 17), F(df, 15), F(rk.getIdx(), 10), F(rj.getIdx(), 5), F(rd.getIdx(), 0)});
  dd(code);
}


template <typename T> 
void CodeGenerator::LasxFormat3RVec(uint32_t op, const T &rk, const T &rj, const T &rd ) {
  uint32_t code = concat({F(op, 15), F(rk.getIdx(), 10), F(rj.getIdx(), 5), F(rd.getIdx(), 0)});
  dd(code);
}

template <typename T, typename S, typename std::enable_if<std::is_signed<S>::value, std::nullptr_t>::type = nullptr> 
void CodeGenerator::LasxFormatI5(uint32_t op, uint32_t df, S imm5, const T &rj, const T &rd ) {
  verifyIncRange(imm5, -1*(1<<4), ones(4), ERR_ILLEGAL_IMM_RANGE, true);

  uint32_t code = concat({F(op, 17), F(df, 15), F(imm5&ones(5), 10), F(rj.getIdx(), 5), F(rd.getIdx(), 0)});
  dd(code);
}

template <typename T, typename S, typename std::enable_if<std::is_unsigned<S>::value, std::nullptr_t>::type = nullptr> 
void CodeGenerator::LasxFormatI5(uint32_t op, uint32_t df, S imm5, const T &rj, const T &rd ) {
  verifyIncRange(imm5, 0, ones(5), ERR_ILLEGAL_IMM_RANGE, false);

  uint32_t code = concat({F(op, 17), F(df, 15), F(imm5, 10), F(rj.getIdx(), 5), F(rd.getIdx(), 0)});
  dd(code);
}

template <typename T> 
void CodeGenerator::LasxFormatI5Mode(uint32_t op, uint32_t imm5, uint32_t mode, const T &rd ) {
  verifyIncRange(imm5, 0, ones(5), ERR_ILLEGAL_IMM_RANGE, false);

  uint32_t code = concat({F(op, 15), F(imm5, 10), F(mode&ones(5), 5), F(rd.getIdx(), 0)});
  dd(code);
}

template <typename T, typename R> 
void CodeGenerator::LasxFormat2R(uint32_t op, uint32_t df, const R &rj, const T &rd ) {
  uint32_t code = concat({F(op, 12), F(df, 10), F(rj.getIdx(), 5), F(rd.getIdx(), 0)});
  dd(code);
}

template <typename T> 
void CodeGenerator::LasxFormatCFR(uint32_t op, uint32_t df, const T &rj, uint32_t cd) {
  verifyIncRange(cd, 0, 7, ERR_ILLEGAL_IMM_RANGE, false);

  uint32_t miniOp = 0b00;
  uint32_t code = concat({F(op, 12), F(df, 10), F(rj.getIdx(), 5), F(miniOp, 3), F(cd, 0)});
  dd(code);
}

template <typename T> 
void CodeGenerator::LasxFormatBIT(uint32_t op, uint32_t df, uint32_t m, const T &rj, const T &rd) {
  uint32_t df_m = 0;

  switch(df) {
    case 0:  //Byte: 00001mmm
    {
      verifyIncRange(m, 0, ones(3), ERR_ILLEGAL_IMM_RANGE, false);
      uint32_t m3 = m & ones(3);
      df_m = (0b1<<3) | m3;
      break; 
    }
    case 1:  //H: 0001mmmm
    {
      verifyIncRange(m, 0, ones(4), ERR_ILLEGAL_IMM_RANGE, false);
      uint32_t m4 = m & ones(4);
      df_m = (0b1<<4) | m4;
      break; 
    }
    case 2:  //W: 001mmmmm
    {
      verifyIncRange(m, 0, ones(5), ERR_ILLEGAL_IMM_RANGE, false);
      uint32_t m5 = m & ones(5);
      df_m = (0b1<<5) | m5;
      break; 
    }
    case 3:  //D: 01mmmmmm
    {
      verifyIncRange(m, 0, ones(6), ERR_ILLEGAL_IMM_RANGE, false);
      uint32_t m6 = m & ones(6);
      df_m = (0b1<<6) | m6;
      break; 
    }
    case 4:  //Q: 1mmmmmmm
    {
      verifyIncRange(m, 0, ones(7), ERR_ILLEGAL_IMM_RANGE, false);
      uint32_t m7 = m & ones(7);
      df_m = (0b1<<7) | m7;
      break; 
    }
  }

  uint32_t code = concat({F(op, 18),F(df_m, 10), F(rj.getIdx(), 5), F(rd.getIdx(), 0)});
  dd(code);
}

template <typename T, typename R> 
void CodeGenerator::LasxFormatELM(uint32_t op, uint32_t df, uint32_t idx, const T &rj, const R &rd ) {
  uint32_t df_n = 0;

  switch(df) {
    case 0:  //Byte: 1110|idx4
    { 
      verifyIncRange(idx, 0, ones(4), ERR_ILLEGAL_IMM_RANGE, false);
      uint32_t idx4 = idx & ones(4);
      df_n = (0b1110 << 4) | idx4;
      break;
    }
    case 1:  //H: 11110|idx3
    { 
      verifyIncRange(idx, 0, ones(3), ERR_ILLEGAL_IMM_RANGE, false);
      uint32_t idx3 = idx & ones(3);
      df_n = (0b11110 << 3) | idx3;
      break;
    }
    case 2:  //W: 111110|idx2
    { 
      verifyIncRange(idx, 0, ones(2), ERR_ILLEGAL_IMM_RANGE, false);
      uint32_t idx2 = idx & ones(2);
      df_n = (0b111110 << 2) | idx2;
      break;
    }
    case 3:  //D: 1111110|idx1
    { 
      verifyIncRange(idx, 0, ones(1), ERR_ILLEGAL_IMM_RANGE, false);
      uint32_t idx1 = idx & ones(1);
      df_n = (0b1111110 << 1) | idx1;
      break;
    }
  }

  uint32_t code = concat({F(op, 18),F(df_n, 10), F(rj.getIdx(), 5), F(rd.getIdx(), 0)});
  dd(code);
}

template <typename T, typename R> 
void CodeGenerator::LasxFormatELM_1(uint32_t op, uint32_t df, uint32_t idx, const T &rj, const R &rd ) {
  uint32_t df_n = 0;

  switch(df) {
    case 2:  //W: 11110|idx3
    { 
      verifyIncRange(idx, 0, ones(3), ERR_ILLEGAL_IMM_RANGE, false);
      uint32_t idx3 = idx & ones(3);
      df_n = (0b11110 << 3) | idx3;
      break;
    }
    case 3:  //D: 111110|idx2
    { 
      verifyIncRange(idx, 0, ones(2), ERR_ILLEGAL_IMM_RANGE, false);
      uint32_t idx2 = idx & ones(2);
      df_n = (0b111110 << 2) | idx2;
      break;
    }
    default:
    {
      //ERROR
      throw Error(ERR_BAD_PARAMETER);
    }
  }

  uint32_t code = concat({F(op, 18),F(df_n, 10), F(rj.getIdx(), 5), F(rd.getIdx(), 0)});
  dd(code);
}

template <typename T> 
void CodeGenerator::LasxFormat2RSubOp(uint32_t op, uint32_t subOp, const T &rj, const T &rd ) {
  uint32_t code = concat({F(op, 18), F(subOp, 10), F(rj.getIdx(), 5), F(rd.getIdx(), 0)});
  dd(code);
}

template <typename T> 
void CodeGenerator::LasxFormatI8(uint32_t op, uint32_t imm8, const T &rj, const T &rd ) {
  verifyIncRange(imm8, 0, ones(8), ERR_ILLEGAL_IMM_RANGE, false);

  uint32_t code = concat({F(op, 18), F(imm8, 10), F(rj.getIdx(), 5), F(rd.getIdx(), 0)});
  dd(code);
}

template <typename T> 
void CodeGenerator::LasxFormatI13(uint32_t op, int32_t imm13, const T &rd ) {
  verifyIncRange(imm13, -1*(1<<12), ones(12), ERR_ILLEGAL_IMM_RANGE, true);

  uint32_t code = concat({F(op, 18), F(imm13&ones(13), 5), F(rd.getIdx(), 0)});
  dd(code);
}

/******************** LoongArch SIMD end ****************************/
