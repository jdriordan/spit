CC = gcc

CFLAGS  = -Wextra -Wall -std=c99 #-fdiagnostics-color=always -time

GCCFLAGS   = -Wpedantic 
CLANGFLAGS = -Weverything

GCCFAST	  = -Ofast -march=native -flto
CLANGFAST = -O4 #requires gold linker
INTELFAST = -fast -opt-prefetch -unroll-aggressive -m64

PARFLAGS= -fopenmp
LIBS	= -lm -lgsl
BLAS	= -lgslcblas

TARGET 	= spit

SRCDIR  = src
SOURCES = $(wildcard $(SRCDIR)/*.c)

OBJDIR	= obj
OBJECTS	= $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

RM 	= rm -fv 

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(TARGET) $(LIBS) 

$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

gcc: CFLAGS+=$(GCCFLAGS)
gcc: LIBS+=$(BLAS)
gcc: $(TARGET)

gccfast: CFLAGS+=$(GCCFAST)
gccfast: gcc

par: CFLAGS+=$(PARFLAGS)
par: fast

clang: CC=clang 
clang: LIBS+=$(BLAS)
clang: CFLAGS+=$(CLANGFLAGS)
clang: $(TARGET)

clangfast: CFLAGS+=$(CLANGFAST)
clangfast: clang

intel: CC=icc
intel: LIBS+=$(BLAS)
intel: $(TARGET)

intelfast: CFLAGS+=$(INTELFAST)
intelfast: intel

intelpar: CFLAGS+=$(PARFLAGS)
intelpar: intelfast

clean:
	for i in src obj; do $(RM) $$i/*.o $$i/*.gch; done
	$(RM) $(TARGET)

