//  Created by Eugene Rivera on 12/2/15.


#include "FreeGrid.hpp"

FreeGrid::FreeGrid(int row, int column){
    _column = column;
    _row = row;
    _numCells = (_row * _column);
    _numGameCells = (_row - 2) * (_column - 2);
    _poolSize = _munchieValue = _munchieTotal = _score = 0;
    freePool = new Row_Column[_numGameCells];
    boolMunchie = false;
    
    grid = new int*[_row];
    for (int i = 0; i < _row; ++i)
        grid[i] = new int[_column];
    drawGrid();
    fillFreePool();
    worm = new Worm(_numGameCells);
}

void FreeGrid::drawGrid(){
    // draw walls and freepool indexs in the grid
    int gameCellCounter = 0;
    int gameIndexCounter = _column+1;
    // for loop to write the walls (-1) for the grid
    startup();
    for (int i = 0; i < _column; i++){
        mvaddch(0, i, '*');
        mvaddch((_row - 1), i,'*');
        //first row of grid
        grid[0][i] = -1;
        //last row of grid
        grid[_row - 1][i] = -1;
    }
    for (int i = 0; i < _row; i++){
        mvaddch(i, 0, '*');
        mvaddch(i, (_column - 1), '*');
        //first column of grid
        grid[i][0] = -1;
        //last column of grid
        grid[i][_column - 1] = -1;
    }
    //loop to write the contents of the grid (0-n)
    // starting with 0 in cell (1, 1)
    int count = 0;
    for (int j = 1; j < (_row - 1); j++){
        for (int i = 1; i < (_column - 1); i++){
            grid[j][i] = count;
            count++;
        }
    }
}

void FreeGrid::printGrid(){
    // prints grid
    for (int j = 0; j < _row; j++){
        for (int i = 0; i < _column; i++)
            cout << left << setw(4) << grid[j][i] << " ";
        cout << endl;
    }
}

void FreeGrid::fillFreePool(){
    // fills the free pool with rowcol objests
    int index = 0;
    for (int j = 1; j <= (_row - 2); j++){
        for (int i = 1; i <= (_column - 2); i++){
            freePool[index] = Row_Column(j, i);
            index++;
            _poolSize++;
        }
    }
}

void FreeGrid::printFreePool(){
    // prints contents of freepool
    cout << "pool size: " << _poolSize << endl;
    for (int i = 0; i < _poolSize; i++){
        cout << "Index: " << i << " ";
        freePool[i].print();
    }
}

void FreeGrid::insert(int gridRow, int gridColumn){
    // insert the head and parts of the worm
    // arguments are the row/col position
    // sets the index for the cell you are inseting into
    int index = grid[gridRow][gridColumn];
    // create a new rowcol object to be added to the worm
    Row_Column g = Row_Column(gridRow, gridColumn);
    // sets target cell in the grid to -1 (were the worm will be inserted)
    grid[gridRow][gridColumn] = -1;
    // sets freepool at index to last element of freepool array
    freePool[index] = freePool[_poolSize - 1];
    //decrement free pool size
    _poolSize -= 1;
    //gets rowcol from new freepool element at index
    gridRow = freePool[index].getRow();
    gridColumn = freePool[index].getColumn();
    // sets cell at updated rowcol to index
    grid[gridRow][gridColumn] = index;
    // inserts rowcol to worm
    worm->insert(g);
}

void FreeGrid::insertMunchie(){
    // similar to insert for worm, but creates a munchie on the grid with a random value 1-9
    // and draws it on the scree
    int index = rand () % (_poolSize - 1);
    int mValue = rand () % 9 + 1;
    int gridRow = freePool[index].getRow();
    int gridColumn = freePool[index].getColumn();
    _munchie = Row_Column(gridRow, gridColumn);
    _munchieValue = mValue;
    mvaddch(gridRow, gridColumn, '0'+_munchieValue);
   }

