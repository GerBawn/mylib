//
// Created by tew on 2016/5/24.
//

#ifndef DATASTRUCTURE_DOUBLENODE_H
#define DATASTRUCTURE_DOUBLENODE_H

template <class elem>
class DoubleNode {
public:
    elem element;
    DoubleNode *prev;
    DoubleNode *next;

    DoubleNode(const elem &element, DoubleNode *prev = nullptr, DoubleNode *next = nullptr) {
        this->element = element;
        this->prev = prev;
        this->next = next;
    }

    DoubleNode(DoubleNode *prev = nullptr, DoubleNode *next = nullptr) {
        this->prev = prev;
        this->next = next;
    }
};

#endif //DATASTRUCTURE_DOUBLENODE_H
