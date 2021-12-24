CXX=g++
CXXFLAGS=-g -Wall -Wextra -pedantic-errors -std=c++11
LIBS=-lm -pthread
EXE_FILE_NAME=main
SOURCE_FILES=*.cpp
all	:
	${CXX} ${SOURCE_FILES} ${CXXFLAGS} ${LIBS} -o ${EXE_FILE_NAME}

clean	:
	rm *.o
	rm main
