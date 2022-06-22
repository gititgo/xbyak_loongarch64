[![Build Status]()]()

# Xbyak_loongarch64 ; JIT assembler for LoongArch CPUs by C++

## Abstract

Xbyak_loongarch64 is C++ header files which enables run-time assemble coding with the LoongArch instruction set architecture.
Xbyak_loongarch64 is based on Xbyak_aarch64 developed for aarch64 CPUs by fujitsu.

## Feature

* GNU assembler like syntax.
* Fully support LASX instructions.

### Requirement

Xbyak_loongarch64 uses no external library and it is written as standard C++ header files 
so that we believe Xbyak_loongarch64 works various environment with various compilers.

### News
- 

### Supported Compilers

Almost C++11 or later compilers for loongarch such as g++, clang++.

## Install

The command `make` builds `lib/libxbyak_loongarch64.a`.

`make install` installs headers and a library into `/usr/local/` (default path).
Or add the location of the `xbyak_loongarch64` directory to your compiler's include and link paths.

### Execution environment

You can execute programs using xbyak_loongarch64 on systems running on LoongArch CPUs.

## How to make lib

```
make
```
makes `lib/libxbyak_loongarch64.a`.

## How to use Xbyak_loongarch64

Inherit `Xbyak_loongarch64::CodeGenerator` class and make the class method.
Make an instance of the class and get the function
pointer by calling `getCode()` and call it.
The following example 1) generates a JIT-ed function which simply adds two integer values passed as arguments and returns an integer value as a result,
and 2) calls the function. This example outputs "7" to STDOUT.

compile options:
- `-I <xbyak_loongarch dir>/xbyak_loongarch64`.
- `-L <xbyak_loongarch dir>/lib -lxbyak_loongarch64`.

```
#include "xbyak_loongarch64.h"
using namespace Xbyak_loongarch64;
class Generator : public CodeGenerator {
public:
  Generator() {
    Label L1, L2;
    addi_d(t0, zero, 13);
    L(L1);
    add_d(a0, a1, a0);
    bge(a0, t0, L2);
    addi_d(a1, a1, 1);
    b(L1);
    L(L2);
    jirl(zero, ra, 0);
  }
};
int main() {
  Generator gen;
  gen.ready();
  auto f = gen.getCode<int (*)(int, int)>();
  std::cout << f(3, 4) << std::endl;
  return 0;
}
```

## Syntax
Synatx is similar to "AS" (GNU assembler).
Each LoongArch instruction is correspond to each function written in "xbyak_loongarch64_mnemonic.h", we call it a **mnemonic function**.
Please refer files in sample/mnemonic_syntax directory for usage of mnemonic functions.
The below example shows correspondence between "AS" syntax and Xbyak_loongarch64 mnemonic functions.

```
"AS"                  Xbyak_loongarch64
add.d  v0, t0, t1  --> add_d (v0, t0, t1);
addi.d v1, a0, 7   --> addi_d(v1, a0, 7);
nop                --> nop();
```

### Mnemonic functions
Each **mnemonic function** corresponds to one LoongArch instruction.
Function name represents corresponding mnemonic of instruction.
Because **"and", "or"** are reserved keywords C++ and **"."** can't be used in C++ function name,
the following special cases are exist.

|Mnemonic of instruction|Name of **mnemonic funciton**|
|----|----|
|and|and_|
|or|or_|

### Operand
This section explains operands, which are given to mnemonic functions as their arguments.

#### General purpose registers

As general purpose registers,
the following table shows example of mnemonic functions' arguments ("Instance name" column).

|Instance name|C++ class name|Remarks|
|----|----|----|
|zero, ra, tp, sp, a0,...,s8|XReg|64-bit general purpose registers|

You can also use your original instance as mnemonic functions argumetns.
Please refer constructor of "C++ class name" in Xbyak_loongarch64 files.

```
XReg dstReg(4);
XReg srcReg0(5);
XReg srcReg1(6);

add.d(dstReg, srcReg0, srcReg1);  <--- (1)
add.d(a0, a1, a2);                <--- Output is same JIT code of (1)
```

##### SIMD/Floating point registers as scalar registers

As SIMD/Floating point registers with scalar use, 
the following table shows example of mnemonic functions' arguments ("Instance name" column).

|Instance name|C++ class name|Remarks|
|----|----|----|
|vr0, vr1, ..., vr31|VReg|128-bit scalar registers|
|xr0, xr1, ..., xr31|XVReg|256-bit scalar registers|

You can also use your original instance as mnemonic functions argumetns.
Please refer constructor of "C++ class name" in Xbyak_loongarch64 files.

```
XVReg dstReg(0);
XVReg srcReg1(1);
XVReg srcReg2(2);

xvadd.w(xr0, xr1, xr2);       <--- (1)
xvadd.w(dstReg, srcReg1, srcReg2);   <--- Output is same JIT code of (1)

```

### Immediate values

You can use immediate values for arguments of mnemonic functions in the form that C++ syntax allows,
such as, "10", "-128", "0xFF", "1<<32", "3.5", etc.

