#include <iostream>
#include "List/LinkList.h"

using namespace std;

int main() {
    LinkList<int> al;
    al.append(4);
    al.append(5);
    al.append(2);
    al.print();
    al.insert(9, 0);
    al.print();
    al.insert(20, 3);
    al.print();
    al.insert(30, 3);
    al.print();
    cout<<al.size()<<endl;
    cout<<al.getValue(0)<<endl;
    al.setPos(1);
    cout<<al.getValue()<<endl;
    al.prev();
    cout<<al.getValue()<<endl;
    al.next();
    al.next();
    cout<<al.getValue()<<endl;
    return 0;
}