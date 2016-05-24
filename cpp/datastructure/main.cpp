#include <iostream>
#include "List/Stack.h"

using namespace std;

int main() {
    Stack<int> al;
    al.push(5);
    al.push(2);
    al.push(10);
    al.print();
    int a;
    al.pop(a);
    al.print();
    cout<<al.size()<<endl;
    al.flush();
    cout<<al.size()<<endl;
    al.print();
//    al.insert(9);
//    al.print();
//    al.insert(20);
//    al.print();
//    al.insert(30);
//    al.print();
//    cout<<al.size()<<endl;
//    cout<<al.getValue(0)<<endl;
//    al.setPos(1);
//    cout<<al.getValue()<<endl;
//    al.prev();
//    cout<<al.getValue()<<endl;
//    al.next();
//    al.next();
//    cout<<al.getValue()<<endl;
    return 0;
}