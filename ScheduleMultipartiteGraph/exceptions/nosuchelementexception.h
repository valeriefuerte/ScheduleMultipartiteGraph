#ifndef NOSUCHELEMENTEXCEPTION_H
#define NOSUCHELEMENTEXCEPTION_H

#include "exceptions/exception.h"

namespace GraphContainer {

template<class T>
class NoSuchElementException: public GraphException
{
private:
    T *element;
public:
    NoSuchElementException(T *element_,  const QString *file_, int line_, const QString *func_) noexcept;
    T *getElement() const;
};

template<class T>
NoSuchElementException<T>::NoSuchElementException(T *element_, const QString *file_, int line_, const QString *func_) noexcept : GraphException (file_, line_, func_)
{
    element = element_;
}

template<class T>
T *NoSuchElementException<T>::getElement() const
{
    return element;
}

}

#endif // NOSUCHELEMENTEXCEPTION_H
