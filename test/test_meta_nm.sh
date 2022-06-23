#!/bin/sh
TEST_FILE=${1}
SRC=${TEST_FILE}.cpp
GPP=g++

xbyak="../lib/libxbyak_loongarch64.a"
CFLAGS="-std=c++11 -g -DNDEBUG -Wall -Wextra -I ../"

dumpOK () {
    echo "##########################################"
    echo "# Test OK :-)"
    echo "##########################################"
}    

dumpNG () {
    echo "##########################################"
    echo "# $1"
    echo "# Test NG :-p"
    echo "##########################################"
} 
   
# Make binary
#echo ${GPP} ${CFLAGS} -o ${TEST_FILE} ${SRC} ${xbyak}
${GPP} ${CFLAGS} -o ${TEST_FILE} ${SRC} ${xbyak}

if [ $? != 0 ] ; then
    dumpNG "Compiling binary for generating test source file."
    exit 1
fi

#Run test
./${TEST_FILE}




