#ifndef TREEEXCEPTION_H
#define TREEEXCEPTION_H

#include <QString>

namespace GraphContainer {

class GraphException: public std::exception
{
protected:
    time_t timeStamp;
    const QString *file;
    int line;
    const QString *func;
public:
    GraphException(const QString *file_, int line_, const QString *func_);
    const QString *getFile() const;
    int getLine() const;
    const QString *getFunc() const;
    time_t getTimeStamp() const;
};
}

#endif // TREEEXCEPTION_H