Please care for range of values.
For example, "ADDI.D" instruction can receive signed 12-bit value
so that you have to ensure that the value passed to mnemonic function is inside the range.
Mnemonic functions of Xbyak_loongarch64 checks immediate values at runtime, 
and throws exception if it detects range over.

```
void genAddFunc() {
     int imm = 1<<16;
     addi_d(v0, a0, imm);    <--- This mnemonic function throws exception at runtime.
     jirl(zero, ra, 0);
}
```

Some immediate values may not decided at coding time but runtime.
You should check the immediate values and handle them.

```
void gen_Summation_From_One_To_Parameter_Func(unsigned int N) {

    if(N < (1<<11)) {
        for(int i=0; i<N; i++) {
            addi_d(v0, a0, N);
        }
        jirl(zero, ra, 0);
    } else {
        printf("Invalid parameter N=%d\n", N);
        printf("This function supports less than 2048.\n");
    }
}
```    

## Label

You can use "Label" to direct where branch instruction jump to.
The following example shows how to use "Label".

```
Label L1;           // (1), instance of Label class
 
add_d(t4, t0, zero); 
add_d(t3, zero, zero); 
addi_d(t0, t1, 0); 
L(L1);              // (2), "L" function registers JIT code address of this position to label L1.
add_d(t0, t0, t4); 
addi_d(t3, t3, 1); 
bge(t2, t3, L1);    // (3), set destination of branch instruction to the address stored in L1.
```

1. Prepare Label class instance.
1. Call the L function to register destination address to the instance.
1. Pass the instance to mnemonic functions correspond to branch instructions.

You can copy the address stored in "Label" instance by using `assignL` function.

```
Label L1,L2,L3; 
....
L(L1);               // JIT code address of this position is stored to L1.
....
L(L2);               // JIT code address of this position is stored to L1.
....
if (flag) { 
assignL(L3,L1);      // The address stored in L1 is copied to L3.
} else { 
assignL(L3,L2);      // The address stored in L1 is copied to L3.
} 
b(L3);               // If flag == true, branch destination is L1, otherwise L2.
```



## Code size
The default max size of JIT-ed code is 4096 bytes.
Specify the size in constructor of `CodeGenerator()` if necessary.

```
class Quantize : public Xbyak_loongarch64::CodeGenerator {
public:
  Quantize()
    : CodeGenerator(8192)
  {
  }
  ...
};
```

## User allocated memory

You can make JIT-ed code on prepared memory.

Call `setProtectModeRE` yourself to change memory mode if using the prepared memory.

```
uint8_t alignas(4096) buf[8192]; // C++11 or later

struct Code : Xbyak_loongarch64::CodeGenerator {
    Code() : Xbyak_loongarch64::CodeGenerator(sizeof(buf), buf)
    {
        addi_d(v0, zero, 123);
        jirl(zero, ra, 0);
    }
};

int main()
{
    Code c;
    c.setProtectModeRE(); // set memory to Read/Exec
    printf("%d\n", c.getCode<int(*)()>()());
}
```

**Note**: See [sample/test.cpp](sample/test.cpp).

### AutoGrow

If `AutoGrow` is specified in a constructor of `CodeGenerator`,
the memory region for JIT-ed code is automatically extended if needed.

Call `ready()` or `readyRE()` before calling `getCode()` to fix jump address.
```
struct Code : Xbyak_loongarch64::CodeGenerator {
  Code()
    : Xbyak_loongarch64::CodeGenerator(<default memory size>, Xbyak_loongarch64::AutoGrow)
  {
     ...
  }
};
Code c;
// generate code for jit
c.ready(); // mode = Read/Write/Exec
```

**Note**:
* Don't use the address returned by `getCurr()` before calling `ready()` because it may be invalid address.

### Read/Exec mode
Xbyak_loongarch64 set Read/Write/Exec mode to memory to run JIT-ed code.
If you want to use Read/Exec mode for security, then specify `DontSetProtectRWE` for `CodeGenerator` and
call `setProtectModeRE()` after generating JIT-ed code.

```
struct Code : Xbyak_loongarch64::CodeGenerator {
    Code()
        : Xbyak_loongarch64::CodeGenerator(4096, Xbyak_loongarch64::DontSetProtectRWE)
    {
        addi_d(v0, zero, 123);
        jirl(zero, ra, 0);
    }
};

Code c;
c.setProtectModeRE();
```

## Sample
To be written...

* [add.cpp](sample/add.cpp) ; tiny sample
* [label.cpp](sample/label.cpp) ; label sample

## License

Copyright LOONGSON LIMITED 2021-2022

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.

## Notice

* Loongson is a registered trademark of Loongson Limited (or its subsidiaries) in the China and/or elsewhere.


## Acknowledgement

We are grateful to fujitsu for release Xbyak_aarch64 as an open source software.

## History

|Date|Version|Remarks|
|----|----|----|
|June 10, 2022|0.0.0|First public release version.|


## Copyright

Copyright LOONGSON LIMITED 2021-2022
