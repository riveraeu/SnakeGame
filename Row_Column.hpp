//  Created by Eugene Rivera on 12/3/15.


#ifndef Row_column_hpp
#define Row_column_hpp

#include <iostream>

using namespace std;

class Row_Column {
public:
    Row_Column(){}
    Row_Column(int row, int column);
    int getRow()                             {return _row;}
    void setRow(int row)                     {_row = row;}
    int getColumn()                          {return _column;}
    void setColumn(int column)               {_column = column;}
    void print()                             {cout << "Row: " << _row << " Column: " << _column << endl;}
    
private:
    int _row, _column;
};

#endif /* Row_column_hpp */
