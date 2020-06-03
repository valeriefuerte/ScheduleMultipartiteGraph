#ifndef NoParentNodeFoundByIdException_H
#define NoParentNodeFoundByIdException_H

#include "exceptions/noparentnodefoundexception.h"
#include <QString>

namespace GraphContainer {

template<class T>
class NoParentNodeFoundByIdException: public NoParentNodeFoundException<T>
{
private:
    int parentId;
    T *element;
public:
    NoParentNodeFoundByIdException(int parentId_, T *element_,  const QString *file_, int line_, const QString *func_) noexcept;
    T *getElement() const;
    int getParentId() const;
};

template<class T>
NoParentNodeFoundByIdException<T>::NoParentNodeFoundByIdException(int parentId_, T *element_, const QString *file_, int line_, const QString *func_) noexcept : NoParentNodeFoundException<T> (element_, file_, line_, func_)
{
    parentId = parentId_;
    element = element_;
}

template<class T>
T *NoParentNodeFoundByIdException<T>::getElement() const
{
    return element;
}

template<class T>
int NoParentNodeFoundByIdException<T>::getParentId() const
{
    return parentId;
}


}

#endif // NoParentNodeFoundByIdException_H
