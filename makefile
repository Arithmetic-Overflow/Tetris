CPP = g++
FLAGS = -Wall -Werror
OBJ = main.o
PROGRAMNAME = tetmatch

main : $(OBJ)
	$(CPP) $(OBJ) -o $(PROGRAMNAME)

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