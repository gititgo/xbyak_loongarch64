#*******************************************************************************
# Copyright 2021 LOONGSON LIMITED
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
#*******************************************************************************

file(GLOB SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/xbyak_loongarch_impl.cpp
    )

set(OBJ_LIB ${LIB_NAME}_cpu_loongarch_xbyak_loongarch)
add_library(${OBJ_LIB} OBJECT ${SOURCES})

target_include_directories(
    ${OBJ_LIB}
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/xbyak_loongarch
)

set_property(GLOBAL APPEND PROPERTY DNNL_LIB_DEPS
    $<TARGET_OBJECTS:${OBJ_LIB}>)
