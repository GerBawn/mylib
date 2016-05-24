//
// Created by tew on 2016/5/24.
//

#ifndef DATASTRUCTURE_STACK_H
#define DATASTRUCTURE_STACK_H

#include "../Node.h"

template <class elem>
class Stack {
private:
    int stackSize;
    Node<elem> *top;
public:
    Stack() {
        stackSize = 0;
        top = nullptr;
    }

    ~Stack() {

    }

    bool push(const elem &element) {
        if (stackSize == 0) {
            top = new Node<elem>(element);
        } else {
            Node<elem> *tmp = new Node<elem>(element, top);
            top = tmp;
        }
        ++stackSize;
        return true;
    }

    bool pop(elem &element) {
        if (stackSize == 0)
            return false;
        element = top->element;
        top = top->next;
        --stackSize;
        return true;
    }

    int size() {
        return stackSize;
    }

    bool flush() {
        Node<elem> *tmp;
        while (top) {
            tmp = top;
            top = top->next;
            delete tmp;
        }
        stackSize = 0;
    }

    void print() {
        Node<elem> *tmp = top;
        while (tmp) {
            std::cout<<tmp->element<<" ";
            tmp = tmp->next;
        }
        std::cout<<std::endl;
    }
};

#endif //DATASTRUCTURE_STACK_H
