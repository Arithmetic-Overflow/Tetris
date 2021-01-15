CPP = g++
FLAGS = -Wall -Werror -g
OBJ = main.o tetris.o matrix.o piece.o
PROGRAMNAME = tetris

main : $(OBJ)
	$(CPP) $(OBJ) -o $(PROGRAMNAME) -lsfml-graphics -lsfml-window -lsfml-system

%.o : %.cpp
	$(CPP) $(FLAGS) -c $<

exportDisplay:
	export DISPLAY=:0

clean:
	rm -fv *.o $(PROGRAMNAME)

run:
	./$(PROGRAMNAME)

rerun:
	make clean
	make
	make run