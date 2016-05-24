//
// Created by tew on 2016/5/24.
//

#ifndef DATASTRUCTURE_SORTEDLIST_H
#define DATASTRUCTURE_SORTEDLIST_H

#include "LinkList.h"

template <class elem>
class SortedList : protected LinkList<elem> {
public:
    SortedList() : LinkList<elem>() {

    }

    ~SortedList() {

    }

    bool insert(const elem &element){
        return LinkList<elem>::append(element);
    }

    using LinkList<elem>::remove;
    using LinkList<elem>::setStart;
    using LinkList<elem>::setEnd;
    using LinkList<elem>::prev;
    using LinkList<elem>::next;
    using LinkList<elem>::setPos;
    using LinkList<elem>::getValue;
    using LinkList<elem>::print;
    using LinkList<elem>::size;

};

#endif //DATASTRUCTURE_SORTEDLIST_H
