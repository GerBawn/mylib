//
// Created by tew on 2016/5/19.
//

#ifndef DATASTRUCTURE_DOUBLELINKLIST_H
#define DATASTRUCTURE_DOUBLELINKLIST_H

#include "List.h"

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

template <class elem>
class DoubleLinkList : public List<elem> {
private:
    DoubleNode<elem> *head;
    DoubleNode<elem> *tail;
    int listSize;
    DoubleNode<elem> *cur;
public:
    DoubleLinkList() {
        head = cur = nullptr;
        listSize = 0;
    }

    ~DoubleLinkList() {
        clear();
    }

    void clear() {
        DoubleNode<elem> *tmp;
        while (head != nullptr) {
            tmp = head;
            head = head->next;
            delete tmp;
        }
        head = cur = tail = nullptr;
        listSize = 0;
    }

    bool insert(const elem &, int pos = -1);

    bool append(const elem &);

    bool remove(elem &);

    void setStart() {
        cur = head;
    }

    void setEnd() {
        cur = tail;
    }

    void prev() {
        if (cur->prev == nullptr)
            return;
        cur = cur->prev;
    }

    void next() {
        if (cur->next == nullptr)
            return;
        cur = cur->next;
    }

    bool setPos(int pos) {
        if (pos >= listSize)
            return false;
        cur = head;
        for (int i = 0; i < pos; ++i) {
            cur = cur->next;
        }
    }

    elem &getValue(int pos = -1) const {
        if (pos == -1)
            return cur->element;
        if (pos >= 0 && pos < listSize) {
            DoubleNode<elem> *tmp = head;
            for (int i = 0; i < pos; ++i) {
                tmp = tmp->next;
            }
            return tmp->element;
        }
    }

    void print() const {
        DoubleNode<elem> *tmp = head;
        while (tmp) {
            std::cout<<tmp->element<<" ";
            tmp = tmp->next;
        }
        std::cout<<std::endl;
    }

    int size() const {
        return listSize;
    }
};

template <class elem>
bool DoubleLinkList<elem>::append(const elem &element) {
    if (listSize == 0) {
        head = new DoubleNode<elem>(element);
        tail = head;
    } else {
        DoubleNode<elem> *newNode = new DoubleNode<elem>(element);
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }
    ++listSize;
    return true;
}

template <class elem>
bool DoubleLinkList<elem>::insert(const elem &element, int pos) {
    if (pos > listSize)
        return false;
    if (pos == 0) {
        if (listSize == 0) {
            head = new DoubleNode<elem>(element);
        } else {
            DoubleNode<elem> *tmp = new DoubleNode<elem>(element);
            head->prev = tmp;
            tmp->next = head;
            head = tmp;
        }
        ++listSize;
    } else if (pos == listSize) {
        append(element);
    } else {
        DoubleNode<elem> *tmp = head;
        for (int i = 0; i < pos; ++i) {
            tmp = tmp->next;
        }
        DoubleNode<elem> *newNode = new DoubleNode<elem>(element);
        newNode->next = tmp;
        newNode->prev = tmp->prev;
        tmp->prev->next = newNode;
        tmp->prev = newNode;
        ++listSize;
    }
    return true;
}

template <class elem>
bool DoubleLinkList<elem>::remove(elem &element) {
    return true;
}

#endif //DATASTRUCTURE_DOUBLELINKLIST_H
