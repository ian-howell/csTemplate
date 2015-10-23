OBJS = csTemplate.cpp

CC = g++

OBJ_NAME = csTemplate

all:
	${CC} ${OBJS} -o ${OBJ_NAME}

run:
	./${OBJ_NAME}

clean:
	rm ${OBJ_NAME}
