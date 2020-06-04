#ifndef NONEXTELEMENTITERATOREXCEPTION_H
#define NONEXTELEMENTITERATOREXCEPTION_H

#include "exceptions/exception.h"

namespace GraphContainer {

template<class T>
class NoNextElementIteratorException: public GraphException
{
private:
    T *iterator;
public:
    NoNextElementIteratorException(T *iterator_, const QString *file_, int line_, const QString *func_);
    T *getIterator() const;
};


template<class T>
T *NoNextElementIteratorException<T>::getIterator() const
{
    return iterator;
}

template<class T>
NoNextElementIteratorException<T>::NoNextElementIteratorException(T *iterator_, const QString *file_, int line_, const QString *func_) : GraphException (file_, line_, func_)
{
    iterator = iterator_;
}
}
#endif // NONEXTELEMENTITERATOREXCEPTION_H