Row_Column FreeGrid::Move(){
    // waits for the user to enter a vaild key ( w, a , s, d)
    char userMove = ' ';
    while (userMove == ' ')
        userMove = get_char();
    // moves the worm, based on parameter userMove
    // calls local move to update the data structures for moving the worm
    // first gets rowCol of the head to pass to local_move
    int gridRow = worm->getWorm()[worm->getHead()].getRow();
    int gridColumn = worm->getWorm()[worm->getHead()].getColumn();
    //cout << "head row: " << gridRow << " column: " << gridColumn << endl;
    switch (userMove){
    case 'a':
            gridColumn -= 1;
            return Row_Column(gridRow, gridColumn);
    case 'd':
            gridColumn += 1;
            return Row_Column(gridRow, gridColumn);
    case 's':
            gridRow += 1;
            return Row_Column(gridRow, gridColumn);
    case 'w':
            gridRow -= 1;
            return Row_Column(gridRow, gridColumn);
    }
}

void FreeGrid::local_move(int gridRow, int gridColumn){
    // checks if move hits a wall or part of the worm
    if (grid[gridRow][gridColumn] != -1){
        // create new rowcol object called g with the cordinates of the cell the worm is moving to
        Row_Column g = Row_Column(gridRow, gridColumn);
        // sets oldIndex to cell we are moving into
        int oldIndex = grid[gridRow][gridColumn];
        int headRow = worm->getWorm()[worm->getHead()].getRow();
        int headColumn = worm->getWorm()[worm->getHead()].getColumn();
        // sets cell worm is moving into to -1
        grid[gridRow][gridColumn] = -1;
        // inserts new cell into worm array
        worm->insert(g);
        if (!(boolMunchie)){
            // sets variables for worm's tail location
            int tailRow = worm->getWorm()[worm->getTail()].getRow();
            int tailColumn = worm->getWorm()[worm->getTail()].getColumn();
            // sets cell tail used to be in back to the correct index
            grid[tailRow][tailColumn] = oldIndex;
            // sets element of freepool at index to the cell we just updated to correct cordinates
            freePool[oldIndex] = Row_Column (tailRow, tailColumn);
            if (worm->getTail() == (_numGameCells - 1))
                worm->setTail(0);
            else
                worm->setTail(worm->getTail() + 1);
            //draws worm after moving
            mvaddch(tailRow, tailColumn, ' ');
            mvaddch(headRow, headColumn, 'o');
            mvaddch(gridRow, gridColumn, '@');
        }else{
            // move condition after eating a munchie
            int Row = freePool[_poolSize - 1].getRow();
            int Column = freePool[_poolSize - 1].getColumn();
            grid[Row][Column] = oldIndex;
            freePool[oldIndex] = Row_Column(Row, Column);
            _poolSize--;
            mvaddch(headRow, headColumn, 'o');
            mvaddch(gridRow, gridColumn, '@');
        }
    }else{
        terminate();
        cout << "You hit a wall or part of the worm, your score was: " << _score << endl;
        exit(1);
    }
    refresh();
}

void FreeGrid::run(){
    // keeps the program running till you win or lose
    refresh();
    while (true){
        local_run();
    }
}

void FreeGrid::local_run(){
    // takes care of move, win condition, and munchie eating
    Row_Column g = Move();
    int gridRow = g.getRow();
    int gridColumn = g.getColumn();
    local_move(gridRow, gridColumn);
    if (_poolSize == 1){
        terminate();
        cout << "You won! your score was: " << _score << endl;
        exit(1);
    }
    if (gridRow == _munchie.getRow() && gridColumn == _munchie.getColumn()){
        // update score and munchieTotal
        _score += _munchieValue;
        _munchieTotal += _munchieValue;
        // insert new munchie
        insertMunchie();
        // set bool value for muchie to ture
        boolMunchie = true;
        // draws the updated score
        mvaddch((_row + 1), (_column + 7), ' ');
        mvprintw((_row + 1), (_column + 7), "%d", _score);
        while (_munchieTotal > 0){
            // loop for not moving the tail after eating munchie
            local_run();
            _munchieTotal--;
        }
        // set bool function for munchie to false;
        boolMunchie = false;
    }
}

void FreeGrid::startup( void ){
    initscr();	 /* activate the curses */
    curs_set(0);/* do not display the cursor */
    clear();	 /* clear the screen that curses provides */
    noecho();	 /* prevent the input chars to be echoed to the screen */
    cbreak();	 /* change the stty so that characters are delivered to the
                  program as they are typed--no need to hit the return key!*/
}

void FreeGrid::terminate( void ){
    mvcur( 0, COLS - 1, LINES - 1, 0 );
    clear();
    refresh();
    endwin();
}

