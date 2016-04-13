//  Created by Eugene Rivera on 12/4/15.


#ifndef Worm_hpp
#define Worm_hpp

#include <iostream>
#include "Row_Column.hpp"

using namespace std;

class Worm {
public:
    Worm(int size);
    int getHead();
    void setHead(int head)          {_head = head;}
    int getTail()                   {return _tail;}
    void setTail(int tail)          {_tail = tail;}
    Row_Column * getWorm()          {return worm;}
    void insert(Row_Column cord);
    void print();

    
private:
    int _head, _tail, _size;
    Row_Column * worm;
};

#endif /* Worm_hpp */
