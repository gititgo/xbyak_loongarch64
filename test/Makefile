#*******************************************************************************
# Copyright 2022 LOONGSON LIMITED 
# 
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
# 
#     http://www.apache.org/licenses/LICENSE-2.0
# 
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
# *******************************************************************************/

all: test

test:
	./test_all.sh

clean:
	rm -rf *.o $(TARGET) nm.cpp nm.make*.cpp nm_frame a.asm a.out ok.lst a.lst ok_human_readable.lst x.lst\
        make_nm_lasx make_nm_loongarch make_nm_fp_loongarch make_nm_branch \
        mov_imm add_sub_imm meta_mnemonic

