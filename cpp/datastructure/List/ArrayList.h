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

#endif //DATASTRUCTURE_ARRAYLIST_H
