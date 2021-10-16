CCPP = g++
CFLAGS = -g -Wall
TARGET = gap-gale-shapley.out

SRC = src/main.cpp

all: ${TARGET}

${TARGET}: ${SRC}
	${CCPP} ${CFLAGS} ${SRC} -o ${TARGET}
