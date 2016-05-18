#include <iostream>
#include "ArrayList.h"

template <class elem>
ArrayList<elem>::ArrayList(int size) {
    maxSize = size;
    listSize = 0;
    listArray = new elem[maxSize];
    cur = 0;
}

template <class elem>
bool ArrayList<elem>::insert(const elem &value, int pos) {
    if (pos == -1)
        pos = cur;
    if (listSize >= maxSize) {
        if (!moveWhenOverflow()) {
            return false;
        }
    }
    for (int i = pos; i < listSize; ++i) {
        listArray[i + 1] = listArray[i];
    }
    listArray[pos] = value;
    ++listSize;
}

template <class elem>
bool ArrayList<elem>::append(const elem &value) {
    if (listSize > maxSize) {
        if(!moveWhenOverflow()){
            return false;
        }
    }
    listArray[listSize++] = value;
    return true;
}

template <class elem>
void ArrayList<elem>::print() const{
    for (int i = 0; i < listSize; ++i) {
        std::cout<<listArray[i]<<" ";
    }
    std::cout<<std::endl;
}

template <class elem>
bool ArrayList<elem>::remove(elem& value){

}

template <class elem>
bool ArrayList<elem>::moveWhenOverflow() {
    elem *temp = new elem[2 * maxSize];
    if (temp == NULL)
        return false;
    maxSize *= 2;
    for (int i = 0; i < listSize; i++) {
        temp[i] = listArray[i];
    }
    delete[] listArray;
    listArray = temp;
    return true;
}