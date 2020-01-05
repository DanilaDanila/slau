COMPILER=g++
I_DIR=
L_DIR=
OUTPUT=slau_solver

all: main.cpp
	$(COMPILER) main.cpp -I$(I_DIR) -L$(L_DIR) -o $(OUTPUT)
