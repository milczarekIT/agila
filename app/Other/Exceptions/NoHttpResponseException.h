#ifndef NOHTTPRESPONSEEXCEPTION_H
#define NOHTTPRESPONSEEXCEPTION_H

#include "Exception.h"

/**
  * Wyjątek zgłaszany, gdy brak odpowiedzi od serwera po wywołaniu HttpRequesta
  */
class NoHttpResponseException : public Exception
{
public:
    NoHttpResponseException(QString sourceMethod);
};

#endif // NOHTTPRESPONSEEXCEPTION_H
