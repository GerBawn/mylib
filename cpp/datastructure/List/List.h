//
// Created by tew on 2016/5/17.
//

#ifndef DATASTRUCTURE_LIST_H
#define DATASTRUCTURE_LIST_H
template<class elem> class List{
public:
    virtual void clear() = 0;
    virtual bool insert(const elem&, int pos) = 0;
    virtual bool append(const elem&) = 0;
    virtual bool remove(elem&) = 0;
    virtual void setStart() = 0;
    virtual void setEnd() = 0;
    virtual void prev() = 0;
    virtual void next() = 0;
    virtual bool setPos(int pos) = 0;
    virtual elem& getValue(int pos) const = 0;
    virtual void print() const = 0;
    virtual int size() const = 0;
};
#endif //DATASTRUCTURE_LIST_H
