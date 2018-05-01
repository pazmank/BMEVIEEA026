CC = g++
#CC = icc

#CFLAGS = -Wall -g -std=c++11
CFLAGS = -std=c++11

OUT = test_program

SRC = main.cpp\
	vect.cpp\
	mat.cpp
		
OBJ = $(SRC:.cpp=.o)

.cpp.o:
	$(CC) -c $(CFLAGS) $<
	
test_program: $(OBJ)
	$(CC) $^ -o $@
	
all: test_program

clean:
	rm $(OBJ) $(OUT)
