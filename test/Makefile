FUCK_ROOT = ../
CC         = ${CROSS_COMPILE}gcc
INCLUDE    = -I${FUCK_ROOT}linux

CFLAGS     = -g -O0 ${INCLUDE} 
#LIBS

%.o: %.c
	${CC} ${CFLAGS} -c $< -o $@

PFPROGS =  fctest

TARGETS = ${PFPROGS}
all: ${TARGETS}
clean:
	@rm -f ${TARGETS} *.o *~

fctest:fctest.o
	${CC} ${CFLAGS} fctest.o ${LIBS} -o $@
