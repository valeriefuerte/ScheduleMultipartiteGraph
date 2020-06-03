#include "exceptions/exception.h"
#include <ctime>

namespace GraphContainer {
    time_t GraphException::getTimeStamp() const
    {
        return timeStamp;
    }

    GraphException::GraphException(const QString *file_, int line_, const QString *func_)
    {
        file = file_;
        line = line_;
        func = func_;
        time(&timeStamp);
    }

    const QString *GraphException::getFile() const
    {
        return file;
    }

    int GraphException::getLine() const
    {
        return line;
    }

    const QString *GraphException::getFunc() const
    {
        return func;
    }
}
