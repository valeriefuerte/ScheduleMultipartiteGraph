#ifndef REPODATA_H
#define REPODATA_H
#include <stack>
#include <exception>
#include <stdexcept>
#include "exceptions/nonextelementiteratorexception.h"


template<class T>
class RepoIterator
{
private:
    std::stack<T*> nodes;
    void pushChildren(T *currentNode);
public:
    RepoIterator(T *node) {
        pushChildren(node);
    }
    bool hasNext();
    T* next();
};


template<class T>
void RepoIterator<T>::pushChildren(T *currentNode)
{
    if (currentNode == nullptr) return;
    nodes.push(currentNode);
    for(auto iter = currentNode->getChildren()->begin(); iter!=currentNode->getChildren()->end(); ++iter)
    {
        pushChildren(*iter);
    }
}

template<class T>
bool RepoIterator<T>::hasNext()
{
    return !nodes.empty();
}

template<class T>
T* RepoIterator<T>::next()
{
    if (!hasNext())
    {
        throw stderr(this, new std::string("RepoIterator.h"), 46, new std::string("next()"));
        //throw NoNextElementIteratorException<RepoIterator<T>>(this, new std::string("repoiterator.h"), 46, new std::string("next()"));

    }

    T* res = nodes.top();
    nodes.pop();
    return res->getValue();
}

#endif // REPODATA_H
