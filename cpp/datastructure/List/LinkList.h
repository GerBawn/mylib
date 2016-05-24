//
// Created by tew on 2016/5/18.
//

#ifndef DATASTRUCTURE_LINKLIST_H
#define DATASTRUCTURE_LINKLIST_H

#include "List.h"
#include "../Node.h"

template <class elem>
class LinkList : public List<elem> {
protected:
    Node<elem> *head;
    int listSize;
    Node<elem> *cur;
public:
    LinkList() {
        head = cur = nullptr;
        listSize = 0;
    }

    ~LinkList() {
        clear();
    }

    void clear() {
        Node<elem> *tmp;
        while (head != nullptr) {
            tmp = head;
            head = head->next;
            delete tmp;
        }
        head = cur = nullptr;
        listSize = 0;
    }

    bool insert(const elem &, int pos = -1);

    bool append(const elem &);

    bool remove(elem &);

    void setStart() {
        cur = head;
    }

    void setEnd() {
        while (cur->next) {
            cur = cur->next;
        }
    }

    void prev() {
        Node<elem> *tmp = head;
        if (cur == head)
            return;
        while (tmp->next != cur) {
            tmp = tmp->next;
        }
        cur = tmp;
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
            Node<elem> *tmp = head;
            for (int i = 0; i < pos; ++i) {
                tmp = tmp->next;
            }
            return tmp->element;
        }
    }

    void print() const {
        Node<elem> *tmp = head;
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
bool LinkList<elem>::append(const elem &element) {
    if (listSize == 0) {
        head = new Node<elem>(element);
    } else {
        Node<elem> *tmp = head;
        while (tmp->next) {
            tmp = tmp->next;
        }
        tmp->next = new Node<elem>(element);
    }
    ++listSize;
    return true;
}

template <class elem>
bool LinkList<elem>::insert(const elem &element, int pos) {
    if (pos > listSize)
        return false;
    if (listSize == 0) {
        head = new Node<elem>(element);
    } else {
        Node<elem> *tmp = head;
        for (int i = 0; i < pos; ++i) {
            tmp = tmp->next;
        }
        tmp->next = new Node<elem>(element, tmp->next);
    }

    ++listSize;
    return true;
}

template <class elem>
bool LinkList<elem>::remove(elem &element) {
    return true;
}

#endif //DATASTRUCTURE_LINKLIST_H
