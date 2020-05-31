#ifndef MYEXCEPTION_H
#define MYEXCEPTION_H
#include <QException>
#include <QErrorMessage>



class MyException : public QException
{
public:
   void raise() const override;
   MyException *clone() const override;


};


void MyException::raise() const {
    throw *this;
}

MyException *MyException::clone() const {
    return new MyException(*this);
}

#endif // MYEXCEPTION_H
