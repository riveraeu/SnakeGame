//  Created by Eugene Rivera on 12/2/15.


#include <iostream>
#include "FreeGrid.hpp"
#include <curses.h>
#include <stdlib.h>

using namespace std;

int main (int argc, char *argv[]) {
    int column;
    int row;
    if (argc == 3){
        row = atoi(argv[1]);
        column = atoi(argv[2]);
    }
    else{
        cout << "Please enter the row (10-25) and column(10-80) number after the executable" << endl;
        exit(1);
    }
    int numGameCells = (row - 2) * (column - 2);
    
    //creates grid, freepool, and worm data structures
    FreeGrid * grid = new FreeGrid(row, column);
    
    //sets cordinates for tail of worm to be inserted
    int gridRow = row/2;
    int gridColumn;
    if (column < 15)
        gridColumn = 1;
    else
        gridColumn = (column/2) -7;
    
    //writes first 8 segments of the worm (head included)
    for (int i = 0; i < 7; i++){
        mvaddch(gridRow, gridColumn, 'o');
        grid->insert(gridRow, gridColumn);
        gridColumn += 1;
    }
    mvaddch(gridRow, gridColumn, '@');
    mvaddstr((row + 1), 0, "Worm");
    mvaddstr((row + 1), column, "Score: 0");
    grid->insert(gridRow, gridColumn);
    // inserts munchie to grid
    grid->insertMunchie();
    grid->run();
    return 0;
}
