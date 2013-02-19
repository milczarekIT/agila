#include "Exception.h"

Exception::Exception()
{
}

Exception::Exception(QString sourceMethod, QString message)
{
    this->sourceMethod = sourceMethod;
    this->message = message;
}

QString Exception::getMessage() {
    return message;
}

QString Exception::getSourceMethod() {
    return sourceMethod;
}
