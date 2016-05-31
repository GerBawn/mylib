//
// Created by tew on 2016/5/30.
//

#ifndef DATASTRUCTURE_LISTQUEUE_H
#define DATASTRUCTURE_LISTQUEUE_H
#include "../Node.h"

template <class elem>
class ListQueue{
private:
    Node<elem> *head, *tail;
    int listSize;
public:
    ListQueue(){
        listSize = 0;
        head = tail = nullptr;
    }

    ~ListQueue(){
        Node<elem> *temp;
        while(head != nullptr){
            temp = head;
            head = head->next;
            delete head;
        }
    }

    bool enqueue(const elem &element){
        Node<elem> *newNode = new Node<elem>(element);
        if(listSize == 0){
            head = tail = newNode;
        }else{
            tail->next = newNode;
            tail = tail->next;
        }
        ++listSize;
        return true;
    }

    bool dequeue(elem &element){
        if(listSize == 0){
            return false;
        }
        element = head->element;
        Node<elem> temp = head;
        head = head->next;
        delete temp;
        if(head == nullptr){
            tail = nullptr;
        }
        --listSize;
        return true;
    }

    void print(){
        Node<elem> *temp = head;
        while(temp != nullptr){
            std::cout<<temp->element<<" ";
            temp = temp->next;
        }
        std::cout<<std::endl;
    }
};
#endif //DATASTRUCTURE_LISTQUEUE_H
