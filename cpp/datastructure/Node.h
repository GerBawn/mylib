//
// Created by tew on 2016/5/24.
//

#ifndef DATASTRUCTURE_NODE_H
#define DATASTRUCTURE_NODE_H

template <class elem>
class Node {
public:
    elem element;
    Node<elem> *next;

    Node(const elem &element, Node *next = nullptr) {
        this->element = element;
        this->next = next;
    }

    Node(Node *next = nullptr) {
        this->next = next;
    }
};

#endif //DATASTRUCTURE_NODE_H
