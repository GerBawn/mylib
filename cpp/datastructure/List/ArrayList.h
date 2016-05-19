//
// Created by tew on 2016/5/17.
//

#ifndef DATASTRUCTURE_ARRAYLIST_H
#define DATASTRUCTURE_ARRAYLIST_H

#include "List.h"

template <class elem>
class ArrayList : public List<elem> {
private:
    int maxSize;
    int listSize;
    elem *listArray;
    int cur;
public:
    ArrayList(int size = 10);

    ~ArrayList() {
        delete[] listArray;
    }

    void clear() {
        delete[] listArray;
        listSize = 0;
        listArray = new elem[maxSize];
    }

    bool insert(const elem &value, int pos = -1);

    bool append(const elem &);

    bool remove(elem &);

    void setStart() {
        cur = 0;
    }

    void setEnd() {
        cur = listSize - 1;
    }

    void prev() {
        if (cur > 0)
            cur--;
    }

    void next() {
        if (cur < listSize - 1)
            cur++;
    }

    bool setPos(int pos) {
        cur = pos;
    }

    elem &getValue(int pos) const {
        if (pos >= 0 && pos < listSize)
            return listArray[pos];
    }

    void print() const;

    int size() const {
        return listSize;
    }

private:
    bool moveWhenOverflow();

};

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
    for (int i = listSize; i > pos; --i) {
        listArray[i] = listArray[i - 1];
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

#endif //DATASTRUCTURE_ARRAYLIST_H
