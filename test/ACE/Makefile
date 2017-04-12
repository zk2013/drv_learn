FUCK_ROOT = ../
CXX         = ${CROSS_COMPILE}g++
INCLUDE    = -I${FUCK_ROOT}linux

CXXFLAGS     = -g -O0 ${INCLUDE} 

#USE_STATIC_LINK
ifdef USE_STATIC_LINK
LIBS = -lACE -static -lpthread -ldl
else
LIBS = -lACE 
endif

%.o: %.cpp
	${CXX} ${CXXFLAGS} -c $< -o $@

PFPROGS =  ACE-1

TARGETS = ${PFPROGS}
all: ${TARGETS}
clean:
	@rm -f ${TARGETS} *.o *~

ACE-1:ACE-1.o
	${CXX} ${CXXFLAGS} $< ${LIBS} -o $@
