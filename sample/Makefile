SRC=add.cpp add2.cpp strcat.cpp mul.cpp sub.cpp div.cpp strcmp.cpp label.cpp cpuinfo.cpp strlen.cpp strcpy.cpp strstr.cpp test.cpp bf.cpp bf_loongarch.cpp
OBJ=$(SRC:.cpp=.o)
DEP=$(SRC:.cpp=.d)
EXE=$(SRC:.cpp=.exe)
all: $(EXE)

LDFLAGS=-L ../lib -lxbyak_loongarch64
CFLAGS=-std=c++11 -g -DNDEBUG -Wall -Wextra -I ../
ifneq ($(DEBUG),1)
CFLAGS+=-O2
endif

%.o: %.cpp
	$(CXX) -c $< -o $@ $(CFLAGS) -MMD -MP -MF $(@:.o=.d)

-include $(DEP)

%.exe: %.o ../lib/libxbyak_loongarch64.a
	$(CXX) $< -o $@ $(LDFLAGS)

../lib/libxbyak_loongarch64.a:
	$(MAKE) -C ..

clean:
	rm -rf $(EXE) $(OBJ) $(DEP)

.PHONY: clean

.SECONDARY: $(OBJ)
