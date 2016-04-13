//  Created by Eugene Rivera on 12/2/15.

#ifndef FreeGrid_hpp
#define FreeGrid_hpp

#include "Row_Column.hpp"
#include "Worm.hpp"
#include <iostream>
#include <string>
#include <iomanip>
#include <curses.h>
#include "getChar.hpp"

using namespace std;

class FreeGrid {
public:
    FreeGrid(int row, int column);
    void drawGrid();
    void printGrid();
    void fillFreePool();
    void printFreePool();
    void insert(int gridRow, int gridColumn);
    void insertMunchie();
    Row_Column Move();
    void run();
    void startup(void);
    void terminate(void);
    
private:
    int _column, _row, _numCells, _numGameCells, _poolSize, _munchieValue, _munchieTotal, _score;
    int ** grid;
    Row_Column * freePool;
    Worm *worm;
    Row_Column _munchie;
    bool boolMunchie;
    
    void local_move(int gridRow, int gridColumn);
    void local_run();
};

#endif /* FreeGrid_hpp */
