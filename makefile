# !/bin/make

CPP = g++
FLAGS = -Wall -Werror
OBJ = main.o
PROGRAMNAME = tetmatch

main : $(OBJ)
	$(CPP) $(OBJ) -o $(PROGRAMNAME) -lsfml-graphics -lsfml-window -lsfml-system

%.o : %.cpp
	$(CPP) $(FLAGS) -c $<

clean:
	rm -fv *.o $(PROGRAMNAME)

run:
	./$(PROGRAMNAME)

rerun:
	make clean
	make
	make run