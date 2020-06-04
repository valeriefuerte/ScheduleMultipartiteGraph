#ifndef NOPARENTNODEFOUNDBYVALUEEXCEPTION_H
#define NOPARENTNODEFOUNDBYVALUEEXCEPTION_H
#include "exceptions/noparentnodefoundexception.h"
#include <QString>

namespace GraphContainer {

template<class T>
class NoParentNodeFoundByValueException: public NoParentNodeFoundException<T>
{
private:
    T *parent;
    T *element;
public:
    NoParentNodeFoundByValueException(T *parent_, T *element_,  const QString *file_, int line_, const QString *func_) noexcept;
    T *getElement() const;
    T *getParentValue() const;
};

template<class T>
NoParentNodeFoundByValueException<T>::NoParentNodeFoundByValueException(T* parent_, T *element_, const QString *file_, int line_, const QString *func_) noexcept : NoParentNodeFoundException<T> (element_, file_, line_, func_)
{
    parent = parent_;
    element = element_;
}

template<class T>
T *NoParentNodeFoundByValueException<T>::getElement() const
{
    return element;
}

template<class T>
T *NoParentNodeFoundByValueException<T>::getParentValue() const
{
    return parent;
}
}
#endif // NOPARENTNODEFOUNDBYVALUEEXCEPTION_H
