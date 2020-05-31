#ifndef GRAPHEXCEPTION_H
#define GRAPHEXCEPTION_H

#include <QString>
#include <QTime>

class GraphException: public std::exception
{


protected:
    QString *msg;
    int line;
public:
    GraphException();

};

#endif // GRAPHEXCEPTION_H
