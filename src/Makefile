FAMILY=-mpic14
MCU=-p12f675
CC=sdcc
LD=sdcc
CFLAGS=-I. -I/usr/local/share/sdcc/non-free/include
TARGET=bingo

SRCS = bingo.c

all: build doxygen run

build:
	${CC} --use-non-free ${FAMILY} ${MCU} ${CFLAGS} -o ${TARGET} ${SRCS}

doxygen:
	doxygen -g
	doxygen

run:
	open html/index.html

clean:
	rm -f *.c~ *.h~ *.o *.elf *.hex *.asm *.cod *.lst
	rm -rf html latex Doxyfile
