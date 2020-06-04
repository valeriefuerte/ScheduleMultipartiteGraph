#ifndef NOPARENTNODEFOUNDEXCEPTION_H
#define NOPARENTNODEFOUNDEXCEPTION_H

#include "exceptions/exception.h"

namespace GraphContainer {

template<class T>
class NoParentNodeFoundException: public GraphException
{
private:
    T *element;
public:
    NoParentNodeFoundException(T *element_,  const QString *file_, int line_, const QString *func_) noexcept;
    T *getElement() const;
};

template<class T>
NoParentNodeFoundException<T>::NoParentNodeFoundException(T *element_, const QString *file_, int line_, const QString *func_) noexcept : GraphException (file_, line_, func_)
{
    element = element_;
}

template<class T>
T *NoParentNodeFoundException<T>::getElement() const
{
    return element;
}
}

#endif // NOPARENTNODEFOUNDEXCEPTION_H
