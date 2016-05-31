//
// Created by tew on 2016/5/30.
//

#ifndef DATASTRUCTURE_ARRAYQUEUE_H
#define DATASTRUCTURE_ARRAYQUEUE_H

template <class elem>
class ArrayQueue {
private:
    elem *queueArray;
    int head;
    int tail;
    int size;
    int maxSize;
public:
    ArrayQueue(int size){
        this->maxSize = size;
        this->size = 0;
        head = tail = 0;
        queueArray = new elem[size];
    }

    ~ArrayQueue(){
        delete[] queueArray;
    }

    void clear() {
        head = tail;
        size = 0;
    }

    bool enqueue(const elem &element){
        if(size >= maxSize){
            return false;
        }
        if(tail + 1 >= maxSize) {
            tail = 0;
            queueArray[tail] = element;
        }else{
            queueArray[++tail] = element;
        }
        ++size;
        return true;
    }

    bool dequeue(elem &element){
        if(size == 0){
            return false;
        }
        if(head == maxSize - 1){
            element = queueArray[head];
            head = 0;
        }else{
            element = queueArray[++head];
        }
        --size;
        return true;
    }

    void print(){
        int temp = head;
        int print = 0;
        while(print != size){
            if(temp == maxSize - 1){
                std::cout<<temp<<": "<<queueArray[temp]<<" ";
                temp = 0;
            }else{
                std::cout<<temp<<": "<<queueArray[temp]<<" ";
                temp++;
            }
            ++print;
        }
        std::cout<<std::endl;
    }
};
#endif //DATASTRUCTURE_ARRAYQUEUE_H
