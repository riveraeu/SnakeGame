//  Created by Eugene Rivera on 12/4/15.


#include "Worm.hpp"
#include <curses.h>

Worm::Worm(int size){
    _head = 0;
    _tail = 0;
    _size = size;
    worm = new Row_Column[_size];
}

void Worm::insert(Row_Column cord){
    worm[_head] = cord;
    _head++;
    if (_head == _size)
        _head = 0;
}

void Worm::print(){
    cout << "Worm Head: ";
    if (_tail < _head)
        for (int i = _tail; i < _head; i++){
            cout << "Index :" << i;
            worm[i].print();
        }
    else{
        //wrap around print case
        for (int i = 0; i < _head; i++){
            cout << "Index :" << i;
            worm[i].print();
        }
        for (int i = (_size - 1); i >= _tail; i--){
            cout << "Index :" << i;
            worm[i].print();
        }
    }
}

int Worm::getHead(){
    if (_head == 0)
        return (_size - 1);
    else
        return (_head - 1);
}
