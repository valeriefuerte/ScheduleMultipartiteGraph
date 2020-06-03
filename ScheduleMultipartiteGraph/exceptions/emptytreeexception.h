#ifndef EMPTYTREEEXCEPTION_H
#define EMPTYTREEEXCEPTION_H

#include "exceptions/exception.h"
namespace GraphContainer {
template <class T>
class EmptyGraphException : public GraphException
{
private:
    T *graphRoot;
public:
    EmptyGraphException(T *graphRoot_, const QString *file_, int line_, const QString *func_) noexcept;
    T *getGraphRoot() const;
};

template<class T>
EmptyGraphException<T>::EmptyGraphException(T *graphRoot_, const QString *file_, int line_, const QString *func_) noexcept : GraphException (file_, line_, func_)
{
    graphRoot = graphRoot_;
}

template<class T>
T *EmptyGraphException<T>::getGraphRoot() const
{
    return graphRoot;
}
}

#endif // EMPTYTREEEXCEPTION_H
