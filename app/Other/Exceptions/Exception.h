#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <QString>
#include <QDebug>

/**
  * Wyjątek wywoływany przez nieoczekiwane działanie programu
  * @author Bartosz Milczarek
  */
class Exception
{
protected:
    QString message;
    QString sourceMethod;
public:
    Exception();
    Exception(QString sourceMethod, QString message = "");

    QString getMessage();
    QString getSourceMethod();

};

#endif // EXCEPTION_H
