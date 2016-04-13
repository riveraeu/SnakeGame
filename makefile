CFLAGS = g++ -g -std=c++11 -c -o

game.x: main.o freeGrid.o row_column.o worm.o getChar.o getChar.o
	g++ -g -std=c++11 -o game.x main.o freeGrid.o row_column.o worm.o getChar.o -lcurses -ltermcap

main.o: main.cpp FreeGrid.hpp
	$(CFLAGS) main.o main.cpp

freeGrid.o: FreeGrid.cpp FreeGrid.hpp Row_Column.hpp Worm.hpp getChar.hpp
	$(CFLAGS) freeGrid.o FreeGrid.cpp 

row_column.o: Row_Column.cpp Row_Column.hpp
	$(CFLAGS) row_column.o Row_Column.cpp

worm.o: Worm.cpp Worm.hpp Row_Column.hpp
	$(CFLAGS) worm.o Worm.cpp

getChar.o: getChar.cpp getChar.hpp
	$(CFLAGS) getChar.o getChar.cpp

clean:
	rm -f *.o *.x *~
 
