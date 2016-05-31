#include <iostream>
#include "List/ArrayQueue.h"
#include "List/ListQueue.h"

using namespace std;

int main() {
    ListQueue<int> aq;
    aq.enqueue(6);
    aq.enqueue(3);
    aq.enqueue(12);
    aq.enqueue(9);
    aq.enqueue(2);
    aq.print();
    int a;
    aq.dequeue(a);
    aq.print();
    aq.dequeue(a);
    aq.print();
    aq.enqueue(20);
    aq.print();
    return 0;
}