COMPILER=g++
I_DIR=
L_DIR=
OUTPUT=slau_solver

all: main.o fract.o vector.hpp vector.cpp 
	$(COMPILER) *.o -std=c++17 -I$(I_DIR) -L$(L_DIR) -o $(OUTPUT)

main.o: main.cpp
	$(COMPILER) -c main.cpp

fract.o: fract.hpp fract.cpp
	$(COMPILER) -c fract.cpp -std=c++17

clean:
	rm *.o $(OUTPUT)
