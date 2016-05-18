//
// Created by tew on 2016/5/18.
//

#ifndef DATASTRUCTURE_LINKLIST_H
#define DATASTRUCTURE_LINKLIST_H
#include <LinkList.h>
#include "List.h"

template <class elem>
class Node {
public:
    elem element;
    Node *next;

    Node(const elem &element, Node *next = NULL) {
        this->element = element;
        this->next = next;
    }

    Node(Node *next = NULL) {
        this->next = next;
    }
};

template <class elem>
class LinkList : public List<elem> {
private:
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

    bool remove(elem&);

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

    elem &getValue(int pos) const {
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
        while(tmp){
            std::cout<<tmp->element<<" ";
            tmp = tmp->next;
        }
        std::cout<<std::endl;
    }

    int size() const {
        return listSize;
    }

};

#endif //DATASTRUCTURE_LINKLIST_H
