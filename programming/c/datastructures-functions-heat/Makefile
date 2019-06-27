ifeq ($(COMP),)
COMP=gnu
endif

ifeq ($(COMP),cray)
CC=cc
CCFLAGS=-O3 -I/appl/opt/libpng/include
LIBS=-L/appl/opt/libpng/lib -lpng -lz
endif

ifeq ($(COMP),gnu)
CC=cc
#CCFLAGS=-O3 -Wall
CCFLAGS=-O3 -I/opt/local/include/libpng16
LIBS=-L/opt/local/lib -lpng
endif

EXE=laplacian
OBJS=pngwriter.o laplacian.o

all: $(EXE)

pngwriter.o: pngwriter.c pngwriter.h
laplacian.o: laplacian.c

$(EXE): $(OBJS)
	$(CC) $(CCFLAGS) $(OBJS) -o $@ $(LIBS)

%.o: %.c
	$(CC) $(CCFLAGS) -c $< -o $@

clean:
	-/bin/rm -f $(EXE) a.out *.o *.png
